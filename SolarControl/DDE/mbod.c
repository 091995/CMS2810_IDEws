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

 \file      mbod.c
 \brief     Словарь объектов MODBUS
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2017

*/

/** \addtogroup MODBUS */
/*@{*/

#include "mbod.h"
#include "main.h"


/* Тестовые посылки
 * Формат байт в посылке:
 * Номер узла 1 байт, функция 1 байт, адрес 2 байта, данные/кол-во переменных 2 байта, контрольная сумма CRC16(LH)
 * Удобно тестировать, например, программой COMpump
 *
01 06 07 D0 00 01 48 87  - запустить привод (запись в 2000 значения 1)
01 06 07 D1 00 64 D9 6C - задать частоту вращения (2001) равной 100 об/мин
01 06 A8 6C 00 64 68 5C - задать защиту по напряжению Udc равной 100В

01 03 9C 42 00 01 0A 4E - запрос текущей частоты вращения
01 03 9C 76 00 01 4B 80	- запрос кодов аварий


В массивах:
mbodHR - переменные Holding Registers (на чтение и запись). Код функции	0x03(на чтение) 0x06(на запись)
mbodIR - переменные Input Registers (на чтение). Код функции	0x04
mbodC - битовые переменные Coil (для записи). Код функции 0x05(на запись)
mbodDI - битовые переменные Discrete Inputs (для чтения). Код функции 0x02(на чтение)

Первая цифра массива - адрес переменной в словаре  ModBus.
Вторая - номер бита для битовых переменных в переменной контроллера.
Третья - адрес переменной.


*/

//this is example
//volatile MB_Record mbodHR[] = {\
//		2000,  0,(long)(&MBVarsConv.Vars.Command),/*Слово управления. 0й бит - пуск, 1й бит - стоп, 2й бит - сброс аварии */\
//		2001,  0,(long)(&MBVarsConv.Vars.speed_ref), /*Задание частоты вращения в об/мин*/\
//		40002, 0,(long)(&MBVarsConv.Vars.CurSpeed),/* Текущая частота вращения (об/мин) */\
//		40007, 0,(long)(&MBVarsConv.Vars.CurIs),/*Ток статора амплитудный (А)*/\
//		40054, 0,(long)(&MBVarsConv.Vars.Main_ErrorCode),/*Код аварии (сменяется, если аварий несколько)*/\
//		43116,  0,(long)(&MBVarsConv.Vars.Umax_protect),/*Уставка макс. напряж ЗПТ*/\
//        0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
//};

volatile MB_Record mbodHR[] = {\
		0x0022,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[0]),\
		0x0023,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[1]),\
		0x0024,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[2]),\
		0x0025,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[3]),\
		0x0026,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[4]),\
		0x0027,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[5]),\
		0x0028,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[6]),\
		0x0029,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[7]),\
		0x002A,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[8]),\
		0x002B,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[9]),\
		0x002C,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[10]),\
		0x002D,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[11]),\
		0x002E,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[12]),\
		0x002F,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[13]),\
		0x0030,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[14]),\
		0x0031,  0,(long)(&MBVarsConv.Vars._0022_Manufacture[15]),\

		0x0032,  0,(long)(&MBVarsConv.Vars._032_ModelName[0]),\
		0x003A,  0,(long)(&MBVarsConv.Vars._03A_DeviceNumber[0]),\
		0x003B,  0,(long)(&MBVarsConv.Vars._03A_DeviceNumber[1]),\
		0x003C,  0,(long)(&MBVarsConv.Vars._03A_DeviceNumber[2]),\
		0x003D,  0,(long)(&MBVarsConv.Vars._03A_DeviceNumber[3]),\
		0x003E,  0,(long)(&MBVarsConv.Vars._03A_DeviceNumber[4]),\
		0x003F,  0,(long)(&MBVarsConv.Vars._03A_DeviceNumber[5]),\
		0x0040,  0,(long)(&MBVarsConv.Vars._040_CnfNumber[0]),\
		0x0041,  0,(long)(&MBVarsConv.Vars._040_CnfNumber[1]),\
		0x0042,  0,(long)(&MBVarsConv.Vars._040_CnfNumber[2]),\
		0x0043,  0,(long)(&MBVarsConv.Vars._040_CnfNumber[3]),\
		0x0044,  0,(long)(&MBVarsConv.Vars._040_CnfNumber[4]),\
		0x0045,  0,(long)(&MBVarsConv.Vars._040_CnfNumber[5]),\
		0x0046,  0,(long)(&MBVarsConv.Vars._046_FirmwareVersion[0]),\
		0x004C,  0,(long)(&MBVarsConv.Vars._04C_InverterName[0]),\
		0x0054,  0,(long)(&MBVarsConv.Vars._054_Location[0]),\
		0x0074,  0,(long)(&MBVarsConv.Vars._074_RealTime[0]),\
		0x0075,  0,(long)(&MBVarsConv.Vars._074_RealTime[1]),\
		0x0076,  0,(long)(&MBVarsConv.Vars._074_RealTime[2]),\
		0x0077,  0,(long)(&MBVarsConv.Vars._074_RealTime[3]),\
		0x00C9,  0,(long)(&MBVarsConv.Vars._00C9_InverterVoltageNom),\
		0x00CA,  0,(long)(&MBVarsConv.Vars._00CA_InverterPowerNom),\
		0x00CB,  0,(long)(&MBVarsConv.Vars._00CB_PVSystemOperation),\
		0x00CC,  0,(long)(&MBVarsConv.Vars._00CC_NoOfInputSwitch),\
		0x00CD,  0,(long)(&MBVarsConv.Vars._00CD_DC_IsolationMonitoring),\
		0x00CE,  0,(long)(&MBVarsConv.Vars._00CE_NumberOfCANIO),\
		0x00CF,  0,(long)(&MBVarsConv.Vars._00CF_GridFreqSetPointMax),\
		0x00D0,  0,(long)(&MBVarsConv.Vars._00D0_GridFreqSetPointMin),\
		0x00D1,  0,(long)(&MBVarsConv.Vars._00D1_GridVoltSetPointMax),\
		0x00D2,  0,(long)(&MBVarsConv.Vars._00D2_GridVoltSetPointMin),\


		0x012D,  0,(long)(&MBVarsConv.Vars._012D_Inverter_Operation_State),\
		0x012E,  0,(long)(&MBVarsConv.Vars._012E_PV_Input_DC_Information),\
		0x012F,  0,(long)(&MBVarsConv.Vars._012F_PV_Input_DC_Warning),\
		0x0130,  0,(long)(&MBVarsConv.Vars._0130_PV_Input_DC_Fault),\
		0x0131,  0,(long)(&MBVarsConv.Vars._0131_PV_Input_DC_Fault_SACK),\

		0x0191,  0,(long)(&MBVarsConv.Vars._0191_PV_Inverter_Information),\
		0x0192,  0,(long)(&MBVarsConv.Vars._0192_PV_Inverter_Warning),\
		0x0193,  0,(long)(&MBVarsConv.Vars._0193_PV_Inverter_Fault),\
		0x0194,  0,(long)(&MBVarsConv.Vars._0194_PV_Inverter_Fault_SACK),\
		0x01F5,  0,(long)(&MBVarsConv.Vars._01F5_PV_Output_AC_Information),\
		0x01F6,  0,(long)(&MBVarsConv.Vars._01F6_PV_Output_AC_Warning),\
		0x01F7,  0,(long)(&MBVarsConv.Vars._01F7_PV_Output_AC_Fault),\
		0x01F8,  0,(long)(&MBVarsConv.Vars._01F8_PV_Output_AC_Fault_SACK),\
		0x01FE,  0,(long)(&MBVarsConv.Vars._01FE_PV_Cabinet_Door),\

		0x0244, 0,(long)(&MBVarsConv.Vars._0244_unknown[0]),\
		0x0245, 0,(long)(&MBVarsConv.Vars._0244_unknown[1]),\
		0x0246, 0,(long)(&MBVarsConv.Vars._0244_unknown[2]),\

		0x0255, 0,(long)(&MBVarsConv.Vars._0255_unknown[0]),\
		0x0256, 0,(long)(&MBVarsConv.Vars._0255_unknown[1]),\
		0x0257, 0,(long)(&MBVarsConv.Vars._0255_unknown[2]),\
		0x0258, 0,(long)(&MBVarsConv.Vars._0255_unknown[3]),\


		0x0259,  0,(long)(&MBVarsConv.Vars._0259_PV_Voltage),\
		0x025A,  0,(long)(&MBVarsConv.Vars._025A_PV_Current),\
		0x025B,  0,(long)(&MBVarsConv.Vars._025B_PV_Power),\
		0x025C,  0,(long)(&MBVarsConv.Vars._025C_DC_Isolation_Resistor),\
		0x02BD,  0,(long)(&MBVarsConv.Vars._02BD_AmbientAirTemp),\
		0x02BE,  0,(long)(&MBVarsConv.Vars._02BE_CosPhi),\
		0x02BF,  0,(long)(&MBVarsConv.Vars._02BF_InvFrequency),\
		0x02C0,  0,(long)(&MBVarsConv.Vars._02C0_InvVoltL1_L2),\
		0x02C1,  0,(long)(&MBVarsConv.Vars._02C1_InvVoltL2_L3),\
		0x02C2,  0,(long)(&MBVarsConv.Vars._02C2_InvVoltL3_L1),\
		0x02C3,  0,(long)(&MBVarsConv.Vars._02C3_InvCurrentL1),\
		0x02C4,  0,(long)(&MBVarsConv.Vars._02C4_InvCurrentL2),\
		0x02C5,  0,(long)(&MBVarsConv.Vars._02C5_InvCurrentL3),\
		0x02C6,  0,(long)(&MBVarsConv.Vars._02C6_InvTotalApparentPower),\
		0x02C7,  0,(long)(&MBVarsConv.Vars._02C7_InvTotalTruePower),\
		0x02C8,  0,(long)(&MBVarsConv.Vars._02C8_InvTotalReactivePower),\
		0x02C9,  0,(long)(&MBVarsConv.Vars._02C9_DayEnergy),\
		0x02CA,  0,(long)(&MBVarsConv.Vars._02CA_TotalEnergy),\
		0x02CB,  0,(long)(&MBVarsConv.Vars._02CB_TotalEnergy2),\
		0x0321,  0,(long)(&MBVarsConv.Vars._0321_GridFrequency),\
		0x0322,  0,(long)(&MBVarsConv.Vars._0322_GridVoltL1_L2),\
		0x0323,  0,(long)(&MBVarsConv.Vars._0323_GridVoltL2_L3),\
		0x0324,  0,(long)(&MBVarsConv.Vars._0324_GridVoltL3_L1),\
		0x0385,  0,(long)(&MBVarsConv.Vars._0385_unknown),\
		0x0386,  0,(long)(&MBVarsConv.Vars._0386_InvHoursOfOperation),\
		0x0387,  0,(long)(&MBVarsConv.Vars._0387_FanHoursOfOperationHalfSpeed),\
		0x0388,  0,(long)(&MBVarsConv.Vars._0388_FanHoursOfOperationFullSpeed),\
		0x0389,  0,(long)(&MBVarsConv.Vars._0389_CounterOfInvOutputContactor),\
		0x038A,  0,(long)(&MBVarsConv.Vars._038A_CounterPowerOFFGridFault),\

		0x03E8,  0,(long)(&MBVarsConv.Vars._03E8_Serial_SlaveAddress[0]),\
		0x03E9,  0,(long)(&MBVarsConv.Vars._03E8_Serial_SlaveAddress[1]),\
		0x03EA,  0,(long)(&MBVarsConv.Vars._03E8_Serial_SlaveAddress[2]),\
		0x03EB,  0,(long)(&MBVarsConv.Vars._03E8_Serial_SlaveAddress[3]),\
		0x03EC,  0,(long)(&MBVarsConv.Vars._03E8_Serial_SlaveAddress[4]),\
		0x03ED,  0,(long)(&MBVarsConv.Vars._03E8_Serial_SlaveAddress[5]),\


		0x03F2,  0,(long)(&MBVarsConv.Vars._03F2_ResetSetPoint),\
		0x03F3,  0,(long)(&MBVarsConv.Vars._03F3_TruePowerLimitPoint),\
		0x03F4,  0,(long)(&MBVarsConv.Vars._03F4_ReactivePowerSetPoint),\
		0x03F5,  0,(long)(&MBVarsConv.Vars._03F5_CosPhiSetPointOrBMS_Pref),\
		0x03F6,  0,(long)(&MBVarsConv.Vars._03F6_P_F_Grid_Release),\
		0x03F7,  0,(long)(&MBVarsConv.Vars._03F7_Q_U_Grid_Release),\
		0x03F8,  0,(long)(&MBVarsConv.Vars._03F8_Q_P_Inv_Release),\
		0x03F9,  0,(long)(&MBVarsConv.Vars._03F9_InverterOFF),\
		0x03FA,  0,(long)(&MBVarsConv.Vars._03FA_TruePowerLimitPointRelease),\
		0x03FB,  0,(long)(&MBVarsConv.Vars._03FB_ReactivePowerSetPointRelease),\
		0x03FC,  0,(long)(&MBVarsConv.Vars._03FC_CosPhiSetPointRelease),\
		0x03FD,  0,(long)(&MBVarsConv.Vars._03FD_StartMode),\
		0x03FE,  0,(long)(&MBVarsConv.Vars._03FE_TimerX),\
		0x03FF,  0,(long)(&MBVarsConv.Vars._03FF_TimerY),\
		0x0400,  0,(long)(&MBVarsConv.Vars._0400_TruePowerLimitPoint),\

		0x0500,	0,(long)(&MBVarsConv.Vars._0500_BMS_Power_ref),\
		0x0501,	0,(long)(&MBVarsConv.Vars._0501_BMS_U2_meas),\
		0x0502,	0,(long)(&MBVarsConv.Vars._0502_BMS_I2_meas),\
		0x0503,	0,(long)(&MBVarsConv.Vars._0503_BMS_E_charge),\
		0x0504,	0,(long)(&MBVarsConv.Vars._0504_BMS_status),\

		0x1000,	0,(long)(&MBVarsConv.Vars._1000_time_H_charge),\
		0x1001,	0,(long)(&MBVarsConv.Vars._1001_time_H_discharge),\
		0x1002,	0,(long)(&MBVarsConv.Vars._1002_charge_P),\
		0x1003,	0,(long)(&MBVarsConv.Vars._1003_discharge_P),\

		0x1004,	0,(long)(&MBVarsConv.Vars._1004_cmd_word),\

		0x1100,	0,(long)(&MBVarsConv.Vars._1100_diesel_ready),\
		0x1101,	0,(long)(&MBVarsConv.Vars._1101_diesel_operating),\
		0x1102,	0,(long)(&MBVarsConv.Vars._1102_I_diesel),\
		0x1103,	0,(long)(&MBVarsConv.Vars._1103_P_diesel),\
		0x1104,	0,(long)(&MBVarsConv.Vars._1104_Profile),\
		0x1105,	0,(long)(&MBVarsConv.Vars._1105_Invs_off),\

        0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
};
volatile MB_Record mbodIR[] = {\
                           	0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
                           	};

volatile MB_Record mbodC[] =  {\
                           	0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
                            };



volatile MB_Record mbodDI[] =  {0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
                          	};

/*@}*/
