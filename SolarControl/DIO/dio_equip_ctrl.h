#ifndef DIO_EQUIP_CTRL_H
#define DIO_EQUIP_CTRL_H


///////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////////
//STATUS definitions
//#define DIO_LOGIC_EXT_IO_STATUS_INIT		0
//#define DIO_LOGIC_EXT_IO_STATUS_WAIT_READY	1
//#define DIO_LOGIC_EXT_IO_STATUS_READY		2
//#define DIO_LOGIC_EXT_IO_STATUS_ALARM		3
//#define DIO_LOGIC_EXT_IO_STATUS_PROTECT		4



///////////////////////////////////////////////////////////////////////////////////////////
//CAN_IO
typedef struct
{
int state;
int state_prev;
int E;
int counter;
int status;
	//#1
	float Riso; //analog input from bender iso 0-10V 10bit IQ8.8 MOhm
	int Q4_on_K21;
	int Q4_off_K22;
	int Q4_aux;
	int bender_iso_inp1;
	int bender_iso_inp2;
	int opn_DC;
	//#2
	int opn_AC;
	int K60_aux;
	int F60_aux;
	int F61_aux;
	int Q26_aux;
	int S100200300;
	//#3
	int Q6_on_K21;
	int Q6_off_K22;
	int bender_off_K23;
	int Q6_aux;

	int diesel_start;
	int diesel_operating;
	int diesel_fuel;

	int DC_precharge_on;

	//link
	int link1;
	int link2;
	int link3;

} AUX_CAN_IO;
////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
// вспомогательный автомат. ¬ нем рассчитываются состояния всего оборудования
typedef struct
{
int alarm_word;
int protect_word;
void (*init)();
void (*ms_calc)();
void (*fast_calc)();
} DIO_EQUIP_CTRL;


#define DIO_EQUIP_CTRL_DEFAULTS {0,0,\
							(void (*)())DIO_EQUIP_CTRL_Init,\
							(void (*)())DIO_EQUIP_CTRL_ms_Calc,\
							(void (*)())DIO_EQUIP_CTRL_FastCalc,\
						  }

// «десь объявляем прототиты функций модуля
void DIO_EQUIP_CTRL_Init();
void DIO_EQUIP_CTRL_ms_Calc();
void DIO_EQUIP_CTRL_FastCalc();

#endif
