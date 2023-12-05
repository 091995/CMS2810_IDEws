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
 
 \file      V_PWM_Module.c
 \brief     ������ ���������� ��������� ��� (��. TPWM_Module)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_PWM_Module 
 @{*/


#include "IQmathLib.h"          // ���������� IQmath
#include "V_PWM_Module.h"
#include "main.h"

#if defined(HW_MOTORCONTROLBOARD)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

//! ����������� �������� "������� �������"
#if defined(HW_MOTORCONTROLBOARD)
//! ��� ������������ ��������� ������ ������ 3���, ����� �� �����
#define DEAD_BAND_MIN	_IQ(3)
#define DEAD_BAND_MAX	_IQ(10)
#else
#define DEAD_BAND_MIN	_IQ(0)
#define DEAD_BAND_MAX	_IQ(10)
#endif

//! �������������

//������������� ��� ������������� ���������� ����������� ��������
void PWM_6_12_Init_No_SV_Eva(TPWM_Module *p) {

    p->slow_calc(p);
    EvaRegs.T1PR=4000;//����� ���-�� ������
    p->k_pwm=4000;
    p->FreqPrev=0;//����� ������������� �������

    if (sm_sys.IntEna)
        DINT;
    EvaRegs.T1CNT = 3;
    if (sm_sys.IntEna)
        EINT;

    EvaRegs.T1CON.bit.TENABLE = 1; //����� �� �������� ��� (����� ��)

    EvaRegs.T1CON.all = PWM_INIT_STATE; /* Symmetrical Operation         */
    EvaRegs.DBTCONA.all = PWM_DBTCON_INIT_STATE;
    EvaRegs.ACTRA.all = PWM_ACTR_INIT_STATE;
    //�������� ���������, ����� ����������� ������� ���������, Space PWM enabler,
    //����� ����������� control �������, �������� ������ ���������, trip
    EvaRegs.COMCONA.all=0;//��� ����� ������ ��� ������. ���� "������" �����
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

    EvaRegs.GPTCONA.bit.T1TOADC = 1;// T1 ��������� ADC �� underflow
}

//! ������������ ������� �������.

//!��������� ����������� ���������� ��� ��������� Ud,
//!��������� ���������� ������� � ����������, ���� ���������, �
//!��������� ����� ������, ������������ �������� ���� ����������.
//! \memberof TPWM_Module
void PWM_Module_NormInput(TPWM_Module* p) {
    _iq knorm;

    p->UalphaNorm=p->UalphaRef;
    p->UbetaNorm=p->UbetaRef;

    //������� ��������� (��� ����� �����������)
    p->U_mag=_IQmag(p->UalphaNorm,p->UbetaNorm);


    p->UdCorTmp=_IQdiv(_IQ(1.0),(_IQ(1.0)+_IQmpy((adc.Udc_meas-_IQ(1.0)),p->UdCompK)));
    //���� ��������� ���������� �� Ud
    if (p->UdCompEnable&1) { //�� �������?
        p->UalphaNorm=_IQmpy(p->UalphaNorm, p->UdCorTmp);//������� ��������������� �����-�� ���������
        p->UbetaNorm=_IQmpy(p->UbetaNorm, p->UdCorTmp);//� ��� ����
    }

    //���������� �������� ��������� ���������� � ����������, ����������� � ������������� ������� ��������
    //����� U_lim=1.0, ��� � ���� ����� ����������. ������, ��� �� ����� ��������� � �������������. ����� ������ �������� ����� ������������ U_lim
    if (p->U_lim>_IQ(1.0/0.866)) //�� ��� ������ �������� ���� �����������-������. ���������� (������ �������� �������)
        p->U_lim=_IQ(1.0/0.866);
    /* ������������ ��������� �������, ������� ����� ����������*/
    knorm=_IQmag(p->UalphaNorm,p->UbetaNorm);//���� ��������� �� 540 � 311
    if (knorm>=p->U_lim) { //�� ������, ��� ���� �����������?
        knorm=_IQdiv(p->U_lim,knorm);//� ��� �� ����������, ��� ��������, ������������ ����������
        p->UalphaNorm=_IQmpy(knorm,p->UalphaNorm);//��������� ��������������� ����������
        p->UbetaNorm=_IQmpy(knorm,p->UbetaNorm);//� ���
        p->ULimitation=1;//���� � ���, ��� ���� ����������� ����������
    } else
        p->ULimitation=0;

    /* ������������ ����������� �������*/
    /* �� ����� ������� ���������� ������������� ������������
    ������ ������� ������������ ��������, ��������, 220*sqrt(2)
    ������ ������������ �������, ��� �� ������� ����������� �����������
    ����������� ���������� (����� �������� �������)
    */
    p->UalphaNorm=_IQmpy(p->UalphaNorm,_IQ(0.866));
    p->UbetaNorm=_IQmpy(p->UbetaNorm,_IQ(0.866));
}



//! ������� 6�� ��������� ��������� ���

//! \memberof TPWM_Module
void PWM_Module_No_SV_Update(TPWM_Module *p) {
    _iq lambda1;
    _iq lambda2;
    _iq lambda3;

    int16 gamma;
    int16 gamma1;
    long tmp_pwm;

    //���������� ���� ������� ��������� ������ ���� ������� ������� ����� �� ����, �����
    //������������� ��������� ���������� �����������, ��� � ��������� ��� ����� ���� �������� � ��������� ������ ���.
    DINT;
    if (abs(p->EvXRegs->T1CNT) > 30) {
        p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
        p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
        p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
        p->EvXRegs->T1PR = p->k_pwm;
    }
    EINT;

    PWM_Module_NormInput(p);

    //������ ����������� �� ������ ���������.
    //��������� ��. ����������� ����� �.�. http://motorcontrol.ru/wp-content/uploads/2015/11/Chuev_vector_control.pdf
    tmp_pwm = _IQmpy(_1_SQRT3,p->UbetaNorm);  /*����� �� ������ �� 3*/
    lambda1 = _IQmpy(p->k_pwm,(p->UalphaNorm - tmp_pwm));
    lambda2 = _IQmpy(p->k_pwm,2*tmp_pwm);
    lambda3 = _IQmpy(p->k_pwm,p->UalphaNorm + tmp_pwm);


    if (lambda1<=0)
        if (lambda3>0) {
            gamma=lambda3;
            gamma1=-lambda1;
            p->sector=1; /*110 ������ */
            p->GammaA=p->k_pwm-gamma;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-0;

        } else if (lambda2>0) {
            gamma=lambda2;
            gamma1=-lambda3;
            p->sector=2; /*011 ������ */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-gamma1;
            /*011 ������ */
        } else if (lambda1!=0) {
            gamma=-lambda1;
            gamma1=-lambda2;
            p->sector=3; /*011 ������ */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-gamma;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*011 ������ */
        } else {
            gamma=-lambda3;
            gamma1 = lambda1;
            p->sector= 4; /*101 ������ */
            p->GammaA=p->k_pwm-gamma1;
            p->GammaB=p->k_pwm-0;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*101 ������ */

        }
    else if (lambda2>0) {
        gamma=lambda1;
        gamma1=lambda2;
        p->sector= 0; /*110 ������ */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-gamma1;
        p->GammaC=p->k_pwm-0;
        /*110 ������ */
    } else if (lambda3<0) {
        gamma=-lambda3;
        gamma1 = lambda1;
        p->sector= 4; /*101 ������ */
        p->GammaA=p->k_pwm-gamma1;
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-(gamma+gamma1+1);
        /*101 ������ */
    } else {
        gamma=-lambda2;
        gamma1=lambda3;
        p->sector=5; /*101 ������ */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-gamma;
        /*101 ������ */
    }


    /*��������� */

    if (p->GammaA<0) p->GammaA=0;
    if (p->GammaB<0) p->GammaB=0;
    if (p->GammaC<0) p->GammaC=0;

    if (p->GammaA>p->k_pwm) p->GammaA=p->k_pwm+1;
    if (p->GammaB>p->k_pwm) p->GammaB=p->k_pwm+1;
    if (p->GammaC>p->k_pwm) p->GammaC=p->k_pwm+1;

    //���������� ���� ������� ��������� ������ ���� ������� ������� ����� �� ����, �����
    //������������� ��������� ���������� �����������, ��� � ��������� ��� ����� ���� �������� � ��������� ������ ���.
    //������ ��� - ����� ������������� �������� � ���������� "�����������" ��� ��������� ������ ������� � ���
    DINT;
    if (abs(p->EvXRegs->T1CNT) > 30) {
        p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
        p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
        p->EvXRegs->CMPR3 = (Uint16) p->GammaC;
        p->EvXRegs->T1PR = p->k_pwm;
    }
    EINT;
}

//! ������� �������������� ���

//! \memberof TPWM_Module
void PWM_Module_Sin_Update(TPWM_Module *p) {
	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;


	p->UalphaNorm = p->UalphaRef;
	p->UbetaNorm = p->UbetaRef;

	//������� ��������� (��� ����� �����������)
	p->U_mag = _IQmag(p->UalphaNorm, p->UbetaNorm);

	/* ������������ ��������� �������, ������� ����� ����������*/
	knorm = _IQmag(p->UalphaNorm, p->UbetaNorm);
	if (knorm >= p->U_lim) { //�� ������, ��� ���� �����������?
		knorm = _IQdiv(p->U_lim, knorm); //� ��� �� ����������, ��� ��������, ������������ ����������
		p->UalphaNorm = _IQmpy(knorm, p->UalphaNorm); //��������� ��������������� ����������
		p->UbetaNorm = _IQmpy(knorm, p->UbetaNorm); //� ���
		p->ULimitation = 1; //���� � ���, ��� ���� ����������� ����������
	} else
		p->ULimitation = 0;

	//������������ �������� ����������. ��� ��� �������������� ��� ��������� �� 0.866 ������� ����������,
	//��� ��������� ��� (270� ������������ ������� ���������� ������ 311�), �� ��� ����, ����� ��� ��� �� ������� � ����������
	//p->UalphaNorm, p->UbetaNorm ���������� �� �� ����� ���������� �� ������, ��� � � ��������� ���, ����� ������� ��������� � 1/0.866 ���.
	//������� �� ��� ����� ��� ����������� ������, ����� ��������� �������� � ���������� �� ������������� ���������.
	p->UalphaNorm = _IQmpy(p->UalphaNorm, _IQ(1/0.866/2));
	p->UbetaNorm = _IQmpy(p->UbetaNorm, _IQ(1/0.866/2));

	/*������ �������������� �� ������� �����, ����� � a,b,c */

	PhasePtsA = _IQ(0.5) - (p->UalphaNorm);
	PhasePtsB = _IQ(0.5) - (_IQmpy(p->UbetaNorm,_IQ(0.8660254)) - (p->UalphaNorm >> 1));
	PhasePtsC = _IQ(0.5) - (-_IQmpy(p->UbetaNorm, _IQ(0.8660254)) - (p->UalphaNorm >> 1));

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	/*��������� */

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

//! ������� ��� � ����������� ������ (��� ������ SRM)

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

	/*��������� */

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

	//������ �������������� ��� ����������� ������������ ���������� � ��������� -1 - 0 - +1 (� ������������� ��������)
	//���������� 1 - ���������� (1/2 + 0.5) = 1, ���������� 0 - ���������� 0,5 � �.�.
	gamma1_DC = -(UalphaRef >> 1) + _IQ(0.5); // (IQ), �������� �������� ���������� � ��������������� ����������.

	//�� ������ �������� �������� p->k_pwm �������, ������ ������� ����� ���� � temp32.
	//��-����� ��� �������� ������������� ������������ ������ iq16.
	gamma1_DC = gamma1_DC >> 8; // (IQ16) ��������� ��, ��� ����, � iq16.
	temp32 = _IQ16mpy(gamma1_DC, _IQ16(p->k_pwm)); // (IQ16) ��������� ���������� � �������� ��� �������� � ������� ���������.
	p->GammaA = temp32 >> 16; // (IQ0) �������� ����� ����� � ������� ���������.
	p->GammaB = p->k_pwm - p->GammaA; // � �������� ��������� EPwm2 �� ��, ��� � � EPwm1.

	//�� ������ �������� �������� p->k_pwm �������, ������ ������� ����� ���� � temp32.
	//��-����� ��� �������� ������������� ������������ ������ iq16.
	gamma2_DC = UbetaRef >> 8; // (IQ16) ��������� ��, ��� ����, � iq16.
	temp32 = _IQ16mpy(gamma2_DC, _IQ16(p->k_pwm)); // (IQ16) ��������� ���������� � �������� ��� �������� � ������� ���������.
	p->GammaC = p->k_pwm - (temp32 >> 16); // (IQ0) �������� ����� ����� � ������� ���������.

    p->EvXRegs->CMPR1 = (Uint16) p->GammaA;
    p->EvXRegs->CMPR2 = (Uint16) p->GammaB;
    p->EvXRegs->CMPR3 = (Uint16) p->GammaC;

}

//! ������� ��� ��� ��������� ������� ����������� ������������� ���������

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

//! ����� �������-������� ��� ������� ���

//����������� �� ������ ��� (�� �������), ��� ������� � ����������.

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

//! ��������� ������

//! ��������������� ��������� ������������� ��������
//! �������� �������� �������, ������� ��� � �.�.

//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *p) {
	Uint16 tmp;

	//������� ���. ����� "�� ����".
	if (p->FreqPrev != p->Frequency) { //������� �������
		DINT; //���������� ����������
        //�������� ���������/��������
        if (p->Frequency < PWM_FREQ_MIN)
            p->Frequency = PWM_FREQ_MIN;
        if (p->Frequency > PWM_FREQ_MAX)
            p->Frequency = PWM_FREQ_MAX;
        //�������� ������
        p->k_pwm = _IQ10div(_IQ10(150000), p->Frequency << 2) >> 10;        //������. � �������� ��������� � ����� ����
        if (p->k_pwm<2000)
            p->k_pwm =2000;

		//��������� ����� ������� ��� ���������� �����, ������ �� ������� ���
		adc.IASampleLength = (p->Frequency >> 10) / 10;	//������� ��� � ������� 22.10, �������� � ���� � ����� �� 10 - ������� ������� ������� ����������
		if (adc.IASampleLength > 4)	//�� ����� 4 �����
			adc.IASampleLength = 4;
		if (adc.IASampleLength < 1)	//�� ����� 1 �����
			adc.IASampleLength = 1;
		adc.IBSampleLength = adc.IASampleLength;
		adc.ICSampleLength = adc.IASampleLength;
		adc.UdcSampleLength = adc.IASampleLength;

		p->FreqPrev = p->Frequency; //���������� �������
		EINT;
	}
}

//! ������� ��������� ��� (��������� ���������)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//���� "��������"

	// ������� �������������� ��������� �������
    EvaRegs.COMCONA.all |= 0x0200;
	GPIO_INV_ON;

}

//! ������� ���������� ��� (���������� ���������)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//���� "���������"
	// ������������� ������� ��� �����

    EvaRegs.COMCONA.all &= 0xfdff;
	GPIO_INV_OFF;

}

/*@}*/
