/*!
 Copyright 2023 "НПФ ВЕКТОР"

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 \file      Vled.c
 \brief     Управление светодиодами
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup led
 */

#include "DSP28_Device.h"
#include "main.h"

//Для  VectorCARD
#if defined (HW_MOTORCONTROLBOARD) || defined (HW_MOTORCONTROLBOARD_SIMULATOR)

#define VD7_OFF GpioDataRegs.GPESET.bit.GPIOE0 = 1
#define VD7_ON GpioDataRegs.GPECLEAR.bit.GPIOE0 = 1
#define VD7_TOGGLE GpioDataRegs.GPETOGGLE.bit.GPIOE0 = 1

#define VD6_OFF GpioDataRegs.GPFSET.bit.GPIOF14 = 1
#define VD6_ON GpioDataRegs.GPFCLEAR.bit.GPIOF14 = 1
#define VD6_TOGGLE GpioDataRegs.GPFTOGGLE.bit.GPIOF14 = 1

#endif

void LED_init(Tled *p) {
//Для  VectorCARD

	EALLOW;
    GpioMuxRegs.GPEMUX.bit.XINT1_XBIO_GPIOE0 = 0;
    GpioMuxRegs.GPEDIR.bit.GPIOE0 = 1;

    GpioMuxRegs.GPFMUX.bit.XF_GPIOF14 = 0;
    GpioMuxRegs.GPFDIR.bit.GPIOF14 = 1;
    EDIS;
}

void LED_toggle(Tled *p, Uint16 led) {
//Для  VectorCARD
    GpioDataRegs.GPETOGGLE.bit.GPIOE0 = 1;
    GpioDataRegs.GPFTOGGLE.bit.GPIOF14 = 1;
}

void LED_on(Tled *p, Uint16 led) {
//Для  VectorCARD
}

void LED_off(Tled *p, Uint16 led) {
//Для  VectorCARD
}

void LED_clearAll(Tled *p) {
//Для  VectorCARD
}

void LED_msCalc(Tled *p) {
//Для  VectorCARD

#if defined (HW_MOTORCONTROLBOARD) || defined (HW_MOTORCONTROLBOARD_SIMULATOR)

    //светодиоднаЯ интикациЯ на плате контроллера
	if (sm_prot.state == PROT_ON_OK)   //если нет аварии
	{
		p->timer1++;

	    if (sm_ctrl.state==CTRL_STOP)
	    {
	        if (p->timer1 >= 1000) {
	            p->timer1 = 0;
	            VD7_TOGGLE;
	        }
	    }

	    else
	    {
	        if (p->timer1 >= 300) {
	            p->timer1 = 0;
	            VD7_TOGGLE;
	         }
	    }

		VD6_OFF;
	}

	else  	//если есть авария
	{
		p->timer2++;

        if (p->timer2 >= 500) {
            p->timer2 = 0;
            VD6_TOGGLE;
        }

        VD7_OFF;
	}

#endif

}

