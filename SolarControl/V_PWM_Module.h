/*!
     Copyright 2023 ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_PWM_Module.h
 \brief     ������ ���������� ��������� ��� (��. TPWM_Module)
 \author    ��� "��� ������". http://motorcontrol.ru

 \defgroup  V_PWM_Module ������ ���������� ��������� ��� (��. TPWM_Module)
 @{*/

#ifndef _V_PWM_Module_
#define _V_PWM_Module_

#ifdef __cplusplus
extern "C"
{
#endif

//#include "filter.h"
#include "f28xbmsk.h"
#include "DSP28_Device.h"

/*----------------------------------------------------------------------------
Initialization constant for the F28X Timer TxCON for PWM Generation.
Sets up the timer to run free upon emulation suspend, continuous up-down mode
prescaler 1, timer enabled.
----------------------------------------------------------------------------*/


#define _1_SQRT3 _IQ(0.5773503)
#define _2_SQRT3 _IQ(1.1547005)

//0x0000 ����������� ��� ��� ���� ������ �� ������� ���� �� ������ ����
#define PWM_INIT_STATE  (0x0000+\
                       TIMER_CONT_UPDN + \
                       TIMER_CLK_PRESCALE_X_1 + \
                       TIMER_ENABLE_BY_OWN    + \
                       TIMER_ENABLE + \
                       TIMER_ENABLE_COMPARE \
                      )

/*----------------------------------------------------------------------------
Initialization constant for the F28X ACTRx register for PWM Generation.
Sets up PWM polarities.
----------------------------------------------------------------------------*/
#define PWM_ACTR_INIT_STATE ( COMPARE1_AH + \
                            COMPARE2_AL + \
                            COMPARE3_AH + \
                            COMPARE4_AL + \
                            COMPARE5_AH + \
                            COMPARE6_AL )


/*----------------------------------------------------------------------------
Initialization constant for the F28X DBTCONx register for PWM Generation.
Sets up the dead band for PWM and sets up dead band values.
----------------------------------------------------------------------------*/
//DBT_VAL_10*DBTPS_X32=320; 150000000/2=75000000; DB=1/(75000000/320.)=4.2e-6
#define PWM_DBTCON_INIT_STATE ( DBT_VAL_10 +  \
                              EDBT3_EN   +  \
                              EDBT2_EN   +  \
                              EDBT1_EN   +  \
                              DBTPS_X32 )

//! ����������� ������� ��� (���) min
#define PWM_FREQ_MIN    _IQ10(2)
//! ����������� ������� ��� (���) max
#define PWM_FREQ_MAX    _IQ10(100.0)

//!��������� 6-�� ��������� ���
#define PWM_TYPE_6SECT_NO_SV    0
//!�������������� ���
#define PWM_TYPE_SIN_PWM        1
//!��������� 12-�� ��������� ���
#define PWM_TYPE_12SECT_NO_SV   2
//!��� ������� ���������� ������ �����������
#define PWM_TYPE_FLY_12SECT     3
//!��� ��� ���������� ���
#define PWM_TYPE_DC_DRIVE       4
//!��� ��� ���������� SRM
#define PWM_TYPE_SRD            5


//! ����������� �������� "����������� ����������", ���, min
#define GAMMA_LIMIT_MIN _IQ(0)
//! ����������� �������� "����������� ����������", ���, max
#define GAMMA_LIMIT_MAX _IQ(10)

// ��������� �������� ��������� AQCTL# � AQCSFRC (ePWM)
// (���������� ��������� ������� ��� ������� ���)
#define AQ_EPWM_DISABLE 0x0000                          //!< ��� ������� ���������

//! ���� ���������� ���������� �������� ���-�������
#define ENABLE_PULLUP   0

//!��� ������ ��� ���������� ������ � �������
#define TZ_STATE  TZ_FORCE_LO

/*! \class TPWM_Module
 \brief ������ ���������� ���

 ����� \a TPWM_Module, ���������� �� ��������� SPWM_Module, ���������
 ��������� � ��������� �������-���������� ��������� ��� ����������
 ������������� ����������. ����� ��������� �������� �������,
 �������, ��������� � ����������� �� ���������� ���,
 ����������� �������� �������.
 ������� ���������� ���������� �� ���� ���������������� ���� ����� � �����.
 ��� ���� ��� ����� ������������ � ���� � ���������� ������� ���������. ��� ������� ������ ���������� �����
 ��������� ������� � UalphaRef, UbetaRef � ������� update. � ����������� �� ����,
 ����� ��� ��� ������ � ���������� (������������� ������������� � ���������� PWM_type),
 ������� PWM_Module_Update ������� ������ �������, ����������� ��������� ��� ���.
 � ���������� ����� �� ���� ����� ��������� � ������� �� ������ ��� ����� ����������
 ����� ������ ����������, ������� ����� � UalphaRef, UbetaRef. ����� ������� ����������
 �������������� ����������, ��������� ������� ������ ������� ������� �� ��������� � ������ ��� ����������.
 */

//! ��. TPWM_Module
struct SPWM_Module {
    int16 Enabled; //!< ���� ��� ������ - ������� ��� ��� ��������.
    int32 UalphaRef; //!<������� �� ��� ����� (��������)
    int32 UbetaRef; //!<������� �� ��� ����� (��������)
    int32 Udc_meas; // ��� ������������� �� ���������� ���

    int32 UPhARef; //!<������� �� ���� A (��������)
    int32 UPhBRef; //!<������� �� ���� B (��������)
    int32 UPhCRef; //!<������� �� ���� c (��������)

    int32 k_pwm; //!< ������ ������� ���, ��� ������.
    int32 U_mag; //!< ������� ��������� ����������, ��� ������.
    int32 U_lim; //!< ����������� ������� ����������, ��������

    int32 GammaA; //!< ���������� ���� � � ����������� ������� ���, ��� ������.
    int32 GammaB; //!< ���������� ���� B � ����������� ������� ���, ��� ������.
    int32 GammaC; //!< ���������� ���� C � ����������� ������� ���, ��� ������.

    int16 PWM_type; //!< ��� ���. ��������� �������� �������� � ��������� PWM_TYPE_. ��������.
    int16 PWM_typeOld; //!< ���������� �������� ���� ���, ��������� ����������.
    int16 sector; //!< ������� ������ � ��������� ���� ���. ��� ������.

    int32 UalphaNorm; //!< ������������� �������, ��������� ����������.
    int32 UbetaNorm; //!< ������������� �������, ��������� ����������.
    int32 UdCorTmp; //!<��������� ���������� ��� ������������� ��������� ���������� � ����������� �� ���������� ���
    int32 UdCompK; //!< ����������� ������������� ��������� ���������� ��������� � ����������� �� ��������� ���������� ��� �� ������������. ��������.
    int32 UdCompEnable; //!< ���������� ������������� ��������� ���������� ��������� � ����������� �� ��������� ���������� ��� �� ������������. ��������.
    int16 ULimitation; //!< ���� � ���, ��� ���� ����������� ���������� - �������� ���������� ������ ���������. ��� ������.
    _iq Frequency; //!< ������� ��� � ���. ������ 22.10! ��������.
    _iq FreqPrev; //!< ���������� ������� ���, ��������� ����������.
    int32 DeadBand; //!< �������� "������� �������", ���, ��������.
    int32 MinGammaLimit; //!< ����������� ���������� �� �����, ��������.
    int PDP_Fault; //!< ���� � ���, ��� ������� ��� ������������� ���������� ������ �� ���������. ��� ������. �� ��� ���������� ������� ������ �����!
    int ChargingMode; //!< ����� ������ ����������� �������������. ������ ������������ � ������� �� ����� 2-10 �� ������� ���������� ����� �������� ���.
    int PDP_inv1;
    int PDP_inv_ext_lost;
    int PDP_pulses_block_Imax;
    volatile struct EVA_REGS *EvXRegs;
    void (*init)(volatile struct SPWM_Module*); /* Pointer to the init function               */
    void (*update)(volatile struct SPWM_Module*); /* Pointer to the update function             */
    void (*slow_calc)(volatile struct SPWM_Module*);
    void (*On)(volatile struct SPWM_Module*); //!< ��������� ��������� (����������) ���-�������
    void (*Off)(volatile struct SPWM_Module*); //!<  ��������� ���������� (����������) ���-�������
};

typedef volatile struct SPWM_Module TPWM_Module;

//! ������������� ��-���������.
#define PWM_Module_DEFAULTS  {\
    0,0,0,0, \
    0,0,0, \
    0, \
    0, \
    _IQ(0.866),0, \
    0,0,\
    0,0,\
    0,\
    0,0,0,0,0,0,0x1400,0,0,0,0,0,0,0,0,\
    &EvaRegs,\
    PWM_Module_Init,  \
    PWM_Module_Update, \
    PWM_Module_SlowCalc, \
    PWM_Module_On, \
    PWM_Module_Off, \
  }

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_Update(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *);

//��������� ������� �� ����������
void PWM_Module_No_SV_Update(TPWM_Module *);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/

