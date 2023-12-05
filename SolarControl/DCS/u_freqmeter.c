
#ifndef MODEL
#include "DCS_func.h"
#include "DCS_base.h"
#endif


void FREQMETER_Init(FREQMETER*p)
{
int ii;
p->a1 = _IQ(1.0);  // ������������ ������� �������� ��� ������ ������ Filt_Bat.mdl
p->a2 = _IQ(-1.822694925196308); 
p->a3 = _IQ(0.837181651256023); 
p->b1 = _IQ(0.003621681514929); 
p->b2 = _IQ(0.007243363029857); 
p->b3 = _IQ(0.003621681514929); 
// ������������� �������� �����/������ ������� ����������
for (ii=0; ii<3; ii++){
	p->out[ii] = 0; 
	p->in[ii] = 0;
}     
// ������������� ������� ���������� ��� �����������
for(ii=0; ii<NIn_uf; ii++) p->MTf[ii] = 330000; 
for(ii=0; ii<NIn_uf; ii++) p->M_fma[ii] = 0; 
// ������������� ������� ���������� ��� �����������
for(ii=0; ii<2; ii++) p->uf[ii] = -1; 
p->nd = 0;
p->Nftek = 0;
p->SumTf = 0;
p->IDTf = 0; 
p->Nf = 50;
p->_1_Nf = _IQdiv(_IQ(1.0),_IQ(p->Nf));
p->flgON1 = 0;
p->T_start = _IQ14mpy(_IQ(0.016),_IQ12(_1_Td)); 

// �������� ����������� �����
p->T_iner = _IQ(0.03);
p->K1_iner = _IQdiv(_IQ(Td),p->T_iner);
p->K2_iner = _IQ(1.0) - p->K1_iner;

p->P_fma = 0;
p->Out_fma = 0;

// ������������
p->fs_out = _IQ(1.0);
p->Ts_out = _IQ30(0.02);
p->out_iner = _IQ30(0.02);
}      

void FREQMETER_Calc(FREQMETER*p){
// ��������� ����������
_iq		delta;    /*������������� ���������� �� ������ �������� ���������� ����� �� �������� �������� uf �� ������������� ������� � �������������*/
int		Tf;

// ********************* "������ ����������" ***************************** //
p->in[0] = p->Ua - _IQmpy2(p->Uc); 
p->out[0] =  _IQmpy(p->in[0],p->b1)\
           + _IQmpy(p->in[1],p->b2)\
           + _IQmpy(p->in[2],p->b3)\
           - _IQmpy(p->out[1],p->a2)\
           - _IQmpy(p->out[2],p->a3); 
// ��������������
p->out[2] = p->out[1];
p->out[1] = p->out[0];
p->in[2]  = p->in[1];
p->in[1]  = p->in[0];

// ********************* "����������� ������� ����" ********************* // 
p->uf[1] = p->uf[0];
p->uf[0] = p->out[0]; 
//���� ���������� � ���� Fl_Us==1 � ( ������ ������� ����� 0 �� + � �.�. ���� flgON1)
if (p->Fl_Us && (((p->uf[0]<0)&&(p->uf[1]>=0))||p->flgON1)) {
	p->flgON1 = 1;
	//���� ������� ����� 0 �� + � - � ����� ������ nd, ������� delta
	if ((p->uf[0]<0)&&(p->uf[1]>=0)&&(p->nd>=p->T_start)) 
	{	//������ ����� �����������
		delta = _IQdiv(p->uf[1],(p->uf[1] + _IQabs(p->uf[0])));
		Tf = _IQ28mpy((p->nd + _IQtoIQ22(delta)),_IQ30(Td));
		p->nd = _IQ22(1.0) - _IQtoIQ22(delta);            
		//� ������ ��� ������� ������ �������
		if (p->Nftek < p->Nf) {
			p->SumTf += Tf;
			p->Nftek += 1;
			p->Ts = _IQtoIQ30(_IQdiv(p->SumTf,_IQ(p->Nftek)));
		}
		else { //����� ������� ���������
			p->SumTf = Tf + p->SumTf - p->MTf[p->IDTf];
			p->Ts = _IQ18mpy(p->SumTf,p->_1_Nf);  // 8.24*8.24=2.30
		}
//		p->Ts = _IQ10toF(_IQ10toF(_IQ4toF(p->Ts)));
		p->MTf[p->IDTf] = Tf;
		p->IDTf++;
		if (p->IDTf>(p->Nf-1)) { p->IDTf = 0; }
    }
	else //���� ��� �������� ����� 0 ������� ����� 
	{ 
		p->nd = p->nd + _IQ22(1.0); 
	}
} //���� ���������� ���, ������ ������������� 50��.
else { p->Ts = _IQ30(0.0200);}

p->Ts_out = p->Ts;
p->fs_out = _IQdiv(_IQ(1.0),(_IQ30mpy(_IQ(Kt_f),(p->Ts_out))));
}
