
#ifndef MODEL
#include "V_IQmath.h"         /* Include header for IQmath library */
#include "DCS_func.h"
#endif


void generator_calc(TGenerator *v) {

	//выход меньше входа?
	if (gen.w_e < _IQ(1))
		gen.w_e += gen.step;//увелчичиваем с заданным темпом выход
	if (gen.w_e > _IQ(1))
		gen.w_e -= gen.step;

	if (labs(gen.w_e - _IQ(1)) <= gen.step) {//вошли в задание с точность до шага или ЗИ вообще отключен
		gen.w_e = _IQ(1);//выход равен входу
	}

	//added ramp here gen.w_e =  _IQ(1);// TODO5 - for 1st day only , shuld be replaced with ramp

	gen.wt+=_IQmpy(gen.w_e,_IQ(Td))*50;
	gen.wt&=0xffffff;

}

/*@}*/

