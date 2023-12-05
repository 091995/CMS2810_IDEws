/*!
 Copyright 2019  A&D
 \file      V_GridModel.с
 \brief     Модуль моделей электрической сети (см. TGridModel)
 \author
 \version   v 1.0 23/05/2019

 \addtogroup V_GridModel
 @{ */
#ifndef MODEL
#include "V_GridModel.h"
#include "V_GridParams.h"
#include "math.h"
#include  "V_IQmath.h"
#include "main.h"
#endif

#define ADC_MAX_VALUE 4095
#define ADC_HALF_VALUE 2047

//функция случайного "шума" для АЦП
int Model_fastrand() {
	static unsigned long g_seed;
	g_seed = (214013 * g_seed + 2531011);
	return ((g_seed >> 16) & 0x3) - 2;
}

//инициализация переменных модели
void GridModel_Init(TGridModel *p) {

	int i = 0;

}

//основная функция расчета модели, вызывается в рперывании 10 кГц
void GridModel_Execute(TGridModel *p) {

//	p->motorInternals.cmpr0 = p->motorInternals.tpr - p->cmpr0;	//уставки сравнения ШИМ. С инверсией, потому что так настроен модуль ШИМ
//	p->motorInternals.cmpr1 = p->motorInternals.tpr - p->cmpr1;
//	p->motorInternals.cmpr2 = p->motorInternals.tpr - p->cmpr2;
//	p->motorInternals.cmpr3 = p->motorInternals.tpr - p->cmpr3;
//
//	if (p->fault == 0)		//если нет ошибки модели, считаем
//			{
////		if (p->motorInternals.type == MODEL_INDUCTION_MOTOR) {
////			Model_Execute_InductionMotor(p);
/////....
//	} else {		//модель в аварии
//		p->motorInternals.iAtemp = ADC_HALF_VALUE;
//		p->motorInternals.iBtemp = ADC_HALF_VALUE;
//		p->motorInternals.iCtemp = ADC_HALF_VALUE;
//		p->motorInternals.iDtemp = ADC_HALF_VALUE;
//
//	}
//
//
////	p->motorInternals.omega_rpm = p->motorInternals.omega * MODEL_INV_2PI * 60;	//Частота вращения вала из рад/с в об/мин
////	p->motorInternals.Udc_temp = p->motorInternals.udc
////			* p->motorInternals.udSenseK;	//Имитация измерения напряжения ЗПТ
//
//	//наложение шума АЦП
//	p->motorInternals.iAtemp += MotorModel_fastrand();
//	p->motorInternals.iBtemp += MotorModel_fastrand();
//	p->motorInternals.iCtemp += MotorModel_fastrand();
//	p->motorInternals.iDtemp += MotorModel_fastrand();
//	p->motorInternals.adcSpeedtemp += MotorModel_fastrand();
//	p->motorInternals.Udc_temp += MotorModel_fastrand();
//
//	//насыщение каналов АЦП
//	if (p->motorInternals.iAtemp > ADC_MAX_VALUE)
//		p->motorInternals.iAtemp = ADC_MAX_VALUE;
//	if (p->motorInternals.iAtemp < 0)
//		p->motorInternals.iAtemp = 0;
//	if (p->motorInternals.iBtemp > ADC_MAX_VALUE)
//		p->motorInternals.iBtemp = ADC_MAX_VALUE;
//	if (p->motorInternals.iBtemp < 0)
//		p->motorInternals.iBtemp = 0;
//	if (p->motorInternals.iCtemp > ADC_MAX_VALUE)
//		p->motorInternals.iCtemp = ADC_MAX_VALUE;
//	if (p->motorInternals.iCtemp < 0)
//		p->motorInternals.iCtemp = 0;
//	if (p->motorInternals.iDtemp > ADC_MAX_VALUE)
//		p->motorInternals.iDtemp = ADC_MAX_VALUE;
//	if (p->motorInternals.iDtemp < 0)
//		p->motorInternals.iDtemp = 0;
//	if (p->motorInternals.adcSpeedtemp > ADC_MAX_VALUE)
//		p->motorInternals.adcSpeedtemp = ADC_MAX_VALUE;
//	if (p->motorInternals.adcSpeedtemp < 0)
//		p->motorInternals.adcSpeedtemp = 0;
//	if (p->motorInternals.Udc_temp > ADC_MAX_VALUE)
//		p->motorInternals.Udc_temp = ADC_MAX_VALUE;
//	if (p->motorInternals.Udc_temp < 0)
//		p->motorInternals.Udc_temp = 0;
//
//	p->adc_code_iA = p->motorInternals.iAtemp;
//	p->adc_code_iB = p->motorInternals.iBtemp;
//	p->adc_code_iC = p->motorInternals.iCtemp;
//	p->adc_code_iD = p->motorInternals.iDtemp;
//	p->adc_code_Speed = p->motorInternals.adcSpeedtemp;
//	p->adc_code_Udc = p->motorInternals.Udc_temp;

}

/*@}*/
