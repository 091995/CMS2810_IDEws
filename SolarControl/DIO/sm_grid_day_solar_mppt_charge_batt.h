#ifndef SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_H
#define SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_H


#include <DIO/sm_profile.h>
#include "DSP.h"



typedef struct
{
	//PROFILE_OUT*out;
	//PROFILE_IN*in;


	PROFILE_SETTINGS set;

	 Uint16 ena;
	 Uint16 ena_prev;
	 Uint16 status;
	 Uint16 status_prev;
	 Uint16 counter;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;
	 Uint16 dcdc_attempts;
 void (*init)();
 void (*ms_calc)();
} SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT;



#define SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_DEFAULTS {{0},\
				0,0,0,0,0,0,0,0,0,\
                (void (*)(long))SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_Init,\
                (void (*)(long))SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_ms_Calc,\
                 }


void SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_Init(SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT*p);
void SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_ms_Calc(SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT*p);


#endif
