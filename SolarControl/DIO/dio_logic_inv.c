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
	//inv.params.Udc_low_level = _IQ(0.13); //13% �� ���� �� ���������� �� 0.866 (��������� ���������) �� ��������� � 2-�� ���������� �������
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
inv.params.time_go_on_ms 			=  10*1000; //1 ��� TODO4

inv.params.Udc_min_lim_power = _IQ(450.0/700); //start limit power from this point
inv.params.Udc_max_lim_power = _IQ(750.0/700); //start limit power from this point


inv.params.freq_max_level_go_on	= _IQ(1.05);
inv.params.freq_min_level_go_on	= _IQ(0.95);
inv.params.Urms_level_go_on	= _IQ(0.8);
inv.params.Udc_day			= _IQ(600.0/700);
inv.params.Udc_night		= _IQ(250.0/700);
//
inv.params.go_day_mode_timeout_s = 60;				//����� ���������� ������� ������� � ������ WAIT_DC_CONDITION ��� ������� �������
inv.params.go_night_mode_timeout_s = 300;

inv.params.P_low_time_s =  3*60; //�������� ����� �������� ����� ����� �������� ������, ����� ���������� ����������.
inv.params.P_low_timeshift_s = 3*60;//��������� �����, ������� ����� ���������� ���������� ������������ � ��������� ������� ��������.
inv.params.P_low_attempts_max = 5 ;//������������ ���������� ����������� ���������� ������.
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
	case SM_DIO_LOGIC_INV_INIT: //�������������, ���� ����� ���� �������� ��������� ������.

		if (inv.E == 1) {
			inv.counter = 0;
		}
		inv.out.ready = 0;
		inv.status = STATUS_DIO_LOGIC_INV_INIT;
		inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_NONE; //���� DCS ����� ������ �� ������.

		//��� ����������� ������ ���� ���������, ����� ������
		/*	if (inv.aux_Q1.state==STATE_Q_OFF) inv.prot_word|=P_Q1_ON_WHEN_INIT;
		 if (inv.aux_Q2.state==STATE_Q_OFF) inv.prot_word|=P_Q2_ON_WHEN_INIT;
		 if (inv.aux_Q3.state==STATE_Q_OFF) inv.prot_word|=P_Q3_ON_WHEN_INIT;
		 if (inv.aux_Q4.state==STATE_Q_OFF) inv.prot_word|=P_Q4_ON_WHEN_INIT;
		 */
		inv.counter++;
		if (inv.counter >= 1000) { // ����� ����������

			inv.attempts_counter=0;
			inv.state = SM_DIO_LOGIC_INV_INIT_PROC;

		}
		break;
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
	case SM_DIO_LOGIC_INV_INIT_PROC: //��������� ��������� ���� ���������, ��������� ��������������
		if (inv.E == 1) {
			inv.counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_INIT_PROC;
		}

//Set outputs
		inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_NONE; //���� DCS ����� ������ �� ������.
		inv.out.ready = 0;

//control aux_io TODO 220 - ��� ����� �� �����������. A&D ��������
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
	case SM_DIO_LOGIC_INV_POW_OFF: //�������� ��������, ���� ���� ��������� � ������ ���������� �������
//	8.2.7	�������� �������� �� ���� ����������� � ����������� ���� - ��������� K7 ��������, � ����������� Q4 ����� ���� �������� ��� �������.
//	8.2.8	���������� �������� � ������ ���������������, ���������� ��������� �� �����������.
//	8.2.9	��������� ����� ���������:
//	������� ���˻ ������ ������ ��������� �� Q4, � � ������ ��������� ��������� ���������� �������  � ��������� ��������� ������� �������� ��������.
//   ���� ������� ����������� ���������� ����������� ���� ����������� �������� ���������� �� �����,
// ������� ��� ����� ��������, �� ���������� ��������� � ��������� ��������� ������� �������� ��������.

		if (inv.E == 1) {
			inv.counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_POW_OFF;

		}
		inv.out.ready = 1;

		//if MODE_AUTO, i.e. autostart after power on

		//Only here Profile may be changed!!! TODO5 - logic needs to be improved
		if (cmd_logic.status.profile==5) inv.params.profile=DIO_LOGIC_INV_DCS_PROFILE_GENERATOR;
		else inv.params.profile=DIO_LOGIC_INV_DCS_PROFILE_P_GEN;

		//���� ��� ������ ������������� ��������� ��������� �� �������� ���
		if ((inv.in.cmd_protect_pow_off==0)&&(inv.in.cmd_protect_pwm_off==0)) {
			//��������� ��������� ������������ ����������� ����, ���� ����� ��������������, �� ��������
			//	if (inv.params.mode == DIO_LOGIC_INV_MODE_AUTO) {
			aux_Q4.cmd_in=CMD_Q_ON; //always turn on Q4

			if (inv.in.cmd_pow_on==1)
				inv.state = SM_DIO_LOGIC_INV_SELECT_PROFILE_AND_TRY_TO_RUN;//aux_Q4.cmd_in = CMD_Q_ON;


			inv.out.cmd_DCS_set_mode = DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC;


			//if (inv.in.cmd_pulses_on) inv.out.cmd_DCS_run = 1;
			//if (inv.in.cmd_pulses_off) inv.out.cmd_DCS_stop = 1;

		}


		//���� ������� Q4, �.�. ���������� ��������� ������, �� ����� ��������� � �������� �������� ����������
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
case SM_DIO_LOGIC_INV_SELECT_PROFILE_AND_TRY_TO_RUN: //8.2.10	��������� ��������� ������� �������� ��������("�������������")
		if (inv.E == 1) {
			inv.counter = 0;
			inv.sub_counter = 0;// INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
			inv.sub_state=INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
			inv.status = STATUS_DIO_LOGIC_INV_CHECK_CONDITION;
		}

		inv.out.ready = 1;


	//����� ��������� �������� ������.
	if (inv.in.cmd_pow_off==1) {
		inv.out.cmd_DCS_stop=1;
		aux_K7.cmd_in=CMD_Q_OFF;
		inv.state=SM_DIO_LOGIC_INV_POW_OFF;
	}


// �������� �� �������.
			switch (inv.params.profile) {
				case DIO_LOGIC_INV_DCS_PROFILE_P_GEN:

					//��������� ������ ���� ����� � ���� ���� ��������� � fail
					if ((inv.in.cmd_protect_pow_off!=0)||(inv.in.cmd_protect_pwm_off!=0))
						inv.state = SM_DIO_LOGIC_INV_FAULT;

					switch (inv.sub_state) {
					case INV_SUBSTATE_CHECK_DAY_OR_NIGHT:
						//��������� ������� �������� ������
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
						//���� ���� ������� ��� ������ , �� ��������� � �������������, ������ ����� ��� DCS � ���� ��������
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

						//���� ������ ���� ���������, �� ��������� DCS � ���� � �������� ����/����. ���� ����� ��������������, �� ������ ���� ����� ����� ��������� ������
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

						// ������������� � ���� ��������� ��������, ���������, ��� ���������� �� �����
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

					//��������� ������ ����������� ����� � ���� ���� ��������� � fail
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
case SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION: //��������� ��������� ��� ���������� ������ ������ K7
//	8.2.17	���� ������� ������������ �������� � ��������� �������� ��������� ���� ������������� ��������, �� ������� ������ ��������� ������� � ��������� ���������. ��� ��������� ���������� �.�. ���������� ���������� ����� ���� ���������� ������� � ���������� ��� ���������� ������� �������� ������� � ��������� ��������� ������� �������� ��������, ��� �������� � ������ ������� ���������.  ��� ����, ����� �������� �� ��������� �����, � ��� ����, ����� ��� �������� ��������� K7 �� ���������/���������� ������� �����, ��������, ����� ��������� ��������������, ������� ��������� � ��������� ���������. � ���� ��������� ���������� �������� ������������ ����� � ������ ����� ������������� � ��������� ��������� ������� �������� ��������.
//	8.2.18	��������� ����� ���������:
//	���� ����� �������� ������, ���������� ������ ��������� ������������ � ��������� ��������� ������� �������� ��������.
//	���� ���������� ������, �� ��������� ������������ � ��������� �������.
//	���� ���� ������� ���������� ����˻ ��  ������������� � ��������� ��������ͻ.

		if (inv.E == 1)  //ENTRY
				{
			inv.counter = 0;
			inv.sub_counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
			inv.sub_state = INV_SUBSTATE_CHECK_DAY_OR_NIGHT;
		}

		//��������� ������ ���� ����� � ���� ���� ��������� � fail
		if ((inv.in.cmd_protect_pow_off!=0)||(inv.in.cmd_protect_pwm_off!=0))
			inv.state = SM_DIO_LOGIC_INV_FAULT;


		inv.out.ready = 1;

		if (inv.in.cmd_pow_off) {
			inv.out.cmd_DCS_stop = 1;
			aux_K7.cmd_in = CMD_Q_OFF;
			inv.state = SM_DIO_LOGIC_INV_POW_OFF;
		}

		////////////////////added 23.06.2023 ��� �������� � ����� ������ �� �������� ���������� ����
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

			// ������������� � ���� ��������� ��������, ���������, ��� ���������� �� �����
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

case SM_DIO_LOGIC_INV_OPERATION: //��������� �������
		//		8.2.14	��� ��������� �������� � ������ ������ �������� �������� � ����. �������� ��������� � ���� ����������� ���� (Q4 �������) � � ���� ����������� ���� (�7 �������).
		//		8.2.15	��������� ����� ���������:
		//		���� ������� �������� ��������� �� ������������ ����� ���� ������������� ��������, �� ������� ������������ ������ �� �����������. ������� ��������� � ��������� ���������.
		//		���� ���������� ������, �� ��������� ������������ � ��������� �������.
		//		���� ���� ������� ���������� ����˻ �� ������������� � ��������� ��������ͻ.

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
												//��������� ������ ���� ����� � ���� ���� ��������� � fault
												//������ ������ ������� �� ���������� ������� ��������� �������� � ��������� ������
												//������ ��������� � �������������� ������������ ��� � ������������� ��������
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


//TODO 209 ���� ������� ���������� ���� �� �������� ������ � ����� ���
//		if (inv.in.DCS_Urms > inv.params.Urms_level_go_on)
//		{
//
//		}



		//TODO 205 A&D11 force goes to SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION if DC voltage bellow threshold
		//TODO 206 ��������, �.�. ������ ��� ������ ������  ���
//		if (inv.in.DCS_Udc<_IQmpy(inv.params.Udc_day,_IQ(0.7)))
//		{
//			inv.out.cmd_DCS_stop = 1;
//			aux_K7.cmd_in = CMD_Q_OFF;
//			inv.state = SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION;
//		}


		break;



case SM_DIO_LOGIC_INV_NIGHT_MODE: //��������� ������� ������
		if (inv.E == 1)
		{
			inv.counter = 0;
			inv.status=STATUS_DIO_LOGIC_INV_NIGHT_MODE;
		}
		//
		inv.attempts_counter=0; //start immediatly after NIGHT MODE

		//��������� ������ ���� ����� � ���� ���� ��������� � fail
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

case SM_DIO_LOGIC_INV_FAULT: //��������� ������ ������ ������������ - ��� �� ������! ������������������ ��������� ������
		if (inv.E == 1)  {
			inv.counter = 0;
			inv.status = STATUS_DIO_LOGIC_INV_FAULT;
		}
		inv.out.ready = 0;


		inv.out.cmd_DCS_stop=1;

		//��������� ��� ������ ���, � ������� FAULT
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


