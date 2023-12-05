/*
 * dio_func.c
 *
 *  Created on: 6 сент. 2019 г.
 *      Author: admin
 */


//this file is for support MODEL
#ifdef MODEL

#include "../DIO/dio_aux_io.h"
#include "../DIO/dio_equip_ctrl.h"
#include "../DIO/dio_leds.h"
#include "../DIO/dio_fan_ctrl.h"
#include "../DIO/dio_cmd_logic.h"
#include "../DIO/dio_logic.h"
#include "../DIO/dio_logic_inv.h"
#include "../DIO/dio_logic_copain.h"
#include "../DIO/dio_protect.h"


extern TFAN_ACTRL  fan_actrl;
extern TFAN_DCTRL  fan_dctrl;
extern TFAN_SPEC_RELAY_OUTPUT fan_spec;
extern DIO_LOGIC_INV inv;
extern DIO_LOGIC dio_logic;
extern CMD_LOGIC cmd_logic;
extern DIO_EQUIP_CTRL dio_equip;
extern TLEDS leds;

extern DIO_LOGIC_COPAIN copain;
extern DIO_AUX_Q copain_aux_QS1;
extern DIO_AUX_Q copain_aux_QS2;

extern DIO_AUX_IO aux_io;
extern DIO_AUX_Q aux_Q4;
extern DIO_AUX_Q aux_Q26;
extern DIO_AUX_Q aux_K7;
extern DIO_AUX_CS aux_CS;
extern DIO_AUX_CB aux_CB;

// this is C file to directly show compiler modules paths

#include "../DIO/dio_aux_io.c"
//#include "../DIO/dio_equip_ctrl.c"
#include "../DIO/dio_leds.c"
#include "../DIO/dio_fan_ctrl.c"
#include "../DIO/dio_cmd_logic.c"
#include "../DIO/dio_logic.c"
#include "../DIO/dio_logic_inv.c"
#include "../DIO/dio_logic_copain.c"
#include "../DIO/dio_protect.c"



#endif

