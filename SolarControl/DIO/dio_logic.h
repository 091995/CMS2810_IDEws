#ifndef M_DIO_LOGIC_H
#define M_DIO_LOGIC_H

#ifndef MODEL
#include "dio_func.h"
#endif
 
//protection description
//#define ALARM_Q1_STATE_UNDEFINED				0x1
//#define ALARM_Q2_STATE_UNDEFINED				0x2
//#define ALARM_Q3_STATE_UNDEFINED				0x4

//#define	P_CB_READY_FAIL_WHEN_STATCOM_ON  		0x10
//#define	P_CS_READY_FAIL_WHEN_STATCOM_ON  		0x20
//#define	P_CC_READY_FAIL_WHEN_STATCOM_ON  		0x40
//#define	P_VALVE_READY_FAIL_WHEN_STATCOM_ON 		0x80
//#define	P_SYRZA_READY_FAIL_WHEN_STATCOM_ON 		0x100
//#define	P_DCBUS_READY_FAIL_WHEN_STATCOM_ON 		0x800



//
//#define STATUS_CTRL_STOP					0
//#define STATUS_CTRL_RUN						1

// mode description
#define DIO_LOGIC_MODE_AUTO				0
#define DIO_LOGIC_MODE_MANUAL			1
#define DIO_LOGIC_MODE_TEST				2

// status description


// test params description
#define PARAM_TEST_MODE_VALVE_PULSE		1
#define PARAM_TEST_MODE_PHASE_PULSE		2
#define PARAM_TEST_MODE_PIO				3



#define SM_DIO_LOGIC2_WAIT_CHARGE          		0
#define SM_DIO_LOGIC2_CB1_ON		 			1
#define SM_DIO_LOGIC2_CHARGING				 	2
#define SM_DIO_LOGIC2_SHUNT_ON				 	3
#define SM_DIO_LOGIC2_STATCOM_ON 				4
#define SM_DIO_LOGIC2_CB1_OFF 					5
#define SM_DIO_LOGIC2_CB_SHUNT_OFF 				6
#define SM_DIO_LOGIC2_WAIT_NOBLOCK_DISCHARGE	7
#define SM_DIO_LOGIC2_WAIT_DISCHARGE  			8

typedef struct
{
int DO1;
int DO2;
int DO3;
int DO4;
} DIO_LOGIC_TEST_CMD;

typedef struct
{
int DCS_ready;
int DCS_Udc;
int DCS_freq;
int DCS_Urms;
} DIO_LOGIC_DCS_INP_DATA;
 

typedef struct
{
	int counter;
	int state;
	int state_prev;
	int E;

	//DIO_LOGIC_DCS_INP_DATA DCS_inp;

	DIO_LOGIC_TEST_CMD	test_cmd;

	//AUX_TIMER timer_1s;

	//DIO_LOGIC_COPAIN COPAIN;
	//DIO_AUX_SURZA aux_SURZA;


	void (*init)();
	void (*calc)();
} DIO_LOGIC;

// «десь присваиваем значения по умолчанию для них
#define DIO_LOGIC_DEFAULTS {0,0,0,0,\
				{0},\
                (void (*)(long))DIO_LOGIC_Init,\
                (void (*)(long))DIO_LOGIC_Calc,\
                 }

// «десь объявляем прототиты функций модуля
void DIO_LOGIC_Init();


void DIO_LOGIC_Calc();
#endif
