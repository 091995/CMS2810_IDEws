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
 
 \file      V_SSI_Encoder.c
 \brief     Модуль оценки скорости и положения при помощи цифрового энкодера, работающего по интерфейсу SSI (см. TSSI_Encoder)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 25/04/2016

 \addtogroup V_QEP
 @{*/

#include "DSP28_Device.h"
#include "IQmathLib.h"          // библиотека IQmath
#include "V_SSI_Encoder.h"
#include "math.h"
#include "stdlib.h"
#include "main.h"

//! Инициализация

//! \memberof TSSI_Encoder
void SSI_Encoder_init(TSSI_Encoder *p) {
	volatile long delay;
	volatile Uint32 tempREG;
}


//! Функция расчёта скорости и положения, вызывается с необходимой дискретностью
//! \memberof TSSI_Encoder
void SSI_Encoder_Calc(TSSI_Encoder *p) {
	p->read(p);
}

void SSI_Encoder_Read(TSSI_Encoder*p) {
}



/*@}*/

