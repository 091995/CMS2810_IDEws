

/** \addtogroup V_CurPar */
/*@{*/

#ifndef MODEL
#include "DSP.h"
#include "V_IQmath.h"
#include "V_CurPar.h"
#include "main.h"
#endif
//! Инициализация модуля

//! Так, всяие обнуления...
//! \memberof TCurPar
void CurPar_init(TCurPar* p) {
	//фильтры
	//p->.T = _IQ(0.001);  //фильтр мощности для вывода на экран

}

//!Расчет мощности из данных фаз

//!Расчет происходит в двухфазной системе координат, привязанной к статору
//!Для расчета используются мгнованнеые напряжения фаз UalphaRef, UbetaRef,
//!мгнованные токи фаз Ialpha, Ibeta. Для каждой из осей напряжение умножается на ток,
//!полученная мгновенная мощность суммируется с аналогичной мощностью по другой оси,
//!а затем полученная суммартная мгновенная мощность фильтруется инерционным звеном первого порядка.
//! \memberof TCurPar
void CurPar_PowerCalcUf(TCurPar* p) {
//	p->Ualpha = pwm.UalphaRef;  //Напряжение заданное оси альфа
//	p->Ubeta = pwm.UbetaRef; //Напряжение заданное оси бета
//
//	//мгновенная мощность по осям альфа и бета подается на вход фильтра
//	p->fPower.input = _IQmpy(p->PowerK,
//			_IQmpy(p->Ualpha,p->Ialpha)+_IQmpy(p->Ubeta,p->Ibeta));
//
//	//расчет фильтра
//	p->fPower.calc(&p->fPower);
//	//результат работы фильтра - текущая активная мощность.
//	p->power = p->fPower.output;
}



//! \memberof TCurPar
void CurPar_fast_calc(TCurPar* p) {

	CurPar_PowerCalcUf(p); //Расчет мощности

	cur_par.Ia_rms=adc.rms.Ia_inv;
	cur_par.Ib_rms=adc.rms.Ib_inv;
	cur_par.Ic_rms=adc.rms.Ic_inv;

	cur_par.Uab_rms=adc.rms.Uab_inv;
	cur_par.Uab_rms=adc.rms.Ubc_inv;
	cur_par.Uab_rms=adc.rms.Uca_inv;


}

//! \memberof TCurPar
//Расчет внутреннего масштабирующего коэффицента мощности
//для приведения различных типов расчетов мощности к базовой мощности drv_params.power
void CurPar_slow_calc(TCurPar* p) {
//	float PowerMaxReal;
//	float PowerMaxScale;
//	PowerMaxReal = (float) inv_params.I_nom * inv_params.U_nom;
//	PowerMaxScale = _IQ6toF(inv_params.P_nom);
//	p->PowerK = _IQmpy(_IQ(PowerMaxReal / PowerMaxScale), _IQ(3.0/2));//дробь 3/2 нужна для преобразования мощности от 2х фазного представления к 3х фазному



}

