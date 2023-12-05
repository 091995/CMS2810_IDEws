/*!
     Copyright 2023 ��� "��� ������"

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
 \brief     ������ ���������� ������������� �������� QEP
 \author    ��� "��� ������". http://motorcontrol.ru
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
// 0:1       INPUT: ����� ������������� ��������� ��� �����:
//                  0 - �� ������������ �������
//                  1 - ���������� ������ ����, ����� ���� � ��������� ������(�������� ��������� - 0 ������������� ��������);
//                  2 - ���� � ��������� ������(�������� ��������� - ��������� ����������)
// 2         INPUT: ������� ������
//                  0 - ����� �����������
//                  1 - ����� ���������;
// 3         INPUT: ����������� ��������(� ������ ������������� �����������);
//                  0 - (�� ���������)������ ���������;
//                  1 - ��������;
// 4         INPUT: ��� ������ �������������
// 5:8       INPUT: ����������� ����� ����� ��� ������� �� ������ �������� - �� ������!!!!!
//                  Min_clk=2 - 4 �����
//                          3 - 8 ����� - �� ���������
//                          4 - 16 �����
//                          5 - 32 �����
//                          6 - 64 �����
//                          7 - 128 �����
//                          8 - 256 �����
//                          9 - 512 �����
//                          10 - 1024 �����
// 9         INPUT: ������� ������ (shadow) ��� ���������
//                  0 - ����� �����������
//                  1 - ����� ���������;

#define QEP_CAP_INIT_STATE    0x9004
#define QEP_TIMER_INIT_STATE (FREE_RUN_FLAG +      \
                          TIMER_DIR_UPDN +         \
                          TIMER_CLK_PRESCALE_X_1 + \
                          TIMER_ENABLE_BY_OWN +    \
                          TIMER_ENABLE +           \
                          TIMER_CLOCK_SRC_QEP +    \
                          TIMER_COMPARE_LD_ON_ZERO)

struct SEncoder {
    Uint32  resolution;         //���������� �������
    _iq     _1_resol;           //��������, �������� ���������� �������
    int32   RevolutionCounter;  //���-�� ���������� ��������
    Uint16  GPIOsValue;         //��� ����������� ����� ���� � �������
    Uint16  direction;          //����������� ��������
    Uint16  indexEnable;
    int32   posCnt;             //���-�� ��������� �����
    int32   posCntPrev;         //���������� ���-�� �����
    _iq     thetaMech;          //������������ ����
    _iq     thetaMechPrev;      //���������� �������� ������������� ����
    _iq     thetaElFiltered;    //������������ ���� �������������
    _iq     thetaElFilterK;     //����-� ����������
    _iq     theta_elec;            //������������� ����
    _iq     thetaElPrev;        //���������� �������� �������������� ����
    _iq     dThetaEl;           //���������� ��. �����
    _iq     AngleOffset;        //����� ����
    _iq     thetaMechDelta;     //���������� ������������� ���� ��� ������ �� ������ ���������� ����
    _iq     thetaMechDeltaPrev; //���������� ���������� ������������� ����
    _iq     speed_elec;         //������������� ��������
    _iq     speedMech;          //������������ ��������
    _iq     KThetaToSpeed;      //����������� ��� ������� �������� �� ����
    Uint16  pole_pairs;         //����� ��� �������;
    TFilter speedF;             //������ ��������

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
