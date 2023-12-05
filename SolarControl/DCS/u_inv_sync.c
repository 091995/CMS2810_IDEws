#ifndef MODEL
#include "V_IQmath.h"         /* Include header for IQmath library */
#include "DCS_func.h"
#endif

// see pdf "����� ������������ ���������� �� ���������� ��������" 09 dec 2022


#define SM_INV_SYNC_CHECK_ANY_DEV_EXIST 		0
#define SM_INV_SYNC_ONLY_OPERATION 				1
#define SM_INV_SYNC_DO_SOFT_SYNC_TO_EXISTING 	2
#define SM_INV_SYNC_READY						3


void inv_sync_init()
{


	// ������������ ������� ����� - PWM
		//NT_COMMON_REG->GPIOPCTLF_bit.PIN0 = 0;//B0
		//NT_COMMON_REG->GPIOPCTLA_bit.PIN11 = 2;//B1

//use i2_pow1_fail(CAP_PWM1 GPIO_E5) and i2_pow2_fail(CAP_PWM2 GPIO_E6) as can_rx1 and can_rx2
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 5); //reset altfunction to GPIO mode
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 6); //reset altfunction to GPIO mode
													// input is a default mode

//		i2_cmd1 (PWM_A6 GPIO_H4) and i2_cmd2 (PWM_B6 GPIO_H5) as can_tx1 and can_tx2

	NT_GPIOH->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 4); //reset altfunction to GPIO mode
	NT_GPIOH->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 5); //reset altfunction to GPIO mode

	NT_GPIOH->OUTENSET_bit.OUTENSET |= (1 << 4);    //set output mode
	NT_GPIOH->OUTENSET_bit.OUTENSET |= (1 << 5);    //set output mode

	isync.sync_ready=0;
	isync.wt= _IQ(1);  //in base units this is 50Hz

	//from matlab model
	long carrier_freq = 5; // in Hz
	long Ts=125e-6;
	long carrier_period_pu= _IQ(1/carrier_freq/Ts)-1;
								//b = 1;
								//E = 0.05;
	isync.alpha =_IQ(1.0513);  //(exp(b*E));
	isync.beta = _IQ(0.0298); //(exp(b*E)-1)/(exp(b)-1));

}





// calculated at ISR 8kHz enables
//  	syncronizaton for referenced 50Hz
//		maximum current detection

void inv_sync_fast_calc() {


//  1.  FRONT DETECTOR AND WIDTH CALCULATION



//  2.	CARRIER COUNTER

//switch (cc_state)
//case init
//break;
//case cnt_up
//break;
//case cnt_down
//break;
//case RX_received
//delta_fi = min (...)
//break;

// 	3.	SIG_TX_LENGTH




// 4 ��� ������� ������� ��� ������ � �������������� ���������� ������� ������� ������ ���� isync.ena==1
if 	(isync.ena==1)
{
	if (isync.state!=isync.state_prev) isync.E=1;else isync.E=0;
	isync.state_prev= isync.state;

	switch (isync.state) {

	case SM_INV_SYNC_CHECK_ANY_DEV_EXIST: // ��� ������ ��������� ����� ��������� ��� �� ����� ������ ���,
										  // � ���� ���-�� ���� �� ����� ������������������ � ������������ ���������

		if (isync.sig_RX==1 && isync.sig_RX_prev==0) //���-�� ����
			isync.state = SM_INV_SYNC_DO_SOFT_SYNC_TO_EXISTING;

		break;

	case SM_INV_SYNC_ONLY_OPERATION: // ���� � ���� ������ ��� �� �������� � ������ ������ ����������. ��� ������� ��������, ��������, ���� ������ ������ �� ���������,
									 // ��� ����� ��������� ��� ������� �������������, ������� ��������� ������ ���� CAN,
									 // ���� ������ ������� �� ��������� sig_TX!=sig_RX, �� ��������� ������������� ������� �������������

		break;

	case SM_INV_SYNC_DO_SOFT_SYNC_TO_EXISTING: // TODO ��� ���������� ��� ������������� ����������?



		break;



	case SM_INV_SYNC_READY: //������������� ���������� - TODO ��� ���������� ��� ������������� ����������?


		break;

	default: break;
	}
} //end if (isync.ena==1)


isync.sig_RX_prev=isync.sig_RX;

}

