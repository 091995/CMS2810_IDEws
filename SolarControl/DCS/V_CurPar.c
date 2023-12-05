

/** \addtogroup V_CurPar */
/*@{*/

#ifndef MODEL
#include "DSP.h"
#include "V_IQmath.h"
#include "V_CurPar.h"
#include "main.h"
#endif
//! ������������� ������

//! ���, ����� ���������...
//! \memberof TCurPar
void CurPar_init(TCurPar* p) {
	//�������
	//p->.T = _IQ(0.001);  //������ �������� ��� ������ �� �����

}

//!������ �������� �� ������ ���

//!������ ���������� � ���������� ������� ���������, ����������� � �������
//!��� ������� ������������ ����������� ���������� ��� UalphaRef, UbetaRef,
//!���������� ���� ��� Ialpha, Ibeta. ��� ������ �� ���� ���������� ���������� �� ���,
//!���������� ���������� �������� ����������� � ����������� ��������� �� ������ ���,
//!� ����� ���������� ���������� ���������� �������� ����������� ����������� ������ ������� �������.
//! \memberof TCurPar
void CurPar_PowerCalcUf(TCurPar* p) {
//	p->Ualpha = pwm.UalphaRef;  //���������� �������� ��� �����
//	p->Ubeta = pwm.UbetaRef; //���������� �������� ��� ����
//
//	//���������� �������� �� ���� ����� � ���� �������� �� ���� �������
//	p->fPower.input = _IQmpy(p->PowerK,
//			_IQmpy(p->Ualpha,p->Ialpha)+_IQmpy(p->Ubeta,p->Ibeta));
//
//	//������ �������
//	p->fPower.calc(&p->fPower);
//	//��������� ������ ������� - ������� �������� ��������.
//	p->power = p->fPower.output;
}



//! \memberof TCurPar
void CurPar_fast_calc(TCurPar* p) {

	CurPar_PowerCalcUf(p); //������ ��������

	cur_par.Ia_rms=adc.rms.Ia_inv;
	cur_par.Ib_rms=adc.rms.Ib_inv;
	cur_par.Ic_rms=adc.rms.Ic_inv;

	cur_par.Uab_rms=adc.rms.Uab_inv;
	cur_par.Uab_rms=adc.rms.Ubc_inv;
	cur_par.Uab_rms=adc.rms.Uca_inv;


}

//! \memberof TCurPar
//������ ����������� ��������������� ����������� ��������
//��� ���������� ��������� ����� �������� �������� � ������� �������� drv_params.power
void CurPar_slow_calc(TCurPar* p) {
//	float PowerMaxReal;
//	float PowerMaxScale;
//	PowerMaxReal = (float) inv_params.I_nom * inv_params.U_nom;
//	PowerMaxScale = _IQ6toF(inv_params.P_nom);
//	p->PowerK = _IQmpy(_IQ(PowerMaxReal / PowerMaxScale), _IQ(3.0/2));//����� 3/2 ����� ��� �������������� �������� �� 2� ������� ������������� � 3� �������



}

