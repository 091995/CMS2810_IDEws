
#ifndef MODEL
#include "v_rmp_ctrl.h"
#include "V_IQmath.h"
#include "stdlib.h"
#endif


//! Функция расчета задатчика интенсивности

//!Изменяет output с заданным темпом T,
//!пока output не достигнет input.

//! \memberof TRMPCtrl
void V_RMP_CTRL_calc(TRMPCtrl *p) {
	//выход меньше входа?
	if (p->output < p->input)
		p->output += p->step;//увелчичиваем с заданным темпом выход
	if (p->output > p->input)
		p->output -= p->step;

	if ((labs(p->output - p->input) <= p->step) || (p->T==0)) {//вошли в задание с точность до шага или ЗИ вообще отключен
		p->output = p->input;//выход равен входу
	}
}

//! Вспомогательная функция задатчика интенсивности

//!Пересчитывает темп разгона T в шаг step c учетом частоты 
//!вызова основной функции Ts (дискретизация, обычно 10кГц).

//! \memberof TRMPCtrl
void V_RMP_CTRL_slow_calc(TRMPCtrl *p) {
	p->step = _IQdiv(p->Ts, p->T);//шаг интегратора ЗИ
}

/*@}*/

