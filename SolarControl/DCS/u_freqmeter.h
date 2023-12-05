#ifndef U_FREQMETER_H
#define U_FREQMETER_H

//#include "IQmath.h"

#define NIn_uf 150 /* = NInFpz */

typedef struct 
{ 
_iq	out[3];
_iq	in[3];
_iq	a1;
_iq	a2;
_iq	a3;
_iq	b1;
_iq	b2;
_iq	b3; 

_iq	M_fma[NIn_uf];
_iq	Out_fma;
int	P_fma;

_iq	T_start;	/* _iq22 */
_iq	Ua;
_iq	Uc;
int	Fl_Us;
_iq	Ts;			/* _iq30 */
_iq	Ts_out;		/* _iq30 */
_iq	fs_out;
_iq	nd;			/* _iq22 относительное расстояние от последнего перехода критерия uf из положительной области в отрицательную до начала текущего расчетного такта*/
_iq	Nftek;		/* “екущее количество просуммированных периодов критерия fp по которому происходит усреднение частоты*/
int	SumTf;		/* “екущая сумма периодов критерия uf*/
int	IDTf;
int	Nf;			/* количество периодов для усреднения „ј—“ќ“џ*/
_iq	_1_Nf;		/* величина обратная Nf*/
int	flgON1;		/* ‘лаг первого перехода через 0 */
_iq	T_iner;		/* инерционное звено */
_iq	K1_iner;
_iq	K2_iner;
_iq	out_iner;
_iq	in_iner;
int	MTf[NIn_uf];	/* ћассив периодов критерия uf*/
_iq	uf[2];		/* значение критерия uf */

  void (*init)();
  void (*calc)();
} FREQMETER;


#define FREQMETER_DEFAULTS {{0},{0},0,0,0,0,0,0,\
							{0},0,0,\
							0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
							{0},{0},\
							(void (*)(long))FREQMETER_Init,\
							(void (*)(long))FREQMETER_Calc,\
							}
void FREQMETER_Init(FREQMETER*);
void FREQMETER_Calc(FREQMETER*);

#endif
