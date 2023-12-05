/*!
     Copyright 2017 	АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file		v_MBVarsConv.h
 \brief		Модуль преобразования данных Modbus
 \author	ООО "НПФ ВЕКТОР"
 \version	v.1.1. 02/03/2017

 \addtogroup v_ModBus

 @{
*/



#ifndef V_MBVARSCONV_H
#define V_MBVARSCONV_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "DSP.h"

/*! \class TMBVarsConv
  \brief Модуль преобразования данных Modbus

  Класс \a TMBVarsConv, основанный на структуре SMBVarsConv, предназначен
  для преобразования данных из формата 16 разрядов Modbus в формат системы управления (IQ 24).
*/


struct SMBVars{
	int	Command;
	int	CommandPrev;
	Uint16 _0022_Manufacture[16];
	Uint16 _032_ModelName[8];
	Uint16 _03A_DeviceNumber[6];
	Uint16 _040_CnfNumber[6];
	Uint16 _046_FirmwareVersion[6];
	Uint16 _04C_InverterName[6];
	Uint16 _054_Location[16];
	Uint16 _074_RealTime[4];

	Uint16 _00C9_InverterVoltageNom;
	Uint16 _00CA_InverterPowerNom;
	Uint16 _00CB_PVSystemOperation;
	Uint16 _00CC_NoOfInputSwitch;
	Uint16 _00CD_DC_IsolationMonitoring;
	Uint16 _00CE_NumberOfCANIO;
	Uint16 _00CF_GridFreqSetPointMax;
	Uint16 _00D0_GridFreqSetPointMin;
	Uint16 _00D1_GridVoltSetPointMax;
	Uint16 _00D2_GridVoltSetPointMin;


	Uint16 _012D_Inverter_Operation_State;
	Uint16 _012E_PV_Input_DC_Information;
	Uint16 _012F_PV_Input_DC_Warning;
	Uint16 _0130_PV_Input_DC_Fault;
	Uint16 _0131_PV_Input_DC_Fault_SACK;

	Uint16 _0191_PV_Inverter_Information;
	Uint16 _0192_PV_Inverter_Warning;
	Uint16 _0193_PV_Inverter_Fault;
	Uint16 _0194_PV_Inverter_Fault_SACK;
	Uint16 _01F5_PV_Output_AC_Information;
	Uint16 _01F6_PV_Output_AC_Warning;
	Uint16 _01F7_PV_Output_AC_Fault;
	Uint16 _01F8_PV_Output_AC_Fault_SACK;
	Uint16 _01FE_PV_Cabinet_Door;

	Uint16 _0244_unknown[3];
	Uint16 _0255_unknown[4];


	Uint16 _0259_PV_Voltage;
	Uint16 _025A_PV_Current;
	Uint16 _025B_PV_Power;
	Uint16 _025C_DC_Isolation_Resistor;
	Uint16 _02BD_AmbientAirTemp;
	Uint16 _02BE_CosPhi;
	Uint16 _02BF_InvFrequency;
	Uint16 _02C0_InvVoltL1_L2;
	Uint16 _02C1_InvVoltL2_L3;
	Uint16 _02C2_InvVoltL3_L1;
	Uint16 _02C3_InvCurrentL1;
	Uint16 _02C4_InvCurrentL2;
	Uint16 _02C5_InvCurrentL3;
	Uint16 _02C6_InvTotalApparentPower;
	Uint16 _02C7_InvTotalTruePower;
	Uint16 _02C8_InvTotalReactivePower;
	Uint16 _02C9_DayEnergy;
	Uint16 _02CA_TotalEnergy;
	Uint16 _02CB_TotalEnergy2;
	Uint16 _0321_GridFrequency;
	Uint16 _0322_GridVoltL1_L2;
	Uint16 _0323_GridVoltL2_L3;
	Uint16 _0324_GridVoltL3_L1;
	Uint16 _0385_unknown;
	Uint16 _0386_InvHoursOfOperation;
	Uint16 _0387_FanHoursOfOperationHalfSpeed;
	Uint16 _0388_FanHoursOfOperationFullSpeed;
	Uint16 _0389_CounterOfInvOutputContactor;
	Uint16 _038A_CounterPowerOFFGridFault;

	Uint16 _03E8_Serial_SlaveAddress[6];

	Uint16 _03F2_ResetSetPoint;
	Uint16 _03F3_TruePowerLimitPoint;
	Uint16 _03F4_ReactivePowerSetPoint;
	int16 _03F5_CosPhiSetPointOrBMS_Pref;
	Uint16 _03F6_P_F_Grid_Release;
	Uint16 _03F7_Q_U_Grid_Release;
	Uint16 _03F8_Q_P_Inv_Release;
	Uint16 _03F9_InverterOFF;
	Uint16 _03FA_TruePowerLimitPointRelease;
	Uint16 _03FB_ReactivePowerSetPointRelease;
	Uint16 _03FC_CosPhiSetPointRelease;
	Uint16 _03FD_StartMode;
	Uint16 _03FE_TimerX;
	Uint16 _03FF_TimerY;
	Uint16 _0400_TruePowerLimitPoint;

	Uint16 _0500_BMS_Power_ref;
	Uint16 _0501_BMS_U2_meas;
	Uint16 _0502_BMS_I2_meas;
	Uint16 _0503_BMS_E_charge;
	Uint16 _0504_BMS_status;

	Uint16	_1000_time_H_charge;
	Uint16	_1001_time_H_discharge;
	Uint16	_1002_charge_P;
	Uint16	_1003_discharge_P;
	Uint16	_1004_cmd_word;//0-on,1-0ff,2-trip reset,3-on dcdc,4-off dcdc

	Uint16	_1100_diesel_ready;
	Uint16	_1101_diesel_operating;
	Uint16	_1102_I_diesel;
	Uint16	_1103_P_diesel;
	Uint16	_1104_Profile;

	Uint16	_1105_Invs_off;

	};
//!см. TMBVarsConv	MBVars
#define SMBVARS_DEFAULTS {0}


struct SMBVarsConv{
				struct SMBVars Vars;
				Uint16 NeedForSave;
                void (*init)(volatile struct SMBVarsConv*);
                void (*ms_calc)(volatile struct SMBVarsConv*);
                void (*slow_calc)(volatile struct SMBVarsConv*);
               };

typedef volatile struct SMBVarsConv TMBVarsConv;

//!Инициализатор по умолчанию
#define MBVARSCONV_DEFAULTS { SMBVARS_DEFAULTS,\
				0,\
                MBVarsConv_init,\
                MBVarsConv_ms_calc,\
                MBVarsConv_slow_calc\
                }

//! \memberof TMBVarsConv
void MBVarsConv_init(TMBVarsConv *p);
//! \memberof TMBVarsConv
void MBVarsConv_ms_calc(TMBVarsConv *p);
//! \memberof TMBVarsConv
void MBVarsConv_slow_calc(TMBVarsConv *p);


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
