/*!
    Copyright 2019 	A&D

 \file       V_MPPT.c
 \brief
 \author    A&D
 \version   v 1.0 06/06/2019

 \defgroup  mmpt  (см. TMPPT)

 @{
*/


#ifndef MODEL
#include "DSP.h"
#include "V_MPPT.h"
#include "V_IQmath.h"
#include "main.h"
#endif

void TMPPT_Init(TMPPT *p) {

	mppt.Dinit=_IQ(1);  //Initial value for Vdc_ref
	mppt.D=mppt.Dinit;  //Initial value for Vdc_ref
	mppt.Dmax=_IQ(1.17) ;   //Maximum value for Vdc_ref
	mppt.Dmin=_IQ(500.0/700.0);   //Minimum value for Vdc_ref
	mppt.deltaD=_IQ(4.0/700.0); //Increment value used to increase/decrease Vdc_ref
	mppt.deltaV=_IQ(35.0/700.0);
	mppt.ena=1;
	mppt.delayvar=4;



}

static long dV,dP;
//unsigned short mppt.counter=0;
int twoorone=0;
int flag=0;
int napr=0;
static int _mppt_ena_prev=0;
static int _mppt_ena=0;  //use atomic instruction to transfer from fast_isr to 1ms_isr

void TMPPT_Calc(TMPPT *p) {


	mppt.P=_IQmpy(mppt.V,mppt.I);

	_mppt_ena =  mppt.ena;  //use atomic instruction to transfer from fast_isr to 1ms_isr
	if ((_mppt_ena==1)&&(_mppt_ena_prev==0)) {
		mppt.D=_IQmpy(_IQ(0.9),mppt.V); // Latelly moved rising edge of ena
		mppt.D_prev=mppt.D; //A&D 17.11.2011 - D_prev add initialise for D_prev
	}
	_mppt_ena_prev=_mppt_ena;

	if(_mppt_ena==0)
	{
		mppt.counter=0;
		mppt.counter2=0;
		mppt.Vmax=mppt.V;
		mppt.Vmin=mppt.V;
	}
	else
	{
	mppt.counter2++;

	if(mppt.V>mppt.Vmax)
		mppt.Vmax=mppt.V;
	if(mppt.V<mppt.Vmin)
		mppt.Vmin=mppt.V;


		if (mppt.counter2>2000) //each 2000 cycles set new min max
		{
			mppt.counter2=0;
			if(labs(mppt.Vmax-mppt.Vmin)>mppt.deltaV)
			{
				mppt.D=mppt.D+4*mppt.deltaD;
				mppt.D_prev=mppt.D_prev+4*mppt.deltaD;
			}

			mppt.Vmax=mppt.V;
			mppt.Vmin=mppt.V;
		}

		mppt.counter++;
		if(mppt.counter>(mppt.delayvar*8000))
		{
			mppt.counter=0;

			dV= mppt.V - mppt.V_prev;
			dP= mppt.P - mppt.P_prev;


			if (dP < -_IQ(0.0005)) {
				if (dV < 0) mppt.D=mppt.D_prev+mppt.deltaD;
					else	mppt.D=mppt.D_prev-mppt.deltaD;
				}
			 if (dP > _IQ(0.0005)) {
				if (dV < 0) mppt.D = mppt.D_prev - mppt.deltaD;
				else	mppt.D = mppt.D_prev + mppt.deltaD;
				}



			if (mppt.D > mppt.Dmax) mppt.D = mppt.Dmax;
			else if (mppt.D < mppt.Dmin) mppt.D = mppt.Dmin;

			mppt.D_prev=mppt.D;
			mppt.V_prev=mppt.V;
			mppt.P_prev=mppt.P;
		}

	}

}


/*@}*/

