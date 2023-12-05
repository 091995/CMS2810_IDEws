/*!
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

 \file      SM_Net.h
 \brief     Модуль сетевых интерфейсов
 \author    ООО "НПФ Вектор". http://motorcontrol.ru

*/

/* ==================================================================================
 File name:        SM_NET.h

 -----------------------------------------------------------------------------*/
#ifndef SM_NET_H
#define SM_NET_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "IQmathLib.h"         // Include header for IQmath library

#define DRV_STATUS_INIT     0x0
#define DRV_STATUS_READY    0x1
#define DRV_STATUS_RUNNING  0x2
#define DRV_STATUS_FAULT    0x3
#define DRV_STATUS_TESTING  0x4
#define DRV_STATUS_STOPPED  0x5
#define DRV_STATUS_AUTO_SET 0x6
#define DRV_STATUS_ALARM    0x8
#define DRV_STATUS_OVERHEAT 0xC



#define CAN_ONLINE_TIMEOUT_MS 600

#define ONLINE_TIMEOUT_MAX 10000

#define PDO_PACK_DEFAULTS {0,0}

//TPDO1
typedef struct {
        unsigned long PDO32_L;
        unsigned long PDO32_H;
        } PDO_PACK_32;


typedef struct {
        Uint64 status:8;
        Uint64 Ud:8;
        int64 torqueActual:8;
        int64 power:8;
        int64 speed:16;
        Uint64 TrqLimitFlags:16;
        } TPDO_PACK_1TD;



typedef union {
        PDO_PACK_32  u32;
        TPDO_PACK_1TD bit;
        } TPDO_PACK_1;


//TPDO2

typedef struct {
    Uint64 reserved1:8;
    Uint64 reserved2:8;
    Uint64 Umag:8;
    Uint64 Id:8;
    Uint64 Iq:8;
    Uint64 Ud:8;
    Uint64 Uq:8;
    Uint64 If:8;
        } TPDO_PACK_2TD;


typedef union {
    PDO_PACK_32 u32;
    TPDO_PACK_2TD bit;
} TPDO_PACK_2;



typedef struct {
    Uint64 TempInv:8;
    Uint64 TempMotorBearing1:8;
    Uint64 TempMotorBearing2:8;
    Uint64 TempMotorPhase1:8;
    Uint64 TempMotorPhase2:8;
    Uint64 TempMotorFlux1:8;
    Uint64 TempMotorFlux2:8;
    Uint64 SupplyVoltage24:8;
} TPDO_PACK_3TD;


typedef union {
    PDO_PACK_32 u32;
    TPDO_PACK_3TD bit;
} TPDO_PACK_3;



typedef struct {
    Uint64 FaultBits:48;
    Uint64 AlarmBits:16;
} TPDO_PACK_4TD;


typedef union {
    PDO_PACK_32 u32;
    TPDO_PACK_4TD bit;
} TPDO_PACK_4;


//RPDO1
typedef struct {
        unsigned long PDO32_L;
        unsigned long PDO32_H;
        } RPDO_PACK_1_32;



typedef struct {
    unsigned long cmd_by_level:32;
    unsigned long Key:1;
    unsigned long Emergency:1;
    unsigned long reserved1:1;
    unsigned long reserved2:1;
    unsigned long BIOS_online:1;
    unsigned long Braking:1;
    unsigned long selector:3;
} RPDO_PACK_1Master;


typedef union {
        RPDO_PACK_1_32 u32;
        RPDO_PACK_1Master bit;
        } RPDO_PACK_1;


typedef struct {
        int64 trqEl_1L :8;
        int64 trqEl_2R :8;
        Uint64 speed_limit_1L :8;
        Uint64 speed_limit_2R :8;
        Uint64 TG_Udc_ref :8;
        Uint64 TD_U_lim :8;
        Uint64 TR_GammaRef:8;
        Uint64 rsvd2:8; //  резерв
        } RPDO_PACK_2Master;



typedef union {
        PDO_PACK_32   u32;
        RPDO_PACK_2Master bit;
        } RPDO_PACK_2;




typedef struct
{
    long Is_Scale;
    long If_Scale;
    long Id_Scale;
    long Power_Scale;
    long Ud_Scale;
    long U_Scale;
    long Speed_Scale;
    long Trq_Scale;
} TPDO_Scales;

//****************************
typedef struct {
    int16 CANPDO_Enabled :1;
    int16 reservedEnabled1 :1;
    int16 reservedEnabled2 :1;
    int16 CANPDO_Online :1;
    int16 reservedOnline1 :1;
    int16 reservedOnline2 :1;
} S_CommFlags;

typedef union {
    Uint16 All;
    S_CommFlags bit;
} U_CommFlags;


struct SSM_Net
{
    int state;
    int state_prev;
    int E;
    int UniCONReadStateDropCounter;

    int CANPDO1_DropCounter;
    int CANPDO2_DropCounter;
    int CANPDO3_DropCounter;
    int CANPDO4_DropCounter;
    int CANPDO5_DropCounter;
    int CANPDO6_DropCounter;

    int CANPDO1_Counter;
    int CANPDO2_Counter;
    int CANPDO3_Counter;
    int CANPDO4_Counter;
    int CANPDO5_Counter;
    int CANPDO6_Counter;

    int CANOpenReinitFlag;
    TPDO_Scales PDO_Scales;
    U_CommFlags CommFlags;
    void (*init)(volatile struct SSM_Net*); /* Pointer to the init funcion           */
    void (*slow_calc)(volatile struct SSM_Net*); /* Pointer to the calc funtion           */
    void (*ms_calc)(volatile struct SSM_Net*); /* Pointer to the calc funtion           */
    void (*fast_calc)(volatile struct SSM_Net*); /* Pointer to the calc funtion           */
};
typedef volatile struct SSM_Net TSM_Net;

/*-----------------------------------------------------------------------------
 Default initializer for the
 -----------------------------------------------------------------------------*/
#define SM_NET_DEFAULTS {\
    .init = SM_Net_Init,\
    .slow_calc = SM_Net_Slow_Calc,\
    .ms_calc = SM_Net_ms_Calc, \
    .fast_calc = SM_Net_fast_Calc}

/*-----------------------------------------------------------------------------
 Prototypes for the functions
 -----------------------------------------------------------------------------*/
void SM_Net_Init(TSM_Net*);
void SM_Net_Slow_Calc(TSM_Net*);
void SM_Net_ms_Calc(TSM_Net*);
void SM_Net_fast_Calc(TSM_Net*);


#ifdef __cplusplus
}
#endif

#endif

