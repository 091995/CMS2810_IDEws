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

 \file		v_MBVarsConv.c
 \brief		Модуль преобразования данных Modbus
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version	v.1.1. 02/03/2017

 \addtogroup v_ModBus */
/*@{*/

#include "main.h"
#include "mbod.h"
#include "math.h" //для fabs
//! Инициализация не требуется
//! \memberof	TMBVarsConv
//!


//int _03E8_Serial_SlaveAddress[6]={70,13,10,19,0,3};
//000012 14:03:58.225  00 10 03 E8 00 060C 3730 3133 3130 3139 3030 3311  63D9
//
//000028 14:11:58.198  00 10 03E8 00 06 0C37 3031 3331 3031 3930 3033 11 63D9


//char _03E8_Serial_SlaveAddress[12]={'7','0','1','3','1','0','1','9','0','0','0','3'};
//char _03E8_Serial_SlaveAddress[12]={'0','7','3','1','0','1','9','1','0','0','3','0'};
//Uint8 _03E8_Serial_SlaveAddress[12]={0x37, 0x30, 0x31, 0x33, 0x31, 0x30, 0x31, 0x39, 0x30, 0x30, 0x33, 0x11};
Uint8 _03E8_Serial_SlaveAddress[12]={0x30, 0x37, 0x33, 0x31, 0x30, 0x31, 0x39, 0x31, 0x30, 0x30, 0x11, 0x33};

Uint8 _0022_Manufacture[16]= {"Manufacture_100"};
Uint8 _032_ModelName[8] = {"ModelNam"};
Uint8 _03A_DeviceNumber[12] = {0x30, 0x37, 0x33, 0x31, 0x30, 0x31, 0x39, 0x31, 0x30, 0x30, 0x11, 0x33};
Uint8 _040_CnfNumber[12] = {0x30, 0x37, 0x33, 0x31, 0x30, 0x31, 0x39, 0x31, 0x30, 0x30, 0x11, 0x33};
Uint8 _046_FirmwareVersion[6] ={"FW_100"};
Uint8 _04C_InverterName[6] ={"Andrei"};
Uint8 _054_Location[16] = {"somewhere_on_"};
Uint8 _074_RealTime[4] ={0x01,0x02,0x08,0x40};
int Prefprev;
//
//		(11 03 08 40 20 13 04 30 08 18 20 92 9C)
//		сек минуты часы 04 день месяц год

void char2word_memcpy(Uint16*p_out,Uint8*v_in,int size)
{
int ii;
Uint16*p=p_out;
for (ii=0;ii<(size>>1);ii++)
	p_out[ii]=((Uint16)(v_in[2*ii+1])|v_in[2*ii]<<8);


}


void MBVarsConv_init(TMBVarsConv *p) {

	memcpy(&p->Vars._03E8_Serial_SlaveAddress,&_03E8_Serial_SlaveAddress,sizeof(p->Vars._03E8_Serial_SlaveAddress));

	char2word_memcpy(&p->Vars._0022_Manufacture,&_0022_Manufacture,sizeof(p->Vars._0022_Manufacture));
	memcpy(&p->Vars._032_ModelName,&_032_ModelName,sizeof(p->Vars._032_ModelName));
	memcpy(&p->Vars._03A_DeviceNumber,&_03A_DeviceNumber,sizeof(p->Vars._03A_DeviceNumber));
	memcpy(&p->Vars._040_CnfNumber,&_040_CnfNumber,sizeof(p->Vars._040_CnfNumber));
	memcpy(&p->Vars._046_FirmwareVersion,&_046_FirmwareVersion,sizeof(p->Vars._046_FirmwareVersion));
	memcpy(&p->Vars._04C_InverterName,&_04C_InverterName,sizeof(p->Vars._04C_InverterName));
	memcpy(&p->Vars._054_Location,&_054_Location,sizeof(p->Vars._054_Location));
	memcpy(&p->Vars._074_RealTime,&_074_RealTime,sizeof(p->Vars._074_RealTime));

	MBVarsConv.Vars._03F3_TruePowerLimitPoint=2550;
	cmd_logic.refs.P_ref=255;
	Prefprev=255;
}


static short _0500_BMS_Power_ref_prev=0;
static short _03F5_CosPhiSetPointOrBMS_Pref_prev=0;
static short _invs_off_prev=0;
//! Основная процедура

//! Вход в .input, выход в .output
//! Кривая задается массивом из NumOfPoints точек по x и по y.
//! \memberof	TMBVarsConv
//!
int _counter_HR = 0;
void MBVarsConv_ms_calc(TMBVarsConv *p) {
	float number, scale, scaled;
	long i, index;

	if (ModBus.Enabled == 1){ // Если включен MODBUS
		//Для уменьшения вычислительной нагрузки в случае необходимости можно убрать цикл for и проверять по одному элементу за один заход
		//for (i = 0; i < ModBus.MBInternals.NumOfHRs; i++)// Проверяем все элементы словаря HR (редактируемых параметров)
		_counter_HR++;
		if (_counter_HR>=ModBus.MBInternals.NumOfHRs) _counter_HR=0;
		i=_counter_HR;

			if (mbodHR[i].type_or_acc == 1){// Если параметр менялся, то анализируем, как его преобразовать

				mbodHR[i].type_or_acc = 0;		// Сбрасываем флаг изменения параметра
				index = mbodHR[i].index;		//какой индекс меняли

//				if ((index != 2000) && (index != 2001))	//если не 2000 и не 2001, то нужно сохранить параметры
//					p->NeedForSave = 1;//Нужно не злоупотреблять этой командой, иначе вся пользовательская память сотрется до дыр!

				//В зависимости от того, какой индекс словаря поменялся, выполняем нужное преобразование.
				//На каждую проверку индекса тратится 3 такта. Если проверок будет очень много,
				//то логично дополнить драйвер функциями обратного вызова при обращении к параметру
				switch (index){
//					case 1011:
//						cmd_logic.remote_refs.P_ref=_IQ(MBVarsConv.Vars._03F3_TruePowerLimitPoint/2550.0);
//						DebugW3=MBVarsConv.Vars._03F3_TruePowerLimitPoint;
//						break;
					case 4096:
						dcdc.abc.time_H_charge = MBVarsConv.Vars._1000_time_H_charge;
						break;
					case 4097:
						dcdc.abc.time_H_discharge = MBVarsConv.Vars._1001_time_H_discharge;
						break;
					case 4098:
						dcdc.abc.charge_P = MBVarsConv.Vars._1002_charge_P;
						break;
					case 4099:
						dcdc.abc.discharge_P = MBVarsConv.Vars._1003_discharge_P;
						break;

//					case 2000://слово управления
//						//если значение поля команда изменилось по сравнению с предыдущим
//						if (p->Vars.Command!=p->Vars.CommandPrev){
//
//							// incorrect module usage -
//							//if (p->Vars.Command & (1<<0))//команда на запуск
//								//cmd.bit.start = 1;
//							//if (p->Vars.Command & (1<<1))//команда на останов
//								//cmd.bit.stop = 1;
//							//if (p->Vars.Command & (1<<2))//команда на сброс аварии
//								// cmd.bit.trip_reset = 1;
//
//						}
//						p->Vars.CommandPrev=p->Vars.Command;
//						break;
//
//					case  2001:  // текущая частота вращения
//						//number = (float) p->Vars.speed_ref;
//						number = fabs(number);
//						scale = (float) co2_vars.co_scaleNum14;	// Частота вращения (об/мин) 16.0
//						scaled = number / scale;
//
//						// incorrect Modbus
//						//refs.speed_ref = _IQ(scaled);
//						break;
//
//					case 0x3F3:
//						//cmd_logic.remote_refs.P_ref=MBVarsConv.Vars._03F3_TruePowerLimitPoint;
//						break;
//
//					case 43116: //напряжение защиты в вольтах
//						//number = (float) MBVarsConv.Vars.Umax_protect;
//						scale = (float) co2_vars.co_scaleNum7;	//напряжение ЗПТ базовое
//						scaled = number / scale;
//						dcs_prot.Udc_max = _IQ(scaled);
//						break;

					}
			} //end if (mbodHR[i].type_or_acc == 1)
	}


	//MXI - some adjsutment for power limit which is not according A&D architecture
	//TODO use remote/local selector in cmd_logig  than set it for cmd_logic.regs.P_ref and than use in DCS
	//pid_Udc.pid_out_max=_IQ((MBVarsConv.Vars._03F3_TruePowerLimitPoint/2550.0)*0.93);//Ограничение мощности

//	WAS EXCLUDED 12.10.21
//	if (mbodHR[103].type_or_acc == 1)
//	{
//		mbodHR[103].type_or_acc = 0;
//		cmd_logic.remote_refs.P_ref=_IQ(MBVarsConv.Vars._03F3_TruePowerLimitPoint/2550.0);
//		DebugW3=MBVarsConv.Vars._03F3_TruePowerLimitPoint;
//	}




	//A&D May 2021 this was excluded and moved to cmd_logic
	//Берем значение ограничения мощности в предыдущий момент времени и текущий. Если значение поменялось, то пишем это в
	//регистр. После этого считываем значение в Unicon всегда.


	if(MBVarsConv.Vars._03F3_TruePowerLimitPoint!=Prefprev)
		cmd_logic.remote_refs.P_ref=_IQ(MBVarsConv.Vars._03F3_TruePowerLimitPoint/2550.0);

	MBVarsConv.Vars._03F3_TruePowerLimitPoint = (_IQmpy(cmd_logic.remote_refs.P_ref,inv_params.P_nom)>>16)*10;
	Prefprev=MBVarsConv.Vars._03F3_TruePowerLimitPoint;


	if(MBVarsConv.Vars._1105_Invs_off!=_invs_off_prev)
		sm_isla_batt_diesel.invs_off = MBVarsConv.Vars._1105_Invs_off;

	_invs_off_prev = MBVarsConv.Vars._1105_Invs_off;

	//DebugW1=MBVarsConv.Vars._03F4_ReactivePowerSetPoint;
	//DebugW2=MBVarsConv.Vars._03FB_ReactivePowerSetPointRelease;
	//DebugW4=MBVarsConv.Vars._03FA_TruePowerLimitPointRelease;

	if (MBVarsConv.Vars._03F5_CosPhiSetPointOrBMS_Pref!=_03F5_CosPhiSetPointOrBMS_Pref_prev)
		 cmd_logic.remote_refs.P_dcdc_ref = (_IQ(MBVarsConv.Vars._03F5_CosPhiSetPointOrBMS_Pref*256.0)>>16);

	MBVarsConv.Vars._03F5_CosPhiSetPointOrBMS_Pref=((int)((int)cmd_logic.remote_refs.P_dcdc_ref)>>8);//was *100
	_03F5_CosPhiSetPointOrBMS_Pref_prev=MBVarsConv.Vars._03F5_CosPhiSetPointOrBMS_Pref;


//
//	if (MBVarsConv.Vars._0500_BMS_Power_ref!=_0500_BMS_Power_ref_prev)
//	 cmd_logic.remote_refs.P_BMS_ref = (_IQ(MBVarsConv.Vars._0500_BMS_Power_ref*256.0)>>16);

	MBVarsConv.Vars._0500_BMS_Power_ref = ((int)((int)cmd_logic.remote_refs.P_dcdc_ref)>>8);//was *100
	// _0500_BMS_Power_ref_prev=MBVarsConv.Vars._0500_BMS_Power_ref;

	 MBVarsConv.Vars._0501_BMS_U2_meas = dcdc.regs.U2_meas_V_I12Q4>>4;
	 MBVarsConv.Vars._0502_BMS_I2_meas = dcdc.regs.I2_meas_A_I12Q4>>4;
	 MBVarsConv.Vars._0503_BMS_E_charge = dcdc.regs.E_charge_persent;
	 MBVarsConv.Vars._0504_BMS_status = dcdc.status;

//	Prefprev=cmd_logic.refs.P_ref;


	// Для наблюдаемых преобразование запускаем всегда
// 40002
	// incorrect Modbus
	//number = _IQtoF(cur_par.speed);
//	scale = (float) co2_vars.co_scaleNum14;	// Частота вращения (об/мин)
//	scaled = scale * number;
	// incorrect Modbus
	//p->Vars.CurSpeed = scaled;

// 40007
//	number = _IQtoF(cur_par.Idc_meas); 		//TODO OK changed by A&D
//	scale = (float) co2_vars.co_scaleNum4;	//Ток фазный базовый
//	scaled = scale * number;
	// incorrect Modbus
	//p->Vars.CurIs = scaled;

// 40054
	//p->Vars.Main_ErrorCode = apl.protect_Code; //код текущей аварии (листается, если несколько)
}


void MBVarsConv_slow_calc(TMBVarsConv *p) {
	if (p->NeedForSave) {//команда на сохранение параметров привода через модбас
		p->NeedForSave = 0;

		//сохраняем посредством драйвера CANopen (все его параметры)
		//вызывая функцию сохранения с разными диапазонами, перебирая их все.
//		co_ODexpositor_paramConservation(&co2_vars, 1, 1);
//		co_ODexpositor_paramConservation(&co2_vars, 2, 1);
//		co_ODexpositor_paramConservation(&co2_vars, 3, 1);
//		co_ODexpositor_paramConservation(&co2_vars, 1, 2);
//		co_ODexpositor_paramConservation(&co2_vars, 2, 2);
//		co_ODexpositor_paramConservation(&co2_vars, 3, 2);
//
//		co_ODexpositor_paramConservation(&co2_vars, 1, 3);
//		co_ODexpositor_paramConservation(&co2_vars, 2, 3);
//		co_ODexpositor_paramConservation(&co2_vars, 3, 3);
//		co_ODexpositor_paramConservation(&co2_vars, 1, 4);
//		co_ODexpositor_paramConservation(&co2_vars, 2, 4);
//		co_ODexpositor_paramConservation(&co2_vars, 3, 4);
//		co_ODexpositor_paramConservation(&co2_vars, 1, 5);
//		co_ODexpositor_paramConservation(&co2_vars, 2, 5);
//		co_ODexpositor_paramConservation(&co2_vars, 3, 5);
	}
}

/*@}*/

