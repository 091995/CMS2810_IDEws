#ifndef MODEL
#include "DSP.h"
#include "mean_filter.h"
#include "V_IQmath.h"
#endif


void TMeanFilter_Calc(TMeanFilter *p) {

//	MOut[ii]	= MOut[ii]  + Inp[ii]  - MInt[ii][buff_pointer];
//	MInt[ii][buff_pointer]	= Inp[ii];
//
	p->integral = p->integral +p->input -p->buff[p->pos];
	p->buff[p->pos]=p->input;
	p->pos++;
	p->pos&=0x1f;//
	p->output=p->integral>>5;

}



