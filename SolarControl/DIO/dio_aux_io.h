#ifndef DIO_AUX_IO_H
#define DIO_AUX_IO_H

// автомат конторля правильности переключений Q по блок контакту auxQ 

#define STATE_Q_INIT 					0
#define STATE_Q_OFF 					1
#define STATE_Q_GO_ON                  	2
#define STATE_Q_ON                  	3
#define STATE_Q_GO_OFF                 	4
#define STATE_Q_TURNING_FAILED          5

#define STATUS_Q_OFF					1
#define STATUS_Q_ON						2
#define STATUS_Q_UNDEFINED				3

//defines to improve text 
#define CMD_Q_ON   1
#define CMD_Q_OFF -1
//врем€ удержани€ команды дл€ сигналов cmd_on cmd_off
#define AUX_Q_CMD_TIME_MS				500

typedef struct
{
int state;
int state_prev;
int E;
int counter;

int status;
int time_on_ms;
int time_off_ms;
int bk_fail;			//during continous state aux changed
int switch_fail;		//mean when changing state no aux
int aux_on;
int aux_off;

int cmd_in;
int cmd_in_prev;
int cmd_on;
int cmd_off;
int cmd_trip_reset;

int hold_on;
int hold_off;

int log[8];
int log_counter;
void (*init)();
void (*calc)();
} DIO_AUX_Q;

#define DIO_AUX_Q_DEFAULTS {-1,0,0,0,\
							0,0,0,0,0,0,0,\
							0,0,0,0,0,\
							0,0,\
							{0},0,\
							(void (*)(long))DIO_AUX_Q_Init,\
							(void (*)(long))DIO_AUX_Q_Calc,\
						  }

void DIO_AUX_Q_Init(DIO_AUX_Q*p);
void DIO_AUX_Q_Calc(DIO_AUX_Q*p);
////////////////////////////////////////////////////////////////////////////////////////////
//typedef struct
//{
//int ena;
//int counter;
//int heartbeat[5];
//int heartbeat_sum;
//} AUX_TIMER;








////////////////////////////////////////////////////////////////////////////////////////////
// вспомогательный автомат. ¬ нем рассчитываются состояния всего оборудования
typedef struct
{
	int alarm_word;
	int protect_word;
	void (*init)();
	void (*calc)();
} DIO_AUX_IO;

// «десь присваиваем значения по умолчанию для них
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\

#define DIO_AUX_IO_DEFAULTS {0,0,\
							(void (*)(long))DIO_AUX_IO_Init,\
							(void (*)(long))DIO_AUX_IO_Calc,\
						  }

// «десь объявляем прототиты функций модуля
void DIO_AUX_IO_Init();
void DIO_AUX_IO_Calc();

#endif
