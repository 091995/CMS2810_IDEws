#ifndef _DCS_CTRL_H
#define _DCS_CTRL_H


#define SM_DCS_CTRL_INIT 					0
#define SM_DCS_CTRL_STOP 					1
#define SM_DCS_CTRL_RUN			 			2
#define SM_DCS_CTRL_RUN_DO_SYNC				3
#define SM_DCS_CTRL_RUN_SYNCED_P_GEN		4
#define SM_DCS_CTRL_RUN_GENERATOR			5
#define SM_DCS_CTRL_RUN_TEST				6


#define DCS_TEST_PARAM_TEST_PWM				2


////!Битовое поле слова управления
//  typedef struct
//  {
//unsigned int start:
//    1;
//unsigned int stop:
//    1;
//unsigned int trip_reset:
//    1;
//unsigned int reserved:
//    5;
//  } CMD_BIT;
//
////!Структура слова управления (содержит DRV_STATUS_BIT)
//  typedef union
//  {
//    unsigned int all;
//    CMD_BIT bit;
//  }TCmd;

////! Структура, содержащия основные задания
//  typedef volatile struct
//  {
//	long Id_ref; //Задание тока Iq
//    long P_ref;// Задание активной мощности
//    long Q_ref;// Задание активной мощности
//  } TRefs;

//! Структура, содержащия основные задания
  typedef volatile struct
  {
	long Urms; //Задание тока Iq
    long Udc;// Задание активной мощности
    long freq;// Задание активной мощности
    int16 ready;
    int16 running;

  } DCS_CTRL_OUT;


struct SDCS_Ctrl
{
	int16 cmd_run;
	int16 cmd_stop;
	int16 cmd_trip_reset;
	int16 cmd_set_mode;
	int16 test_param1;
	int16 test_param2;

	int16 cmd_Udc_ctrl_ena; //comand from DIO to control Udc, regulaton and protection enabled

	int16 counter;
	int16 state;
	int16 state_prev;
	int16 E;

	int16 ctrl_mode_synced_P_gen;
    DCS_CTRL_OUT out;
    void (*init)(struct SDCS_Ctrl*);
    void (*slow_calc)(struct SDCS_Ctrl*);
    void (*fast_calc)(struct SDCS_Ctrl*);
    void (*ms_calc)(struct SDCS_Ctrl*);
};

  typedef struct SDCS_Ctrl TDCS_Ctrl;

//!Инициализатор по умолчанию
#define DCS_CTRL_DEFAULTS { 0,0,0,0,0,0,0,\
		0,0,0,0,\
		0,\
		{0},\
		DCS_Ctrl_Init,\
		DCS_Ctrl_Slow_Calc,\
		DCS_Ctrl_Fast_Calc,\
		DCS_Ctrl_ms_Calc,\
		}

  void DCS_Ctrl_Init(TDCS_Ctrl*);
  void DCS_Ctrl_Slow_Calc(TDCS_Ctrl*);
  void DCS_Ctrl_Fast_Calc(TDCS_Ctrl*);
  void DCS_Ctrl_ms_Calc(TDCS_Ctrl*);



#endif






