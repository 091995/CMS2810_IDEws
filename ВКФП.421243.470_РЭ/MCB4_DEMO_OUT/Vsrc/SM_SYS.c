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

 \file      SMSys.h
 \brief     Модуль-обертка для расчета остальных модулей. (см. TSM_Sys)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru

 \defgroup  SMSys Модуль-обертка для расчета остальных модулей. (см. TSM_Sys)
 @{
*/

/*@{*/
#include "DSP28_Device.h"
#include "IQmathLib.h"
#include "main.h"

//! ИнициализациЯ системы управлениЯ после включениЯ

//!ИнициализациЯ некоторых модулей и настройка прерываний системы.
//!Здесь настраиваетсЯ большинство прерываний, однако некоторые настраиваютсЯ
//!в конкретных модулЯх (настример, CANOpen).
//! \memberof TSMSys
void SM_Sys_Init(TSM_Sys *p) {

    sw.HardwareType = 3;

    spimem.init(&spimem);
    cmd.all = 0;
    drv_status.all = 0;

    adc.init(&adc_calibration); /* Call init function for adc1 */

    sm_net.init(&sm_net); //Сетевая часть
    sm_prot.init(&sm_prot); //Защиты
    sm_cmd_logic.init(&sm_cmd_logic); //Логика включения/выключения
    sm_ctrl.init(&sm_ctrl); //Структура системы управления
    pwm.init(&pwm); //Модуль ШИМ
    cur_par.init(&cur_par); //Расчет текущих показателей привода
    leds.init(&leds);//светодиоды
    udControl.init(&udControl); //плавная зарядка ЗПТ через термисторы
    DIO_Init(); //дискретные входы/выходы
    FanControl.init(&FanControl); //вентилятор
    //глобальное времЯ (внешние или внутр. часы)
    global_time.init(&global_time);

    drv_params.sens_type = drv_params.sens_type & 7; //Отсекаем верхнюю часть переменной, там мусор
    if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //В типе датчика выбран ДПР на элементах Холла
        DPReCAP.Init(&DPReCAP); //ДПР иниц.
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER){ //В типе датчика выбран энкодер
        //настроим квадратурный декодер
        //posspeedEqep.speed_nom = drv_params.speed_nom;    //базовая скорость
        posspeedEqep.pole_pairs = drv_params.p;    //кол-во пар полюсов дригателя
        posspeedEqep.direction = 1;    //направление движения
        posspeedEqep.RevolutionCounter=0;
        posspeedEqep.init(&posspeedEqep);//инициализация модуля энкодера
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //В типе датчика выбран датчик с SSI интерфейсом. Читайте заголовочник модуля перед использованием!
        //настроим модуль датчика положения SSI
        SSI_Encoder.speed_nom = drv_params.speed_nom;    //базовая скорость
        SSI_Encoder.pole_pairs = drv_params.p;    //кол-во пар полюсов дригателя
        SSI_Encoder.rotation_dir = 0;    //направление движения
        SSI_Encoder.RevolutionCounter=0;
        SSI_Encoder.init(&SSI_Encoder);//Датчик положения SSI
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_ENC_HALL){
        //настроим квадратурный декодер
        DPReCAP.Init(&DPReCAP); //ДПР иниц.
        //posspeedEqep.speed_nom = drv_params.speed_nom;    //базовая скорость
        posspeedEqep.pole_pairs = drv_params.p;    //кол-во пар полюсов дригателя
        posspeedEqep.direction = 1;    //направление движения
        posspeedEqep.RevolutionCounter=0;
        posspeedEqep.init(&posspeedEqep);//инициализация модуля энкодера
    }

    //листалка аварий для отображения на пульте управления (UniCON)
    pult_faults_lister.num_of_words = 2;
    pult_faults_lister.out_refresh_devisor = 1000; //при вызове в мс таймере период обновления будет равен 1сек
    pult_faults_lister.w_ptrs[0] = (Uint16*) &sm_prot.masked_bit_fault1;//перебираются эти флаги аварий модуля защит
    pult_faults_lister.w_ptrs[1] = (Uint16*) &sm_prot.masked_bit_fault2;

    AutoOffset.FilterK = _IQ(0.00001);//постоянная времени фильтра для автосмещения АЦП
    AutoOffset.init(&AutoOffset); //авто смещение некоторых каналов АЦП (токи)

	//запускаем таймер CPU0
	CpuTimer0Regs.PRD.all = 14999;
	CpuTimer0Regs.TCR.bit.SOFT = 1;
	CpuTimer0Regs.TCR.bit.FREE = 1;
	CpuTimer0Regs.TCR.bit.TIE = 1;

	//запускаем таймер CPU2
	CpuTimer2Regs.PRD.all = 0xFFFFFFFF;
	CpuTimer2Regs.TCR.bit.SOFT = 1;
	CpuTimer2Regs.TCR.bit.FREE = 1;
	CpuTimer2Regs.TCR.bit.TIE = 1;

	//настройка 1мс таймера
	EvbRegs.T4PR = 4688; //;9375;
	EvbRegs.T4CON.all = 0x1440; //16x

	EvbRegs.EVBIMRB.bit.T4UFINT = 1;
	EvbRegs.EVBIFRB.bit.T4UFINT = 1;

	EvbRegs.EVBIMRA.bit.CMP6INT = 1;
	EvbRegs.EVBIFRA.bit.CMP6INT = 1;

	EALLOW;

	PieVectTable.T4UFINT = &EvbTimer4;
	PieVectTable.PDPINTA = &pdpinta_protect_isr;
	PieVectTable.CAPINT4 = &cap1_interrupt_isr;
	PieVectTable.CAPINT5 = &cap2_interrupt_isr;
	PieVectTable.CAPINT6 = &cap3_interrupt_isr;
	PieVectTable.TINT0 = &CPUTimer0_isr;

	EDIS;
	// Enable PIE  interrupt 3 for T4UFINT
	PieCtrlRegs.PIEIER5.all |= M_INT3;
	// Enable CPU INT5 for T4UFINT:
	IER |= M_INT5;

	// Enable CPU INT1 for PDPINTA:
	PieCtrlRegs.PIEIER1.all |= M_INT1;
	IER |= M_INT1;
	// Enable PIE interrupt 7 for TINT0
	PieCtrlRegs.PIEIER1.all |= M_INT7;
	IER |= M_INT1;
	// Enable CPU INT1 for CAP4INT:
	PieCtrlRegs.PIEIER5.all |= M_INT5;
	IER |= M_INT5;
	// Enable CPU INT2 for CAP5INT:
	PieCtrlRegs.PIEIER5.all |= M_INT6;
	IER |= M_INT5;
	// Enable CPU INT3 for CAP6INT:
	PieCtrlRegs.PIEIER5.all |= M_INT7;
	IER |= M_INT5;

	//сброс висЯщего флага аппаратной аварии (если есть)
	EvaRegs.EVAIFRA.all = (1 << 0);
	EvbRegs.EVBIFRA.all = (1 << 0);

    sm_sys.state = SYS_READY;

}

//!Медленный расчет (фоновый).

//!Вызов медленных расчетов остальных модулей
//! \memberof TSMSys
void SM_Sys_Slow_Calc(TSM_Sys *p) {


    //spimem.slow_calc(&UserMem);//пользовательская память в МК
    RTCclock.slowCalc(&RTCclock);//часы реального времени
    sm_prot.slow_calc(&sm_prot);//модуль защит
    sm_net.slow_calc(&sm_net); //обертка для вызова коммуникационных драйверов
    dlog.background_analyzer(&dlog); //фоновый обработчик модуля осциллографирования
    global_time.slow_calc(&global_time);
    rmp.slow_calc(&rmp); //пересчет интенсивности разгона из пользовтельской во внутреннее представление
    pwm.slow_calc(&pwm); //фоновый обработчик модуля ШИМ (пересчет пользовательских заданий)
    adc.slow_calc(&adc); //Фоновый обработчик АЦП
    cur_par.slow_calc(&cur_par); //Расчет текущих показателей привода
    AutoOffset.slow_calc(&AutoOffset);
    posspeedEqep.slow_calc(&posspeedEqep);//инициализация модуля энкодера
    RotorObserver.slow_calc(&RotorObserver);//наблюдатель потока ротора АД
    DIO_slow_calc(); //дискретные входы/выходы
    FanControl.slow_calc(&FanControl);//вентилятор

    //Пересчет коэффициентов для масштабирования токов и напряжений
    drv_params._1_Udc_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.Udc_nom));
    drv_params._1_I_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.I_nom));
    drv_params._1_U_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.U_nom));

    if (sw.Reboot & 1) { //команда перезагрузки
        sw.Reboot = 0; //сбрасываем её
        if (sm_ctrl.state == CTRL_STOP) { //перезагружаемсЯ только в останове
            //выполнЯем сброс проца с помощью WatchDog
            EALLOW;
            SysCtrlRegs.WDCR = 0x28;
            SysCtrlRegs.WDKEY = 0xFF;       //немедленно вызывает reset так как ключ неправильный
            EDIS;
        }
    }

    //вызов расчета смещения АЦП для токов фаз
    //Делаем расчет только в останове и отсутствии аварии
    if ((sw.AutoOffset & 1) &&
        (sm_ctrl.state == CTRL_STOP)){
        AutoOffset.Enabled=1;
    } else
        AutoOffset.Enabled=0;

}

void SM_Sys_ms_Calc(TSM_Sys *p) {
    sm_cmd_logic.ms_calc(&sm_cmd_logic); //Обработка команд управления
    sm_net.ms_calc(&sm_net); //обертка для вызова коммуникационных драйверов
    adc.ms_calc(&adc); //АЦП
    sm_prot.ms_calc(&sm_prot); //Защиты
    AutoOffset.ms_calc(&AutoOffset); //авто смещение некоторых каналов АЦП

    leds.msCalc(&leds);//светодиоды
    RTCclock.msCalc(&RTCclock);//часы
    //spimem.ms_calc(&UserMem);//пользовательская память в МК
    if ((drv_params.sens_type == 2) || (drv_params.sens_type == 3)){ //В типе датчика выбран ДПР Холла
        DPReCAP.ms_calc(&DPReCAP);
    }
    global_time.ms_calc(&global_time);

    DIO_fast_calc(); //дискретные входы/выходы
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(SM_SYS_Fast_Calc,"secureRamFuncs");
#endif

//!Быстрый расчет (обычно 10кГц).
//!Вызов быстрых расчетов остальных модулей
//! \memberof TSMSys
void SM_Sys_Fast_Calc(TSM_Sys *p) {
    sm_net.fast_calc(&sm_net);//расчет коммуникационных драйверов
    if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER) //В типе датчика выбран энкодер
        posspeedEqep.calc(&posspeedEqep); //ДПР энкодер
    if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //В типе датчика выбран ДПР Холла

        DPReCAP.Angle6Calc(&DPReCAP); //ДПР Холл, получение угла с точнгстью 60 градусов (результат в DPReCAP.Angle6)
        DPReCAP.AngleErrorCalc(&DPReCAP);
        if (DPReCAP.CAPCalcEna1==0){
            DPReCAP.CAPCalcEna1=1;
            EvbRegs.EVBIFRC.bit.CAP4INT = 1; // Сбрасываем флаг прерываниЯ
        }
        if (DPReCAP.CAPCalcEna2==0){
            DPReCAP.CAPCalcEna2=1;
            EvbRegs.EVBIFRC.bit.CAP5INT = 1; // Сбрасываем флаг прерываниЯ
        }
        if (DPReCAP.CAPCalcEna3==0){
            DPReCAP.CAPCalcEna3=1;
            EvbRegs.EVBIFRC.bit.CAP6INT = 1; // Сбрасываем флаг прерываниЯ
        }

        DPReCAP.AngleCalc(&DPReCAP); //ДПР Холл, интерполяция угла положения (результат в DPReCAP.Angle)
        DPReCAP.SpeedCalc(&DPReCAP); //ДПР Холл, расчет скорости вращения (DPReCAP.speed)
        //DPReCAP.calc_10k(&DPReCAP); //ДПР Холл, служебные функции
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //Датчик с интерфейсом SSI. Перед употреблением читайте заголовочный файл!
        SSI_Encoder.calc(&SSI_Encoder);//Датчик положения SSI
    }

    adc.fast_calc(&adc); //АЦП
    dlog.update(&dlog); //Осциллографирование данных
    sm_prot.fast_calc(&sm_prot); //Защиты
    sm_ctrl.fast_calc(&sm_ctrl); //Главный дискретный автомат системы управления
    udControl.calc(&udControl);//Плавная зарядка ЗПТ через термисторы

    CANtoRS.calc_10k(&CANtoRS);

    global_time.calc(&global_time);

    cur_par.calc(&cur_par); //Расчет текущих показателей привода
    drv_params.sens_type = drv_params.sens_type & 7; //Отсекаем верхнюю часть переменной, там мусор

#ifdef WATCHDOG_ON
    WatchDog.calc();//если сторожевой таймер используется, сбрасываем его здесь
#endif //WATCHDOG_ON
}

/*@}*/

