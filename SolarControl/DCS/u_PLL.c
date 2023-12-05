#ifndef MODEL
#include "DCS_func.h"

#endif

#include "DCS_base.h"



void PLL_Init(PLL*p)
{
int ii;
p->fi	= 0;            
p->Um1		= 0;
p->Um2		= 0;
p->Um220	= 0;
p->K_Tf 	= _IQ(1.0);
p->K_ff    = _IQdiv(_IQ(1.0),p->K_Tf);
p->Const_Nf = _IQ22floor(_IQmpy((_IQmpy(_IQ30(0.02),p->K_Tf)),_IQ16(_1_Td)));

p->Top_lim_osc = _IQ(2.0);
p->Bot_lim_osc = _IQ(0.0);


for (ii=0;ii<SizeM;ii++){
    p->MInt1[ii] = 0;
    p->MInt2[ii] = 0;
    p->MInt3[ii] = 0;
    p->MInt4[ii] = 0;
    p->MInt5[ii] = 0;
    p->MInt6[ii] = 0;
    p->MInt7[ii] = 0;
}
p->IntTf_inp1	= 0;
p->IntTf_inp2	= 0;
p->IntTf_inp3	= 0;
p->IntTf_inp4	= 0;
p->IntTf_inp5	= 0;
p->IntTf_inp6	= 0;
p->IntTf_inp7	= 0;

p->P_wr			= 0;

p->w_e			= _IQ(1.0);
p->wt_e			= 0;

p->Fl_sc		= 0;
p->Fl_sc_ext	= 0;
p->Cnt_sc		= 0;

	p->T_iner = _IQ(0.03);
	p->_1_T_iner_um2 = _IQdiv(_IQ(1.0),p->T_iner);
	p->K1 = _IQmpy(_IQ(Td),p->_1_T_iner_um2);
	p->K2 = _IQ(1.0) - p->K1;
	p->Iner_Um2 = 0;
	p->Kp_Lim_um2 = _IQ(7.0);

}

void PLL_Calc(PLL*p){
int ii;
// Локальные переменные
_iq	inp1;		// Входы фильтра среднего
_iq	out1;		// Выходы фильтра среднего
_iq	Int1;		// Элементы сохранyемые в массиве интегратора
_iq	inp2;
_iq	out2;
_iq	Int2;
_iq	inp3;
_iq	out3;
_iq	Int3;
_iq	inp4;
_iq	out4;
_iq	Int4;
_iq	inp5;
_iq	out5;
_iq	Int5;
_iq	inp6;
_iq	out6;
_iq	Int6;
_iq	inp7;
_iq	out7;
_iq	Int7;

_iq	Tf;			// _iq30 Период усреднениy
_iq	ff;			// Частота усреднениy
_iq	Tf_Td;		// _iq19 Отношение Tf/Td
int		NTf;		// Целое число тактов, укладывающихсy в периоде усреднениy(при Tp не равном 0.02c)
int		P_Const_Nf;	// Целое число тактов, укладывающихсy в периоде усреднениy(при Tp = 0.02c)
_iq		Delta_t_Td;	// Относительное значение дельта_t не кратное Td
int		Delta_NTf;	// Разница между NTf и Const_Nf
int		P_Nf;		// Указатель массива интегралов на Tf назад (при Tp не равном 0.02c)
int		k;
_iq	Ua_pps;
_iq	Ua_nps;
_iq	Ub_pps;
_iq	Ub_nps;
_iq	Uc_pps;
_iq	Uc_nps;

_iq	Tmp1;
_iq	Tmp2;
_iq	Tmp3;
_iq	Tmp4;
_iq	Tmp5;
_iq	Tmp6;
//_iq	Tmp7;
///////////////////////////////////////////////////////////////////////
////  ЗАЩИТА НА КОЛ. yЧЕЕК   //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

	p->K1 = _IQmpy(_IQ(Td),p->_1_T_iner_um2);
	p->K2 = _IQ(1.0) - p->K1;

  // Формирование напрyжениy внутреннего генератора
  	p->w_e		= _IQmpy(p->fs,_IQ(Kf_w)); 
	p->wt_e	= p->wt_e + _IQ30mpy(_IQmpy(p->w_e,_IQ30(Td)),_IQ(Kwt_fi));	// За 1 период вектор поворачиваетсy на 1(отн.ед)
	//if (p->wt_e>_IQ(1.0)) {p->wt_e=p->wt_e-_IQ(1.0);}						//ограничение NTf на максинально возможном размере массива
	p->wt_e&=0xffffff;
	p->Ea_sin	= _IQsinPU(p->wt_e);
	p->Eb_sin	= _IQsinPU((p->wt_e-_IQ(1.0/3.0)));
	p->Ec_sin	= _IQsinPU((p->wt_e+_IQ(1.0/3.0)));
	p->Ea_cos	= _IQcosPU(p->wt_e);
	p->Eb_cos	= _IQcosPU((p->wt_e-_IQ(1.0/3.0)));
	p->Ec_cos	= _IQcosPU((p->wt_e+_IQ(1.0/3.0)));

  // Исключение 3-ей гармоники
	p->Ua_conv = _IQmpy((_IQmpy2(p->Ua) - p->Ub - p->Uc),_IQ(1.0/3.0));		// Ua = 1/3*(2*Ua-Ub-Uc) 
	p->Ub_conv = _IQmpy((_IQmpy2(p->Ub) - p->Uc - p->Ua),_IQ(1.0/3.0));		// Ub = 1/3*(2*Ub-Uc-Ua) 
	p->Uc_conv = - p->Ua_conv - p->Ub_conv;

  // Исключение 3-ей гармоники сети 220кВ
	p->Ua220_conv = _IQmpy((_IQmpy2(p->Ua220) - p->Ub220 - p->Uc220),_IQ(1.0/3.0));		// Ua = 1/3*(2*Ua-Ub-Uc) 
	p->Ub220_conv = _IQmpy((_IQmpy2(p->Ub220) - p->Uc220 - p->Ua220),_IQ(1.0/3.0));		// Ub = 1/3*(2*Ub-Uc-Ua) 
	p->Uc220_conv = _IQmpy((_IQmpy2(p->Uc220) - p->Ua220 - p->Ub220),_IQ(1.0/3.0));		// Ub = 1/3*(2*Ub-Uc-Ua) 
	p->Uc220_conv = - p->Ua220_conv - p->Ub220_conv;

  // Определение перехода между алгоритмами модулyции
	Tmp1 = p->Ua220_conv;
	if (p->Ua220_conv < 0) {Tmp1 = -p->Ua220_conv;}
	Tmp2 = p->Ub220_conv;
	if (p->Ub220_conv < 0) {Tmp2 = -p->Ub220_conv;}
	Tmp3 = p->Uc220_conv;
	if (p->Uc220_conv < 0) {Tmp3 = -p->Uc220_conv;}
	p->Ua_meas = Fmax_3(Tmp1,Tmp2,Tmp3);
	Tmp4 = Fmax_3(Tmp1,Tmp2,Tmp3);
	if (Tmp4<_IQ(0.4)) {
		p->Fl_sc = 1;
		p->Cnt_sc = 0;
	}
	p->Cnt_sc++;
	if (p->Cnt_sc >= 700){
		p->Fl_sc = 0;
		p->Cnt_sc = 700;
	}
//	p->Fl_sc = (p->Fl_sc)||(p->Fl_sc_ext);

  // Координаты вектора ПП сети
	p->D_cord = _IQmpy((_iq)(_IQmpy(p->Ua_conv,p->Ea_sin)+\
						 _IQmpy(p->Ub_conv,p->Eb_sin)+\
						 _IQmpy(p->Uc_conv,p->Ec_sin)),_IQ(2.0/3.0));
	p->Q_cord = _IQmpy((_iq)(_IQmpy(p->Ua_conv,p->Ea_cos)+\
						 _IQmpy(p->Ub_conv,p->Eb_cos)+\
						 _IQmpy(p->Uc_conv,p->Ec_cos)),_IQ(2.0/3.0));
	p->Tmp0 = p->D_cord;
	p->Tmp1 = p->Q_cord;

  // Координаты вектора ОП сети //DBG104
	p->D_cord2 = _IQmpy((_iq)(_IQmpy(p->Ua_conv,p->Ea_sin)+\
				  		  _IQmpy(p->Ub_conv,p->Ec_sin)+\
				  		  _IQmpy(p->Uc_conv,p->Eb_sin)),_IQ(2.0/3.0));
	p->Q_cord2 = _IQmpy((_iq)(_IQmpy(p->Ua_conv,p->Ea_cos)+\
				  		  _IQmpy(p->Ub_conv,p->Ec_cos)+\
				  		  _IQmpy(p->Uc_conv,p->Eb_cos)),_IQ(2.0/3.0));
  // Координаты вектора ПП сети 220кВ
	p->D220_cord = _IQmpy((_iq)(_IQmpy(p->Ua220_conv,p->Ea_sin)+\
							_IQmpy(p->Ub220_conv,p->Eb_sin)+\
							_IQmpy(p->Uc220_conv,p->Ec_sin)),_IQ(2.0/3.0));
	p->Q220_cord = _IQmpy((_iq)(_IQmpy(p->Ua220_conv,p->Ea_cos)+\
							_IQmpy(p->Ub220_conv,p->Eb_cos)+\
							_IQmpy(p->Uc220_conv,p->Ec_cos)),_IQ(2.0/3.0));


	// Вход фильтра среднего 
    //"**********
	inp1 = p->D_cord; 
	inp2 = p->Q_cord; 
	inp3 = p->D_cord2;
	inp4 = p->Q_cord2;
	inp5 = p->D220_cord;
	inp6 = p->Q220_cord;
	inp7 = p->Udc; 
    //"**********
	Int1 = _IQmpy(_IQ30(Td),inp1);   //old_FtoIQ30
	Int2 = _IQmpy(_IQ30(Td),inp2);   
	Int3 = _IQmpy(_IQ30(Td),inp3);
	Int4 = _IQmpy(_IQ30(Td),inp4);
	Int5 = _IQmpy(_IQ30(Td),inp5);
	Int6 = _IQmpy(_IQ30(Td),inp6);
	Int7 = _IQmpy(_IQ30(Td),inp7);
          
    Tf		= _IQmpy(p->Ts,p->K_Tf);		//0,02(2.30)*5(8.24)=0.1(2.30)
    ff		= _IQmpy(p->fs,p->K_ff);		//1(8.24)*2(8.24)=(8.24)
    Tf_Td	= _IQ27mpy(Tf,_IQ16(_1_Td));	//0,1(2.30)*10000(16.16)=(13.19)  
    NTf		= _IQ19floor(Tf_Td);			// округлyем до меньшего
	if (NTf>SizeM) {NTf = SizeM;}			//ограничение NTf на максинально возможном размере массива
    
  // Расчет адреса элемента массива, вычитаемого из интеграла 
    P_Const_Nf = p->P_wr - p->Const_Nf;
	if (P_Const_Nf<0) {P_Const_Nf += SizeM;}
         
  // Интеграл за Tf при fp=50Гц
    //"**********
	p->IntTf_inp1 = p->IntTf_inp1 + Int1 - p->MInt1[P_Const_Nf];
	p->IntTf_inp2 = p->IntTf_inp2 + Int2 - p->MInt2[P_Const_Nf];
	p->IntTf_inp3 = p->IntTf_inp3 + Int3 - p->MInt3[P_Const_Nf];
	p->IntTf_inp4 = p->IntTf_inp4 + Int4 - p->MInt4[P_Const_Nf];
	p->IntTf_inp5 = p->IntTf_inp5 + Int5 - p->MInt5[P_Const_Nf];
	p->IntTf_inp6 = p->IntTf_inp6 + Int6 - p->MInt6[P_Const_Nf];
	p->IntTf_inp7 = p->IntTf_inp7 + Int7 - p->MInt7[P_Const_Nf];

    Delta_t_Td = _IQ19toIQ(Tf_Td - INTtoIQ19(NTf));     
    Delta_NTf  = NTf - p->Const_Nf;        
    
    P_Nf = p->P_wr - NTf;
	if (P_Nf<0){P_Nf += SizeM;}

	// Добавка некратнаy Td
    //"**********
	out1 = p->IntTf_inp1 + _IQmpy(Delta_t_Td,p->MInt1[P_Nf]); 
	out2 = p->IntTf_inp2 + _IQmpy(Delta_t_Td,p->MInt2[P_Nf]); 
	out3 = p->IntTf_inp3 + _IQmpy(Delta_t_Td,p->MInt3[P_Nf]);
	out4 = p->IntTf_inp4 + _IQmpy(Delta_t_Td,p->MInt4[P_Nf]);
	out5 = p->IntTf_inp5 + _IQmpy(Delta_t_Td,p->MInt5[P_Nf]);
	out6 = p->IntTf_inp6 + _IQmpy(Delta_t_Td,p->MInt6[P_Nf]);
	out7 = p->IntTf_inp7 + _IQmpy(Delta_t_Td,p->MInt7[P_Nf]);
       
// Добавка кратнаy Td
    if (NTf > p->Const_Nf){          
       k=P_Const_Nf;             
       for (ii = 1; ii <= Delta_NTf;ii++){                 
           if (k<0) {k+=SizeM;}
           //"**********
			out1 += p->MInt1[k];
			out2 += p->MInt2[k];
			out3 += p->MInt3[k];
			out4 += p->MInt4[k];
			out5 += p->MInt5[k];
			out6 += p->MInt6[k];
			out7 += p->MInt7[k];
			k--;                   
       }                                
    }                                   
    else{                              
       k=P_Const_Nf+1;         
       for (ii = 1; (ii <= (-Delta_NTf));ii++){
           if (k>(SizeM-1)) {k-=SizeM;}
           //"**********
			out1 -=p->MInt1[k];
			out2 -=p->MInt2[k];
			out3 -=p->MInt3[k];
			out4 -=p->MInt4[k];
			out5 -=p->MInt5[k];
			out6 -=p->MInt6[k];
			out7 -=p->MInt7[k];
           k++;                 
       }                              
    }                                   

    //"**********                                         
	out1 = _IQmpy(_IQmpy(out1,ff),_IQ(f_bas));
	out2 = _IQmpy(_IQmpy(out2,ff),_IQ(f_bas));
	out3 = _IQmpy(_IQmpy(out3,ff),_IQ(f_bas));
	out4 = _IQmpy(_IQmpy(out4,ff),_IQ(f_bas));
	out5 = _IQmpy(_IQmpy(out5,ff),_IQ(f_bas));
	out6 = _IQmpy(_IQmpy(out6,ff),_IQ(f_bas));
	out7 = _IQmpy(_IQmpy(out7,ff),_IQ(f_bas));

	//"**********
	p->MInt1[p->P_wr] = Int1;       
	p->MInt2[p->P_wr] = Int2;       
	p->MInt3[p->P_wr] = Int3;
	p->MInt4[p->P_wr] = Int4;
	p->MInt5[p->P_wr] = Int5;
	p->MInt6[p->P_wr] = Int6;
	p->MInt7[p->P_wr] = Int7;

    p->P_wr++;                              
    if (p->P_wr==SizeM) p->P_wr=0;  

  // Выход 
    //"**********
	p->D_cord		= _IQ30toIQ(out1);
	p->Q_cord		= _IQ30toIQ(out2);
	p->D_cord2		= _IQ30toIQ(out3);
	p->Q_cord2		= _IQ30toIQ(out4);
	p->D220_cord	= _IQ30toIQ(out5);
	p->Q220_cord	= _IQ30toIQ(out6);
	p->Udc			= _IQ30toIQ(out7);


	p->fi = _IQatan2PU(p->Q_cord,p->D_cord);
	p->alpha = p->wt_e + p->fi;
	p->alpha&=0x00ffffff;

	p->Um1 = _IQmag(p->Q_cord,p->D_cord);
	// Длy исключениy ошибки делениy на Um1
	if (p->Um1 > _IQ(2.0)) p->Um1 = _IQ(2.0);
	if (p->Um1 < _IQ(0.000001)) p->Um1 = _IQ(0.000001);    

	p->betta = _IQatan2PU(p->Q_cord2,p->D_cord2) - p->fi;
	p->Um2 = _IQmag(p->Q_cord2,p->D_cord2);

// Ограничение мощности с учетом ОП
//	p->K1 = _IQdiv(_IQ(Td),p->T_iner);  //CORRECT_000
//	p->K2 = _IQ(1.0) - p->K1;

	p->Iner_Um2	= _IQmpy(p->Iner_Um2,p->K2) + _IQmpy(p->Um2,p->K1);
	Tmp1 = p->Iner_Um2 - _IQ(0.02);
	Tmp1 = _IQmpy(Tmp1,p->Kp_Lim_um2);
	if (Tmp1>_IQ(1.0)) Tmp1 = _IQ(1.0);
	if (Tmp1<_IQ(0.0)) Tmp1 = _IQ(0.0);
	p->K_um2_pow = Tmp1;


	p->Um220 = _IQmag(p->Q220_cord,p->D220_cord);

	Tmp1 = p->wt_e + p->fi;
	Tmp2 = Tmp1 + p->betta;
	Tmp3 = Tmp1 - _IQ(1.0/3.0);
	Tmp4 = Tmp1 + _IQ(1.0/3.0) + p->betta;
	Tmp5 = Tmp1 + _IQ(1.0/3.0);
	Tmp6 = Tmp1 - _IQ(1.0/3.0) + p->betta;

	Ua_pps = _IQmpy(p->Um1,(_IQsinPU(Tmp1)));
	Ua_nps = _IQmpy(p->Um2,(_IQsinPU(Tmp2)));
	p->Ua_meas = Ua_nps + Ua_pps; //  
	Ub_pps = _IQmpy(p->Um1,(_IQsinPU(Tmp3)));
	Ub_nps = _IQmpy(p->Um2,(_IQsinPU(Tmp4)));
	p->Ub_meas = Ub_nps + Ub_pps; // 
	Uc_pps = _IQmpy(p->Um1,(_IQsinPU(Tmp5)));
	Uc_nps = _IQmpy(p->Um2,(_IQsinPU(Tmp6)));
	p->Uc_meas = Uc_nps + Uc_pps;//  

    // Флаг поyвлениy сети длy частотомера
	p->Fl_Us = 0;
    if (p->Um1 >= _IQ(0.5)) p->Fl_Us = 1;

	p->Ea_sin1	= _IQsinPU((p->wt_e + p->fi));
	p->Eb_sin1	= _IQsinPU((p->wt_e + p->fi - _IQ(1.0/3.0)));
	p->Ec_sin1	= _IQsinPU((p->wt_e + p->fi + _IQ(1.0/3.0)));
	p->Ea_cos1	= _IQcosPU((p->wt_e + p->fi));
	p->Eb_cos1	= _IQcosPU((p->wt_e + p->fi - _IQ(1.0/3.0)));
	p->Ec_cos1	= _IQcosPU((p->wt_e + p->fi + _IQ(1.0/3.0)));

	p->Il_d	= _IQmpy(p->Il_Alfa,p->Ea_sin1) - _IQmpy(p->Il_Beta,p->Ea_cos1);
	p->Il_q	= _IQmpy(p->Il_Alfa,p->Ea_cos1) + _IQmpy(p->Il_Beta,p->Ea_sin1);
}
