/*!
    Copyright 2023 ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      main.h
 \brief     ������� ������������ ���� �������. 
���������� � ���� ��� ������������ ����� ���� �������,
�������� ���������� (extern) ���� �������� ������
���������� �������� � ����������.

 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  MAIN ������� ���� �������

@{*/

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif


#include "DSP.h"
#include "build.h"
#include "V_common.h"
#include <stdlib.h> //��� labs
#include "IQmathLib.h"          // ���������� IQmath
#include "SM_Sys.h"
#include "SM_Net.h"
#include "co_ODvars.h"
#include "CANOpen_drv.h"
#include "V_data_log.h"
#include "SM_Protect.h"
#include "V_bits_to_enum_numbers.h"
#include "SM_Ctrl.h"
#include "SM_CmdLogic.h"
#include "V_RTC_Clock.h"
#include "clarke.h"
#include "park.h"
#include "ipark.h"
#include "V_pid_reg3.h"
#include "V_pid_reg3_pos.h"
#include "V_rmp_ctrl.h"
#include "V_adc.h"
#include "V_PWM_Module.h"
#include "V_CurPar.h"
#include "V_hzprof.h"
#include "V_DPR_eCAP.h"
#include "V_QEP.h"
#include "V_led.h"
#include "V_AutoOffset.h"
#include "V_SSI_Encoder.h"
#include "V_UserMemory.h"
#include "V_rotor_observer.h"
#include "V_relay_reg.h"
#include "V_ModBus.h"
//#include "V_MBVarsConv.h"
#include "V_excitation.h"
#include "X_CANFlashProgData.h"
#include "X_CANFlashProgStarter.h"
#include "CANBlockTransferInterface.h"
#include "DRV_INTERFACE.h"
#include "V_event_log.h"
#include "Global_time.h"
#include "V_UdControl.h"
#include "V_DIO.h"
#include "V_fifo.h"
#include "V_Fan.h"
#include "V_CANtoRS.h"
#include "V_MBVarsConv.h"

extern Uint16 secureRamFuncs_loadstart;
extern Uint16 secureRamFuncs_loadend;
extern Uint16 secureRamFuncs_runstart;

extern Uint16 secureMathFuncs_loadstart;
extern Uint16 secureMathFuncs_loadend;
extern Uint16 secureMathFuncs_runstart;


extern TClarke 		clarke;
extern TPark 		park;
extern TIPark 		ipark;
extern TPidReg3 	pid_id;
extern TPidReg3 	pid_iq;
extern TPidReg3 	pid_ia;
extern TPidReg3 	pid_spd;
extern TPidReg3_pos 	pid_pos;
extern TRelayReg i_a_reg;
extern TRelayReg i_b_reg;
extern TRelayReg i_c_reg;
extern TSM_Sys 		sm_sys;
extern Uint16 disp_group_number;
extern TDataLog dlog;
extern TSM_Protect sm_prot;
extern TCmd	  cmd;
extern TDrvStatus drv_status;
extern TBitsToEnumNums pult_faults_lister;
extern TSM_Ctrl sm_ctrl;
extern TSM_CmdLogic sm_cmd_logic;
extern TRefs refs;
extern TSM_Net sm_net;
extern TRMPCtrl rmp;
extern TDrvParams drv_params;
extern TAdcDrv  adc;
extern TPWM_Module pwm;
extern TCurPar cur_par;
extern TVhzProf vhz;
extern TDPReCAP	DPReCAP;
extern TEncoder posspeedEqep;
extern TRTCClock	RTCclock;
extern TAutoOffset AutoOffset;
extern TSSI_Encoder SSI_Encoder;
extern TRotorObserver RotorObserver;
//extern TCANtoRS CANtoRS;

extern TModBus    ModBus;
extern MODBUS_INT         MBInternals;
extern MODBUS_RS          ModBusRS;
extern TMBVarsConv MBVarsConv;

extern TCANtoRS CANtoRS;

//extern TMBVarsConv MBVarsConv;
extern Texcitation pwm_ex;
extern TCanBTInterface 	Can2BTInterface;
extern TDrvInterface drv_interface;
extern TLogger		FaultLog;
extern TGlobalTime global_time;
extern TUdControl udControl;
extern TFanControl FanControl;

extern Uint32 msCounter;
extern Uint32 FastCounter;
extern Uint16 LoopCounter;
extern Uint32 TIsr10;
extern Uint32 TIsr1;
extern int drv_status_code;
extern Uint32 VendorToken;

volatile extern long Debug1;
volatile extern long Debug2;
volatile extern Uint16 Debug3;
volatile extern Uint16 Debug4;
volatile extern long DebugW1;
volatile extern long DebugW2;
volatile extern long DebugW3;
volatile extern long DebugW4;
volatile extern float DebugF1;
volatile extern float DebugF2;
volatile extern float DebugF3;
volatile extern float DebugF4;

//�������� ���������� ������ �������
extern Uint16 CounterCAP_isr;
extern Uint16 cap0_counter;
extern Uint16 cap1_counter;
extern Uint16 cap2_counter;

extern Uint32 CpuTimerIsr1;
extern TSysSwitches   sw;

extern TSpiMem 		spimem;
extern Tled leds;
extern TCanBTInterface  Can1BTInterface;
extern TCanBTInterface  Can2BTInterface;
//extern TCANSpeedTableOptions canSpeedTable;

extern TPDO_PACK_1 TPDO_pack1;
extern TPDO_PACK_2 TPDO_pack2;
extern TPDO_PACK_3 TPDO_pack3;
extern TPDO_PACK_4 TPDO_pack4;
extern TPDO_PACK_1 RPDO_pack3;
extern RPDO_PACK_1 RPDO_pack1;
extern RPDO_PACK_2 RPDO_pack2;

extern void callback_dlog(Uint16 par);
extern void callback_RTC(Uint16 par);

interrupt void EvbTimer4(void);
interrupt void cap1_interrupt_isr(void);
interrupt void cap2_interrupt_isr(void);
interrupt void cap3_interrupt_isr(void);
interrupt void scib_rx_isr(void);
interrupt void scia_tx_isr(void);

interrupt void pdpinta_protect_isr(void);

interrupt void CPUTimer0_isr(void);


#if defined(TRUE) && (TRUE != 1)
#error "TRUE previously defined not equal to 1"
#endif
#if defined(FALSE) && (FALSE != 0)
#error "FALSE previously defined not equal to 0"
#endif
#ifndef TRUE
#define TRUE  (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#ifdef __cplusplus
}
#endif

#endif
/*@}*/

