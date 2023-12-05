#ifndef DIO_FUNC_H
#define DIO_FUNC_H
#include "V_IQmath.h"

#include <DIO/dio_logic_dcdc.h>
#include <DIO/dio_logic_diesel.h>
#include <DIO/dio_logic_vacuum.h>
#include <DIO/sm_grid_evng_batt_diesel.h>

	
#include "DIO/dio_aux_io.h"
#include "DIO/dio_equip_ctrl.h"
#include "DIO/dio_leds.h"
#include "DIO/dio_fan_ctrl.h"
#include "DIO/dio_cmd_logic.h"
#include "DIO/dio_logic.h"
#include "DIO/dio_logic_inv.h"
#include "DIO/dio_protect.h"

#include <DIO/sm_profile.h>
#include <DIO/sm_grid_day_solar_mppt_charge_batt.h>
#include <DIO/sm_grid_evng_batt_diesel.h>
#include <DIO/sm_grid_night_batt_charge.h>
#include <DIO/sm_manual.h>
#include <DIO/sm_isla_batt_diesel.h>

#include <DIO/sm_daily_cicle.h>





//#define DIO_LOGIC_DCS
extern TFAN_ACTRL  fan_actrl;
extern TFAN_DCTRL  fan_dctrl;
extern TFAN_SPEC_RELAY_OUTPUT fan_spec;
extern DIO_LOGIC_INV inv;
extern DIO_LOGIC dio_logic;
extern CMD_LOGIC cmd_logic;
extern DIO_EQUIP_CTRL dio_equip;
extern TDIO_PROTECT dio_protect;
extern TLEDS leds;

extern DIO_AUX_Q aux_Q6;

extern DIO_LOGIC_DCDC dcdc;
extern DIO_LOGIC_DIESEL diesel;
extern DIO_LOGIC_VACUUM vacuum;

extern SC_PROFILE sc_profile;
extern SM_ISLA_BATT_DIESEL sm_isla_batt_diesel;
extern SM_GRID_EVNG_BATT_DIESEL sm_grid_evng_batt_diesel;
extern SM_GRID_NIGHT_BATT_CHARGE sm_grid_night_batt_charge;
extern SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT sm_grid_day_solar_mppt_charge_batt;
extern SM_DAILY_CICLE sm_daily_cicle;



extern DIO_AUX_IO aux_io;
extern DIO_AUX_Q aux_Q4;   	// switch to DC
extern DIO_AUX_Q aux_Q26;	// switch to power grid
extern DIO_AUX_Q aux_K7;  // relay to grid
extern DIO_AUX_Q aux_K91; //fan power control

//extern DIO_AUX_CS aux_CS;
//extern DIO_AUX_CB aux_CB;

extern AUX_CAN_IO can_io;



#endif
