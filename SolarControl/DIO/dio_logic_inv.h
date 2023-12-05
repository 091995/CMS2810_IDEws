#ifndef DIO_LOGIC_STATCOM_H
#define DIO_LOGIC_STATCOM_H


//#define DIO_LOGIC_INV_POW_OFF			0
//#define DIO_LOGIC_INV_POW_ON			1
//#define DIO_LOGIC_INV_POW_UNDEF			2


// States that are used in different state mashines
#define SM_DIO_LOGIC_INV_INIT 						0
#define SM_DIO_LOGIC_INV_INIT_PROC 					1
#define SM_DIO_LOGIC_INV_POW_OFF  					2
#define SM_DIO_LOGIC_INV_SELECT_PROFILE_AND_TRY_TO_RUN			3
#define SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION			4
#define SM_DIO_LOGIC_INV_OPERATION					5
#define SM_DIO_LOGIC_INV_NIGHT_MODE					6
#define SM_DIO_LOGIC_INV_FAULT						7
#define SM_DIO_LOGIC_INV_TEST	 					8


//#define


// INV
#define STATUS_DIO_LOGIC_INV_INIT					0
#define STATUS_DIO_LOGIC_INV_INIT_PROC				1
#define STATUS_DIO_LOGIC_INV_POW_OFF				2
#define STATUS_DIO_LOGIC_INV_CHECK_CONDITION		3
#define STATUS_DIO_LOGIC_INV_WAIT_ALL_CONDITION		4
#define STATUS_DIO_LOGIC_INV_OPERATING				5
#define STATUS_DIO_LOGIC_INV_NIGHT_MODE				6
#define STATUS_DIO_LOGIC_INV_FAULT					7
#define STATUS_DIO_LOGIC_INV_TEST_STOP				8
#define STATUS_DIO_LOGIC_INV_TEST_RUNNING			9
#define STATUS_DIO_LOGIC_FEED_OPERATION_LOW_LEVEL   10
#define STATUS_DIO_LOGIC_FEED_OPERATION_MPP_PEAK    11
#define STATUS_DIO_LOGIC_SYNC				    	12
#define STATUS_DIO_LOGIC_GENERATOR				   	13
#define STATUS_DIO_LOGIC_GENERATOR_RUNNING			14

//это профили, работы обрудования, которые может выбирать пользователь
//они должны быть одинаковы с профилями DCS
#define DIO_LOGIC_INV_DCS_PROFILE_NONE				0
#define DIO_LOGIC_INV_DCS_PROFILE_DO_SYNC			3
#define DIO_LOGIC_INV_DCS_PROFILE_U_Q_REG			2
#define DIO_LOGIC_INV_DCS_PROFILE_P_GEN				4
#define DIO_LOGIC_INV_DCS_PROFILE_GENERATOR			5
#define DIO_LOGIC_INV_DCS_PROFILE_COMMISIONING		6




#define DIO_LOGIC_INV_MODE_MANUAL 	0
#define DIO_LOGIC_INV_MODE_AUTO 	1
#define DIO_LOGIC_INV_MODE_TEST	 	2

//#define ALARM_DIO_LOGIC_INV_Q26_ON_WHEN_INIT 	0x0001
//#define ALARM_DIO_LOGIC_INV_K7_ON_WHEN_INIT 	0x0002

#define INV_SUBSTATE_INIT				0
#define INV_SUBSTATE_CHECK_DAY_OR_NIGHT 1
#define INV_SUBSTATE_TRY_DAY_SYNC		2
//#define INV_SUBSTATE_TRY_K7				2
#define INV_SUBSTATE_TRY_P_GEN			3



typedef struct
{
int CS_ready;     	//готовность СО
int CB_ready;		//готовность КРУ
int DCS_ready;
int DCS_running;
int cmd_trip_reset;
int cmd_pulses_off;
int cmd_pulses_on;
int cmd_pow_off;
int cmd_pow_on;
int cmd_protect_pow_off;
int cmd_protect_pwm_off;
int DCS_Udc;
int DCS_freq;
int DCS_Urms;
//int DCS_P; not used A&D
} DIO_LOGIC_INV_INP_DATA;

typedef struct
{
//int status;
int ready;
int cmd_DCS_set_mode;
int cmd_DCS_run;
int cmd_DCS_stop;
int cmd_DCS_trip_reset;
}  DIO_LOGIC_INV_OUT_DATA;

typedef struct
{
int Udc_level_go_on;
int Udc_level_go_on_fail;
int freq_max_level_go_on;
int freq_min_level_go_on;
int Urms_level_go_on;
int time_go_on_ms;
int Udc_day;
int Udc_night;
int Udc_min_lim_power;
int Udc_max_lim_power;
int P_night;
int go_day_mode_timeout_s;
int go_night_mode_timeout_s;
int P_low_time_s; //Базисное время ожидания перед новой попыткой старта, после выключения устройства.
int P_low_timeshift_s;//Временной сдвиг, который после выключения устройства прибавляется к базисному времени ожидания.
int P_low_attempts_max;//Максимальное количество прибавлений временного сдвига.
int mode; //MODE - MANUAL, AUTO, TEST
int mode_prev;
int test_mode;
int test_param;
int profile;	//тип профилей смтри выше.DIO_LOGIC_INV_DCS_PROFILE_NONE
} DIO_LOGIC_INV_PARAMS;




typedef struct
{
 DIO_LOGIC_INV_INP_DATA in;
 DIO_LOGIC_INV_OUT_DATA out;
 DIO_LOGIC_INV_PARAMS params;


 int status;
 int status_prev;
 //int prot_word;
 int alarm_word;

 int counter;
 int state;
 int state_prev; 
 int E;

  int sub_counter;
  int sub_state;
  int sub_state_prev;
  int sub_E;

  int attempts_counter;

// int counter2;
// int state2;
// int state2_prev;
// int state2_prev1;
// int E2;

// int aux_ADC_and_CB_protect_word; //for terminal only
// int aux_ADC_and_CB_protect_mask_word; //for terminal only
// int aux_ADC_and_CB_protect_mask_apv_word; //for terminal only
// int aux_ADC_and_CB_protect_mask_switch_word; //for terminal only
// int aux_ADC_and_CB_alarm_word; //for terminal only
// int aux_ADC_and_CB_alarm_mask_word; //for terminal only
void (*init)();
void (*ms_calc)();

} DIO_LOGIC_INV;



// Здесь присваиваем значениЯ по умолчанию длЯ них
#define DIO_LOGIC_INV_DEFAULTS {{0},{0},{0},\
				0,0,0,\
				0,0,0,0,\
				0,0,0,0,\
				0,\
                (void (*)(long))DIO_LOGIC_INV_Init,\
                (void (*)(long))DIO_LOGIC_INV_ms_Calc,\
                 }

void DIO_LOGIC_INV_Init();
void DIO_LOGIC_INV_ms_Calc();

#endif
