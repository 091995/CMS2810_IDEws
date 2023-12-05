#ifndef sm_manual_H
#define sm_manual_H


#include "sm_profile.h"
#include "DSP.h"



typedef struct
{
	//PROFILE_SETTINGS_POINTERS*p;
	PROFILE_SETTINGS set;

	 Uint16 ena;  //defines is this profile enabled in system. Initaiily all profiles are available
	 Uint16 ena_prev;
	 Uint16 status;
	 Uint16 status_prev;
	 Uint16 counter;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;
 void (*init)();
 void (*ms_calc)();
} SM_MANUAL;



#define SM_MANUAL_DEFAULTS { {0},\
				0,0,0,0,0,0,0,0,\
                (void (*)(long))SM_MANUAL_Init,\
                (void (*)(long))SM_MANUAL_ms_Calc,\
                 }


void SM_MANUAL_Init(SM_MANUAL*p);
void SM_MANUAL_ms_Calc(SM_MANUAL*p);


#endif
