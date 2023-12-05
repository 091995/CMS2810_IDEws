/*****************************************************************************/
/* Модуль связи с HMI Delta - Terminal по Modbus */
/* Разработал Дроздов А.В. */
/*****************************************************************************/

#ifndef RS_TERMINAL_H
#define RS_TERMINAL_H


/* Определения для Terminal*/
#define CMD_REGREAD             0x03
#define CMD_REGWRITE            0x06
#define CMD_MREGWRITE           0x10
#define WRITE_HEADER            5

//БЛИС 1
#define START_ADDR_READ_bl1         100
#define START_ADDR_WRITE1_bl1    	200
#define START_ADDR_WRITE2_bl1     	280
//БЛИС 2
#define START_ADDR_READ_bl2        110
#define START_ADDR_WRITE1_bl2      120
#define START_ADDR_WRITE2_bl2      340

#define NUMBER_REGS_FOR_READ 	10
#define NUMBER_REGS_FOR_WRITE1 	80
#define NUMBER_REGS_FOR_WRITE2 	60

#define BUFF_READY             1
#define BUFF_EMPTY             2

#define TERMINAL_IDLE					0
#define TERMINAL_READ_REQ				1
#define TERMINAL_WHAIT_WRITE_DATA_READY 2
#define TERMINAL_WRITE_REQ				3
#define TERMINAL_WRITE2_REQ				4

#define STATE_READY   						0
#define STATE_OPERATION_FAILED   			1
#define STATE_WAIT_BUFF_FOR_READ_REQ   		2
#define STATE_TRANSMIT_BUFF_FOR_READ_REQ   	3
#define STATE_TRANSMIT_BUFF_FOR_WRITE_REQ   4
#define STATE_WAIT_REQUESTED_BUFF           5
#define STATE_WAIT_BUFF_FOR_WRITE_REQ		6
#define STATE_WAIT_UNSWER		           	7
#define STATE_WAIT_BUFF_FOR_REQ		   		8
#define STATE_TRANSMIT_BUFF_FOR_REQ		   	9


/*Значения слова word_in*/
//word_in[0]
//системное слово - Link и служебные биты
//#define TERMINAL_LINK_WORD			0x0
//#define TERMINAL_LINK_MASK 			0x00FF //cnt 255


//typedef struct
//{
//	unsigned short	set_source_scada;
//	unsigned short	set_source_local;
//	unsigned short	allow_correct_PA;
//	unsigned short	disallow_correct_PA;
//	//short			correct_P;
//	//short 			P;
//	//unsigned short 	U1_220;
//	//unsigned short 	U2_220;
//	short			P_plus;
//	short			P_min;
//	short			U1_plus;
//	short			U1_min;
//	short			U2_plus;
//	short			U2_min;
//	//short 			redu_ena;
//	//short 			redu_dis;
//	//short 			redu_go_active;
//	//short 			redu_go_passive;
//} TERMINAL_CMD_REFS;

typedef struct
{

//TERMINAL_CMD_REFS 	cmd_refs;
//float 			float_in[15];
//float 			float_out[15];
short 			word_in[NUMBER_REGS_FOR_READ];
short 			word_out[NUMBER_REGS_FOR_WRITE1];
short 			word_out2[NUMBER_REGS_FOR_WRITE2];
unsigned short 	inp_buff[200];
unsigned short	out_buff[200];

unsigned short 	recv;
unsigned short 	active_flag;

 int 			send_req_error;
 int 			read_req_error;
 int 			crc_fail_counter;
 int 			data_in_ready;    //флаг синхронизации фонового кольца и терминала

 int 			inp_buff_state;
 int 			out_buff_state;
 int 			ms_counter;
 int 			slow_state;
 int 			count_pause;

 int 			slow_E;
 int 			slow_state_prev;
 int 			state;
 int 			E;

 int 			state_prev;
 int 			counter;
 int 			status;
 int			crc_ok_cnt;

 int 			link;
 int 			link_prev;
 int 			link_cnt;
 int 			link_OK;
 int 			link_cnt_send;

 int 			TX_nRX_dir_counter;

 unsigned short 	flag_write_to_flash;
 unsigned short 	U1_load_to_flash;
 unsigned short 	U2_load_to_flash;
 unsigned short 	P_load_to_flash;

 short			flag_error_read;
 short 			NeedForSave; //TODO103 Андрей-добавил для команды сохранить параметры с экрана.
 	 	 	 	 	 	 	 // еще нужно результат на ONI - успешно/неуспешно.


 void 			(*init)();
 void 			(*slow_calc)();
 void 			(*ms_calc)();
 void 			(*fast_calc)();
} TERMINAL;

//TERMINAL terminal;

//Константа инициализации структуры TERMINAL
#define TERMINAL_DEFAULTS {{0},{0},{0},{0},{0},\
		0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0, 0,0,0,0, 0,0,\
		(void (*)(long))TERMINAL_Init,\
		(void (*)(long))TERMINAL_Slow_Calc,\
		(void (*)(long))TERMINAL_1ms_Calc,\
        (void (*)(long))TERMINAL_FastCalc};

//Прототипы функций модуля TERMINAL
void TERMINAL_Init();
 void TERMINAL_Slow_Calc();
void TERMINAL_1ms_Calc();
void TERMINAL_FastCalc();
int usart_receive_char_terminal();
int usart_transmit_char_terminal(int c);

#endif
