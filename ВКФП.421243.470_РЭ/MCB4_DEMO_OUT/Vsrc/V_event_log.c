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

#include "DSP.h"
#include "IQmathLib.h"
#include "V_event_log.h"
#include "V_UserMemory.h"

extern TSpiMem spimem;

Uint16 Event_FIFO_Read(TEventFIFO* p, volatile TEvent* ev) {
    if (p->busy_flag > 0)
        return EVENT_FIFO_BUSY;
//выставляем флажок работы с FIFO
    p->busy_flag = 1;
    if (p->number_of_msgs == 0) {
        //освобождаем флаг работы с FIFO
        p->busy_flag = 0;
        return EVENT_FIFO_EMPTY;
    }
//читаем данные из FIFO
    ev->ev_code = p->msg_array[(p->read_ptr)].ev_code;
    ev->ev_time = p->msg_array[(p->read_ptr)].ev_time;
    ev->ev_num = p->msg_array[(p->read_ptr)].ev_num;
//подготовка FIFO к следующему вызову
    p->read_ptr++;
    if (p->read_ptr >= p->size)
        p->read_ptr = 0;
    p->number_of_msgs--;
//освобождаем флаг работы с FIFO
    p->busy_flag = 0;
    return EVENT_FIFO_SUCCESSFUL;
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(Event_FIFO_Write,"secureRamFuncs");
#endif

Uint16 Event_FIFO_Write(TEventFIFO* p, volatile TEvent* ev) {
    if (p->busy_flag > 0)
        return EVENT_FIFO_BUSY;
//выставляем флажок работы с FIFO
    p->busy_flag = 1;
    if (p->number_of_msgs == p->size) {
        //освобождаем флаг работы с FIFO
        p->busy_flag = 0;
        return EVENT_FIFO_FULL;
    }
//записываем данные в FIFO
    p->msg_array[(p->write_ptr)].ev_code = ev->ev_code;
    p->msg_array[(p->write_ptr)].ev_time = ev->ev_time;
    p->msg_array[(p->write_ptr)].ev_num = ev->ev_num;
//подготовка FIFO к следующему вызову
    p->write_ptr++;
    if (p->write_ptr >= p->size)
        p->write_ptr = 0;
    p->number_of_msgs++;
//освобождаем флаг работы с FIFO
    p->busy_flag = 0;
    return EVENT_FIFO_SUCCESSFUL;
}

void Logger_Init(TLogger* p, Uint16 BS, Uint16 SA, volatile Uint32* tptr) {
    TEvent tmp;
    volatile Uint16 i;
    volatile Uint16 last_log_num = 0;
    volatile Uint16 last_log_index = 0;
//инициализируем внутренние переменные
    p->SPI_buf_size = BS;
    p->SPI_start_addr = SA;
    p->time_ptr = tptr;
    DSP28x_usDelay(200L);
    DSP28x_usDelay(200L);
//далее нужно просканировать буфер в Ёнќ«” - найти последнюю
    spimem.spiaddr = p->SPI_start_addr;
    spimem.data_length = 0;
    for (i = 0; i < p->SPI_buf_size; i++) {
        //читаем номер
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&tmp.ev_num);
        spimem.data_length = LOG_NUM_LENGTH;
        spimem.readspi(&spimem);
        //читаем время
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&tmp.ev_time);
        spimem.data_length = LOG_TIME_LENGTH;
        spimem.readspi(&spimem);
        //читаем код
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&tmp.ev_code);
        spimem.data_length = LOG_CODE_LENGTH;
        spimem.readspi(&spimem);

        //делаем необходимые проверки
        //если все поля 0xFFFF, то чистим всю память
        if ((tmp.ev_num == 0xFFFF) && (tmp.ev_time == 0xFFFFFFFF) && (tmp.ev_code == 0xFFFF)) {
            //чистим
            p->clear(p);
            //инициализируем переменные
            p->INTERNAL_last_log_num = 0;
            p->INTERNAL_last_log_index = 0;
            return;
        }
        //ищем последнюю запись
        if (last_log_num < tmp.ev_num) {
            last_log_num = tmp.ev_num;
            last_log_index = i;
        }
    }
    p->INTERNAL_last_log_num = last_log_num;
    p->INTERNAL_last_log_index = last_log_index;
}
//функция очстки буфера в Ёнќ«”
void Logger_Clear(TLogger* p) {
    Uint16 i;
    Uint16 zero = 0;
    spimem.spiaddr = p->SPI_start_addr;
    spimem.startaddr = (Uint16*) (&zero);
    spimem.data_length = 1;
    for (i = 0; i < (p->SPI_buf_size * (LOG_LENGTH)); i++) {
        spimem.writespi(&spimem);
        spimem.spiaddr++;
    }
    p->INTERNAL_last_log_index = 0;
    p->INTERNAL_last_log_num = 0;
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(Logger_Event_Write,"secureRamFuncs");
#endif

//быстрая функция записи события в FIFO
Uint16 Logger_Event_Write(TLogger* p, Uint16 code) {
    TEvent event;
//формируем данные
    DINT;
    event.ev_time = *(p->time_ptr);
    event.ev_code = code;
    event.ev_num = ++p->INTERNAL_last_log_num;
    p->INTERNAL_last_log_code = code;
    EINT;
//пишем в FIFO
    return p->FIFO.write(&(p->FIFO), &event);
}

void Logger_Event_Read(TLogger* p, Uint16 shift_index, volatile TEvent* event) {
    Uint16 correction = 0;
//проверяем правильность запроса
    if (shift_index > (p->SPI_buf_size - 1))
        return;

//ввод коррекции для организации кольца
    if (((int) p->INTERNAL_last_log_index - (int) shift_index) < 0)
        correction = p->SPI_buf_size;
//чтение номера
    spimem.spiaddr = p->SPI_start_addr + ((p->INTERNAL_last_log_index - shift_index + correction) * (LOG_LENGTH));
    spimem.startaddr = (Uint16*) (&(event->ev_num));
    spimem.data_length = LOG_NUM_LENGTH;
    spimem.readspi(&spimem);
//чтение времени
    spimem.spiaddr += spimem.data_length;
    spimem.startaddr = (Uint16*) (&(event->ev_time));
    spimem.data_length = LOG_TIME_LENGTH;
    spimem.readspi(&spimem);
//чтение кода
    spimem.spiaddr += spimem.data_length;
    spimem.startaddr = (Uint16*) (&(event->ev_code));
    spimem.data_length = LOG_CODE_LENGTH;
    spimem.readspi(&spimem);
}
//функция обработки FIFO и записи аварий в Ёнќ«”
void Logger_Background_Calc(TLogger* p) {
    Uint16 ret;
    TEvent event;
//чтобы не сильно затормаживать фоновый цикл будем записывать по 1 записи за раз
    ret = p->FIFO.read(&(p->FIFO), &event);
    if (ret == EVENT_FIFO_SUCCESSFUL) {
        //пишем в Ёнќ«”
        if (p->INTERNAL_last_log_index >= (p->SPI_buf_size - 1))
            p->INTERNAL_last_log_index = 0;
        else
            p->INTERNAL_last_log_index++;

        //запись номера
        spimem.spiaddr = p->SPI_start_addr + (p->INTERNAL_last_log_index) * (LOG_LENGTH);
        spimem.startaddr = (Uint16*) (&(event.ev_num));
        spimem.data_length = LOG_NUM_LENGTH;
        spimem.writespi(&spimem);
        //запись времени
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&(event.ev_time));
        spimem.data_length = LOG_TIME_LENGTH;
        spimem.writespi(&spimem);
        //запись кода
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&(event.ev_code));
        spimem.data_length = LOG_CODE_LENGTH;
        spimem.writespi(&spimem);
    }
}
/*@}*/
