/*
 * dde_func.h
 *
 *  Created on: 9 θών. 2019 γ.
 *      Author: admin
 */

#ifndef DDE_DDE_FUNC_H_
#define DDE_DDE_FUNC_H_


#include "DDE/V_data_log.h"
#include "DDE/V_RTC_Clock.h"
#include "DDE/V_bits_to_enum_numbers.h"
#include "co_ODvars.h"
#include "CANOpen_drv.h"
#include "DDE/V_UserMemory.h"
//#include "DDE/V_CANtoRS.h"
#include "DDE/V_ModBus.h"
#include "DDE/V_MBVarsConv.h"
//#include "DDE/X_CANFlashProgData.h"
//#include "DDE/X_CANFlashProgStarter.h"
#include "DDE/CANBlockTransferInterface.h"
#include "DRV_INTERFACE.h"
#include "DDE/V_event_log.h"
#include "DDE/Global_time.h"

#include "DDE/RS_terminal.h"

//#include "DDE/can_init.h"
#include "DDE/canopen_mini.h"



extern TRTCClock	RTCclock;
//extern TCANtoRS CANtoRS;
extern TModBus ModBus;
extern TMBVarsConv MBVarsConv;

extern TCanBTInterface 	Can2BTInterface;
extern TDrvInterface drv_interface;
extern TLogger		FaultLog;
extern TGlobalTime global_time;
extern TDataLog dlog;
//extern TCmd	  cmd;
extern TBitsToEnumNums pult_protect_lister;
extern TBitsToEnumNums pult_alarm_lister;

extern TUserMemory 		UserMem;

extern TERMINAL terminal;

extern TCANOPEN_MINI can_mini;
//extern TCANSpeedTableOptions canSpeedTable;

#endif /* DDE_DDE_FUNC_H_ */
