#ifndef M_CMD_LOGIC_H
#define M_CMD_LOGIC_H
 
#define SM_CMD_LOGIC_INIT 				0	


typedef struct
{
unsigned int cmd_pow_on:1; //0
unsigned int cmd_pow_off:1; //1
unsigned int cmd_trip_reset:1; //2
unsigned int cmd_pulses_on:1; //3
unsigned int cmd_pulses_off:1; //4
unsigned int cmd_more:1; //5
unsigned int cmd_less:1; //6
unsigned int cmd_set_cmd_source_LOCAL:1; //7
unsigned int cmd_set_cmd_source_REMOTE:1; //8
unsigned int cmd_set_refs_source_LOCAL:1; //9
unsigned int cmd_set_refs_source_REMOTE:1; //10
unsigned int cmd_connect_COPAIN:1; //11
unsigned int cmd_separate_COPAIN:1;//12
unsigned int cmd_set_dio_logic_mode_manual:1; //13
unsigned int cmd_set_dio_logic_mode_auto:1; //14
unsigned int cmd_set_dio_logic_mode_test:1; //15
 } CMD_FROM_SOURCE_BIT;

 //!—труктура дл€ статуса системы управлени€
typedef union {
	unsigned int all;
	CMD_FROM_SOURCE_BIT bit;
} CMD_FROM_SOURCE;

typedef struct {
	 int P_ref;
	 int P_ref_prev;
	 int P_dcdc_ref;
	 int Q_ref;
	 int U_ref;
}REFS_FROM_SOURCE;


typedef struct
{
unsigned int cmd_pow_on;
unsigned int cmd_pow_off;
unsigned int cmd_trip_reset;
unsigned int cmd_pulses_on;
unsigned int cmd_pulses_off;
unsigned int cmd_more;
unsigned int cmd_less;
unsigned int cmd_set_cmd_source_LOCAL;
unsigned int cmd_set_cmd_source_REMOTE;
unsigned int cmd_set_refs_source_LOCAL;
unsigned int cmd_set_refs_source_REMOTE;
unsigned int cmd_set_dio_logic_mode_manual;
unsigned int cmd_set_dio_logic_mode_auto;
unsigned int cmd_set_dio_logic_mode_test;
unsigned int cmd_set_profile1;
unsigned int cmd_set_profile2;
unsigned int cmd_set_profile3;

unsigned int cmd_pow_on_prev;
unsigned int cmd_pow_off_prev;
unsigned int cmd_trip_reset_prev;
unsigned int cmd_pulses_on_prev;
unsigned int cmd_pulses_off_prev;
unsigned int cmd_more_prev;
unsigned int cmd_less_prev;
unsigned int cmd_set_cmd_source_LOCAL_prev;
unsigned int cmd_set_cmd_source_REMOTE_prev;
unsigned int cmd_set_refs_source_LOCAL_prev;
unsigned int cmd_set_refs_source_REMOTE_prev;
unsigned int cmd_set_dio_logic_mode_manual_prev;
unsigned int cmd_set_dio_logic_mode_auto_prev;
unsigned int cmd_set_dio_logic_mode_test_prev;
unsigned int cmd_set_ctrl_profile1_prev;
unsigned int cmd_set_ctrl_profile2_prev;
unsigned int cmd_set_ctrl_profile3_prev;
int CMD_source;
} CMD_OUT;

typedef struct {
int P_ref;
int P_dcdc_ref;
int Q_ref;
int U_ref;
int REFS_source;
} REFS_OUT;





#define CTRL_PROFILE_GEN_P_MODE				0
#define CTRL_PROFILE_GEN_Q_MODE				1
#define CTRL_PROFILE_AUTONOM_GEN_MODE 		2



#define CMD_LOGIC_CMD_SOURCE_LOCAL			0
#define CMD_LOGIC_CMD_SOURCE_REMOTE			1

#define CMD_LOGIC_REFS_SOURCE_LOCAL			0
#define CMD_LOGIC_REFS_SOURCE_REMOTE		1



typedef struct
{
unsigned short profile;
unsigned short cmd_source;
unsigned short refs_source;
unsigned short dio_logic_mode;

//unsigned int cmd_source_prev;
//unsigned int refs_source_prev;
//unsigned int dio_logic_mode_prev;
} 
CMD_LOGIC_STATUS;




typedef struct
{
	CMD_FROM_SOURCE local_cmd;
	CMD_FROM_SOURCE remote_cmd;
	REFS_FROM_SOURCE local_refs;
	REFS_FROM_SOURCE remote_refs;

	CMD_OUT cmd;
	REFS_OUT refs;


CMD_LOGIC_STATUS status;

int counter;
int state;
int state_prev;
int E;
void (*init)();
void (*ms_calc)();
} CMD_LOGIC;





#define CMD_LOGIC_DEFAULTS { {0},{0},{0},{0},\
				{0},{0},\
				{0},\
				0,0,0,0,\
                (void (*)())CMD_LOGIC_Init,\
                (void (*)())CMD_LOGIC_1ms_Calc,\
                 }

void CMD_LOGIC_Init();
void CMD_LOGIC_1ms_Calc();
#endif
