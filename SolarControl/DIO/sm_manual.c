#ifndef MODEL
#include "dio_func.h"
#include "dcs_func.h"
//#include "main.h"
#include "sm_manual.h"
#endif


//give descriptions according real state
#define SM_LOGIC_INIT				99
#define SM_LOGIC_MANUAL 					1
//#define SM_LOGIC_FAILED				100


void SM_MANUAL_Init(SM_MANUAL*p)
{
	p->state=SM_LOGIC_INIT;
	p->state_prev=-1;

}



static int _temp=0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SM_MANUAL_ms_Calc(SM_MANUAL*p)
{
//volatile  int _I2_mult_U2;
//volatile  int _P_dcdc_ref;
//
//if(dcs_ctrl.ctrl_mode_synced_P_gen==1)
//{
//	if (dcdc.charge_state == 2)
//	{
//		_I2_mult_U2 = dcdc.U2_meas_V_I12Q4*dcdc.Idc2_ref;
//		_P_dcdc_ref = -_IQmpy(_IQmpy(_I2_mult_U2,_IQ(0.001))<<16,inv_params._1_P_nom);
//	}
//	else
//		_P_dcdc_ref = -_IQmpy(cmd_logic.refs.P_dcdc_ref<<16,inv_params._1_P_nom); //знак минус нужен
//
//	if(_P_dcdc_ref > 0)
//		cmd_logic.refs.P_ref=diesel.P_ref*diesel.ON+_P_dcdc_ref*dcdc.operating+_IQmpy(_IQ(2),inv_params._1_P_nom);
//
//	if(_P_dcdc_ref < 0)
//		cmd_logic.refs.P_ref=diesel.P_ref*diesel.ON+_P_dcdc_ref*dcdc.operating-_IQmpy(_IQ(2),inv_params._1_P_nom);
//}
//

if (p->state!=p->state_prev) p->E=1; else p->E=0;
p->state_prev=p->state;

switch (p->state) {
case SM_LOGIC_INIT:
		p->state=SM_LOGIC_MANUAL;
	break;

case SM_LOGIC_MANUAL:
	if(p->E==1) {
		p->counter=0;
	}
	break;



case SM_PROFILE_LOGIC_FAILED:
	break;
default:
	break;
}

p->ena_prev=p->ena;




}
