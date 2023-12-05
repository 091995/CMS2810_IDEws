/*!
    Copyright 2019 A&D
 \file      main.h
 \brief     ������� ������������ ���� �������. 
���������� � ���� ��� ������������ ����� ���� �������,
�������� ���������� (extern) ���� �������� ������
���������� �������� � ����������.

 \author
 \version   v 1.0 23/05/2019

 \defgroup  MAIN ������� ���� �������

@{*/

#ifndef MAIN_H
#define MAIN_H


//#define LAB_MODE_GLOBAL_DEFINE

#ifdef LAB_MODE_GLOBAL_DEFINE
#pragma message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
#pragma message("!!!!!!!!!!!!!LAB_MODE_GLOBAL_DEFINE!!!!!!!!!!!!!!!!!!!!")
#pragma message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
#endif

//����� ���� ���������� �����
//VectorCARD � ���������� ���������� DRV8301
//#define HW_VECTORCARD_DRV8301_EVM
//VectorCARD � ������������� �������� ����������
#define HW_VECTORCARD_SIMULATOR
//��� UART, ���������� ��� ��� ������ - MODBUS ��� CANtoRS ���������
//#define MODBUS_ENA
//#define CANTORS_ENA


#include "DSP.h"
//#include "build.h"
#include <stdlib.h> //��� labs
#include <stdint.h> //��� uintX_t

#include "IQmathLib.h"          // ���������� IQmath
//#include "HAL_drv.h"
//#include "SM_Sys.h"
//#include "SM_Net.h"
//
//
//
//#include "DIO/dio_func.h"
//
//#include "DCS/dcs_func.h"
//
//#include "DDE/dde_func.h"
//
//#include "APL/APL_func.h"
//
//
//
//
//extern TSM_Sys 	sm_sys;
//
//extern TSM_Net sm_net;
//
//extern HAL_ENERGY19 HAL;
//
//extern Uint16 	disp_group_number;
//
//extern Uint16 msCounter;
//extern Uint16 FastCounter;
//extern Uint16 LoopCounter;
//extern Uint16 TIsr10;
//extern Uint16 TIsr1;
//extern int inv_status_code;
//extern Uint32 VendorToken;
//
//volatile extern long Debug1;
//volatile extern long Debug2;
//volatile extern Uint16 Debug3;
//volatile extern Uint16 Debug4;
//volatile extern long DebugW1;
//volatile extern long DebugW2;
//volatile extern long DebugW3;
//volatile extern long DebugW4;
//volatile extern float DebugF1;
//volatile extern float DebugF2;
//volatile extern float DebugF3;
//volatile extern float DebugF4;
//
//
//
//extern unsigned long CpuTimerIsr1;
//
//extern Uint16 delimeter_sign;
//
//extern TCanBTInterface  Can1BTInterface;
//extern TCanBTInterface  Can2BTInterface;

extern void callback_dlog(Uint16 par);
extern void callback_RTC(Uint16 par);

interrupt void EvbTimer4(void);
interrupt void CPUTimer0_isr(void);
interrupt void pdpinta_protect_isr(void);
//interrupt void cap1_interrupt_isr(void);
//interrupt void cap2_interrupt_isr(void);
//interrupt void cap3_interrupt_isr(void);
//interrupt void scib_rx_isr(void);
//interrupt void scia_tx_isr(void);
//
//

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

