#ifndef MODEL
#include "dio_func.h"
#include "main.h"
//#include "../DDE/V_RTC_Clock.h"
#endif


extern TRTCClock RTCclock; //NOT GOOD this module is from DDE

void DIO_LOGIC_VACUUM_Init(DIO_LOGIC_VACUUM*p)
{
	p->state=0;
	p->state_prev=-1;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DIO_LOGIC_VACUUM_ms_Calc(DIO_LOGIC_VACUUM*p)
{

	if (p->state!=p->state_prev) p->E=1; else p->E=0;
	p->state_prev=p->state;

	if ((p->off == p->on)||(p->blocked==1)) p->state = SM_VACUUM_CTRL_FAILED;

	if(p->state == SM_VACUUM_CTRL_FAILED) p->fail=1;
	else p->fail=0;

	switch (p->state)
	{
	case SM_VACUUM_CTRL_INIT:
		if(p->E==1)
		{
			p->cmd_out_on=0;
			p->cmd_out_off=0;
			p->counter=0;

		}
		if (p->off == 1) p->state = SM_VACUUM_CTRL_OFF;
		if (p->on == 1) p->state = SM_VACUUM_CTRL_ON;


	break;

	case SM_VACUUM_CTRL_OFF:
		if(p->E==1)
		{
			p->counter=0;
		}

		if(p->on == 1) p->state=SM_VACUUM_CTRL_FAILED;
		if (p->cmd_in_on==1) p->state=SM_VACUUM_CTRL_GO_ON;

	break;

	case SM_VACUUM_CTRL_GO_ON:
		if(p->E==1)
		{
			p->counter=0;
			p->cmd_out_on=1;
			p->cmd_out_off=0;
		}
		p->counter++;
		if (p->on==1) p->state=SM_VACUUM_CTRL_ON;
		if(p->counter>10000)
		{
			p->counter=10000;
			p->state=SM_VACUUM_CTRL_FAILED;
		}


	break;

	case SM_VACUUM_CTRL_ON:
		if(p->E==1)
		{
			p->counter=0;
		}

		if(p->off == 1) p->state=SM_VACUUM_CTRL_FAILED;
		if (p->cmd_in_off==1) p->state=SM_VACUUM_CTRL_GO_OFF;

	break;

	case SM_VACUUM_CTRL_GO_OFF:
		if(p->E==1)
		{
			p->counter=0;
			p->cmd_out_off=1;
			p->cmd_out_on=0;
		}
		p->counter++;
		if (p->off==1) p->state=SM_VACUUM_CTRL_OFF;
		if(p->counter>10000)
		{
			p->counter=10000;
			p->state=SM_VACUUM_CTRL_FAILED;
		}


	break;

	case SM_VACUUM_CTRL_FAILED:
		if(p->E==1)
		{
			p->cmd_out_on=0;
			p->cmd_out_off=0;
			p->counter=0;
		}
		p->counter++;
		if(p->counter>1000)
		{
			p->counter=1000;
			if (p->off == 1) p->state = SM_VACUUM_CTRL_OFF;
			if (p->on == 1) p->state = SM_VACUUM_CTRL_ON;
		}

	break;

	default:
	break;

	}

	p->cmd_in_on=0;
	p->cmd_in_off=0;
	p->cmd_in_block=0;

}
