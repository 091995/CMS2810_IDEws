
#ifndef MODEL
#include "V_IQmath.h"
#include "dcs_func.h"
#endif

void iclarke_calc(TIClarke *p) {
	p->a = p->ds;
	p->b = ((_IQmpy(_IQ(_sqrt_3),p->qs)-p->ds)>>1);
	p->c=-p->a-p->b;
}

