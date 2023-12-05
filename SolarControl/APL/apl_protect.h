#ifndef APL_PROTECT_H
#define APL_PROTECT_H


#define SM_PROTECT_INIT 				0	
#define SM_PROTECT_NO_TRIP				1
#define SM_PROTECT_TRIP					2
#define SM_PROTECT_TRIP_RESET			3


/*

//prot_word0
#define P_Q1TK1_NO_BK_WHEN_ON  			0x0001
#define P_Q2TK1_NO_BK_WHEN_ON           0x0002
#define P_Q3TK1_NO_BK_WHEN_ON  			0x0004
#define P_Q4TK1_NO_BK_WHEN_ON           0x0008
#define P_Q1TK1_BK_WHEN_OFF  			0x0010
#define P_Q2TK1_BK_WHEN_OFF             0x0020
#define P_Q3TK1_BK_WHEN_OFF  			0x0040
#define P_Q4TK1_BK_WHEN_OFF             0x0080
#define P_Q1TK1_ON_WHEN_INIT			0x0100
#define P_Q2TK1_ON_WHEN_INIT            0x0200
#define P_Q3TK1_ON_WHEN_INIT            0x0400
#define P_Q4TK1_ON_WHEN_INIT            0x0800

//prot_word[1]
#define P_NO_CC_READY2_WHEN_CHARGING			0x0001
#define P_SOFT_FAST_LOOP_FAIL 					0x0002
#define P_CS_READY_FAIL_WHEN_READY_TO_RUN  		0x0004	
#define P_CC_READY1_FAIL_WHEN_READY_TO_RUN  	0x0008
#define P_CC_READY2_FAIL_WHEN_READY_TO_RUN  	0x0010
#define P_KRU_READY_FAIL_WHEN_READY_TO_RUN  	0x0020
#define P_SYRZA_READY_FAIL_WHEN_READY_TO_RUN 	0x0040 
#define P_CS_READY_FAIL_WHEN_RUNNING  			0x0080	
#define P_CC_READY1_FAIL_WHEN_RUNNING  			0x0100
#define P_CC_READY2_FAIL_WHEN_RUNNING  			0x0200
#define P_KRU_READY_FAIL_WHEN_RUNNING  			0x0400
#define P_SYRZA_READY_FAIL_WHEN_RUNNING 		0x0800 
#define P_SOFT_PWR_ZONE_FAST_CHANGE				0x1000 
#define P_SOFT_MIN_LEVEL_DURATION               0x2000
#define P_SOFT_TO_MANY_LEVELS_ON_PERID          0x4000
#define P_SOFT_PWR_UNDEFINED_CUR_STATE			0x8000


//prot_word[2] - можно только ј¬ј–»» —”–«џ
#define P_CMD_LOGIC_UNDEFINED_SOURCE	0x0001
#define P_FPGA_TIMERA_ERROR 			0x0002
#define P_FPGA_TIMERB_ERROR				0x0004
#define P_FPGA_TIMERC_ERROR				0x0008
#define P_FPGA_WD_ERROR					0x0010

//prot_word[3] - только аппаратные аварии
#define P_SYRZA_LOCAL_EMERGENCY_STOP 	0x0001
#define P_SYRZA_HW_TRIP_IA_MAX			0x0002
#define P_SYRZA_HW_TRIP_IB_MAX			0x0004
#define P_SYRZA_HW_TRIP_IC_MAX			0x0008
#define P_SYRZA_HW_TRIP_UDC1_MAX		0x0010
#define P_SYRZA_HW_TRIP_UDC2_MAX		0x0020
#define P_SYRZA_HW_TRIP_UDC12_DIFF		0x0040

//prot_word[4] - только программные аварии
#define P_PROG_I_MAX                	0x0001
#define P_PROG_I_NO_PULSE              	0x0002
#define P_PROG_UDC_MAX		        	0x0004
#define P_PROG_SINH_BAD                 0x0008
#define P_PROG_CANT_LOAD_PARAMS         0x0010
#define P_PROG_CANT_SAVE_PARAMS         0x0020
#define P_PROG_SPWM_TIMER_NOT_SYNC 		0x0040 
#define P_PROG_UDC_MIN		        	0x0080
#define P_PROG_UDC_DELTA            	0x0100
#define P_PROG_OPWM_CORR_DATA_NOT_READY	0x0200
#define P_PROG_UDC_RAISE_BEZ_IMP		0x0400
#define P_PROG_UDC_DIFFER_UST			0x0800
#define	P_PROG_US						0x1000
*/

#define	AR_STATE_INIT				0
#define	AR_STATE_STOP				1
#define	AR_STATE_WAIT_PROTECT_PRE	2
#define	AR_STATE_TRIP_RESET_PRE		3
#define	AR_STATE_PULSES_ON_PRE		4
#define	AR_STATE_WAIT_TIME1			5
#define	AR_STATE_TRIP_RESET1		6
#define	AR_STATE_PULSES_ON1			7
#define	AR_STATE_WAIT_TIME2			8
#define	AR_STATE_TRIP_RESET2		9
#define	AR_STATE_PULSES_ON2			10
#define	AR_STATE_WAIT_TIME3			11
#define	AR_STATE_TRIP_RESET3		12
#define	AR_STATE_PULSES_ON3			13
#define	AR_STATE_FAIL				14


typedef struct
{
int state;
int state_prev;
int E;
int counter;

short 	ena;

int trip_reset;
int pulses_on;
int flag_protect;
int flag_protect_Q_off;
int in_trip_reset;
int acting_time1;
int acting_time2;
int acting_time3;
int acting_time_pre;
int ready_time;
int ctrl_status;
int in_cmd_stop;
int AR_acting;
int AR_word[8];
} APL_PROTECT_AR;


typedef struct
{
APL_PROTECT_AR AR1;

Uint16*p_prot_word[2];
Uint16*p_prot_off_word[2];
//Uint16 prev_prot_word[2];
Uint16 masked_word[2];
Uint16 masked_off_word[2];

int AR_word[2];
//Uint16*p_mask_word[2];
Uint16 mask_apv_word[2];
//Uint16*p_mask_switch_word[2];


Uint16 counter1;
Uint16 state1;
Uint16 state_prev1;
Uint16 E1;


Uint16 flag_protect1;

Uint16 flag_protect1_Q_off;

int cmd_trip_reset1;

int dcs_ctrl_running;

void (*init)();
void (*calc)();
void (*ms_calc)();
} APL_PROTECT;

// «десь присваиваем значения по умолчанию для них
#define APL_PROTECT_DEFAULTS {{0},\
				{0},{0},{0},{0},\
				{0},{0},\
				0,0,0,0,\
				0,0,0,0,\
                (void (*)(long))APL_PROTECT_Init,\
                (void (*)(long))APL_PROTECT_Calc, \
				(void (*)(long))APL_PROTECT_ms_Calc \
                 }

// «десь объявляем прототиты функций модуля
void APL_PROTECT_Init();
void APL_PROTECT_Calc();
void APL_PROTECT_ms_Calc();
#endif
