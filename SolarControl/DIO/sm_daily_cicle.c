#ifndef MODEL
#include "dio_func.h"
#include "main.h"
#include "sm_daily_cicle.h"
#endif


//give descriptions according real state
#define SM_DAILY_CICLE_INIT				99
#define SM_DAILY_CICLE_OFF 					1
//#define SM_LOGIC_FAILED				100


void SM_DAILY_CICLE_Init(SM_DAILY_CICLE*p)
{
	p->state=SM_DAILY_CICLE_INIT;
	p->state_prev=-1;
	p->week = 0b00011111;

}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SM_DAILY_CICLE_ms_Calc(SM_DAILY_CICLE*p)
{

	if(p->week>>(RTCclock.DOW-1) & 0x1)
	{
		sm_grid_evng_batt_diesel.autostart=1;
		sm_grid_night_batt_charge.autostart=1;
	}
	else
	{
		sm_grid_evng_batt_diesel.autostart=0;
		sm_grid_night_batt_charge.autostart=0;
	}


	if(sm_grid_evng_batt_diesel.autostart==1)
	if(RTCclock.hour==sm_grid_evng_batt_diesel.start_hour&&RTCclock.minute==sm_grid_evng_batt_diesel.start_minute&&RTCclock.second<3)
		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_EVNG_BATT_DIESEL;

	///ADDED 21.11.22 turn off dcdc before 1hr evng_mode
	if(sm_grid_evng_batt_diesel.autostart==1)
		if(RTCclock.hour==sm_grid_evng_batt_diesel.start_hour-1&&RTCclock.minute==sm_grid_evng_batt_diesel.start_minute&&RTCclock.second<3)
			dcdc.ena=0;


//	if(sm_grid_night_batt_charge.autostart==1)
//	if(RTCclock.hour==sm_grid_night_batt_charge.start_hour&&RTCclock.minute==sm_grid_night_batt_charge.start_minute&&RTCclock.second<3)
//		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_NIGHT_BATT_CHARGE;

//	if(RTCclock.hour==sm_grid_night_batt_charge.night_to_day_hour&&RTCclock.minute==sm_grid_night_batt_charge.night_to_day_minute&&RTCclock.second<3)
//		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

	//if Um1 drops lower U1_min protection and autostart is ena, but only after AR tries go to ISLA
	if(inv.in.DCS_Urms < dcs_prot.U1_min && sm_isla_batt_diesel.autostart == 1 && apl_protect.AR1.state == AR_STATE_FAIL)
		sc_profile.in.cmd_remote_set_profile = SM_PROFILE_ISLA_BATT_DIESEL;

	//if autostart is ena go to ISLA by time
	if(sm_isla_batt_diesel.autostart==1)
	if(RTCclock.hour==sm_isla_batt_diesel.start_hour&&RTCclock.minute==sm_isla_batt_diesel.start_minute&&RTCclock.second<3)
	{
		inv.in.cmd_pow_off = 1;
		sc_profile.in.cmd_remote_set_profile=SM_PROFILE_ISLA_BATT_DIESEL;
	}


	// - THIS ABC PART was moved to scenario profile - this is scenario
	////auto start/stop from RTC
	//if (p->abc.ena==0) p->abc.state=SM_ABC_DIS;
	//if (p->abc.state!=p->abc.state_prev) p->abc.E=1; else p->abc.E=0;
	//p->abc.state_prev=p->abc.state;
	//
	//switch (p->abc.state) {
	//case SM_ABC_DIS:
	//	if(p->abc.E==1) {
	//		p->abc.cmd_on=0;
	//		p->abc.P_ref=0;
	//	}
	//	if (p->abc.ena==1) p->abc.state=SM_ABC_WAIT_H_OR_CONDITIONS;
	//	break;
	//
	//case SM_ABC_WAIT_H_OR_CONDITIONS:
	//	if (p->abc.E==1){
	//		//p->abc.cmd_on=0;
	//		p->abc.P_ref=0;
	//		cmd_logic.remote_refs.P_BMS_ref=p->abc.P_ref;
	//	}
	//
	////PROVER CHTO NE VKLUCHILI V RUCHNUI
	//	if ((dcdc.E_charge_persent>90)&&(cmd_logic.remote_refs.P_BMS_ref>0))
	//		cmd_logic.remote_refs.P_BMS_ref=0;
	//	if ((dcdc.E_charge_persent<20)&&(cmd_logic.remote_refs.P_BMS_ref<0))
	//		cmd_logic.remote_refs.P_BMS_ref=0;
	//
	//
	//	//only if DCDC is connected and inverter operate normaly
	//	if (dcdc.status==SM_DCDC_CTRL_CONNECTED) {
	//
	//		if (inv.state==SM_DIO_LOGIC_INV_OPERATION) {
	//			// check time, charge and inverter power more 3%
	//			if ((RTCclock.hour>=p->abc.time_H_charge)&&(RTCclock.hour<p->abc.time_H_discharge)&&\
	//					(dcdc.E_charge_persent<90)&&(cur_par.Pdc > _IQ(0.03)))
	//			p->abc.state=SM_ABC_CHARGE;
	//
	//			if ((RTCclock.hour>=p->abc.time_H_discharge)&&(dcdc.E_charge_persent>25))
	//				p->abc.state=SM_ABC_DISCHARGE;
	//		}
	//
	//
	//			//during NIGHT mode (aka WAIT DC) just discharge possible
	//		if (inv.state==SM_DIO_LOGIC_INV_NIGHT_MODE) {
	//			if ((RTCclock.hour>=p->abc.time_H_discharge)&&(dcdc.E_charge_persent>25)) {
	//					p->abc.state=SM_ABC_DISCHARGE;
	//				}
	//			}
	//	}
	//	else //if DCDC not connected
	//	{
	//		//DO NOTHING and wait untill connected
	//	}
	//
	//	break;
	//
	//case SM_ABC_CHARGE:
	//	if (p->abc.E==1){
	//		p->abc.charge_counter=0;
	//		//p->abc.cmd_on=1;
	//		p->abc.P_ref=p->abc.charge_P;
	//		cmd_logic.remote_refs.P_BMS_ref=p->abc.P_ref;
	//		}
	//
	//	p->abc.charge_counter++;
	//	//check charged more90% to make hysteresis, inverter power more than 1,5%
	//	if ((dcdc.E_charge_persent>90)||(cur_par.Pdc<_IQ(0.015)))
	//		p->abc.state = SM_ABC_WAIT_H_OR_CONDITIONS;
	//
	//	if (RTCclock.hour>=p->abc.time_H_discharge)
	//					p->abc.state=SM_ABC_WAIT_H_OR_CONDITIONS;
	//	break;
	//
	//case SM_ABC_DISCHARGE:
	//	if (p->abc.E==1){
	//		p->abc.discharge_counter=0;
	//		//p->abc.cmd_on=1;
	//		p->abc.P_ref=p->abc.discharge_P;
	//		cmd_logic.remote_refs.P_BMS_ref=p->abc.P_ref;
	//		}
	//	p->abc.discharge_counter++;
	//	//discharged  less then 20% to make hysteresis
	//	if (dcdc.E_charge_persent<20)
	//		p->abc.state = SM_ABC_WAIT_H_OR_CONDITIONS;
	//
	//
	//	if (RTCclock.hour<p->abc.time_H_discharge)
	//					p->abc.state=SM_ABC_WAIT_H_OR_CONDITIONS;
	//	break;
	//default:break;
	//}

	//if ((p->abc.cmd_on==1)&&(p->abc.cmd_on_prev==0)) p->ena=1;
	//if ((p->abc.cmd_on==0)&&(p->abc.cmd_on_prev==1)) p->ena=0;
	//p->abc.cmd_on_prev=p->abc.cmd_on;

//if (p->state!=p->state_prev) p->E=1; else p->E=0;
//p->state_prev=p->state;
//
//switch (p->state) {
//case SM_LOGIC_INIT:
//	//if (p->ena==1)
//		p->state=SM_LOGIC_MANUAL;
//	break;
//
//case SM_LOGIC_MANUAL:
//	if(p->E==1) {
//		p->counter=0;
//	}
//
//
//	break;
//
//
//
//case SM_PROFILE_LOGIC_FAILED:
//default:
//	//reset by ena=0
//	break;
//}    //end switch (p->state)
//
//p->ena_prev=p->ena;




}
