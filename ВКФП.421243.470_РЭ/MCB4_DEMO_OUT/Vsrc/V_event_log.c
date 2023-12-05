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

 \file     V_event_log.h
 \brief    ���������� ������� � ������� ������������� � �����
 \author   ��� "��� ������". http://motorcontrol.ru

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
//���������� ������ ������ � FIFO
    p->busy_flag = 1;
    if (p->number_of_msgs == 0) {
        //����������� ���� ������ � FIFO
        p->busy_flag = 0;
        return EVENT_FIFO_EMPTY;
    }
//������ ������ �� FIFO
    ev->ev_code = p->msg_array[(p->read_ptr)].ev_code;
    ev->ev_time = p->msg_array[(p->read_ptr)].ev_time;
    ev->ev_num = p->msg_array[(p->read_ptr)].ev_num;
//���������� FIFO � ���������� ������
    p->read_ptr++;
    if (p->read_ptr >= p->size)
        p->read_ptr = 0;
    p->number_of_msgs--;
//����������� ���� ������ � FIFO
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
//���������� ������ ������ � FIFO
    p->busy_flag = 1;
    if (p->number_of_msgs == p->size) {
        //����������� ���� ������ � FIFO
        p->busy_flag = 0;
        return EVENT_FIFO_FULL;
    }
//���������� ������ � FIFO
    p->msg_array[(p->write_ptr)].ev_code = ev->ev_code;
    p->msg_array[(p->write_ptr)].ev_time = ev->ev_time;
    p->msg_array[(p->write_ptr)].ev_num = ev->ev_num;
//���������� FIFO � ���������� ������
    p->write_ptr++;
    if (p->write_ptr >= p->size)
        p->write_ptr = 0;
    p->number_of_msgs++;
//����������� ���� ������ � FIFO
    p->busy_flag = 0;
    return EVENT_FIFO_SUCCESSFUL;
}

void Logger_Init(TLogger* p, Uint16 BS, Uint16 SA, volatile Uint32* tptr) {
    TEvent tmp;
    volatile Uint16 i;
    volatile Uint16 last_log_num = 0;
    volatile Uint16 last_log_index = 0;
//�������������� ���������� ����������
    p->SPI_buf_size = BS;
    p->SPI_start_addr = SA;
    p->time_ptr = tptr;
    DSP28x_usDelay(200L);
    DSP28x_usDelay(200L);
//����� ����� �������������� ����� � ����� - ����� ���������
    spimem.spiaddr = p->SPI_start_addr;
    spimem.data_length = 0;
    for (i = 0; i < p->SPI_buf_size; i++) {
        //������ �����
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&tmp.ev_num);
        spimem.data_length = LOG_NUM_LENGTH;
        spimem.readspi(&spimem);
        //������ �����
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&tmp.ev_time);
        spimem.data_length = LOG_TIME_LENGTH;
        spimem.readspi(&spimem);
        //������ ���
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&tmp.ev_code);
        spimem.data_length = LOG_CODE_LENGTH;
        spimem.readspi(&spimem);

        //������ ����������� ��������
        //���� ��� ���� 0xFFFF, �� ������ ��� ������
        if ((tmp.ev_num == 0xFFFF) && (tmp.ev_time == 0xFFFFFFFF) && (tmp.ev_code == 0xFFFF)) {
            //������
            p->clear(p);
            //�������������� ����������
            p->INTERNAL_last_log_num = 0;
            p->INTERNAL_last_log_index = 0;
            return;
        }
        //���� ��������� ������
        if (last_log_num < tmp.ev_num) {
            last_log_num = tmp.ev_num;
            last_log_index = i;
        }
    }
    p->INTERNAL_last_log_num = last_log_num;
    p->INTERNAL_last_log_index = last_log_index;
}
//������� ������ ������ � �����
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

//������� ������� ������ ������� � FIFO
Uint16 Logger_Event_Write(TLogger* p, Uint16 code) {
    TEvent event;
//��������� ������
    DINT;
    event.ev_time = *(p->time_ptr);
    event.ev_code = code;
    event.ev_num = ++p->INTERNAL_last_log_num;
    p->INTERNAL_last_log_code = code;
    EINT;
//����� � FIFO
    return p->FIFO.write(&(p->FIFO), &event);
}

void Logger_Event_Read(TLogger* p, Uint16 shift_index, volatile TEvent* event) {
    Uint16 correction = 0;
//��������� ������������ �������
    if (shift_index > (p->SPI_buf_size - 1))
        return;

//���� ��������� ��� ����������� ������
    if (((int) p->INTERNAL_last_log_index - (int) shift_index) < 0)
        correction = p->SPI_buf_size;
//������ ������
    spimem.spiaddr = p->SPI_start_addr + ((p->INTERNAL_last_log_index - shift_index + correction) * (LOG_LENGTH));
    spimem.startaddr = (Uint16*) (&(event->ev_num));
    spimem.data_length = LOG_NUM_LENGTH;
    spimem.readspi(&spimem);
//������ �������
    spimem.spiaddr += spimem.data_length;
    spimem.startaddr = (Uint16*) (&(event->ev_time));
    spimem.data_length = LOG_TIME_LENGTH;
    spimem.readspi(&spimem);
//������ ����
    spimem.spiaddr += spimem.data_length;
    spimem.startaddr = (Uint16*) (&(event->ev_code));
    spimem.data_length = LOG_CODE_LENGTH;
    spimem.readspi(&spimem);
}
//������� ��������� FIFO � ������ ������ � �����
void Logger_Background_Calc(TLogger* p) {
    Uint16 ret;
    TEvent event;
//����� �� ������ ������������� ������� ���� ����� ���������� �� 1 ������ �� ���
    ret = p->FIFO.read(&(p->FIFO), &event);
    if (ret == EVENT_FIFO_SUCCESSFUL) {
        //����� � �����
        if (p->INTERNAL_last_log_index >= (p->SPI_buf_size - 1))
            p->INTERNAL_last_log_index = 0;
        else
            p->INTERNAL_last_log_index++;

        //������ ������
        spimem.spiaddr = p->SPI_start_addr + (p->INTERNAL_last_log_index) * (LOG_LENGTH);
        spimem.startaddr = (Uint16*) (&(event.ev_num));
        spimem.data_length = LOG_NUM_LENGTH;
        spimem.writespi(&spimem);
        //������ �������
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&(event.ev_time));
        spimem.data_length = LOG_TIME_LENGTH;
        spimem.writespi(&spimem);
        //������ ����
        spimem.spiaddr += spimem.data_length;
        spimem.startaddr = (Uint16*) (&(event.ev_code));
        spimem.data_length = LOG_CODE_LENGTH;
        spimem.writespi(&spimem);
    }
}
/*@}*/
