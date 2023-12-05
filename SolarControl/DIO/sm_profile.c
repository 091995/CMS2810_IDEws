
#ifndef MODEL

#include "dio_func.h"
#include "main.h"


#endif


SM_ISLA_BATT_DIESEL sm_isla_batt_diesel 								= SM_ISLA_BATT_DIESEL_DEFAULTS;
SM_GRID_EVNG_BATT_DIESEL sm_grid_evng_batt_diesel 						= SM_GRID_EVNG_BATT_DIESEL_DEFAULTS;
SM_GRID_NIGHT_BATT_CHARGE sm_grid_night_batt_charge 					= SM_GRID_NIGHT_BATT_CHARGE_DEFAULTS;
SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT sm_grid_day_solar_mppt_charge_batt 	= SM_GRID_DAY_SOLAR_MPPT_CHARGE_BATT_DEFAULTS;
SM_MANUAL sm_manual = SM_MANUAL_DEFAULTS;

SM_DAILY_CICLE sm_daily_cicle = SM_DAILY_CICLE_DEFAULTS;

//void SETP(int32*p_val,int32 val) {
//	*p_val = val;
//}
//
//int GETP(int32*p_val)		{
//	return (int32) *p_val;
//}


void SC_PROFILE_Init(SC_PROFILE*p)
{
	p->profile=SM_PROFILE_MANUAL;
	p->profile_prev=-1;

	sm_daily_cicle.init(&sm_daily_cicle);
	//so looong name ... мне это не очень нравиться но когда работаешь из модуля обращение только set.dcdc_P_charge
	//sm_grid_day_solar_mppt_charge_batt.set.dcdc_P_charge

	// эти разрешения нужны только для работы по суточной циклограмме из модуля DAILY_CICLE
	sm_isla_batt_diesel.ena=1 ;
	sm_grid_evng_batt_diesel.ena=1;
	sm_grid_night_batt_charge.ena=1;
	sm_grid_day_solar_mppt_charge_batt.ena=1;
	sm_manual.ena=1;


	sm_grid_day_solar_mppt_charge_batt.set.inv_Udc_min = _IQ(450/700.0);
	sm_grid_day_solar_mppt_charge_batt.set.dcdc_P_charge=((25)<<8);
	sm_grid_day_solar_mppt_charge_batt.set.dcdc_I_charge=((5)<<4);

	sm_grid_evng_batt_diesel.autostart=0;
	sm_grid_evng_batt_diesel.start_hour=19;
	sm_grid_evng_batt_diesel.start_minute=46;
	sm_grid_evng_batt_diesel.fade_hour=21;
	sm_grid_evng_batt_diesel.fade_minute=1;
	sm_grid_evng_batt_diesel.set.inv_Udc_min = _IQ(450/700.0);
	sm_grid_evng_batt_diesel.set.dcdc_P_discharge = ((-103)<<8);
	sm_grid_evng_batt_diesel.set.dcdc_I_discharge = ((-550)<<4);
	sm_grid_evng_batt_diesel.set.diesel_P_ref = _IQ16(88);
	sm_grid_evng_batt_diesel.warming_time = 5;
	sm_grid_evng_batt_diesel.without_batt = 0;
	sm_grid_evng_batt_diesel.without_diesel = 0;
	sm_grid_evng_batt_diesel.batt_idle_time_min = 60;


	sm_grid_night_batt_charge.set.inv_Udc_min = _IQ(450/700.0);
	sm_grid_night_batt_charge.set.dcdc_P_charge =((25)<<8);
	sm_grid_night_batt_charge.set.dcdc_I_charge =((5)<<4);
	sm_grid_night_batt_charge.start_hour=22;
	sm_grid_night_batt_charge.start_minute=0;
	sm_grid_night_batt_charge.autostart=0;
	sm_grid_night_batt_charge.night_to_day_hour=6;
	sm_grid_night_batt_charge.night_to_day_minute=30;
	sm_grid_night_batt_charge.jump_time_min = 20;

	sm_isla_batt_diesel.Udc2_high = _IQ4(230);
	sm_isla_batt_diesel.Udc2_low = _IQ4(190);
	sm_isla_batt_diesel.fade_hour = 19;
	sm_isla_batt_diesel.fade_minute = 0;
	sm_isla_batt_diesel.start_hour = 15;
	sm_isla_batt_diesel.start_minute = 0;



//	sc_profile.p.inv_pid_Udc_kp = &pid_Udc.Kp_reg3;
//	sc_profile.p.inv_pid_Udc_ki = &pid_Udc.Ki_reg3;
//	sc_profile.p.inv_cmd_pulses_on =&cmd_logic.cmd.cmd_pulses_on;
//	sc_profile.p.inv_cmd_pulses_off =&cmd_logic.cmd.cmd_pulses_off;
//	sc_profile.p.inv_cmd_pow_on =&cmd_logic.cmd.cmd_pow_on;
//	sc_profile.p.inv_cmd_pow_off =&cmd_logic.cmd.cmd_pow_off;
//	sc_profile.p.inv_profile = &inv.params.profile;
//	sc_profile.p.inv_mppt_ena = &mppt.ena;
//
//
//	sc_profile.p.dcdc_P_ref = &cmd_logic.remote_refs.P_dcdc_ref;
//	sc_profile.p.dcdc_ena = &dcdc.ena;
//	sc_profile.p.dcdc_batt_charge = &dcdc.E_charge_persent;
//	sc_profile.p.dcdc_operating =  &dcdc.operating;
//	sc_profile.p.diesel_start = &diesel.ena;
//
//	sm_manual.p=&sc_profile.p;
//	sm_grid_day_solar_mppt_charge_batt.p=&sc_profile.p;
//	sm_grid_evng_batt_diesel.p=&sc_profile.p;
//	sm_grid_night_batt_charge.p=&sc_profile.p;
//	sm_isla_batt_diesel.p=&sc_profile.p;
}



int _set_profile_prev=-1;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SC_PROFILE_ms_Calc(SC_PROFILE*p)
{

/*Здесь большой вопрос как менять профиль. Мы хотим чтобы с экрана можно было выбрать профиль и система
 * автоматически перешла в него. но всегда ли можно просто сменить профиль? Что может быть если текущее
 * состояние оборудования не совместимо с новым профилем?
 * Возможен подход при котором старый профиль просто бросается,  а новый профиль сам определяет
 * что из этого состава оборудовнаия ему нужно и переводит в нужное состояние (например отключает дизель и добавляет АКБ)
 * В реализовнном ниже автомате нет переходного состояние - это по сути не автомат а просто селектор профилей
 * Каждый новый профиль начинает свое выполнение с init (чтобы обнулить state) и далее ms_calc.
 * Первой задачей профиля явлется определение состава оборудования и дальше выполнять ДА с приведением
 * оборудования к требуемым по профилю состояниям
 */


/* сделать схему смены профиля
 * Профиль можно выбрать с экрана панели и через unicon
 * 	- в панели это кнопки которые пишут в адрес номер профиля - 1,2,3..
 * 	- в unicon это переменная sc_profile.in.cmd_remote_set_profile
 *
 *
 * */


//if (p->ena==0) p->state=SM_PROFILE_INIT;

sm_daily_cicle.ms_calc(&sm_daily_cicle);

p->profile1_state=sm_grid_day_solar_mppt_charge_batt.state;
p->profile2_state=sm_grid_evng_batt_diesel.state;
p->profile3_state=sm_grid_night_batt_charge.state;
p->profile4_state=sm_isla_batt_diesel.state;



//команда на смену профиля по умолчанию 0 и изменилась относительно предыдущего значения
if ((p->in.cmd_local_set_profile!=0)&&(p->in.cmd_local_set_profile!=p->in.cmd_local_set_profile_prev))
		p->profile = p->in.cmd_local_set_profile;
p->in.cmd_local_set_profile_prev=p->in.cmd_local_set_profile;

if ((p->in.cmd_remote_set_profile!=0)&&(p->in.cmd_remote_set_profile!=p->in.cmd_remote_set_profile_prev))
		p->profile = p->in.cmd_remote_set_profile;
p->in.cmd_remote_set_profile_prev=p->in.cmd_remote_set_profile;



///это не автомат а просто селектор
if (p->profile!=p->profile_prev) p->E=1; else p->E=0;
p->profile_prev=p->profile;

switch (p->profile) {
case SM_PROFILE_MANUAL:
	if (p->E==1) sm_manual.init(&sm_manual);
	sm_manual.ms_calc(&sm_manual);

	p->status = sm_manual.state+(SM_PROFILE_MANUAL*10);

	///if (sm_manual.state>=SM_PROFILE_LOGIC_FAILED) p->profile =  SM_PROFILE_SELECT_PROFILE;
	break;

case SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT:
	if (p->E==1){
		p->counter=0;
		sm_grid_day_solar_mppt_charge_batt.init(&sm_grid_day_solar_mppt_charge_batt);
	}
	sm_grid_day_solar_mppt_charge_batt.ms_calc(&sm_grid_day_solar_mppt_charge_batt);
	p->status = sm_grid_day_solar_mppt_charge_batt.state+(SM_PROFILE_GRID_DAY_SOLAR_MMPT_CHARGE_BATT*10);

	break;

case SM_PROFILE_GRID_EVNG_BATT_DIESEL:

	if (p->E==1) {
		sm_grid_evng_batt_diesel.init(&sm_grid_evng_batt_diesel);
	}

	sm_grid_evng_batt_diesel.ms_calc(&sm_grid_evng_batt_diesel);
	p->status = sm_grid_evng_batt_diesel.state+(SM_PROFILE_GRID_EVNG_BATT_DIESEL*10);
	/// You may use check for states and change or reset profile
	// if (sm_grid_evng_batt_diesel.state) p->profile =  SM_PROFILE_SELECT_PROFILE;

	break;


case SM_PROFILE_GRID_NIGHT_BATT_CHARGE:

	if (p->E==1) {
		sm_grid_night_batt_charge.init(&sm_grid_night_batt_charge);
	}

	sm_grid_night_batt_charge.ms_calc(&sm_grid_night_batt_charge);
	p->status = sm_grid_night_batt_charge.state+(SM_PROFILE_GRID_NIGHT_BATT_CHARGE*10);
	//if (sm_grid_night_batt_diesel.state>=SM_PROFILE_LOGIC_FAILED) p->profile =  SM_PROFILE_SELECT_PROFILE;

	break;



case SM_PROFILE_ISLA_BATT_DIESEL:
	if (p->E==1) sm_isla_batt_diesel.init(&sm_isla_batt_diesel);
	sm_isla_batt_diesel.ms_calc(&sm_isla_batt_diesel);
	p->status = sm_isla_batt_diesel.state+(SM_PROFILE_ISLA_BATT_DIESEL*10);
	//if (sm_isla_batt_diesel.state>=SM_PROFILE_LOGIC_FAILED) p->state =  SM_PROFILE_SELECT_PROFILE;

	break;


default:break;
}    //end switch (p->state)



}
