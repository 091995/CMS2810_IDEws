/*
 * Terminal.c
 *
 *  Created on: 05.12.2013
 *      Author: 1
 */

/*****************************************************************************/
/* Модуль связи с HMI Delta - Terminal по Modbus */
/* Разработал Дроздов А.В. */
/*****************************************************************************/
//#include "altera_avalon_pio_regs.h"
//#include "system.h"
#include "RS_Terminal.h"
#include "CRC.h"
//#include "dcs_func.h"

#include "DSP.h"
#include "main.h"

#define 	CMDRA_RRES_FIFO
#define 	CMDRA_XRES_FIFO

#define	_SET_RS485_TX_MODE if (mode_Tx_nRx_mode==0) mode_Tx_nRx_mode=1;
#define	_SET_RS485_RX_MODE if (mode_Tx_nRx_mode==1) mode_Tx_nRx_mode=0;
#define _SET_RS485_DIR set_TX_nRX_dir(mode_Tx_nRx_mode);

//unsigned short term_cmd_start_prev=0;
//unsigned short term_cmd_stop_prev=0;
//unsigned short term_cmd_trip_reset_prev=0;



//extern M_LOG m_log;

int _start_addr_read;
int _start_addr_write1;
int _start_addr_write2;
volatile int mode_Tx_nRx_mode;

void set_TX_nRX_dir(int dir)
{
	if (dir) {
		NT_GPIOG->MASKHIGHBYTE_bit[(1<<(8-8))].MASKHB=(1<<(8-8)); //tx ena
		NT_GPIOG->MASKHIGHBYTE_bit[(1<<(14-8))].MASKHB=(1<<(14-8)); //rx dis
	}else
	{
		NT_GPIOG->MASKHIGHBYTE_bit[(1<<(8-8))].MASKHB=0; //tx ena
		NT_GPIOG->MASKHIGHBYTE_bit[(1<<(14-8))].MASKHB=0; //rx dis
	}
}

//Частота тактирования блока UART (настраивается в инициализации микроконтроллера)
#define UART_CLOCK_FREQ 25000000


//Функция инициализации модуля связи с terminal
void TERMINAL_Init()
{
	Uint32 BaudRate;
	terminal.slow_state=0;
	terminal.state=0;
	terminal.state_prev=-1;
	terminal.slow_state_prev=-1;
	mode_Tx_nRx_mode=0;

	//G8tx_ena -  G14rx_dis
	//F11- RX2 F10 TX2

	//Set to GPIO func to control TX|RX dirrection
	NT_GPIOG->ALTFUNCCLR_bit.ALTFUNCCLR = ((1 << 8)|(1<<14));
	NT_GPIOG->OUTENSET_bit.OUTENSET |= ((1 << 8)|(1 << 14));

	NT_COMMON_REG->GPIOPCTLF_bit.PIN10 = 0;
	NT_COMMON_REG->GPIOPCTLF_bit.PIN11 = 0;
	NT_GPIOF->ALTFUNCSET = ((1 << 10)|(1 << 11));




	// Изменить периферийную функцию F12 и F13, чтобы они не заблокировали UART3
//	NT_COMMON_REG->GPIOPCTLF_bit.PIN12 = 1;
//	NT_COMMON_REG->GPIOPCTLF_bit.PIN13 = 1;
//

//	p->MBInternals.NT_UART=NT_UART3;//Используемый в драйвере номер UART (1,2,3)
//
	NT_UART2->CR_bit.UARTEN = 1; 		// Разрешить работу UART

	//Текущая реализация драйвера не использует FIFO, обрабатывает данные по одному байту
	//и вызывается в прерывании 10кГц. Поэтому частоты обмена больше 57600 не поддерживаются (будет терять байты)
//	if (p->BaudRate>57600)
//		p->BaudRate=57600;

	// Настройка частоты в двух регистрах:
	// задание делителя частоты для получения BaudRate
	// Т.к. блок UART тактируется с частотой 25 МГц (так настроено в ините микроконтроллера),
	// то для получения частоты, например, 57600 бит/с необходим
	// делитель 25000000 / (16 * 57600) = 27,126736111111111111111111111111
	// Целая часть I = 27
	// Дробная часть F = (int)( 0.126736111*64 + 0.5 ) = 8
	// Формулы см. в документации
	BaudRate=38400;

	float DivResFloat=(float)UART_CLOCK_FREQ / (16 *BaudRate);
	long DivResInt=(long)DivResFloat;
	long DivResFrac=(int)((DivResFloat-DivResInt)*64 + 0.5);

	NT_UART2->IBRD_bit.BAUD_DIVINT= DivResInt;
	NT_UART2->FBRD_bit.BAUD_DIVFRAC = DivResFrac;

	// 8 бит данных, 1 стоп бит, без контроля четности
	NT_UART2->LCR_H_bit.SPS = 0;		// Нет проверки четности
	NT_UART2->LCR_H_bit.WLEN = 3;		// Длина посылки 8 бит
	NT_UART2->LCR_H_bit.FEN = 0;		// Не использовать FIFO
	NT_UART2->CR_bit.TXE = 1;			// Разрешить приём
	NT_UART2->CR_bit.RXE = 1;			// Разрешить передачу
	NT_UART2->LCR_H_bit.STP2 = 0;		// 1 стоп-бит

}


static short NeedForSave_prev=0;
void TERMINAL_Slow_Calc() {


	if ((terminal.NeedForSave==1)&&(NeedForSave_prev==0)) //чтобы только один раз. Пока кнопку не отпустят сохранять не будет
	{
		//сохраняем посредством драйвера CANopen (все его параметры)
		//вызывая функцию сохранения с разными диапазонами, перебирая их все.
		//co_ODexpositor_paramConservation(&co2_vars, 1, 1); //teminal.save_progress=5;
		//co_ODexpositor_paramConservation(&co2_vars, 2, 1); //teminal.save_progress=10;
		//co_ODexpositor_paramConservation(&co2_vars, 3, 1); //teminal.save_progress=15;
		//co_ODexpositor_paramConservation(&co2_vars, 1, 2); //teminal.save_progress=20;
		//co_ODexpositor_paramConservation(&co2_vars, 2, 2); //teminal.save_progress=25;
		//co_ODexpositor_paramConservation(&co2_vars, 3, 2); //teminal.save_progress=30;
		//Andrei - сохраняем только rw параметры
		co_ODexpositor_paramConservation(&co2_vars, 1, 3); //teminal.save_progress=35;
		//co_ODexpositor_paramConservation(&co2_vars, 2, 3); //teminal.save_progress=40;
		//co_ODexpositor_paramConservation(&co2_vars, 3, 3); //teminal.save_progress=45;
		co_ODexpositor_paramConservation(&co2_vars, 1, 4); //teminal.save_progress=50;
		//co_ODexpositor_paramConservation(&co2_vars, 2, 4); //teminal.save_progress=55;
		//co_ODexpositor_paramConservation(&co2_vars, 3, 4); //teminal.save_progress=60;
		co_ODexpositor_paramConservation(&co2_vars, 1, 5); //teminal.save_progress=65;
		//co_ODexpositor_paramConservation(&co2_vars, 2, 5); //teminal.save_progress=70;
		//co_ODexpositor_paramConservation(&co2_vars, 3, 5); //teminal.save_progress=75;
		//teminal.save_progress=100; TODO103 - прогресс сохранния в процентах
	}


NeedForSave_prev=terminal.NeedForSave;




}


//Функция распаковки и отсылки данных в terminal (внешняя)

void TERMINAL_1ms_Calc()
{
unsigned short crc16calc;
unsigned short crc16recv;
int ii;

//when terminal.flag_error_read==1 means that unswer was wrong - this is a bug in SW architecture here
//to handle ii use direct cmd to go to TERMINAL_IDLE,
//overwise SW hangs

if (terminal.flag_error_read==1) terminal.slow_state=TERMINAL_IDLE;

if (terminal.slow_state_prev!=terminal.slow_state) terminal.slow_E=1;
else terminal.slow_E=0;
terminal.slow_state_prev=terminal.slow_state;


switch (terminal.slow_state)
{
case TERMINAL_IDLE:									//пауза между посылками

	terminal.flag_error_read = 0;

    if (terminal.slow_E==1)
    {
    //link на отправку
    terminal.link_cnt_send++;
    if (terminal.link_cnt_send >= 4)
    {
    	 if (terminal.word_out[0] == 0) terminal.word_out[0] = 1;
    	 else terminal.word_out[0] = 0;
    	 terminal.link_cnt_send = 0;
    }

    }
    //you may change addresses here
   	_start_addr_read = START_ADDR_READ_bl1;
   	_start_addr_write1 = START_ADDR_WRITE1_bl1;
   	_start_addr_write2 = START_ADDR_WRITE2_bl1;

    //terminal.word_out[0] = terminal.active_flag; //  on terminal  0 - is blinking led

	terminal.word_out[1] = _IQmpy(adc.I_diesel,inv_params.I_nom)>>16;
	terminal.word_out[2] = _IQmpy(adc.P_diesel,inv_params.Pdc_nom)>>16;
	terminal.word_out[3] = diesel.ON;
	terminal.word_out[4] = _IQmpy(diesel.P_ref,inv_params.P_nom)>>16;
	terminal.word_out[5] = _IQmpy(cmd_logic.refs.P_dcdc_ref<<16,inv_params._1_P_nom)>>16;
	terminal.word_out[6] = dcdc.status;
	terminal.word_out[7] = dcdc.operating;

	//время запитки часы, потом минуты
	terminal.word_out[8] = global_time.PowerOn_time_min/60;
	terminal.word_out[9] = global_time.PowerOn_time_min%60;
	//время работы
	terminal.word_out[10] = global_time.operational_time_min/60;
	terminal.word_out[11] = global_time.operational_time_min%60;

   	terminal.word_out[30] = apl.protect_Code;

   	terminal.word_out[31] = apl.alarm_Code;
   	terminal.word_out[32] =  inv.status;

	terminal.word_out[33]= _IQmag(cur_par.Pac,cur_par.Qac)>>16;

	terminal.word_out[34]=dio_protect.bit_fault1;//free
	terminal.word_out[35]=dio_protect.bit_alarm1;//busy
	terminal.word_out[36]=dcs_prot.bit_fault1;//busy

	terminal.word_out[37] = sc_profile.profile;
	terminal.word_out[38] = sm_grid_evng_batt_diesel.autostart;
	terminal.word_out[39] = sm_grid_night_batt_charge.autostart;

   	terminal.word_out[40] = _IQmpy(cur_par.Pdc,inv_params.Pdc_nom)>>16;
   	terminal.word_out[41] = _IQmpy(adc.Udc,inv_params.Udc_nom)>>16;
   	terminal.word_out[42] = _IQmpy(adc.Idc,inv_params.I_nom)>>16;
   	terminal.word_out[43] = (int16) can_io.Riso;

   	//ToDo scale to terminal values
    terminal.word_out[50]=_IQmpy(adc.rms.Uab_tr,inv_params.U_nom)>>16;
    terminal.word_out[51]=_IQmpy(adc.rms.Ubc_tr,inv_params.U_nom)>>16;
    terminal.word_out[52]=_IQmpy(adc.rms.Uca_tr,inv_params.U_nom)>>16;

	terminal.word_out[53]=_IQmpy(adc.rms.Ia_tr,inv_params.I_nom)>>16;
	terminal.word_out[54]=_IQmpy(adc.rms.Ib_tr,inv_params.I_nom)>>16;
	terminal.word_out[55]=_IQmpy(adc.rms.Ic_tr,inv_params.I_nom)>>16;

    terminal.word_out[56]=_IQmpy(pll.Um1,inv_params.U_nom)>>16;
    terminal.word_out[57]=_IQmpy(pll.Um2,inv_params.U_nom)>>16;

    terminal.word_out[58]=apl.state; //ToDo need change to сбои сетевого питания

	terminal.word_out[60]=_IQmpy(adc.rms.Uab_inv,inv_params.U_nom)>>16;
	terminal.word_out[61]=_IQmpy(adc.rms.Ubc_inv,inv_params.U_nom)>>16;
	terminal.word_out[62]=_IQmpy(adc.rms.Uca_inv,inv_params.U_nom)>>16;

	terminal.word_out[63]=_IQmpy(adc.rms.Ia_inv,inv_params.I_nom)>>16;
	terminal.word_out[64]=_IQmpy(adc.rms.Ib_inv,inv_params.I_nom)>>16;
	terminal.word_out[65]=_IQmpy(adc.rms.Ic_inv,inv_params.I_nom)>>16;


	terminal.word_out[66]=_IQmpy(cur_par.Pac,inv_params.P_nom)>>16; //ToDo cahnge to cur_par values
	terminal.word_out[67]= _IQmpy(cur_par.Qac,inv_params.P_nom)>>16;

	terminal.word_out[68]=adc.T3>>4;
	terminal.word_out[69]=adc.T4>>4;

	terminal.word_out[70] = _IQmpy(cur_par.S,inv_params.P_nom)>>16;
	terminal.word_out[71] = _IQmpy(adc.Udc,inv_params.Udc_nom)>>16;// _IQmpy(cur_par.S,inv_params.P_nom)>>16;
	terminal.word_out[72] = cur_par.cos_fi>>16;
	terminal.word_out[73] = _IQmpy(adc.Edc_day,inv_params.Pdc_nom)>>16;
	terminal.word_out[74] = cur_par.operating_time>>16;
	terminal.word_out[75] = (int16) adc.Edc_total;
	terminal.word_out[76] = _IQmpy(cur_par.Freq,inv_params.freq_nom)>>8;
	terminal.word_out[77] = adc.T1_inv1>>4;
	terminal.word_out[78] = adc.T2_inv1>>4;
	terminal.word_out[79] = adc.T3_inv1>>4;





//    terminal.word_out[59]=regs.ext_adc.adc_T1;
//    terminal.word_out[60]=regs.ext_adc.adc_T2;


    //for (ii=0;ii<60;ii++)
    //terminal.word_out[1]++;

	terminal.slow_state= TERMINAL_READ_REQ;
	break;

case TERMINAL_READ_REQ:
    if (terminal.slow_E==1)
    {
    	terminal.out_buff[0]=0x01;  				// TERMINAL ADDR
    	terminal.out_buff[1]=CMD_REGREAD; 			// CMD
    	terminal.out_buff[2]=0x00; 					// ADDR
    	terminal.out_buff[3]=_start_addr_read; 		// ADDR
    	terminal.out_buff[4]=0x00; 					// NUM
    	terminal.out_buff[5]=NUMBER_REGS_FOR_READ; 	// NUM
    	crc16calc=usCRC16(terminal.out_buff,6);
    	terminal.out_buff[6]=(crc16calc&0xff);
    	terminal.out_buff[7]=((crc16calc>>8)&0xff);	//CRC команды read (Modbus funct)

    	//mylog.crc_fail_cnt[2]=crc16calc;

    	terminal.out_buff_state=BUFF_READY;
    	terminal.inp_buff_state=BUFF_READY;
    	terminal.state=STATE_WAIT_BUFF_FOR_READ_REQ;
    }
    /*ждем когда автомат закончит выполнение -
    или свалится в состояние готов - тогда разбираем посылку, или
    в состояние аварии  тогда все с начала*/
 	if (terminal.state==STATE_READY)								//STATE_READY - в in_buf пришли данные
	{
 		terminal.count_pause = 0;
 		if (terminal.inp_buff[1] == CMD_REGREAD)
 		{
 			crc16calc=usCRC16(terminal.inp_buff,NUMBER_REGS_FOR_READ*2+3);
 			crc16recv=((unsigned short)terminal.inp_buff[NUMBER_REGS_FOR_READ*2+3]&0xff)+\
	          ((unsigned short)(terminal.inp_buff[NUMBER_REGS_FOR_READ*2+4]&0xff)<<8);
 			if (crc16calc!=crc16recv)
 			{
 				terminal.slow_state=TERMINAL_IDLE;
 				terminal.crc_fail_counter++;
 			}
 			else
 			{
 				//данные получены правильно, можно разводить по массивам
 				for (ii=0;ii<NUMBER_REGS_FOR_READ;ii++)
 					terminal.word_in[ii]=(terminal.inp_buff[ii*2+3]<<8)+terminal.inp_buff[ii*2+4]; //выбираем из пришедших 100 однобайт. (short) регистра нужные

 				terminal.data_in_ready=1;
 				terminal.slow_state = TERMINAL_WRITE_REQ;//TERMINAL_IDLE;//
 			}
 		}
 		else terminal.flag_error_read = 1;
 	}
 	else
 	{
 		terminal.count_pause++;
 		if (terminal.count_pause >= 10000) {
 			terminal.count_pause = 10010;
 		}
 	}
	if (terminal.state==STATE_OPERATION_FAILED)
	{
		terminal.slow_state=TERMINAL_IDLE;
	}

break;

case TERMINAL_WRITE_REQ:
{
    if (terminal.slow_E==1) //ПОСТАВИТЬ ФЛАГ ВНУТРЕННЕЙ ГОТОВНОСТИ ДАННЫХ!!!
    {
    	terminal.out_buff[0]=0x01;  					//TERMINAL ADDR
    	terminal.out_buff[1]=CMD_MREGWRITE; 			// CMD
    	terminal.out_buff[2]=((_start_addr_write1>>8)&0xff); // ADDR 			 //Команда Write
    	terminal.out_buff[3]=(_start_addr_write1&0xff); 		// ADDR
    	terminal.out_buff[4]=0x00; 					// NUM
    	terminal.out_buff[5]=NUMBER_REGS_FOR_WRITE1; 	// NUM
    	terminal.out_buff[6]=NUMBER_REGS_FOR_WRITE1*2; 	// NUM BYTE

    	//собираем данные

    	for (ii=0;ii<NUMBER_REGS_FOR_WRITE1;ii++)
    	{
    		terminal.out_buff[2*ii+7]=((terminal.word_out[ii]>>8)&0xff);
    		terminal.out_buff[2*ii+8]=((terminal.word_out[ii])&0xff);
    	}
		crc16calc=usCRC16(terminal.out_buff,NUMBER_REGS_FOR_WRITE1*2+7);
    	terminal.out_buff[NUMBER_REGS_FOR_WRITE1*2+7]=(crc16calc&0xff);			// размещение своей CRC
    	terminal.out_buff[NUMBER_REGS_FOR_WRITE1*2+8]=((crc16calc>>8)&0xff);
    	terminal.out_buff_state=BUFF_READY;
    	terminal.inp_buff_state=BUFF_READY;
    	terminal.state=STATE_WAIT_BUFF_FOR_WRITE_REQ;
    }
    /*ждем когда автомат закончит выполнение -
    или свалится в состояние готов - тогда разбираем посылку, или
    в состояние аварии  тогда все с начала*/
	if (terminal.state==STATE_READY)
	{
		//terminal.count_pause = 0;
		if (terminal.inp_buff[1] == CMD_MREGWRITE)
		{
			crc16calc=usCRC16(terminal.inp_buff,6);							// CRC зарезервированной формы ответа на write
			crc16recv=((unsigned short)terminal.inp_buff[6]&0xff)+\
				((unsigned short)(terminal.inp_buff[7]&0xff)<<8);
			if (crc16calc!=crc16recv)
			{
				terminal.slow_state=TERMINAL_IDLE;
				terminal.crc_fail_counter++;
			}
			else
			{
				//ответ о том что данные записаны правильный
				//проверим только код
				if (terminal.inp_buff[1]!=0x10)
				{
					terminal.crc_fail_counter++;
					terminal.flag_error_read = 1;
				}
				//можно переходить к процедуре чтения
				//данных с терминала
				terminal.slow_state=TERMINAL_IDLE;
				//terminal.slow_state=TERMINAL_WRITE2_REQ;
			}
		}
		else terminal.flag_error_read = 1;
	}
	else terminal.count_pause++;

	if (terminal.state==STATE_OPERATION_FAILED)
		terminal.slow_state=TERMINAL_IDLE;
    break;
}
//вторую посылку в terminal не используем
case TERMINAL_WRITE2_REQ:
{
    if (terminal.slow_E==1)
    {
    	terminal.out_buff[0]=0x01;  						//TERMINAL ADDR
    	terminal.out_buff[1]=CMD_MREGWRITE; 				// CMD
    	terminal.out_buff[2]=((_start_addr_write2>>8)&0xff); // ADDR
    	terminal.out_buff[3]=(_start_addr_write2&0xff); 		// ADDR
    	terminal.out_buff[4]=0x00; 							// NUM
    	terminal.out_buff[5]=NUMBER_REGS_FOR_WRITE2; 		// NUM
    	terminal.out_buff[6]=NUMBER_REGS_FOR_WRITE2*2; 		// NUM BYTE

    	for (ii=0;ii<NUMBER_REGS_FOR_WRITE2;ii++)
    	{
    		terminal.out_buff[2*ii+7]=((terminal.word_out2[ii]>>8)&0xff);
    		terminal.out_buff[2*ii+8]=((terminal.word_out2[ii])&0xff);
    	}
    	crc16calc=usCRC16(terminal.out_buff,NUMBER_REGS_FOR_WRITE2*2+7);
    	terminal.out_buff[NUMBER_REGS_FOR_WRITE2*2+7]=(crc16calc&0xff);
    	terminal.out_buff[NUMBER_REGS_FOR_WRITE2*2+8]=((crc16calc>>8)&0xff);
    	terminal.out_buff_state=BUFF_READY;
    	terminal.inp_buff_state=BUFF_READY;
    	terminal.state=STATE_WAIT_BUFF_FOR_WRITE_REQ;
    }
    /*ждем когда автомат закончит выполнение -
    или свалится в состояние готов - тогда разбираем посылку, или
    в состояние аварии  тогда все с начала*/
	if (terminal.state==STATE_READY)
	{
		terminal.count_pause = 0;
		if (terminal.inp_buff[1] == CMD_MREGWRITE)
		{
			crc16calc=usCRC16(terminal.inp_buff,6);
			crc16recv=((unsigned short)terminal.inp_buff[6]&0xff)+\
	          ((unsigned short)(terminal.inp_buff[7]&0xff)<<8);
			if (crc16calc!=crc16recv)
			{
				terminal.slow_state=TERMINAL_IDLE;
				terminal.crc_fail_counter++;
			}
			else
			{
				//ответ о том что данные записаны правильный
				//проверим только код
				if (terminal.inp_buff[1]!=0x10)
				{
					terminal.crc_fail_counter++;
					terminal.flag_error_read = 1;
				}
				//можно переходить к процедуре чтения
				//данных с терминала
				terminal.slow_state=TERMINAL_IDLE;

			}
		}
		else terminal.flag_error_read = 1;
	}
	else terminal.count_pause++;

	if (terminal.state==STATE_OPERATION_FAILED)
		terminal.slow_state=TERMINAL_IDLE;
    break;
}

default:break;
}

terminal.ms_counter++;

}
int word_in_7_prev=0;
void TERMINAL_FastCalc()
{/* очень быстрый дискретный автомат, который только принимает
или выдвигает данные в зависимости от состояния. Все буферы собираются и
разбираются в фоновом кольце. Они только сообщают о своем состоянии*/
Uint32 temp_u32;

//mode_Tx_nRx_mode=1;
//_SET_RS485_DIR;
//usart_transmit_char_terminal(0xA5);
//return;
//здесь (и только здесь) можно приравнять данные к внутреним переменным
if (terminal.data_in_ready==1)
{
	//source
	cmd_logic.local_cmd.bit.cmd_pow_on=((terminal.word_in[0]>>0)&0x1);
	cmd_logic.local_cmd.bit.cmd_pow_off=((terminal.word_in[0]>>1)&0x1);
	cmd_logic.local_cmd.bit.cmd_trip_reset=((terminal.word_in[0]>>2)&0x1);
	cmd_logic.local_cmd.bit.cmd_pulses_on=((terminal.word_in[0]>>3)&0x1);
	cmd_logic.local_cmd.bit.cmd_pulses_off=((terminal.word_in[0]>>4)&0x1);
	diesel.cmd_in_on=((terminal.word_in[0]>>5)&0x1);
	diesel.cmd_in_off=((terminal.word_in[0]>>6)&0x1);

	if(((terminal.word_in[0]>>7)&0x1)&&dcdc.ena==0)
		dcdc.ena=1;
	if(((terminal.word_in[0]>>8)&0x1)&&dcdc.ena==1)
		dcdc.ena=0;

	terminal.NeedForSave = ((terminal.word_in[0]>>15)&0x1); //самый старший бит

	if(((terminal.word_in[0]>>9)*0x1))
	{
	sm_grid_evng_batt_diesel.autostart=1;
	sm_grid_night_batt_charge.autostart=1;
	}
	if(((terminal.word_in[0]>>10)*0x1))
	{
	sm_grid_evng_batt_diesel.autostart=0;
	sm_grid_night_batt_charge.autostart=0;
	}


	sc_profile.in.cmd_local_set_profile = terminal.word_in[3];

	//прием нажатий от кнопок калибровоки измерений
	adc.sUbc_tr.calibration.more = terminal.word_in[4]&0x1;
	adc.sUbc_tr.calibration.less = terminal.word_in[4]&0x2;
	adc.sUbc_inv.calibration.more = terminal.word_in[4]&0x4;
	adc.sUbc_inv.calibration.less = terminal.word_in[4]&0x8;
	adc.sIa_tr.calibration.more = terminal.word_in[4]&0x10;
	adc.sIa_tr.calibration.less = terminal.word_in[4]&0x20;
	adc.sIb_tr.calibration.more = terminal.word_in[4]&0x40;
	adc.sIb_tr.calibration.less = terminal.word_in[4]&0x80;
	adc.sIc_tr.calibration.more = terminal.word_in[4]&0x100;
	adc.sIc_tr.calibration.less = terminal.word_in[4]&0x200;
	adc.sIa_inv.calibration.more = terminal.word_in[4]&0x400;
	adc.sIa_inv.calibration.less = terminal.word_in[4]&0x800;
	adc.sIb_inv.calibration.more = terminal.word_in[4]&0x1000;
	adc.sIb_inv.calibration.less = terminal.word_in[4]&0x2000;
	adc.sIc_inv.calibration.more = terminal.word_in[4]&0x4000;
	adc.sIc_inv.calibration.less = terminal.word_in[4]&0x8000;

//	diesel.P_ref+=_IQ16(terminal.word_in[5]);
//	cmd_logic.remote_refs.P_dcdc_ref+=_IQ8(terminal.word_in[6]);
//	cmd_logic.cmd_refs_local.cmd_set_mode_test = ((terminal.word_in[0]>>8)&0x1);
//	cmd_logic.cmd_refs_local.cmd_set_mode_auto = ((terminal.word_in[0]>>9)&0x1);
//
//
//	dcs.test_mode	=terminal.word_in[1];
//	dcs.test_param1	=terminal.word_in[2];
//	dcs.test_param2	=terminal.word_in[3];
//
//	dio_logic.test_cmd.DO1	= (terminal.word_in[4]>>1)&0x1;
//	dio_logic.test_cmd.DO2	= (terminal.word_in[4]>>2)&0x1;
//	dio_logic.test_cmd.DO3	= (terminal.word_in[4]>>3)&0x1;
//	dio_logic.test_cmd.DO4	= (terminal.word_in[4]>>4)&0x1;


	//temp_u32=(alt_u32)((terminal.word_in[4]<<16)+terminal.word_in[5]);
	//cmd_logic.cmd_refs.Udc2= *(float*)(&temp_u32);


//
//	//Link check
//	terminal.link=terminal.word_in[9]&TERMINAL_LINK_MASK;
//	if(terminal.link!=terminal.link_prev)
//	{
//		terminal.link_cnt=0;
//		terminal.link_OK=LINK;
//		protect.prot_word[1]&=(!P_TERMINAL_NO_LINK);
//	}
//	else terminal.link_cnt++;
//	if (terminal.link_cnt>=30)
//	{
//		terminal.link_OK =NO_LINK;
//		protect.prot_word[1]|=P_TERMINAL_NO_LINK;
//		terminal.link_cnt = 30;
//	}
//	terminal.link_prev=terminal.link;

	//after copy clear data_in_ready flag
	terminal.data_in_ready=0;
}



if (terminal.state_prev!=terminal.state)
	terminal.E=1;
else
	terminal.E=0;
terminal.state_prev=terminal.state;

switch (terminal.state)
{

case STATE_READY: // ждем готовности буфер

	_SET_RS485_RX_MODE;
	usart_receive_char_terminal();
	break;

case STATE_OPERATION_FAILED: // ждем готовности буфер
	_SET_RS485_RX_MODE;
	usart_receive_char_terminal();
	break;

case STATE_WAIT_BUFF_FOR_READ_REQ: // ждем готовности буфер
    if (terminal.E==1) terminal.ms_counter=0;
    usart_receive_char_terminal();
    	if ((terminal.out_buff_state==BUFF_READY)&&\
    	(terminal.inp_buff_state==BUFF_READY)&&\
    	//(terminal.ms_counter>20))
    	(terminal.ms_counter>30))
    		 terminal.state = STATE_TRANSMIT_BUFF_FOR_READ_REQ;  //прождали 20 прерываний после упаковки read_request
break;

case STATE_TRANSMIT_BUFF_FOR_READ_REQ:  //отправляем READ_REQ
     if (terminal.E==1)
     	{	_SET_RS485_TX_MODE;
    	 	CMDRA_RRES_FIFO;
     		CMDRA_XRES_FIFO;
     		terminal.counter=0;
     		terminal.ms_counter=0;
     		break;
     	}
        if (usart_transmit_char_terminal(terminal.out_buff[terminal.counter])==0x100)
        {	// если сразу отправить не удалось...
        	if (terminal.ms_counter<6) break; //terminal.counter==0) break; //попробуем отправить позже.
       	 	else         //но если уже начали отправлять и не смогли отправить, то
        	{            //фиксируем ошибку
       	 		terminal.state = STATE_OPERATION_FAILED;
       	 		terminal.send_req_error++;
        	break;
        	}
        } else terminal.ms_counter=0;

        terminal.counter++;
        if (terminal.counter==8)
        {
        	terminal.state = STATE_WAIT_REQUESTED_BUFF;
        	terminal.out_buff_state=BUFF_EMPTY;
        	terminal.ms_counter=0;
		}
		break;

case STATE_WAIT_REQUESTED_BUFF:
     if (terminal.E==1)
     	{
    	 	terminal.counter=0;
    	 	terminal.ms_counter=0;
    	 	terminal.TX_nRX_dir_counter=0;
    	}
     	// trick to wait some time all TX data goes out
        if (terminal.TX_nRX_dir_counter<3) {terminal.TX_nRX_dir_counter++;usart_receive_char_terminal(); break;}
        else _SET_RS485_RX_MODE;

     	 if ((terminal.ms_counter>15*50)|| //150 ms
     	((terminal.counter!=0)&&(terminal.ms_counter>50)))    //(200мкс*20=4мс) между чарами (байтами rx)
     	{
     		terminal.state = STATE_OPERATION_FAILED;
     		terminal.read_req_error++;
      	}

        terminal.recv=usart_receive_char_terminal();

        if (terminal.recv==0x101)  //было 0х101
        {
        	terminal.read_req_error++;
        	terminal.state = STATE_OPERATION_FAILED;
        	break;
        }
        if ((terminal.recv&0x100)==0)
        {	/*если успешно приняли данное
        	сбрасываем счетчик чтобы не попасть в аварию*/
        	terminal.ms_counter=0;
        	/* terminal.no_link_cnt=0;
        	set.terminal_NLF=LINK;*/
        	/*записываем данное*/
        	terminal.inp_buff[terminal.counter]=terminal.recv;
        	terminal.counter++;
        }

        if (terminal.counter==(NUMBER_REGS_FOR_READ*2+5))
        {
        	terminal.state = STATE_READY;
		}


		break;

//******************WRITE**************************
case STATE_WAIT_BUFF_FOR_WRITE_REQ:
    if (terminal.E==1)
     	{
     		terminal.ms_counter=0;
     	}
     	terminal.counter++;
 	if ((terminal.out_buff_state==BUFF_READY)&&\
    	(terminal.inp_buff_state==BUFF_READY)&&\
    	//(terminal.ms_counter>20))
    	(terminal.ms_counter>30))
 		terminal.state = STATE_TRANSMIT_BUFF_FOR_WRITE_REQ;
    break;

case STATE_TRANSMIT_BUFF_FOR_WRITE_REQ:
     if (terminal.E==1)
     	{	_SET_RS485_TX_MODE;
    	 	 CMDRA_RRES_FIFO;
    	 	 CMDRA_XRES_FIFO;
    	 	 terminal.counter=0;
    	 	 terminal.ms_counter=0;
    	 	 break;
     	}
        if (usart_transmit_char_terminal(terminal.out_buff[terminal.counter])==0x100)
        {	//если сразу отправить не удалось...
        	if (terminal.ms_counter<6) break; //terminal.counter==0) break; //попробуем отправить позже.
       	 	else         //но если уже начали отправлять и не смогли отпаравить, то
        	{            //фиксируем ошибку
       	 		terminal.state = STATE_OPERATION_FAILED;
       	 		terminal.send_req_error++;
       	 		break;
        	}
        } else terminal.ms_counter=0;

        terminal.counter++;
        if (terminal.counter==(NUMBER_REGS_FOR_WRITE1*2+9))
        {
        	terminal.state = STATE_WAIT_UNSWER;
        	terminal.out_buff_state=BUFF_EMPTY;
        	terminal.ms_counter=0;
		}
		break;

case STATE_WAIT_UNSWER:
     if (terminal.E==1)
     	{	 terminal.counter=0;
    	 	 terminal.ms_counter=0;
    	 	terminal.TX_nRX_dir_counter=0;
     	}

  	// trick to wait some time all TX data goes out
     if (terminal.TX_nRX_dir_counter<3) {terminal.TX_nRX_dir_counter++;usart_receive_char_terminal(); break;}
     else _SET_RS485_RX_MODE;


     	if ((terminal.ms_counter>15*5)||
     	((terminal.counter!=0)&&(terminal.ms_counter>20)))    //(200мкс*20=4мс) между чарами
     	{
     		terminal.state = STATE_OPERATION_FAILED;
     		terminal.read_req_error++;
        }

        terminal.recv=usart_receive_char_terminal();

        if (terminal.recv==0x101)
        {
        	terminal.read_req_error++;
        	terminal.state = STATE_OPERATION_FAILED;
        break;
        }
        if ((terminal.recv&0x100)==0)
        {	/*если успешно приняли данное
        	сбрасываем счетчик чтобы не попасть в аварию*/
        	terminal.ms_counter=0;
        	/*записываем данное*/
        	terminal.inp_buff[terminal.counter]=terminal.recv;
        	terminal.counter++;
        }

        if (terminal.counter==8)
        {
        	terminal.state = STATE_READY;
		}
		break;


default: break;
} /*end switch*/

//mode_Tx_nRx_mode
set_TX_nRX_dir(mode_Tx_nRx_mode);
//_SET_RS485_DIR;

}

//Функция приема байта посылки из регистра uart_rx
int usart_receive_char_terminal()
{
  int c;
  volatile int rd_status_uart;

  rd_status_uart = NT_UART2->FR_bit.RXFE;  // read status 1= no data in buffer
  //rd_status_uart &= 0x00000080; // only bit RRDY - receiver empty
  if(rd_status_uart == 0)
  {
	   c= NT_UART2->DR; // read
  }
  else return 0x100;		// not ready
  return c;
}
//void  ModBus_ResetError(TModBus *p)
//{
//	// Биты 0-3 - биты ошибок, сбрасываются записью в них "1"
//	p->MBInternals.NT_UART->RSR_ECR |= 0x000F;
//}
//
//int16 ModBus_CheckDataReady(TModBus *p)
//{
//	// return 1 - если буфер приёмника не пуст
//	return (!p->MBInternals.NT_UART->FR_bit.RXFE);
//}
//
//int16  ModBus_CheckTxEmpty(TModBus *p) //Если все отправлено (пуст и основной и теневой регистры)
//{
//	// return 1 - если буфер передатчика пуст
//	return (p->MBInternals.NT_UART->FR_bit.TXFE);
//}
//
//int16  ModBus_CheckTxReady(TModBus *p) //В передатчик можно положить следующий символ (буфер свободен)
//{
//	// "1" - если буфер передатчика пуст
//	return (p->MBInternals.NT_UART->FR_bit.TXFE);
//}
//
//void  ModBus_Tx(TModBus *p, int16 data)  // Передача данных
//{
//	Uint8 tmp_data = data;
//	p->MBInternals.NT_UART->DR_bit.DATA = tmp_data;
//}
//Функция отправки байта посылки в регистр uart_tx
int usart_transmit_char_terminal(int c) //c - terminal.tx_message[i]
{
  volatile int rd_status_uart;


  rd_status_uart=NT_UART2->FR_bit.TXFE;  // read status
 // rd_status_uart &= 0x00000040; // only bit TRDY - transmit ready
  if(rd_status_uart == 1)
	  NT_UART2->DR_bit.DATA= c; 	// write to transmitter UART
  else return 0x100;	// not ready
  return 0;
}
