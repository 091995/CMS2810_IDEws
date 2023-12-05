/*!
    Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      SMProtect.c
 \brief     ������ �����.   (��. TSM_Protect)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup SMProtect
 @{ */
#ifndef MODEL
#include "DSP.h"
#include "main.h"
#include "stdlib.h"
#endif

int16 WriteCounter = 0;

int cntrinva=0;
int cntrinvb=0;
int cntrinvc=0;
int cntrtra=0;
int cntrtrb=0;
int cntrtrc=0;

void DCS_Protect_Init(TDCS_Protect *p) {
	p->state_prev =-1;
	p->state = SM_DCS_PROT_INIT;
	p->U1_max=_IQ(1.4);
	p->U1_min=_IQ(0.7);
	p->Udc_max=_IQ(900/700.0);
	p->Udc_min=_IQ(400/700.0);
	p->Imax = _IQ(0.98);

	//if any protect turn pwm off
	p->mask_fault_pwm1=0xffff;
	//if any HW protect turn power off
	p->mask_fault_off=F_PDP_INV1|F_PDP_IMAX|F_PDP_EXT_LOST|F_PROGRAM_10K; //TODO 206 ������ ��� ������ ��������� ���������� ��������
																		   //�������� � Unicon
	p->T_max=(Uint16)(90<<4); //90 degree is protection

	//pwm.PDP_trip_reset(&pwm);


}


void DCS_Protect_Fast_Calc(TDCS_Protect *p) {

	static long udc_min_cntr;

#ifndef MODEL

//directly check states of 	TZ pin
	pwm.PDP_inv1 |= (~NT_GPIOG->DATA>>13)&0x1;
//	_TZ[1] = (NT_GPIOA->DATA>>9)&0x1;
	pwm.PDP_pulses_block_Imax |= (~NT_GPIOG->DATA>>15)&0x1;
	pwm.PDP_inv_ext_lost |= NT_PWM0->TZFLG_bit.OST;
//	_TZ[3] = (NT_GPIOE->DATA>>7)&0x1;
//	_TZ[4] = (NT_GPIOC->DATA>>8)&0x1;
//	_TZ[5] = (NT_GPIOE->DATA>>14)&0x1;
#endif
	//TODO OK jsut for debug
	//pwm.PDP_inv1=0;
	//���������� ������ �� ���������
	if (pwm.PDP_inv1)  p->bit_fault1 |= F_PDP_INV1;
	if (pwm.PDP_inv_ext_lost)  p->bit_fault1 |= F_PDP_EXT_LOST;
	if (pwm.PDP_pulses_block_Imax)  p->bit_fault1 |= F_PDP_IMAX;


	/*������ �� ������������� ���� from inverter side*/
	if (labs(adc.Ia_inv) > p->Imax) {
		cntrinva++;
		if(cntrinva>=3)
		p->bit_fault1 |= F_MAX_I_INV_A;
	}
	else cntrinva=0;

	if (labs(adc.Ib_inv) > p->Imax) {
			cntrinvb++;
			if(cntrinvb>=3)
			p->bit_fault1 |= F_MAX_I_INV_B;
		}
	else cntrinvb=0;

	if (labs(adc.Ic_inv) > p->Imax) {
			cntrinvc++;
			if(cntrinvc>=3) p->bit_fault1 |= F_MAX_I_INV_C;
		}
	else cntrinvc=0;

	/*������ �� ������������� ���� from trafo side*/
	if (labs(adc.Ia_tr) > p->Imax) {
			cntrtra++;
			if(cntrtra>=3) p->bit_fault1 |= F_MAX_I_TR_A;
		}
	else cntrtra=0;

	if (labs(adc.Ib_tr) > p->Imax){
			cntrtrb++;
			if(cntrtrb>=3) p->bit_fault1 |= F_MAX_I_TR_B;
		}
	else cntrtrb=0;

	if (labs(adc.Ic_tr) > p->Imax) {
			cntrtrc++;
			if(cntrtrc>=3) p->bit_fault1 |= F_MAX_I_TR_C;
		}
	else cntrtrc=0;

	//if (labs(labs(adc.Ia_tr) - labs(adc.Ib_tr))>_IQ(60.0/848.0) || labs(labs(adc.Ib_tr)-labs(adc.Ic_tr))>_IQ(60.0/848.0) ||labs(labs(adc.Ic_tr)-labs(adc.Ia_tr))>_IQ(60.0/848.0))
		//p->bit_fault1 |= F_GRID_SHORT_CIRCUIT;

	//��� ���������� ���������� ���� ��������� �����
	if (adc.Udc > p->Udc_max) {
		p->bit_fault1 |= F_UDC_MAX; // ������������� Ud
	}

	// TODO 204 �������� ���������� Udc ��� ������. ������ ��������� ������� �������� � ��������� � ������ �����.
	// TODO 204 ��� ���������� ����� ��������� Udc �� �������� ���������� �������� ����� ��������� �������� ���
	//TODO 204 - ���� ������ �� �������� ���������� ��� ���

	if (dcs_ctrl.cmd_Udc_ctrl_ena == 1)
	{
		if (adc.Udc < p->Udc_min) {
			udc_min_cntr++;
			if(udc_min_cntr>2) p->bit_fault1 |= F_UDC_MIN;
		}
		else udc_min_cntr=0;
	}

	//������ �� �����������.
	if ((adc.T1_inv1>p->T_max)||(adc.T2_inv1>p->T_max)||(adc.T3_inv1>p->T_max)||(adc.T3>p->T_max)||(adc.T4>p->T_max))
	{
		p->bit_fault1|= P_TEMPERATURE_MAX;
	}


	//TODO 203 ������ � ������ ������ ������������ ���������� ��������������
	if (inv.state==SM_DIO_LOGIC_INV_OPERATION) {
	if(adc.rms.Uab_tr > p->U1_max||adc.rms.Ubc_tr > p->U1_max||adc.rms.Uca_tr > p->U1_max)
			 p->bit_fault1|=F_U_TR_MAX;
	if (adc.rms.Uab_tr < p->U1_min||adc.rms.Ubc_tr < p->U1_min||adc.rms.Uca_tr < p->U1_min) //TODO 210 - ������ ����� �� ������� ������?
			p->bit_fault1|=F_U_TR_MIN;

	}
//
//
	DINT; //���������� ����������
		  //������, ��������� ������� ��������
	p->masked_bit_fault1 = p->bit_fault1 & p->mask_fault_pwm1;//������������ ������ ������
	p->masked_fault_off = p->masked_bit_fault1 & p->mask_fault_off;//������������ ������ ������

	EINT;      //���������� ����������

//
	//������� ���������� ������� �����
	if (p->state_prev != p->state) p->E = 1; else p->E = 0;
	p->state_prev = p->state;

	switch (p->state) {
	case SM_DCS_PROT_INIT: {
		if (p->E == 1) {
			p->counter=0;
		}

		p->counter++;

		p->bit_fault1 = 0;
		pwm.PDP_inv1=0;
		pwm.PDP_pulses_block_Imax=0;
		pwm.PDP_inv_ext_lost=0;

		if (p->counter==50)
			pwm.PDP_trip_reset(&pwm);
		//���������� ��������� ������� ����� ��������� �����������
		//����� �� ������ ������ ������������ ������ ���
		if (p->counter > 100) {
			p->state = SM_DCS_PROT_NO_TRIP;
		}
		break;
	}

	case SM_DCS_PROT_NO_TRIP: {  //�����
		if (p->E == 1) {        //������ ���������
			//inv_status.bit.fault = 0;
		}
		//���� ������?
		if (p->masked_bit_fault1  != 0) {
			pwm.Off(&pwm);
			p->state = SM_DCS_PROT_TRIP; //��������� � ��������� ������
		}
		break;
	}

	case SM_DCS_PROT_TRIP: { //��������� ������ (��������� ������)
		if (p->E == 1) {

		}
		//inv_status.bit.fault = 1;
		//���������� ���. ���� ��� ��� ��������� ���������� �������� �����������, ����� �� �� �����
		pwm.Off(&pwm);

		//������ ������� ������
		if (dcs_ctrl.cmd_trip_reset == 1) {//������� �� ����� ������
			//�������� ��� ����� ������
			p->bit_fault1 = 0;
			pwm.PDP_trip_reset(&pwm);
			p->state = SM_DCS_PROT_NO_TRIP;	//���� � "�����"

		}
		break;
	}
	}
}

//! \memberof TSM_Protect
void DCS_Protect_ms_Calc(TDCS_Protect *p) {
//	if (WriteCounter <= 15)   //���� ������ �����
//	{
//		if (((p->masked_bit_fault1 >> WriteCounter) & 0x1) != 0)  //����� ii-� ���� ������
//		{
//			if (((p->bit_fault_written1 >> WriteCounter) & 0x1) == 0)  //� ��� �� ��������
//			{
//				FaultLog.write(&FaultLog, WriteCounter + 1);
//				p->bit_fault_written1 |= (1 << WriteCounter);
//			}
//		}
//		else
//			p->bit_fault_written1 &= ~(1 << WriteCounter);
//	}
//	else if (WriteCounter <= 31) //������ �����
//	{
//		if (((p->masked_bit_fault2 >> (WriteCounter - 16)) & 0x1) != 0)  //����� ii-� ���� ������
//		{
//			if (((p->bit_fault_written2 >> (WriteCounter - 16)) & 0x1) == 0)  //� ��� ������ ��� ���������
//			{
//				FaultLog.write(&FaultLog, WriteCounter + 1);
//				p->bit_fault_written2 |= (1 << (WriteCounter - 16));
//			}
//		}
//		else
//			p->bit_fault_written2 &= ~(1 << (WriteCounter - 16));
//	}
//	WriteCounter++;
//	if (WriteCounter >= (33 - 1))
//		WriteCounter = 0;
}

//! ��������� ������.

//! \memberof TSM_Protect
void DCS_Protect_Slow_Calc(TDCS_Protect *p) {
	/* �������� ���������� ����� ��������. �� ������������� �������� ����� ��� �������,
	 * � �������� ������� /FAULT � /OCTW, �� ����� ������, ��� ������ ���������, ���� �� SPI ��������� �������.
	 * �������, ������, ����� � ����.
	 */
//	if (p->readDrvSts == 1) {
//		p->readDrvSts = 0;
//		drv8301.read(&drv8301);
//
//	}

	/* ����� �������� ������, ���� ��������� ��� ����� GATE_RESET */
//	if (p->clearDrvFault == 1) {
//		p->clearDrvFault = 0;
//		drv8301.CTRL1.bit.GATE_RESET = 1;
//		drv8301.write(&drv8301, CNTRL_REG_1_ADDR);
//		drv8301.write(&drv8301, CNTRL_REG_2_ADDR);
//	}
}
