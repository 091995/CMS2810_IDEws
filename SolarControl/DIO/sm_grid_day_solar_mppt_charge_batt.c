#ifndef MODEL
#include "dio_func.h"
#include "main.h"

#endif


//give descriptions according real state
#define SM_LOGIC_INIT				99
#define SM_CHECK_OPERATION 			0
#define SM_GO_LOAD_BATT				1
#define SM_CHARGE_BATT				2

//#define SM_LOGIC_FAILED	100


void SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_Init(SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT*p)
{
	p->state=SM_LOGIC_INIT;
	p->state_prev=-1;
	inv.params.Udc_day=_IQ(600.0/700);
	inv.params.Udc_level_go_on=_IQ(670.0/700);
	cmd_logic.refs.P_ref=220<<16;
	dcdc.Idc2_ref = p->set.dcdc_I_charge;
	cmd_logic.remote_refs.P_dcdc_ref = p->set.dcdc_P_charge;
	cmd_logic.status.profile = 1;
	dcdc.discharge_type = 1;
}



static int cntr=0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_ms_Calc(SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT*p)
{

//если сработала защита на отключение инвертора идем в fail
if(inv.in.cmd_protect_pow_off==1)
	p->state = SM_PROFILE_LOGIC_FAILED;

if (p->state!=p->state_prev) p->E=1; else p->E=0;
p->state_prev=p->state;

switch (p->state) {
case SM_LOGIC_INIT:
	if(p->E==1) {
	p->dcdc_attempts=0;
	p->counter=0;
	dcs_ctrl.ctrl_mode_synced_P_gen=0;
	diesel.cmd_in_off=1;
	}


	p->state=SM_CHECK_OPERATION;
	break;

case SM_CHECK_OPERATION:
	if(p->E==1) {
		if (inv.state!=SM_DIO_LOGIC_INV_OPERATION) inv.in.cmd_pow_on=1;
		p->counter=0;
	}

	if(dcdc.operating==1)
		{
			if(dcdc.charge_state != 9)
			{
				cntr=0;
				if(adc.Udc<_IQ(480.0/700))
					{
						cmd_logic.remote_refs.P_dcdc_ref = 0;
						dcdc.Idc2_ref = 0;
					}
					else
					{
						dcdc.Idc2_ref = p->set.dcdc_I_charge;

						if(adc.Udc>=_IQ(480.0/700) && adc.Udc<_IQ(490.0/700))
							cmd_logic.remote_refs.P_dcdc_ref = _IQmpy(_IQ(0.2),p->set.dcdc_P_charge);
						if(adc.Udc>=_IQ(490.0/700) && adc.Udc<_IQ(500.0/700))
							cmd_logic.remote_refs.P_dcdc_ref = _IQmpy(_IQ(0.4),p->set.dcdc_P_charge);
						if(adc.Udc>=_IQ(500.0/700))
							cmd_logic.remote_refs.P_dcdc_ref = p->set.dcdc_P_charge;

					}

				if(adc.Udc<_IQ(470.0/700))
				{
					if(inv.in.DCS_Urms > inv.params.Urms_level_go_on
									&& dcdc.regs.stat_protect == 0
									&& dcdc.regs.stat_protect_Q_off == 0)
					{
						sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_NIGHT_BATT_CHARGE;
						break;
					}
					else dcdc.ena = 0;

				}
			}
			else
			{
				//посчитаем счетчик чтобы прошли процессы
				cntr++;
				if(cntr>5000)
				{
					cntr=0;
					dcdc.ena = 0;
				}

			}

		}
	else
	{
		if(dcdc.U2_meas_V_I12Q4<dcdc.U2_min && dcdc.regs.link == 1)
		{

			if(adc.Udc<_IQ(470.0/700))
			{
				if(inv.in.DCS_Urms > inv.params.Urms_level_go_on
						&& dcdc.regs.stat_protect == 0
						&& dcdc.regs.stat_protect_Q_off == 0)
				{
					sc_profile.in.cmd_remote_set_profile=SM_PROFILE_GRID_NIGHT_BATT_CHARGE;
					break;
				}

			}
			else
			{
				p->counter++;
				if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
					p->counter=1000;
					if ((dcdc.operating==0)&&(p->dcdc_attempts<3)) {p->state = SM_GO_LOAD_BATT; break;}
				}
			}

		}
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
				p->state = SM_CHECK_OPERATION;
			}
			else
			{
				p->dcdc_attempts++;
				p->state= SM_CHECK_OPERATION;
			}

		}

		break;

case SM_PROFILE_LOGIC_FAILED:
	if(p->E==1) {
			p->counter=0;
			dcdc.ena=0;
		}
	if ((inv.in.cmd_protect_pow_off==0)&&(inv.in.cmd_protect_pwm_off==0))
		p->state=SM_CHECK_OPERATION;
	break;
default:
	break;
}
p->ena_prev=p->ena;




}
