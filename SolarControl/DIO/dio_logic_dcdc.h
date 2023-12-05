
#ifndef DIO_LOGIC_DCDC_H
#define DIO_LOGIC_DCDC_H


#include "DSP.h"

#define SM_DCDC_CTRL_INIT 					0
#define SM_DCDC_CTRL_DISABLED				1
#define SM_DCS_CTRL_GO_DISABLE				2
#define SM_DCDC_CTRL_WAIT_READY2CONNECT		3
#define SM_DCDC_CTRL_DO_CONNECTION			4
#define SM_DCDC_CTRL_CONNECTED	5


#define SM_DCDC_CTRL_LINK_FAILED			6
#define SM_DCDC_CTRL_LOGIC_FAILED			7

#define SM_DCDC_CTRL_PRECHARGE_UDC1			8



#define SM_ABC_DIS			0
#define SM_ABC_WAIT_H_OR_CONDITIONS		1
#define SM_ABC_CHARGE		2
#define SM_ABC_DISCHARGE	3

typedef struct
{
	int state;
	int state_prev;
	int E;
	int counter;
	int ena;
	int time_H_charge;
	int time_H_discharge;
	int charge_P;
	int discharge_P;
	int P_ref;
	int cmd_on;
	int cmd_on_prev;
	int charge_counter;
	int discharge_counter;
} AUTO_BMS_CTRL;

typedef struct
{
	//Uint8 _nu_Umax1;
	//Uint8 _nu_Umin1;
	Uint8 Udc1;
	int8 P_ref_kW_I8; //plus sign is for charging and minus for discharging
	Uint8  ctrl_word;
		Uint8 ctrl_start_nstop;
		Uint8 ctrl_trip_reset;
		Uint8 ctrl_prep2connect;
	int32 E_charge_persent;
	int32 I2_meas_A_I12Q4;
	int32  U2_meas_V_I12Q4;
	int32 P_meas_kW;
	Uint8  status_word;
		Uint8 stat_ready2connect;
		Uint8 stat_running;
		Uint8 stat_stopped;
		Uint8 stat_protect_Q_off;
		Uint8 stat_protect;
		Uint8 stat_no_master;
	Uint8 link; //can link control
} DCDC_REGS;

typedef struct
{
	DCDC_REGS regs;
	AUTO_BMS_CTRL abc;

	Uint32 DC_precharge_on;
	Uint32 operating;
	Uint8 discharge_type;
	Uint16 U2_min;
	Uint8 charge_state;
	//Uint32 _nu_Umax1;
	//Uint32 _nu_Umin1;
	Uint32 Udc1; //measured value to pass to slave during DCDC startup and for regulation
	int16 P_ref_kW_IQ8; //plus sign is for charging and minus for discharging
	int16 Idc2_ref;
	Uint16 E_charge_persent;
	int16 I2_meas_A_I12Q4;
	int16  U2_meas_V_I12Q4;
	int16 P_meas_kW_IQ8;

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
} DIO_LOGIC_DCDC;


#define DIO_LOGIC_DCDC_DEFAULTS { {0}, {0}, \
				0,0,0,0,0,0,0, \
				0,0,0,0,0, \
				0,0,0,0,0,0,0,0,\
                (void (*)(long))DIO_LOGIC_DCDC_Init,\
                (void (*)(long))DIO_LOGIC_DCDC_ms_Calc,\
                 }


void DIO_LOGIC_DCDC_Init(DIO_LOGIC_DCDC*p);
void DIO_LOGIC_DCDC_ms_Calc(DIO_LOGIC_DCDC*p);


#endif
