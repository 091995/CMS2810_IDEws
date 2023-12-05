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

 \file      SMProtect.c
 \brief     ������ �����.   (��. TSM_Protect)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup SMProtect
 @{ */

#include "DSP28_Device.h"
#include "main.h"
#include "stdlib.h"

int16 WriteCounter = 0;

//!�������������

//!������������ ������ ����������
//! \memberof TSM_Protect
void SM_Protect_Init(TSM_Protect *p) {
	p->state_prev = 0xff;
	p->state = 0x00;

#if defined (HW_MOTORCONTROLBOARD)

	EALLOW;
	// ����� ���������� ������
	GpioMuxRegs.GPGMUX.bit.SCIRXDB_GPIOG5 = 0;
    GpioMuxRegs.GPGDIR.bit.GPIOG5 = 0;

    //������ ������ � ����� �0
    GpioMuxRegs.GPDMUX.bit.T2CTRIP_SOCA_GPIOD1 = 0;
    GpioMuxRegs.GPDDIR.bit.GPIOD1 = 0;

    //������ ������ � ����� �1
    GpioMuxRegs.GPDMUX.bit.T3CTRIP_PDPB_GPIOD5 = 0;
    GpioMuxRegs.GPDDIR.bit.GPIOD5 = 0;

    //������ ������ � ����� �2
    GpioMuxRegs.GPDMUX.bit.T4CTRIP_SOCB_GPIOD6 = 0;
    GpioMuxRegs.GPDDIR.bit.GPIOD6 = 0;

    //������ ������ � ������ ������
    GpioMuxRegs.GPBMUX.bit.C5TRIP_GPIOB14 = 0;
    GpioMuxRegs.GPBDIR.bit.GPIOB14 = 0;
    EDIS;

#endif

}

//! ������� ������.

//!������������ ��� ������ � ��� �� ������������� ������������� ������.
//! \memberof TSM_Protect
void SM_Protect_Fast_Calc(TSM_Protect *p) {

    p->poweredOk++;
    if (p->poweredOk < 5000)
        return;
    else
        p->poweredOk = 5000;


    //���������� ������ �� ���������
	if (pwm.PDP_Fault) {
		if ((sm_ctrl.state != CTRL_STOP) && (sm_ctrl.state != CTRL_RUN))
			sm_prot.bit_fault1 |= F_PDPINT;
	}

    if (!DRV_FAULT) {
        //������� �����-�� ���������� ������
        sm_prot.bit_fault1 |= F_PDPINT;
    }


#if defined (HW_MOTORCONTROLBOARD)
	if (!DRV_FAULT1) {
		//������� �����-�� ���������� ������
		sm_prot.bit_fault2 |= F_PDP_SWITCH_A0;
	}

	if (!DRV_FAULT2) {
		//������� �����-�� ���������� ������
		sm_prot.bit_fault2 |= F_PDP_SWITCH_A1;
	}

	if (!DRV_FAULT3) {
		//������� �����-�� ���������� ������
		sm_prot.bit_fault2 |= F_PDP_SWITCH_A2;
	}

	if (!DRV_FAULT4) {
		//������� �����-�� ���������� ������
		sm_prot.bit_fault2 |= F_PDP_SWITCH_LOWER;
	}
#endif

	/*������ �� ������������� ����*/
	if (adc.Imeas_a > sm_prot.Imax_protect)
		sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_A;
	if (adc.Imeas_a < -sm_prot.Imax_protect)
		sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_A;
	if (adc.Imeas_b > sm_prot.Imax_protect)
		sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_B;
	if (adc.Imeas_b < -sm_prot.Imax_protect)
		sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_B;
	if (adc.Imeas_c > sm_prot.Imax_protect)
		sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_C;
	if (adc.Imeas_c < -sm_prot.Imax_protect)
		sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_C;

	//��� ���������� �������� ���� ��������� ����� 
	if (labs(cur_par.speed) > sm_prot.speed_max) {
		sm_prot.bit_fault2 |= F_CTRL_SPEED_MAX; // ������������� ��������
	}

	//��� ���������� ���������� ���� ��������� ����� 
	if (adc.Udc_meas > sm_prot.Umax_protect) {
		sm_prot.bit_fault1 |= F_CTRL_HI_UDC; // ������������� Ud
	}

	//�������� ����������
	if (adc.Udc_meas < sm_prot.Umin_protect) { //���� ������ ������� �� ����� ������
		if (sm_ctrl.state != CTRL_STOP) {
			sm_prot.bit_fault1 |= F_CTRL_LOW_UDC;
		}
	}

	//��� ���������� ����������� ���� ��������� �����
	if (adc.T_meas > sm_prot.T_max) {
		sm_prot.bit_fault1 |= F_CTRL_HI_TEMP; // ������������ �����������
	}

	DINT; //���������� ����������
		  //������, ��������� ������� ��������
	p->masked_bit_fault1 = p->bit_fault1 & p->mask_fault1;//������������ ������ ������
	p->masked_bit_fault2 = p->bit_fault2 & p->mask_fault2;
	EINT;      //���������� ����������


	//������� ���������� ������� �����
	if (p->state_prev != p->state) //����� ���������?
		p->E = 1;//�������� ���� ������� ��������� "entry"
	else
		p->E = 0;//����� ����������
	p->state_prev = p->state;

	switch (p->state) {//� ����������� �� �������� ���������
	case PROT_OFF: { //������ ���������
		if (p->E == 1) { //������ ���������
		}

		//�������� ��� ������
		p->bit_fault1 = 0;
		p->bit_fault2 = 0;

		//���������� ��������� ������� ����� ��������� �����������
		//����� �� ������ ������ ������������ ������ ���
		if (p->powered_okCounter++ > 5000) {
			p->state = PROT_ON_OK;
		}
		break;
	}

	case PROT_ON_OK: {  //�����
		if (p->E == 1) {        //������ ���������
			drv_status.bit.fault = 0;
		}
		//���� ������?
		if ((p->masked_bit_fault1 | p->masked_bit_fault2) != 0) {
			p->state = PROT_FAIL; //��������� � ��������� ������
		}
		break;
	}

	case PROT_FAIL: { //��������� ������ (��������� ������)
		if (p->E == 1) {
			cmd.all = 0;
		}

		drv_status.bit.fault = 1;
		//���������� ���. ���� ��� ��� ��������� ���������� �������� �����������, ����� �� �� �����
		pwm.Off(&pwm);
		//������ ������� ������
		if ((cmd.bit.trip_reset == 1) || (RESET_FAULT_BUTTON == 1)) {//������� �� ����� ������
			p->state = PROT_ON_OK;//���� � "�����"
			//�������� ��� ����� ������
			p->bit_fault1 = 0;
			p->bit_fault2 = 0;
			cmd.all = 0;//��������� �����

            drv_status.bit.fault = 0;
            //���������� ���� - �� ������ �� �����
            co1_vars.ParamRestorationError = 0;
		}
		break;
	}
	}
}

//! \memberof TSM_Protect
void SM_Protect_ms_Calc(TSM_Protect *p) {
	if (WriteCounter <= 15)   //���� ������ �����
	{
		if (((sm_prot.masked_bit_fault1 >> WriteCounter) & 0x1) != 0)  //����� ii-� ���� ������
		{
			if (((sm_prot.bit_fault_written1 >> WriteCounter) & 0x1) == 0)  //� ��� �� ��������
			{
				FaultLog.write(&FaultLog, WriteCounter + 1);
				sm_prot.bit_fault_written1 |= (1 << WriteCounter);
			}
		}
		else
			sm_prot.bit_fault_written1 &= ~(1 << WriteCounter);
	}
	else if (WriteCounter <= 31) //������ �����
	{
		if (((sm_prot.masked_bit_fault2 >> (WriteCounter - 16)) & 0x1) != 0)  //����� ii-� ���� ������
		{
			if (((sm_prot.bit_fault_written2 >> (WriteCounter - 16)) & 0x1) == 0)  //� ��� ������ ��� ���������
			{
				FaultLog.write(&FaultLog, WriteCounter + 1);
				sm_prot.bit_fault_written2 |= (1 << (WriteCounter - 16));
			}
		}
		else
			sm_prot.bit_fault_written2 &= ~(1 << (WriteCounter - 16));
	}
	WriteCounter++;
	if (WriteCounter >= (33 - 1))
		WriteCounter = 0;

	// �������� �������������� ���������� CANopen �� EEPROM
#ifdef CAN_1_ENABLE
	if(co1_vars.ParamRestorationError)
		p->bit_fault1 |= F_CAN_RESTORATION_ERROR;
#endif
}

//! ��������� ������.

//! \memberof TSM_Protect
void SM_Protect_Slow_Calc(TSM_Protect *p) {

}

/*@}*/
