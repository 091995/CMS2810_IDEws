
#ifndef MODEL
#include "V_IQmath.h"         /* Include header for IQmath library */
#include "DCS_func.h"
#endif


void generator_calc(TGenerator *v) {

	//����� ������ �����?
	if (gen.w_e < _IQ(1))
		gen.w_e += gen.step;//������������ � �������� ������ �����
	if (gen.w_e > _IQ(1))
		gen.w_e -= gen.step;

	if (labs(gen.w_e - _IQ(1)) <= gen.step) {//����� � ������� � �������� �� ���� ��� �� ������ ��������
		gen.w_e = _IQ(1);//����� ����� �����
	}

	//added ramp here gen.w_e =  _IQ(1);// TODO5 - for 1st day only , shuld be replaced with ramp

	gen.wt+=_IQmpy(gen.w_e,_IQ(Td))*50;
	gen.wt&=0xffffff;

}

/*@}*/

