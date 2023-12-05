/*!
    Copyright 2019 A&D
 \file      main.h
 \brief     Главный заголовочный файл проекта. 
Подключает в себе все заголовочные файлы всех модулей,
Содержит объявления (extern) всех наиболее важных
глобальных структур и переменных.

 \author
 \version   v 1.0 23/05/2019

 \defgroup  MAIN Главный файл проекта

@{*/

#ifndef MAIN_H
#define MAIN_H


//#define LAB_MODE_GLOBAL_DEFINE

#ifdef LAB_MODE_GLOBAL_DEFINE
#pragma message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
#pragma message("!!!!!!!!!!!!!LAB_MODE_GLOBAL_DEFINE!!!!!!!!!!!!!!!!!!!!")
#pragma message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
#endif

//Выбор типа аппаратной части
//VectorCARD с отладочным комплектом DRV8301
//#define HW_VECTORCARD_DRV8301_EVM
//VectorCARD с имитационными моделями двигателей
#define HW_VECTORCARD_SIMULATOR
//Для UART, выбирается чем его занять - MODBUS или CANtoRS драйвером
#define MODBUS_ENA
//#define CANTORS_ENA


#include "DSP.h"
//#include "build.h"
#include <stdlib.h> //для labs
#include <stdint.h> //для uintX_t

#include "IQmathLib.h"          // библиотека IQmath
#include "HAL_drv.h"
#include "SM_Sys.h"
#include "SM_Net.h"



#include "DIO/dio_func.h"

#include "DCS/dcs_func.h"

#include "DDE/dde_func.h"

#include "APL/APL_func.h"




extern TSM_Sys 	sm_sys;

extern TSM_Net sm_net;

extern HAL_ENERGY19 HAL;

extern Uint16 Nikita;

extern Uint16 	disp_group_number;

extern Uint16 msCounter;
extern Uint16 FastCounter;
extern Uint16 LoopCounter;
extern Uint16 TIsr10;
extern Uint16 TIsr1;
extern int inv_status_code;
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



extern unsigned long CpuTimerIsr1;

extern Uint16 delimeter_sign;

extern TCanBTInterface  Can1BTInterface;
extern TCanBTInterface  Can2BTInterface;

void callback_dlog(Uint16 par, Uint16 tag_CANnum);
void callback_RTC(Uint16 par, Uint16 tag_CANnum);
void propReset(void);

// Объявление ISR-ов. В CodeMaster-ском и GCC-шном стартапе они назиываются по-разному
#if defined (__GNUC__)
void TIM1_IRQHandler(void);
void TIM0_IRQHandler(void);
void EPWM_TZ_0_IRQHandler(void);
void ECAP0_IRQHandler(void);
void ECAP1_IRQHandler(void);
void ECAP2_IRQHandler(void);
void EQEP1_IRQHandler(void);
#elif defined (__CMCPPARM__)
void TIM1_IRQHandler(void);
void TIM0_IRQHandler(void);
void PWM0_TZ_IRQHandler(void);
void CAP0_IRQHandler(void);
void CAP1_IRQHandler(void);
void CAP2_IRQHandler(void);
void QEP1_IRQHandler(void);
#endif

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


#endif
/*@}*/

