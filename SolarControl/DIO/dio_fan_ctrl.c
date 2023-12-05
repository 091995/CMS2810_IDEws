/*!
    Copyright 2019 	A&D

 \file       dio_fan_ctrl.c
 \brief
 \author    A&D
 \version   v 1.0 08/06/2019

 \defgroup  fan_ctrl  (см. TFAN_DCTRL)

 @{
*/


#ifndef MODEL
#include "V_IQmath.h"
#endif
#ifndef MODEL
#include "dio_fan_ctrl.h"
#endif
#ifndef MODEL
#include "main.h"
#endif


void TFAN_ACTRL_Init(TFAN_ACTRL *p) {
	p->Temp_max_fan=40;
	p->Temp_min_fan=20;
	p->K=10.0/(p->Temp_max_fan-p->Temp_min_fan);

	p->time_1st_run_ms=10000;
	p->state=ST_FAN_ACTRL_INIT;
	p->state_prev=-1;
}

void TFAN_ACTRL_Calc(TFAN_ACTRL *p) {

float V_out; //p->Vout used in fast_isr, but module calc 1ms, used as shadow reg

	if (p->state!=p->state_prev) p->E=1;
	else p->E=0;
	p->state_prev=p->state;

	switch (p->state)
	{
	case ST_FAN_ACTRL_INIT:
		p->state=ST_FAN_ACTRL_1ST_RUN;
		break;
//!-------------------------------------------------------------------------------------------------------
	case ST_FAN_ACTRL_1ST_RUN:
		if (p->E) {
			p->cnt_ms=0;
			p->V_out=10;
		}
			p->cnt_ms++;
			if (p->cnt_ms>p->time_1st_run_ms) p->state=ST_FAN_ACTRL_ACTIVE;
		break;
//!-------------------------------------------------------------------------------------------------------
	case ST_FAN_ACTRL_ACTIVE:
		if (p->E) {
			p->cnt_ms=0;
		}
		p->cnt_ms++;
		//p->K=10.0/(p->Temp_max_fan-p->Temp_min_fan);
		V_out=p->K*(p->T-p->Temp_min_fan);
		if (V_out<0) V_out=0;
		if (V_out>10.0) V_out=10.0;
		p->V_out=V_out;

		break;

//!-------------------------------------------------------------------------------------------------------
	default:break;
	}


}


void TFAN_DCTRL_Init(TFAN_DCTRL *p) {
	p->Temp_hi2lo=55;
	p->Temp_lo2hi=60;
	p->Temp_hi=40;
	p->Temp_lo=35;
	p->time_1st_run_ms=5000;
	p->time_hi2lo_ms=60000;
	p->time_lo2hi_ms = 10000;
	p->state=ST_FAN_DCTRL_INIT;
	p->state_prev=-1;
}

void TFAN_DCTRL_Calc(TFAN_DCTRL *p) {

	//while temperature
	if (p->T>p->T_max) p->ready=0;
	else p->ready=1;


	if (p->state!=p->state_prev) p->E=1;
	else p->E=0;
	p->state_prev=p->state;

	switch (p->state)
	{
	case ST_FAN_DCTRL_INIT:
		p->set_hi=0;
		p->set_lo=0;
		p->state=ST_FAN_DCTRL_HI_1ST_RUN;
		break;
//!-------------------------------------------------------------------------------------------------------
	case ST_FAN_DCTRL_HI_1ST_RUN:
		if (p->E) {
			p->set_lo=0;
			p->set_hi=1;
			p->cnt_ms=0;
		}
				p->cnt_ms++;
				if (p->cnt_ms>p->time_1st_run_ms)
					if (p->T<p->Temp_lo) p->state = ST_FAN_DCTRL_OFF;
					else p->state=ST_FAN_DCTRL_LO_1ST_RUN;
		break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_DCTRL_LO_1ST_RUN:
		if (p->E) {
					p->set_lo=1;
					p->set_hi=0;
					p->cnt_ms=0;
				}
				p->cnt_ms++;
				if (p->cnt_ms>p->time_1st_run_ms)

					if (p->T<p->Temp_lo) p->state=ST_FAN_DCTRL_OFF;
					else if (p->T>p->Temp_lo2hi) p->state=ST_FAN_DCTRL_HI;
					else p->state=ST_FAN_DCTRL_LO;


		break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_DCTRL_LO:
		if (p->E) {
					p->set_lo=1;
					p->set_hi=0;
					p->cnt_ms=0;
				}
				p->cnt_ms++;
				if (p->cnt_ms>p->time_lo2hi_ms ) {
					p->cnt_ms=p->time_lo2hi_ms;
					if (p->T>p->Temp_lo2hi) p->state=ST_FAN_DCTRL_HI;
					if (p->T<p->Temp_lo) p->state=ST_FAN_DCTRL_OFF;

					}
		break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_DCTRL_HI:
		if (p->E) {
					p->set_lo=0;
					p->set_hi=1;
					p->cnt_ms=0;
				}
				p->cnt_ms++;
				if (p->cnt_ms>p->time_hi2lo_ms ) {
					p->cnt_ms=p->time_hi2lo_ms;
					if (p->T<p->Temp_hi2lo) p->state=ST_FAN_DCTRL_LO;
					if (p->T<p->Temp_lo) p->state=ST_FAN_DCTRL_OFF;
					}
		break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_DCTRL_OFF:

		if (p->E) {
					p->set_lo=0;
					p->set_hi=0;
				}

				if (p->T>p->Temp_hi) p->state=ST_FAN_DCTRL_HI;

		break;

	default:break;
	}

}


void TFAN_SPEC_RELAY_OUTPUT_Init(TFAN_SPEC_RELAY_OUTPUT*p) {
p->time_pow_ms=1000;
p->state=ST_FAN_SPEC_INIT;
p->state_prev=-1;
}


void TFAN_SPEC_RELAY_OUTPUT_Calc(TFAN_SPEC_RELAY_OUTPUT*p) {

	if (p->state!=p->state_prev) p->E=1;
	else p->E=0;
	p->state_prev=p->state;


	switch (p->state)
	{
	case ST_FAN_SPEC_INIT:
		p->cmd_hi=0;
		p->cmd_lo=0;
		p->cmd_pow=0;
		p->state=ST_FAN_SPEC_OFF;
		break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_SPEC_OFF:

		if (p->E) {
					p->cmd_lo=0;
					p->cmd_hi=0;
					p->cmd_pow=0;
				}
		if ((p->lo==1)&&(p->hi==1)) {p->err_counter++; break;}
		if (p->lo==1) p->state = ST_FAN_SPEC_GO_LO;
		if (p->hi==1) p->state = ST_FAN_SPEC_GO_HI;

		break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_SPEC_GO_LO:
		if (p->E) {
					p->cmd_lo=1;
					p->cmd_hi=0;
					p->cmd_pow=0;
					p->cnt_ms=0;
				}
		p->cnt_ms++;
		if (p->cnt_ms>p->time_pow_ms )
			p->state = ST_FAN_SPEC_LO;
			break;
//!-------------------------------------------------------------------------------------------------------

	case ST_FAN_SPEC_LO:
		if (p->E) {
		p->cmd_lo=1;
		p->cmd_hi=0;
		p->cmd_pow=1;
		p->cnt_ms=0;
		}

		p->cnt_ms++;//check if current is OK after 50ms
		if (p->cnt_ms>200) {
			p->cnt_ms=200;
			 p->fail=p->d_fdb;
		}


		if (p->lo==0) p->state = ST_FAN_SPEC_GO_OFF;

		break;

		//!-------------------------------------------------------------------------------------------------------
	case ST_FAN_SPEC_GO_OFF:
		if (p->E) {
					p->cmd_pow=0;
					p->cnt_ms=0;
				}
		p->cnt_ms++;
		if (p->cnt_ms>p->time_pow_ms )
			p->state = ST_FAN_SPEC_OFF;

		break;
				//!-------------------------------------------------------------------------------------------------------
	case ST_FAN_SPEC_GO_HI:
		if (p->E) {
					p->cmd_lo=0;
					p->cmd_hi=1;
					p->cmd_pow=0;
					p->cnt_ms=0;
				}
		p->cnt_ms++;
		if (p->cnt_ms>p->time_pow_ms )
			p->state = ST_FAN_SPEC_HI;
		break;
//!-------------------------------------------------------------------------------------------------------
	case ST_FAN_SPEC_HI:
		if (p->E) {
		p->cmd_lo=0;
		p->cmd_hi=1;
		p->cmd_pow=1;
		p->cnt_ms=0;
		}

		p->cnt_ms++; //chech if current is OK after 50ms
		if (p->cnt_ms>200) {
			p->cnt_ms=200;
			 p->fail=p->d_fdb;
		}


		if (p->hi==0) p->state = ST_FAN_SPEC_GO_OFF;
		break;

//!-------------------------------------------------------------------------------------------------------
	default:break;
	}




}



