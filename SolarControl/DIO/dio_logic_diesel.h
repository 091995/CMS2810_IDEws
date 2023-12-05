
#ifndef DIO_LOGIC_DISEL_H
#define DIO_LOGIC_DISEL_H


#include "DSP.h"

#define SM_DIESEL_CTRL_INIT 					0
#define SM_DIESEL_CTRL_OPERATING				1
#define SM_DIESEL_CTRL_STOP						2
#define SM_DIESEL_CTRL_GO_RUN					3
#define SM_DIESEL_CTRL_GO_STOP					4
//#define SM_DIESEL_CTRL_CONNECTED				5
///#define SM_DCDC_CTRL_CONNECTED_ACTIVE		6

//#define SM_DIESEL_CTRL_LINK_FAILED			6
//#define SM_DIESEL_CTRL_LOGIC_FAILED			7


//DIESEL
typedef struct
{

	int P_ref;
	int P_meas;
	int Udc_load; //minimum Udc when power should flow according to generator ref

	Uint16 fuel_level;
	Uint16  cmd_out_start;
	Uint16  cmd_in_on;
	Uint16  cmd_in_off;
	Uint16 	ready;
	Uint16  operating;
	Uint16  ON;

	 Uint16 ena;
	 Uint16 ena_prev;
	 Uint16 status;
	 Uint16 status_prev;
	 Uint16 counter;
	 Uint16 state;
	 Uint16 state_prev;
	 Uint16 E;

 void (*init)();
 void (*ms_calc)();
} DIO_LOGIC_DIESEL;


#define DIO_LOGIC_DIESEL_DEFAULTS {0,0,0,\
				0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,\
                (void (*)(long))DIO_LOGIC_DIESEL_Init,\
                (void (*)(long))DIO_LOGIC_DIESEL_ms_Calc,\
                 }


void DIO_LOGIC_DIESEL_Init(DIO_LOGIC_DIESEL*p);
void DIO_LOGIC_DIESEL_ms_Calc(DIO_LOGIC_DIESEL*p);


#endif
