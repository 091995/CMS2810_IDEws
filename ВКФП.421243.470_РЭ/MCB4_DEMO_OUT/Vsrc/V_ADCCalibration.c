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

#include "V_ADCCalibration.h"
#include "main.h"

TAdcCalibration adc_calibration = ADC_CALIBRATION_DEFAULTS;

void AdcCalibration_Init(TAdcCalibration *p)
{
	//указатели на опорные каналы (вообще-то они есть в дефолтах, но на всякий случай...)
	p->RefHighChAddr = (Uint16 *) &AdcRegs.REF_HIGH_CH;
	p->RefLowChAddr = (Uint16 *) &AdcRegs.REF_LOW_CH;

	//опорные уровни (уставки)
	p->RefHighIdealCount = REF_HIGH_IDEAL_COUNT_MK17_1;
	p->RefLowIdealCount = REF_LOW_IDEAL_COUNT_MK17_1;

	//постоянная времени фильтров
	p->RefHigh_Filter.T = _IQ(0.001);	//1 секунда при вызове раз в миллисекунду
	p->RefLow_Filter.T = _IQ(0.001);	//1 секунда при вызове раз в миллисекунду
	//инициализация выходов фильтров
	p->RefHigh_Filter.output = ((unsigned long)((p->RefHighIdealCount)))<<16;
	p->RefLow_Filter.output = ((unsigned long)((p->RefLowIdealCount)))<<16;

	p->Avg_RefHighActualCount = p->RefHighIdealCount;
	p->Avg_RefLowActualCount = p->RefLowIdealCount;

	p->CalGain = _IQ(1.0);
	p->CalOffset = 0;
	p->CalGainAlt = _IQ(2.0);
	p->CalOffsetAlt = 2048;
	p->_1_CalGain = _IQ(1.0);
}

//расчет калибровочного коэффициента и смещения нуля
//формулы:
//____________________________________________________________
//				 RefHighIdealCount-RefLowIdealCount
//CalGain = --------------------------------------------
//			Avg_RefHighActualCount-Avg_RefLowActualCount
//____________________________________________________________
//CalGainAlt = CalGain*2
//____________________________________________________________
//CalOffset = Avg_RefLowActualCount - RefLowIdealCount/CalGain
//____________________________________________________________
//CalOffsetAlt = CalOffset + 2048/CalGain
//____________________________________________________________
//Калибровочные смещения нужно ВЫЧИТАТЬ, а не прибавлять
void AdcCalibration_Update(TAdcCalibration *p)
{
	long temp;
	//Опорные уровни - 12-разрядные инты, выравненные по правому краю (старшие 4 бита - нулевые). Переводим их в формат 16.16 для большей точности, но с запасом.
	p->CalGain = _IQ16div(((long)(p->RefHighIdealCount - p->RefLowIdealCount))<<16,((long)(p->Avg_RefHighActualCount - p->Avg_RefLowActualCount))<<16);	//считаем коэффициент усиления в формате 16.16 (для расчетов далее)

	temp = _IQ16div(((long)p->RefLowIdealCount)<<16,p->CalGain);	//переводим эталонный опорный низкий сигнал в формат 16.16 и делим на коэффициент усиления
	temp = temp>>16;												//результат переводим из 16.16 в инт
	p->CalOffset = p->Avg_RefLowActualCount - temp;					//считаем калибровочное смещение
	temp = _IQ16div(((long)2048)<<16,p->CalGain);
	temp = temp>>16;
	p->CalOffsetAlt = p->CalOffset + temp;							//считаем калибровочное смещение для разнополярных каналов

	p->CalOffset <<= 4;												//сдвигаем к левому краю инта, как и каналы АЦП
	p->CalOffsetAlt <<= 4;
	p->CalGain <<= 8;												//переводим коэффициент усиления в 8.24 для использования в модуле АЦП
	p->CalGainAlt = p->CalGain <<1;									//для разнополярного канала коэффициент в 2 раза больше - умножаем
	p->_1_CalGain = _IQdiv(_IQ(1.0),p->CalGain);					//для нормирования оффсетов из юникона

}

//ИНСТРУКЦИЯ ПО ПРИМЕНЕНИЮ.
//-----Для ОДНОполярных каналов.-----
//	По-старому данные с АЦП опрашивались и преобразовывались так:
//	p->Udc_temp = (unsigned int) adc_calibration_vars.ch15;	//Перед вызовом функции опроса АЦП вызывалась функция калибровки ADCcalibrationDriverUpdate,
															//adc_calibration_vars.chN - калиброваные по опорным сигналам каналы АЦП
//	p->Udc = p->UdcGainNom * ((long) p->Udc_temp + p->Udc_meas_offset);	//p->Udc_meas_offset задается через юникон, а p->UdcGainNom считается в фоне:
//	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain,drv_params._1_Udc_nom);	//p->Udc_meas_gain и номинальное напряжение задаются через юникон
//	По-новому будет делаться так:
//	p->Udc_temp = AdcRegs.ADCRESULT15;	//Напрямую берутся некалиброванные данные с канала АЦП
//	p->Udc = p->UdcGainNom * (p->UdcOffsetNom + (Uint16)p->Udc_temp);	//Добавляется смещение и коэффициент, которые включают в себя и заданные:
																		//p->Udc_meas_offset, p->Udc_meas_gain, и калбировочные смещение и коэффициент:
																		//adc_calibration.CalOffset, adc_calibration.CalGain.
																		//Калибровочные оффсет и гейн считаются в фоне по фильтрованным с T=1с опорным каналам АЦП
//	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain,_IQmpy(drv_params._1_Udc_nom, adc_calibration.CalGain));
//	p->UdcOffsetNom = _IQmpy(p->Udc_meas_offset, adc_calibration._1_CalGain) - adc_calibration.CalOffset;
//-----Для РАЗНОполярных каналов.-----
//	Было:
//	p->IA_temp = (int) adc_calibration_vars.ch0 ^ 0x8000;	//Калиброванные данные смещаются на половину диапазона, чтобы был -0.5x..+0.5x вместо 0..x
//	p->IA = p->IaGainNom * (((long) p->IA_temp + p->Imeas_a_offset) << 1);	//умножается на 2 (<<1), чтобы было -x..+x
//	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain,drv_params._1_I_nom);
//	Стало:
//	p->IA_temp = AdcRegs.ADCRESULT0;	//^ 0x8000 не нужно, это добавлено в калибровояное смещение для разнополярных каналов
//	p->IA = p->IaGainNom * (p->IaOffsetNom + (Uint16)p->IA_temp);
//	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain,_IQmpy(drv_params._1_I_nom, adc_calibration.CalGainAlt));
//	p->IaOffsetNom = _IQmpy(p->Imeas_a_offset, adc_calibration._1_CalGain) - adc_calibration.CalOffsetAlt;	//здесь заданное смещение нормируется делением на калибровочный
																											//коэффициент для ОДНОполярного канала, т.к. по-старому оно умножалось на 2,
																											//а 1/gain для ОДНОполярного канала как раз в 2 раза больше, чем 1/gain для РАЗНОполярного
//Как и раньше, опрос и умножение на коэффициент делается в нужном прерывании, а расчет коэффициента и оффсета - в фоне. Но теперь калибровка делается в фоне, а не непосредственно перед опросом.
//Функцию AdcCalibration_Update нужно вызывать в фоне, а AdcCalibration_AvgCalc - в миллисекундном прерывании. Указатели на них соответтсвенно adc_calibration.slow_calc и adc_calibration.ms_calc.

//фильтрация опорных каналов АЦП
void AdcCalibration_AvgCalc(TAdcCalibration *p)
{
#if !defined(DEBUG_ON_TABLE)
	p->RefHigh_Filter.input = ((unsigned long)(*(p->RefHighChAddr)))<<12;	//<<12 для лучшей точности, регистры АЦП выравнены по левому краю
	p->RefLow_Filter.input = ((unsigned long)(*(p->RefLowChAddr)))<<12;		//<<12 для лучшей точности, регистры АЦП выравнены по левому краю
#else
	p->RefHigh_Filter.input = ((unsigned long)((p->RefHighIdealCount)))<<16;
	p->RefLow_Filter.input = ((unsigned long)((p->RefLowIdealCount)))<<16;
#endif
	p->RefHigh_Filter.calc(&(p->RefHigh_Filter));
	p->Avg_RefHighActualCount = (Uint16)((p->RefHigh_Filter.output >> 16) & 0x0FFF)+1;
	p->RefLow_Filter.calc(&(p->RefLow_Filter));
	p->Avg_RefLowActualCount = (Uint16)((p->RefLow_Filter.output >> 16) & 0x0FFF)+1;
}
