#ifndef sm_grid_night_batt_charge_H
#define sm_grid_night_batt_charge_H


#include <DIO/sm_profile.h>
//#include "DSP.h"



typedef struct
{


	PROFILE_SETTINGS set;
	 Uint16 ena;
	 Uint16 ena_prev;
	 Uint16 status;
	 Uint16 status_prev;
	 Uint32 counter;
	 Uint32 counter_2;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;
	 Uint16 dcdc_attempts;

	 Uint16 start_hour;
	 Uint16 start_minute;
	 Uint16 autostart;

	 Uint16 night_to_day_hour;
	 Uint16 night_to_day_minute;

	 Uint16 DOW;

	 Uint16 jump_time_min;

 void (*init)();
 void (*ms_calc)();
} SM_GRID_NIGHT_BATT_CHARGE;



#define SM_GRID_NIGHT_BATT_CHARGE_DEFAULTS {{0},\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
                (void (*)(long))SM_GRID_NIGHT_BATT_CHARGE_Init,\
                (void (*)(long))SM_GRID_NIGHT_BATT_CHARGE_ms_Calc,\
                 }


void SM_GRID_NIGHT_BATT_CHARGE_Init(SM_GRID_NIGHT_BATT_CHARGE*p);
void SM_GRID_NIGHT_BATT_CHARGE_ms_Calc(SM_GRID_NIGHT_BATT_CHARGE*p);


#endif
