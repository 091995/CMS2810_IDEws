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

 \file      V_DIO.h
 \brief     ������ ���������� ������/�������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#ifndef V_DIO_H
#define V_DIO_H

#ifdef __cplusplus
extern "C" {
#endif

// �������� ���������� �����
#ifdef HW_MOTORCONTROLBOARD
#define D_IN1			!GpioDataRegs.GPBDAT.bit.GPIOB13	    //�����
#define D_IN2			!GpioDataRegs.GPADAT.bit.GPIOA11	    //����
#define D_IN3			!GpioDataRegs.GPADAT.bit.GPIOA12	    //����� ������
#else
#define D_IN1	0
#define D_IN2	0
#define D_IN3	0
#endif

// �������� ���������� ������
#ifdef HW_MOTORCONTROLBOARD
#define D_OUT1_ON       GpioDataRegs.GPASET.bit.GPIOA13 = 1;
#define D_OUT1_OFF      GpioDataRegs.GPACLEAR.bit.GPIOA13 = 1;
#define D_OUT2_ON       GpioDataRegs.GPASET.bit.GPIOA14 = 1;
#define D_OUT2_OFF      GpioDataRegs.GPACLEAR.bit.GPIOA14 = 1;
#define D_OUT3_ON       GpioDataRegs.GPASET.bit.GPIOA15 = 1;
#define D_OUT3_OFF      GpioDataRegs.GPACLEAR.bit.GPIOA15 = 1;
#else
#define D_OUT1_ON
#define D_OUT1_OFF
#define D_OUT2_ON
#define D_OUT2_OFF
#define D_OUT3_ON
#define D_OUT3_OFF
#endif


void DIO_Init();
void DIO_slow_calc();	// �������� � ������� ���������
void DIO_fast_calc();	// �������� � �������� 1��� ��� 10 ���


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
