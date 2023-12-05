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

 \file     V_event_log.h
 \brief    —охранение событий и времени возникновения в Ёнќ«”
 \author   ќќќ "Ќѕ‘ ¬ектор". http://motorcontrol.ru

 \addtogroup
 @{*/

#ifndef V_EVENT_LOG_H
#define V_EVENT_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

//#define LOG_BUF_SIZE 50   //сохраняем последние 50 событий
#define LOG_FIFO_SIZE 10    //размер фифо для буферирования сообщений прежде чем они будут записаны в SPI
//#define LOG_SPI_START_ADDR 3000                       //начальный адрес в SPI

#define LOG_NUM_LENGTH 2        //длина номера события (16бит) - 2байта
#define LOG_TIME_LENGTH 4       //длина времени события (32бит) - 4байта
#define LOG_CODE_LENGTH 2       //длина кода события (16бит) - 2байта
#define LOG_LENGTH LOG_NUM_LENGTH + LOG_TIME_LENGTH + LOG_CODE_LENGTH   //общая длина записи ошибки

#define EVENT_FIFO_SUCCESSFUL 0
#define EVENT_FIFO_EMPTY 1
#define EVENT_FIFO_FULL 2
#define EVENT_FIFO_BUSY 3

  typedef struct
  {
    Uint16 ev_num;
    Uint32 ev_time;
    Uint16 ev_code;
  }TEvent;

  struct SEventFIFO
  {
    Uint16 busy_flag;
    Uint16 size;
    Uint16 number_of_msgs;
    Uint16 read_ptr;
    Uint16 write_ptr;
    TEvent msg_array[LOG_FIFO_SIZE];
    Uint16(*read)(volatile struct SEventFIFO*,volatile TEvent*);
    Uint16(*write)(volatile struct SEventFIFO*,volatile TEvent*);
  };

  typedef volatile struct SEventFIFO TEventFIFO;

#define EVENT_FIFO_DEFAULTS {0,\
    LOG_FIFO_SIZE,\
    0,0,0,\
    {0},\
    Event_FIFO_Read,\
    Event_FIFO_Write,\
  }

  Uint16 Event_FIFO_Read(TEventFIFO*,volatile TEvent*);
  Uint16 Event_FIFO_Write(TEventFIFO*,volatile TEvent*);

  struct SLogger
  {
    Uint16 INTERNAL_last_log_index;
    Uint16 INTERNAL_last_log_num;
    Uint16 INTERNAL_last_log_code;
    Uint16 SPI_buf_size;
    Uint16 SPI_start_addr;
    volatile Uint32* time_ptr;
    TEventFIFO FIFO;
    void (*init)(volatile struct SLogger*,Uint16 BS,Uint16 SA,volatile Uint32* tptr);
    void (*background_calc)(volatile struct SLogger*);
    void (*clear)(volatile struct SLogger*);
    Uint16(*write)(volatile struct SLogger*,Uint16);
    void (*read)(volatile struct SLogger*,Uint16,volatile TEvent*);
  };

  typedef volatile struct SLogger TLogger;

#define LOGGER_DEFAULTS {0,0,0,1,0,\
    &RTCclock.packed_time,\
    EVENT_FIFO_DEFAULTS,\
    Logger_Init,\
    Logger_Background_Calc,\
    Logger_Clear,\
    Logger_Event_Write,\
    Logger_Event_Read,\
  }

  void Logger_Init(TLogger*,Uint16 BS,Uint16 SA,volatile Uint32* tptr);
  void Logger_Background_Calc(TLogger*);
  void Logger_Clear(TLogger*);
  Uint16 Logger_Event_Write(TLogger*,Uint16);
  void Logger_Event_Read(TLogger* p,Uint16 shift_index,volatile TEvent* event);

#ifdef __cplusplus
}
#endif

#endif
