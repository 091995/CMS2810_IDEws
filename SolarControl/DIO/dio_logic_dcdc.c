#ifndef MODEL
#include "dio_func.h"
#include "main.h"
//#include "../DDE/V_RTC_Clock.h"
#endif


extern TRTCClock RTCclock; //NOT GOOD this module is from DDE

void DIO_LOGIC_DCDC_Init(DIO_LOGIC_DCDC*p)
{

	p->abc.state=SM_ABC_DIS;
	p->abc.state_prev=-1;
	p->state=SM_DCDC_CTRL_INIT;
	p->state_prev=-1;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DIO_LOGIC_DCDC_ms_Calc(DIO_LOGIC_DCDC*p)
{


//-----------------------------DCDC MASTER PART-----------------------------------------


//always if link failed go to protection state turn off DCDC and turn off Q6
	if (p->regs.link==0) p->state = SM_DCDC_CTRL_LINK_FAILED;

//if ext protection, then go directly to protectin state
	if (p->regs.stat_protect_Q_off==1) {p->ena=0;p->state= SM_DCDC_CTRL_LOGIC_FAILED;}
	if (p->regs.stat_protect==1) {p->ena=0;p->state= SM_DCDC_CTRL_LOGIC_FAILED;}
	if (inv.in.cmd_protect_pow_off==1)  {p->ena=0;p->state= SM_DCDC_CTRL_LOGIC_FAILED;}

	if (p->state==SM_DCDC_CTRL_CONNECTED) dcdc.operating=1;
	else dcdc.operating=0;


if (p->state!=p->state_prev) p->E=1; else p->E=0;
p->state_prev=p->state;


//select ENA/DIS from cmd_logic ref. If ref=0 then DIS, else ENA
// i decide not to do this to exclude Q6 othen switching.
// just on the side of DCDC Pref=0 is used to stop pulses and Pref!=0 to run.
// connection of inverter and DCDC should me done by qualified technicians.
// if any protection then Q6 will be off.

switch (p->state)
{
//----------------------------------------------------------------------------------------------
case SM_DCDC_CTRL_INIT:
	if (p->E==1){
		p->status=SM_DCDC_CTRL_INIT;
		p->counter=0;
		p->regs.ctrl_prep2connect=0;
		p->regs.ctrl_start_nstop=0;
		p->regs.ctrl_trip_reset=0;
	}
	p->counter++;
	//wait until can update all regs. for 1 sec
	if (p->counter>1000)
	{
		//if module operation enabled
		//if (p->ena==1)
		//{
		//	if (p->regs.link == 0) p->state =  SM_DCDC_CTRL_LOGIC_FAILED;
		//}
		//else  // ena==0
		//{
			if ((aux_Q6.state == STATUS_Q_ON)||(aux_Q6.state == STATUS_Q_UNDEFINED)) //if Q6 was ON when CPU wake-up but ena==0 then go GO_DISABLE
				p->state = SM_DCS_CTRL_GO_DISABLE;
			else p->state =  SM_DCDC_CTRL_DISABLED;
		//}

	}
break;

//----------------------------------------------------------------------------------------------
case SM_DCS_CTRL_GO_DISABLE:
	if (p->E==1){
		p->status=SM_DCDC_CTRL_DISABLED;
		p->counter=0;
	}
	p->counter++;
	p->regs.ctrl_start_nstop=0;
	p->regs.ctrl_prep2connect=0;
	//wait 1000ms. we did all to turn off current in DCDC. If no link, then it will be stopped by trip NO_LINK
	if (p->counter>1000)
	aux_Q6.cmd_in = CMD_Q_OFF;

	//wait else 2000ms and go DISABLED state
	if (p->counter>2000)
		p->state=SM_DCDC_CTRL_DISABLED;
	break;

//----------------------------------------------------------------------------------------------
case SM_DCDC_CTRL_DISABLED:
	if (p->E==1){
    	p->status=SM_DCDC_CTRL_DISABLED;
    	p->counter=0;
    }

//TODO3 just for experiment to precharge and hold ref voltage
//	if (p->ena==1) {
//		p->regs.ctrl_prep2connect=1;
//		if (p->regs.stat_ready2connect==1)
//			p->regs.ctrl_start_nstop=1;
//		else
//			p->regs.ctrl_start_nstop=0;
//	}
//	else
//	{
//		p->regs.ctrl_prep2connect=0;
//		p->regs.ctrl_start_nstop=0;
//	}



	if (p->ena==1) {
		p->counter++;

		if (p->regs.link==1) //if link with DCDC is ok
		{	//1st - check Udc1 is >300V and go to ready2connect
			//2nd if less 300 - go precharge

			if (p->Udc1>_IQ(250.0/700.0))
			p->state = SM_DCDC_CTRL_WAIT_READY2CONNECT;
			else
			p->state = SM_DCDC_CTRL_PRECHARGE_UDC1;
		}
		//wait 1 seconds to check link and if no link then we fail to get to ena
		if (p->counter>1000) p->state = SM_DCDC_CTRL_LINK_FAILED;

	}
	else p->counter=0;



break;


case SM_DCDC_CTRL_PRECHARGE_UDC1:
	if (p->E==1){ //ENTRY
    	p->status=SM_DCDC_CTRL_DISABLED;
    	p->counter=0;
    	p->DC_precharge_on=1;
    }


	p->counter++;
					//inv_params._1_Udc_nom
	if (p->Udc1>_IQ(250.0/700.0)) p->state=SM_DCDC_CTRL_WAIT_READY2CONNECT;

	//проверка что зардяка началась
	if ((p->counter>2000)&&(p->Udc1<_IQ(50.0/700.0))) p->state = SM_DCDC_CTRL_LOGIC_FAILED;
	//превышено время предзаряда
	if (p->counter>9000) p->state = SM_DCDC_CTRL_LOGIC_FAILED;


	//EXIT
	if(p->state!=p->state_prev)
	{
		p->DC_precharge_on=0;
	}

	break;
//----------------------------------------------------------------------------------------------
case SM_DCDC_CTRL_WAIT_READY2CONNECT:
	if (p->E==1){
    	p->status=SM_DCDC_CTRL_WAIT_READY2CONNECT;
    	p->counter=0;
    	p->regs.ctrl_prep2connect=1;
    }

	p->counter++;


	// TODO2 just for debug DCDC side, then uncomment it
	if (p->regs.stat_ready2connect==1) p->state= SM_DCDC_CTRL_DO_CONNECTION;


	//wait 3 seconds to preachrge, if not, then go LOGIC_FAILED
	if (p->counter>3000) p->state=SM_DCDC_CTRL_LOGIC_FAILED;



break;


//----------------------------------------------------------------------------------------------
case SM_DCDC_CTRL_DO_CONNECTION:
	if (p->E==1){
    	p->status=SM_DCDC_CTRL_DO_CONNECTION;
    	p->counter=0;
    	aux_Q6.cmd_in = CMD_Q_ON;
    }

	p->counter++;
	if (aux_Q6.status==STATUS_Q_ON) p->state = SM_DCDC_CTRL_CONNECTED;
	//if Q6 is not in ON after 1 second< then something wrong - go protection
	if (p->counter>2000) p->state = SM_DCDC_CTRL_LOGIC_FAILED;

break;

//----------------------------------------------------------------------------------------------
case SM_DCDC_CTRL_CONNECTED:
	if (p->E==1){
    	p->status=SM_DCDC_CTRL_CONNECTED;
    	p->counter=0;
    	p->regs.ctrl_start_nstop=1; //start regulation
    }
	if (aux_Q6.status!=STATUS_Q_ON) p->state = SM_DCDC_CTRL_LOGIC_FAILED;


	if (p->ena==0)// || dcdc.regs.stat_no_master == 0)
	{
		p->regs.ctrl_start_nstop=0;
		p->regs.ctrl_prep2connect=0;
		p->state = SM_DCS_CTRL_GO_DISABLE;
	}
//	Hysteresis for P_ref 5% is done inside DCDC slave controller
//	if (labs(p->P_ref)>_IQ(0.05)) p->regs.ctrl_start_nstop=1;
//	else p->regs.ctrl_start_nstop=0;

break;


//----------------------------------------------------------------------------------------------
case SM_DCDC_CTRL_LINK_FAILED:
	if (p->E==1){
		p->status_prev = p->status;
		p->status=SM_DCDC_CTRL_LINK_FAILED;
    	aux_Q6.cmd_in = CMD_Q_OFF;
    	p->regs.ctrl_start_nstop=0;  // release both ctrl to stop DCDC
    	p->regs.ctrl_prep2connect=0; //
    	p->DC_precharge_on=0;
    	p->ena=0;
    }
	if (p->regs.link==1) p->state = SM_DCDC_CTRL_LOGIC_FAILED;
	break;


case SM_DCDC_CTRL_LOGIC_FAILED:
	if (p->E==1){
		p->status_prev = p->status;
    	p->status=SM_DCDC_CTRL_LOGIC_FAILED;
    	aux_Q6.cmd_in = CMD_Q_OFF;
    	p->regs.ctrl_start_nstop=0;  // release both ctrl to stop DCDC
    	p->regs.ctrl_prep2connect=0; //
    	p->DC_precharge_on=0;
    	p->ena=0;
    }


	//only when new rising edge catch enable (like trip_reset command but for logic)
	if ((p->ena==1)&&(p->ena_prev==0)) p->state = SM_DCDC_CTRL_INIT;


	break;

default:break;
}    //end switch (p->state)

p->ena_prev=p->ena;

//scale from REGS values to original
p->I2_meas_A_I12Q4 = p->regs.I2_meas_A_I12Q4;
p->U2_meas_V_I12Q4 =  p->regs.U2_meas_V_I12Q4;

p->P_meas_kW_IQ8 = (p->regs.P_meas_kW<<8);
p->E_charge_persent = p->regs.E_charge_persent; //in persentage 0..100%

//p->regs._nu_Umax1=(p->_nu_Umax1 >>17&0xff); // Umax = 8.24 to IQ1.7 UNSIGNED
//p->regs._nu_Umin1=(p->_nu_Umin1>>17&0xff); // Umin = 8.24 to IQ1.7

p->P_ref_kW_IQ8 = cmd_logic.refs.P_dcdc_ref;
p->regs.Udc1 = (p->Udc1>>17&0xff);  // Udc1 = 8.24 to IQ1.7
p->regs.P_ref_kW_I8=(p->P_ref_kW_IQ8>>8)&0xff; // P_ref in kW

}
