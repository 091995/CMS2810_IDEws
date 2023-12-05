/*
 * dio_logic_vacuum.h
 *
 *  Created on: 6 апр. 2023 г.
 *      Author: User
 */

#ifndef DIO_DIO_LOGIC_VACUUM_H_
#define DIO_DIO_LOGIC_VACUUM_H_


#include "DSP.h"

#define SM_VACUUM_CTRL_INIT 					0
#define SM_VACUUM_CTRL_ON						1
#define SM_VACUUM_CTRL_OFF						2
#define SM_VACUUM_CTRL_BLOCKED					3
#define SM_VACUUM_CTRL_FAILED					4
#define SM_VACUUM_CTRL_GO_ON					5
#define SM_VACUUM_CTRL_GO_OFF					6



//VACUUM
typedef struct
{

	Uint16  cmd_in_on;
	Uint16  cmd_in_off;
	Uint16  cmd_in_block;
	Uint16  cmd_out_on;
	Uint16  cmd_out_off;
	Uint16  cmd_out_block;
	Uint16 	on;
	Uint16  off;
	Uint16  blocked;
	Uint16  fail;

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
} DIO_LOGIC_VACUUM;


#define DIO_LOGIC_VACUUM_DEFAULTS {0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,\
                (void (*)(long))DIO_LOGIC_VACUUM_Init,\
                (void (*)(long))DIO_LOGIC_VACUUM_ms_Calc,\
                 }


void DIO_LOGIC_VACUUM_Init(DIO_LOGIC_VACUUM*p);
void DIO_LOGIC_VACUUM_ms_Calc(DIO_LOGIC_VACUUM*p);


#endif /* DIO_DIO_LOGIC_VACUUM_H_ */
