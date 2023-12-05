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

 \file      V_ModBus.h
 \brief      ������� ModBus (��. TModBus)
 \author    ��� "��� ������"
 \version   v.1.1. 02/03/2017

 \defgroup  V_ModBus ������� ModBus (��. TModBus)

 @{
*/

#ifndef V_MODBUS_H
#define V_MODBUS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "mbod.h"

#define MODBUS_MAX_RX_COUNT 10
//!��������� ��� �������� ��������� ������ � ������ RS
typedef struct {
                int error;
                int auto_res;
                int clear_error;
                unsigned int received_data;
                unsigned int sending_data;
                unsigned int receivedBytes;
                volatile int RecievedGoodCounter;//!<������� �������� �������
                volatile int ErrorCRCCounter;//!<������� ������� � ������� ����������� �����
                Uint16 isOnline;//!< � ���� �� ��� ��� (���� �� ������)
                Uint32 OfflineCounter;//!< ������� ���������������� � �������� ������ ��������� ModBus_Execute � ����������, ���� � ���� ���� ������
                Uint32 OfflineCounterMax;//!< ������� ���������� ������� � ���� (� �������� ����� OfflineCounter)
                Uint16 OfflineAction;//!< ��� ������, ���� ��� ����
               } MODBUS_RS;

#define MODBUS_RS_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,50000,0}


/*! \class TModBus
      \brief ������� ModBus

      ����� \a TModBus, ���������� �� ��������� SModBus, ������������
      �������� ������� �� RS-485 ��� ������� ModBus (RTU). */

//! ��. TModBus

struct SModBus{volatile unsigned int BaudRate;//!<�������� ������ �� RS
                volatile unsigned long LowPrescSpeed;   // kHz. 10 000 = 10 MHz
                volatile unsigned int ExecutionFreq;//!< ������� ������������ ������
                volatile unsigned int RSNodeID; //!< ����� ���� � ����
                volatile unsigned int Enabled; //!< ���������� ��������� ���������� ������� ����� ModBus
                volatile unsigned int Refresh;  //!< ���� ��������� ���������� �� Modbus
                void (*Init)(volatile struct SModBus*);
                void (*Execute)(volatile struct SModBus*);
                };


typedef volatile struct SModBus TModBus;


//! ��������� modbus ��� �������� ���������� ������
typedef struct {volatile unsigned int In[MODBUS_MAX_RX_COUNT];//!<������ ��� �������� ������
                volatile unsigned int InCount;//!<������� ��� ������� �������� ������
                volatile MB_Record /*const*/ *Addr;//!<��������� �� �������
                volatile unsigned int TimeOut;//!<������� �������, ������� ���� �����������
                volatile unsigned int TimeOut1_5;//!<������������ ������� 1,5 ����� ����������� �����
                volatile unsigned int TimeOut2_5;//!<������������ ������� 2,5 ����� ����������� �����
                volatile unsigned int ToSend;//!<������ ��� ��������
                volatile unsigned int NumOfHRs;//!<���������� Holding Registers
                volatile unsigned int MiddleOfHRs;//!<�������� Holding Registers
                volatile unsigned int InitialStepOfHRs;//!<��� Holding Registers
                volatile unsigned int NumOfIRs;//!<���������� Input Registers
                volatile unsigned int MiddleOfIRs;//!<�������� Input Registers
                volatile unsigned int InitialStepOfIRs;//!<��� Input Registers
                volatile unsigned int NumOfCs;//!<���������� Coils
                volatile unsigned int MiddleOfCs;//!<�������� Coils
                volatile unsigned int InitialStepOfCs;//!<��� Coils
                volatile unsigned int NumOfDIs;//!<���������� Discrete Inputs
                volatile unsigned int MiddleOfDIs;//!<�������� Discrete Inputs
                volatile unsigned int InitialStepOfDIs;//!<��� Discrete Inputs
                volatile unsigned int RxCRC;//!<����������� ����������� �����
                volatile unsigned int TxCRC;//!<������������ ����������� �����
                volatile unsigned int MagicNumber;//!<��...
                volatile int TxState;//!<��������� ��������
                volatile unsigned int temp;//!<
                volatile int RecievedCounter;//!<������� ��� ����������� �������� �� ������
                } MODBUS_INT;

#define MODBUS_INT_DEFAULTS {{0},0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
                0xFFFF,0xFFFF, 0xA001,-1, 0,0, \
                }

#define MODBUS_DEFAULTS {38400,37500,10000, 0x01, 1, 0,\
                ModBus_Init, \
                ModBus_Execute,\
                }


extern MODBUS_INT   MBInternals;
//! \memberof TModBus
void ModBus_Init(TModBus *p);
//! \memberof TModBus
void ModBus_Execute(TModBus *p);



#ifdef __cplusplus
}
#endif

#endif

/*@}*/
