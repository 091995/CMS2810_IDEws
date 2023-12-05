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
_iq	nd;			/* _iq22 ������������� ���������� �� ���������� �������� �������� uf �� ������������� ������� � ������������� �� ������ �������� ���������� �����*/
_iq	Nftek;		/* ������� ���������� ���������������� �������� �������� fp �� �������� ���������� ���������� �������*/
int	SumTf;		/* ������� ����� �������� �������� uf*/
int	IDTf;
int	Nf;			/* ���������� �������� ��� ���������� �������*/
_iq	_1_Nf;		/* �������� �������� Nf*/
int	flgON1;		/* ���� ������� �������� ����� 0 */
_iq	T_iner;		/* ����������� ����� */
_iq	K1_iner;
_iq	K2_iner;
_iq	out_iner;
_iq	in_iner;
int	MTf[NIn_uf];	/* ������ �������� �������� uf*/
_iq	uf[2];		/* �������� �������� uf */

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
