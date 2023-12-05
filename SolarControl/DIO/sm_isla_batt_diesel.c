#ifndef MODEL
#include "dio_func.h"
#include "main.h"
#include "sm_isla_batt_diesel.h"
#endif


//give descriptions according real state
#define SM_LOGIC_INIT				99
#define SM_TURN_OFF_VACUUM 			1
#define SM_CHECK_OPERATION_DIESEL 	2
#define SM_GO_LOAD_DIESEL 			3
#define SM_LOAD_DIESEL 				4
#define SM_GO_ENABLE_BATT 			5
#define SM_GO_LOAD_BATT 			6
#define SM_DIESEL_ISLA_CHARGE_BATT 	7
#define SM_GO_DISCHARGE_BATT 		8
#define SM_GO_DISABLE_DIESEL 		9
#define SM_ISLA_DISCHARGE_BATT 		10
#define SM_DIESEL_ISLA 				11
#define SM_K7_ON 					12
#define SM_CYCLE_END 				13
#define SM_NON_CRITICAL_FAIL 		14
#define SM_TURN_ON_VACUUM 			15
#define SM_CHECK_EQUIP				16
#define SM_CHECK_INVS_OFF			17
#define SM_POWER_OFF				18
#define SM_WAIT_UNBLOCK_VACUUM		19
#define SM_ISLA_DENY				20
//#define SM_CHECK_CONDITIONS 		0
//#define SM_UDC_LOW					1
//#define SM_GO_LOAD_BATT				2
//#define SM_LOAD_BATT				3
//#define SM_GO_LOAD_BATT_DIESEL		4
//#define SM_LOAD_BATT_DIESEL			5
#define SM_LOGIC_FAILED				100


void SM_ISLA_BATT_DIESEL_Init(SM_ISLA_BATT_DIESEL*p)
{
	p->state=SM_LOGIC_INIT;
	p->state_prev=-1;
	dcdc.discharge_type = 0;
	vacuum.cmd_out_block = 1;

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SM_ISLA_BATT_DIESEL_ms_Calc(SM_ISLA_BATT_DIESEL*p)
{
	if (p->ena==1)
	{

	if(inv.in.cmd_pow_off == 1)
		p->state = SM_CYCLE_END;

	//если сработала защита на отключение инвертора или АПВ сработало 3 раза и не включил импульсы идем в fail
	if(inv.in.cmd_protect_pow_off==1 || apl_protect.AR1.state == AR_STATE_FAIL)
		p->state = SM_LOGIC_FAILED;

	if(vacuum.blocked == 1)
		p->state = SM_ISLA_DENY;


	if (p->state!=p->state_prev) p->E=1; else p->E=0;
	p->state_prev=p->state;

	switch (p->state) {
	case SM_LOGIC_INIT:
		if (p->E == 1)
		{
			p->counter = 0;
		}
		p->state=SM_CHECK_EQUIP;
		break;

	case SM_CHECK_INVS_OFF:
		if (p->E == 1)
		{
			cmd_logic.status.profile = 5;//enable GENERATOR MODE
			p->counter = 0;
		}
		p->counter++;
		if(p->invs_off == 1)
			p->state = SM_TURN_OFF_VACUUM;

		if(p->counter>120000)
			p->state = SM_NON_CRITICAL_FAIL;
		break;
	case SM_TURN_OFF_VACUUM:
		if (p->E == 1)
		{
			p->counter = 0;
			vacuum.cmd_in_off = 1;
		}
		p->counter++;

		if(vacuum.off==1)
			p->state = SM_K7_ON;

		if (p->counter > 12000)//now one attempt to turn off vacuum
		{
			p->counter = 0;
			p->state = SM_NON_CRITICAL_FAIL;
		}

		break;


	case SM_K7_ON:
		if (p->E == 1)
		{
			p->counter = 0;
			vacuum.cmd_out_block=1;
		}
		p->counter++;
		if (p->counter>1000)
		{
			p->counter = 0;
			inv.in.cmd_pow_on=1; // turn on K7
		}
		if(aux_K7.aux_on == 1) p->state = SM_CHECK_EQUIP;
		break;

	case SM_CHECK_EQUIP:
		if (p->E == 1)
		{
			p->counter = 0;
		}
		if (dcdc.U2_meas_V_I12Q4 < p->Udc2_low)
			p->state = SM_CHECK_OPERATION_DIESEL;
		else
		{
			cmd_logic.remote_refs.P_dcdc_ref = _IQ8(-100);
			dcdc.Idc2_ref=_IQ4(-5);
			p->state = SM_GO_ENABLE_BATT;
		}

		break;

	case SM_CHECK_OPERATION_DIESEL:
		if(p->E==1) {
			p->counter=0;
		}
		p->counter++;

		if(diesel.ON==1)//if diesel is working go to
		{
			if(aux_K7.hold_on == 0)
			p->state = SM_CHECK_INVS_OFF;
			else
			p->state = SM_LOAD_DIESEL;
		}

		if(diesel.ON==0&&p->diesel_attempts>=5)// if diesel doesn't working after 5 attempts go to fail
		{
			p->state=SM_CYCLE_END;
		}


		if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
			p->counter=1000;
			//TODO 225 здесь нужен вложенный автомат на каждое устройство.
			//В этой реализцаии я вынужден поставить break иначе выполняется только последняя ветка
		if ((diesel.ON==0)&&(p->diesel_attempts<5)) {p->state = SM_GO_LOAD_DIESEL;break;}
			//TODO 223 добавить проверку что батарейка разрядилась
		}

		break;


	case SM_GO_LOAD_DIESEL:
		if(p->E==1) {
				p->counter=0;
				diesel.cmd_in_on=1;

			}

		p->counter++;

		if (p->counter>10000)//check diesel is runing after 7 seconds
		{
			if (diesel.ON==1) {
				p->diesel_attempts=0;
				p->state = SM_CHECK_OPERATION_DIESEL;
			}
			else
			{
				p->diesel_attempts++;
				p->state = SM_CHECK_OPERATION_DIESEL;
			}

		}


	break;

	case SM_LOAD_DIESEL:
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pulses_on=1; // enable pulses
		}
		p->counter++;
		// go to charge batt 10 kW
		if (p->counter > 5000)
		{p->counter=5000;
		cmd_logic.remote_refs.P_dcdc_ref = _IQ8(40);
		dcdc.Idc2_ref=_IQ4(40);
		p->state = SM_GO_ENABLE_BATT;}

		break;

	case SM_GO_ENABLE_BATT:
		if (p->E == 1)
		{
			p->counter = 0;
		}
		p->counter++;


		if(dcdc.operating==0&&p->dcdc_attempts>=3&&diesel.ON==1)
		{
			p->state=SM_DIESEL_ISLA;//work without batt only diesel
		}


		if(dcdc.operating==0&&p->dcdc_attempts>=3&&diesel.ON==0)
		{
			p->state=SM_CHECK_OPERATION_DIESEL;
		}


		if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
			p->counter=1000;
			if (p->dcdc_attempts<3) {p->state = SM_GO_LOAD_BATT; break;}
			//if ((diesel.operating==0)&&(p->diesel_attempts<3)) {p->state = SM_GO_LOAD_DIESEL;break;}
			//TODO 223 добавить проверку что батарейка разрядилась
		}
		break;
	case SM_GO_LOAD_BATT:
		if(p->E==1) {
				p->counter=0;
				dcdc.ena=1;
			}

		p->counter++;

		if (p->counter>10000){
			if (dcdc.operating==1) {
				p->dcdc_attempts=0;
				if(aux_K7.aux_on == 0)
				p->state = SM_CHECK_INVS_OFF;
				else
				p->state = SM_DIESEL_ISLA_CHARGE_BATT;
			}
			else
			{
				p->dcdc_attempts++;
				p->state= SM_GO_ENABLE_BATT;
			}

		}

			break;

	case SM_DIESEL_ISLA:
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pulses_on=1;
		}

		if(RTCclock.hour==p->fade_hour&&RTCclock.minute==p->fade_minute&&RTCclock.second<3)
		{
			p->state = SM_CYCLE_END;
			break;
		}

		break;

	case SM_DIESEL_ISLA_CHARGE_BATT:
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pulses_on=1; // enable pulses
		}
		if(RTCclock.hour==p->fade_hour&&RTCclock.minute==p->fade_minute&&RTCclock.second<3)
		{
			p->state = SM_CYCLE_END;
			break;
		}

		if (diesel.ON == 0)
		{
			p->state = SM_GO_DISCHARGE_BATT;
			break;
		}

		if (dcdc.operating==0)
		{
			p->state = SM_DIESEL_ISLA;
			break;
		}

		//if Udc2 is higher then 230 volts go to discharge batt and turn off diesel
		if (dcdc.U2_meas_V_I12Q4 > p->Udc2_high)
			p->counter++;
		else
			p->counter=0;
		if (p->counter > 5000)
			p->state = SM_GO_DISCHARGE_BATT;
		break;

	case SM_GO_DISCHARGE_BATT:
		if (p->E == 1)
		{
			p->counter = 0;
			cmd_logic.remote_refs.P_dcdc_ref = _IQ8(-100);
			dcdc.Idc2_ref=_IQ4(-5);
		}

		if(diesel.P_meas < _IQ16(5))
			p->state = SM_GO_DISABLE_DIESEL;


		break;

	case SM_GO_DISABLE_DIESEL:
		if (p->E == 1)
		{
			p->counter = 0;
			diesel.cmd_in_off = 1;
		}
		p->counter++;

		if(p->counter > 10000)
		{if(diesel.ON == 0) p->state = SM_ISLA_DISCHARGE_BATT; p->counter=1000;}
		break;


	case SM_ISLA_DISCHARGE_BATT:
		if (p->E == 1)
		{
			p->counter = 0;
		}
		if(RTCclock.hour==p->fade_hour&&RTCclock.minute==p->fade_minute&&RTCclock.second<3)
		{
			p->state = SM_CYCLE_END;
			break;
		}

		if (dcdc.operating==0)
		{
			p->state = SM_CHECK_OPERATION_DIESEL;
			break;
		}

		//if Udc2 drops to 190 volts on 5sec start diesel
		if (dcdc.U2_meas_V_I12Q4 < p->Udc2_low)
			p->counter++;
		else
			p->counter=0;
		if (p->counter > 5000)
			p->state = SM_CHECK_OPERATION_DIESEL;
		break;


	case SM_TURN_ON_VACUUM:
		if (p->E == 1)
		{
			p->counter = 0;
			vacuum.cmd_in_on = 1;
		}
		p->counter++;
		if(vacuum.on==1)
			p->state = SM_CYCLE_END;

		if (p->counter > 12000)
		{
			p->counter = 12000;
			p->state = SM_NON_CRITICAL_FAIL;

		}

		break;

	case SM_WAIT_UNBLOCK_VACUUM:
		if (p->E == 1)
		{
			p->counter = 0;
			vacuum.cmd_out_block=0;
		}
		p->counter++;
		if (p->counter > 3000)
		{
			p->counter = 3000;
			p->state = SM_TURN_ON_VACUUM;
		}

		break;


	case SM_CYCLE_END:
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pow_off=1;
			diesel.cmd_in_off = 1;
			dcdc.ena=0;
			cmd_logic.status.profile = 1;
			vacuum.cmd_out_block=0;
		}
		if(vacuum.on == 0)
		p->state = SM_WAIT_UNBLOCK_VACUUM;
		else
		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

	break;

	case SM_NON_CRITICAL_FAIL://about vacuum fails or invsoff fails
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pow_off=1;
			diesel.cmd_in_off = 1;
			dcdc.ena=0;
			cmd_logic.status.profile = 1;
			vacuum.cmd_out_block=0;
		}

		if(vacuum.on == 0)
		p->state = SM_WAIT_UNBLOCK_VACUUM;
		else
		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

		break;

	case SM_LOGIC_FAILED://about inverter protects
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pow_off=1;
			diesel.cmd_in_off = 1;
			dcdc.ena=0;
			cmd_logic.status.profile = 1;
			vacuum.cmd_out_block=0;
		}

		if(vacuum.on == 1)
		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

		break;

	case SM_ISLA_DENY://about vacuum blocked by the protect
		if (p->E == 1)
		{
			p->counter = 0;
			inv.in.cmd_pow_off=1;
			diesel.cmd_in_off = 1;
			dcdc.ena=0;
			cmd_logic.status.profile = 1;
			vacuum.cmd_out_block=0;
			p->ena = 0;
		}

		if(vacuum.on == 1)
		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

		break;

	default:
		break;
	}    //end switch (p->state)

	p->ena_prev=p->ena;

	}
}

