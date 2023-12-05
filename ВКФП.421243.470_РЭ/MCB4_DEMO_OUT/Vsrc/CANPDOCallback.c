/* ==================================================================================
   Copyright 2023 ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

//File name:       CANPDOCallback.c

//Description: В файл вынесены функции драйвера CANOpen определяемые пользователем (колбэк функции, функции инициализации и т.п.)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 2017_02_08

//=====================================================================================*/
#include "DSP.h"
#include "co_ODvars.h"
#include "CANOpen_drv.h"
#include "main.h"

#ifdef CAN_RX_PDO_CALLBACK_ENABLE

Uint16 PDO_cntr1 = 0;
Uint16 PDO_cntr2 = 0;
#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO1_Callback,"secureRamFuncs");
#endif
void co_RPDO1_Callback(Uint16 nodeID)
{
	
	switch(nodeID)
	{
		case 1:
		{
			PDO_cntr1++;
			//обрабатываем как нибудь...
			break;
		}
		case 2:
		{
			PDO_cntr2++;
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO2_Callback,"secureRamFuncs");
#endif
void co_RPDO2_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO3_Callback,"secureRamFuncs");
#endif
void co_RPDO3_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO4_Callback,"secureRamFuncs");
#endif
void co_RPDO4_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO5_Callback,"secureRamFuncs");
#endif
void co_RPDO5_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO6_Callback,"secureRamFuncs");
#endif
void co_RPDO6_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO7_Callback,"secureRamFuncs");
#endif
void co_RPDO7_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(co_RPDO8_Callback,"secureRamFuncs");
#endif
void co_RPDO8_Callback(Uint16 nodeID)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//обрабатываем как нибудь...
			break;
		}
		default:
			break;
	}
	*/
}
#endif
