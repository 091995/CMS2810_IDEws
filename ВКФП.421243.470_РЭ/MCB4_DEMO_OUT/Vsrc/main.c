/*!
    Copyright 2023 ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      main.h
 \brief     Главный заголовочный файл проекта.
Подключает в себе все заголовочные файлы всех модулей,
Содержит объявления (extern) всех наиболее важных
глобальных структур и переменных.

 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  MAIN Главный файл проекта

@{*/
/*@{*/

#ifdef __cplusplus
extern "C"
{
#endif
#include "IQmathLib.h"         	// библиотека IQmath
#include "DSP28_Device.h"		//
#include "main.h"
#include "string.h" //длЯ memcpy
#ifdef __cplusplus
}
#endif

TClarke clarke = CLARKE_DEFAULTS; //!<Фазные преобразования
TPark park = PARK_DEFAULTS; //!<Координатные преобразования
TIPark ipark = IPARK_DEFAULTS; //!<Обратные координатные преобразования
TPidReg3 pid_id = PIDREG3_DEFAULTS; //!<Рег. тока по оси d
TPidReg3 pid_iq = PIDREG3_DEFAULTS; //!<Рег. тока по оси q
TPidReg3 pid_ia = PIDREG3_DEFAULTS; //!<Рег. тока якоря ДПТ
TPidReg3 pid_spd = PIDREG3_DEFAULTS; //!<Рег. скорости
TPidReg3_pos pid_pos = PIDREG3_DEFAULTS_POS; //!<Рег. положения
TRelayReg i_a_reg = RELAY_REG_DEFAULTS; //!<регулятор тока фазы A (для модели SRM)
TRelayReg i_b_reg = RELAY_REG_DEFAULTS; //!<регулятор тока фазы A (для модели SRM)
TRelayReg i_c_reg = RELAY_REG_DEFAULTS; //!<регулятор тока фазы A (для модели SRM)
TVhzProf vhz = VHZPROF_DEFAULTS;    //!< закон U/f=const
TSM_Sys sm_sys = SM_Sys_DEFAULTS; //!< Главная оболочка для вызова всех модулей
Uint16 disp_group_number = 0;   //!< Необходимо для драйвера CANOpen и Unicon
TDataLog dlog = DATALOG_DEFAULTS; //!< Модуль осциллографирования переменных CANOpen
TSM_Protect sm_prot = SM_PROTECT_DEFAULTS;  //!< Модуль защит
TBitsToEnumNums pult_faults_lister = BITS_TO_ENUM_NUMS_DEFAULTS; //!<Листалка аварий для Unicon
TSM_Ctrl sm_ctrl = SM_CTRL_DEFAULTS; //!< Главный дискретный автомат, реализует структуру управления
TSM_CmdLogic sm_cmd_logic = SM_CMD_LOGIC_DEFAULTS; //!< Обработка пользовательских команд управления
TSM_Net sm_net = SM_NET_DEFAULTS;   //!< Оболочка для вызова сетевых драйверов
TRMPCtrl rmp = V_RMP_CTRL_DEFAULTS;     //!< Задатчик интенсивности
TAdcDrv adc = ADC_DRV_DEFAULTS;     //!< Модуль АЦП
TPWM_Module pwm = PWM_Module_DEFAULTS;  //!< Модуль ШИМ
Texcitation pwm_ex = excitation_DEFAULTS;   //!< Модуль возбудителя СД
TDPReCAP DPReCAP = DPRECAP_DEFAULTS; //!< Модуль ДПР на элементах Холла
TEncoder posspeedEqep = ENCODER_DEFAULTS; //!< Модуль ДПР типа энкодер                              //!<Модуль обработки инкрементального энкодера
TCurPar cur_par = TCUR_PAR_DEFAULTS; //!< Модуль расчета и хранения текущих показателей привода - мощность, скорость
TSpiMem spimem = USERMEMORY_DEFAULTS; //!< Модуль работы с энергонезависимой памятью.
Tled leds = LED_DEFAULTS; //!< модуль для красивого мигания светодиодами
TCanBTInterface Can1BTInterface = T_CANBT_INTERFACE_DEFAULTS;//!<Пакетная передача CANopen
//TCanBTInterface Can2BTInterface = T_CANBT_INTERFACE_DEFAULTS;//!<Пакетная передача CANopen
TRTCClock RTCclock = RTC_CLOCK_DEFAULTS; //!< Модуль работы с часами реальноговремени. "spi" - по историческим причинам совместимости
TAutoOffset AutoOffset = AUTO_OFFSET_DEFAULTS;  //!<Автоматическая подстройка смещения токов АЦП
TSSI_Encoder SSI_Encoder = SSI_ENCODER_DEFAULTS; //!<Драйвер обработки датчика положения с SSI интерфейсом
TRotorObserver RotorObserver = ROTOR_OBSERVER_DEFAULTS; //!<Датчиковый наблюдатель потокосцепления ротора асинхронного двигателя
//TCANtoRS CANtoRS = CAN_TO_RS_DEFAULTS; //!<Модуль для работы с драйвером CANopen через UART (RS). Посылки CAN запаковываются в UART

TModBus ModBus = MODBUS_DEFAULTS;                        //!<Драйвер ModBus
MODBUS_INT MBInternals = MODBUS_INT_DEFAULTS;   //!<Драйвер ModBus внутр. перем.
MODBUS_RS ModBusRS = MODBUS_RS_DEFAULTS;            //!<Драйвер ModBus ошибки RS
TMBVarsConv MBVarsConv = MBVARSCONV_DEFAULTS;//!< Модуль преобразования данных из формата 16 разрядов Modbus в формат системы управления (IQ 24)

TCANtoRS CANtoRS = CAN_TO_RS_DEFAULTS; //!<Модуль для работы с драйвером CANopen через UART (RS). Посылки CAN запаковываются в UART

//TMBVarsConv MBVarsConv = MBVARSCONV_DEFAULTS;//!< Модуль преобразования данных из формата 16 разрядов Modbus в формат системы управления (IQ 24)
TDrvInterface drv_interface = DRV_INTERFACE_DEFAULTS;   //!<Интерфейс длЯ работы с банками аварий, событий и т.п.
TLogger FaultLog = LOGGER_DEFAULTS;         //!<Протоколирование аварий
TGlobalTime global_time = GLOBAL_TIME_DEFAULTS; //!<Работа с часами
TUdControl udControl = UD_CONTROL_DEFAULTS; //!<Плавная зарядка ЗПТ через термисторы
TFanControl FanControl = FAN_CONTROL_DEFAULTS; //!<Вентилятор

TRefs refs; //!< Структура с заданиями (токи, скорости)
TCmd cmd = { 0 }; //!< Структура с командами управления
TDrvStatus drv_status = { 0 }; //!< Текущий статус привода
TDrvParams drv_params; //!< Параметры двигателя
TSysSwitches sw; //!< Различные дискретные настройки системы управления

TPDO_PACK_1 TPDO_pack1 = PDO_PACK_DEFAULTS;
TPDO_PACK_2 TPDO_pack2 = PDO_PACK_DEFAULTS;
TPDO_PACK_3 TPDO_pack3 = PDO_PACK_DEFAULTS;
TPDO_PACK_4 TPDO_pack4 = PDO_PACK_DEFAULTS;
TPDO_PACK_1 RPDO_pack3 = PDO_PACK_DEFAULTS;
RPDO_PACK_1 RPDO_pack1 = PDO_PACK_DEFAULTS;
RPDO_PACK_2 RPDO_pack2 = PDO_PACK_DEFAULTS;

Uint32 VendorToken=0x33333333;//!< Уникальный ключ производителя, нужный для программы UniCON и COODEdit для различных наборов текстов разных произхводителей
int drv_status_code; //!<Статус системы управления в виде константы (ГОТОВ, РАБОТА и т.п.)

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

//Счетчики прерываний модуля захвата
Uint16 CounterCAP_isr = 0;
Uint16 cap0_counter = 0;
Uint16 cap1_counter = 0;
Uint16 cap2_counter = 0;

Uint16 LoopCounter = 0; //!< Счетчик итераций фонового цикла

Uint32 msCounter=0;
Uint32 FastCounter=0;
Uint32 TIsr10;
Uint32 TIsr1;

/*! Начало выполенения программы - main()  */
//! \memberof main
int main(void) {
	/***********************************/
	/* СекциЯ инициализации процессора */
	/***********************************/

	InitSysCtrl();
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();
	InitPieVectTable();

	StartCpuTimer0();

#ifdef FLASH_VERS
	// Section secureRamFuncs contains user defined code that runs from CSM secured RAM
	memcpy(&secureMathFuncs_runstart, &secureMathFuncs_loadstart, &secureMathFuncs_loadend - &secureMathFuncs_loadstart);

	memcpy(&secureRamFuncs_runstart, &secureRamFuncs_loadstart, &secureRamFuncs_loadend - &secureRamFuncs_loadstart);

	InitFlash();			//включаетсЯ конвейер	// Initialize the FLASH (FILE: SysCtrl.c)
#endif

	pwm.Off(&pwm); //выключить ШИМ (на всякий случай)


    //Инициализация, собственно, всего.
    sm_sys.init(&sm_sys);
    sm_sys.IntEna=1;//инициализация завершена

	EINT;
	// Enable Global interrupt INTM
	ERTM;
	// Enable Global realtime interrupt DBGM

	/********************************************************/
	/************ Фоновый замкнутый цикл ********************/
	/********************************************************/
	for (;;) {
	    LoopCounter++;
		sm_sys.slow_calc(&sm_sys);//расчет всего медленного
	}
}


unsigned long prevCpuTimer_ms;
unsigned long T_ms;

/*! 1мс таймер  */
//! \memberof main
interrupt void EvbTimer4(void) {
    prevCpuTimer_ms = CpuTimer2Regs.TIM.all; //для подсчета тактов
    EINT;

    sm_sys.ms_calc(&sm_sys); //миллисекундный расчет всего
    msCounter++;

    T_ms = prevCpuTimer_ms - CpuTimer2Regs.TIM.all;

    if (T_ms > 140000)
        sm_prot.bit_fault1 |= F_PROGRAM_1K; //если расчет слишком долгий, ошибка

    //для подтверждения прерывания (тока как-то странно, я не помню, почему так надо).
    EvbRegs.EVBIMRB.all |= (1 << 2);   //EvbRegs.EVBIMRB.bit.T4UFINT = 1;
    EvbRegs.EVBIFRB.all |= (1 << 2); //EvbRegs.EVBIFRB.bit.T4UFINT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

unsigned long Tpwm;
unsigned long TpwmMax = 0;
unsigned long prevCpuTimer_10k;

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(CPUTimer0_isr,"secureRamFuncs");
#endif
/*! 10кГц таймер  */
//! \memberof main
interrupt void CPUTimer0_isr(void) {
	//запрещение прерываний
	DINT;
	//на всЯЯкий случай
	//обход кривЯтины срабатываниЯ ложного прерываниЯ
	PieCtrlRegs.PIEIER9.all &= ~M_INT5;  //запрещение группы 9 (CAN)
	PieCtrlRegs.PIEIER5.all &= ~M_INT3;  //запрещение группы 5 (1мс - T4UFINT)
	asm(" nop");
	//когда запрещаем прерывание, нужно выждать
	asm(" nop");
	//несколько тактов, иначе, если прерывание уже началось обрабатыватьсЯ аппаратно,
	asm(" nop");
	//а мы его запретили строчками выше, процессор в итоге вызовет совершенно
	asm(" nop");
	//другое прерывание, ложное, наиболее приоритетное в данной группе
	asm(" nop");
	//также важно выставить перед этим DINT
	IFR &= ~M_INT9;  //снимаем флаги - они могли возникнуть за те "nop" (CAN)
	IFR &= ~M_INT5; //снимаем флаги - они могли возникнуть за те "nop" (T4UFINT)
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;  //подтверждаем, чтобы оно не обработалось еще раз( CAN)
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;  //подтверждаем, чтобы оно не обработалось еще раз (T4UFINT)
	//  PieCtrlRegs.PIEIER5.bit.INTx3=0;// &= ~M_INT3;
	//  IER &= ~M_INT5;

	//Учет счетчиков длЯ измерениЯ длительности прерывани
	prevCpuTimer_10k = CpuTimer2Regs.TIM.all; //150МГЦ таймер, длЯ расчета кол-ва тактов

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	EINT;
	IER |= 1;
	FastCounter++;

	//основной расчет всего, что надо считать раз в 10кГц
	sm_sys.fast_calc(&sm_sys);
	DINT;

	// Enable more interrupts from this timer
	//  EvbRegs.EVBIMRA.all |= (1<<9);
	//  EvbRegs.EVBIFRA.all |= (1<<9);

	//разрешаем назад
	PieCtrlRegs.PIEIER9.all |= M_INT5; //CAN
	PieCtrlRegs.PIEIER5.all |= M_INT3; //T4UFINT

	//Подсчет кол-ва потраченных тактов
	Tpwm = prevCpuTimer_10k - CpuTimer2Regs.TIM.all;

	if (Tpwm > TpwmMax)//захлопнем максимум
		TpwmMax = Tpwm;

	if (Tpwm > 14000)
        sm_prot.bit_fault1 |= F_PROGRAM_10K; //если расчет слишком долгий, ошибка
}

Uint16 ePWM0_TZ_isr_counter = 0;
/*! Аппаратная авария менеджера событий "a"  */
//! \memberof main
interrupt void pdpinta_protect_isr(void) {

    ePWM0_TZ_isr_counter++;

    pwm.Off(&pwm);

    if (sm_ctrl.state!=CTRL_STOP)
    {
        sm_prot.bit_fault1|= F_PDPINT;
    }
    sm_ctrl.state=CTRL_STOP;

    //сбрасываем флаги прерываний по этой ножке
	EvaRegs.EVAIMRA.all |= (1 << 0); //EvaRegs.EVAIMRA.bit.PDPINTA = 1;
	EvaRegs.EVAIFRA.all |= (1 << 0); //EvaRegs.EVAIFRA.bit.PDPINTA = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(cap1_interrupt_isr,"secureRamFuncs");
#endif
/*! Прерывание ДПР канал1  */
//! \memberof main
interrupt void cap1_interrupt_isr(void) {


    if (DPReCAP.CAPCalcEna1 == 0) { //если функция вызвалась повторно
        DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
        DPReCAP.CAP_WrongEdgeCnt1++;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
        return;
    }
    DPReCAP.CAPCalcEna1 = 0;//расчет будет разрешен, когда тикнет прерывание 10кГц. Чаще считать нет смысла, это помехи

    CounterCAP_isr++;//общий счётчик всех прерываний модуля захвата
    CounterCAP_isr = CounterCAP_isr & 0xF;
    cap0_counter++;//счётчик прерываний именно этого канала
    //исходя из состояния ног трех датчиков Холла высчитывает текущий угол с точностью 60 градусов.
    //выходом функции является  DPReCAP.Angle6 - угол с точностью 60 градусов.
    DPReCAP.Timer1 = CpuTimer2Regs.TIM.all;
    DPReCAP.Angle6Calc(&DPReCAP);
    //обработчик модуля захвата канала1 (0, если считать с нуля, но не переименовывать же какждый раз функции, в зависимости от версии заголовочных файлов...).
    //Засекает время между этим импульсом и предыдущими для расчета интерполятора угла и частоты вращения (скорости)
    DPReCAP.CAP1Calc(&DPReCAP);

	EvbRegs.EVBIFRC.bit.CAP4INT = 1; // Сбрасываем флаг прерываниЯ
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

}


#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(cap2_interrupt_isr,"secureRamFuncs");
#endif
/*! Прерывание ДПР канал2  */
//! \memberof main
interrupt void cap2_interrupt_isr(void) {

    if (DPReCAP.CAPCalcEna2 == 0) { //если функция вызвалась повторно
        DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
        DPReCAP.CAP_WrongEdgeCnt2++;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
        return;
    }
    DPReCAP.CAPCalcEna2 = 0;

    CounterCAP_isr++;
    CounterCAP_isr = CounterCAP_isr & 0xF;
    cap1_counter++;
    DPReCAP.Timer2 = CpuTimer2Regs.TIM.all;
    DPReCAP.Angle6Calc(&DPReCAP);
    DPReCAP.CAP2Calc(&DPReCAP);

    EvbRegs.EVBIFRC.bit.CAP5INT = 1; // Сбрасываем флаг прерываниЯ
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}


#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(cap3_interrupt_isr,"secureRamFuncs");
#endif
/*! Прерывание ДПР канал3  */
//! \memberof main
interrupt void cap3_interrupt_isr(void) {

    if (DPReCAP.CAPCalcEna3 == 0) { //если функция вызвалась повторно
        DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
        DPReCAP.CAP_WrongEdgeCnt3++;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
        return;
    }
    DPReCAP.CAPCalcEna3 = 0;

    CounterCAP_isr++;
    CounterCAP_isr = CounterCAP_isr & 0xF;
    cap2_counter++;
    DPReCAP.Timer3 = CpuTimer2Regs.TIM.all;
    DPReCAP.Angle6Calc(&DPReCAP); //если убрать, то в момент прихода метки на один период ШИМ косяк, так как прерывание посчиталось, а Angle6Calc нет
    DPReCAP.CAP3Calc(&DPReCAP);

    EvbRegs.EVBIFRC.bit.CAP6INT = 1; // Сбрасываем флаг прерываниЯ
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

Uint16 scib_rx_isr_counter=0;
Uint16 scib_tx_isr_counter=0;

interrupt void scib_rx_isr(void)
{
    scib_rx_isr_counter++;
    EINT;

    CANtoRS.receive(&CANtoRS);

    CANTORS_SCIXREGS.SCIFFRX.bit.RXFFINTCLR=1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
/*@}*/
