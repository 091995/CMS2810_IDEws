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

#include "main.h"


void POSSPEEDEQEP_init(TEncoder *p) {
    //���� ��������� CAP
    EvaRegs.CAPCON.all = QEP_CAP_INIT_STATE;
    //���� ������� ��� �������� ��������� ��������
    EvaRegs.T2CON.all = QEP_TIMER_INIT_STATE;
    //������ ������� � 4 ���� ������ ���������� �������, �� ��������� �������� � ������ ������ 2 �������
    //-1 �����, ����� ������ ������ �� 0 �� 9999
    EvaRegs.T2PR = p->resolution * 4 - 1;

    //���. ����� ��������� �����
    EvaRegs.EXTCON.bit.QEPIE = 1;
    //������������ ��������� �����: ��������� �� ������ �����, ����� �� ������� A � B �������
    EvaRegs.EXTCON.bit.QEPIQEL = 1;

    EALLOW;
    //����� �8/�9/�10 ��� QEP
    GpioMuxRegs.GPAMUX.all |= 0x0700;
    //������ GPIO - ������ ������� = QUALPRD x SYSCLK
    GpioMuxRegs.GPAQUAL.BIT.QUALPRD = 5;
    EDIS;
    //1/����������
    //����: ������� �� ���������� � ������� _IQ16.
    //��� ���������� ������� 2500 �����, �������� �������� �����: 1/2500*2^16 = 26.2144,
    //������� ����� 0.2144 �������������, ��-�� ���� ������ �������� ��������, � � ������, ����� �������� ����� 9999,
    //������������ ���� ����� 0.991, � ������������� � ������� 0.967.
    //��-�� ����� ���������� ������ � ��������, ��� ����������� ����� ����� 0 ��� ����� ������.
    ///p->_1_resol = _IQ16div(_IQ16(1.0), (p->resolution << 16));

    //��� ����� ������� ����������, �� � ����� ��������� ������� IQ ������ �������� �� ������.
    //������� ������ ������� �� ��-�������� � IQ24:
    p->_1_resol = _IQ(1.0/p->resolution);
    //������� ��������
    p->RevolutionCounter = 0;
}

//������� ������� ��������
#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(POSSPEEDEQEP_Calc,"secureRamFuncs");
#endif
void POSSPEEDEQEP_FastCalc(TEncoder *p) {
    //��������� �����
    p->GPIOsValue = (Uint16) GpioDataRegs.GPADAT.bit.GPIOA8 +
                    ((Uint16) GpioDataRegs.GPADAT.bit.GPIOA9 << 1) +
                    ((Uint16) GpioDataRegs.GPADAT.bit.GPIOA10 << 2);

    //������ ��������� �����: ������� ���-�� �����
    p->posCnt = EvaRegs.T2CNT;

    //����������� �������� ����������� �� ���� (����������� ���������� � ���) � ��������
    //����� �� 3 ����� ��������� ������� �� ���������� 127,
    //����� ��� ������������� ����� ��������� ����� �� 3
    p->KThetaToSpeed=_IQdiv(_IQ(1.0),_IQmpyI32(drv_params.freq_nom,FAST_CALC_TS)<<3);

    //����: ������ ������������� ���� � �.�. (IQ24(1.0) == 2pi)
    //����� ������� ���-�� ����� �� ���������� ���� � ������� IQ16:
    //��� ����� ������� ���-�� ����� �������� �� 16, �������� �� ��������, �������� ����������.
    //�������� ���� ������ ���� � ������� IQ24, ��, ��������� ���-�� ����� � 4 ���� ������ ����������,
    //�������� �������� ��������� �� 6, � �� �� 8 (4 == << 2)
    ///p->thetaMech = _IQ16mpy(((int32) p->posCnt) << 16, p->_1_resol) << 6;

    //�����: ��������� "_1_resol" � ��� � ����� IQ24 ���� ���������� ��������,
    //����� ������������ "_IQ16mpy(((int32) p->posCnt) << 16, p->_1_resol)" ��������� ����� ������ ����������� � 24 - 16 = 8 ���.
    //� ���� ������ ��� ���������� � ������� IQ24 ����������� �������� ��������� ����� �� 6 (��. ����),
    //�� ������ �� ��� �������� �� 8 - 6 = 2 ������. ����� ��������!
    p->thetaMech = _IQ16mpy(((int32) p->posCnt) << 16, p->_1_resol) >> 2;
    p->thetaMech &= 0x00FFFFFF;

    //������ �������������� ����: ������ ������������� � ����� ��� ������� + ��������
    p->theta_elec = _IQmpy(p->thetaMech, _IQ(p->pole_pairs)) + p->AngleOffset;
    p->theta_elec = p->theta_elec & 0x00FFFFFF;

    //������ �������������� ����
    if (p->thetaElFilterK != 0) {
        p->thetaElFiltered = p->thetaElFiltered + _IQmpy(p->thetaElFilterK,
                                 ((p->theta_elec - p->thetaElFiltered + _IQ(0.5)) & 0x00FFFFFF) - _IQ(0.5));
        p->thetaElFiltered &= 0x00FFFFFF;
    } else p->thetaElFiltered = p->theta_elec;

    p->dThetaEl = p->theta_elec - p->thetaElPrev;
    //���� ���������� ����� �������������
    if (p->dThetaEl > 0) {
        //���� ���� ����� � ���������� ����� ����
        if (p->dThetaEl > _IQ(0.5))
            p->dThetaEl = p->theta_elec - (_IQ(1.0) + p->thetaElPrev);
    } else {
        //���� ���� ������ � ���������� ������
        if (labs(p->dThetaEl) > _IQ(0.5))
            p->dThetaEl = _IQ(1.0) - p->thetaElPrev + p->theta_elec;
    }

    //������� ���������� ����. ������ <<8 � >>8 ������������ ���������� ���� �������� ����� 0 ��������
    ///p->dThetaEl = ((p->thetaEl << 8) - (p->thetaElPrev << 8)) >> 8;

    //������ ��������
    p->speed_elec = _IQmpy(p->dThetaEl, p->KThetaToSpeed) << 3;

    //������� ���������� ������ ��������
    if (p->thetaMech - p->thetaMechPrev > _IQ(0.5))
        p->RevolutionCounter++;
    if (p->thetaMech - p->thetaMechPrev < _IQ(-0.5))
        p->RevolutionCounter--;

    //������� ���������� ����. ������ <<8 � >>8 ������������ ���������� ���� �������� ����� 0 ��������
    p->thetaMechDelta = ((p->thetaMech << 8) - (p->thetaMechPrev << 8)) >> 8;

    //���� ������� ����� ������� ����������� ���� � ���������� ������ 5 ��������
    if (labs(p->thetaMechDelta - p->thetaMechDeltaPrev) > _IQ(5.0/360)) {
        //���������� ��������� ������, ����� �� ������ ������ ��� ������ �������
        if (sm_prot.poweredOk > 10)
            sm_prot.bit_fault1 |= F_ENCODER_FAULT;
    }

    //��������� �������� ����� ��� ��������� ��������
    p->thetaMechPrev = p->thetaMech;
    p->thetaElPrev = p->theta_elec;
    p->thetaMechDeltaPrev = p->thetaMechDelta;

    //����������� ������ ��� ��������
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

    //���������/���������� ��������� �����
    if (p->indexEnable == 0)
        EvaRegs.EXTCON.bit.QEPIE = 0;
    else
        EvaRegs.EXTCON.bit.QEPIE = 1;

}

