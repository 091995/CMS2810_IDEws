
#include "IQmathLib.h"          // ���������� IQmath
#include "V_PWM_Module.h"
#include "main.h"

#if defined(HW_MOTORCONTROLBOARD)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

//! ����������� �������� "������� �������"
#if defined(HW_MOTORCONTROLBOARD)
//! ��� ������������ ��������� ������ ������ 3���, ����� �� �����
#define DEAD_BAND_MIN   _IQ(3)
#define DEAD_BAND_MAX   _IQ(10)
#else
#define DEAD_BAND_MIN   _IQ(0)
#define DEAD_BAND_MAX   _IQ(10)
#endif
*/
//! �������������

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {



}


//! ��������� ������

//! ��������������� ��������� ������������� ��������
//! �������� �������� �������, ������� ��� � �.�.

//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *p) {

}


//! ������� ��������� ��� (��������� ���������)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {


}

//! ������� ���������� ��� (���������� ���������)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

}

void PWM_Module_PDP_trip_reset(TPWM_Module *p)
{

}


//! ������������ ������� �������.

//!��������� ����������� ���������� ��� ��������� Ud,
//!��������� ���������� ������� � ����������, ���� ���������, �
//!��������� ����� ������, ������������ �������� ���� ����������.
//! \memberof TPWM_Module
void PWM_Module_NormInput(TPWM_Module* p) {

}


//! ������� 6�� ��������� ��������� ���

//! \memberof TPWM_Module
//volatile long TBCTR_reg;

//volatile int gam1[256];
//volatile int gam2[256];
//volatile int gam1_pos=0;
//volatile int gam2_pos=0;
//volatile int gam_state=0;




void PWM_Module_No_SV_Update(TPWM_Module *p) {

}



void PWM_Module_Aux_Update(TPWM_Module*p)
{


}



/*@}*/
