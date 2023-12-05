/*!
     Copyright 2023 ќќќ "Ќѕ‘ ¬≈ “ќ–"

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
 \brief      ƒрайвер ModBus (см. TModBus)
 \author    ќќќ "Ќѕ‘ ¬≈ “ќ–"
 \version   v.1.1. 02/03/2017

 \defgroup  V_ModBus ƒрайвер ModBus (см. TModBus)

 @{
*/

#ifndef V_MODBUS_H
#define V_MODBUS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "mbod.h"

#define MODBUS_MAX_RX_COUNT 10
//!—труктура для хранения счетчиков данных и ошибок RS
typedef struct {
                int error;
                int auto_res;
                int clear_error;
                unsigned int received_data;
                unsigned int sending_data;
                unsigned int receivedBytes;
                volatile int RecievedGoodCounter;//!<—четчик успешных посылок
                volatile int ErrorCRCCounter;//!<—четчик посылок с ошибкой контрольной суммы
                Uint16 isOnline;//!< ¬ сети мы или нет (идут ли пакеты)
                Uint32 OfflineCounter;//!< —четчик инкрементируется с частотой вызова процедуры ModBus_Execute и обнуляется, если в сети есть пакеты
                Uint32 OfflineCounterMax;//!< “аймаут отсутствия пакетов в сети (в единицах счЄта OfflineCounter)
                Uint16 OfflineAction;//!< „то делать, если нет сети
               } MODBUS_RS;

#define MODBUS_RS_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,50000,0}


/*! \class TModBus
      \brief ƒрайвер ModBus

       ласс \a TModBus, основанный на структуре SModBus, обрабатывает
      входящие посылки по RS-485 как посылки ModBus (RTU). */

//! см. TModBus

struct SModBus{volatile unsigned int BaudRate;//!<—корость работы по RS
                volatile unsigned long LowPrescSpeed;   // kHz. 10 000 = 10 MHz
                volatile unsigned int ExecutionFreq;//!< „астота тактирования модуля
                volatile unsigned int RSNodeID; //!< Ќомер узла в сети
                volatile unsigned int Enabled; //!< –азрешение изменения параметров привода через ModBus
                volatile unsigned int Refresh;  //!< ‘лаг изменения параметров по Modbus
                void (*Init)(volatile struct SModBus*);
                void (*Execute)(volatile struct SModBus*);
                };


typedef volatile struct SModBus TModBus;


//! —труктура modbus для хранения внутренних данных
typedef struct {volatile unsigned int In[MODBUS_MAX_RX_COUNT];//!<ћассив для принятия данных
                volatile unsigned int InCount;//!<—четчик для массива принятых данных
                volatile MB_Record /*const*/ *Addr;//!<”казатель на словарь
                volatile unsigned int TimeOut;//!<“екущий таймаут, который надо выдерживать
                volatile unsigned int TimeOut1_5;//!<–ассчитанный таймаут 1,5 длины переданного байта
                volatile unsigned int TimeOut2_5;//!<–ассчитанный таймаут 2,5 длины переданного байта
                volatile unsigned int ToSend;//!<ƒанные для отправки
                volatile unsigned int NumOfHRs;//!< оличество Holding Registers
                volatile unsigned int MiddleOfHRs;//!<—ередина Holding Registers
                volatile unsigned int InitialStepOfHRs;//!<Ўаг Holding Registers
                volatile unsigned int NumOfIRs;//!< оличество Input Registers
                volatile unsigned int MiddleOfIRs;//!<—ередина Input Registers
                volatile unsigned int InitialStepOfIRs;//!<Ўаг Input Registers
                volatile unsigned int NumOfCs;//!< оличество Coils
                volatile unsigned int MiddleOfCs;//!<—ередина Coils
                volatile unsigned int InitialStepOfCs;//!<Ўаг Coils
                volatile unsigned int NumOfDIs;//!< оличество Discrete Inputs
                volatile unsigned int MiddleOfDIs;//!<—ередина Discrete Inputs
                volatile unsigned int InitialStepOfDIs;//!<Ўаг Discrete Inputs
                volatile unsigned int RxCRC;//!<ѕринимаемая контрольная сумма
                volatile unsigned int TxCRC;//!<ѕередаваемая контрольная сумма
                volatile unsigned int MagicNumber;//!<Ём...
                volatile int TxState;//!<—остояние передачи
                volatile unsigned int temp;//!<
                volatile int RecievedCounter;//!<—четчик для отсчиывания таймаута по приему
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
