#ifndef MODEL

#include "dio_func.h"
#include "main.h"
#endif


//give descriptions according real state
#define SM_LOGIC_INIT				99
#define SM_CHECK_OPERATION 			0
#define SM_GO_LOAD_BATT				1
#define SM_GO_CHARGE_BATT			2
#define SM_CHECK_CONDITIONS 		3
#define SM_GO_UP_BATT 				4
#define SM_CHARGE_BATT 				5
//#define SM_UDC_LOW					1
//#define SM_GO_LOAD_BATT				2
//#define SM_LOAD_BATT				3
//#define SM_GO_LOAD_BATT_DIESEL		4
//#define SM_LOAD_BATT_DIESEL			5
#define SM_LOGIC_FAILED				100


void SM_GRID_NIGHT_BATT_CHARGE_Init(SM_GRID_NIGHT_BATT_CHARGE*p)
{
	p->state=SM_LOGIC_INIT;
	p->state_prev=-1;
	inv.params.Udc_day=_IQ(500.0/700);
	inv.params.Udc_level_go_on=_IQ(500.0/700);
	cmd_logic.status.profile = 1;
	dcdc.discharge_type = 0;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SM_GRID_NIGHT_BATT_CHARGE_ms_Calc(SM_GRID_NIGHT_BATT_CHARGE*p)
{
volatile  int _P_mult;
volatile  int _P_dcdc_ref;

if(cmd_logic.remote_refs.P_dcdc_ref<0)
	_P_dcdc_ref = -_IQmpy(cmd_logic.refs.P_dcdc_ref<<16,inv_params._1_P_nom); //знак минус нужен
else
{
	_P_dcdc_ref=-100<<16;

}

//if(cmd_logic.remote_refs.P_dcdc_ref<0)
//	_P_dcdc_ref=220<<16;
//else
//{
//	_P_dcdc_ref=-1<<16;
//	if (dcdc.charge_state == 2)
//	{
//	//	_P_mult = dcdc.U2_meas_V_I12Q4*dcdc.Idc2_ref;
//	//	_P_dcdc_ref = -_IQmpy(_IQmpy(_P_mult,_IQ(0.001))<<16,inv_params._1_P_nom);
//		_P_dcdc_ref=(-100)<<16;
//	}
//	else
//		_P_dcdc_ref = -_IQmpy(cmd_logic.refs.P_dcdc_ref<<16,inv_params._1_P_nom); //знак минус нужен
//}


cmd_logic.refs.P_ref=_P_dcdc_ref - _IQmpy(_IQ(2),inv_params._1_P_nom);//2 kwt for sine filter
//todo 224 т.к. форматы уставки мощности DCDC и инертора и дизеля рахные нужно привожить в все к одному формату инвертора


if (p->state!=p->state_prev) p->E=1; else p->E=0;
p->state_prev=p->state;

if ((dcdc.operating==0)&&(p->dcdc_attempts>=3)) {p->state = SM_PROFILE_LOGIC_FAILED;}

if(inv.in.cmd_protect_pow_off==1 || apl_protect.AR1.state == AR_STATE_FAIL)
	p->state = SM_PROFILE_LOGIC_FAILED;

switch (p->state) {
case SM_LOGIC_INIT:
	if(p->E==1) {
		p->dcdc_attempts=0;
		dcs_ctrl.ctrl_mode_synced_P_gen=1;
		diesel.cmd_in_off=1;
	}
	if(dcdc.operating == 1 && inv.state == SM_DIO_LOGIC_INV_OPERATION) p->state = SM_CHARGE_BATT;
	else
	p->state = SM_CHECK_OPERATION;
	break;

case SM_CHECK_OPERATION:
	if(p->E==1) {
		p->counter=0;
	}
	p->counter++;

	if(dcdc.operating==1)
		{p->state=SM_GO_LOAD_BATT;break;}


	if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
		p->counter=1000;
		//TODO 225 здесь нужен вложенный автомат на каждое устройство.
		//В этой реализцаии я вынужден поставить break иначе выполняется только последняя ветка
		if ((dcdc.operating==0)&&(p->dcdc_attempts<3)) {p->state = SM_GO_LOAD_BATT; break;}
		//TODO 223 добавить проверку что батарейка разрядилась
	}

	break;

case SM_GO_LOAD_BATT:
	if(p->E==1) {
			p->counter=0;
			cmd_logic.remote_refs.P_dcdc_ref = ((-2)<<8);
			dcdc.Idc2_ref = ((-10)<<4);
			dcdc.ena=1;
		}

		//check after 5 seconds DCDC is working. If not go start diesel
		p->counter++;

		if (p->counter>10000){
			if (dcdc.operating==1) {
				p->dcdc_attempts=0;
				p->state = SM_GO_CHARGE_BATT;
			}
			else
			{
				p->dcdc_attempts++;
				p->state= SM_CHECK_OPERATION;
			}

		}

		break;

case SM_GO_UP_BATT:
	if(p->E==1) {
			p->counter=0;
			dcdc.ena=1;
		}

		//check after 5 seconds DCDC is working. If not go start diesel
		p->counter++;

		if (p->counter>10000){
			if (dcdc.operating==1) {
				p->dcdc_attempts=0;
				p->state = SM_CHARGE_BATT;
			}
			else
			{
				p->dcdc_attempts++;
				p->state= SM_CHARGE_BATT;
			}

		}

		break;

case SM_GO_CHARGE_BATT:
	if(p->E==1) {
			p->counter=0;

		}

		if (inv.state!=SM_DIO_LOGIC_INV_OPERATION) inv.in.cmd_pow_on=1;

		p->counter++;

		if(inv.state==SM_DIO_LOGIC_INV_OPERATION)
			p->state=SM_CHARGE_BATT;

		if(p->counter>(1000*60*p->jump_time_min))
			sc_profile.in.cmd_remote_set_profile = SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;


	break;

case SM_CHARGE_BATT:
	if(p->E==1) {
			p->counter=0;
			p->counter_2=0;
			cmd_logic.remote_refs.P_dcdc_ref = p->set.dcdc_P_charge;
			dcdc.Idc2_ref = p->set.dcdc_I_charge;
		}

	p->counter++;
	p->counter_2++;


	if ((dcdc.operating==0)&&(p->dcdc_attempts<3)) {p->state = SM_GO_UP_BATT;}

	if(p->counter>5000)
	{
		p->counter = 5000;
		if(dcdc.charge_state == 9) sc_profile.in.cmd_remote_set_profile = SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;
	}


	if(p->counter_2>(1000*60*p->jump_time_min))
		sc_profile.in.cmd_remote_set_profile = SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

	break;


case SM_PROFILE_LOGIC_FAILED:
	if(p->E==1) {
		sc_profile.in.cmd_remote_set_profile = SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;
		}

	break;
default:
	break;
}

p->ena_prev=p->ena;




}
