


#ifndef MODEL
#include "DSP.h"
#include "V_adc.h"
#include "main.h"
#endif

#include "dcs_base.h"

#define ENCODE_ADC_FILTER(ch_name) \
				adc.s##ch_name.offset_32bit = \
				(((adc.regs.ch_name##_reg16<<12)-adc.s##ch_name.offset_32bit)>>16) +adc.s##ch_name.offset_32bit;\
				adc.s##ch_name.offset=adc.s##ch_name.offset_32bit>>12;\



void AdcDrv_init(TAdcDrv *p) {

//p->fUdc.T=_IQ(Td/0.005); //фильтр 5ms  T=Ts/Tfiltra где - Tfiltra
//p->fIdc.T=_IQ(Td/0.005); //фильтр 5ms  T=Ts/Tfiltra где - Tfiltra

p->fP_diesel.T=_IQ(Td/0.010); //фильтр 5ms  T=Ts/Tfiltra где - Tfiltra
p->fI_diesel.T=_IQ(Td/0.010); //фильтр 5ms  T=Ts/Tfiltra где - Tfiltra


p->fIalpha_tr_dc.T=_IQ(Td/0.5);
p->fIbeta_tr_dc.T=_IQ(Td/0.5);


adc.sUbc_tr._100to1V_gain=_IQ16(160);//was april 2022 _IQ16(160);
adc.sUbc_tr._1Vto16bit_gain=_IQ24(6.6/0x7fff);

adc.sUbc_inv._100to1V_gain=_IQ16(160);//was april 2022 _IQ16(162);
adc.sUbc_inv._1Vto16bit_gain=_IQ24(6.6/0x7fff);


adc.sUbc_inv.offset=0;
adc.sUac_inv.offset=0;
adc.sUnc_inv.offset=0;
//
//
////!HAL800S - 4V when 800A
////!

#ifdef LAB_MODE_GLOBAL_DEFINE

adc.sIa_tr._100to1V_gain=_IQ16(4.54*10);
adc.sIb_tr._100to1V_gain=_IQ16(4.54*10);
adc.sIc_tr._100to1V_gain=_IQ16(4.54*10);
adc.sIa_tr._1Vto16bit_gain=_IQ24(10.0/0x7fff);
adc.sIb_tr._1Vto16bit_gain=_IQ24(10.0/0x7fff);
adc.sIc_tr._1Vto16bit_gain=_IQ24(10.0/0x7fff);

adc.sI_diesel._100to1V_gain=_IQ16(200); //TODO check this gain according lab model
adc.sI_diesel._1Vto16bit_gain=_IQ24(10.0/0x7fff);

adc.sIa_inv._100to1V_gain=_IQ16(4.54*10);
adc.sIb_inv._100to1V_gain=_IQ16(4.54*10);
adc.sIc_inv._100to1V_gain=_IQ16(4.54*10);

adc.sIa_inv._1Vto16bit_gain=_IQ24(-11.73/0x7fff); // inverting b's of invertng OpAmp mode
adc.sIb_inv._1Vto16bit_gain=_IQ24(-11.73/0x7fff); // inverting b's of invertng OpAmp mode
adc.sIc_inv._1Vto16bit_gain=_IQ24(-11.73/0x7fff); // inverting b's of invertng OpAmp mode


adc.sIdc.offset=1270; //near 0 viltage it is wrong, b's of Opa scheme used, but for 10V inputs it shows 10V measurement with actacom meas
				   // and the error for 1V measurement is 1.2V output due to Opa nonlinearity (
adc.sIdc._100to1V_gain=_IQ16(125); //HTA500-S
adc.sIdc._1Vto16bit_gain=_IQ24(5.75/0x7fff);

adc.sUdc._100to1V_gain=_IQ16(225/8*10); //2.2M/(82.5+6.8)= and x10 to work as real
adc.sUdc._1Vto16bit_gain=_IQ24(5.0/0x7fff);

#else
adc.sIa_tr._100to1V_gain=_IQ16(200);
adc.sIb_tr._100to1V_gain=_IQ16(200);
adc.sIc_tr._100to1V_gain=_IQ16(200);
adc.sIa_tr._1Vto16bit_gain=_IQ24(10.0/0x7fff);
adc.sIb_tr._1Vto16bit_gain=_IQ24(10.0/0x7fff);
adc.sIc_tr._1Vto16bit_gain=_IQ24(10.0/0x7fff);

adc.sI_diesel._100to1V_gain=_IQ16(200);
adc.sI_diesel._1Vto16bit_gain=_IQ24(10.0/0x7fff);

adc.sIa_inv._100to1V_gain=_IQ16(200);//was april 2022 _IQ16(204);
adc.sIb_inv._100to1V_gain=_IQ16(200);//_IQ16(189);
adc.sIc_inv._100to1V_gain=_IQ16(200);//_IQ16(190);

adc.sIa_inv._1Vto16bit_gain=_IQ24(-11.73/0x7fff); // inverting b's of invertng OpAmp mode
adc.sIb_inv._1Vto16bit_gain=_IQ24(-11.73/0x7fff); // inverting b's of invertng OpAmp mode
adc.sIc_inv._1Vto16bit_gain=_IQ24(-11.73/0x7fff); // inverting b's of invertng OpAmp mode

adc.sI_diesel.offset = -300; //TODO 230 для работы диземле измеряется ток по каналу sIc_tr
adc.sIc_tr.offset =-300; //TODO 230 нужно либо замениь канал, или помнить что это аппаратная фича

adc.sIdc.offset=1120;//1270; //near 0 viltage it is wrong, b's of Opa scheme used, but for 10V inputs it shows 10V measurement with actacom meas
				   // and the error for 1V measurement is 1.2V output due to Opa nonlinearity (
adc.sIdc._100to1V_gain=_IQ16(125); //HTA500-S
adc.sIdc._1Vto16bit_gain=_IQ24(5.75/0x7fff);

adc.sUdc._100to1V_gain=_IQ16(225); //18x2.2M/(82.5+6.8)=440 and amp config div 2
adc.sUdc._1Vto16bit_gain=_IQ24(5.0/0x7fff);
#endif


}


//!Расчет АЦП с частотой основного расчета всей системы управления (обычно 10кГц).

//! Занимается обработкой измеренных АЦП значений и преобразует в формат IQ24.
//! Токи фаз для повышения точности усредняются за несколько измерений

//! \memberof TAdcDrv
//!
//!



//adc.s##ch_name##.offset=(adc.s##ch_name##.offset_32bit>>12);

void AdcDrv_fast_calc(TAdcDrv *p) {

//	volatile long Uac_tr,Ubc_tr,Unc_tr;
	long	Tmpa,Tmpb,Tmpc;
		//Дл защиты от однофазного КЗ
	long	Uab,Ubc,Uca;


//расчет смещений для переменных величин
	adc.auto_offset_ena=1;
if (adc.auto_offset_ena)
{
	//p->output = _IQmpy(p->T,(p->input-p->output)) + p->output; T=Ts/Tfiltra где - Tfiltra постоянная времени фильтра,
	//Ts 125us/10s=1.25e-6 это примерно 2e-20

	ENCODE_ADC_FILTER(Ubc_inv);
	ENCODE_ADC_FILTER(Uac_inv);
	ENCODE_ADC_FILTER(Unc_inv);

	ENCODE_ADC_FILTER(Ubc_tr);
	ENCODE_ADC_FILTER(Uac_tr);
	ENCODE_ADC_FILTER(Unc_tr);

	ENCODE_ADC_FILTER(Ia_inv);
	ENCODE_ADC_FILTER(Ib_inv);
	ENCODE_ADC_FILTER(Ic_inv);
	ENCODE_ADC_FILTER(Ia_tr);
	ENCODE_ADC_FILTER(Ib_tr);
	//ENCODE_ADC_FILTER(Ic_tr);


}

adc.sUbc_tr.value = _IQ16mpy(adc.sUbc_tr.gain,(int16)(adc.regs.Ubc_tr_reg16-adc.sUbc_tr.offset));
adc.sUac_tr.value = _IQ16mpy(adc.sUac_tr.gain,(int16)(adc.regs.Uac_tr_reg16-adc.sUac_tr.offset));
adc.sUnc_tr.value = _IQ16mpy(adc.sUnc_tr.gain,(int16)(adc.regs.Unc_tr_reg16-adc.sUnc_tr.offset));


adc.sUbc_inv.value = _IQ16mpy(adc.sUbc_inv.gain,(int16)(adc.regs.Ubc_inv_reg16-adc.sUbc_inv.offset));
adc.sUac_inv.value = _IQ16mpy(adc.sUac_inv.gain,(int16)(adc.regs.Uac_inv_reg16-adc.sUac_inv.offset));
adc.sUnc_inv.value = _IQ16mpy(adc.sUnc_inv.gain,(int16)(adc.regs.Unc_inv_reg16-adc.sUnc_inv.offset));


	adc.Ubc_tr = adc.sUbc_tr.value;
	adc.Uca_tr = -adc.sUac_tr.value;
	adc.Uab_tr = -adc.Ubc_tr-adc.Uca_tr;

	adc.Ubc_inv = adc.sUbc_inv.value;
	adc.Uca_inv = -adc.sUac_inv.value;
	adc.Uab_inv = -adc.Ubc_inv-adc.Uca_inv;


adc.sIa_tr.value = _IQ16mpy(adc.sIa_tr.gain,(int16)(adc.regs.Ia_tr_reg16-adc.sIa_tr.offset));
adc.sIb_tr.value = _IQ16mpy(adc.sIb_tr.gain,(int16)(adc.regs.Ib_tr_reg16-adc.sIb_tr.offset));
//adc.sIc_tr.value = _IQ16mpy(adc.sIc_tr.gain,(int16)(adc.regs.Ic_tr_reg16-adc.sIc_tr.offset)); //TODO 15  sensor connected to I_diesel
adc.sI_diesel.value = _IQ16mpy(adc.sIc_tr.gain,(int16)(adc.regs.Ic_tr_reg16-adc.sIc_tr.offset));

adc.Ia_tr=adc.sIa_tr.value;
adc.Ib_tr=adc.sIb_tr.value;
//adc.Ic_tr=adc.sIc_tr.value; //TODO 15  sensor connected to I_diesel
adc.Ic_tr=-adc.Ia_tr-adc.Ib_tr;

adc.I_diesel = adc.sI_diesel.value;


adc.sIa_inv.value = _IQ16mpy(adc.sIa_inv.gain,(adc.regs.Ia_inv_reg16-adc.sIa_inv.offset));
adc.sIb_inv.value = _IQ16mpy(adc.sIb_inv.gain,(adc.regs.Ib_inv_reg16-adc.sIb_inv.offset));
adc.sIc_inv.value = _IQ16mpy(adc.sIc_inv.gain,(adc.regs.Ic_inv_reg16-adc.sIc_inv.offset));
adc.Ia_inv=adc.sIa_inv.value;
adc.Ib_inv=adc.sIb_inv.value;
adc.Ic_inv=adc.sIc_inv.value;

adc.sIdc.value  = _IQ16mpy(adc.sIdc.gain,(adc.regs.Idc_reg16-adc.sIdc.offset));

adc.sUdc.value = _IQ16mpy(adc.sUdc.gain,(adc.regs.Udc_reg16-adc.sUdc.offset));

adc.Idc=adc.sIdc.value;//abs(adc.sIdc.value);//TODO 9

adc.Udc=adc.sUdc.value;

adc.Pdc = _IQmpy(adc.Idc,adc.Udc);

adc.fP_diesel.input =  _IQmpy(adc.I_diesel,adc.Udc);
adc.fP_diesel.calc(&adc.fP_diesel);
adc.P_diesel = adc.fP_diesel.output;


//ToDo make an hour energy meterring



	//Дл защиты от однофазного КЗ
	Uab = adc.Uab_tr;
	Ubc = adc.Ubc_tr;
    Uca = adc.Uca_tr;
//long	UNc = adc.Uc_tr;
//	adc.Ua_tr = Uac-UNc;
//	adc.Ub_tr = Ubc-UNc;
//	adc.Uc_tr = -UNc;

	// ЕСЛИ на Ua приходит Uас, на Ub - Ubc
		//adc.Uca = adc.Ua;
		//adc.Ubc = -adc.Ub;
		//adc.Uab = -adc.Ubc-adc.Uca;
		Tmpc = - Uca + Ubc;
		Tmpc = _IQmpy(Tmpc,_IQ(1.0/3.0));
		Tmpa = Uca + Tmpc;
		Tmpb = - Tmpa - Tmpc;
		adc.Ua_tr	= -Tmpa;
		adc.Ub_tr	= -Tmpb;
		adc.Uc_tr	= -Tmpc;

	Uab = adc.Uab_inv;
	Ubc = adc.Ubc_inv;
    Uca = adc.Uca_inv;
		//long	UNc = adc.Uc_tr;
		//	adc.Ua_tr = Uac-UNc;
		//	adc.Ub_tr = Ubc-UNc;
		//	adc.Uc_tr = -UNc;

			// ЕСЛИ на Ua приходит Uас, на Ub - Ubc
				//adc.Uca = adc.Ua;
				//adc.Ubc = -adc.Ub;
				//adc.Uab = -adc.Ubc-adc.Uca;
				Tmpc = - Uca + Ubc;
				Tmpc = _IQmpy(Tmpc,_IQ(1.0/3.0));
				Tmpa = Uca + Tmpc;
				Tmpb = - Tmpa - Tmpc;
				adc.Ua_inv	= -Tmpa;
				adc.Ub_inv	= -Tmpb;
				adc.Uc_inv	= -Tmpc;



// testing for DC component reducing in AC currents algo in phase currents" like in Mogocha
//				clarke.as = adc.Ia_tr;
//				clarke.bs = adc.Ib_tr;
//				clarke.calc(&clarke);
//				adc.fIalpha_tr_dc.input=clarke.ds;
//				adc.fIbeta_tr_dc.input=clarke.qs;
//				adc.fIalpha_tr_dc.calc(&adc.fIalpha_tr_dc);
//				adc.fIbeta_tr_dc.calc(&adc.fIbeta_tr_dc);

}

//!Медленный расчет.

//!Занимается пересчетом коэффициентов, используемых в скоростной функции расчета,
//!чтобы не занимать процессорное время там. Находит коэффициенты,
//!на которые надо умножить полученное с АЦП значение, чтобы получить
//!относительные единицы с заданной базой.

//! Пример   p->PvalveGainNom=_IQ16mpy(p->Pvalve_gain,_IQ(1.0/100));
//! Pvalve_gain - значение в формате int. задается пользователем в UniCON.
//!Определяет, скольким процентам соответствует полный диапазон АЦП. В простейшем случае
//!равен 100. Т.е. когда на АЦП максимальный сигнал, это соответствует 100%.

//!_IQ(1.0/100) обратное значение для масштабирующего коэффициента. Так как величину процентов
//!естественнее всего перевести в относительные единицы так, что 100% соответствут 1.0,
//!то масштабирующий коэффициент (база) равен 100. Т.е. UniCON, прочитав из системы управления
//! число 1.0 в формате 8.24 должен умножить его на 100, чтобы отобразились проценты.
//! Здесь коэффициент задан явно как 1.0/100, но для ряда случаев базовое значение нужно менять.
//!Так, для токов фаз используется значение _1_I_nom, в формате 8.24, соответствующее единице деленной на
//базовое значение тока, например, 200 А. Так как в зависимости от мощности преобразователя базовый ток может меняться,
//то это значение, в отличие от процентов, сделано настраиваемым. Расчет _1_I_nom идет в другом месте, так как
//занимает много тактов расчета.

//Для беззнакового значения АЦП измеряет число от 0 до 65535. (16 разрядов, где заполнены верхние).
//Для примера с процентами необходимо сделать так, чтобы получилось результирующее значение в формате 8.24,
//где 1.0 это 65535. Таким образом, нужно сдвинуть число 65535 на 24-16=8 разрядов.
//Сдвиг на 8 разрядов - это умножение на число 255. Число 255 - это 1.0 в формате 24.8.

//Таким образом, PvalveGainNom - это коэффициент в формате 24.8. он получается в результате использования функции
//_IQ16mpy, аргумены которой Pvalve_gain (int) и 1.0/100 в формате 8.24. Функция IQ множения
//по сути представляет собой обычное оуможение в 64 разрядах со сдвигом результата вправо на Q разрядов.
//Т.е. _IQ16mpy умножает число в формате IQ24 9второй аргумент) на целочисленный коэффициент (первый аргумент),
//а потом сдвигате результат на 16 разрядов вправо.
//Так, в результате _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); получается целочисленное число 255, являющейся
//1.0 в формате 24.8 из-за сдвига на 16 разрядов вправо.

//Всё вышеприведенное мутево сделано с одной целью - увеличить производитлеьность обработки АЦП.


//#define ENCODE_ADC_FILTER(ch_name) \
//				adc.s##ch_name.offset_32bit = \
//				(((adc.regs.ch_name##_reg16<<12)-adc.s##ch_name.offset_32bit)>>16) +adc.s##ch_name.offset_32bit;\
//				adc.s##ch_name.offset=adc.s##ch_name.offset_32bit>>12;\

#define CALIBRATE_ADC(ch_name) \
if ((adc.s##ch_name.calibration.more!=0)&&(adc.s##ch_name.calibration.more_prev==0)) adc.s##ch_name.calibration.gain++;\
if ((adc.s##ch_name.calibration.less!=0)&&(adc.s##ch_name.calibration.less_prev==0)) adc.s##ch_name.calibration.gain--;\
if (adc.s##ch_name.calibration.gain <90) adc.s##ch_name.calibration.gain=90;\
if (adc.s##ch_name.calibration.gain >110) adc.s##ch_name.calibration.gain=110;\
adc.s##ch_name.calibration.more_prev = adc.s##ch_name.calibration.more;\
adc.s##ch_name.calibration.less_prev = adc.s##ch_name.calibration.less;\

//! \memberof TAdcDrv
void AdcDrv_slow_calc(TAdcDrv *p) {
	static float cal;

	//if (adc.sUbc_tr.calibration.more==1)&&(adc.sUbc_tr.calibration.more_prev==1) adc.sUbc_tr.calibration.gain++;

	CALIBRATE_ADC(Ubc_tr)
	//ограничиваем минимум и максимум калибровочного коэф
//
//	if (adc.sUbc_tr.calibration.gain	<90) 	adc.sUbc_tr.calibration.gain	=90;
//	if (adc.sUbc_inv.calibration.gain	<90) 	adc.sUbc_inv.calibration.gain	=90;
//	if (adc.sIa_tr.calibration.gain		<90) 	adc.sIa_tr.calibration.gain		=90;
//	if (adc.sIb_tr.calibration.gain		<90) 	adc.sIb_tr.calibration.gain		=90;
//	if (adc.sIc_tr.calibration.gain		<90) 	adc.sIc_tr.calibration.gain		=90;
//	if (adc.sIa_inv.calibration.gain	<90)	adc.sIa_inv.calibration.gain	=90;
//	if (adc.sIb_inv.calibration.gain	<90) 	adc.sIb_inv.calibration.gain	=90;
//	if (adc.sIc_inv.calibration.gain	<90) 	adc.sIc_inv.calibration.gain	=90;
//	if (adc.sUdc.calibration.gain		<90) 	adc.sUdc.calibration.gain		=90;
//	if (adc.sIdc.calibration.gain		<90) 	adc.sIdc.calibration.gain		=90;
//	if (adc.sI_diesel.calibration.gain	<90) 	adc.sI_diesel.calibration.gain	=90;
//
//
//	if (adc.sUbc_tr.calibration.gain	>110) 	adc.sUbc_tr.calibration.gain	=110;
//	if (adc.sUbc_inv.calibration.gain	>110) 	adc.sUbc_inv.calibration.gain	=110;
//	if (adc.sIa_tr.calibration.gain		>110) 	adc.sIa_tr.calibration.gain		=110;
//	if (adc.sIb_tr.calibration.gain		>110) 	adc.sIb_tr.calibration.gain		=110;
//	if (adc.sIc_tr.calibration.gain		>110) 	adc.sIc_tr.calibration.gain		=110;
//	if (adc.sIa_inv.calibration.gain	>110)	adc.sIa_inv.calibration.gain	=110;
//	if (adc.sIb_inv.calibration.gain	>110) 	adc.sIb_inv.calibration.gain	=110;
//	if (adc.sIc_inv.calibration.gain	>110) 	adc.sIc_inv.calibration.gain	=110;
//	if (adc.sUdc.calibration.gain		>110) 	adc.sUdc.calibration.gain		=110;
//	if (adc.sIdc.calibration.gain		>110) 	adc.sIdc.calibration.gain		=110;
//	if (adc.sI_diesel.calibration.gain	>110) 	adc.sI_diesel.calibration.gain	=110;


	cal= adc.sUbc_tr.calibration.gain*0.01;
	adc.sUbc_tr.gain = adc.sUbc_tr._1Vto16bit_gain*_IQmpy(adc.sUbc_tr._100to1V_gain*cal, inv_params._1_U_nom);
	adc.sUac_tr.gain = adc.sUbc_tr.gain;
	adc.sUnc_tr.gain = adc.sUbc_tr.gain;

	cal= adc.sUbc_inv.calibration.gain*0.01;
	adc.sUbc_inv.gain = adc.sUbc_inv._1Vto16bit_gain*_IQmpy(adc.sUbc_inv._100to1V_gain*cal, inv_params._1_U_nom);
	adc.sUac_inv.gain = adc.sUbc_inv.gain;
	adc.sUnc_inv.gain = adc.sUbc_inv.gain;


	cal= adc.sIa_tr.calibration.gain*0.01;adc.sIa_tr.gain = adc.sIa_tr._1Vto16bit_gain*_IQmpy(adc.sIa_tr._100to1V_gain*cal, inv_params._1_I_nom);
	cal= adc.sIb_tr.calibration.gain*0.01;adc.sIb_tr.gain = adc.sIa_tr._1Vto16bit_gain*_IQmpy(adc.sIb_tr._100to1V_gain*cal, inv_params._1_I_nom);
	cal= adc.sIc_tr.calibration.gain*0.01; adc.sIc_tr.gain = adc.sIa_tr._1Vto16bit_gain*_IQmpy(adc.sIc_tr._100to1V_gain*cal, inv_params._1_I_nom);

	cal= adc.sIa_inv.calibration.gain*0.01; adc.sIa_inv.gain = adc.sIa_inv._1Vto16bit_gain*_IQmpy(adc.sIa_inv._100to1V_gain*cal, inv_params._1_I_nom);
	cal= adc.sIb_inv.calibration.gain*0.01; adc.sIb_inv.gain = adc.sIa_inv._1Vto16bit_gain*_IQmpy(adc.sIb_inv._100to1V_gain*cal, inv_params._1_I_nom);
	cal= adc.sIc_inv.calibration.gain*0.01; adc.sIc_inv.gain = adc.sIa_inv._1Vto16bit_gain*_IQmpy(adc.sIc_inv._100to1V_gain*cal, inv_params._1_I_nom);


	cal= adc.sUdc.calibration.gain*0.01;adc.sUdc.gain = adc.sUdc._1Vto16bit_gain*_IQmpy(adc.sUdc._100to1V_gain*cal, inv_params._1_Udc_nom);
	cal= adc.sIdc.calibration.gain*0.01;adc.sIdc.gain = adc.sIdc._1Vto16bit_gain*_IQmpy(adc.sIdc._100to1V_gain*cal, inv_params._1_I_nom);
	cal= adc.sI_diesel.calibration.gain*0.01;adc.sI_diesel.gain = adc.sI_diesel._1Vto16bit_gain*_IQmpy(adc.sI_diesel._100to1V_gain*cal, inv_params._1_I_nom);



}


void AdcDrv_ms_calc(TAdcDrv *p) {

}


static int32 Inp[24];
static int32 MOut[24];
static int32 MInt[24][20];

static Uint16  adc_cycle_counter = 0;
static Uint16 buff_pointer =0;
int E_cntr=0;


void AdcDrv_fast_calc_rms (TAdcDrv*p)
{
int32 Ea_cos;
int32 Ea_sin;
int ii;

Ea_cos=pll.Ea_cos;
Ea_sin=pll.Ea_sin;

adc_cycle_counter++;
adc_cycle_counter&=0x7;//do 8 cycles b's 8kHz and we need 20ms period
switch (adc_cycle_counter)
{
	case 0:
	Inp[0]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ia_tr,Ea_cos));
	Inp[1]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ia_tr,Ea_sin));
	Inp[2]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ib_tr,Ea_cos));
	Inp[3]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ib_tr,Ea_sin));
	Inp[4]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ic_tr,Ea_cos));
	Inp[5]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ic_tr,Ea_sin));

	for (ii=0;ii<6;ii++){
		MOut[ii]	= MOut[ii]  + Inp[ii]  - MInt[ii][buff_pointer];
		MInt[ii][buff_pointer]	= Inp[ii];
		}

		adc.rms.Ia_tr	= _IQmpy2(_IQmag(MOut[0],MOut[1]));
		adc.rms.Ib_tr	= _IQmpy2(_IQmag(MOut[2],MOut[3]));
		adc.rms.Ic_tr	= _IQmpy2(_IQmag(MOut[4],MOut[5]));

	break;
	case 1:
	Inp[6]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uab_inv,Ea_cos));
	Inp[7]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uab_inv,Ea_sin));
	Inp[8]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ubc_inv,Ea_cos));
	Inp[9]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ubc_inv,Ea_sin));
	Inp[10]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uca_inv,Ea_cos));
	Inp[11]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uca_inv,Ea_sin));

	for (ii=6;ii<12;ii++){
		MOut[ii]	= MOut[ii]  + Inp[ii]  - MInt[ii][buff_pointer];
		MInt[ii][buff_pointer]	= Inp[ii];
		}
		// Амплитуды линейных напрЯжений
		adc.rms.Uab_inv	= _IQmpy2(_IQmag(MOut[6],MOut[7]));
		adc.rms.Ubc_inv	= _IQmpy2(_IQmag(MOut[8],MOut[9]));
		adc.rms.Uca_inv	= _IQmpy2(_IQmag(MOut[10],MOut[11]));

	break;
	case 2:
	Inp[12]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uab_tr,Ea_cos));
	Inp[13]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uab_tr,Ea_sin));
	Inp[14]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ubc_tr,Ea_cos));
	Inp[15]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ubc_tr,Ea_sin));
	Inp[16]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uca_tr,Ea_cos));
	Inp[17]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Uca_tr,Ea_sin));

	for (ii=12;ii<18;ii++){
		MOut[ii]	= MOut[ii]  + Inp[ii]  - MInt[ii][buff_pointer];
		MInt[ii][buff_pointer]	= Inp[ii];
		}
	// Амплитуды линейных напрЯжений
		adc.rms.Uab_tr	= _IQmpy2(_IQmag(MOut[12],MOut[13]));
		adc.rms.Ubc_tr	= _IQmpy2(_IQmag(MOut[14],MOut[15]));
		adc.rms.Uca_tr	= _IQmpy2(_IQmag(MOut[16],MOut[17]));
	break;

	case 3:
	Inp[18]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ia_inv,Ea_cos));
	Inp[19]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ia_inv,Ea_sin));
	Inp[20]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ib_inv,Ea_cos));
	Inp[21]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ib_inv,Ea_sin));
	Inp[22]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ic_inv,Ea_cos));
	Inp[23]	= _IQmpy(_IQ(0.05/1.41),_IQmpy(adc.Ic_inv,Ea_sin));

	for (ii=18;ii<24;ii++){
		MOut[ii]	= MOut[ii]  + Inp[ii]  - MInt[ii][buff_pointer];
		MInt[ii][buff_pointer]	= Inp[ii];
		}

		adc.rms.Ia_inv	= _IQmpy2(_IQmag(MOut[18],MOut[19]));
		adc.rms.Ib_inv	= _IQmpy2(_IQmag(MOut[20],MOut[21]));
		adc.rms.Ic_inv	= _IQmpy2(_IQmag(MOut[22],MOut[23]));
	// mean value for 20
	buff_pointer++;
	if (buff_pointer==20) buff_pointer = 0;
	break;
	default: break;
}




cur_par.Pac	= _IQmpy(adc.Id,pll.Um1) ; //TODO 9 abs(_IQmpy(adc.Id,pll.Um1));
cur_par.Qac	= _IQmpy(adc.Iq,pll.Um1);
cur_par.S = _IQmag(cur_par.Pac,cur_par.Qac);
cur_par.cos_fi=_IQdiv(cur_par.Pac,cur_par.S);
cur_par.Freq=pll.fs;

E_cntr++;
if(E_cntr>8000)
{
	E_cntr=0;
	adc.Edc_day +=_IQmpy(labs(cur_par.Pdc),_IQ(1.0/3600)); //this is in seconds
	adc.Edc_total +=(float)(_IQmpy(labs(cur_par.Pdc),inv_params.Pdc_nom)>>16)*(float)(1.0/3600000);
}

if(RTCclock.hour==0&&RTCclock.minute==0&&RTCclock.second==0)
	adc.Edc_day = 0;

if(adc.Edc_total > 10000000000)	adc.Edc_total = 0;

//adc.statcom1.Q_iner	= _IQmpy(adc.statcom1.Q_iner,adc.K2_out) + _IQmpy(adc.statcom1.Q_pu,adc.K1_out);
//adc.statcom1.Q_pu	= adc.statcom1.Q_iner;
//adc.statcom1.P_iner	= _IQmpy(adc.statcom1.P_iner,adc.K2_out) + _IQmpy(adc.statcom1.P_pu,adc.K1_out);
//adc.statcom1.P_pu	= adc.statcom1.P_iner;


	// Амплитуды линейных напрЯжений

//	fi_a	= -_IQatan2PU(adc.Out[6],adc.Out[7])	+ _IQatan2PU(adc.Out[0],adc.Out[1]);
//	Am_a	= _IQmpy(_IQmpy2(_IQmag(adc.Out[0],adc.Out[1])),_IQmpy2(_IQmag(adc.Out[6],adc.Out[7])));
//	fi_b	= -_IQatan2PU(adc.Out[8],adc.Out[9])	+ _IQatan2PU(adc.Out[2],adc.Out[3]);
//	Am_b	= _IQmpy(_IQmpy2(_IQmag(adc.Out[2],adc.Out[3])),_IQmpy2(_IQmag(adc.Out[8],adc.Out[9])));
//	fi_c	= -_IQatan2PU(adc.Out[10],adc.Out[11])+ _IQatan2PU(adc.Out[4],adc.Out[5]);
//	Am_c	= _IQmpy(_IQmpy2(_IQmag(adc.Out[4],adc.Out[5])),_IQmpy2(_IQmag(adc.Out[10],adc.Out[11])));


}



