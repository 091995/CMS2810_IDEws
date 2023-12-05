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

 \file      V_DPR_eCAP.h
 \brief     // Модуль расчёта скорости и положениЯ по трём датчикам на элементах Холла.
 \author    ООО "НПФ Вектор". http://motorcontrol.ru

 \addtogroup
 @{*/

#include "main.h"

#define DPR_CHANNEL1_DATA (GpioDataRegs.GPBDAT.bit.GPIOB8==1)
#define DPR_CHANNEL2_DATA (GpioDataRegs.GPBDAT.bit.GPIOB9==1)
#define DPR_CHANNEL3_DATA (GpioDataRegs.GPBDAT.bit.GPIOB10==1)

/******************************************************************************
 Процедура инициализации
 ******************************************************************************/
void DPReCAP_Init(TDPReCAP* p) {

    //настраиваем мультиплицированные выходы на CAP
    EALLOW;

    GpioMuxRegs.GPBMUX.bit.CAP4Q1_GPIOB8 = 1;
    GpioMuxRegs.GPBDIR.bit.GPIOB8 = 0;

    GpioMuxRegs.GPBMUX.bit.CAP5Q2_GPIOB9 = 1;
    GpioMuxRegs.GPBDIR.bit.GPIOB9 = 0;

    GpioMuxRegs.GPBMUX.bit.CAP6QI2_GPIOB10 = 1;
    GpioMuxRegs.GPBDIR.bit.GPIOB10 = 0;

    EDIS;

    // Настройка CAP
    EvbRegs.CAPCONB.bit.CAPRES = 0; // сброс всех регистров CAP

    // ИнициализациЯ модулей захвата 1 и 2.
    EvbRegs.CAPCONB.bit.CAPQEPN = 1; // разрешение на модуль захвата CAP4 и CAP5
    EvbRegs.CAPCONB.bit.CAP45TSEL = 0; // устанавливаем CAP по таймеру 3

//  EvbRegs.CAPCONB.bit.CAP1EDGE = 0x1; // передний фронт
//  EvbRegs.CAPCONB.bit.CAP2EDGE = 0x1; // передний фронт
//  EvbRegs.CAPCONB.bit.CAP1EDGE = 0x2; // задний фронт
//  EvbRegs.CAPCONB.bit.CAP2EDGE = 0x2; // задний фронт
    EvbRegs.CAPCONB.bit.CAP4EDGE = 0x3; // передний и задний фронты
    EvbRegs.CAPCONB.bit.CAP5EDGE = 0x3; // передний и задний фронты

    EvbRegs.CAP4FIFO = 0;   // обнулЯем стек.
    EvbRegs.CAP5FIFO = 0;   // обнулЯем стек.
    EvbRegs.EVBIMRC.bit.CAP4INT = 1;    // Разрешаем прерывание.
    EvbRegs.EVBIMRC.bit.CAP5INT = 1;    // Разрешаем прерывание.

    // ИнициализациЯ модулЯ захвата 3.
    EvbRegs.CAPCONB.bit.CAP6EN = 1; // разрешение на модуль захвата CAP6
    EvbRegs.CAPCONB.bit.CAP6TSEL = 0; // устанавливаем CAP3 по таймеру 3

//  EvbRegs.CAPCON.bit.CAP3EDGE = 0x1; // передний фронт
//  EvbRegs.CAPCON.bit.CAP3EDGE = 0x2; // задний фронт
    EvbRegs.CAPCONB.bit.CAP6EDGE = 0x3; // передний и задний фронты

    EvbRegs.CAP6FIFO = 0;   // обнулЯем стек.
    EvbRegs.EVBIMRC.bit.CAP6INT = 1;    // Разрешаем прерывание.

    // Кол-во счётов таймера, соответствующее номинальной скорости.
    p->TsNom = ((150000000 / (drv_params.speed_nom * drv_params.p)) * 10);
    p->TsNomMilsec = (100000 / (drv_params.speed_nom * drv_params.p));

    DPReCAP_Angle6Calc(p);
    p->CAP_WrongEdgeCnt = 0;
}

/******************************************************************************
 Процедура расчёта угла.
 ******************************************************************************/
#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_Angle6Calc,"secureRamFuncs");
#endif

void DPReCAP_Angle6Calc(TDPReCAP* p) {
    int ch1;
    int ch2;
    int ch3;
    ch1=DPR_CHANNEL1_DATA;
    ch2=DPR_CHANNEL2_DATA;
    ch3=DPR_CHANNEL3_DATA;
    if (p->Channel2Inversion)
        ch2=!ch2;
    // Формируем код по состоЯнию ножек.
    p->DPReCAP_CODE.bit.Code = 0;
    if (p->Direction == 0) {
        if (ch1)
            p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 1;
        if (ch2)
            p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 2;
        if (ch3)
            p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 4;
    } else {
        if (ch1)
            p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 4;
        if (ch2)
            p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 2;
        if (ch3)
            p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 1;
    }
#if defined(DEBUG_ON_TABLE)
    if (Simulator.teta<_IQ(360.0/360))
        p->DPReCAP_CODE.bit.Code = 2;
    if (Simulator.teta<_IQ(300.0/360))
        p->DPReCAP_CODE.bit.Code = 6;
    if (Simulator.teta<_IQ(240.0/360))
        p->DPReCAP_CODE.bit.Code = 4;
    if (Simulator.teta<_IQ(180.0/360))
        p->DPReCAP_CODE.bit.Code = 5;
    if (Simulator.teta<_IQ(120.0/360))
        p->DPReCAP_CODE.bit.Code = 1;
    if (Simulator.teta<_IQ(60.0/360))
        p->DPReCAP_CODE.bit.Code = 3;
#endif


    if (p->DPReCAP_CODE.bit.Code==0){ //ошибка - запрещенное состоЯние
        switch (p->NumOfBadChannel){//надо кое-как пофиксить пропавший канал
            case 1://запрещенное состояние пусть будет первым каналом
                p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 1;
                break;
            case 2://и так далее
                p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 2;
                break;
            case 3:
                p->DPReCAP_CODE.bit.Code = p->DPReCAP_CODE.bit.Code + 4;
                break;
            default ://ничего не надо делать
                break;
        }
    }


    switch (p->DPReCAP_CODE.bit.Code) {
    case 3: // 0
        p->Angle6 = 0;
        break;
    case 1: // 60
        p->Angle6 = _IQ(60.0/360);
        break;
    case 5: // 120
        p->Angle6 = _IQ(120.0/360);
        break;
    case 4: //180
        p->Angle6 = _IQ(180.0/360);
        break;
    case 6: // 240
        p->Angle6 = _IQ(240.0/360);
        break;
    case 2: // 300
        p->Angle6 = _IQ(300.0/360);
        break;
    }

    if (p->DPReCAP_CODE.bit.Code == 0){ //ошибка - запрещенное состоЯние
        p->WrongCodeCounterPerSec++;
        p->WrongCodeCounter++;
    }
}

void DPReCAP_AngleErrorCalc(TDPReCAP* p) {
    long AngleDiff=0;
    AngleDiff=(labs(((p->Angle6-p->AnglePrev+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5)))&0x00FFFFFF;
    p->AnglePrev=p->Angle6;

    if (AngleDiff>_IQ(61.0/360)){//если угол с прошлого раза изменился больше, чем на 60 градусов, то датчик косячит
        if (p->NumOfBadChannel==0){//не включена маскировка неработающего канала
            p->WrongCodeCounter++;
            p->WrongCodeCounterPerSec++;
        }
    }
}


/******************************************************************************
 Процедура расчёта интерполированного угла.
 ******************************************************************************/

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_AngleCalc,"secureRamFuncs");
#endif

void DPReCAP_AngleCalc(TDPReCAP* p) {
    Uint32 delta, Timer;
    Uint32 PrevTs, Ts;
    _iq Angle;
    _iq Angle6;

    // Захватываем значение таймера на момент начала расчёта
    Timer = CpuTimer2Regs.TIM.all;

    // ЗапрещЯем прерываниЯ по захвату.
    EvaRegs.EVAIMRC.bit.CAP1INT = 0;
    EvaRegs.EVAIMRC.bit.CAP2INT = 0;
    EvaRegs.EVAIMRC.bit.CAP3INT = 0;

    // Фиксируем значениЯ переменных на момент начала расчёта
    Angle6 = p->Angle6;
    PrevTs = p->PrevTs;
    Ts = p->Ts;

    // Разрешаем прерываниЯ назад.
    EvaRegs.EVAIMRC.bit.CAP1INT = 1;
    EvaRegs.EVAIMRC.bit.CAP2INT = 1;
    EvaRegs.EVAIMRC.bit.CAP3INT = 1;

    // Если скорость равна нулю или выбран соответствующий режим, то угол не интеполируем.
    if ((p->DPReCAP_FLG1.bit.AngleMode == 0) || (p->DPReCAP_FLG1.bit.SpeedMinFLG == 0) || (Ts == 0)) {
        Angle = _IQ(1.0/12);
    } else {
        delta = PrevTs - Timer; // Сколько натикал таймер с момента прошлого обновлениЯ периода.
        Angle = _IQdiv(delta, Ts); // Интеполируем угол. Отношение прошлого переода к текущим "тикам".
        if (Angle >= _IQ(1.0/6.0)) // Ограничиваем угол в пределах 1/6.
            Angle = _IQ(1.0/6.0);
    }
    if (p->DPReCAP_FLG1.bit.Dir == 1)
        Angle = _IQ(1.0/6.0) - Angle;

    if (p->Direction) //пользовательскаЯ инверсиЯ направлениЯ
        Angle = -Angle + _IQ(1.0/6);

    p->Angle = Angle6 + Angle + p->AngleOffset;

    p->Angle &= 0x00FFFFFF;

}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_SpeedCalc,"secureRamFuncs");
#endif

/******************************************************************************
 Процедура расчёта скорости
 ******************************************************************************/
void DPReCAP_SpeedCalc(TDPReCAP* p) {

    _iq speed;
    DPReCAP.milsec++;

    // Считаем скорость в относительных единицах относительно номинальной.
    if ((p->Tspeed != 0) && (DPReCAP.DPReCAP_FLG1.bit.ZeroFLG == 0)) {

        // Знак скорости опрделЯетсЯ в зависимости от направлениЯ.
        if (p->DPReCAP_FLG1.bit.Dir == 0)
            speed = _IQdiv(p->TsNom, p->Tspeed);
        else
            speed = -_IQdiv(p->TsNom, p->Tspeed);
        if (p->Direction) { //задаетсЯ пользователем
            speed = -speed;
        }
    } else {
        speed = 0;
    }

    if (p->DPReCAP_FLG1.bit.SpeedMode == 1)
        p->speed = speed;
    else
        p->speed = _IQmpy(speed, _IQ(6));

    if (DPReCAP.milsecREF != DPReCAP.milsecPrevREF) {
        DPReCAP.milsecFIX = DPReCAP.milsecREF * 10; //к 10кГц
        DPReCAP.speedMinREF = _IQdiv(p->TsNomMilsec, DPReCAP.milsecFIX);
        DPReCAP.milsecPrevREF = DPReCAP.milsecREF;
    }

    DINT;//нужно для потокобезопасного обращения к переменной DPReCAP_FLG1 (чтобы не перетереть присваивание в прерывании захвата)
    // Обнуление скорости, если привысили заданное времЯ между двумЯ соседними событиЯми.
    if (DPReCAP.milsec > DPReCAP.milsecFIX)
    {
        DPReCAP.speed = 0;
        DPReCAP.Tspeed = 0;
        DPReCAP.PrevTspeed = 0;
        DPReCAP.DPReCAP_FLG1.bit.ZeroFLG = 1;

        DPReCAP.cnt = 0;

        DPReCAP.PrevTspeed1 = 0;
        DPReCAP.PrevTspeed11 = 0;

        DPReCAP.PrevTspeed2 = 0;
        DPReCAP.PrevTspeed22 = 0;

        DPReCAP.PrevTspeed3 = 0;
        DPReCAP.PrevTspeed33 = 0;
    }

    EINT;

    DINT;//нужно для потокобезопасного обращения к переменной DPReCAP_FLG1 (чтобы не перетереть присваивание в прерывании захвата)
    // При скорости меньше заданной, отключаем интерполЯцию угла.
    if ((_IQabs(p->speed)) <= (p->speedMIN))
        p->DPReCAP_FLG1.bit.SpeedMinFLG = 0;
    else
        p->DPReCAP_FLG1.bit.SpeedMinFLG = 1;
    EINT;
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_CAP1Calc,"secureRamFuncs");
#endif
void DPReCAP_CAP1Calc(TDPReCAP* p) {
#if (!defined(DEBUG_ON_TABLE))
    if (DPReCAP.cnt >= 2) {
        DPReCAP.HelpCalc(&DPReCAP);

        // В зависимости от номера предудыщего CAP определЯем направление вращениЯ.
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 3)
            DPReCAP.DPReCAP_FLG1.bit.Dir = 0;
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 2)
            DPReCAP.DPReCAP_FLG1.bit.Dir = 1;
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 1) {
            if (DPReCAP.DPReCAP_FLG1.bit.PrevDir == 0)
                DPReCAP.DPReCAP_FLG1.bit.Dir = 1;
            else
                DPReCAP.DPReCAP_FLG1.bit.Dir = 0;
        }

        if (DPReCAP.DPReCAP_FLG1.bit.Dir != DPReCAP.DPReCAP_FLG1.bit.PrevDir) {
            DPReCAP.DPReCAP_FLG1.bit.PrevDir = DPReCAP.DPReCAP_FLG1.bit.Dir;
            DPReCAP.cnt2 = 1;
        }

        // считаем времЯ между двумЯ метками длЯ расчёта угла и скорости.
        if (DPReCAP.PrevTspeed1 == 0)
        {
            if (DPReCAP.cnt2 == 1)
                DPReCAP.Tspeed = 0;
            else
            {
                if (p->DPReCAP_FLG1.bit.SpeedMode == 1)
                    DPReCAP.Tspeed = (DPReCAP.PrevTspeed - p->Timer1);
                else
                    DPReCAP.Tspeed = (DPReCAP.PrevTspeed - p->Timer1)*6;
            }
        } else {
            if (DPReCAP.cnt2 <= 3) {
                DPReCAP.Tspeed = 0;
                DPReCAP.speed = 0;
            } else if (DPReCAP.cnt2 <= 6)
                DPReCAP.Tspeed = (DPReCAP.PrevTspeed11 - p->Timer1) * 2;
            else
                DPReCAP.Tspeed = DPReCAP.PrevTspeed1 - p->Timer1;
        }

        DPReCAP.Ts = (DPReCAP.PrevTs - p->Timer1) * 6;

        DPReCAP.cnt = 2;
        if (DPReCAP.cnt2 > 6)
            DPReCAP.cnt2 = 7;
    } else {
        DPReCAP.Ts = 0;
        DPReCAP.Tspeed = 0;
    }

    DPReCAP.PrevTs = p->Timer1;
    DPReCAP.PrevTspeed = p->Timer1;
    DPReCAP.PrevTspeed11 = p->Timer1;

    if (DPR_CHANNEL1_DATA == 1) {
        p->TimeRising1 = p->Timer1;
        DPReCAP.PrevTspeed1 = p->TimeFalling1;
    } else {
        p->TimeFalling1 = p->Timer1;
        DPReCAP.PrevTspeed1 = p->TimeRising1;
    }

    DPReCAP.cnt++;
    DPReCAP.cnt2++;
    DPReCAP.milsec = 0;
    DPReCAP.DPReCAP_FLG1.bit.CAPnumber = 1;
#endif
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_CAP2Calc,"secureRamFuncs");
#endif

void DPReCAP_CAP2Calc(TDPReCAP* p) {
    int ch2;
#if (!defined(DEBUG_ON_TABLE))
    if (DPReCAP.cnt >= 2) {
        DPReCAP.HelpCalc(&DPReCAP);

        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 1)
            DPReCAP.DPReCAP_FLG1.bit.Dir = 0;
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 3)
            DPReCAP.DPReCAP_FLG1.bit.Dir = 1;
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 2) {
            if (DPReCAP.DPReCAP_FLG1.bit.PrevDir == 0)
                DPReCAP.DPReCAP_FLG1.bit.Dir = 1;
            else
                DPReCAP.DPReCAP_FLG1.bit.Dir = 0;
        }

        if (DPReCAP.DPReCAP_FLG1.bit.Dir != DPReCAP.DPReCAP_FLG1.bit.PrevDir) {
            DPReCAP.DPReCAP_FLG1.bit.PrevDir = DPReCAP.DPReCAP_FLG1.bit.Dir;
            DPReCAP.cnt2 = 1;
        }

        // считаем времЯ между двумЯ метками длЯ расчёта угла и скорости.
        if (DPReCAP.PrevTspeed2 == 0)
        {
            if (DPReCAP.cnt2 == 1)
                DPReCAP.Tspeed = 0;
            else
            {
                if (p->DPReCAP_FLG1.bit.SpeedMode == 1)
                    DPReCAP.Tspeed = (DPReCAP.PrevTspeed - p->Timer2);
                else
                    DPReCAP.Tspeed = (DPReCAP.PrevTspeed - p->Timer2)*6;
            }
        } else {
            if (DPReCAP.cnt2 <= 3) {
                DPReCAP.Tspeed = 0;
                DPReCAP.speed = 0;
            } else if (DPReCAP.cnt2 <= 6)
                DPReCAP.Tspeed = (DPReCAP.PrevTspeed22 - p->Timer2) * 2;
            else
                DPReCAP.Tspeed = DPReCAP.PrevTspeed2 - p->Timer2;
        }

        DPReCAP.Ts = (DPReCAP.PrevTs - p->Timer2) * 6;

        DPReCAP.cnt = 2;
        if (DPReCAP.cnt2 > 6)
            DPReCAP.cnt2 = 7;
    } else {
        DPReCAP.Ts = 0;
        DPReCAP.Tspeed = 0;
    }

    DPReCAP.PrevTs = p->Timer2;
    DPReCAP.PrevTspeed = p->Timer2;
    DPReCAP.PrevTspeed22 = p->Timer2;
    ch2=DPR_CHANNEL2_DATA;
    if (p->Channel2Inversion)
        ch2=!ch2;

    if (ch2) {
        p->TimeRising2 = p->Timer2;
        DPReCAP.PrevTspeed2 = p->TimeFalling2;
    } else {
        p->TimeFalling2 = p->Timer2;
        DPReCAP.PrevTspeed2 = p->TimeRising2;
    }

    DPReCAP.cnt++;
    DPReCAP.cnt2++;
    DPReCAP.milsec = 0;
    DPReCAP.DPReCAP_FLG1.bit.CAPnumber = 2;
#endif
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_CAP3Calc,"secureRamFuncs");
#endif

void DPReCAP_CAP3Calc(TDPReCAP* p) {
#if (!defined(DEBUG_ON_TABLE))
    if (DPReCAP.cnt >= 2) {
        DPReCAP.HelpCalc(&DPReCAP);

        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 2)
            DPReCAP.DPReCAP_FLG1.bit.Dir = 0;
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 1)
            DPReCAP.DPReCAP_FLG1.bit.Dir = 1;
        if (DPReCAP.DPReCAP_FLG1.bit.CAPnumber == 3) {
            if (DPReCAP.DPReCAP_FLG1.bit.PrevDir == 0)
                DPReCAP.DPReCAP_FLG1.bit.Dir = 1;
            else
                DPReCAP.DPReCAP_FLG1.bit.Dir = 0;
        }

        if (DPReCAP.DPReCAP_FLG1.bit.Dir != DPReCAP.DPReCAP_FLG1.bit.PrevDir) {
            DPReCAP.DPReCAP_FLG1.bit.PrevDir = DPReCAP.DPReCAP_FLG1.bit.Dir;
            DPReCAP.cnt2 = 1;
        }

        // считаем времЯ между двумЯ метками длЯ расчёта угла и скорости.
        if (DPReCAP.PrevTspeed3 == 0)
        {
            if (DPReCAP.cnt2 == 1)
                DPReCAP.Tspeed = 0;
            else
            {
                if (p->DPReCAP_FLG1.bit.SpeedMode == 1)
                    DPReCAP.Tspeed = (DPReCAP.PrevTspeed - p->Timer3);
                else
                    DPReCAP.Tspeed = (DPReCAP.PrevTspeed - p->Timer3)*6;
            }
        } else {
            if (DPReCAP.cnt2 <= 3) {
                DPReCAP.Tspeed = 0;
                DPReCAP.speed = 0;
            } else if (DPReCAP.cnt2 <= 6)
                DPReCAP.Tspeed = (DPReCAP.PrevTspeed33 - p->Timer3) * 2;
            else
                DPReCAP.Tspeed = DPReCAP.PrevTspeed3 - p->Timer3;
        }

        DPReCAP.Ts = (DPReCAP.PrevTs - p->Timer3) * 6;

        DPReCAP.cnt = 2;
        if (DPReCAP.cnt2 > 6)
            DPReCAP.cnt2 = 7;
    } else {
        DPReCAP.Ts = 0;
        DPReCAP.Tspeed = 0;
    }

    DPReCAP.PrevTs = p->Timer3;
    DPReCAP.PrevTspeed = p->Timer3;
    DPReCAP.PrevTspeed33 = p->Timer3;

    if (DPR_CHANNEL3_DATA == 1) {
        p->TimeRising3 = p->Timer3;
        DPReCAP.PrevTspeed3 = p->TimeFalling3;
    } else {
        p->TimeFalling3 = p->Timer3;
        DPReCAP.PrevTspeed3 = p->TimeRising3;
    }

    DPReCAP.cnt++;
    DPReCAP.cnt2++;
    DPReCAP.milsec = 0;
    DPReCAP.DPReCAP_FLG1.bit.CAPnumber = 3;
#endif
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(DPReCAP_HelpCalc,"secureRamFuncs");
#endif

void DPReCAP_HelpCalc(TDPReCAP* p) {
    // ОбнулЯем скорость и выставлЯем флаг,
    // если времЯ между двумЯ событиЯми больше заданного.
    if (DPReCAP.milsec > DPReCAP.milsecFIX) {
        DPReCAP.speed = 0;
        DPReCAP.DPReCAP_FLG1.bit.ZeroFLG = 1;
    } else {
        DPReCAP.DPReCAP_FLG1.bit.ZeroFLG = 0;
    }
}

void DPReCAP_SlowCalc(TDPReCAP* p) {
//формула длЯ расчета T=Ts/Tfiltra где - Tfiltra постоЯннаЯ времени фильтра
//  p->AngleFilter_1_T=_IQdiv(FAST_CALC_TS,AngleFilterT);
}

void DPReCAP_msCalc(TDPReCAP* p) {
    p->ErrorLevelTimeCounterBig++;
    if (p->ErrorLevelTimeCounterBig > 10000) {
        p->ErrorLevel = p->ErrorLevelCounter;
        p->ErrorLevelCounter = 0;
        p->ErrorLevelTimeCounterBig = 0;
    }

    p->ErrorLevelTimeCounter++;
    if (p->ErrorLevelTimeCounter > 1000) {
        if ((p->WrongCodeCounterPerSec > p->WrongCodeCounterLimitPerSec) ||
            (p->ErrorExternalSpeedEstimatorCounter > p->ErrorExternalSpeedEstimatorCounterLimitPerSec) ||
            (p->WrongPowerCounter>3000)){
            p->SensorFault = 1;
        } else
            p->SensorFault = 0;
        p->WrongCodeCounterPerSec=0;
        p->ErrorExternalSpeedEstimatorCounter=0;
        p->ErrorLevelTimeCounter = 0;
    }

    if (p->CAP_WrongEdgeCntPrev != p->CAP_WrongEdgeCnt)
        p->ErrorLevelCounter++;
    p->CAP_WrongEdgeCntPrev = p->CAP_WrongEdgeCnt;

}

/*@}*/

