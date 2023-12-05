#ifndef MODEL
#include "dio_func.h"
#endif
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>

//macros
//#define SET_SRC_STATCOM(cmd_in,cmd_out,value_cmd_out) \
//if (cmd_logic.cmd_refs.##cmd_in == 1 && cmd_logic.cmd_refs.##cmd_in##_prev == 0) \
//{cmd_logic.cmd_refs.##cmd_in##_prev = 1; cmd_logic.status.##cmd_out = value_cmd_out;} \
//else {cmd_logic.cmd_refs.##cmd_in##_prev = cmd_logic.cmd_refs.##cmd_in; cmd_logic.cmd_refs.##cmd_in = 0;}
//

//#define SET_SRC_HVDC(cmd_in,cmd_out,value_cmd_out) \
//if (cmd_logic.cmd_refs.hvdc.##cmd_in == 1 && cmd_logic.cmd_refs.hvdc.##cmd_in##_prev == 0) \
//{cmd_logic.cmd_refs.hvdc.##cmd_in##_prev = 1; cmd_logic.status.hvdc.##cmd_out = value_cmd_out;} \
//else {cmd_logic.cmd_refs.hvdc.##cmd_in##_prev = cmd_logic.cmd_refs.hvdc.##cmd_in; \
//	cmd_logic.cmd_refs.hvdc.##cmd_in = 0;}


#define DETECT_RISE_FRONT(cmd_in) if((cmd_in==1)&&(cmd_in##_prev==0))cmd_in##_prev=1;else{cmd_in##_prev=cmd_in;cmd_in=0;}



void CMD_LOGIC_Init()
{
cmd_logic.state=0;
cmd_logic.state_prev=-1;
cmd_logic.refs.Q_ref=0;



cmd_logic.status.cmd_source = CMD_LOGIC_CMD_SOURCE_LOCAL;
cmd_logic.status.refs_source = CMD_LOGIC_REFS_SOURCE_REMOTE;

cmd_logic.local_refs.P_ref = _IQ(1);

//ToDo CMD_LOGIC_Init set initial status forcmd_logic.status
//cmd_logic.status.dio_logic_mode=
//cmd_logic.status.profile=
}
                       
void CMD_LOGIC_1ms_Calc()
{




if (cmd_logic.state_prev!=cmd_logic.state) cmd_logic.E=1;
else cmd_logic.E=0;
cmd_logic.state_prev=cmd_logic.state;


///////////////////////////////////////////////////////////////////////////////////////
/////  										CMD LOGIC VSC #1
//////////////////////////////////////////////////////////////////////////////////////

switch (cmd_logic.status.cmd_source)
{
case CMD_LOGIC_CMD_SOURCE_REMOTE:
	cmd_logic.cmd.cmd_pow_on=cmd_logic.remote_cmd.bit.cmd_pow_on;
	cmd_logic.cmd.cmd_pow_off=cmd_logic.remote_cmd.bit.cmd_pow_off;
	cmd_logic.cmd.cmd_trip_reset=cmd_logic.remote_cmd.bit.cmd_trip_reset;
	cmd_logic.cmd.cmd_pulses_on=cmd_logic.remote_cmd.bit.cmd_pulses_on;
	cmd_logic.cmd.cmd_pulses_off=cmd_logic.remote_cmd.bit.cmd_pulses_off;

	cmd_logic.cmd.cmd_more=cmd_logic.remote_cmd.bit.cmd_more;
	cmd_logic.cmd.cmd_less=cmd_logic.remote_cmd.bit.cmd_less;
	cmd_logic.cmd.cmd_set_cmd_source_LOCAL=cmd_logic.remote_cmd.bit.cmd_set_cmd_source_LOCAL;
	cmd_logic.cmd.cmd_set_cmd_source_REMOTE=cmd_logic.remote_cmd.bit.cmd_set_cmd_source_REMOTE;
	cmd_logic.cmd.cmd_set_refs_source_LOCAL=cmd_logic.remote_cmd.bit.cmd_set_refs_source_LOCAL;
	cmd_logic.cmd.cmd_set_refs_source_REMOTE=cmd_logic.remote_cmd.bit.cmd_set_refs_source_REMOTE;

//	cmd_logic.cmd.cmd_set_ctrl_profile1=cmd_logic.remote.cmd_set_ctrl_profile1; commented b's can change profile in remote
//	cmd_logic.cmd.cmd_set_ctrl_profile2=cmd_logic.remote.cmd_set_ctrl_profile2;
//	cmd_logic.cmd.cmd_set_ctrl_profile3=cmd_logic.remote.cmd_set_ctrl_profile3;
	cmd_logic.cmd.cmd_set_dio_logic_mode_auto=cmd_logic.remote_cmd.bit.cmd_set_dio_logic_mode_auto;
	cmd_logic.cmd.cmd_set_dio_logic_mode_manual=cmd_logic.remote_cmd.bit.cmd_set_dio_logic_mode_manual;
	cmd_logic.cmd.cmd_set_dio_logic_mode_test=cmd_logic.remote_cmd.bit.cmd_set_dio_logic_mode_test;


break;

case CMD_LOGIC_CMD_SOURCE_LOCAL:
	cmd_logic.cmd.cmd_pow_on=cmd_logic.local_cmd.bit.cmd_pow_on;
	cmd_logic.cmd.cmd_pow_off=cmd_logic.local_cmd.bit.cmd_pow_off;
	cmd_logic.cmd.cmd_trip_reset=cmd_logic.local_cmd.bit.cmd_trip_reset;
	cmd_logic.cmd.cmd_pulses_on=cmd_logic.local_cmd.bit.cmd_pulses_on;
	cmd_logic.cmd.cmd_pulses_off=cmd_logic.local_cmd.bit.cmd_pulses_off;

	cmd_logic.cmd.cmd_more=cmd_logic.local_cmd.bit.cmd_more;
	cmd_logic.cmd.cmd_less=cmd_logic.local_cmd.bit.cmd_less;
	cmd_logic.cmd.cmd_set_cmd_source_LOCAL=cmd_logic.local_cmd.bit.cmd_set_cmd_source_LOCAL;
	cmd_logic.cmd.cmd_set_cmd_source_REMOTE=cmd_logic.local_cmd.bit.cmd_set_cmd_source_REMOTE;
	cmd_logic.cmd.cmd_set_refs_source_LOCAL=cmd_logic.local_cmd.bit.cmd_set_refs_source_LOCAL;
	cmd_logic.cmd.cmd_set_refs_source_REMOTE=cmd_logic.local_cmd.bit.cmd_set_refs_source_REMOTE;

//	cmd_logic.cmd.cmd_set_ctrl_profile1=cmd_logic.local_cmd.bit.;
//	cmd_logic.cmd.cmd_set_ctrl_profile2=cmd_logic.remote.cmd_set_ctrl_profile2;
//	cmd_logic.cmd.cmd_set_ctrl_profile3=cmd_logic.remote.cmd_set_ctrl_profile3;
	cmd_logic.cmd.cmd_set_dio_logic_mode_auto=cmd_logic.local_cmd.bit.cmd_set_dio_logic_mode_auto;
	cmd_logic.cmd.cmd_set_dio_logic_mode_manual=cmd_logic.local_cmd.bit.cmd_set_dio_logic_mode_manual;
	cmd_logic.cmd.cmd_set_dio_logic_mode_test=cmd_logic.local_cmd.bit.cmd_set_dio_logic_mode_test;
break;
default: break;
} //end switch cmd_logic.status.cmd_source


//clear all commands from remote and local
cmd_logic.local_cmd.all=0;
cmd_logic.remote_cmd.all=0;



switch (cmd_logic.status.refs_source)
{
case CMD_LOGIC_REFS_SOURCE_LOCAL:
	switch (cmd_logic.status.cmd_source)
	{
	case CMD_LOGIC_CMD_SOURCE_REMOTE:
		cmd_logic.cmd.cmd_more=cmd_logic.remote_cmd.bit.cmd_more;
		cmd_logic.cmd.cmd_less=cmd_logic.remote_cmd.bit.cmd_less;
	break;
	case CMD_LOGIC_CMD_SOURCE_LOCAL:
		cmd_logic.cmd.cmd_less=cmd_logic.local_cmd.bit.cmd_less;
		cmd_logic.cmd.cmd_more=cmd_logic.local_cmd.bit.cmd_more;
	break;
	default: break;

	}
	cmd_logic.refs.P_dcdc_ref = cmd_logic.local_refs.P_dcdc_ref;
	cmd_logic.refs.P_ref=cmd_logic.local_refs.P_ref;
break;
case CMD_LOGIC_REFS_SOURCE_REMOTE:

	//A&D May 2021
	//the idea is to pass any change in P_ref - if it is from UNICON or RDC (remote mode)
	// so we store _prev value and when it changes apply to cmd_logic.refs.P_ref

	if (cmd_logic.remote_refs.P_ref_prev!=cmd_logic.remote_refs.P_ref) {
		cmd_logic.remote_refs.P_ref_prev = cmd_logic.remote_refs.P_ref;	 //апдетим
		cmd_logic.refs.P_ref=cmd_logic.remote_refs.P_ref;			//запоминаем
		//cmd_logic.local_refs.P_ref = cmd_logic.remote_refs.P_ref;   //корректировка должна происходить при смене источника, а не всегда чттобы не грузить проц
		//cmd_logic.local_refs.P_ref_prev = cmd_logic.remote_refs.P_ref; //корректируем прев
	}

	if (cmd_logic.local_refs.P_ref!=cmd_logic.local_refs.P_ref_prev) {
		cmd_logic.local_refs.P_ref_prev = cmd_logic.refs.P_ref; //апдейтим
		cmd_logic.refs.P_ref=cmd_logic.local_refs.P_ref; //запоминаем
														 //ремоут не корректируем
		}




	//TODO 11 - just from modbus, but i add this to UNICON, so may be changed if MODBUS is not overwrite
	cmd_logic.refs.P_dcdc_ref = cmd_logic.remote_refs.P_dcdc_ref;

break;
default: break;
}




//clear all commands to pass only one's
cmd_logic.remote_cmd.all=0;
cmd_logic.local_cmd.all=0;


DETECT_RISE_FRONT(cmd_logic.cmd.cmd_pow_on);
DETECT_RISE_FRONT(cmd_logic.cmd.cmd_pow_off);
DETECT_RISE_FRONT(cmd_logic.cmd.cmd_pulses_on);
DETECT_RISE_FRONT(cmd_logic.cmd.cmd_pulses_off);
DETECT_RISE_FRONT(cmd_logic.cmd.cmd_trip_reset);



}

