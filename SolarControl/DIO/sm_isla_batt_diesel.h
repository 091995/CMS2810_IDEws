#ifndef sm_isla_batt_diesel_H
#define sm_isla_batt_diesel_H


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
	 Uint32 counter;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;
	 Uint16 diesel_attempts;
	 Uint16 dcdc_attempts;
	 Uint16 Udc2_high;
	 Uint16 Udc2_low;
	 Uint16 start_hour;
	 Uint16 start_minute;
	 Uint16 fade_hour;
	 Uint16 fade_minute;
	 Uint16 autostart;

	 Uint16 invs_off;

 void (*init)();
 void (*ms_calc)();
} SM_ISLA_BATT_DIESEL;



#define SM_ISLA_BATT_DIESEL_DEFAULTS { {0},\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
                (void (*)(long))SM_ISLA_BATT_DIESEL_Init,\
                (void (*)(long))SM_ISLA_BATT_DIESEL_ms_Calc,\
                 }


void SM_ISLA_BATT_DIESEL_Init(SM_ISLA_BATT_DIESEL*p);
void SM_ISLA_BATT_DIESEL_ms_Calc(SM_ISLA_BATT_DIESEL*p);


#endif
