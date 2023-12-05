
#ifndef MODEL
#include "v_rmp_ctrl.h"
#include "V_IQmath.h"
#include "stdlib.h"
#endif


//! ������� ������� ��������� �������������

//!�������� output � �������� ������ T,
//!���� output �� ��������� input.

//! \memberof TRMPCtrl
void V_RMP_CTRL_calc(TRMPCtrl *p) {
	//����� ������ �����?
	if (p->output < p->input)
		p->output += p->step;//������������ � �������� ������ �����
	if (p->output > p->input)
		p->output -= p->step;

	if ((labs(p->output - p->input) <= p->step) || (p->T==0)) {//����� � ������� � �������� �� ���� ��� �� ������ ��������
		p->output = p->input;//����� ����� �����
	}
}

//! ��������������� ������� ��������� �������������

//!������������� ���� ������� T � ��� step c ������ ������� 
//!������ �������� ������� Ts (�������������, ������ 10���).

//! \memberof TRMPCtrl
void V_RMP_CTRL_slow_calc(TRMPCtrl *p) {
	p->step = _IQdiv(p->Ts, p->T);//��� ����������� ��
}

/*@}*/

