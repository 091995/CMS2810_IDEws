#ifndef SM_DAILY_CICLE_H
#define SM_DAILY_CICLE_H


#include "sm_profile.h"
#include "DSP.h"

typedef struct{
	int32 time1;
	int32 time2;
} SM_DAILY_CICLE_SETTINGS;

typedef struct
{
	SM_DAILY_CICLE_SETTINGS set;

	 Uint16 ena;  //defines is this profile enabled in system. Initaiily all profiles are available
	 Uint16 ena_prev;
	 Uint16 status;
	 Uint16 status_prev;
	 Uint16 counter;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;
	 Uint8 week;
 void (*init)();
 void (*ms_calc)();
} SM_DAILY_CICLE;



#define SM_DAILY_CICLE_DEFAULTS { {0},\
				0,0,0,0,0,0,0,0,0,\
                (void (*)(long))SM_DAILY_CICLE_Init,\
                (void (*)(long))SM_DAILY_CICLE_ms_Calc,\
                 }


void SM_DAILY_CICLE_Init(SM_DAILY_CICLE*p);
void SM_DAILY_CICLE_ms_Calc(SM_DAILY_CICLE*p);


#endif
