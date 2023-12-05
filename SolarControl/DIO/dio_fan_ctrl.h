/*!
    Copyright 2019 	A&D

 \file        V_FUN_CTRL.h
 \brief
 \author    A&D
 \version   v 1.0 08/06/2019

 \defgroup  FUN_CTRL  (см. TFUN_CTRL)

 @{
*/


#ifndef _V_FAN_CTRL_H_
#define _V_FAN_CTRL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define	ST_FAN_DCTRL_INIT 			 	0
#define ST_FAN_DCTRL_HI_1ST_RUN			1
#define	ST_FAN_DCTRL_LO_1ST_RUN			2
#define	ST_FAN_DCTRL_LO					3
#define	ST_FAN_DCTRL_HI					4
#define	ST_FAN_DCTRL_OFF				5

//! General ctrl function for discrete fan control
 struct SFAN_DCTRL
  {
	  float T;
	  float Temp_lo;
	  float Temp_hi;
	  float Temp_lo2hi;
	  float Temp_hi2lo;
	  float T_max;

	  int time_hi2lo_ms;
	  int time_lo2hi_ms;
	  int time_1st_run_ms;

	  int state;
	  int state_prev;
	  int E;
	  int cnt_ms;

	  int set_lo;
	  int set_hi;

	  int ready;
	  void (*init)(volatile struct SFAN_DCTRL*);
	  void (*calc)(volatile struct SFAN_DCTRL*);
  };

typedef volatile struct SFAN_DCTRL TFAN_DCTRL;

#define FAN_DCTRL_DEFAULTS {0,0,0,0,0,0, \
			0,0,0,\
			0,0,0,0,\
			0,0,\
			0,\
			TFAN_DCTRL_Init,\
			TFAN_DCTRL_Calc}

void TFAN_DCTRL_Init(TFAN_DCTRL*);
void TFAN_DCTRL_Calc(TFAN_DCTRL*);






//! special function to turn ON|OFF power relay during lo|hi|off states change
//!

#define	ST_FAN_SPEC_INIT		0
#define	ST_FAN_SPEC_OFF	   		1
#define	ST_FAN_SPEC_GO_LO		2
#define	ST_FAN_SPEC_LO			3
#define	ST_FAN_SPEC_GO_HI		4
#define	ST_FAN_SPEC_HI			5
#define	ST_FAN_SPEC_GO_OFF		6


struct SFAN_SPEC_RELAY_OUTPUT
{
int lo; //input
int hi; //input
int cmd_lo; //cmd to relay
int cmd_hi; //cmd to relay
int cmd_pow; //cmd to power relay
int d_fdb; //fdb to monitor current when FAN is running
int fail;

int state;
int state_prev;
int E;
int cnt_ms;

int time_pow_ms;
int err_counter;

void (*init)(volatile struct SFAN_SPEC_RELAY_OUTPUT*);
void (*calc)(volatile struct SFAN_SPEC_RELAY_OUTPUT*);
};

typedef volatile struct SFAN_SPEC_RELAY_OUTPUT TFAN_SPEC_RELAY_OUTPUT;

#define FAN_SPEC_RELAY_OUTPUT_DEFAULTS {0,0,0,0,0,0,0, \
			0,0,0,0,\
			0,0,\
			TFAN_SPEC_RELAY_OUTPUT_Init,\
			TFAN_SPEC_RELAY_OUTPUT_Calc}
void TFAN_SPEC_RELAY_OUTPUT_Init(TFAN_SPEC_RELAY_OUTPUT*);
void TFAN_SPEC_RELAY_OUTPUT_Calc(TFAN_SPEC_RELAY_OUTPUT*);





//! General ctrl function for ANALOG fan control

#define	ST_FAN_ACTRL_INIT 			 	0
#define	ST_FAN_ACTRL_1ST_RUN		 	1
#define	ST_FAN_ACTRL_ACTIVE				2

struct SFAN_ACTRL
  {
	  float T;
	  float Temp_max_fan;
	  float Temp_min_fan;
	  int time_1st_run_ms;

	  int state;
	  int state_prev;
	  int E;
	  int cnt_ms;

	  float V_out;
	  float V_fdb;
	  float K;
	  void (*init)(volatile struct SFAN_ACTRL*);
	  void (*calc)(volatile struct SFAN_ACTRL*);
  };

typedef volatile struct SFAN_ACTRL TFAN_ACTRL;

#define FAN_ACTRL_DEFAULTS {0,0,0,0, \
			0,0,0,0,\
			0,0,0,\
			TFAN_ACTRL_Init,\
			TFAN_ACTRL_Calc}

void TFAN_ACTRL_Init(TFAN_ACTRL*);
void TFAN_ACTRL_Calc(TFAN_ACTRL*);


#ifdef __cplusplus
}
#endif




#endif

/*@}*/





