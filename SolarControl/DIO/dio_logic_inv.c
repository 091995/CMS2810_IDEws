#ifndef MODEL
#include "dio_func.h"
#include "main.h"
#endif

// TO exchange between modules with some parameters i need this copy from DCS
//please be sure that they are the same as in DCS_ctrl.h file
#define SM_DCS_CTRL_INIT 					0
#define SM_DCS_CTRL_STOP 					1
#define SM_DCS_CTRL_RUN			 			2
#define SM_DCS_CTRL_RUN_DO_SYNC				3
#define SM_DCS_CTRL_RUN_SYNCED_P_GEN		4
#define SM_DCS_CTRL_RUN_GENERATOR			5
#define SM_DCS_CTRL_RUN_TEST				6

void DIO_LOGIC_INV_Init(DIO_LOGIC_INV*p) {

//ToDo proper initialization
	//inv.params.Udc_level_go_on ctrl_time_Udc_hi_level = 5000; // 5sec
	//inv.params.Udc_low_level = _IQ(0.13); //13% от сети КБ зарЯжаетсЯ до 0.866 (амплитуда линейного) по отношению к 2-ум амплитудам фазного
	//inv.params.Udc_hi_level = _IQ(0.75); //0.92 DCHECK

	inv.status=0;
	inv.state =0;
	inv.state_prev=-1;

inv.params.mode=DIO_LOGIC_INV_MODE_AUTO;//DIO_LOGIC_INV_MODE_TEST;
inv.params.profile = DIO_LOGIC_INV_DCS_PROFILE_P_GEN; //TODO 5 select SW revision
//inv.params.profile = DIO_LOGIC_INV_DCS_PROFILE_GENERATOR; //TODO 5 select SW revision

inv.params.test_mode=2;
inv.params.test_param=1000;

inv.params.Udc_level_go_on 		= _IQ(670.0/700);
inv.params.Udc_level_go_on_fail 	= _IQ(450.0/700);  //ToDo from doc by Isaev this 450V
inv.params.time_go_on_ms 			=  10*1000; //1 мин TODO4

inv.params.Udc_min_lim_power = _IQ(450.0/700); //start limit power from this point
inv.params.Udc_max_lim_power = _IQ(750.0/700); //start limit power from this point


inv.params.freq_max_level_go_on	= _IQ(1.05);
inv.params.freq_min_level_go_on	= _IQ(0.95);
inv.params.Urms_level_go_on	= _IQ(0.8);
inv.params.Udc_day			= _IQ(600.0/700);
inv.params.Udc_night		= _IQ(250.0/700);
//
inv.params.go_day_mode_timeout_s = 60;				//время выполнения сетевых условий в режиме WAIT_DC_CONDITION для попытки запуска
inv.params.go_night_mode_timeout_s = 300;

inv.params.P_low_time_s =  3*60; //Базисное время ожидания перед новой попыткой старта, после выключения устройства.
inv.params.P_low_timeshift_s = 3*60;//Временной сдвиг, который после выключения устройства прибавляется к базисному времени ожидания.
inv.params.P_low_attempts_max = 5 ;//Максимальное количество прибавлений временного сдвига.
inv.params.P_night = _IQ(5.0/593.0);


}

void DIO_LOGIC_INV_ms_Calc(DIO_LOGIC_INV*p) {
	int _P_low_timeout_ms;
// reset command from prev calc
	inv.out.cmd_DCS_run = 0;
	inv.out.cmd_DCS_stop = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//if (inv.in.cmd.mode_manual==1) inv.params.dio_logic_statcom_mode=DIO_LOGIC_STATCOM_MODE_MANUAL;
//if (inv.in.cmd.mode_auto==1) inv.params.dio_logic_statcom_mode=DIO_LOGIC_STATCOM_MODE_AUTO;
//if (inv.in.cmd.mode_test==1) inv.params.dio_logic_statcom_mode=DIO_LOGIC_STATCOM_MODE_TEST;

if (inv.params.mode ==  DIO_LOGIC_INV_MODE_TEST ) //TODO actually TEST mode is for DIO_LOGIC and not just for unverter, maybe move it upper?
{
	inv.out.cmd_DCS_run = inv.in.cmd_pulses_on;
	inv.out.cmd_DCS_stop = inv.in.cmd_pulses_off;
	inv.out.cmd_DCS_trip_reset = inv.in.cmd_trip_reset;
	inv.out.cmd_DCS_set_mode = SM_DCS_CTRL_RUN_TEST;

	if (inv.in.DCS_running)
	inv.status = STATUS_DIO_LOGIC_INV_TEST_RUNNING;
	else
	inv.status = STATUS_DIO_LOGIC_INV_TEST_STOP;

	return;
}


//limit counter
if (inv.counter > _IQ(100)) inv.counter=_IQ(100);
//limit sub_counter
if (inv.sub_counter > _IQ(100)) inv.sub_counter=_IQ(100);

	inv.out.cmd_DCS_trip_reset = inv.in.cmd_trip_reset;


	if (inv.state_prev != inv.state) inv.E = 1; else inv.E = 0;
	inv.state_prev = inv.state;

	switch (inv.state) {
	case SM_DIO_LOGIC_INV_INIT: //Инициализация, даем время всем системам завершить расчет.

		if (inv.E == 1) {
			inv.counter = 0;
		}
		inv.out.ready = 0;
		inv.status = STATUS_DIO_LOGIC_INV_INIT;
		inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_NONE; //пока DCS может ничего не делать.

		//все выключатели должны быть выключены, иначе защита
		/*	if (inv.aux_Q1.state==STATE_Q_OFF) inv.prot_word|=P_Q1_ON_WHEN_INIT;
		 if (inv.aux_Q2.state==STATE_Q_OFF) inv.prot_word|=P_Q2_ON_WHEN_INIT;
		 if (inv.aux_Q3.state==STATE_Q_OFF) inv.prot_word|=P_Q3_ON_WHEN_INIT;
		 if (inv.aux_Q4.state==STATE_Q_OFF) inv.prot_word|=P_Q4_ON_WHEN_INIT;
		 */
		inv.counter++;
		if (inv.counter >= 1000) { // можно переходить

			inv.attempts_counter=0;
			inv.state = SM_DIO_LOGIC_INV_INIT_PROC;

		}
		break;
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
	case SM_DIO_LOGIC_INV_INIT_PROC: //Проверяем состояние всех подсистем, формируем предупреждения
		if (inv.E == 1) {
			inv.counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_INIT_PROC;
		}

//Set outputs
		inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_NONE; //пока DCS может ничего не делать.
		inv.out.ready = 0;

//control aux_io TODO 220 - это нигде не применяется. A&D исключил
		//if (aux_Q26.state == STATE_Q_ON)
		//	inv.alarm_word |= ALARM_DIO_LOGIC_INV_Q26_ON_WHEN_INIT; //ToDO
		//if (aux_K7.state == STATE_Q_ON)
		//	inv.alarm_word |= ALARM_DIO_LOGIC_INV_K7_ON_WHEN_INIT;  //ToDO

//wait fan test run done



		inv.counter++;
		if (inv.counter >= 1000) {
			//template for Isaev power after reset sequense
			//if no protection then check aux_Q4 state and turn it on
			if ((inv.in.cmd_protect_pow_off==0)&&(inv.in.cmd_protect_pwm_off==0))
			{
				if (aux_Q4.state == STATE_Q_OFF) aux_Q4.cmd_in = CMD_Q_ON;
				inv.state = SM_DIO_LOGIC_INV_POW_OFF;
			}
			else
				inv.state = SM_DIO_LOGIC_INV_FAULT;
		}

		break;

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
	case SM_DIO_LOGIC_INV_POW_OFF: //ИНВЕРТОР ОТКЛЮЧЕН, ищем пути включения в рамках выбранного профиля
//	8.2.7	Инвертор отключен от сети переменного и постоянного тока - контактор K7 отключен, а выключатель Q4 может быть отключен или включен.
//	8.2.8	Устройство работает в режиме самодиагностики, управление мощностью не выполняется.
//	8.2.9	Возможные смены состояния:
//	Команда «ВКЛ» подает сигнал включения на Q4, и в случае успешного включения переводить автомат  в состояние «Ожидание условий сетевого питания».
//   Если уровень постоянного напряжения поднимается выше предельного значения напряжения на время,
// большее чем время задержки, то устройство переходит в состояние «Ожидание условий сетевого питания».

		if (inv.E == 1) {
			inv.counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_POW_OFF;

		}
		inv.out.ready = 1;

		//if MODE_AUTO, i.e. autostart after power on

		//Only here Profile may be changed!!! TODO5 - logic needs to be improved
		if (cmd_logic.status.profile==5) inv.params.profile=DIO_LOGIC_INV_DCS_PROFILE_GENERATOR;
		else inv.params.profile=DIO_LOGIC_INV_DCS_PROFILE_P_GEN;

		//если нет защиты препятстующей включению инвертора то включаем его
		if ((inv.in.cmd_protect_pow_off==0)&&(inv.in.cmd_protect_pwm_off==0)) {
			//проверяем состояние выключателей постоянного тока, если режим автоматический, то включаем
			//	if (inv.params.mode == DIO_LOGIC_INV_MODE_AUTO) {
			aux_Q4.cmd_in=CMD_Q_ON; //always turn on Q4

			if (inv.in.cmd_pow_on==1)
				inv.state = SM_DIO_LOGIC_INV_SELECT_PROFILE_AND_TRY_TO_RUN;//aux_Q4.cmd_in = CMD_Q_ON;


			inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;


			//if (inv.in.cmd_pulses_on) inv.out.cmd_DCS_run = 1;
			//if (inv.in.cmd_pulses_off) inv.out.cmd_DCS_stop = 1;

		}


		//если включен Q4, т.е. подключены солнечные панели, то сразу переходим в ожидание сетевого напряжения
		//if (aux_Q4.state == STATE_Q_ON) {
			//inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
		//}
//			if (inv.in.DCS_Udc > inv.params.Udc_day)
//			inv.counter++;
//			else
//			inv.counter = 0;
//
//			if (inv.counter > (inv.params.day_mode_timeout_s * 1000))
//				inv.state = SM_DIO_LOGIC_INV_WAIT_AC_CONDITION;



		break;

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
case SM_DIO_LOGIC_INV_SELECT_PROFILE_AND_TRY_TO_RUN: //8.2.10	Состояние «Ожидание условий сетевого питания»("Синхронизация")
		if (inv.E == 1) {
			inv.counter = 0;
			inv.sub_counter = 0;// INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
			inv.sub_state=INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
			inv.status = STATUS_DIO_LOGIC_INV_CHECK_CONDITION;
		}

		inv.out.ready = 1;


	//можно отключить инвертор всегда.
	if (inv.in.cmd_pow_off==1) {
		inv.out.cmd_DCS_stop=1;
		aux_K7.cmd_in=CMD_Q_OFF;
		inv.state=SM_DIO_LOGIC_INV_POW_OFF;
	}


// Работаем по профилю.
			switch (inv.params.profile) {
				case DIO_LOGIC_INV_DCS_PROFILE_P_GEN:

					//проверяем работу всех защит и если есть переходим в fail
					if ((inv.in.cmd_protect_pow_off!=0)||(inv.in.cmd_protect_pwm_off!=0))
						inv.state = SM_DIO_LOGIC_INV_FAULT;

					switch (inv.sub_state) {
					case INV_SUBSTATE_CHECK_DAY_OR_NIGHT:
						//проверяем условия дневного режима
						if ((inv.in.DCS_Udc > inv.params.Udc_level_go_on)
								&& (inv.in.DCS_freq < inv.params.freq_max_level_go_on)
								&& (inv.in.DCS_freq > inv.params.freq_min_level_go_on)
								&& (inv.in.DCS_Urms > inv.params.Urms_level_go_on))
						{
												inv.sub_counter =  inv.params.time_go_on_ms;
												inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;


												inv.sub_state = INV_SUBSTATE_TRY_DAY_SYNC;
												inv.status = STATUS_DIO_LOGIC_SYNC;
												inv.sub_counter=0; //no entry in substate mashine do reset manualy
												//inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;
												//if (inv.params.mode==DIO_LOGIC_INV_MODE_AUTO)
												inv.out.cmd_DCS_run = 1;

							//inv.sub_counter++;
						//else
							//inv.sub_counter = 0;
						//если есть условия для работы , то переходим к синхронизации, ставим режим для DCS и даем импульсы
						//if (inv.sub_counter > inv.params.time_go_on_ms) {
							//inv.sub_counter =  inv.params.time_go_on_ms;
							//inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;

							//if (inv.in.cmd_pow_on==1) {
							//inv.sub_state = INV_SUBSTATE_TRY_DAY_SYNC;
							//inv.sub_counter=0; //no entry in substate mashine do reset manualy
							//inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;
							//if (inv.params.mode==DIO_LOGIC_INV_MODE_AUTO)
							//inv.out.cmd_DCS_run = 1;
						}


						break;

					case INV_SUBSTATE_TRY_DAY_SYNC: //try synced pulses, set DCS_mode SYNC check DC voltage drop
						inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;

						//если нажали стоп импульсов, то выключаем DCS и идем в ожидание день/ночь. Если режим автоматический, то придем сюда опять через несколько тактов
						if (inv.in.cmd_pulses_off) {
							inv.out.cmd_DCS_stop = 1;
							inv.sub_state= INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
						}

						if (inv.in.cmd_pow_off)
						{
							inv.out.cmd_DCS_stop = 1;
							//aux_Q4.cmd_in=CMD_Q_OFF;
							inv.state=SM_DIO_LOGIC_INV_POW_OFF;
						}
						if (inv.in.cmd_pulses_on) inv.out.cmd_DCS_run = 1;
						if (inv.in.cmd_pulses_off) inv.out.cmd_DCS_stop = 1;

						// регулирование в этом состоянии включено, проверяем, что напряжение не упало
						if ((inv.in.DCS_Udc > inv.params.Udc_level_go_on_fail)
								&& (inv.in.DCS_freq < inv.params.freq_max_level_go_on)
								&& (inv.in.DCS_freq > inv.params.freq_min_level_go_on)
								&& (inv.in.DCS_Urms > inv.params.Urms_level_go_on))
						{
							inv.sub_counter++;
						}
						else
						{
							inv.sub_counter=0;
						}

						//if pulses operating normal for time_ms, then go next state
						if (inv.sub_counter == inv.params.time_go_on_ms) {
							aux_K7.cmd_in = CMD_Q_ON;
						}


						if (aux_K7.state == STATE_Q_ON) {
							inv.state = SM_DIO_LOGIC_INV_OPERATION;
						}
						break;


					default:
						break;
					}
		//								case DIO_LOGIC_INV_DCS_PROFILE_NONE: break;
		//								case DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC: break;
		//								case DIO_LOGIC_INV_DCS_PROFILE_U_Q_REG: break;
				break; //case DIO_LOGIC_INV_DCS_PROFILE_P_GEN:

				case DIO_LOGIC_INV_DCS_PROFILE_GENERATOR:



					//TODO5 jsut for 1st day - add extra lgic which check all conditions

					//проверяем работу отключающих защит и если есть переходим в fail
					if (inv.in.cmd_protect_pow_off!=0) // pwm off is not needed to prevents K7 off ||(inv.in.cmd_protect_pwm_off!=0))
						{inv.state = SM_DIO_LOGIC_INV_FAULT;break;}

						if (inv.in.DCS_running==1) inv.status = STATUS_DIO_LOGIC_GENERATOR_RUNNING;
						else inv.status = STATUS_DIO_LOGIC_GENERATOR;

						if (inv.in.cmd_pow_on==1) aux_K7.cmd_in = CMD_Q_ON;
						if (inv.in.cmd_pow_off==1)
						{
							aux_K7.cmd_in = CMD_Q_OFF;
							inv.out.cmd_DCS_stop = 1;
						}


						inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_GENERATOR;
						if (inv.in.cmd_pulses_on==1) inv.out.cmd_DCS_run = 1;
						if (inv.in.cmd_pulses_off==1) inv.out.cmd_DCS_stop = 1;
				break; //case DIO_LOGIC_INV_DCS_PROFILE_GENERATOR:
			} //end switch (inv.params.profile) {

break;

///////////////////////////////////////////////////////////////////////////////////////////////
case SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION: //Состояние «Ожидание» для исключения лишней работы K7
//	8.2.17	Если уровень генерируемой мощности в состоянии «РАБОТА» снижается ниже определенного значения, то система должна выполнить перевод в состояние «Ожидание». Это состояние необходимо т.к. постоянное напряжение может быть достаточно высоким и стабильным для выполнения условий сетевого питания в состоянии «Ожидание условий сетевого питания», что приведет к лишней попытке включения.  Для того, чтобы инвертор не включался сразу, и для того, чтобы его выходной контактор K7 не включался/отключался слишком часто, инвертор, после состояния «Эксплуатация», сначала переходит в состояние «Ожидание». В этом состоянии устройство остается определенное время и только после переключается в состояние «Ожидание условий сетевого питания».
//	8.2.18	Возможные смены состояния:
//	Если время ожидания прошло, устройство должно выполнить переключение в состояние «Ожидание условий сетевого питания».
//	Если происходит защита, то выполнить переключение в состояние «Ошибка».
//	Если дана команда управления «ОТКЛ» то  переключиться в состояние «ОТКЛЮЧЕН».

		if (inv.E == 1)  //ENTRY
				{
			inv.counter = 0;
			inv.sub_counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
			inv.sub_state = INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
		}

		//проверяем работу всех защит и если есть переходим в fail
		if ((inv.in.cmd_protect_pow_off!=0)||(inv.in.cmd_protect_pwm_off!=0))
			inv.state = SM_DIO_LOGIC_INV_FAULT;


		inv.out.ready = 1;

		if (inv.in.cmd_pow_off) {
			inv.out.cmd_DCS_stop = 1;
			aux_K7.cmd_in = CMD_Q_OFF;
			inv.state = SM_DIO_LOGIC_INV_POW_OFF;
		}

		////////////////////added 23.06.2023 для перехода в режим остров по снижению напряжения сети
		if(inv.in.DCS_Urms < dcs_prot.U1_min && sm_isla_batt_diesel.autostart == 1)
			inv.state = SM_DIO_LOGIC_INV_POW_OFF;
		///////////////////

		if (inv.in.DCS_Udc<inv.params.Udc_night)
		{
		p->counter++;
			if (p->counter>inv.params.P_low_time_s*1000)
			p->state = SM_DIO_LOGIC_INV_NIGHT_MODE;
		}
		else p->counter=0;

		switch (inv.sub_state) {
		case INV_SUBSTATE_CHECK_DAY_OR_NIGHT:

			// регулирование в этом состоянии включено, проверяем, что напряжение не упало
			if ((inv.in.DCS_Udc > inv.params.Udc_level_go_on)
					&& (inv.in.DCS_freq < inv.params.freq_max_level_go_on)
					&& (inv.in.DCS_freq > inv.params.freq_min_level_go_on)
					&& (inv.in.DCS_Urms > inv.params.Urms_level_go_on))
			{
				inv.sub_counter++;

				if (inv.in.cmd_pow_on) {
					inv.sub_counter =  0;
					inv.sub_state = INV_SUBSTATE_TRY_DAY_SYNC;
					inv.status = STATUS_DIO_LOGIC_SYNC;
					inv.sub_counter=0;
					inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;
					inv.out.cmd_DCS_run = 1;
					inv.attempts_counter=0;
					}
			}
			else
				inv.sub_counter=0;


			if (inv.attempts_counter<inv.params.P_low_attempts_max){
			if (inv.sub_counter > (inv.params.P_low_timeshift_s*500*(inv.attempts_counter+1))) {
				inv.sub_counter =  0;
				inv.sub_state = INV_SUBSTATE_TRY_DAY_SYNC;
				inv.status = STATUS_DIO_LOGIC_SYNC;
				inv.sub_counter=0;
				inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;
				inv.out.cmd_DCS_run = 1;
			}
			}
			break;

		case INV_SUBSTATE_TRY_DAY_SYNC: //try synced pulses, set DCS_mode SYNC check DC voltage drop


			inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;

			//if pulses operating normal for time_ms, then go next state
			if (inv.sub_counter >= inv.params.time_go_on_ms) {
				aux_K7.cmd_in = CMD_Q_ON;
			}

			if (aux_K7.state == STATE_Q_ON) {
				inv.attempts_counter++;
				inv.state = SM_DIO_LOGIC_INV_OPERATION;

			}

			inv.sub_counter++;

			break;
		default:break;
		}
	break;

case SM_DIO_LOGIC_INV_OPERATION: //Состояние «Работа»
		//		8.2.14	САУ инвертора работает в режиме выдачи активной мощности в сеть. Инвертор подключен к сети постоянного тока (Q4 включен) и к сети переменного тока (К7 включен).
		//		8.2.15	Возможные смены состояния:
		//		если уровень мощности снижается на определенное время ниже определенного значения, то условия эксплуатации больше не выполняются. Система переходит в состояние «Ожидание».
		//		Если происходит защита, то выполнить переключение в состояние «Защита».
		//		Если дана команда управления «ОТКЛ» то переключиться в состояние «ОТКЛЮЧЕН».

		if (inv.E == 1)
				{
			inv.counter = 0;
			inv.sub_counter=0;

			inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_P_GEN;


		}

		inv.sub_counter++;

		inv.status = STATUS_DIO_LOGIC_INV_OPERATING;
		if(cur_par.Pdc < _IQ(0.05)) inv.status = STATUS_DIO_LOGIC_FEED_OPERATION_LOW_LEVEL;
		if(cur_par.Pdc > _IQ(0.43))	inv.status = STATUS_DIO_LOGIC_FEED_OPERATION_MPP_PEAK;

		inv.out.ready = 1;
												//проверяем работу всех защит и если есть переходим в fault
												//Теперь только сигналы на отключение питания переводят инвертор в состояние защиты
												//защиты связанные с регулированием сбрасываются АПВ и перезапускают импульсы
		if ((inv.in.cmd_protect_pow_off!=0)) 	//TODO 206 - was ||(inv.in.cmd_protect_pwm_off!=0))
			inv.state = SM_DIO_LOGIC_INV_FAULT;

		//if sub_counter is greater then double P_low_time_s then inverter is working properly
		//and set attepts_counter to 0
		if (p->sub_counter>(inv.params.P_low_time_s*2*1000)) {
			p->attempts_counter=0;
			p->sub_counter=(inv.params.P_low_time_s*2*1000);
		}

		if (inv.in.cmd_pow_off) {
			inv.out.cmd_DCS_stop = 1;
			aux_K7.cmd_in = CMD_Q_OFF;
		}

		if (aux_K7.state==STATE_Q_OFF)
		{
			inv.state = SM_DIO_LOGIC_INV_POW_OFF;
		}

		if (inv.in.cmd_pulses_off) {
			inv.out.cmd_DCS_stop = 1;
		}

		if (inv.in.cmd_pulses_on) {
			inv.out.cmd_DCS_run = 1;
		}

		if(apl_protect.AR1.state == AR_STATE_FAIL)
		{
			cmd_logic.cmd.cmd_trip_reset = 1;
			inv.out.cmd_DCS_stop = 1;
			aux_K7.cmd_in = CMD_Q_OFF;
			inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
		}

		if (inv.in.DCS_Udc<_IQ(400.0/700) && dcdc.operating == 0)
		{
			inv.out.cmd_DCS_stop = 1;
			aux_K7.cmd_in = CMD_Q_OFF;
			inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
		}

		if (abs(mppt.P)<inv.params.P_night && dcdc.operating == 0) {
			p->counter++;
			if (p->counter>inv.params.P_low_time_s*1000)
			{
				inv.out.cmd_DCS_stop = 1;
				aux_K7.cmd_in = CMD_Q_OFF;
				inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
			}
		}
		else p->counter=0;


//TODO 209 если пропало напряжение сети то работает защита и циклы АПВ
//		if (inv.in.DCS_Urms > inv.params.Urms_level_go_on)
//		{
//
//		}



		//TODO 205 A&D11 force goes to SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION if DC voltage bellow threshold
		//TODO 206 исключил, т.к. теперь эту задачу решает  АПВ
//		if (inv.in.DCS_Udc<_IQmpy(inv.params.Udc_day,_IQ(0.7)))
//		{
//			inv.out.cmd_DCS_stop = 1;
//			aux_K7.cmd_in = CMD_Q_OFF;
//			inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
//		}


		break;



case SM_DIO_LOGIC_INV_NIGHT_MODE: //Состояние «Ночной режиме»
		if (inv.E == 1)
		{
			inv.counter = 0;
			inv.status=STATUS_DIO_LOGIC_INV_NIGHT_MODE;
		}
		//
		inv.attempts_counter=0; //start immediatly after NIGHT MODE

		//проверяем работу всех защит и если есть переходим в fail
		if ((inv.in.cmd_protect_pow_off!=0)||(inv.in.cmd_protect_pwm_off!=0))
			inv.state = SM_DIO_LOGIC_INV_FAULT;

		inv.out.ready = 1;

		if (inv.in.cmd_pow_on==1)  aux_Q4.cmd_in=CMD_Q_ON;
		if (inv.in.cmd_pow_off==1)  aux_Q4.cmd_in=CMD_Q_OFF;


		if (inv.in.DCS_Udc > inv.params.Udc_day)
		inv.counter++;
		else
		inv.counter = 0;

		if (inv.counter > (inv.params.go_day_mode_timeout_s * 1000))
			inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;


		break;

case SM_DIO_LOGIC_INV_FAULT: //Состояние Ошибка логиги переключений - это не защита! непредусмеотренное поведение логики
		if (inv.E == 1)  {
			inv.counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_FAULT;
		}
		inv.out.ready = 0;


		inv.out.cmd_DCS_stop=1;

		//проверяем что защиты нет, и снимаем FAULT
		if ((inv.in.cmd_protect_pow_off==0)&&(inv.in.cmd_protect_pwm_off==0))
		//if (inv.in.cmd_trip_reset==1)
		{
			if (aux_Q4.state == STATE_Q_ON)
		inv.state =  SM_DIO_LOGIC_INV_SELECT_PROFILE_AND_TRY_TO_RUN;
			else
		inv.state =  SM_DIO_LOGIC_INV_POW_OFF;

		}

		break;

/*********************************************************************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////                    TESTS ONLY
/////////////////////////////////////////////////////////////////////////////////////////////
case SM_DIO_LOGIC_INV_TEST:
		if (inv.E == 1) {
			inv.status = STATUS_DIO_LOGIC_INV_TEST_STOP;
			inv.out.ready = 1;
		}
	break;


	default:
		break;
	}
//end switch inv.state



}


