/*!
    Copyright ��� "��� ������"

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
 \brief     ������ ���������� ���
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.1 18/05/2015

 \defgroup  SMProtect ������ �����. (��. TSM_Protect)
 @{
*/

#include "V_ADCCalibration.h"
#include "main.h"

TAdcCalibration adc_calibration = ADC_CALIBRATION_DEFAULTS;

void AdcCalibration_Init(TAdcCalibration *p)
{
	//��������� �� ������� ������ (������-�� ��� ���� � ��������, �� �� ������ ������...)
	p->RefHighChAddr = (Uint16 *) &AdcRegs.REF_HIGH_CH;
	p->RefLowChAddr = (Uint16 *) &AdcRegs.REF_LOW_CH;

	//������� ������ (�������)
	p->RefHighIdealCount = REF_HIGH_IDEAL_COUNT_MK17_1;
	p->RefLowIdealCount = REF_LOW_IDEAL_COUNT_MK17_1;

	//���������� ������� ��������
	p->RefHigh_Filter.T = _IQ(0.001);	//1 ������� ��� ������ ��� � ������������
	p->RefLow_Filter.T = _IQ(0.001);	//1 ������� ��� ������ ��� � ������������
	//������������� ������� ��������
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

//������ �������������� ������������ � �������� ����
//�������:
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
//������������� �������� ����� ��������, � �� ����������
void AdcCalibration_Update(TAdcCalibration *p)
{
	long temp;
	//������� ������ - 12-��������� ����, ����������� �� ������� ���� (������� 4 ���� - �������). ��������� �� � ������ 16.16 ��� ������� ��������, �� � �������.
	p->CalGain = _IQ16div(((long)(p->RefHighIdealCount - p->RefLowIdealCount))<<16,((long)(p->Avg_RefHighActualCount - p->Avg_RefLowActualCount))<<16);	//������� ����������� �������� � ������� 16.16 (��� �������� �����)

	temp = _IQ16div(((long)p->RefLowIdealCount)<<16,p->CalGain);	//��������� ��������� ������� ������ ������ � ������ 16.16 � ����� �� ����������� ��������
	temp = temp>>16;												//��������� ��������� �� 16.16 � ���
	p->CalOffset = p->Avg_RefLowActualCount - temp;					//������� ������������� ��������
	temp = _IQ16div(((long)2048)<<16,p->CalGain);
	temp = temp>>16;
	p->CalOffsetAlt = p->CalOffset + temp;							//������� ������������� �������� ��� ������������� �������

	p->CalOffset <<= 4;												//�������� � ������ ���� ����, ��� � ������ ���
	p->CalOffsetAlt <<= 4;
	p->CalGain <<= 8;												//��������� ����������� �������� � 8.24 ��� ������������� � ������ ���
	p->CalGainAlt = p->CalGain <<1;									//��� �������������� ������ ����������� � 2 ���� ������ - ��������
	p->_1_CalGain = _IQdiv(_IQ(1.0),p->CalGain);					//��� ������������ �������� �� �������

}

//���������� �� ����������.
//-----��� ������������ �������.-----
//	��-������� ������ � ��� ������������ � ����������������� ���:
//	p->Udc_temp = (unsigned int) adc_calibration_vars.ch15;	//����� ������� ������� ������ ��� ���������� ������� ���������� ADCcalibrationDriverUpdate,
															//adc_calibration_vars.chN - ������������ �� ������� �������� ������ ���
//	p->Udc = p->UdcGainNom * ((long) p->Udc_temp + p->Udc_meas_offset);	//p->Udc_meas_offset �������� ����� ������, � p->UdcGainNom ��������� � ����:
//	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain,drv_params._1_Udc_nom);	//p->Udc_meas_gain � ����������� ���������� �������� ����� ������
//	��-������ ����� �������� ���:
//	p->Udc_temp = AdcRegs.ADCRESULT15;	//�������� ������� ��������������� ������ � ������ ���
//	p->Udc = p->UdcGainNom * (p->UdcOffsetNom + (Uint16)p->Udc_temp);	//����������� �������� � �����������, ������� �������� � ���� � ��������:
																		//p->Udc_meas_offset, p->Udc_meas_gain, � ������������� �������� � �����������:
																		//adc_calibration.CalOffset, adc_calibration.CalGain.
																		//������������� ������ � ���� ��������� � ���� �� ������������� � T=1� ������� ������� ���
//	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain,_IQmpy(drv_params._1_Udc_nom, adc_calibration.CalGain));
//	p->UdcOffsetNom = _IQmpy(p->Udc_meas_offset, adc_calibration._1_CalGain) - adc_calibration.CalOffset;
//-----��� ������������� �������.-----
//	����:
//	p->IA_temp = (int) adc_calibration_vars.ch0 ^ 0x8000;	//������������� ������ ��������� �� �������� ���������, ����� ��� -0.5x..+0.5x ������ 0..x
//	p->IA = p->IaGainNom * (((long) p->IA_temp + p->Imeas_a_offset) << 1);	//���������� �� 2 (<<1), ����� ���� -x..+x
//	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain,drv_params._1_I_nom);
//	�����:
//	p->IA_temp = AdcRegs.ADCRESULT0;	//^ 0x8000 �� �����, ��� ��������� � ������������� �������� ��� ������������� �������
//	p->IA = p->IaGainNom * (p->IaOffsetNom + (Uint16)p->IA_temp);
//	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain,_IQmpy(drv_params._1_I_nom, adc_calibration.CalGainAlt));
//	p->IaOffsetNom = _IQmpy(p->Imeas_a_offset, adc_calibration._1_CalGain) - adc_calibration.CalOffsetAlt;	//����� �������� �������� ����������� �������� �� �������������
																											//����������� ��� ������������� ������, �.�. ��-������� ��� ���������� �� 2,
																											//� 1/gain ��� ������������� ������ ��� ��� � 2 ���� ������, ��� 1/gain ��� ��������������
//��� � ������, ����� � ��������� �� ����������� �������� � ������ ����������, � ������ ������������ � ������� - � ����. �� ������ ���������� �������� � ����, � �� ��������������� ����� �������.
//������� AdcCalibration_Update ����� �������� � ����, � AdcCalibration_AvgCalc - � �������������� ����������. ��������� �� ��� �������������� adc_calibration.slow_calc � adc_calibration.ms_calc.

//���������� ������� ������� ���
void AdcCalibration_AvgCalc(TAdcCalibration *p)
{
#if !defined(DEBUG_ON_TABLE)
	p->RefHigh_Filter.input = ((unsigned long)(*(p->RefHighChAddr)))<<12;	//<<12 ��� ������ ��������, �������� ��� ��������� �� ������ ����
	p->RefLow_Filter.input = ((unsigned long)(*(p->RefLowChAddr)))<<12;		//<<12 ��� ������ ��������, �������� ��� ��������� �� ������ ����
#else
	p->RefHigh_Filter.input = ((unsigned long)((p->RefHighIdealCount)))<<16;
	p->RefLow_Filter.input = ((unsigned long)((p->RefLowIdealCount)))<<16;
#endif
	p->RefHigh_Filter.calc(&(p->RefHigh_Filter));
	p->Avg_RefHighActualCount = (Uint16)((p->RefHigh_Filter.output >> 16) & 0x0FFF)+1;
	p->RefLow_Filter.calc(&(p->RefLow_Filter));
	p->Avg_RefLowActualCount = (Uint16)((p->RefLow_Filter.output >> 16) & 0x0FFF)+1;
}
