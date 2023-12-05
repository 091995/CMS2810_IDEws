
#ifndef DIO_LOGIC_SM_PROFILE_H
#define DIO_LOGIC_SM_PROFILE_H


#include "DSP.h"
#include "V_IQmath.h"




//#define SETP(p_val,val) *p_val = val
//#define GETP(p_val)		(int32) *p_val
void SETP(int32*p_val,int32 val);
int GETP(int32*p_val);

//учесть, что состояние профиля должны соответствовать написям в термиаале

#define SM_PROFILE_INIT			 								-1
#define	SM_PROFILE_0											0
#define SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT				1
#define SM_PROFILE_GRID_EVNG_BATT_DIESEL						2
#define SM_PROFILE_GRID_NIGHT_BATT_CHARGE						3
#define SM_PROFILE_ISLA_BATT_DIESEL								4

#define SM_PROFILE_MANUAL										5

//#define SM_PROFILE_GO_ISLA										6
//#define SM_PROFILE__ISLA__SOL__BATT__DIESEL						7
//#define SM_PROFILE__ISLA__BATT__DIESEL							8
#define SM_PROFILE_LOGIC_FAILED									100

#define BATT_REGULATION_MODE_UDC_SUPPORT  		1
#define BATT_REGULATION_MODE_P_CONST 		 	2


//A&D add here pinters for settings you want to change during profile switching
//typedef struct {
//	int32* inv_pid_Udc_kp;
//	int32* inv_pid_Udc_ki;
//	int32* inv_cmd_pulses_on;
//	int32* inv_cmd_pulses_off;
//	int32* inv_cmd_pow_on;
//	int32* inv_cmd_pow_off;
//	int32* inv_profile;
//	int32* inv_mppt_ena;
//	int32* inv_Udc;
//
//
//	int32* dcdc_ena;
//	int32* dcdc_P_ref;
//	int32* dcdc_batt_charge;
//	int32* dcdc_operating;
//	int32* dcdc_regulation_mode;
//
//	int32* diesel_start;
//	int32* diesel_operating;
//	int32* diesel_fuel_level;
//
//} PROFILE_SETTINGS_POINTERS;

typedef struct{
	int32 pid_Udc_kp;
	int32 pid_Udc_ki;
	int32 mppt_ena;
	int32 dcdc_P_discharge;
	int16 dcdc_I_discharge;
	int32 dcdc_P_charge;
	int16 dcdc_I_charge;
	int32 diesel_P_ref;
	int32 inv_Udc_min;		//low level of Udc when start diesel
} PROFILE_SETTINGS;



typedef struct
{
	int cmd_local_set_profile;
	int cmd_local_set_profile_prev;

	int cmd_remote_set_profile;
	int cmd_remote_set_profile_prev;

//	int Udc;
//	int P_ref;

//	int batt_cmd_on;
//	int batt_cmd_off;
//
//	int diesel_cmd_on;
//	int diesel_cmd_off;
//
//	int solar_cmd_on;
//	int solar_cmd_off;
//
//	int inv_cmd_on;
//	int inv_cmd_off;

//	int inv_isla_mode;

//	int diesel_opearating;

//	int batt_link;
//	int batt_operating;
//	int batt_charge_persent;
} PROFILE_IN;


//typedef struct
//{
////	int inv_regulation_mode;
////	int batt_regulation_mode;
////	int batt_on;
////	int inv_on;
////	int diesel_on;
////	int solar_on;
//} PROFILE_OUT;


typedef struct
{

	//PROFILE_OUT out;
	PROFILE_IN in;

	//PROFILE_SETTINGS_POINTERS p;
	PROFILE_SETTINGS set1;
	PROFILE_SETTINGS set2;
	PROFILE_SETTINGS set3;


	Uint16 profile1_state;
	Uint16 profile2_state;
	Uint16 profile3_state;
	Uint16 profile4_state;


	 Uint16 status;
	 Uint16 status_prev;
	 Uint16 counter;
	 Uint32 profile;
	 Uint32 profile_prev;

	 Uint16 E;
 void (*init)();
 void (*ms_calc)();
} SC_PROFILE;


#define SC_PROFILE_DEFAULTS { {0}, \
				{0},{0},{0},\
				0,0,0,0,\
				0,0,0,0,0,0,\
                (void (*)(long))SC_PROFILE_Init,\
                (void (*)(long))SC_PROFILE_ms_Calc,\
                 }


void SC_PROFILE_Init(SC_PROFILE*p);
void SC_PROFILE_ms_Calc(SC_PROFILE*p);


#endif
