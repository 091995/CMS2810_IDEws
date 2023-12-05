/*!
    Copyright 2019 	A&D

 \file      main.c
 \brief     Главный файл проекта. Содержит main(), а также обработчики прерываний.
 \author    A&D
 \version   v 1.0 09/06/2019

 */

#include "main.h"
#include <string.h> //для memcpy

void InitCLK(void);

//HAL_ADC HAL_adc;
HAL_ENERGY19 HAL;

TClarke clarke = CLARKE_DEFAULTS;
TPark park = PARK_DEFAULTS;
TIPark ipark = IPARK_DEFAULTS;
TPidReg3 pid_id = PIDREG3_DEFAULTS;
TPidReg3 pid_iq = PIDREG3_DEFAULTS;
TPidReg3 pid_ud = PIDREG3_DEFAULTS;
TPidReg3 pid_uq = PIDREG3_DEFAULTS;
TPidReg3 pid_Udc= PIDREG3_DEFAULTS;

TMeanFilter fmIdc = MEAN_FILTER_DEFAULTS;
TMeanFilter fmUdc = MEAN_FILTER_DEFAULTS;

TMPPT mppt = MPPT_DEFAULTS;
FREQMETER freqmeter = FREQMETER_DEFAULTS;
PLL pll = PLL_DEFAULTS;
TDCS_Protect dcs_prot = DCS_PROTECT_DEFAULTS;

TRMPCtrl rmp = V_RMP_CTRL_DEFAULTS;
TRMPCtrl rmp_pow = V_RMP_CTRL_DEFAULTS;
TAdcDrv adc = ADC_DRV_DEFAULTS;
TTEMPSENSOR_NTC temp_NTC10K = TEMPSENSOR_NTC_10K_DEFAULTS;
TTEMPSENSOR_NTC temp_NTC5K = TEMPSENSOR_NTC_5K_DEFAULTS;

TPWM_Module pwm = PWM_Module_DEFAULTS;
TRefs dcs_refs;
TDCS_Ctrl dcs_ctrl = DCS_CTRL_DEFAULTS;
TSim sim = SIM_DEFAULTS;

TCurPar cur_par = TCUR_PAR_DEFAULTS; //!< Модуль расчета и хранения текущих показателей  - мощность, напряжения токи

TGridModel model = GRID_MODEL_DEFAULTS;	//!< Модели сети и солнечных панелей для отладки
TGenerator gen = GENERATOR_DEFAULTS;

//TInvStatus inv_status = { 0 }; //!< Текущий статус привода
TInvParams inv_params; //!< Параметры инвертора

//TRefs refs; //!< Структура с заданиями (токи, скорости)
//TCmd cmd = { 0 }; //!< Структура с командами управления


TFAN_ACTRL  fan_actrl = FAN_ACTRL_DEFAULTS;
TFAN_DCTRL  fan_dctrl = FAN_DCTRL_DEFAULTS;
TFAN_SPEC_RELAY_OUTPUT fan_spec = FAN_SPEC_RELAY_OUTPUT_DEFAULTS;
DIO_LOGIC_INV inv = DIO_LOGIC_INV_DEFAULTS;
DIO_LOGIC dio_logic = DIO_LOGIC_DEFAULTS;
TDIO_PROTECT dio_protect = DIO_PROTECT_DEFAULTS;
CMD_LOGIC cmd_logic = CMD_LOGIC_DEFAULTS;

DIO_AUX_Q copain_aux_QS1  = DIO_AUX_Q_DEFAULTS;
DIO_AUX_Q copain_aux_QS2  = DIO_AUX_Q_DEFAULTS;


DIO_AUX_IO aux_io = DIO_AUX_IO_DEFAULTS;
DIO_AUX_Q aux_Q4 = DIO_AUX_Q_DEFAULTS;		//from DC side only for switch off
DIO_AUX_Q aux_Q26 = DIO_AUX_Q_DEFAULTS;	//from AC side manually by staff
DIO_AUX_Q aux_K7 = DIO_AUX_Q_DEFAULTS;		//from AC side controllable
DIO_AUX_Q aux_K91 = DIO_AUX_Q_DEFAULTS;
DIO_AUX_Q aux_Q6 = DIO_AUX_Q_DEFAULTS;	//special Q6

AUX_CAN_IO can_io;	//info about states of input and output at all 3 can_io modules


DIO_LOGIC_DCDC dcdc = DIO_LOGIC_DCDC_DEFAULTS;

DIO_LOGIC_DIESEL diesel = DIO_LOGIC_DIESEL_DEFAULTS;

DIO_LOGIC_VACUUM vacuum = DIO_LOGIC_VACUUM_DEFAULTS;

SC_PROFILE sc_profile = SC_PROFILE_DEFAULTS;

DIO_EQUIP_CTRL dio_equip = DIO_EQUIP_CTRL_DEFAULTS;


TLEDS leds = TLEDS_DEFAULTS;

APL apl = APL_DEFAULTS;

TSM_Sys sm_sys = SM_Sys_DEFAULTS; //!< Главная оболочка для вызова всех модулей
Uint16 disp_group_number = 0; 	//!< Необходимо для драйвера CANOpen и Unicon
TDataLog dlog = DATALOG_DEFAULTS; //!< Модуль осциллографирования переменных CANOpen
TBitsToEnumNums pult_protect_lister = BITS_TO_ENUM_NUMS_DEFAULTS; //!<Листалка аварий для Unicon
TBitsToEnumNums pult_alarm_lister = BITS_TO_ENUM_NUMS_DEFAULTS; //!<Листалка аварий для Unicon

TSM_Net sm_net = SM_NET_DEFAULTS; 	//!< Оболочка для вызова сетевых драйверов


TUserMemory UserMem = USERMEMORY_DEFAULTS; //!< Модуль работы с энергонезависимой памятью.

TCanBTInterface Can2BTInterface = T_CANBT_INTERFACE_DEFAULTS;//!<Пакетная передача CANopen
TAutoOffset AutoOffset = AUTO_OFFSET_DEFAULTS;	//!<Автоматическая подстройка смещения токов АЦП

TCANtoRS CANtoRS = CAN_TO_RS_DEFAULTS; //!<Модуль для работы с драйвером CANopen через UART (RS). Посылки CAN запаковываются в UART
TModBus ModBus = MODBUS_DEFAULTS; //!<Драйвер для работы по протоколу MODBUS
TMBVarsConv MBVarsConv = MBVARSCONV_DEFAULTS;//!< Модуль преобразования данных из формата 16 разрядов Modbus в формат системы управления (IQ 24)

TDrvInterface drv_interface = DRV_INTERFACE_DEFAULTS;	//!<Интерфейс длЯ работы с банками аварий, событий и т.п.

TLogger FaultLog = LOGGER_DEFAULTS;			//!<Протоколирование аварий
TRTCClock RTCclock = RTC_CLOCK_DEFAULTS; //!< Модуль работы с часами реальноговремени. "spi" - по историческим причинам совместимости
TGlobalTime global_time = GLOBAL_TIME_DEFAULTS; //!<Работа с часами

TERMINAL terminal = TERMINAL_DEFAULTS;


TCANOPEN_MINI can_mini = TCANOPEN_MINI_DEFAULTS;
TInvSync isync = INV_SYNC_DEFAULTS;

TSysSwitches sw; //!< Различные дискретные настройки системы управления
//75855007
Uint32 VendorToken=0x75855007;//1111 1111;//!< Уникальный ключ производителя, нужный для программы UniCON и COODEdit для различных наборов текстов разных произхводителей
//int inv_status_code; //!<Статус системы управления в виде константы (ГОТОВ, РАБОТА и т.п.)


Uint16 Nikita = 12;

//Переменные для отладки - выведены в словарь CANOpen, 
//В них можно присваивать любую другую переменную и наблюдать её
//в UniCon, а также использовать их напрямую в ПО для отладки и менять на ходу.
volatile long Debug1 = 0;
volatile long Debug2 = 0;
volatile Uint16 Debug3 = 0;
volatile Uint16 Debug4 = 0;
volatile long DebugW1 = 0;
volatile long DebugW2 = 0;
volatile long DebugW3 = 0;
volatile long DebugW4 = 0;
volatile float DebugF1 = 0;
volatile float DebugF2 = 0;
volatile float DebugF3 = 0;
volatile float DebugF4 = 0;
Uint16 delimeter_sign=0;


//Счетчики прерываний модуля захвата
Uint16 CounterCAP_isr = 0;
Uint16 cap0_counter = 0;
Uint16 cap1_counter = 0;
Uint16 cap2_counter = 0;

Uint16 LoopCounter = 0; //!< Счетчик итераций фонового цикла

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
int main(void) {


	/* Настройка тактирования, включение периферии */
	InitCLK();
	// Копирование некоторых функций и всех прерываний в RAM
#if defined (__GNUC__)
	memcpy(&__fastcode_ram_start, &__fastcode_flash_start,
			((Uint32) (&__fastcode_ram_end) - (Uint32) (&__fastcode_ram_start)));

	memcpy(&__isr_vector_ram_start, &__isr_vector_flash_start,
			((Uint32) (&__isr_vector_ram_end)
					- (Uint32) (&__isr_vector_ram_start)));
#elif defined (__CMCPPARM__)
	// Для CodeMaster непонятно, как разместить таблицу прерываний во флеше, а обращатся к ней в раме,
	// так что пока так.
#endif


	HAL_init(&HAL);

	pwm.Off(&pwm); //ToDo OK if you wnat to block PWM uses HAL insted, b's it is special init fucntion Commented выключить ШИМ (на всякий случай)

	//Инициализация, собственно, всего.
	//сначала CANOPEN т.к. происходит загрузка параметров


	sm_net.init(&sm_net);
	//потом все модули
	sm_sys.init(&sm_sys);

	//can_mini.can_io[0].o_word=0x1;

	VendorToken=0x75855007;
	EINT;//разрешение прерываний

	//тип и версия устройства для драйвера CANOpen
	co2_vars.co_productCode = 51;
	co2_vars.co_revisionNumber = 1;

	while (1) { //Фоновый цикл
		LoopCounter++;
		sm_sys.slow_calc(&sm_sys); //Фоновый расчет
		sm_net.slow_calc(&sm_net);

		if (dcs_ctrl.state==SM_DCS_CTRL_STOP) leds.toggle(0,500);
		else leds.toggle(0,250);

		if (dcs_prot.state==SM_DCS_PROT_NO_TRIP) leds.toggle(1,500);
		else  leds.toggle(1,100);

		leds.toggle(2,2000);
	}
}







//-------------------------------------------------------------------------------------------------
//        1000Hz interrupt
//-------------------------------------------------------------------------------------------------
unsigned long CpuTimerIsr1 = 0;
Uint16 TIsr1 = 0;
Uint16 msCounter = 0;
int16 btn_press=0;
void TIM1_IRQHandler(void)
{
	CpuTimerIsr1 = NT_TIMER2->VALUE; //Засекается время выполнения функции


	HAL_DIO_read(&HAL.DIO);
	HAL_ms_update();


//	HAL.DIO.FAN2_spd_cmd = fan_dctrl.d_cmd; fignya kakaya-to
//	fan_dctrl.d_fdb=HAL.DIO.DI_6;

//	// this part is for pwm pulses testing using buttons
//	if (dcs_ctrl.state==SM_DCS_CTRL_STOP) {
//	cmd_logic.local_cmd.bit.cmd_pulses_on=HAL.DIO.DI_btn1;
//	cmd_logic.local_cmd.bit.cmd_trip_reset=HAL.DIO.DI_btn2;
//	}
//	else
//	{
//	cmd_logic.local_cmd.bit.cmd_pulses_off=HAL.DIO.DI_btn1;
//	cmd_logic.local_cmd.bit.cmd_trip_reset=HAL.DIO.DI_btn2;
//	}

	DIO_LOGIC_CONNECTORS();


	sm_sys.ms_calc(&sm_sys); //миллисекундный расчет всего
	sm_net.ms_calc(&sm_net);

	HAL.DIO.DO_LED1=leds.led[0].cmd;
	HAL.DIO.DO_LED2=leds.led[1].cmd;
	HAL.DIO.DO_EXT_LED1=  HAL.DIO.DO_2coil; //copy as Isaev asked info about K7 K91 state
	HAL.DIO.DO_EXT_LED2=  HAL.DIO.DO_3coil; //

//TODO my frendly tick tack when alone
 //if (msCounter<3000) HAL.DIO.rel_cmd1=1;
 //else HAL.DIO.rel_cmd1=0;

	//	HAL.DIO.rel_cmd2=0;
//	HAL.DIO.rel_cmd3=0;
//	HAL.DIO.rel_cmd4=0;

// HAL.DIO.rel_cmd1; //B6
// HAL.DIO.rel_cmd2; //B15
// HAL.DIO.rel_cmd3; //B4
// HAL.DIO.rel_cmd4; //B5
// HAL.DIO.FAN_spd_cmd;	//A10
// HAL.DIO.FAN2_spd_cmd;  //G1
//
// HAL.DIO. DO_3coil;   //E11
// HAL.DIO.DO_2coil;   //E15
//
// HAL.DIO.DI_1; //E3
// HAL.DIO.DI_2; //C6
// HAL.DIO. DI_3; //E8
// HAL.DIO.DI_4; //E9
//
// HAL.DIO.DI_6;		//A15
// HAL.DIO. DI_7;		//A14
//
// HAL.DIO.i1_pow1; //
// HAL.DIO.i1_pow2; //
// HAL.DIO.i2_pow1; //
// HAL.DIO.i2_pow2; //
//
// HAL.DIO.DI_btn1;		//D10
// HAL.DIO.DI_btn2;		//D11

 //HAL.DIO.DO_2coil=0;
 //HAL.DIO.DO_3coil=0;
 //HAL.DIO.FAN_spd_cmd=0;
 //HAL.DIO.FAN2_spd_cmd=0;
//if (dcs_ctrl.test_param2==1) HAL.DIO.DO_2coil=1;
// HAL.DIO.DO_2coil=leds.led[2].cmd;
//if (dcs_ctrl.test_param2==2) HAL.DIO.DO_3coil=1;
//if (dcs_ctrl.test_param2==3) {HAL.DIO.DO_2coil=1;HAL.DIO.DO_3coil=1;}
//if (dcs_ctrl.test_param2==4) {HAL.DIO.FAN2_spd_cmd=1;}


	HAL_DIO_write(&HAL.DIO);


	msCounter++;

	TIsr1 = (CpuTimerIsr1 - NT_TIMER2->VALUE) & 0xFFFFFF; //время выполнения функции
	if (TIsr1 > 97000) {
		dcs_prot.bit_fault1 |= F_PROGRAM_10K; //TODO OK move to HAL если расчет слишком долгий, ошибка
	}

	NT_TIMER1->INTSTATUS_INTCLEAR_bit.INT = 1;	//сброс прерывания
}











//-------------------------------------------------------------------------------------------------
//        DCS interrupt
//-------------------------------------------------------------------------------------------------

Uint16 FastCounter = 0;
unsigned long CpuTimerIsr10 = 0;
Uint16 TIsr10 = 0;

//! Прервыние, вызываемое по таймеру с частотой 10кГц NOW IS NOT USED. USE PWM INT
//! \memberof MAIN_C
void TIM0_IRQHandler(void) {
	CpuTimerIsr10 = NT_TIMER2->VALUE; //Засекается время выполнения функции

	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB=(1<<(10-8));

	//HAL_ADC_calc(&HAL.ADC);
	//adc.regs.Ia_inv_reg16=HAL_adc.Ia_inv_reg16;
	//adc.calc(); // normalaise all measurements from regs16 to base units

	//sm_sys.fast_calc(&sm_sys); //расчет 10кГц всего
	//sm_net.fast_calc(&sm_net);//расчет коммуникационных драйверов

	//FastCounter++;
//	TIsr10 = (CpuTimerIsr10 - NT_TIMER2->VALUE) & 0xFFFFFF; //время выполнения функции
//	if (TIsr10 > 9700) {
//		dcs_prot.bit_fault1 |= F_PROGRAM_10K; //TODO OK move to HAL если расчет слишком долгий, ошибка
//	}
	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB = 0;
	NT_TIMER0->INTSTATUS_INTCLEAR_bit.INT = 1;	//сброс прерывания
}


volatile Uint16 ePWM0_isr_counter = 0;

void EPWM_0_IRQHandler(void)
{
	int ii,yy;
	CpuTimerIsr10 = NT_TIMER2->VALUE; //Засекается время выполнения функции

	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB=(1<<(11-8));
	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB=(1<<(10-8));

	ePWM0_isr_counter++;
	FastCounter++;
//	for (ii=0;ii<10;ii++)
//		asm("nop");
	HAL.ADC.irq_id=0;
	HAL_ADC_calc(&HAL.ADC);

	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB = 0;


	DCS_TO_HAL_CONNECTOR();
		sm_sys.fast_calc(&sm_sys); //расчет 10кГц всего
		sm_net.fast_calc(&sm_net);//расчет коммуникационных драйверов

	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB = 0;
	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB=0;
		TIsr10 = (CpuTimerIsr10 - NT_TIMER2->VALUE) & 0xFFFFFF; //время выполнения функции
		if (TIsr10 > 9700) {
			dcs_prot.bit_fault1 |= F_PROGRAM_10K; //TODO OK move to HAL если расчет слишком долгий, ошибка
		}
	NT_PWM0->ETCLR_bit.INT=1;
	NT_PWM0->INTCLR_bit.INT=1;

}

volatile Uint16 ePWM1_isr_counter = 0;
void EPWM_1_IRQHandler(void)
{
	int ii,yy;
	CpuTimerIsr10 = NT_TIMER2->VALUE; //Засекается время выполнения функции

	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB=(1<<(10-8));

	ePWM1_isr_counter++;
	FastCounter++;
//	for (ii=0;ii<10;ii++)
//		asm("nop");
	HAL.ADC.irq_id=1;
	HAL_ADC_calc(&HAL.ADC);
	//NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB = 0;
	DCS_TO_HAL_CONNECTOR();

		sm_sys.fast_calc(&sm_sys); //расчет 10кГц всего
		sm_net.fast_calc(&sm_net);//расчет коммуникационных драйверов

	TIsr10 = (CpuTimerIsr10 - NT_TIMER2->VALUE) & 0xFFFFFF; //время выполнения функции
	if (TIsr10 > 9700) {
		dcs_prot.bit_fault1 |= F_PROGRAM_10K; //TODO OK move to HAL если расчет слишком долгий, ошибка
	}
	NT_PWM1->ETCLR_bit.INT=1;
	NT_PWM1->INTCLR_bit.INT=1;

}


//-------------------------------------------------------------------------------------------------
//        PDP interrupt
//-------------------------------------------------------------------------------------------------

//!Прерывание, возникающее при аппаратной аварии
//!
//! logic of EPWM_TZ_x_IRQHandler corresponds to ePWM, so after each INT you have to check which TZ pin activates
//! i didn't found any reg which hold TZ value, so just direct reading of pins. Not good, b's can lost source, but
//! no other solution for this processor
//!

//from PDF Переход входных сигналов аварии PWM_TZn из состояния логической единицы в
//состояние логического нуля формирует событие аварии


Uint16 ePWM_TZ_0_isr_counter = 0;
Uint16 ePWM_TZ_2_isr_counter = 0;
Uint16 ePWM_TZ_1_isr_counter = 0;

static int _TZ[6];
void EPWM_TZ_0_IRQHandler(void)
{

	ePWM_TZ_0_isr_counter++;

	pwm.Off(&pwm); // set pwm off here for extra protection on different SW behaviour issues


//TODO OK check which TZ sent singnal
	_TZ[0] = (NT_GPIOG->DATA>>13)&0x1;
//	_TZ[1] = (NT_GPIOA->DATA>>9)&0x1;
	_TZ[2] = (NT_GPIOG->DATA>>15)&0x1;
//	_TZ[3] = (NT_GPIOE->DATA>>7)&0x1;
//	_TZ[4] = (NT_GPIOC->DATA>>8)&0x1;
//	_TZ[5] = (NT_GPIOE->DATA>>14)&0x1;

	if (_TZ[0]==0) pwm.PDP_inv1=1;
	if (_TZ[2]==0) pwm.PDP_pulses_block_Imax=1;

	if ((_TZ[0]==1)&&(_TZ[2]==1)){ //signal if no source of TZ detected
		pwm.PDP_inv_ext_lost=1;
		}


	NT_PWM0->TZINTCLR_bit.TZINT=1;
	//не снимаем аварийное удержание выводов, это будет сделано в контуре сброса защит
	//NT_PWM0->TBCTL_bit.TZCLR_bit.OST=1;
}


void EPWM_TZ_1_IRQHandler(void)
{
	NT_PWM0->TZINTCLR_bit.TZINT=1;
}

void EPWM_TZ_2_IRQHandler(void)
{
	NT_PWM0->TZINTCLR_bit.TZINT=1;
}

void DCS_TO_HAL_CONNECTOR()
{

	adc.regs.Ia_inv_reg16	=	(int16)HAL.ADC.regs.I1_A_adc_reg^0x8000;
	adc.regs.Ib_inv_reg16	=	(int16)HAL.ADC.regs.I1_B_adc_reg^0x8000;
	adc.regs.Ic_inv_reg16	=	(int16)HAL.ADC.regs.I1_C_adc_reg^0x8000;

	adc.regs.Ia_tr_reg16	=	(int16)HAL.ADC.regs.I2_A_adc_reg^0x8000;
	adc.regs.Ib_tr_reg16	=	(int16)HAL.ADC.regs.I2_B_adc_reg^0x8000;
	adc.regs.Ic_tr_reg16	=	(int16)HAL.ADC.regs.I2_C_adc_reg^0x8000;

	adc.regs.Uac_inv_reg16	=	(int16)HAL.ADC.regs.U1_AC_adc_reg^0x8000;
	adc.regs.Ubc_inv_reg16	=	(int16)HAL.ADC.regs.U1_BC_adc_reg^0x8000;
	adc.regs.Unc_inv_reg16	=	(int16)HAL.ADC.regs.U1_NC_adc_reg^0x8000;

	adc.regs.Uac_tr_reg16	=	(int16)HAL.ADC.regs.U2_AC_adc_reg^0x8000;
	adc.regs.Ubc_tr_reg16	=	(int16)HAL.ADC.regs.U2_BC_adc_reg^0x8000;
	adc.regs.Unc_tr_reg16	=	(int16)HAL.ADC.regs.U2_NC_adc_reg^0x8000;

	adc.regs.Udc_reg16	=	HAL.ADC.regs.Udc_adc_reg;
	adc.regs.Idc_reg16	=	HAL.ADC.regs.Idc_adc_reg;

	adc.regs.IREF_PWM_adc_reg16 = HAL.ADC.regs.IREF_PWM_adc_reg;
	adc.regs._075V_ref_reg16	= HAL.ADC.regs._0p75V_adc_reg;


}

float R_iso_I_mA;

void DIO_LOGIC_CONNECTORS()
{
int ii;


inv.in.cmd_protect_pow_off = apl_protect.flag_protect1_Q_off;
inv.in.cmd_protect_pwm_off = apl_protect.flag_protect1;

//DC precharege circuit connector
	HAL.DIO.rel_cmd2 = dcdc.DC_precharge_on;

//DCDC connectors
	dcdc.charge_state = (can_mini.can_slave.i_long1)&0xff;
	dcdc.regs.E_charge_persent =  (can_mini.can_slave.i_long1>>8)&0xff;
	dcdc.regs.P_meas_kW = (can_mini.can_slave.i_long1>>16)&0xff;
	dcdc.regs.status_word = (can_mini.can_slave.i_long1>>24)&0xff;

	dcdc.regs.U2_meas_V_I12Q4 = ((can_mini.can_slave.i_long2)&0xffff);
	dcdc.regs.I2_meas_A_I12Q4= (can_mini.can_slave.i_long2>>16)&0xffff;

	dcdc.U2_min = can_mini.can_slave_.i_word0;

	dcdc.regs.stat_ready2connect = (dcdc.regs.status_word>>1)&0x1;
	dcdc.regs.stat_running		 = (dcdc.regs.status_word>>2)&0x1;
	dcdc.regs.stat_stopped 		 = (dcdc.regs.status_word>>3)&0x1;
	dcdc.regs.stat_protect_Q_off = (dcdc.regs.status_word>>4)&0x1;
	dcdc.regs.stat_protect		 = (dcdc.regs.status_word>>5)&0x1;
	dcdc.regs.stat_no_master	 = (dcdc.regs.status_word>>6)&0x1;

	dcdc.regs.ctrl_word = 	(((dcdc.regs.ctrl_start_nstop&0x1)<<0)|\
							((dcdc.regs.ctrl_trip_reset&0x1)<<2)|\
							((dcdc.regs.ctrl_prep2connect&0x1)<<3));

	can_mini.can_slave.o_long1 = 	(((dcdc.Idc2_ref&0xffff)<<0)|\
									 ((dcdc.regs.P_ref_kW_I8&0xff)<<16)|\
									 ((dcdc.regs.ctrl_word&0xff)<<24));

	can_mini.can_slave.o_long2 = (dcdc.regs.Udc1&0xff|((sc_profile.profile&0xff)<<8)|\
								((dcdc.discharge_type&0xff)<<16));
	dcdc.regs.link = can_mini.can_slave.link;
//-------------------------------------------

//FAN connectors
	fan_dctrl.T =(Fmax_3(adc.T1_inv1,adc.T2_inv1,adc.T3_inv1)>>4);//pass from temperature sensor =adc.T3*(1.0/0xf);
	fan_spec.d_fdb = HAL.DIO.DI_6;
	HAL.DIO.FAN2_spd_cmd  =  fan_spec.cmd_lo; //TODO4
	//fan_spec.cmd_pow=0; //TODO2 delete or comment after debug to activate fan control
	if (fan_spec.cmd_pow) aux_K91.cmd_in= CMD_Q_ON;
	else aux_K91.cmd_in= CMD_Q_OFF;
//-------------------------------------------

//AUX_K91 connectors
	HAL.DIO.DO_3coil = aux_K91.hold_on;
	aux_K91.aux_on= (~HAL.DIO.DI_1)&0x1; //inverted in power section
	aux_K91.aux_off= (HAL.DIO.DI_1)&0x1;
//-------------------------------------------

//AUX_K7 connectors
	HAL.DIO.DO_2coil =aux_K7.hold_on;
	aux_K7.aux_on = HAL.DIO.DI_4;
	aux_K7.aux_off = (~HAL.DIO.DI_4)&0x1;
//-------------------------------------------


//CAN_IO_CONNECTOR
//#1
//can_io.Riso=can_mini.can_io[0].a_inp*(40*10.0/0x3fff) ; //analog input from bender iso 40MOhm when 10V = 0x3ff;
//4-20mA,
	R_iso_I_mA=can_mini.can_io[0].a_inp*(20.0/0x3ff);
	can_io.Riso=16*120/(R_iso_I_mA-4)-120;///can_mini.can_io[0].a_inp*(40*20.0/0x3fff) ;

can_mini.can_io[0].o_word	=	can_io.Q4_on_K21+\
								(can_io.Q4_off_K22<<1);

can_io.Q4_aux			=((can_mini.can_io[0].i_word)>>0)&0x1;
//													>>1
//													>>2
can_io.opn_DC			=((can_mini.can_io[0].i_word)>>3)&0x1;
can_io.bender_iso_inp1	=((can_mini.can_io[0].i_word)>>4)&0x1;
can_io.bender_iso_inp2	=((can_mini.can_io[0].i_word)>>5)&0x1;
//#2
can_mini.can_io[2].o_word	=	vacuum.cmd_out_on+\
							(vacuum.cmd_out_off<<1)+\
							((vacuum.cmd_out_block&0x1)<<2);

can_io.K60_aux			=((can_mini.can_io[2].i_word)>>0)&0x1;
can_io.opn_AC			=((can_mini.can_io[2].i_word)>>1)&0x1;
can_io.F60_aux			=((can_mini.can_io[2].i_word)>>2)&0x1;
can_io.F61_aux			=((can_mini.can_io[2].i_word)>>3)&0x1;
can_io.Q26_aux			=((can_mini.can_io[2].i_word)>>4)&0x1; //ToDo4
can_io.S100200300		=((can_mini.can_io[2].i_word)>>5)&0x1;
//#3



// TODO 15 CANIO#1 used for DIESEL control - bender off excluded
//was can_mini.can_io[1].o_word	=	can_io.Q6_on_K21+\
//							(can_io.Q6_off_K22<<1)+\
//							(can_io.bender_off_K23<<2);
//can_io.Q6_aux=((can_mini.can_io[1].i_word&0x1)>>0);

can_mini.can_io[1].o_word	=	can_io.Q6_on_K21+\
							(can_io.Q6_off_K22<<1)+\
							((diesel.cmd_out_start&0x1)<<2);

can_io.Q6_aux=((can_mini.can_io[1].i_word>>0)&0x1);
vacuum.on = ((can_mini.can_io[1].i_word>>1)&0x1);
vacuum.off = ((can_mini.can_io[1].i_word>>2)&0x1);
diesel.operating =((can_mini.can_io[1].i_word>>3)&0x1);
diesel.ready = ((can_mini.can_io[1].i_word>>4)&0x1);
vacuum.blocked = ((can_mini.can_io[1].i_word>>5)&0x1);
diesel.fuel_level= 50;

//example can_io.Riso=can_mini.can_io[0].a_inp*(40*10.0/0x3fff) ; //analog input from bender iso 40MOhm when 10V = 0x3ff;
//4-20mA,
//	R_iso_I_mA=can_mini.can_io[0].a_inp*(20.0/0x3ff);



can_io.link1=can_mini.can_io[0].link;
can_io.link2=can_mini.can_io[1].link;
can_io.link3=can_mini.can_io[2].link;


//TODO LAB_MODE
//can_io.Q4_on_K21=aux_Q4.cmd_on;
//can_io.Q4_off_K22=aux_Q4.cmd_off;
//
//can_io.Q6_on_K21=aux_Q6.cmd_on;
//can_io.Q6_off_K22=aux_Q6.cmd_off;
//
//aux_Q6.aux_on = can_io.Q6_aux;
//aux_Q6.aux_off = (~aux_Q6.aux_on)&0x1;
//
//
//aux_Q4.aux_on = can_io.Q4_aux;
//aux_Q4.aux_off =(~aux_Q4.aux_on)&0x1;

#ifdef LAB_MODE_GLOBAL_DEFINE
HAL.DIO.rel_cmd1=aux_Q6.hold_on;
HAL.DIO.rel_cmd2=aux_Q4.hold_on;
aux_Q6.aux_on = aux_Q6.hold_on;
aux_Q6.aux_off = (~aux_Q6.aux_on)&0x1;
aux_Q4.aux_on = aux_Q4.hold_on;
aux_Q4.aux_off =(~aux_Q4.aux_on)&0x1;

#else
can_io.Q4_on_K21=aux_Q4.cmd_on;
can_io.Q4_off_K22=aux_Q4.cmd_off;

can_io.Q6_on_K21=aux_Q6.cmd_on;
can_io.Q6_off_K22=aux_Q6.cmd_off;

aux_Q6.aux_on = can_io.Q6_aux;
aux_Q6.aux_off = (~aux_Q6.aux_on)&0x1;

aux_Q4.aux_on = can_io.Q4_aux;//aux_Q4.hold_on; //TODO4 can_io.Q4_aux;
aux_Q4.aux_off =(~aux_Q4.aux_on)&0x1;
#endif



aux_Q26.aux_on = can_io.Q26_aux;
aux_Q26.aux_off = (~aux_Q26.aux_on)&0x1;


}







//!--------------------------------------------------------------------------------------------------------------------------------------------------
//! 								GARBAGE //all commented out
//! -------------------------------------------------------------------------------------------------------------------------------------------------
////!-------------------------------------------------------------------------------------------------
////!  Прерывание, возникающее по событиям захвата модуля CAP0
////! \memberof MAIN_C
////!-------------------------------------------------------------------------------------------------
//#if defined (__GNUC__)
//void ECAP0_IRQHandler(void)
//#elif defined (__CMCPPARM__)
//void CAP0_IRQHandler(void)
//#endif
//{
//	//Подтверждаем это прерывание для NVIC - иначе при выходе из функции оно возникнет опять
//	NT_CAP0->PEINT = 1;
//
////	if (DPReCAP.CAPCalcEna1 == 0) { //если функция вызвалась повторно
////		DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
////		DPReCAP.CAP_WrongEdgeCnt1++;
////		return;
////	}
////	DPReCAP.CAPCalcEna1 = 0;//расчет будет разрешен, когда тикнет прерывание 10кГц. Чаще считать нет смысла, это помехи
//
//	CounterCAP_isr++;//общий счётчик всех прерываний модуля захвата
//	CounterCAP_isr = CounterCAP_isr & 0xF;
//	cap0_counter++;//счётчик прерываний именно этого канала
//	//исходя из состояния ног трех датчиков Холла высчитывает текущий угол с точностью 60 градусов.
//	//выходом функции является  DPReCAP.Angle6 - угол с точностью 60 градусов.
////	DPReCAP.Angle6Calc(&DPReCAP);
////	//обработчик модуля захвата канала1 (0, если считать с нуля, но не переименовывать же какждый раз функции, в зависимости от версии заголовочных файлов...).
////	//Засекает время между этим импульсом и предыдущими для расчета интерполятора угла и частоты вращения (скорости)
////	DPReCAP.CAP1Calc(&DPReCAP);
//
//	//Подтверждение прерываний
//	NT_CAP0->ECCLR_bit.CEVT0 = 1;
//	NT_CAP0->ECCLR_bit.CEVT1 = 1;
//	NT_CAP0->ECCLR_bit.INT = 1;
//
//}
//
////!Прерывание, возникающее по событиям захвата модуля CAP1
////! \memberof MAIN_C
//#if defined (__GNUC__)
//void ECAP1_IRQHandler(void)
//#elif defined (__CMCPPARM__)
//void CAP1_IRQHandler(void)
//#endif
//{
//	//Подтверждаем это прерывание для NVIC - иначе при выходе из функции оно возникнет опять
//	NT_CAP1->PEINT = 1;
//
////	if (DPReCAP.CAPCalcEna2 == 0) { //если функция вызвалась повторно
////		DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
////		DPReCAP.CAP_WrongEdgeCnt2++;
////		return;
////	}
////	DPReCAP.CAPCalcEna2 = 0;
////
////	CounterCAP_isr++;
////	CounterCAP_isr = CounterCAP_isr & 0xF;
////	cap1_counter++;
////	DPReCAP.Angle6Calc(&DPReCAP);
////	DPReCAP.CAP2Calc(&DPReCAP);
//
//	//Подтверждение прерываний
//	NT_CAP1->ECCLR_bit.CEVT0 = 1;
//	NT_CAP1->ECCLR_bit.CEVT1 = 1;
//	NT_CAP1->ECCLR_bit.INT = 1;
//}
//
//
////!Прерывание, возникающее по событиям захвата модуля CAP2
////! \memberof MAIN_C
//#if defined (__GNUC__)
//void ECAP2_IRQHandler(void)
//#elif defined (__CMCPPARM__)
//void CAP2_IRQHandler(void)
//#endif
//{
//	//Подтверждаем это прерывание для NVIC - иначе при выходе из функции оно возникнет опять
//	NT_CAP2->PEINT = 1;
//
////	if (DPReCAP.CAPCalcEna3 == 0) { //если функция вызвалась повторно
////		DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
////		DPReCAP.CAP_WrongEdgeCnt3++;
////		return;
////	}
////	DPReCAP.CAPCalcEna3 = 0;
//
//	CounterCAP_isr++;
//	CounterCAP_isr = CounterCAP_isr & 0xF;
//	cap2_counter++;
////	DPReCAP.Angle6Calc(&DPReCAP); //если убрать, то в момент прихода метки на один период ШИМ косяк, так как прерывание посчиталось, а Angle6Calc нет
////	DPReCAP.CAP3Calc(&DPReCAP);
//
//	//Подтверждение прерываний
//	NT_CAP2->ECCLR_bit.CEVT0 = 1;
//	NT_CAP2->ECCLR_bit.CEVT1 = 1;
//	NT_CAP2->ECCLR_bit.INT = 1;
//}
//
//
////!-------------------------------------------------------------------------------------------------
////!Прерывание, возникающее по событию реперной метки(индекса) модуля QEP
////! \memberof MAIN_C
////! Но - на двигателе ACM601V36-1000 нет индексной метки.
////Так что этого прерывания c таким двигателем не будет (или будет от помех, как повезет)
//#if defined (__GNUC__)
//void EQEP1_IRQHandler(void)
//#elif defined (__CMCPPARM__)
//void QEP1_IRQHandler(void)
//#endif
//{
//	//Обработка репера
//	//posspeedEqep.index(&posspeedEqep);
//	//Подтверждаем это прерывание для NVIC
//	NT_QEP1->INTCLR = 1;
//	NT_QEP1->QCLR_bit.IEL = 1;
//	NT_QEP1->QCLR_bit.INT = 1;
//}
//
///*@}*/

