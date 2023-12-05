/*!
     Copyright 2023 ќќќ "Ќѕ‘ ¬≈ “ќ–"

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
 \brief     ћодуль реализации квадратурного энкодера QEP
 \author    ќќќ "Ќѕ‘ ¬ектор". http://motorcontrol.ru
 @{*/

#include "IQmathLib.h"
#ifndef V_POSSPEED_EQEP_H
#define V_POSSPEED_EQEP_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
Initialization states for T2CON and CAPCON
------------------------------------------------------------------------------*/
// 0:1       INPUT: режим инициализации положения при пуске:
//                  0 - всЄ выставляется вручную
//                  1 - выставляем вектор тока, далее пуск в векторном режиме(исходное положение - 0 электрических градусов);
//                  2 - пуск в векторном режиме(исходное положение - последнее сохранЄнное)
// 2         INPUT: наличие репера
//                  0 - репер отсутствует
//                  1 - репер подключЄн;
// 3         INPUT: направление движения(в случае неправильного направления);
//                  0 - (по умолчанию)прямое включение;
//                  1 - инверсия;
// 4         INPUT: для режима инициализации
// 5:8       INPUT: минимальное число меток для захвата на низкой скорости - Ќ≈ ћ≈Ќя“№!!!!!
//                  Min_clk=2 - 4 метки
//                          3 - 8 меток - по умолчанию
//                          4 - 16 меток
//                          5 - 32 метки
//                          6 - 64 метки
//                          7 - 128 меток
//                          8 - 256 меток
//                          9 - 512 меток
//                          10 - 1024 метки
// 9         INPUT: наличие репера (shadow) дл€ переинита
//                  0 - репер отсутствует
//                  1 - репер подключЄн;

#define QEP_CAP_INIT_STATE    0x9004
#define QEP_TIMER_INIT_STATE (FREE_RUN_FLAG +      \
                          TIMER_DIR_UPDN +         \
                          TIMER_CLK_PRESCALE_X_1 + \
                          TIMER_ENABLE_BY_OWN +    \
                          TIMER_ENABLE +           \
                          TIMER_CLOCK_SRC_QEP +    \
                          TIMER_COMPARE_LD_ON_ZERO)

struct SEncoder {
    Uint32  resolution;         //разрешение датчика
    _iq     _1_resol;           //величина, обратна€ разрешению датчика
    int32   RevolutionCounter;  //кол-во пройденных оборотов
    Uint16  GPIOsValue;         //дл€ отображени€ ножек ƒѕ–а в ёниконе
    Uint16  direction;          //направление вращени€
    Uint16  indexEnable;
    int32   posCnt;             //кол-во прошедших меток
    int32   posCntPrev;         //предыдущее кол-во меток
    _iq     thetaMech;          //механический угол
    _iq     thetaMechPrev;      //предыдущее значение механического угла
    _iq     thetaElFiltered;    //механический угол фильтрованный
    _iq     thetaElFilterK;     //коэф-т фильтрации
    _iq     theta_elec;            //электрический угол
    _iq     thetaElPrev;        //предыдущее значение электрического угла
    _iq     dThetaEl;           //приращение эл. угола
    _iq     AngleOffset;        //сдвиг угла
    _iq     thetaMechDelta;     //приращение механического угла дл€ защиты по скачку приращени€ угла
    _iq     thetaMechDeltaPrev; //предыдущее приращение механического угла
    _iq     speed_elec;         //электрическа€ скорость
    _iq     speedMech;          //механическа€ скорость
    _iq     KThetaToSpeed;      //коэффициент дл€ расчета скорости из угла
    Uint16  pole_pairs;         //число пар полюсов;
    TFilter speedF;             //фильтр скорости

    void (*init) (struct SEncoder*);
    void (*calc) (struct SEncoder*);
    void (*slow_calc) (struct SEncoder*);
};

typedef struct SEncoder TEncoder;

#define ENCODER_DEFAULTS {  .resolution = 2500,\
                            .speedF = FILTER_DEFAULTS,\
                            .init = POSSPEEDEQEP_init,\
                            .calc = POSSPEEDEQEP_FastCalc,\
                            .slow_calc = POSSPEEDEQEP_SlowCalc}

void POSSPEEDEQEP_init(TEncoder*);
void POSSPEEDEQEP_FastCalc(TEncoder*);
void POSSPEEDEQEP_SlowCalc(TEncoder*);

void Index_event(TEncoder*);
void POSSPEEDEQEP_angleCorrect (TEncoder *, _iq, _iq);
void POSSPEEDEQEP_resetPosition (TEncoder *);
#ifdef __cplusplus
}
#endif

#endif
