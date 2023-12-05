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

 \file      v_data_log.h
 \brief     N-канальный логгер для осциллографирования в реальном времени (см. TDataLog).
 В версии 3.0 реализовано произвольное число каналов осциллографирования.
 Основные положения:
 Количество каналов определяется дефайном DLOG_CHANNELS_NUM (ограничено размером доступной памяти).
 При SDO-чтении осциллограмм данные возвращаются через 32-битную переменную 'dlog.next_value_var'
 (там, кроме 16-битного значения, есть всякие поля). В неё добавлены два флага:
 - флаг, что в поле "значение" - старшие 16 бит точки
 - флаг, что переменная 16-разрядная
 Юникон сначала запрашивает младшую часть значения, потом - старшую и т.д. по всем точкам.
 Если переменная 16-разрядная, то старшая часть не запрашивается. При буферной передаче:
 Т.к. один буферный запрос ограничен у нас 256-тью 16-битными словами, то Юникон сначала запрашивает
 первые 256 слов (128 32-битных точек), затем - остальные 256 слов. Т.е. используется два буферных запроса.

 \author    Коллектив ООО НПФ Вектор
 \version   v 3.0 23/11/2021
 \defgroup  v_data_log Цифровой осциллограф (см. TDataLog)
 @{
 */
/*@{*/

#include "DSP.h"
#include "co_ODvars.h"
#include "V_data_log.h"
#include "CANOpen_drv.h"
#include "main.h"

//! Фоновый обработчик.

/*! работает в фоне. Нужно для установки адресов переменных через CAN.
 если нет CAN, можно записать нужные адреса вручную в TDataLog.dlog_iptr  */
//! \memberof TDataLog
void dlog_background_analyzer(TDataLog* p)
{
    p->trig_shift_int = (p->trig_shift & 0xFFFFFF) >> 16;  // перевод длины предыстории из % в точки
    if (p->trig_shift_int > 255) p->trig_shift_int = 255;

    if ((p->control & 0x0030) == 0)
    {
        p->control |= (0b11 << 7) | (DLOG_CHANNELS_NUM-1) << 9;
        return;
    }

    // Перед всеми изменениями тормозим даталоггер.
    // Иначе он может начать записывать данные по прерыванию, пока тут, в фоне, идет, скажем, запись адресов.
    // И тогда в лучшем случае будет каша из данных, в худшем - останов контроллера при обращении по неправильному адресу.
    p->mode_reset = 0;
    p->valid_points_num = 0;    // т.к. даталоггер останавливался (mode = 0), то предыстория неактуальна, т.к.
                                // 1) за время стопа даталоггера между записанной предысторией и новыми данными будет разрыв по времени и
                                // 2) выбранные записываемые переменные вообще могли смениться и предыстория останется от старых, а новые данные - от новых

    for (int i = 0; i < DLOG_CHANNELS_NUM; i++)
    {
        if (p->ind_subind[i] != 0)
        {
            if (co_getObjectInfo(p->pco_vars, p->ind_subind[i], (TObjectInfo*)&p->objectInfo[i]) == 0)
            {
                p->objectInfo[i].varAddr = 0;
            }
        }
        else
        {
            p->objectInfo[i].varAddr = 0;
        }
    }
    p->highPartOfValue = 0;
    p->WriteDelimiter = (p->control >> 16) & 0xFF; // прореживание. Ограничивается 8ю битами
    unsigned char mode = (p->control >> 4) & 3; // режим - 2 бита
    p->control = (0b11 << 7) | (DLOG_CHANNELS_NUM-1) << 9;  // все обработали, обнуляем, чтобы при след. вызове не начать обрабатывать снова

    p->mode_reset = mode;
    if (mode == 3) p->Wcounter = 0; // в режиме однократной записи 1024 точек нужно писать с первой точки первого массива
    p->WriteDelimiterCounter = 0;
    p->highPartOfValue = 0;
}


//! Функция для установки mode_reset.
//! Предполагается для управления логгером из других модулей.
//! Проверяет mode_reset на валидность и обнуляет счетчики.
//! \memberof TDataLog
int dlog_try_set_mode(Uint16 mode_reset, TDataLog* p)
{
    switch (mode_reset) // какой режим запрошен?
    {
        case 1: // однократная запись
            if (p->OneShotOperation == 1)
            {
                if (p->mode_reset == 2) p->mode_reset = 1;
                else return 0;
            }
            else
            {
                p->mode_reset = 1;
            }
            break;

        case 2: // запись по кругу без остановки
            if (p->mode_reset == 2) return 1;
            p->mode_reset = 2;
            break;

        case 3: // однократная запись одной переменной последовательно во все 4 массива (1024 точки)
            p->mode_reset = 3;
            p->Wcounter = 0;    // в этом режиме нужно писать с первой точки первого массива
            break;

        default:
            p->mode_reset = 0;
            return 0;
    }

    // При смене режима в любом случае сбрасываем флаг "данные готовы".
    p->control &= ~(1 << 6);
    p->WriteDelimiterCounter = 0;
    p->highPartOfValue = 0;
    return 1;
}


//! Функция для установки mode_reset.
//! Предполагается для управления логгером из других модулей.
//! Проверяет mode_reset на валидность и обнуляет счетчики.
//! Оставлена для совместимости со старым ПО. Вместо неё рекомендуется использовать функцию try_set_mode.
//! \memberof TDataLog
void dlog_set_mode(Uint16 mode_reset, TDataLog* p)
{
    dlog_try_set_mode(mode_reset, p);
}


//! Записывает очередные точки в массивы осциллограммы.
//! Должна вызываться с заданной дискретизацией и занимается записью массивов,
//! т.е. непосредственно осциллографированием. Умеет записывать данные
//! в массивы по-разному в зависимости от выбранного режима работы осциллографа
//! \memberof TDataLog
void data_log_update(TDataLog* p)
{
    p->sampling_rate = 10000;
    // Прореживание данных. Если не достигли уставки WriteDelimiter - выходим/
    // WriteDelimiter = 1 - не делим
    // WriteDelimiter = 2 - берем каждую вторую
    if ((p->WriteDelimiterCounter++ + 1) < p->WriteDelimiter)
        return;
    else
        p->WriteDelimiterCounter = 0;

    if (p->mode_reset != p->mode_reset_prev)
        p->E = 1;
    else
        p->E = 0;
    p->mode_reset_prev = p->mode_reset;

    switch (p->mode_reset)
    {
        case 0:
        {
            p->Wcounter = 0;
            return;
        }

        case 1:  // однократная запись - дошли до конца и стоп (режим 0)
        {
            // При входе в режим получаем точку срабатывания триггера (это текущий Wcounter, с которым мы сюда зашли) и рассчитываем первую точку, относящуюся к данной осце (исходя из текущей точки и заданной длины предыстории)
            if (p->E == 1)
            {
                p->prehistory_length = p->valid_points_num;     //длина предыстории равна количеству валидных точек
                if (p->prehistory_length > p->trig_shift_int)   //если предыстория длиннее заданного, ограничим
                    p->prehistory_length = p->trig_shift_int;
                p->first_point_written = (p->Wcounter - p->prehistory_length) & 0xFF;
                p->highPartOfValue = 0;
            }
            p->Wcounter &= 0xFF; // защита - если вдруг в counter не валидное значение
            for (int i = 0; i < DLOG_CHANNELS_NUM; i++)
            {
                if (p->objectInfo[i].varAddr != 0)
                {
                    p->buff[(i << 8) + p->Wcounter] =
                        p->objectInfo[i].varSize == 16 ? *((int16*)p->objectInfo[i].varAddr) : *((int32*)p->objectInfo[i].varAddr);
                }
            }
            p->Wcounter++;
            p->Wcounter &= 0xFF;  // если прошли 256 точек, обнулится
            if (p->Wcounter == p->first_point_written)  //если дошли до последней записываемой точки
            {
                p->mode_reset = 0;              // режим СТОП
                p->control |= (0b111 << 6) | ((DLOG_CHANNELS_NUM-1) << 9);  // "данные готовы" + "поддерживается блочная передача" + "32-битные данные" + "DLOG_CHANNELS_NUM-1"
            }
            return;
        }

        case 2: // записываем лог по кругу
        {
            if (p->E == 1)
            {
                p->highPartOfValue = 0;
            }
            p->valid_points_num++;  // считаем количество записанных валидных точек предыстории
            if (p->valid_points_num > 256)  // ограничиваем
                p->valid_points_num = 256;
            p->Wcounter &= 0xFF; // защита - если вдруг в counter не валидное значение
            for (int i = 0; i < DLOG_CHANNELS_NUM; i++)
            {
                if (p->objectInfo[i].varAddr != 0)
                {
                    p->buff[(i << 8) + p->Wcounter] =
                        p->objectInfo[i].varSize == 16 ? *((int16*)p->objectInfo[i].varAddr) : *((int32*)p->objectInfo[i].varAddr);
                }
            }
            p->Wcounter++;
            p->Wcounter &= 0xFF;  // если прошли 256 точек, обнулится
            return;
        }

        case 3: // режим однократной записи DLOG_CHANNELS_NUM x DLOG_SAMPLES_NUMBER точек
        {
            if (p->E == 1)
            {
                p->first_point_written = 0;     // пишем с первой точки, предыстория не нужна.
                p->highPartOfValue = 0;
            }
            // с учетом того, что буферы в памяти расположены последовательно,
            // записываем в первый, "заезжая" на остальные
            p->buff[p->Wcounter] =
                    p->objectInfo[0].varSize == 16 ? *((int16*)p->objectInfo[0].varAddr) : *((int32*)p->objectInfo[0].varAddr);
            p->Wcounter++;
            if (p->Wcounter >= (DLOG_CHANNELS_NUM * DLOG_SAMPLES_NUMBER))  // если дошли до конца
            {
                p->mode_reset = 0;                 // режим СТОП
                p->control |= (0b111 << 6) | ((DLOG_CHANNELS_NUM-1) << 9);  // "данные готовы" + "поддерживается блочная передача" + "32-битные данные" + "DLOG_CHANNELS_NUM-1"
            }
            return;
        }
    }
}

/*@}*/
