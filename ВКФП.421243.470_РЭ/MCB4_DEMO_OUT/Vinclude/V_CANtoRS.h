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

 \file        V_CANtoRS.H
 \brief   Модуль CAN to RS
 \author    ООО "НПФ Вектор". http://motorcontrol.ru

 @{
*/

#ifndef V_CAN_TO_RS_H
#define V_CAN_TO_RS_H

#ifdef __cplusplus
extern "C" {
#endif
#define BUFSIZE 30
#define TRANSM_TIME_OUT 100
#define CAN_TO_RS_BUFSIZE 20
#define CAN_TO_RS_TRANSM_TIME_OUT 100
#define READ_DATA_MAX_LEN 10

#define CANTORS_SCIXREGS ScibRegs

#include "CANOpen_drv.h"

typedef unsigned char   Uint8;

struct SCANtoRS {
                Uint16 test_dbg; //для отладки
                Uint16 APIpacketMode;
				int HeartBeatGo;//пропустите сердцебиение!
                char callback_go; //флаг для вызова callback
                char TransmBusy; //флаг занятости передатчика           
                char PacketInWait; //флаг если есть что-то в буфере отправки
                int HeartCounter; //счетчик для отправки HeartCounter
                int TransmBusyTimeCount; //счетчик таймаута занятости передатчика
                int ReadPackDataCounter; //счетчик данных в пакете
                int ReadCRCCounter; //счетчик данных в пакете
                int all_len; //transmit buf len
                int tr_counter; //transmit counter            
				void (*init)(struct SCANtoRS *);     /* Pointer to the init function */
				void (*calc_1k)(struct SCANtoRS *);     /* Pointer to the calc function */
				void (*calc_10k)(struct SCANtoRS *);     /* Pointer to the calc function */
                int (*receive)(struct SCANtoRS *);
                Uint16 (*write)(TZCanMsg* MSG,struct SCANtoRS *);  
                void (*send_next)(struct SCANtoRS *); 
                void (*callback)(TCo_OdVars* ppc, TZCanMsg* p);        
				unsigned char buf_out[CAN_TO_RS_BUFSIZE];
				TZCanMsg MSG;
				TZCanMsg bufMSG;
				unsigned char ReadPackData[CAN_TO_RS_BUFSIZE]; //буфер для API посылки
				unsigned char ReadCRC[2]; //буфер для СRC
				unsigned char TempData[10];
				Uint16* nodeID;
				Uint16 CounterWrongCRC;
				Uint16 CounterRes;
				Uint16 CounterSended;
				Uint16 MessDrop;
				Uint16 MessDrop1;
				};

typedef  struct SCANtoRS TCANtoRS;


//extern void Z_co_receiveSDOrequest(TCo_OdVars*, TZCanMsg*);

void CANtoRS_init(TCANtoRS*);
void CANtoRS_calc_1k(TCANtoRS*);
void CANtoRS_calc_10k(TCANtoRS*);
int  CANtoRS_Receive(TCANtoRS*);
void CANtoRS_Send_next(TCANtoRS *p);
void CANtoRS_DBG(TCANtoRS*);
Uint16 CANtoRS_SendP(unsigned char* Data, int len,TCANtoRS *p);
Uint16 CANtoRS_Write(TZCanMsg* MSG,TCANtoRS *p);
Uint16 CANtoRS_WriteHelper(TZCanMsg* MSG,TCANtoRS *p);
void CANtoRS_HeartBeat(TCANtoRS *p);
Uint16 CANtoRS_C_CRC(TCANtoRS*);
Uint16 CANtoRS_C_CRC1(TCANtoRS*, Uint8*, Uint16);
void CANtoRS_Analiz(TCANtoRS*);
void CANtoRS_Re_CB(TCo_OdVars* ppc,TZCanMsg* p);
//interrupt void scib_rx_isr(void);
//interrupt void scib_tx_isr(void);


//если добавляем в струкуру переменные то добавляем значения по умолчанию
#define CAN_TO_RS_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0, \
						CANtoRS_init,\
						CANtoRS_calc_1k,\
						CANtoRS_calc_10k,\
						CANtoRS_Receive,\
						CANtoRS_WriteHelper,\
						CANtoRS_Send_next,\
						CANtoRS_Re_CB}

#ifdef __cplusplus
}
#endif

#endif




