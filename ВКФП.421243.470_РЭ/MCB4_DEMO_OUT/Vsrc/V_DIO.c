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

 \file      V_DIO.c
 \brief     Модуль дискретных входов/выходов
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/



#include "main.h"

void DIO_Init()
{
#if defined (HW_MOTORCONTROLBOARD)
    EALLOW;
    //Проинитим дискретные входы
    // Вход "Старт"
    GpioMuxRegs.GPBMUX.bit.C4TRIP_GPIOB13 = 0;
    GpioMuxRegs.GPBDIR.bit.GPIOB13 = 0;
    // Вход "Стоп"
    GpioMuxRegs.GPAMUX.bit.TDIRA_GPIOA11 = 0;
    GpioMuxRegs.GPADIR.bit.GPIOA11 = 0;
    // Вход "Сброс Аварии"
    GpioMuxRegs.GPAMUX.bit.TCLKINA_GPIOA12 = 0;
    GpioMuxRegs.GPADIR.bit.GPIOA12 = 0;

	//Проинитим дискретные выходы
    // Выход 1
    GpioMuxRegs.GPAMUX.bit.C1TRIP_GPIOA13 = 0;
    GpioMuxRegs.GPADIR.bit.GPIOA13 = 1;
    // Выход 2
    GpioMuxRegs.GPAMUX.bit.C2TRIP_GPIOA14 = 0;
    GpioMuxRegs.GPADIR.bit.GPIOA14 = 1;
    // Выход 3"
    GpioMuxRegs.GPAMUX.bit.C3TRIP_GPIOA15 = 0;
    GpioMuxRegs.GPADIR.bit.GPIOA15 = 1;
    EDIS;
#endif
}


void DIO_slow_calc()
{
    //TODO: если надо, сделать обработку
    // Пользовательская функция
}


void DIO_fast_calc()
{
    //TODO: если надо, сделать обработку
    // Пользовательская функция
}

/*@}*/

