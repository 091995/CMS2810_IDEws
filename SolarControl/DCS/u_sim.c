
#ifndef MODEL
#include "DSP.h"
#include "dcs_func.h"
#include "../DIO/dio_func.h"
#include "V_IQmath.h"
#endif

#define L_PHASE 0.000175
#define R_PHASE	0.001

static TIClarke iclarke = ICLARKE_DEFAULTS;

void TSim_Init(TSim *p) {

volatile float T = Td/(L_PHASE/R_PHASE);
	sim.T=_IQ(T); //T=Ts/Tfiltra где - Tfiltra постоянная времени фильтра
	sim.Um1_tr=_IQ(1);
	sim.Um1_f=_IQ(1);
	sim.freq = _IQ16(50);
	sim.Udc_ref= _IQ(1);
	sim.dcs_sim_ena = 0;
	sim.dio_sim_ena = 0;

}



void TSim_FastCalc(TSim *p) {
long dU;
static long sim_event_counter=0;

if (sim.dcs_sim_ena) {
	sim.angle+= (long)_IQmpy((sim.freq<<8),_IQ(Td));//*sim.freq;
	sim.angle&=_IQ(1)-1;

	//calc voltage on trafoside. Let set it Um1
	sim.Ua_tr=_IQmpy(sim.Um1_tr,_IQsinPU(sim.angle));
	sim.Ub_tr=_IQmpy(sim.Um1_tr,_IQsinPU(sim.angle-_IQ(1.0/3)));
	sim.Uc_tr=-sim.Ua_tr-sim.Ub_tr;

		sim.Uab_tr	= sim.Ub_tr-sim.Ua_tr;
		sim.Ubc_tr	= sim.Uc_tr-sim.Ub_tr;
		sim.Uca_tr	= sim.Ua_tr-sim.Uc_tr;
		sim.Udc = sim.Udc_ref;
	if ((aux_K7.aux_on)&&(aux_Q26.aux_on)) //if connected to AC power grid
	{
		//depends on pulses if pulses on
		if (pwm.Enabled) {
			//calc voltage on inverter filter side. Let set it the same as inverter, with some assumption
			iclarke.ds=pwm.UalphaRef;
			iclarke.qs=pwm.UbetaRef;
			iclarke.calc(&iclarke);

			sim.Ua_f=iclarke.a;
			sim.Ub_f=iclarke.b;
			sim.Uc_f=iclarke.c;


			dU=sim.Ua_tr-sim.Ua_f;
			sim.Ia_tr = _IQmpy(p->T,(dU-sim.Ia_tr)) + sim.Ia_tr;

			dU=sim.Ub_tr-sim.Ub_f;
			sim.Ib_tr = _IQmpy(p->T,(dU-sim.Ib_tr)) + sim.Ib_tr;

			sim.Ic_tr = -sim.Ia_tr-sim.Ib_tr;

			sim.Ia_inv=sim.Ia_tr;
			sim.Ib_inv=sim.Ib_tr;
			sim.Ic_inv=sim.Ic_tr;
			sim.Idc = sim.Idc_ref;
		}
		else // if pulses off and connected
		{
			sim.Ua_f=sim.Ua_tr;
			sim.Ub_f=sim.Ua_tr;
			sim.Uc_f=sim.Ua_tr;

			sim.Ia_tr =_IQmpy(_IQ(0.05),sim.Ua_tr); //very small current
			sim.Ib_tr =_IQmpy(_IQ(0.05),sim.Ub_tr); //very small current
			sim.Ic_tr =_IQmpy(_IQ(0.05),sim.Uc_tr); //very small current

			sim.Ia_inv=sim.Ia_tr;
			sim.Ib_inv=sim.Ib_tr;
			sim.Ic_inv=sim.Ic_tr;
			sim.Idc = _IQ(0.0);


		}
 	}
	else //if K7 off or Q26 off
	{

		//depends on pulses if pulses on
		if (pwm.Enabled) {
			//calc voltage on inverter filter side. Let set it the same as inverter, with some assumption
			iclarke.ds=pwm.UalphaRef;
			iclarke.qs=pwm.UbetaRef;
			iclarke.calc(&iclarke);

			sim.Ua_f=iclarke.a;
			sim.Ub_f=iclarke.b;
			sim.Uc_f=iclarke.c;

			sim.Ia_inv =_IQmpy(_IQ(0.2),sim.Ua_tr); //very small current on FCB
			sim.Ib_inv =_IQmpy(_IQ(0.2),sim.Ub_tr); //very small current on FCB
			sim.Ic_inv =_IQmpy(_IQ(0.2),sim.Uc_tr); //very small current on FCB

			sim.Ia_tr = 0;
			sim.Ib_tr = 0;
			sim.Ic_tr = 0;
			sim.Idc = _IQ(0.0);

			}
			else // if pulses off and connected
			{
					sim.Ua_f=0;
					sim.Ub_f=0;
					sim.Uc_f=0;

					sim.Ia_tr =0;
					sim.Ib_tr =0;
					sim.Ic_tr =0;

					sim.Ia_inv=sim.Ia_tr;
					sim.Ib_inv=sim.Ib_tr;
					sim.Ic_inv=sim.Ic_tr;
					sim.Idc = _IQ(0.0);
			}

	//hold each sim.event for 20 pwm periods
	if (sim.event!=0) sim_event_counter++;
	if (sim_event_counter>sim.event_timeout) {sim.event=0;sim_event_counter=0;}

	if (sim.event==1) sim.Ia_inv=10*sim.Ia_inv;
	if (sim.event==2) sim.Ia_tr=10*sim.Ia_tr;

	if (sim.event==5) {sim.Ua_tr=sim.Ua_tr>>4;sim.Uab_tr=sim.Uab_tr>>4;}
	if (sim.event==6) {
			sim.Ua_tr=0 ;sim.Ub_tr=0;sim.Uc_tr=0;
			sim.Uab_tr=0 ;sim.Ubc_tr=0;sim.Uca_tr=0;
	}

	if (sim.event==8) sim.Udc=sim.Udc>>1;
	if (sim.event==9) sim.Udc=sim.Udc>>2;

	}

//	adc.Ia_inv=sim.Ia_inv;
//	adc.Ib_inv=sim.Ib_inv;
//	adc.Ic_inv=sim.Ic_inv;
//	adc.Ia_tr=sim.Ia_tr;
//	adc.Ib_tr=sim.Ib_tr;
//	adc.Ic_tr=sim.Ic_tr;
//	adc.Ua_inv=sim.Ua_f;
//	adc.Ub_inv=sim.Ub_f;
//	adc.Uc_inv=sim.Uc_f;
//	adc.Ua_tr=sim.Ua_tr;
//	adc.Ub_tr=sim.Ub_tr;
//	adc.Uc_tr=sim.Uc_tr;
}

if (sim.dio_sim_ena)
	{
		aux_Q4.aux_on=aux_Q4.hold_on;
		aux_Q4.aux_off=aux_Q4.hold_off;

		aux_Q26.aux_on=aux_Q26.hold_on;
		aux_Q26.aux_off=aux_Q26.hold_off;

		aux_K7.aux_on=aux_K7.hold_on;
		aux_K7.aux_off=aux_K7.hold_off;

	}

}

