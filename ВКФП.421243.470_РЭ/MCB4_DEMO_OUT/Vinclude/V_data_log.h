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

/* Callback-функция на переменную "dlog.next_value_var" должна выглядеть так:
 * (эта функция обычно расположена в файле "v_call_back.c" или "CANOpenUDfuncs.c")

void callback_dlog(Uint16 par, Uint16 tag_CANnum)
{
    // Если произошла запись в переменную, то установим буфер на нужную точку.
    if (par == 1)
    {
        //  В переменную next_value_var записывается желаемое смещение, номер буфера, из которого хотим читать,
        // а также разреживание (делитель)
        int n_old = (int)((dlog.next_value_var >> 24) & 3);     // извлекается номер буфера ("старый" 4-канальный Юникон)
        int n_new = (int)((dlog.next_value_var >> 28) & 0xF);   // извлекается номер буфера ("новый" N-канальный Юникон)
        dlog.buff_num = n_new != 0 ? n_new : n_old;
        dlog.highPartOfValue = (int)((dlog.next_value_var >> 26) & 1); // отдавать старшую часть 32-битного значения?
        dlog.Rcounter = (dlog.next_value_var >> 16) & 0xFF; // какую точку надо отдавать
        // Проверяем хотят ли использовать блочную передачу
        if ((dlog.next_value_var & 0xffff) == 1)
        {
            if (dlog.pco_vars->co_blockTransferCommand == CANBT_INTERFACE_FREE)
                dlog.pco_vars->co_blockTransferCommand = CANBT_INTERFACE_DATALOG1;
        }
        if ((dlog.next_value_var & 0xffff) == 2)
        {
            if (dlog.pco_vars->co_blockTransferCommand == CANBT_INTERFACE_FREE)
                dlog.pco_vars->co_blockTransferCommand = CANBT_INTERFACE_DATALOG2;
        }
    }

    //выдвигаем данные:
    int32 val32 = dlog.buff[(dlog.buff_num << 8) + ((dlog.Rcounter + dlog.first_point_written) & 0xFF)];
    int varSizeIs16 = (int)(dlog.objectInfo[dlog.buff_num].varSize == 16);
    dlog.next_value_var = (dlog.highPartOfValue != 0 ? val32 >> 16 : val32) & 0x0000FFFF;
    dlog.next_value_var |= ((Uint32)dlog.Rcounter) << 16;
    dlog.next_value_var |= ((Uint32)(dlog.buff_num & 3)) << 24;
    dlog.next_value_var |= ((Uint32)dlog.highPartOfValue) << 26;
    dlog.next_value_var |= ((Uint32)varSizeIs16) << 27;
    dlog.next_value_var |= ((Uint32)(dlog.buff_num & 0xF)) << 28;

    if ((dlog.highPartOfValue != 0) || varSizeIs16)
    {
        // При следующем запросе отдадим младшую часть следующей точки.
        dlog.Rcounter++;
        dlog.Rcounter &= 0xFF;
        dlog.highPartOfValue = 0;
    }
    else
    {
        // При следующем запросе отдадим старшую часть этой же точки.
        dlog.highPartOfValue = 1;
    }
}

*/

#ifndef V_DATA_LOG_H
#define V_DATA_LOG_H

#include "co_ODvars.h"
#include "CANOpen_drv.h"

#ifdef __cplusplus
extern "C"
{
#endif

//! Число каналов осциллографирования (4...16):
#define DLOG_CHANNELS_NUM   4
#if (DLOG_CHANNELS_NUM < 4) || (DLOG_CHANNELS_NUM > 16)
    #error Число каналов осциллографирования выходит за диапазон [4...16]
#endif


//! Размер массивов для осциллографирования.
//! Если нужно менять, то это делать надо не только тут - слишком много завязано на это число
//! Переделать сложно, так как на это число завязка косвенная: например, для ускорения работы
//! применяются такие конструкции: p->Wcounter&=0xFF, где FF - маска (символизирует 256 точек)
#define DLOG_SAMPLES_NUMBER 256


#define DLOG_DATA_SIZE      32  // для совместимости с модулем CANBlockTransferInterface.c


/*! \class TDataLog
 \brief N-канальный логгер для осциллографирования в реальном времени

 Класс \a TDataLog, основанный на структуре SDataLog, позволяет записывать выбранные N переменных в массивы
 из 255 точек с заданной дискретизацией по времени. Кроме того, имеет
 связь с драйвером CANOpen для автоматизации указания этих переменных: можно
 "зарядить" в даталоггер любой существующий элемент словаря.*/

//! см. TDataLog
struct SDataLog
{
    int32 buff[DLOG_CHANNELS_NUM * DLOG_SAMPLES_NUMBER];    //!< массив для отснятых осциллограмм
    Uint16 Wcounter;            //!< Счетчик по массиву для записи
    Uint16 Rcounter;            //!< Счетчик по массиву для чтения

    int32 upload_buff[DLOG_SAMPLES_NUMBER]; //!< массив для отправки осциллограммы в юникон
    Uint32 trig_shift;  //!< сдвиг первой точки после срабатывания триггера. Используется, чтобы задать, сколько точек предыстории сохранять.
    Uint16 trig_shift_int;      //!< то же, переведенное в точки
    Uint16 first_point_written; //!< первая точка, относящаяся к записываемой осциллограмме с учетом длины предыстории и точки срабатывания триггера
    Uint16 prehistory_length;   //!< длина записанной предыстории (если даталоггер переинициализировался кнопкой "обновить", она обнуляется)
    Uint16 valid_points_num;    //!< счетчик валидных точек предыстории, записанных после переинициализации кнопкой "обновить" в юниконе

    /*!  Режимов работы четыре:
     0 - стоп
     1 - однократная запись
     2 - запись по кругу без остановки
     3 - однократная запись одной переменной во все 4 массива последовательно, для получения длинной осциллограммы.
     Устанавливать переменную надо только вызовом функции set_mode! */
    Uint16 mode_reset;             //!< задается режим работы
    Uint16 mode_reset_prev;        //!< предыдущий режим работы
    int E;                         //!< флаг первого вхождения в состояние

    /*! "control": старшие 16 бит - установка делителя, младшие 16 бит - флаги:
    F E D C B A 9 8 7 6 5 4 3 2 1 0
    | | | | | | | | | | | | | | | |
    | | | | | | | | | | | | первые 4 бита - какие из 4х переменых интересуют (для "старого" 4-канального Юникона)
    | | | | | | | | | | 2 бита - желаемый режим даталоггера: 0, 1, 2
    | | | | | | | | | бит "данные готовы" - устанавливается контроллером
    | | | | | | | | бит "поддерживается блочная передача"
    | | | | | | | бит "32-битные данные"
    | | | число каналов осциллографирования минус 1 (для "нового" N-канального Юникона)
    резерв
    */
    Uint32 control;                  //!< управление даталоггером через внешние программы

    Uint32 ind_subind[DLOG_CHANNELS_NUM];   //!< индекс.подындекс осциллографируемых объектов (устанавливаются внешним ПО, например, Юниконом)

    unsigned int WriteDelimiter;        //!<делитель данных при записи
    unsigned int WriteDelimiterCounter; //!<Счетчик для делителя
    unsigned long next_value_var;   //!<через эту переменную возвращаются записанные значения при считывании внешним ПО:
                                    //!<биты 0-15: значение точки
                                    //!<биты 16-23: Rcounter (отдаваемая точка)
                                    //!<биты 24-25: buff_num (0...3 - для "старого" 4-канального Юникона)
                                    //!<бит 26: флаг, что в поле "значение" - старшие 16 бит точки
                                    //!<бит 27: флаг, что переменная 16-разрядная
                                    //!<биты 28-31: buff_num (0...15 - для "нового" N-канального Юникона)
    Uint16 StartBits;
    int buff_num;               //!<номер канала, из которого идет выдвижение значений в next_value_var
    Uint16 OneShotOperation;    //!<флаг синхронизации осциллографа только по первому событию (переход в 1 возможен только из 2)
    TCo_OdVars *pco_vars;       //!<адрес структуры драйвера CANopen
    Uint32 sampling_rate;       // частота выборки данных (вызова функции 'update'), Гц
    int highPartOfValue;        //!<флаг выдачи старшей части
    TObjectInfo objectInfo[DLOG_CHANNELS_NUM];  //!<информация об осциллографируемых объектах словаря

    void (*update)(volatile struct SDataLog *);         //!<Update function
    int (*try_set_mode)(Uint16 mode_reset, volatile struct SDataLog *); //!<Function to change working mode. Returns 1 on success.
    void (*set_mode)(Uint16 mode_reset, volatile struct SDataLog *);    //!<Function to change working mode (deprecated - use try_set_mode function).
    void (*background_analyzer)(volatile struct SDataLog *);    //!<Background analyzer function
};

typedef volatile struct SDataLog TDataLog;

#if defined(CAN_1_ENABLE) || defined(CAN_A_ENABLE)
#define DLOG_CO_VARS co1_vars
#endif

//! Инициализатор по-умолчанию для данного класса
#define DATALOG_DEFAULTS \
{ \
    .buff = { 0 }, \
    .Wcounter = 0, \
    .Rcounter = 0, \
    .upload_buff = { 0 }, \
    .trig_shift = 0, \
    .trig_shift_int = 0, \
    .first_point_written = 0, \
    .prehistory_length = 0, \
    .valid_points_num = 0, \
    .mode_reset = 2, \
    .mode_reset_prev = 2, \
    .E = 0, \
    .control = (DLOG_CHANNELS_NUM-1) << 9, \
    .ind_subind = { 0 }, \
    .WriteDelimiter = 0, \
    .WriteDelimiterCounter = 0, \
    .next_value_var = 0, \
    .StartBits = 0, \
    .buff_num = 0, \
    .OneShotOperation = 0, \
    .pco_vars = &DLOG_CO_VARS, \
    .sampling_rate = 10000, \
    .highPartOfValue = 0, \
    .objectInfo = { 0 }, \
    .update = data_log_update, \
    .try_set_mode = dlog_try_set_mode, \
    .set_mode = dlog_set_mode, \
    .background_analyzer = dlog_background_analyzer, \
}

//! \memberof TDataLog
void data_log_update(TDataLog*);
//! \memberof TDataLog
int dlog_try_set_mode(Uint16 mode_reset, TDataLog*);
//! \memberof TDataLog
void dlog_set_mode(Uint16 mode_reset, TDataLog*);
//! \memberof TDataLog
void dlog_background_analyzer(TDataLog*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/

