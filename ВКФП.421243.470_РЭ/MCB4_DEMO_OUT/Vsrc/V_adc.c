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
 
 \file      V_adc.c
 \brief     ������ ��������� ��� (��. TAdcDrv)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_adc 
 @{*/

#include "DSP.h"
#include "V_adc.h"
#include "main.h"
#include "string.h" //��� memset

//!�������������.

#define CPU_CLOCK_SPEED      6.6667L   // for a 150MHz CPU clock speed
#define ADC_DELAY 5000.0L
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_CLOCK_SPEED) - 9.0L) / 5.0L)

extern TAdcDrv adc;
extern TDrvParams drv_params;

//! \memberof TAdcDrv
void AdcDrv_init(TAdcCalibration *p) {

    int i;

    //----------------------------------------------------------------------
    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap and reference circuitry.
    // After a 5ms delay the rest of the ADC can be powered up. After ADC
    // powerup, another 20us delay is required before performing the first
    // ADC conversion.
    //
    // V1.1: Fixed bug. Was disabling clock but disabling was not working
    //       because EALLOW and EDIS did not ave a space and hence were
    //       treated as labels. ADC clock was enabled in a previous function
    //       so thats why V1.0 program worked anyway.
    //���� ������ ���������� ������ D �� ������� ������ �������
    //if (sm_sys.SiliconRevision>3)
#warning ��������� ��������� ������� �������
    AdcRegs.ADCTRL3.all=0x0100;
    //AdcRegs.ADCTRL3.all=0x0000;
    DELAY_US(ADC_DELAY);

    asm(" EALLOW");
    SysCtrlRegs.PCLKCR.bit.ADCENCLK = 1;      // Power up clocks to ADC
    asm(" EDIS");

    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;    // Power up bandgap/reference circuitry
    DELAY_US(ADC_DELAY);
    // Delay before powering up rest of ADC
    AdcRegs.ADCTRL3.bit.ADCPWDN = 1;        // Power up rest of ADC
    DELAY_US(ADC_DELAY);
    // Delay after powering up ADC
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;           // ADCCLK=25Mhz
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0;             // Acq Time=3ADC CLK

#if ADC_SAMPLING_MODE == SIMULTANEOUS
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;
    AdcRegs.ADCMAXCONV.all = 7;
#endif

#if ADC_SAMPLING_MODE == SEQUENTIAL
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;
    AdcRegs.ADCMAXCONV.all = 15;
#endif

    AdcRegs.ADCCHSELSEQ1.all = 0x3210;
    AdcRegs.ADCCHSELSEQ2.all = 0x7654;
    AdcRegs.ADCCHSELSEQ3.all = 0xba98;
    AdcRegs.ADCCHSELSEQ4.all = 0xfedc;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0x1;
    //----------------------------------------------------------------------
    // ADC is configured to start a conversion from the SOC signal
    // generated by EV-A:
    //
    AdcRegs.ADCTRL2.bit.EVA_SOC_SEQ1 = 1;  // Enable EVASOC to start SEQ1
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)

    p->init(p); //�������������� ����������� ���

    //----------------------------------------------------------------------
    // Start ADC:
    //
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;

    //----------------------------------------------------------------------
    // Wait for ADC to finish conversions (test INT1 flag):
    //
    while (AdcRegs.ADCST.bit.INT_SEQ1 == 0) {
    }
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    for (i = 0; i < 100; i++)   //TODO: ���������, ����� �� ��� �������� ���. ������ ; ������ ������ ���� 100 ��� ������������ �������� �������� ������ ������������ ���.
        ;

}


//!������ ��� � �������� ��������� ������� ���� ������� ���������� (������ 10���).

//! ���������� ���������� ���������� ��� �������� � ����������� � ������ IQ24.
//! ���� ��� ��� ��������� �������� ����������� �� ��������� ���������
//!
//! ����� �� 4 ����� ��� ������ �� ��� �������� ��� ���������� 12�� ���������� ���������� ��� � 16�� ���������� ����, �����
//! ������������ ����� ������������ ��� ��������, � �������� ^ 0x8000, ���� ����������� � ��������,
//! �������� ����� �� �������� ��������� � ������ ��� ��������. �.�. � ���������� ���� ���� �������� �������� ��� �� 0 �� 4096
//! ������������� � �������� �� -32768 �� +32767, � �������� ��������� ��� (2048, ���� ��������� �������� ����)
//! ������������ 0 � ��������������� �������. ����� ������� ��� ������ ��� ��������� ����������. ��� ����� �������� ��
//! ��������� �� ���������� ��� 2048 � ��������� �� �������������� ����� ��� ��������� ������������ ����������.

//! \memberof TAdcDrv

#if defined(HW_MOTORCONTROLBOARD)
void AdcDrv_fast_calc(TAdcDrv *p) {

    p->IA_temp = AdcRegs.ADCRESULT0;
    p->IC_temp = AdcRegs.ADCRESULT1;
	p->Udc_temp = AdcRegs.ADCRESULT2;

	p->ref_temp = AdcRegs.ADCRESULT3;

	p->T_temp = AdcRegs.ADCRESULT9;


	p->Imeas_a = p->IaGainNom * ((p->IA_temp + p->Imeas_a_offset));
	p->Imeas_c = p->IcGainNom * ((p->IC_temp + p->Imeas_c_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);

	p->Imeas_b = -p->Imeas_a - p->Imeas_c;
	p->T_meas = p->TGainNom * (p->T_temp);		//������ ����������� ��� ��������
	p->ref_meas = p->refGainNom * ((p->ref_temp + p->ref_meas_offset));

}
#endif


//!��������� ������.

//!���������� ���������� �������������, ������������ � ���������� ������� �������,
//!����� �� �������� ������������ ����� ���. ������� ������������,
//!�� ������� ���� �������� ���������� � ��� ��������, ����� ��������
//!������������� ������� � �������� �����.

//! ������   p->PvalveGainNom=_IQ16mpy(p->Pvalve_gain,_IQ(1.0/100));
//! Pvalve_gain - �������� � ������� int. �������� ������������� � UniCON.
//!����������, �������� ��������� ������������� ������ �������� ���. � ���������� ������
//!����� 100. �.�. ����� �� ��� ������������ ������, ��� ������������� 100%.

//!_IQ(1.0/100) �������� �������� ��� ��������������� ������������. ��� ��� �������� ���������
//!������������ ����� ��������� � ������������� ������� ���, ��� 100% ������������ 1.0,
//!�� �������������� ����������� (����) ����� 100. �.�. UniCON, �������� �� ������� ����������
//! ����� 1.0 � ������� 8.24 ������ �������� ��� �� 100, ����� ������������ ��������.
//! ����� ����������� ����� ���� ��� 1.0/100, �� ��� ���� ������� ������� �������� ����� ������.
//!���, ��� ����� ��� ������������ �������� _1_I_nom, � ������� 8.24, ��������������� ������� �������� ��
//������� �������� ����, ��������, 200 �. ��� ��� � ����������� �� �������� ��������������� ������� ��� ����� ��������,
//�� ��� ��������, � ������� �� ���������, ������� �������������. ������ _1_I_nom ���� � ������ �����, ��� ���
//�������� ����� ������ �������.

//��� ������������ �������� ��� �������� ����� �� 0 �� 4096.
//��� ������� � ���������� ���������� ������� ���, ����� ���������� �������������� �������� � ������� 8.24,
//��� 1.0 ��� 4096. ����� �������, ����� �������� ����� 4096 �� 4 �������.

//����� �������, PvalveGainNom - ��� ����������� � ������� 24.8. �� ���������� � ���������� ������������� �������
//_IQ16mpy, �������� ������� Pvalve_gain (int) � 1.0/100 � ������� 8.24. ������� IQ ��������
//�� ���� ������������ ����� ������� ��������� � 64 �������� �� ������� ���������� ������ �� Q ��������.
//�.�. _IQ16mpy �������� ����� � ������� IQ24 9������ ��������) �� ������������� ����������� (������ ��������),
//� ����� �������� ��������� �� 16 �������� ������.
//���, � ���������� _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); ���������� ������������� ����� 255, ����������
//1.0 � ������� 24.8 ��-�� ������ �� 16 �������� ������.

//�� ��������������� ������ ������� � ����� ����� - ��������� ����������������� ��������� ���.

//! \memberof TAdcDrv
void AdcDrv_slow_calc(TAdcDrv *p) {
	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain, drv_params._1_I_nom) << 1;
	p->IbGainNom = _IQ16mpy(p->Imeas_b_gain, drv_params._1_I_nom) << 1;
	p->IcGainNom = _IQ16mpy(p->Imeas_c_gain, drv_params._1_I_nom) << 1;
	p->IdGainNom = _IQ16mpy(p->Imeas_d_gain, drv_params._1_I_nom) << 1;
	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain, drv_params._1_Udc_nom) << 4;
	p->TGainNom = _IQ16mpy(p->T_meas_gain, _IQ(0.05)) << 4;	//0.05 = 1/20, ��� 20 �������� �� ������� - ����������� (�������) �����������
	p->refGainNom = _IQ16mpy(p->ref_meas_gain, _IQ(1.0/100)) << 4;
}

//! �������������� ������

//! \memberof TAdcDrv
void AdcDrv_ms_calc(TAdcDrv *p) {

}

/*@}*/

