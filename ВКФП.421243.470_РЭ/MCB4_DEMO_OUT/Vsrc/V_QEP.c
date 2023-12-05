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

 \file      V_posspeed_eQEP.h
 \brief     Модуль реализации квадратурного энкодера QEP
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 @{*/

#include "main.h"


void POSSPEEDEQEP_init(TEncoder *p) {
    //инит регистров CAP
    EvaRegs.CAPCON.all = QEP_CAP_INIT_STATE;
    //инит таймера ака счетчика импульсов энкодера
    EvaRegs.T2CON.all = QEP_TIMER_INIT_STATE;
    //период таймера в 4 раза больше разрешения датчика, тк считаются передний и задний фронты 2 каналов
    //-1 нужен, чтобы таймер считал от 0 до 9999
    EvaRegs.T2PR = p->resolution * 4 - 1;

    //Вкл. прием индексной метки
    EvaRegs.EXTCON.bit.QEPIE = 1;
    //Квалификатор индексной метки: принимать ее только тогда, когда по каналам A и B единица
    EvaRegs.EXTCON.bit.QEPIQEL = 1;

    EALLOW;
    //ножки А8/А9/А10 под QEP
    GpioMuxRegs.GPAMUX.all |= 0x0700;
    //фильтр GPIO - период выборки = QUALPRD x SYSCLK
    GpioMuxRegs.GPAQUAL.BIT.QUALPRD = 5;
    EDIS;
    //1/разрешение
    //было: деление на разрешение в формате _IQ16.
    //При разрешении датчика 2500 меток, обратная величина равна: 1/2500*2^16 = 26.2144,
    //дробная часть 0.2144 отбрасывается, из-за чего сильно теряется точность, и в момент, когда приходит метка 9999,
    //механический угол равен 0.991, а электрический и подавно 0.967.
    //Из-за этого появляются скачки в скорости, при прохождении меток через 0 или через период.
    ///p->_1_resol = _IQ16div(_IQ16(1.0), (p->resolution << 16));

    //При таком большом разрешении, ни в какие приличные форматы IQ данная величина не влезет.
    //Поэтому теперь считаем ее по-простому в IQ24:
    p->_1_resol = _IQ(1.0/p->resolution);
    //счетчик оборотов
    p->RevolutionCounter = 0;
}

//ФункциЯ расчёта скорости
#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(POSSPEEDEQEP_Calc,"secureRamFuncs");
#endif
void POSSPEEDEQEP_FastCalc(TEncoder *p) {
    //состояние ножек
    p->GPIOsValue = (Uint16) GpioDataRegs.GPADAT.bit.GPIOA8 +
                    ((Uint16) GpioDataRegs.GPADAT.bit.GPIOA9 << 1) +
                    ((Uint16) GpioDataRegs.GPADAT.bit.GPIOA10 << 2);

    //захват положения меток: текущее кол-во меток
    p->posCnt = EvaRegs.T2CNT;

    //коэффициент перевода производной от угла (вычисляемую неизвестно в чем) в скорость
    //сдвиг на 3 чтобы результат деления не переполнил 127,
    //потом при использовании коэфа сдвинется назад на 3
    p->KThetaToSpeed=_IQdiv(_IQ(1.0),_IQmpyI32(drv_params.freq_nom,FAST_CALC_TS)<<3);

    //Было: расчёт механического угла в о.е. (IQ24(1.0) == 2pi)
    //делим текущее кол-во меток на разрешение ДПРа в формате IQ16:
    //для этого текущее кол-во меток сдвигаем на 16, умножаем на величину, обратную разрешению.
    //итоговый угол должен быть в формате IQ24, но, поскольку кол-во меток в 4 раза больше резрешения,
    //сдвигаем итоговый результат на 6, а не на 8 (4 == << 2)
    ///p->thetaMech = _IQ16mpy(((int32) p->posCnt) << 16, p->_1_resol) << 6;

    //Стало: поскольку "_1_resol" у нас в форме IQ24 ради сохранения точности,
    //после перемножения "_IQ16mpy(((int32) p->posCnt) << 16, p->_1_resol)" результат будет больше правильного в 24 - 16 = 8 раз.
    //И если раньше для приведения к формату IQ24 требовалось сдвинуть результат влево на 6 (см. выше),
    //то теперь мы его сдвигаем на 8 - 6 = 2 вправо. Проще простого!
    p->thetaMech = _IQ16mpy(((int32) p->posCnt) << 16, p->_1_resol) >> 2;
    p->thetaMech &= 0x00FFFFFF;

    //расчет электрического угла: больше механического в число пар полюсов + смещение
    p->theta_elec = _IQmpy(p->thetaMech, _IQ(p->pole_pairs)) + p->AngleOffset;
    p->theta_elec = p->theta_elec & 0x00FFFFFF;

    //фильтр электрического угла
    if (p->thetaElFilterK != 0) {
        p->thetaElFiltered = p->thetaElFiltered + _IQmpy(p->thetaElFilterK,
                                 ((p->theta_elec - p->thetaElFiltered + _IQ(0.5)) & 0x00FFFFFF) - _IQ(0.5));
        p->thetaElFiltered &= 0x00FFFFFF;
    } else p->thetaElFiltered = p->theta_elec;

    p->dThetaEl = p->theta_elec - p->thetaElPrev;
    //если приращение меток положительное
    if (p->dThetaEl > 0) {
        //если едем назад и проскочили через ноль
        if (p->dThetaEl > _IQ(0.5))
            p->dThetaEl = p->theta_elec - (_IQ(1.0) + p->thetaElPrev);
    } else {
        //если едем вперед и проскочили период
        if (labs(p->dThetaEl) > _IQ(0.5))
            p->dThetaEl = _IQ(1.0) - p->thetaElPrev + p->theta_elec;
    }

    //Считаем приращение угла. Сдвиги <<8 и >>8 обеспечивают правильный учет перехода через 0 градусов
    ///p->dThetaEl = ((p->thetaEl << 8) - (p->thetaElPrev << 8)) >> 8;

    //расчет скорости
    p->speed_elec = _IQmpy(p->dThetaEl, p->KThetaToSpeed) << 3;

    //подсчет количества полных оборотов
    if (p->thetaMech - p->thetaMechPrev > _IQ(0.5))
        p->RevolutionCounter++;
    if (p->thetaMech - p->thetaMechPrev < _IQ(-0.5))
        p->RevolutionCounter--;

    //Считаем приращение угла. Сдвиги <<8 и >>8 обеспечивают правильный учет перехода через 0 градусов
    p->thetaMechDelta = ((p->thetaMech << 8) - (p->thetaMechPrev << 8)) >> 8;

    //Если разница между текущим приращением угла и предыдущим больше 5 градусов
    if (labs(p->thetaMechDelta - p->thetaMechDeltaPrev) > _IQ(5.0/360)) {
        //пропускаем несколько тактов, чтобы не ловить ошибку при подаче питания
        if (sm_prot.poweredOk > 10)
            sm_prot.bit_fault1 |= F_ENCODER_FAULT;
    }

    //сохраняем значения углов для следующей итерации
    p->thetaMechPrev = p->thetaMech;
    p->thetaElPrev = p->theta_elec;
    p->thetaMechDeltaPrev = p->thetaMechDelta;

    //инерционный фильтр для скорости
    if (p->speedF.T != 0) {
        p->speedF.input = p->speed_elec;
        p->speedF.calc(&p->speedF);
        p->speed_elec = p->speedF.output;
    }
}

//! \memberof TposspeedEqep
void POSSPEEDEQEP_SlowCalc(TEncoder *p) {
    p->_1_resol = _IQ(1.0/p->resolution);
    EvaRegs.T2PR = p->resolution * 4 - 1;

    //Включение/выключение индексной метки
    if (p->indexEnable == 0)
        EvaRegs.EXTCON.bit.QEPIE = 0;
    else
        EvaRegs.EXTCON.bit.QEPIE = 1;

}

