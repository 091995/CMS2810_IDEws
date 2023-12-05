/*
 * canopen_mini.h
 *
 *  Created on: 29 окт. 2018 г.
 *      Author: A&D
 */

#ifndef INCLUDE_CANOPEN_MINI_H_
#define INCLUDE_CANOPEN_MINI_H_

#include "V_IQmath.h"

//TODO 9 time increased #define CAN_IO_HEART_BEAT_TIME_MS 1100
#define CAN_IO_HEART_BEAT_TIME_MS 2200


typedef struct {
//	int K21;
//	int	K22;
//	int K23;
//
//	int inp1;
//	int inp2;
//	int inp3;
//	int inp4;
//	int inp5;
//	int inp6;

	int i_word;
	int o_word;
	int a_inp; //in Volts 0-10V 10bit ADC 0x3ff=10V

	int heart_beat_counter;
	int link; //if link==1 then each CAN_IO_HEART_BEAT_TIME_MS new can msg received
} CAN_IO_DATA;


typedef struct {
	int i_long1;
	int i_long2;
	int o_long1;
	int o_long2;
	int16 i_word0;
	int heart_beat_counter;
	int link; //if link==1 then each CAN_IO_HEART_BEAT_TIME_MS new can msg received
} CAN_SLAVE_DATA;

#define TCANOPEN_MINI_CAN_IO_DATA_DEFAULTS  { 0,0,0, 0,0}


struct sCANOPEN_MINI	{
				int ms_counter;
				int send_data;
				uint16_t  num;
				CAN_IO_DATA can_io[3];
				CAN_SLAVE_DATA can_slave;
				CAN_SLAVE_DATA can_slave_;
				void  (*ms_update)();
				void  (*slow_update)();
				};

typedef struct sCANOPEN_MINI TCANOPEN_MINI;


#define TCANOPEN_MINI_DEFAULTS	{0,0,0, \
								{TCANOPEN_MINI_CAN_IO_DATA_DEFAULTS, \
								TCANOPEN_MINI_CAN_IO_DATA_DEFAULTS, \
								TCANOPEN_MINI_CAN_IO_DATA_DEFAULTS}, \
								{0},{0},\
								canopen_mini_ms_update,\
								canopen_mini_slow_update,\
		}


int canopen_mini_check_can_io_msg(TCANOPEN_MINI*v);
int canopen_mini_send_can_io_msg(TCANOPEN_MINI*v);
int canopen_mini_ms_update(TCANOPEN_MINI*v);
int canopen_mini_slow_update(TCANOPEN_MINI*v);



#endif /* INCLUDE_CANOPEN_MINI_H_ */
