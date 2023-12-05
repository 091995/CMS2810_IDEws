#ifndef MODEL
#include "dio_func.h"
#include "main.h"
//#include "../DDE/V_RTC_Clock.h"
#endif


extern TRTCClock RTCclock; //NOT GOOD this module is from DDE

void DIO_LOGIC_DIESEL_Init(DIO_LOGIC_DIESEL*p)
{
	p->state=0;
	p->state_prev=-1;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DIO_LOGIC_DIESEL_ms_Calc(DIO_LOGIC_DIESEL*p)
{

	if (p->state!=p->state_prev) p->E=1; else p->E=0;
	p->state_prev=p->state;

//	if (p->cmd_in_on==1) {p->cmd_out_start = 1;}
//	else if (p->cmd_in_off==1) {p->cmd_out_start = 0;}


	switch (p->state)
	{
	case SM_DIESEL_CTRL_INIT:
		if(p->E==1)
		{
			p->counter=0;

		}

		if (p->cmd_out_start==1) p->state = SM_DIESEL_CTRL_GO_RUN;
		else p->state= SM_DIESEL_CTRL_STOP;
	break;

	case SM_DIESEL_CTRL_STOP:
		if(p->E==1)
		{
			p->counter=0;
		}
		p->cmd_out_start=0;
		if (p->cmd_in_on==1) {p->state=SM_DIESEL_CTRL_GO_RUN;}
	break;

	case SM_DIESEL_CTRL_GO_RUN:
		if(p->E==1)
		{
			p->cmd_out_start = 1;
			p->counter=0;
		}


		p->counter++;

		if(diesel.operating==1) p->state=SM_DIESEL_CTRL_OPERATING;
		if (p->counter>30000) p->state=SM_DIESEL_CTRL_STOP;

	break;

	case SM_DIESEL_CTRL_OPERATING:
		if(p->E==1)
		{
			p->counter=0;
			diesel.ON = 1;
		}

		//if diesel is operating then check that under certain level of DCvoltage I_diesel current exist
		//если дизель рабоает но тока нет при нагрузке (т.е. ниже напряжения U_load) ставим сигнал предупреждения
		//TODO 231
		if (inv.in.DCS_Udc<diesel.Udc_load)
		{
			if (diesel.operating&labs(diesel.P_ref-diesel.P_meas)>_IQ(0.2)) inv.alarm_word|=A_DCDC_DIESEL_NO_POWER;

		}

		//TODO 221 верим сигналу operating. но логику нужно доработать. Возможно что сигнал operating есть, но ток не течет
		//(например разрыв в цепи/диоды повреждены)
		//тогда ON будет сформирован неправильно

		if(p->cmd_in_off==1 || diesel.operating==0) { p->state= SM_DIESEL_CTRL_GO_STOP;}

	break;


	case SM_DIESEL_CTRL_GO_STOP:
		if(p->E==1)
		{

			p->counter=0;
			diesel.ON=0;
			p->cmd_out_start = 0;
		}

		p->counter++;
		if(diesel.operating==0) p->state=SM_DIESEL_CTRL_STOP;
		if(p->counter>90000) p->state=SM_DIESEL_CTRL_STOP;

	break;

	default:
	break;

	}

	p->cmd_in_on=0;
	p->cmd_in_off=0;

}
