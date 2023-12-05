#ifndef sm_grid_batt_diesel_H
#define sm_grid_batt_diesel_H


#include <DIO/sm_profile.h>
#include "DSP.h"



typedef struct
{


	 PROFILE_SETTINGS set;
	 Uint16 ena;
	 Uint16 ena_prev;
	 Uint16 status;
	 Uint16 status_prev;
	 Uint32 counter;
	 Uint32 counter_diesel;
	 Uint32 counter_batt;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;
	 Uint16 acc_ena;
	 Uint16 acc_ena_batt;

	 Uint16 dcdc_attempts;
	 Uint16 diesel_attempts;

	 Uint16 start_hour;
	 Uint16 start_minute;
	 Uint16 autostart;

	 Uint16 fade_hour;
	 Uint16 fade_minute;

	 Uint8 warming_time;
	 Uint8 without_diesel;
	 Uint8 without_batt;

	 Uint16 batt_idle_time_min;
 void (*init)();
 void (*ms_calc)();
} SM_GRID_EVNG_BATT_DIESEL;



#define SM_GRID_EVNG_BATT_DIESEL_DEFAULTS { {0},\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,\
                (void (*)(long))SM_GRID_BATT_DIESEL_Init,\
                (void (*)(long))SM_GRID_BATT_DIESEL_ms_Calc,\
                 }


void SM_GRID_BATT_DIESEL_Init(SM_GRID_EVNG_BATT_DIESEL*p);
void SM_GRID_BATT_DIESEL_ms_Calc(SM_GRID_EVNG_BATT_DIESEL*p);


#endif
