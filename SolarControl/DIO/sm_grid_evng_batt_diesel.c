#ifndef MODEL
#include "dio_func.h"
#include "dcs_func.h"

#include "main.h"
#include <DIO/sm_grid_evng_batt_diesel.h>
#endif


//give descriptions according real state
#define SM_LOGIC_INIT				99

#define SM_CHECK_OPERATION 			0
#define SM_CHECK_OPERATION_WARMING 	1
#define SM_GO_LOAD_BATT				2
#define SM_GO_LOAD_DIESEL			3
#define SM_CHECK_DIESEL				4
#define SM_CHECK_BATT				5
#define SM_GO_DISABLE				6
#define SM_GO_DISABLE_DIESEL		7
#define SM_GO_LOAD_DIESEL_WARMING	8
#define SM_CHECK_OPERATION_BATT 	9
#define SM_CHECK_OPERATION_DIESEL 	10
#define SM_CYCLE_END 				11
#define SM_BATT_IDLE				12



//#define SM_LOAD_BATT				3
//#define SM_GO_LOAD_BATT_DIESEL		4
//#define SM_LOAD_BATT_DIESEL			5
//#define SM_LOAD_DIESEL				7
//#define SM_LOGIC_FAILED				100 this is predefined in sc_profile.h and common for all


void SM_GRID_BATT_DIESEL_Init(SM_GRID_EVNG_BATT_DIESEL*p)
{
	p->state=SM_LOGIC_INIT;
	p->state_prev=-1;
	inv.params.Udc_day=_IQ(500.0/700);
	inv.params.Udc_level_go_on=_IQ(500.0/700);
	dcdc.Idc2_ref = ((-10)<<4);
	cmd_logic.status.profile = 1;
	dcdc.discharge_type = 1;
	cmd_logic.remote_refs.P_dcdc_ref = ((-20)<<8);

}



//идея этого режим включить и параллельно рабоать АКБ и Дизеля, при этом мощность инвретора это сумма уставок дизеля и АКБ
// если что-то отключается сигнал operation снимется и мощность тоже снимается.
// На протяжении всего режима никакого регулятора напряжения Udc нет. Оно опуститься до уровня выпрямленного напряжения дизеля
// Последовательнотьс работы такая
// в состоянии SM_CHECK_OPERATION смотрим что все работает. Если дизель или АКБ не работают то включаем их
//-- включаем АКБ и ставим 100кВ
//-- включаем дизель, возможно жждем прогрев и ставим 100кВ
//-- работаем по времени не более 1 часа и выключаем все переходя в режим SM_LOAD_CYCLE_OVER
//-- TODO 224 следим что есть топливо и заряд АКБ. Если чего-то не хватает отключаем или ограничиваем мощнсть
// -

// Изанчально модуль задумывался иначе - со следующим приритетом
//-- сначал панели, пока напряженяи хватает
//-- потом АКБ, по мощности она дает до 100кВт
//-- и если не хватает АКБ то включаем дизель
// Макс - возможно захочешь переименовть этот модуль. делай. но придется словарь тоже править

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SM_GRID_BATT_DIESEL_ms_Calc(SM_GRID_EVNG_BATT_DIESEL*p)
{
volatile  int _P_mult;
volatile  int _P_dcdc_ref;

	// мощность инвертора идет в масштабе inv_params.P_nom а мощность dcdc идет в формате 8.8 с масштабом 1.
	//приводим мощность dcdc из абсолютных значений в относительные инвертра)

	//_P_dcdc_ref = -_IQmpy(cmd_logic.refs.P_dcdc_ref<<16,inv_params._1_P_nom); //знак минус нужен
	_P_mult = dcdc.U2_meas_V_I12Q4*dcdc.Idc2_ref;
	_P_dcdc_ref = -_IQmpy(_IQmpy(_P_mult,_IQ(0.001))<<16,inv_params._1_P_nom);

	//todo 222 diesel.P_ref возможно поменять на сигнал из cmd_logic чтобы можо было брать из modbus
	//just for debug //diesel.ON=1;dcdc.operating=1;
	cmd_logic.refs.P_ref=diesel.P_ref*diesel.ON+_P_dcdc_ref*dcdc.operating;
	//todo 224 т.к. форматы уставки мощности DCDC и инертора и дизеля рахные нужно привожить в все к одному формату инвертора


if(inv.in.cmd_protect_pow_off==1 || apl_protect.AR1.state == AR_STATE_FAIL)
	p->state = SM_PROFILE_LOGIC_FAILED;

if (p->state!=p->state_prev) p->E=1; else p->E=0;
p->state_prev=p->state;

switch (p->state) {
case SM_LOGIC_INIT:
	if(p->E==1) {
		dcs_ctrl.ctrl_mode_synced_P_gen=1;
		p->dcdc_attempts=0;
		p->diesel_attempts=0;
	}
	p->state = SM_CHECK_OPERATION_WARMING;

	if(p->without_diesel==1) p->state=SM_CHECK_OPERATION_BATT;

	if(p->without_batt==1&&p->without_diesel==1) p->state=SM_GO_DISABLE;

	break;

case SM_CHECK_OPERATION_WARMING:
	if(p->E==1) {
		p->counter=0;
		p->counter_diesel=0;
	}
	p->counter++;

	if(diesel.ON==1)
	{
		if (inv.state!=SM_DIO_LOGIC_INV_OPERATION) inv.in.cmd_pow_on=1;
		else
		{
			p->counter_diesel++;
			if(p->counter_diesel>(p->warming_time*1000*60))
			{
				p->state=SM_CHECK_OPERATION_DIESEL;
			}
		}

	}

	if(diesel.ON==0&&p->diesel_attempts>=5)
		p->state=SM_CHECK_OPERATION_BATT;

	if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
		p->counter=1000;
		//TODO 225 здесь нужен вложенный автомат на каждое устройство.
		//В этой реализцаии я вынужден поставить break иначе выполняется только последняя ветка
	if ((diesel.ON==0)&&(p->diesel_attempts<5)&&(p->without_diesel==0)) {p->state = SM_GO_LOAD_DIESEL_WARMING;break;}
		//TODO 223 добавить проверку что батарейка разрядилась
	}
	if(p->without_batt==1) dcdc.ena=0;

	if(p->without_diesel==1) {diesel.cmd_in_off = 1; p->state=SM_CHECK_OPERATION_BATT;}

	break;

case SM_CHECK_OPERATION_DIESEL:
	if(p->E==1) {
		p->counter=0;
		p->counter_diesel=0;
	}

	p->counter++;


	if(diesel.ON==1)
	{
		if (inv.state!=SM_DIO_LOGIC_INV_OPERATION) inv.in.cmd_pow_on=1;
		else
		{
			p->counter_diesel++;

			if(p->counter_diesel>2000)
			{
				p->counter_diesel=0;
				diesel.P_ref+=_IQ16(1);
			}
		}

	}

	if(diesel.P_ref>p->set.diesel_P_ref)
	{
		diesel.P_ref=p->set.diesel_P_ref;
		p->state=SM_CHECK_OPERATION_BATT;
	}


	if(diesel.ON==0&&p->diesel_attempts>=5)
		p->state=SM_CHECK_OPERATION_BATT;

	if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
		p->counter=1000;
		//TODO 225 здесь нужен вложенный автомат на каждое устройство.
		//В этой реализцаии я вынужден поставить break иначе выполняется только последняя ветка
		if ((diesel.ON==0)&&(p->diesel_attempts<5)&&(p->without_diesel==0)) p->state = SM_GO_LOAD_DIESEL;
		//TODO 223 добавить проверку что батарейка разрядилась
	}
	if(p->without_batt==1) dcdc.ena=0;

	if(p->without_diesel==1) {diesel.cmd_in_off = 1; p->state=SM_CHECK_OPERATION_BATT;}
	break;

case SM_CHECK_OPERATION_BATT:
	if(p->E==1) {
		p->counter=0;
		p->counter_batt=0;
	}

	p->counter++;


	if(dcdc.operating==1)
	{
		if (inv.state!=SM_DIO_LOGIC_INV_OPERATION) inv.in.cmd_pow_on=1;
		else
		{
			p->counter_batt++;
			if(p->counter_batt>2000)
			{
				p->counter_batt=0;
				dcdc.Idc2_ref+=_IQ4(-5);
			}
		}

	}


	if(dcdc.Idc2_ref<p->set.dcdc_I_discharge)
	{
		dcdc.Idc2_ref=p->set.dcdc_I_discharge;
		p->state=SM_CHECK_OPERATION;
	}


	if(dcdc.operating==0&&p->dcdc_attempts>=3)
		p->state=SM_CHECK_OPERATION;

	if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
		p->counter=1000;
		//TODO 225 здесь нужен вложенный автомат на каждое устройство.
		//В этой реализцаии я вынужден поставить break иначе выполняется только последняя ветка
		if ((dcdc.operating==0)&&(p->dcdc_attempts<3)&&(p->without_batt==0)) p->state = SM_GO_LOAD_BATT;
		//TODO 223 добавить проверку что батарейка разрядилась
	}

	if(p->without_diesel==1) diesel.cmd_in_off = 1;

	if(p->without_batt==1) {dcdc.ena = 0; p->state=SM_CHECK_OPERATION;}
	break;



case SM_CHECK_OPERATION:
	if(p->E==1) {
		p->counter=0;
		p->counter_batt=0;
	}

	p->counter++;

	if(inv.state==SM_DIO_LOGIC_INV_OPERATION)
	{
	if(RTCclock.hour==sm_grid_evng_batt_diesel.fade_hour&&RTCclock.minute==sm_grid_evng_batt_diesel.fade_minute&&RTCclock.second<3)
		p->state=SM_GO_DISABLE;

	}
	else
		p->state=SM_PROFILE_LOGIC_FAILED;


	if(dcdc.U2_meas_V_I12Q4<_IQmpy(dcdc.U2_min,_IQ(0.87))&&dcdc.U2_meas_V_I12Q4>=_IQmpy(dcdc.U2_min,_IQ(0.86)))
	{
		p->counter_batt++;
		if(p->counter_batt>2000)
		{
			p->counter_batt=0;
			dcdc.Idc2_ref+=_IQ4(5);
			if (dcdc.Idc2_ref>_IQmpy(_IQ(0.97),p->set.dcdc_I_discharge))
				dcdc.Idc2_ref=_IQmpy(_IQ(0.97),p->set.dcdc_I_discharge);

		}
	}

	if(dcdc.U2_meas_V_I12Q4<_IQmpy(dcdc.U2_min,_IQ(0.86))&&dcdc.U2_meas_V_I12Q4>=_IQmpy(dcdc.U2_min,_IQ(0.84)))
	{
		p->counter_batt++;
		if(p->counter_batt>2000)
		{
			p->counter_batt=0;
			dcdc.Idc2_ref+=_IQ4(5);
			if (dcdc.Idc2_ref>_IQmpy(_IQ(0.95),p->set.dcdc_I_discharge))
				dcdc.Idc2_ref=_IQmpy(_IQ(0.95),p->set.dcdc_I_discharge);

		}
	}

	if(dcdc.U2_meas_V_I12Q4<_IQmpy(dcdc.U2_min,_IQ(0.84))&&dcdc.U2_meas_V_I12Q4>=_IQmpy(dcdc.U2_min,_IQ(0.82)))
	{
		p->counter_batt++;
		if(p->counter_batt>2000)
		{
			p->counter_batt=0;
			dcdc.Idc2_ref+=_IQ4(5);
			if (dcdc.Idc2_ref>_IQmpy(_IQ(0.93),p->set.dcdc_I_discharge))
				dcdc.Idc2_ref=_IQmpy(_IQ(0.93),p->set.dcdc_I_discharge);

		}
	}

	if(dcdc.U2_meas_V_I12Q4<_IQmpy(dcdc.U2_min,_IQ(0.82)))
	{
		p->counter_batt++;
		if(p->counter_batt>2000)
		{
			p->counter_batt=0;
			dcdc.Idc2_ref+=_IQ4(5);
			if (dcdc.Idc2_ref>_IQmpy(_IQ(0.9),p->set.dcdc_I_discharge))
				dcdc.Idc2_ref=_IQmpy(_IQ(0.9),p->set.dcdc_I_discharge);

		}
	}


	if (p->counter>1000) { // ждем 1 секунду чтобы предыдущие процессы прошли
		p->counter=1000;
		//TODO 225 здесь нужен вложенный автомат на каждое устройство.
		//В этой реализцаии я вынужден поставить break иначе выполняется только последняя ветка
		if ((dcdc.operating==0)&&(p->dcdc_attempts<3)&&(p->without_batt==0)) {p->state = SM_GO_LOAD_BATT; break;}
		if ((diesel.ON==0)&&(p->diesel_attempts<3)&&(p->without_diesel==0)) {p->state = SM_GO_LOAD_DIESEL;break;}
		//TODO 223 добавить проверку что батарейка разрядилась
	}

	if(p->without_diesel==1) diesel.cmd_in_off = 1;
	if(p->without_batt==1) dcdc.ena = 0;

	if(p->without_batt==1&&p->without_diesel==1) p->state=SM_GO_DISABLE;

	break;

case SM_GO_DISABLE:
	if(p->E==1) {
		p->counter=0;
		p->counter_batt=0;
		p->counter_diesel=0;
	}

	p->counter++;


		p->counter_batt++;
		if(p->counter_batt>2000)
		{
			p->counter_batt=0;
			dcdc.Idc2_ref+=_IQ4(5);
			if (dcdc.Idc2_ref>0) dcdc.Idc2_ref=0;
			diesel.P_ref-=_IQ16(1);
			if (diesel.P_ref<0) diesel.P_ref=0;
		}


	if((dcdc.Idc2_ref==0||dcdc.operating==0)&&(diesel.P_ref==0||diesel.ON==0))
		p->state=SM_CYCLE_END;



	break;


case SM_CYCLE_END:
	if(p->E==1) {
		p->counter=0;
		p->counter_diesel=0;
		p->counter_batt=0;
		dcdc.ena=0;
		diesel.cmd_in_off=1;
	}
	p->state = SM_BATT_IDLE;

break;

case SM_PROFILE_LOGIC_FAILED:
	if(p->E==1) {
			p->counter=0;
			p->counter_diesel=0;
			p->counter_batt=0;
			diesel.cmd_in_off = 1;
			dcdc.ena = 0;
		}
	p->state = SM_BATT_IDLE;
break;

case SM_BATT_IDLE:
	if(p->E==1) {
			p->counter=0;
			p->counter_diesel=0;
			p->counter_batt=0;
		}
	p->counter++;
	if(p->counter>(1000*60*p->batt_idle_time_min))
		sc_profile.in.cmd_remote_set_profile = SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT;

break;

case SM_GO_LOAD_BATT:
	if(p->E==1) {
			p->counter=0;
			dcdc.Idc2_ref = ((-10)<<4);
			dcdc.ena=1;
		}

		//check after 5 seconds DCDC is working. If not go start diesel
		p->counter++;

		if (p->counter>10000){
			if (dcdc.operating==1) {
				p->dcdc_attempts=0;
				p->state = SM_CHECK_OPERATION_BATT;
			}
			else
			{
				p->dcdc_attempts++;
				p->state= SM_CHECK_OPERATION_BATT;
			}

		}

		break;



case SM_CHECK_BATT:
	if(p->E==1) {
			p->counter=0;
		}

		break;

case SM_GO_LOAD_DIESEL:
	if(p->E==1) {
			p->counter=0;
			diesel.cmd_in_on=1;
			diesel.P_ref=_IQ16(5);

		}
	p->counter++;

	if (p->counter>10000)//check diesel is runing after 7 seconds
	{
		if (diesel.ON==1) {
			p->diesel_attempts=0;
			p->state = SM_CHECK_OPERATION_DIESEL;
		}
		else
		{
			p->diesel_attempts++;
			p->state = SM_CHECK_OPERATION_DIESEL;
		}

	}

break;

case SM_GO_LOAD_DIESEL_WARMING:
	if(p->E==1) {
			p->counter=0;
			diesel.cmd_in_on=1;
			diesel.P_ref=_IQ16(5);

		}
	p->counter++;

	if (p->counter>10000)//check diesel is runing after 7 seconds
	{
		if (diesel.ON==1) {
			p->diesel_attempts=0;
			p->state = SM_CHECK_OPERATION_WARMING;
		}
		else
		{
			p->diesel_attempts++;
			p->state = SM_CHECK_OPERATION_WARMING;
		}

	}

break;



case SM_CHECK_DIESEL:
	if(p->E==1) {
			p->counter=0;
		}

break;



default:
	break;
}

p->ena_prev=p->ena;




}


