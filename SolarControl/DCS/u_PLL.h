#ifndef U_PLL_H
#define U_PLL_H

//#ifdef TMDS_Z5
//#include "IQmath.h"
//#else
//#include "IQmathLib.h"
//#endif

#define Kwt_fi	50.0
#define Kt_f	50.0
#define f_bas	50.0
#define Kf_w	1.0
#define Kus_udc	1.0

#define SizeM   220

typedef struct
{

_iq Top_lim_osc;
_iq Bot_lim_osc;
_iq _1_T_iner_um2;
_iq Kp_Lim_um2;

_iq Ua;
_iq Ub;
_iq Uc;
_iq Udc;
_iq Ua220;
_iq Ub220;
_iq Uc220;
_iq fs;
_iq Ts;
_iq Il_Alfa;
_iq Il_Beta;

_iq Ua_conv;
_iq Ub_conv;
_iq Uc_conv;
_iq Ua220_conv;
_iq Ub220_conv;
_iq Uc220_conv;

  // ���������� ���������
_iq w_e;
_iq wt_e;
_iq Ea_sin;
_iq Eb_sin;
_iq Ec_sin;
_iq Ea_cos;
_iq Eb_cos;
_iq Ec_cos;
_iq Ea_sin1;
_iq Eb_sin1;
_iq Ec_sin1;
_iq Ea_cos1;
_iq Eb_cos1;
_iq Ec_cos1;
_iq	Il_d;
_iq Il_q;

_iq Ua_meas;
_iq Ub_meas;
_iq Uc_meas;

_iq Tmp0;
_iq Tmp1;

_iq D_cord;      /* D-�������y���y ����y����y ���� ��y �� */
_iq Q_cord;      /* Q-�������y���y ����y����y ���� ��y ��*/
_iq D_cord2;     /* D-�������y���y ����y����y ���� ��y �� (����� �������)*/
_iq Q_cord2;     /* Q-�������y���y ����y����y ���� ��y �� (����� �������)*/
_iq D220_cord;   /* D-�������y���y ����y����y ���� 220�� ��y �� */
_iq Q220_cord;   /* Q-�������y���y ����y����y ���� 220�� ��y ��*/

 // ������
_iq K_Tf;           /*����������� �������� ������ ���������y ������������ 0.02� */
_iq K_ff;
int	Const_Nf;       /*����� ����� ������, �������������y � ������� ���������y(��� Tp=0.02c) */
int	P_wr;           /*��������� ������� y����� ������ � ������� ���������� */
// _iq   P_Nf;           /*��������� ������� ���������� �� Tf ����� (��� Tp �� ������ 0.02c)*/
// _iq   NTf;            /*����� ����� ������, �������������y � ������� ���������y(��� Tp �� ������ 0.02c) */
// _iq Delta_t_Td;     /*������������� �������� ������_t �� ������� Td */
// _iq   Delta_NTf;      /*������� ����� NTf � Const_Nf */
// _iq   k;
 // 1
_iq IntTf_inp1;       /*�������� �� Tf (��� Tp=0.02c) */
_iq MInt1[SizeM];  /*������ �������� ���������� �� ������ ����������� ���� */
 // 2
_iq IntTf_inp2;     
_iq MInt2[SizeM];
 // 3
_iq IntTf_inp3;     
_iq MInt3[SizeM];
 // 4
_iq IntTf_inp4;     
_iq MInt4[SizeM];
 // 5
_iq IntTf_inp5;     
_iq MInt5[SizeM];
 // 6
_iq IntTf_inp6;     
_iq MInt6[SizeM];
 // 6
_iq IntTf_inp7;     
_iq MInt7[SizeM];

// ��������� ����
_iq alpha;
_iq fi;          /* ���� �� ����y����y ���� ������������ ����y����y ����������� ����������*/
_iq Um1;         /* ��������� �� ����y����y ����*/
_iq Um220;       /* ��������� �� ����y����y ���� 220��*/
_iq betta;       /* ���� �� ����y����y ���� ������������ �� ����y����y ����*/
_iq Um2;         /* ��������� �� ����y����y ����*/

_iq Us_d;
_iq Us_q;

int	Fl_Us;

_iq Ucalc_a;
_iq Ucalc_b;
_iq Ucalc_c;
_iq  Am_Usa;
_iq  Am_Usb;
_iq  Am_Usc;

_iq	Fl_sc;
_iq	Cnt_sc;
_iq	Fl_sc_ext;
_iq K_um2_pow;

_iq	T_iner;
_iq	K1;
_iq	K2;
_iq	Iner_Um2;

void (*init)();
void (*calc)();
} PLL;

// ����� ����������� �������y �� ��������� ��y ���
#define PLL_DEFAULTS {0,0,0,0,0,0,0,0,0,0,\
					  0,0,0,0,0,0,0,0,0,0,\
					  0,0,0,0,0,0,0,0,0,0,\
					  0,0,0,0,0,0,0,0,0,0,\
					  0,0,0,0,0,0,0,0,0,0,\
					  0,0,\
                      0,{0},\
                      0,{0},\
                      0,{0},\
                      0,{0},\
                      0,{0},\
                      0,{0},\
                      0,{0},\
                      0,0,0,0,0,0,0,0,0,\
					  0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
                      (void (*)())PLL_Init,\
                      (void (*)())PLL_Calc,\
                     }

// ����� ���y��y�� ��������� ������� �����y
void PLL_Init(PLL*);
void PLL_Calc(PLL*);
#endif
