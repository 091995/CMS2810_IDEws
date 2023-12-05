/*
 * canopen_mini.c
 *
 *  Created on: 29 окт. 2018 г.
 *      Author: A&D
 */

#include "canopen_mini.h"
//#include "co_ODvars.h"
#include "can_init.h"
#include "main.h"


//!На входе структура
//!На выходе данные отпавляются в CAN
TCo_MOData  MOdata;

int canopen_mini_ms_update(TCANOPEN_MINI*v) {

v->ms_counter++;
if (v->ms_counter>100) {
	v->ms_counter=0;
	v->send_data=1;
	}

//decrement each ms
v->can_io[0].heart_beat_counter--;
v->can_io[1].heart_beat_counter--;
v->can_io[2].heart_beat_counter--;
v->can_slave.heart_beat_counter--;


if (v->can_io[0].heart_beat_counter<0) {v->can_io[0].heart_beat_counter=0;v->can_io[0].link=0;}
else v->can_io[0].link=1;
if (v->can_io[1].heart_beat_counter<0) {v->can_io[1].heart_beat_counter=0;v->can_io[1].link=0;}
else v->can_io[1].link=1;
if (v->can_io[2].heart_beat_counter<0) {v->can_io[2].heart_beat_counter=0;v->can_io[2].link=0;}
else v->can_io[2].link=1;
if (v->can_slave.heart_beat_counter<0) {v->can_slave.heart_beat_counter=0;v->can_slave.link=0;}
else v->can_slave.link=1;
if (v->can_slave_.heart_beat_counter<0) {v->can_slave_.heart_beat_counter=0;v->can_slave_.link=0;}
else v->can_slave_.link=1;

}


int canopen_mini_slow_update(TCANOPEN_MINI*v) {

	if (v->send_data) {
		v->send_data=0;
		canopen_mini_send_can_io_msg(v);
	}

	canopen_mini_check_can_io_msg(v);

}

unsigned long float2u32(float val)
{
	unsigned long ul_val;
	memcpy(&ul_val,&val,sizeof(unsigned long));
return ul_val;
}


//! Посылка от CAN_IO при разных адресах в ответ на команду
//! 00000108 8 HEX        00       00       00       00       00       00       00       00
//! Ответ
//! №1 00000291 8 HEX        3F       02       01       00       00       00       00       00
//! №2 00000293 8 HEX        3F       00       00       00       00       00       00
//! №3 00000295 8 HEX        3F       00       01       00       00       00       00
//!
//!
//! Команда включения реле
//! 290 00 07
//! 292 00 07
//! 294 00 07
//!
//!
//!
//! DC 00 = 2.18V 8.3MoM
//! 01 19 = 2.8V 1.3MoM
//! FC 03 = 10V V

int can_io_send_state=0;
int canopen_mini_send_can_io_msg(TCANOPEN_MINI*v)
{
	TMBOX_data data;

	//each time send to slave
	data.u32.MDRL=v->can_slave.o_long1;
	data.u32.MDRH=v->can_slave.o_long2;
	co0_send_msg(0,MBOX_TX_TPDO4,0x498, &data);


	can_io_send_state++;
	can_io_send_state&=0x3;
	//if (can_io_send_state>7) can_io_send_state=0;

	switch (can_io_send_state) {
	case 0:								//SYNC
		data.u32.MDRL=0x0308;
		data.u32.MDRH=0;
		co0_send_msg(0,MBOX_TX_SYNC,0x108, &data);
		break;

	case 1:								//TX_CAN_IO1
		data.u32.MDRL=(v->can_io[0].o_word<<8);
		data.u32.MDRH=0;
		co0_send_msg(0,MBOX_TX_TPDO1,0x290, &data);
		break;

	case 2:								//TX_CAN_IO2
		data.u32.MDRL=(v->can_io[1].o_word<<8);
		data.u32.MDRH=0;
		co0_send_msg(0,MBOX_TX_TPDO2,0x292, &data);
		break;

	case 3:								//TX_CAN_IO3
		data.u32.MDRL=(v->can_io[2].o_word<<8);
		data.u32.MDRH=0;
		co0_send_msg(0,MBOX_TX_TPDO3,0x294, &data);
		break;

	default:break;
	}



}


int canopen_mini_check_can_io_msg(TCANOPEN_MINI*v)
{
int res=0;



res = co0_mailbox_read(0,MBOX_RX_RPDO1,&MOdata);
if (res!=0) {
	v->can_io[0].heart_beat_counter=CAN_IO_HEART_BEAT_TIME_MS;
	v->can_io[0].i_word=(~MOdata.data.u32.MDRL)&0xff; //do inversion due to can_io open state is 1
	v->can_io[0].a_inp=(MOdata.data.u32.MDRL>>16);
	}
res = co0_mailbox_read(0,MBOX_RX_RPDO2,&MOdata);
if (res!=0) {
	v->can_io[1].heart_beat_counter=CAN_IO_HEART_BEAT_TIME_MS;
	v->can_io[1].i_word=(~MOdata.data.u32.MDRL)&0xff; //do inversion due to can_io open state is 1
	//v->can_io[1].a_inp=(MOdata.data.u32.MDRL>>16); not used
	}
res = co0_mailbox_read(0,MBOX_RX_RPDO3,&MOdata);
if (res!=0) {
	v->can_io[2].heart_beat_counter=CAN_IO_HEART_BEAT_TIME_MS;
	v->can_io[2].i_word=(~MOdata.data.u32.MDRL)&0xff; //do inversion due to can_io open state is 1
	//v->can_io[2].a_inp=(MOdata.data.u32.MDRL>>16); not used
	}

res = co0_mailbox_read(0,MBOX_RX_RPDO4,&MOdata);
if (res!=0) {
	v->can_slave.heart_beat_counter=CAN_IO_HEART_BEAT_TIME_MS;
	v->can_slave.i_long1=MOdata.data.u32.MDRL;
	v->can_slave.i_long2=MOdata.data.u32.MDRH;
	}

res = co0_mailbox_read(0,MBOX_RX_RPDO5,&MOdata);
if (res!=0) {
	v->can_slave_.heart_beat_counter=CAN_IO_HEART_BEAT_TIME_MS;
//	v->can_slave.i_long1=MOdata.data.u32.MDRL;
//	v->can_slave.i_long2=MOdata.data.u32.MDRH;
	v->can_slave_.i_word0 = MOdata.data.u16.word0;
	}


return res;
}


int canopen_mini_send_msg(TCANOPEN_MINI*v)
{
//	uint32_t param_ID=0x0;
//	uint32_t sub_param_ID=0x0160;
//	TMBOX_data data;
//
//	for (int ii=0;ii<8;ii++) {
//	param_ID++;
//	data.u32.MDRL=(sub_param_ID<<16)+\
//					(param_ID<<8)+ \
//					v->board_ID;
//	data.u32.MDRH=float2u32(v->Idc[ii]);
//	co0_send_msg(0,MBOX_TX_TPDO1,v->board_ID+0x300, &data);
//	}
//	//DC volatge
//	param_ID++;
//	data.u32.MDRL=(sub_param_ID<<16)+\
//					(param_ID<<8)+ \
//					v->board_ID;
//	data.u32.MDRH=float2u32(v->Udc);
//	co0_send_msg(0,MBOX_TX_TPDO1,v->board_ID+0x300, &data);
//	//Temperature
//	param_ID++;
//	data.u32.MDRL=(sub_param_ID<<16)+\
//					(param_ID<<8)+ \
//					v->board_ID;
//	data.u32.MDRH=float2u32(v->temperature);
//	co0_send_msg(0,MBOX_TX_TPDO1,v->board_ID+0x300, &data);
//	//Q1
//	param_ID++;
//	data.u32.MDRL=(sub_param_ID<<16)+\
//					(param_ID<<8)+ \
//					v->board_ID;
//	data.u32.MDRH=v->Q1;
//	co0_send_msg(0,MBOX_TX_TPDO1,v->board_ID+0x300, &data);
//
//	//Q2
//	param_ID++;
//	data.u32.MDRL=(sub_param_ID<<16)+\
//					(param_ID<<8)+ \
//					v->board_ID;
//	data.u32.MDRH=v->Q2;
//	co0_send_msg(0,MBOX_TX_TPDO1,v->board_ID+0x300, &data);
//
//	//special param set_param
//	param_ID=0x2;
//	sub_param_ID=0x0010;
//	data.u32.MDRL=(sub_param_ID<<16)+\
//					(param_ID<<8)+ \
//					v->board_ID;
//	data.u32.MDRH=0x1;
//	co0_send_msg(0,MBOX_TX_TPDO1,v->board_ID+0x300, &data);


return 0;
}
