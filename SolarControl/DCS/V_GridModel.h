/*
 \file      V_GridModel.h
 \brief     ������ ����
 \author    A&D
 \version   v 1.0 13/03/2019

 \defgroup  V_GridModel.h

 @{
*/


#ifndef V_GRID_MODEL_H
#define V_GRID_MODEL_H

#ifndef MODEL
#include "DSP.h"
#include "V_IQmath.h"
#endif

// faults
#define MODEL_WRONG_PARAMETERS 1
#define MODEL_MAX_CURRENT_FAULT 2
#define MODEL_MAX_SPEED_FAULT 3


#define MODEL_PI 3.1415926f
#define _1_DIV_2PI 0.15915494f

//��������� � ����������� ��� � ���������������
struct Sgrid
{
	int cmpr0, cmpr1, cmpr2, cmpr3; 							//!< ������� ��������� ���
	int tpr;													//!< ������ ���
	float inv_tpr; 												//!< 1/������ ���
	int dt;														//!< �������� �������� ������� � ������
	int dta, dtb, dtc, dtf;										//!< ������� �������� ������� �� ���������� ���
	float udc;													//!< ���������� ���
	float fia, fib, fic, fiav;									//!< ���������� ��� � ������� �����
	float ua, ub, uc;											//!< ������ ����������
	float isa, isb, isc, isd, isq;								//!< ������ ���� � ���� �����, �����
	float usa, usb, usd, usq, urd, urq;							//!< ���������� � ������������� ����
	float ird, irq, ira, irb;									//!< ���� � ������������� ����
	float omega,omega_rpm,torque;								//!< �������� (������� ��������), ������
	float torque_a, torque_b, torque_c;							//!< ������ �� ������ ���� (SRD)
	float j, inv_j;												//!< ������ ������� � �������� ��������
	float MechLoss;												//!< ������ �������
	float pp;													//!< ����� ��� �������
	float inv_pp;												//!<  1/pp
	float tetaR;												//!< ���� ��������� ������, �������������
	float tetaRM;												//!< ���� ��������� ������, ������������
	float cosTetaR, sinTetaR;									//!< cos � sin ���� ��������� ������
	float lm, lr, ls, lsd, lsq;									//!< ������������� - ��������, ������, �������
	float lmin, lmax, dls;										//!< ����������� ������������� (���-���), ������������ ������������� (���-���), ��������� ��������� �������������
	float inv_lmin;												//!<  1/lmin
	float l;													//!< ������� �������������
	float lp;													//!< ������������� � ����������� �������� ���������
	float ip, im;												//!< ���� � ����������� �������� ���������
	float wp, wm;												//!< ��������� ������� ������ ������� � ����������� �������� ���������
	float isat;													//!< ��� ���������
	float rr, rs;												//!< ������������� ����� � �������
	float ks, kr, km;											//!< ������������ ��������������
	float psa, psb, psc, psd, psq, prd, prq, pra, prb;			//!< ��������������� ������� � ������ � ������������� ���� ��� ������
	float ppsa, ppsb, ppsd, ppsq, pprd, pprq, ppra, pprb;		//!< ���������� ��������������� � ������������� ����
	float dpsa, dpsb, dpsd, dpsq, dprd, dprq;					//!< ����������� ��������������� � ������������� ����
	int type;													//!< ��� ���������
	float t, t2;												//!< ������ �������������, �������� ������� �������������
	float speedK;												//!< ����������� ������� ��������
	float iSenseK, ifSenseK, udSenseK, iSenseR, iSenseN;		//!< ����������� ������� ����, ������������� �������������� ��������� ��, ���������� ������ ������� ����� ��
	float RatedPower;											//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	float RatedSpeed;											//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	float RatedCurrent;											//!< ����������� ���
	float RatedFluxCurrent;										//!< ����������� ��� �����������
	int  iADCk, ifADCk;
	float QEPResolution;										//!< ����� ����� ���
	float m;													//!< ��������������� ������ ���������� ������
	float i_a, i_f, u_a, u_f, u_an;
	float r_a, r_f, r_ad, l_a, l_f;
	float _1_l_a, _1_l_f;
	float _1_lsd, _1_lsq;
	float dia, dif, dpa, dpf, pia, pif;
	float l_m,kf;												//!< ����������� ���� ��, ����� ��
	int dcm_pm;													//!< ����, ��� ��� � ��.
	int syncm_pm;												//!< ����, ��� �� � ��.
	float isPhaseA,isPhaseB,isPhaseC,isPhaseD;							//!< ��� ���� A,B,C
	float isPhaseA_prev,isPhaseB_prev,isPhaseC_prev;			//!< ��� ���� A,B,C ���������� ��������
	int CurrentInvertedFlag;									//!< ���� � ���, ��� ����� ���������� ��������� ���� ��� ���� ��� ������� ���� ����
	float cos30;												//!< cos 30 ��������
	float pisa,dprb,disa;										//!< ��������� ���� ������� �����, ���������� ��������������� ������ �� ��� ����, ���� ������� �� ��� �����
	float ThetaMax, PsiMax, IMax;								//!< ������������ ����, ����� � ��� SRM (��� ������������)
	float ThetaStep, PsiStep, IStep;							//!< ��� �� ����, ������ � ���� SRM (��� ������������)
	float ThetaStep_inv, PsiStep_inv, IStep_inv;				//!< �������� �������� ���� �� ����, ������ � ���� SRM (��� ������������)
	float power;												//!< �������� �� ����
	long iAtemp, iBtemp, iCtemp, iDtemp, Udc_temp, adcSpeedtemp;//!<��������� ���������� ��� ������� ������
	float hallSensorOmegaPrev; 									//!< ��� �������� ��������� ������� �������� � ������� �����
};
typedef volatile struct Sgrid Tgrid;


//��������� � ������� ������. �������� ����������� ����� �������� ���������� � ������� ���������.
//��������� ������� ���������, ������ ��� � �������� �������� �������, ������ ��������. ������ ��������� ��������.
struct SGridModel
{
	unsigned short MotorType;		    //!< ��� ��������� � ������ (��� ����������)
	unsigned short MotorParametersNum;	//!< ����� ���������� ��������� �� �������
	unsigned short MotorParametersNumMax; // ������������ ��������� ����� ���������� �� �������
	unsigned short cmpr0;				//!< ������� ��������� ���
	unsigned short cmpr1;
	unsigned short cmpr2;
	unsigned short cmpr3;
	unsigned short InvertorEna;			//!< ���� ��������� ��������� (���� ���, �� ����� �� �����������)
	unsigned short tpr;					//!< ������ ���
	unsigned short dt;					//!< ������� ����� � ����� �������
	unsigned short adc_code_Speed;		//!< ���������� ��������
	unsigned short qepCounter;			//!< ��������� � ��������
	unsigned short hallSensor;			//!< ���������� ������ � ������� ��������� ����� (��� ������ ����)
	float hallSensorInterpAdd;  //!< ��� �������� ������������ ������� �����
	float hallSensorOmega; 		//!< ��� �������� ��������� ������� �������� � ������� �����
	unsigned short adc_code_iA;			//!< ���������� ����
	unsigned short adc_code_iB;
	unsigned short adc_code_iC;
	unsigned short adc_code_iD;
	unsigned short adc_code_Udc;		//!< ���������� �������� ���������� ����� ����������� ���� (���)
	unsigned short fault;				//!< ������ ������
	float load;					//!< ������ ��������
	float loadTmp;				//!< ������ �������� ��������� ����������
	void (*Init)(volatile struct SGridModel*);        //!< Pointer to the init function
	void (*Execute)(volatile struct SGridModel*);      //!<  Pointer to the update function
	Tgrid gridInternals;		//!< ���������� ���������� ��� ������� ������ ���������
};

typedef volatile struct SGridModel TGridModel;

#define GRID_MODEL_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,GridModel_Init, GridModel_Execute}

void GridModel_Init(TGridModel*);
void GridModel_Execute(TGridModel*);



#endif

/*@}*/


