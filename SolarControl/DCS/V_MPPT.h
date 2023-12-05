/*!
    Copyright 2019 	A&D

 \file        V_MPPT.h
 \brief
 \author    A&D
 \version   v 1.0 06/06/2019

 \defgroup  mmpt  (��. TMPPT)

 @{
*/


#ifndef _V_MPPT_H_
#define _V_MPPT_H_


  

  struct SMPPT
  {
	long  Dinit;  //Initial value for Vdc_ref
	long  Dmax ;   //Maximum value for Vdc_ref
	long  Dmin;   //Minimum value for Vdc_ref
	long  deltaD; //Increment value used to increase/decrease Vdc_ref

	long ena;
    long V;
    long V_prev;
    long I;
    long I_prev;
    long D;
    long D_prev;
    long P;
    long P_prev;
    long delayvar;
    long deltaV;
    long Vmax;
    long Vmin;

    long counter;
    long counter2;
    int state;
    int state_prev;
    int E;
    void (*init)(volatile struct SMPPT*);//��������� �� ������� �������
    void (*calc)(volatile struct SMPPT*);//��������� �� ������� �������
  };

  typedef volatile struct SMPPT TMPPT;

  //! ������������� ��-���������
#define MPPT_DEFAULTS {_IQ(1),_IQ(1.1),_IQ(0.8),_IQ(0.01), \
		0,0,0,0,0,0,0,0,0,0,0,0,0, \
		0,0,0,0,0,\
		TMPPT_Init,\
		TMPPT_Calc,\
	}

void TMPPT_Init(TMPPT*);
void TMPPT_Calc(TMPPT*);




#endif

/*@}*/





