/*!
    Copyright ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_ADCCalibration.h
 \brief     Модуль калибровки АЦП
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.1 18/05/2015

 \defgroup  SMProtect Модуль защит. (см. TSM_Protect)
 @{
*/

#ifndef V_ADCCALIBRATION_H_
#define V_ADCCALIBRATION_H_

#include "filter.h"
#include "DSP.h"

#define ADC_MK17_1 0
#define ADC_MK17_4 1

//--------------------------------------------------------
// User needs to select ADC sampling mode:
//
// SEQUENTIAL:   ADC channels are converted one at a time:
//               A0->A1->A2->...B0->B1->B2->....
//
// SIMULTANEOUS: ADC channels are converted in pairs:
//               A0->A1->A2->....
//               B0  B1  B2

#define     SEQUENTIAL             1
#define     SIMULTANEOUS           0
#define     ADC_SAMPLING_MODE      SEQUENTIAL


#define PWM_FREQ40 	40E3
#define PWM_FREQ80 	80E3


//--------------------------------------------------------
// Mapping of ADC channels to result registers:
//
#if ADC_SAMPLING_MODE == SEQUENTIAL
#define     A0       ADCRESULT0
#define     A1       ADCRESULT1
#define     A2       ADCRESULT2
#define     A3       ADCRESULT3
#define     A4       ADCRESULT4
#define     A5       ADCRESULT5
#define     A6       ADCRESULT6
#define     A7       ADCRESULT7
#define     B0       ADCRESULT8
#define     B1       ADCRESULT9
#define     B2       ADCRESULT10
#define     B3       ADCRESULT11
#define     B4       ADCRESULT12
#define     B5       ADCRESULT13
#define     B6       ADCRESULT14
#define     B7       ADCRESULT15
#endif

#if ADC_SAMPLING_MODE == SIMULTANEOUS
#define     A0       ADCRESULT0
#define     A1       ADCRESULT2
#define     A2       ADCRESULT4
#define     A3       ADCRESULT6
#define     A4       ADCRESULT8
#define     A5       ADCRESULT10
#define     A6       ADCRESULT12
#define     A7       ADCRESULT14
#define     B0       ADCRESULT1
#define     B1       ADCRESULT3
#define     B2       ADCRESULT5
#define     B3       ADCRESULT7
#define     B4       ADCRESULT9
#define     B5       ADCRESULT11
#define     B6       ADCRESULT13
#define     B7       ADCRESULT15
#endif

//--------------------------------------------------------
// User needs to select refernce channels and ideal values:
//
// For example:  2V  ( 2*4095/3.0 = 2730 ideal count)
//               1V (1*4095/3.0 = 1365 ideal count)
/*
MK17.1
Канал - на тестере - на ADCRESULT - на adc_calibration_vars
ADC6 - 0,99 - 0x5890
ADC7 - 1,95 - 0xAE30


MK17.4
ADC6 - 1.05  - 0x5960 -
ADC7 - 2.048 - 0xAF00 -
*/

#define     REF_HIGH_CH				A7
#define     REF_LOW_CH				A6
#define     REF_HIGH_IDEAL_COUNT_MK17_1	2730
#define     REF_LOW_IDEAL_COUNT_MK17_1 	1365

#define     REF_HIGH_IDEAL_COUNT_MK17_4	2795
#define     REF_LOW_IDEAL_COUNT_MK17_4 	1433

//--------------------------------------------------------
// Structure used for storing calibration parameters and
// results:
//
struct SAdcCalibration
{
  Uint16  *RefHighChAddr;	     	// Channel Address of RefHigh
  Uint16  *RefLowChAddr;       		// Channel Address of RefLow

  TFilter RefHigh_Filter;			// Фильтр для низкого опорного сигнала
  TFilter RefLow_Filter;			// Фильтр для высокого опорного сигнала

  Uint16  Avg_RefHighActualCount;	// Ideal RefHigh Count (16.0)
  Uint16  Avg_RefLowActualCount;	// Ideal RefLow  Count (16.0)
  Uint16  RefHighIdealCount;	 	// Ideal RefHigh Count (16.0)
  Uint16  RefLowIdealCount;	 		// Ideal RefLow  Count (16.0)
  long CalGain; 			 		// Калибровочный коэффициент для однополярных входов (8.24)
  long CalOffset;					// Калибровочное смещение нуля для однополярных входов (16.0)
  long CalGainAlt; 			 		// Калибровочный коэффициент для разнополярных входов (8.24)
  long CalOffsetAlt;				// Калибровочное смещение нуля для разнополярных входов (16.0)
  long _1_CalGain;					// Обратная гейну величина, для нормирования заданного через юникон оффсета (8.24)
  void (*init)(struct SAdcCalibration *);
  void (*slow_calc)(struct SAdcCalibration *);
  void (*ms_calc)(struct SAdcCalibration *);
};
typedef struct SAdcCalibration TAdcCalibration;

#define ADC_CALIBRATION_DEFAULTS {(Uint16 *) &AdcRegs.REF_HIGH_CH,(Uint16 *) &AdcRegs.REF_LOW_CH, \
    FILTER_DEFAULTS,FILTER_DEFAULTS, \
    0,0,0,0,0,0,0,0,0, \
    AdcCalibration_Init,\
    AdcCalibration_Update,\
    AdcCalibration_AvgCalc,\
  }

void AdcCalibration_Init(TAdcCalibration *p);
void AdcCalibration_Update(TAdcCalibration *p);
void AdcCalibration_AvgCalc(TAdcCalibration *p);

extern TAdcCalibration adc_calibration;

#endif /* V_ADCCALIBRATION_H_ */
