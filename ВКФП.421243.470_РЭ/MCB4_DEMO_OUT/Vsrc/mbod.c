/*!
    Copyright 2023 	ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      mbod.c
 \brief     Словарь объектов MODBUS
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
*/

/** \addtogroup MODBUS */
/*@{*/

#include "mbod.h"
#include "main.h"


/* Тестовые посылки
 * Формат байт в посылке:
 * Номер узла 1 байт, функция 1 байт, адрес 2 байта, данные/кол-во переменных 2 байта, контрольная сумма CRC16(LH)
 * Удобно тестировать, например, программой COMpump
 *
01 06 07 D0 00 64 88 AC // Запись в параметр 2000 числа 100
01 03 07 D0 00 01 84 87 // Запрос параметра 2000

В массивах:
mbodHR - переменные Holding Registers (на чтение и запись). Код функции	0x03(на чтение) 0x06(на запись)
mbodIR - переменные Input Registers (на чтение). Код функции	0x04
mbodC - битовые переменные Coil (для записи). Код функции 0x05(на запись)
mbodDI - битовые переменные Discrete Inputs (для чтения). Код функции 0x02(на чтение)

Первая цифра массива - адрес переменной в словаре  ModBus.
Вторая - номер бита для битовых переменных в переменной контроллера.
Третья - адрес переменной.


*/

#warning заполнить словарь при необходимости
volatile MB_Record mbodHR[] = {\
		2000,  0,(long)(&DebugW1),/*тестовая переменная для проверки работы ModBus */\
        0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
};

volatile MB_Record mbodIR[] = {\
                           	0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
                           	};

volatile MB_Record mbodC[] =  {\
                           	0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
                            };



volatile MB_Record mbodDI[] =  {0,0,0	// конец массива, не удалять - по нулям определятеся размер словаря.
                          	};

/*@}*/
