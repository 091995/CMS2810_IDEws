/*!
     Copyright 2023 ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 
 \file      V_PWM_Module.c
 \brief     Модуль реализации векторной ШИМ (см. TPWM_Module)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_PWM_Module 
 @{*/


#include "IQmathLib.h"          // библиотека IQmath
#include "V_PWM_Module.h"
#include "main.h"

#if defined(HW_MOTORCONTROLBOARD)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

//! Ограничения величины "мёртвого времени"
#if defined(HW_MOTORCONTROLBOARD)
//! для одноплатного инвертора нельзя меньше 3мкс, чтобы не сжечь
#define DEAD_BAND_MIN	_IQ(3)
#define DEAD_BAND_MAX	_IQ(10)
#else
#define DEAD_BAND_MIN	_IQ(0)
#define DEAD_BAND_MAX	_IQ(10)
#endif

//! Инициализация

//инициализациЯ без использованиЯ векторного дискретного автомата
void PWM_6_12_Init_No_SV_Eva(TPWM_Module *p) {

    p->slow_calc(p);
    EvaRegs.T1PR=4000;//чтобы как-то тикало
    p->k_pwm=4000;
    p->FreqPrev=0;//чтобы пересчиталась частота

    if (sm_sys.IntEna)
        DINT;
    EvaRegs.T1CNT = 3;
    if (sm_sys.IntEna)
        EINT;

    EvaRegs.T1CON.bit.TENABLE = 1; //иначе не работает АЦП (вроде бы)

    EvaRegs.T1CON.all = PWM_INIT_STATE; /* Symmetrical Operation         */
    EvaRegs.DBTCONA.all = PWM_DBTCON_INIT_STATE;
    EvaRegs.ACTRA.all = PWM_ACTR_INIT_STATE;
    //включает сравнение, когда перегружать регистр сравнениЯ, Space PWM enabler,
    //когда перегружать control регистр, включить выходы сравнениЯ, trip
    EvaRegs.COMCONA.all=0;//без этого иногда ШИм глючит. Типа "резета" будет
    EvaRegs.COMCONA.all = 0x8007; //0xA007 - 1010000000000111
    //0x8007=1000000000000111
    EvaRegs.CMPR1 = 0xffff;
    EvaRegs.CMPR2 = 0xffff;
    EvaRegs.CMPR3 = 0xffff;
    EALLOW;
    /* Enable EALLOW */
    GpioMuxRegs.GPAMUX.all |= 0x003F;
    GpioMuxRegs.GPBMUX.all &= ~0x003F;
    GpioMuxRegs.GPDMUX.bit.T1CTRIP_PDPA_GPIOD0 = 1;
    EDIS;
    /* Disable EALLOW */
    p->EvXRegs = &EvaRegs;
}

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {
    PWM_6_12_Init_No_SV_Eva(p);

    EvaRegs.GPTCONA.bit.T1TOADC = 1;// T1 запускает ADC по underflow
}

//! Нормирование входных величин.

//!Учитывает компенсацию напряжения при изменении Ud,
//!выполняет вписывание вектора в окружность, если требуется, и
//!выполняет смену базиса, относительно которого идет нормировка.
//! \memberof TPWM_Module
void PWM_Module_NormInput(TPWM_Module* p) {
    _iq knorm;

    p->UalphaNorm=p->UalphaRef;
    p->UbetaNorm=p->UbetaRef;

    //находим амплитуду (без учета ограничения)
    p->U_mag=_IQmag(p->UalphaNorm,p->UbetaNorm);


    p->UdCorTmp=_IQdiv(_IQ(1.0),(_IQ(1.0)+_IQmpy((adc.Udc_meas-_IQ(1.0)),p->UdCompK)));
    //учет пульсаций напряжения на Ud
    if (p->UdCompEnable&1) { //он включен?
        p->UalphaNorm=_IQmpy(p->UalphaNorm, p->UdCorTmp);//изменим пропорционально коэфф-ту коррекции
        p->UbetaNorm=_IQmpy(p->UbetaNorm, p->UdCorTmp);//и это тоже
    }

    //вписывание заданной амплитуды напряжения в окружность, вписываемую в шестиугольник базывых векторов
    //когда U_lim=1.0, это и есть такая окружность. Бывает, что мы хотим вписывать в шестиугольник. Тогда просто задираем вверх огрианичение U_lim
    if (p->U_lim>_IQ(1.0/0.866)) //но нет смысла задирать выше максимально-реализ. напряжения (больше базового вектора)
        p->U_lim=_IQ(1.0/0.866);
    /* рассчитываем амплитуду вектора, который хотим отработать*/
    knorm=_IQmag(p->UalphaNorm,p->UbetaNorm);//плюс нормируем от 540 к 311
    if (knorm>=p->U_lim) { //он больше, чем наше ограничение?
        knorm=_IQdiv(p->U_lim,knorm);//в эту же переменную, для экономии, рассчитываем нормировку
        p->UalphaNorm=_IQmpy(knorm,p->UalphaNorm);//уменьшаем пропорционально нормировке
        p->UbetaNorm=_IQmpy(knorm,p->UbetaNorm);//и это
        p->ULimitation=1;//флаг о том, что идет ограничение напряжения
    } else
        p->ULimitation=0;

    /* рассчитываем приведенные вектора*/
    /* До этого момента напряжение нормировалось относительно
    базиса фазного амплитудного значения, например, 220*sqrt(2)
    Теперь производится переход, где за единицу принимается максимально
    реализуемое напряжение (длина базового вектора)
    */
    p->UalphaNorm=_IQmpy(p->UalphaNorm,_IQ(0.866));
    p->UbetaNorm=_IQmpy(p->UbetaNorm,_IQ(0.866));
}



//! Функция 6ти секторной векторной ШИМ

//! \memberof TPWM_Module
void PWM_Module_No_SV_Update(TPWM_Module *p) {
    _iq lambda1;
    _iq lambda2;
    _iq lambda3;

    int16 gamma;
    int16 gamma1;
    long tmp_pwm;

    //Присвоение трех уставок сравнения только если счетчик таймера далек от нуля, чтобы
    //предотвратить частичное применение скважностей, что в векторной ШИМ может быть критично и испортить период ШИМ.
    DINT;
    if (abs(p->EvXRegs->T1CNT) > 30) {
        p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
        p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
        p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
        p->EvXRegs->T1PR = p->k_pwm;
    }
    EINT;

    PWM_Module_NormInput(p);

    //Расчет скважностей по методу Изосимова.
    //Подробнее см. диссертацию Чуева П.В. http://motorcontrol.ru/wp-content/uploads/2015/11/Chuev_vector_control.pdf
    tmp_pwm = _IQmpy(_1_SQRT3,p->UbetaNorm);  /*делим на корень из 3*/
    lambda1 = _IQmpy(p->k_pwm,(p->UalphaNorm - tmp_pwm));
    lambda2 = _IQmpy(p->k_pwm,2*tmp_pwm);
    lambda3 = _IQmpy(p->k_pwm,p->UalphaNorm + tmp_pwm);


    if (lambda1<=0)
        if (lambda3>0) {
            gamma=lambda3;
            gamma1=-lambda1;
            p->sector=1; /*110 начало */
            p->GammaA=p->k_pwm-gamma;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-0;

        } else if (lambda2>0) {
            gamma=lambda2;
            gamma1=-lambda3;
            p->sector=2; /*011 начало */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-gamma1;
            /*011 начало */
        } else if (lambda1!=0) {
            gamma=-lambda1;
            gamma1=-lambda2;
            p->sector=3; /*011 начало */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-gamma;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*011 начало */
        } else {
            gamma=-lambda3;
            gamma1 = lambda1;
            p->sector= 4; /*101 начало */
            p->GammaA=p->k_pwm-gamma1;
            p->GammaB=p->k_pwm-0;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*101 начало */

        }
    else if (lambda2>0) {
        gamma=lambda1;
        gamma1=lambda2;
        p->sector= 0; /*110 начало */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-gamma1;
        p->GammaC=p->k_pwm-0;
        /*110 начало */
    } else if (lambda3<0) {
        gamma=-lambda3;
        gamma1 = lambda1;
        p->sector= 4; /*101 начало */
        p->GammaA=p->k_pwm-gamma1;
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-(gamma+gamma1+1);
        /*101 начало */
    } else {
        gamma=-lambda2;
        gamma1=lambda3;
        p->sector=5; /*101 начало */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-gamma;
        /*101 начало */
    }


    /*насыщения */

    if (p->GammaA<0) p->GammaA=0;
    if (p->GammaB<0) p->GammaB=0;
    if (p->GammaC<0) p->GammaC=0;

    if (p->GammaA>p->k_pwm) p->GammaA=p->k_pwm+1;
    if (p->GammaB>p->k_pwm) p->GammaB=p->k_pwm+1;
    if (p->GammaC>p->k_pwm) p->GammaC=p->k_pwm+1;

    //Присвоение трех уставок сравнения только если счетчик таймера далек от нуля, чтобы
    //предотвратить частичное применение скважностей, что в векторной ШИМ может быть критично и испортить период ШИМ.
    //Второй раз - чтобы предотвратить ситуацию с постоянной "незагрузкой" при равенстве частот расчета и ШИМ
    DINT;
    if (abs(p->EvXRegs->T1CNT) > 30) {
        p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
        p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
        p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
        p->EvXRegs->T1PR = p->k_pwm;
    }
    EINT;
}

//! Функция синусоидальной ШИМ

//! \memberof TPWM_Module
void PWM_Module_Sin_Update(TPWM_Module *p) {
	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;


	p->UalphaNorm = p->UalphaRef;
	p->UbetaNorm = p->UbetaRef;

	//находим амплитуду (без учета ограничения)
	p->U_mag = _IQmag(p->UalphaNorm, p->UbetaNorm);

	/* рассчитываем амплитуду вектора, который хотим отработать*/
	knorm = _IQmag(p->UalphaNorm, p->UbetaNorm);
	if (knorm >= p->U_lim) { //он больше, чем наше ограничение?
		knorm = _IQdiv(p->U_lim, knorm); //в эту же переменную, для экономии, рассчитываем нормировку
		p->UalphaNorm = _IQmpy(knorm, p->UalphaNorm); //уменьшаем пропорционально нормировке
		p->UbetaNorm = _IQmpy(knorm, p->UbetaNorm); //и это
		p->ULimitation = 1; //флаг о том, что идет ограничение напряжения
	} else
		p->ULimitation = 0;

	//Нормирование входного напряжения. Так как синусоидальная ШИМ формирует на 0.866 меньшее напряжение,
	//чем векторная ШИМ (270В амплитудного фазного напряжения вместо 311В), то для того, чтобы при том же задании в переменных
	//p->UalphaNorm, p->UbetaNorm получилось то же самое напряжение на выходе, что и в векторной ШИМ, нужно задания увеличить в 1/0.866 раз.
	//Деление на два нужно для последующих формул, чтобы переменые менялись в половинном от максимального диапазоне.
	p->UalphaNorm = _IQmpy(p->UalphaNorm, _IQ(1/0.866/2));
	p->UbetaNorm = _IQmpy(p->UbetaNorm, _IQ(1/0.866/2));

	/*фазное преобразование из системы альфа, бетта в a,b,c */

	PhasePtsA = _IQ(0.5) - (p->UalphaNorm);
	PhasePtsB = _IQ(0.5) - (_IQmpy(p->UbetaNorm,_IQ(0.8660254)) - (p->UalphaNorm >> 1));
	PhasePtsC = _IQ(0.5) - (-_IQmpy(p->UbetaNorm, _IQ(0.8660254)) - (p->UalphaNorm >> 1));

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	/*насыщения */

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;

    p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
    p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
    p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
}

//! Функция ШИМ с раздельными фазами (для модели SRM)

//! \memberof TPWM_Module
void PWM_Module_Separate_Update(TPWM_Module *p) {
	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;

	p->UPhARef = _IQmpy(p->UPhARef, _IQ(0.5));
	p->UPhBRef = _IQmpy(p->UPhBRef, _IQ(0.5));
	p->UPhCRef = _IQmpy(p->UPhCRef, _IQ(0.5));

	PhasePtsA = _IQ(0.5) - p->UPhARef;
	PhasePtsB = _IQ(0.5) - p->UPhBRef;
	PhasePtsC = _IQ(0.5) - p->UPhCRef;

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	/*насыщения */

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;

    p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
    p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
    p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
}

void PWM_Module_DC_Update(TPWM_Module *p)
{
	int32 UalphaRef = 0, UbetaRef = 0;
	int32 gamma1_DC = 0, gamma2_DC = 0;
	int32 temp32;

	UalphaRef = p->UalphaRef;
	UbetaRef = p->UbetaRef;

	if (UalphaRef > _IQ(1))
		UalphaRef = _IQ(1);
	else if (UalphaRef < _IQ(-1))
		UalphaRef = _IQ(-1);

	if (UbetaRef > _IQ(1))
		UbetaRef = _IQ(1);
	else if (UbetaRef < _IQ(0))
		UbetaRef = _IQ(0);

	//данное преобразование даёт возможность отрабатывать напряжения в диапазоне -1 - 0 - +1 (в относительных единицах)
	//Напряжение 1 - скважность (1/2 + 0.5) = 1, Напряжение 0 - скважность 0,5 и т.д.
	gamma1_DC = -(UalphaRef >> 1) + _IQ(0.5); // (IQ), Приводим заданное напряжение к соответствующей скважности.

	//На низких частотах величина p->k_pwm большая, значит большой может быть и temp32.
	//по-этому для расчётов целесообразно использовать формат iq16.
	gamma1_DC = gamma1_DC >> 8; // (IQ16) переводим то, что выше, в iq16.
	temp32 = _IQ16mpy(gamma1_DC, _IQ16(p->k_pwm)); // (IQ16) переводим скважность в величину для загрузки в регистр сравнения.
	p->GammaA = temp32 >> 16; // (IQ0) Загружем целую часть в регистр сравнения.
	p->GammaB = p->k_pwm - p->GammaA; // в регистре сравнения EPwm2 то же, что и в EPwm1.

	//На низких частотах величина p->k_pwm большая, значит большой может быть и temp32.
	//по-этому для расчётов целесообразно использовать формат iq16.
	gamma2_DC = UbetaRef >> 8; // (IQ16) переводим то, что выше, в iq16.
	temp32 = _IQ16mpy(gamma2_DC, _IQ16(p->k_pwm)); // (IQ16) переводим скважность в величину для загрузки в регистр сравнения.
	p->GammaC = p->k_pwm - (temp32 >> 16); // (IQ0) Загружем целую часть в регистр сравнения.

    p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
    p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
    p->EvXRegs->CMPR3 = (Uint16) p->GammaC;

}

//! Функция ШИМ для начальной зарядки будстрепных конденсаторов инвертора

//! \memberof TPWM_Module
void PWM_Module_ChargingMode(TPWM_Module *p) {
	p->GammaA = p->k_pwm;
	p->GammaB = p->k_pwm;
	p->GammaC = p->k_pwm;

    DINT;
    if (abs(p->EvXRegs->T1CNT) > 30) {
        p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
        p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
        p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
    }
    EINT;
}

//! Общая функция-обертка для расчета ШИМ

//Вызывающает ту версию ШИМ (ту функцию), что выбрана в настройках.

//! \memberof TPWM_Module
void PWM_Module_Update(TPWM_Module *p) {

    p->PWM_type = p->PWM_type & 1;

    if (p->ChargingMode)
		PWM_Module_ChargingMode(p);
	else {
		switch (p->PWM_type) {
		case PWM_TYPE_6SECT_NO_SV: {
			PWM_Module_No_SV_Update(p);
			break;
		}
		case PWM_TYPE_SIN_PWM: {
			PWM_Module_Sin_Update(p);
			break;
		}
		case PWM_TYPE_DC_DRIVE: {
			PWM_Module_DC_Update(p);
			break;
		}
		case PWM_TYPE_SRD: {
			PWM_Module_Separate_Update(p);
			break;
		}
		}
	}

}

//! Медленный расчет

//! Пересчитываются введенные пользователем величины
//! Величина мертвого времени, частота ШИМ и т.п.

//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *p) {
	Uint16 tmp;

	//частота ШИМ. Смена "на лету".
	if (p->FreqPrev != p->Frequency) { //сменили частоту
		DINT; //запрещение прерываний
        //проверка максимума/минимума
        if (p->Frequency < PWM_FREQ_MIN)
            p->Frequency = PWM_FREQ_MIN;
        if (p->Frequency > PWM_FREQ_MAX)
            p->Frequency = PWM_FREQ_MAX;
        //изменЯем период
        p->k_pwm = _IQ10div(_IQ10(150000), p->Frequency << 2) >> 10;        //период. В регистры запишется в калке ШИМа
        if (p->k_pwm<2000)
            p->k_pwm =2000;

		//посчитаем длину выборки для усреднения токов, исходя из частоты ШИМ
		adc.IASampleLength = (p->Frequency >> 10) / 10;	//Частота ШИМ в формате 22.10, приводим к инту и делим на 10 - частоту расчета системы управления
		if (adc.IASampleLength > 4)	//не более 4 точек
			adc.IASampleLength = 4;
		if (adc.IASampleLength < 1)	//не менее 1 точки
			adc.IASampleLength = 1;
		adc.IBSampleLength = adc.IASampleLength;
		adc.ICSampleLength = adc.IASampleLength;
		adc.UdcSampleLength = adc.IASampleLength;

		p->FreqPrev = p->Frequency; //предыдущая частота
		EINT;
	}
}

//! Функция включения ШИМ (включение инвертора)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//флаг "включено"

	// Снимаем принудительную установку выходов
    EvaRegs.COMCONA.all |= 0x0200;
	GPIO_INV_ON;

}

//! Функция выключения ШИМ (выключение инвертора)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//флаг "выключено"
	// Принудительно обнулим все ножки

    EvaRegs.COMCONA.all &= 0xfdff;
	GPIO_INV_OFF;

}

/*@}*/
