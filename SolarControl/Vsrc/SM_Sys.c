/*!

 */


#include "main.h"

/* Объявление адреса размещения таблицы векторов прерываний */
#if   defined ( __CMCPPARM__ )
	extern const Uint32 __Vectors;
#elif defined (__GNUC__)

#endif

//! Инициализация системы управления после включения

//!Инициализация некоторых модулей и настройка прерываний системы.
//!Здесь настраивается большинство прерываний
//! \memberof TSM_Sys
void SM_Sys_Init(TSM_Sys *p) {
#if defined (HW_VECTORCARD_DRV8301_EVM)
	sw.HardwareType = 0;
#elif defined (HW_VECTORCARD_DRV8312_EVM)
	sw.HardwareType = 1;
#elif defined (HW_VECTORCARD_SIMULATOR)
	sw.HardwareType = 2;
#endif
	//cmd.all = 0;
	//inv_status.all = 0;
	adc.init(&adc); //Инициализация АЦП
	dcs_prot.init(&dcs_prot); //Защиты
	dcs_ctrl.init(&dcs_ctrl); //Структура системы управления
	cur_par.init(&cur_par); //Расчет текущих показателей инвертора
	sim.init(&sim);



	leds.init(&leds);//светодиоды
	dio_logic.init();

	apl_protect.p_prot_word[0]=&dcs_prot.masked_bit_fault1;
	apl_protect.p_prot_off_word[0]=&dcs_prot.masked_fault_off;


	apl_protect.p_prot_word[1]=&dio_protect.masked_bit_fault1;
	apl_protect.p_prot_off_word[1]=&dio_protect.masked_fault_off;

	//only for OC and Udcmin autorecovery - bit set means - AR autorecovery prohibited
	apl_protect.mask_apv_word[0] = 0xffff;
	apl_protect.mask_apv_word[0]&=~((Uint16)(F_UDC_MIN|F_U_TR_MAX|F_U_TR_MIN|F_MAX_I_INV_A|F_MAX_I_INV_B|F_MAX_I_INV_C|F_MAX_I_TR_A|F_MAX_I_TR_B|F_MAX_I_TR_C));
	apl_protect.mask_apv_word[1] = 0xffff;

	apl.init(&apl);

	//глобальное времЯ (внешние или внутр. часы)
	global_time.init(&global_time);



	//TODO remember that T0 timer isr8kHz shoul be synced with pwm
	pwm.init(&pwm); //Модуль ШИМ


	//листалка аварий для отображения на пульте управления (UniCON)
	pult_protect_lister.num_of_words = 2;
	pult_protect_lister.out_refresh_devisor = 1000; //при вызове в мс таймере период обновления будет равен 1сек
	pult_protect_lister.w_ptrs[0] = (Uint16*) &apl_protect.masked_word[0];//перебираются эти флаги аварий модуля защит
	pult_protect_lister.w_ptrs[1] = (Uint16*) &apl_protect.masked_word[1];

	pult_alarm_lister.num_of_words = 2;
	pult_alarm_lister.out_refresh_devisor = 1000; //при вызове в мс таймере период обновления будет равен 1сек

	pult_alarm_lister.w_ptrs[0] = (Uint16*) &dio_protect.bit_alarm1;
	pult_alarm_lister.w_ptrs[1] = (Uint16*) &dcs_prot.bit_alarm1;



	AutoOffset.FilterK = _IQ(0.00001);//постоянная времени фильтра для автосмещения АЦП
	AutoOffset.init(&AutoOffset); //авто смещение некоторых каналов АЦП (токи)

//#if defined(HW_VECTORCARD_SIMULATOR) || defined(HW_NIIET_BOARD_SIMULATOR)
//	//model.motorInternals.udc = 540; //задается через словарь объектов
//	model.tpr = _IQ10div(_IQ10(CORE_CLK/1000.0), pwm.Frequency << 1) >> 10; //период частоты ШИМ
//	model.dt = _IQ4mpy(_IQ4(150 / 4), pwm.DeadBand >> 20) >> 4; //величина мертвого времени
//	model.Init(&model); //Модель двигателя
//#endif

	// Настройка таймера 0 на 10 кГц
	NT_TIMER0->INTSTATUS_INTCLEAR_bit.INT = 1;
	NT_TIMER0->RELOAD = 12500-1; //10000 - 1; //9999 надо чтобы не плыло отностильно прерывания ШИМа, когда у того частота 10кГц
	NT_TIMER0->CTRL = ((1 << 0) | (1 << 3)); // Запуск и разрешение прерываний
	//sync pwm with T0
	NT_PWM0->TBCTR = 0;
	NT_PWM1->TBCTR = 0;
	NT_PWM2->TBCTR = 0;
	NT_PWM3->TBCTR = 0;
	NT_PWM4->TBCTR = 0;
	NT_PWM5->TBCTR = 0;
	NT_PWM6->TBCTR = 0;
	NT_PWM7->TBCTR = 0;
	NT_PWM8->TBCTR = 0;


	// Настройка таймера 1 на 1 кГц
	NT_TIMER1->INTSTATUS_INTCLEAR_bit.INT = 1;
	NT_TIMER1->RELOAD = 100000 - 1;
	NT_TIMER1->CTRL = ((1 << 0) | (1 << 3)); // Запуск и разрешение прерываний

	//Для подсчета тактов
	NT_TIMER2->RELOAD = 0xFFFFFFFF;
	NT_TIMER2->CTRL = (1 << 0); // Запуск

	extern int *g_pfnVectors; //там, где-то в стартап файле есть такой символ
	//Надо показать в этом регистре, где лежит таблица прерываний.
	//А лежит она там, куда записал её линкер, в зависимости от файла компоновки.
	//Поэтому берем адрес от массива g_pfnVectors и кладем туда
#if defined (__CMCPPARM__)
	SCB->VTOR = (uint32_t) (&__Vectors);
#elif defined (__GNUC__)
	extern int *g_pfnVectors;
	SCB->VTOR = (uint32_t) (&g_pfnVectors);
#endif
	NVIC_SetPriorityGrouping(3); // 4 bit preemption, 0 bit of subprio

	NVIC_DisableIRQ(TIM0_IRQn);
	NVIC_DisableIRQ(TIM1_IRQn);
	NVIC_DisableIRQ(CAP0_IRQn);
	NVIC_DisableIRQ(CAP1_IRQn);
	NVIC_DisableIRQ(CAP2_IRQn);
	NVIC_DisableIRQ(PWM0_TZ_IRQn);
	NVIC_DisableIRQ(QEP1_IRQn);

	NVIC_ClearPendingIRQ(TIM0_IRQn);
	NVIC_ClearPendingIRQ(TIM1_IRQn);
	NVIC_ClearPendingIRQ(CAP0_IRQn);
	NVIC_ClearPendingIRQ(CAP1_IRQn);
	NVIC_ClearPendingIRQ(CAP2_IRQn);
	NVIC_ClearPendingIRQ(PWM0_TZ_IRQn);
	NVIC_ClearPendingIRQ(QEP1_IRQn);

	/* Прерывание 10 кГц */
//	NVIC_EnableIRQ(TIM0_IRQn);
//	NVIC_SetPriority(TIM0_IRQn, IRQ_PRIORITY_10K);

	/* Прерывание 1 кГц */
	NVIC_EnableIRQ(TIM1_IRQn);
	NVIC_SetPriority(TIM1_IRQn, IRQ_PRIORITY_1K);

	//NVIC_EnableIRQ(CAP0_IRQn); //CAP0
	//NVIC_SetPriority(CAP3_IRQn, IRQ_PRIORITY_CAP);

	//NVIC_EnableIRQ(CAP1_IRQn); //CAP1
	//NVIC_SetPriority(CAP4_IRQn, IRQ_PRIORITY_CAP);

	//NVIC_EnableIRQ(CAP2_IRQn); //CAP2
	//NVIC_SetPriority(CAP5_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(PWM0_TZ_IRQn); //PDP (в инверторе тексас нету такого пина)
	NVIC_SetPriority(PWM0_TZ_IRQn, IRQ_PRIORITY_TZ);


	NVIC_EnableIRQ(PWM0_IRQn); //PWM0
	NVIC_SetPriority(PWM0_IRQn, IRQ_PRIORITY_10K);
	NVIC_EnableIRQ(PWM1_IRQn); //PWM0
	NVIC_SetPriority(PWM1_IRQn, IRQ_PRIORITY_10K);

	//NVIC_EnableIRQ(QEP1_IRQn); //QEP
	//NVIC_SetPriority(QEP1_IRQn, IRQ_PRIORITY_EQEP);

	sm_sys.state = SYS_READY;


#ifdef WATCHDOG_ON
	WatchDog.init(WATCHDOG_PERIOD);	//если сторожевой таймер используется, инициализируем
#endif //WATCHDOG_ON
}


/**************************************************************************************************
 *
 * @param p
 **************************************************************************************************/
void SM_Sys_Fast_Calc(TSM_Sys *p) {

// this part was moved to dcs_ctrl.call mau be deleted
//		sim.fast_calc(&sim);
//		adc.fast_calc(&adc); //АЦП
//	dlog.update(&dlog); //Осциллографирование данных

	dcs_ctrl.fast_calc(&dcs_ctrl); //Главный дискретный автомат системы управления

	dlog.update(&dlog); //Осциллографирование данных, после dcs чтобы видно что на входе, что на выходе

	global_time.calc(&global_time);

	//Debug1=gen.wt;
	//Debug2=apl_protect.AR1.state;
	Debug3=apl_protect.AR1.AR_word[0];
	Debug4=apl_protect.dcs_ctrl_running;


#ifdef WATCHDOG_ON
	WatchDog.calc();//если сторожевой таймер используется, сбрасываем его здесь
#endif //WATCHDOG_ON
}

//!Миллисекундный расчет 1кГц.

//!Вызов расчетов модулей системы управления, требующих миллисекундной дискретизации
//! \memberof TSM_Sys
void SM_Sys_ms_Calc(TSM_Sys* p) {

	apl_protect.AR1.in_cmd_stop=(cmd_logic.cmd.cmd_pulses_off||cmd_logic.cmd.cmd_pow_off);
	apl_protect.cmd_trip_reset1 = cmd_logic.cmd.cmd_trip_reset;
	apl_protect.dcs_ctrl_running = dcs_ctrl.out.running;
	apl.ms_calc(&apl);


	//ToDo pass data from all sources to inv structure
	inv.in.DCS_Urms =dcs_ctrl.out.Urms;
	inv.in.DCS_Udc = dcs_ctrl.out.Udc;
	//inv.in.DCS_P =  refs.Id_ref;  nto used
	inv.in.DCS_freq=dcs_ctrl.out.freq;
	inv.in.DCS_ready=dcs_ctrl.out.ready;
	inv.in.DCS_running=dcs_ctrl.out.running;

	inv.in.cmd_pow_on			= cmd_logic.cmd.cmd_pow_on;
	inv.in.cmd_pow_off			= cmd_logic.cmd.cmd_pow_off;
	inv.in.cmd_trip_reset		= (cmd_logic.cmd.cmd_trip_reset||apl_protect.AR1.trip_reset);
	inv.in.cmd_pulses_on		= (cmd_logic.cmd.cmd_pulses_on||apl_protect.AR1.pulses_on);
	inv.in.cmd_pulses_off		= cmd_logic.cmd.cmd_pulses_off;

	inv.in.CS_ready  = 	fan_dctrl.ready; //ToDo OK pass ready from fan module
	inv.in.CB_ready	 =	1; //ToDo always ready

	dio_logic.calc(&dio_logic); //Обработка команд управления


	dcs_ctrl.cmd_run = inv.out.cmd_DCS_run;
	dcs_ctrl.cmd_stop = inv.out.cmd_DCS_stop;
	dcs_ctrl.cmd_trip_reset = inv.out.cmd_DCS_trip_reset;
	dcs_ctrl.cmd_set_mode = inv.out.cmd_DCS_set_mode;

	dcs_refs.P_ref = cmd_logic.refs.P_ref;

	//dcs_ctrl.ms_calc(&dcs_ctrl);


	RTCclock.msCalc(&RTCclock);//часы

	global_time.ms_calc(&global_time);




}



/**************************************************************************************************
 *
 * @param p
 **************************************************************************************************/
void SM_Sys_Slow_Calc(TSM_Sys *p) {



	RTCclock.slowCalc(&RTCclock);//часы реального времени

	MBVarsConv.Vars._0259_PV_Voltage = _IQmpy(adc.Udc,inv_params.Udc_nom)>>16;
	MBVarsConv.Vars._025C_DC_Isolation_Resistor=can_io.Riso*10;
	MBVarsConv.Vars._025A_PV_Current=(_IQmpy(adc.Idc,inv_params.I_nom)>>16)*10;
	MBVarsConv.Vars._025B_PV_Power=(_IQmpy(cur_par.Pdc,inv_params.Pdc_nom)>>16)*10;
	MBVarsConv.Vars._02BD_AmbientAirTemp=(adc.T3>>4)*10;
	MBVarsConv.Vars._02BF_InvFrequency=_IQtoF(cur_par.Freq*50.0)*10.0;
	MBVarsConv.Vars._02C0_InvVoltL1_L2=_IQmpy(adc.rms.Uab_inv,inv_params.U_nom)>>16;
	MBVarsConv.Vars._02C1_InvVoltL2_L3=_IQmpy(adc.rms.Ubc_inv,inv_params.U_nom)>>16;
	MBVarsConv.Vars._02C2_InvVoltL3_L1=_IQmpy(adc.rms.Uca_inv,inv_params.U_nom)>>16;
	MBVarsConv.Vars._02C3_InvCurrentL1=(_IQmpy(adc.rms.Ia_inv,inv_params.I_nom)>>16)*10;
	MBVarsConv.Vars._02C4_InvCurrentL2=(_IQmpy(adc.rms.Ib_inv,inv_params.I_nom)>>16)*10;
	MBVarsConv.Vars._02C5_InvCurrentL3=(_IQmpy(adc.rms.Ic_inv,inv_params.I_nom)>>16)*10;
	MBVarsConv.Vars._02C7_InvTotalTruePower=(_IQmpy(cur_par.Pac,inv_params.P_nom)>>16)*10;
	//if(cur_par.Qac>2147483648)
	//MBVarsConv.Vars._02C8_InvTotalReactivePower=((4.046875*(cur_par.Qac-8589934592))/16777216)*10;
	//else
	MBVarsConv.Vars._02C8_InvTotalReactivePower=(_IQmpy(cur_par.Qac,inv_params.P_nom)>>16)*10;
	//MBVarsConv.Vars._02C8_InvTotalReactivePower=(_IQmpy(cur_par.Qac,inv_params.P_nom)>>16);

	MBVarsConv.Vars._02C6_InvTotalApparentPower=(_IQmpy(cur_par.S,inv_params.P_nom)>>16)*10;//(_IQsqrt(_IQmpy(_IQmpy(cur_par.Pac,inv_params.P_nom),_IQmpy(cur_par.Pac,inv_params.P_nom))+_IQmpy(_IQmpy(cur_par.Qac,inv_params.P_nom),_IQmpy(cur_par.Qac,inv_params.P_nom)))>>16)*10;

	MBVarsConv.Vars._0321_GridFrequency=((int)(_IQtoF(cur_par.Freq*50.0)*100))/10.0f;
	MBVarsConv.Vars._0322_GridVoltL1_L2=_IQmpy(adc.rms.Uab_tr,inv_params.U_nom)>>16;
	MBVarsConv.Vars._0323_GridVoltL2_L3=_IQmpy(adc.rms.Ubc_tr,inv_params.U_nom)>>16;
	MBVarsConv.Vars._0324_GridVoltL3_L1=_IQmpy(adc.rms.Uca_tr,inv_params.U_nom)>>16;
	MBVarsConv.Vars._02C9_DayEnergy=_IQmpy(adc.Edc_day,inv_params.Pdc_nom)>>16;
	MBVarsConv.Vars._02CA_TotalEnergy=(int16) adc.Edc_total;
	MBVarsConv.Vars._02CB_TotalEnergy2=(int16) adc.Edc_total;

//	if(cur_par.Pac==0)
//		MBVarsConv.Vars._02BE_CosPhi=0;
//	else
	MBVarsConv.Vars._02BE_CosPhi=(cur_par.cos_fi>>16)*100/255.0f;//cos(atan(MBVarsConv.Vars._02C8_InvTotalReactivePower/MBVarsConv.Vars._02C7_InvTotalTruePower))*100;


	MBVarsConv.Vars._074_RealTime[0]=((RTCclock.second/10)<<12)|((RTCclock.second%10)<<8)|((RTCclock.minute/10)<<4)|((RTCclock.minute%10));//0x0102;//секунды-минуты
	MBVarsConv.Vars._074_RealTime[1]=((RTCclock.hour/10)<<12)|((RTCclock.hour%10)<<8);//0x0304;//часы-день недели
	MBVarsConv.Vars._074_RealTime[2]=((RTCclock.day/10)<<12)|((RTCclock.day%10)<<8)|((RTCclock.month/10)<<4)|((RTCclock.month%10));//0x0506;//число-месяц
	MBVarsConv.Vars._074_RealTime[3]=(((RTCclock.year%100)/10)<<12)|(((RTCclock.year%100)%10)<<8)|((20/10)<<4)|((20%10));//0x0708;//19-20


	MBVarsConv.Vars._01F5_PV_Output_AC_Information=((dio_protect.bit_alarm1>>7)&1);
	MBVarsConv.Vars._01F6_PV_Output_AC_Warning=(((dio_protect.bit_alarm1>>2)&1)<<6)|(((dio_protect.bit_alarm1>>3)&1)<<1)|(((dio_protect.bit_alarm1>>4)&1))|(((dio_protect.bit_alarm1>>5)&1)<<2)|(((dio_protect.bit_alarm1>>6)&1)<<3)|(((dio_protect.bit_alarm1>>11)&1)<<4);
	MBVarsConv.Vars._00C9_InverterVoltageNom=255;
	MBVarsConv.Vars._00CA_InverterPowerNom=255;
	MBVarsConv.Vars._00CB_PVSystemOperation=1;
	MBVarsConv.Vars._00CF_GridFreqSetPointMax=515;
	MBVarsConv.Vars._00D0_GridFreqSetPointMin=475;
	MBVarsConv.Vars._00D1_GridVoltSetPointMax=306;
	MBVarsConv.Vars._00D2_GridVoltSetPointMin=204;


	//MBVarsConv.Vars._03F4_ReactivePowerSetPoint=0;
	//MBVarsConv.Vars._03F5_CosPhiSetPointOrBMS_Pref=0;
	MBVarsConv.Vars._03FA_TruePowerLimitPointRelease=1;

	MBVarsConv.Vars._012F_PV_Input_DC_Warning=(((dio_protect.bit_fault1>>2)&1))|(((dio_protect.bit_alarm1>>2)&1)<<6)|(((dio_protect.bit_fault1>>6)&1)<<8)|(((dio_protect.bit_alarm1)&1)<<11)|(((dio_protect.bit_alarm1>>1)&1)<<12);
	MBVarsConv.Vars._0192_PV_Inverter_Warning=(((dcs_prot.bit_fault1>>11)&1))|(((dio_protect.bit_alarm1>>15)&1)<<3)|(((dio_protect.bit_fault1>>3)&1)<<8)|(((dio_protect.bit_alarm1>>13)&1)<<10)|(((dio_protect.bit_alarm1>>8)&1)<<15)|(((dio_protect.bit_alarm1>>9)&1)<<15)|(((dio_protect.bit_alarm1>>10)&1)<<15)|(((dio_protect.bit_fault1>>9)&1)<<14);
    MBVarsConv.Vars._0194_PV_Inverter_Fault_SACK=(((dio_protect.bit_fault1>>10)&1));
    MBVarsConv.Vars._01F8_PV_Output_AC_Fault_SACK=(((dcs_prot.bit_fault1>>7)&1)<<5)|(((dio_protect.bit_fault1>>8)&1))|(((dio_protect.bit_fault1>>11)&1)<<1)|(((dio_protect.bit_fault1>>2)&1)<<2)|(((dio_protect.bit_fault1>>3)&1)<<3);
    switch(inv.status)
    {
    	case 2:
    	MBVarsConv.Vars._012D_Inverter_Operation_State=3;
    	break;
    	case 4:
    	MBVarsConv.Vars._012D_Inverter_Operation_State=7;
    	break;
    	case 5:
    	MBVarsConv.Vars._012D_Inverter_Operation_State=9;
    	break;
    	case 6:
    	MBVarsConv.Vars._012D_Inverter_Operation_State=5;
        break;
    	case 7:
    	MBVarsConv.Vars._012D_Inverter_Operation_State=4;
        break;
    	case 10:
    	MBVarsConv.Vars._012D_Inverter_Operation_State=8;
        break;
    	case 11:
        MBVarsConv.Vars._012D_Inverter_Operation_State=10;
        break;
    }

    MBVarsConv.Vars._01FE_PV_Cabinet_Door=(dio_protect.bit_alarm1>>7)&1;

    MBVarsConv.Vars._1100_diesel_ready = diesel.ready;
    MBVarsConv.Vars._1101_diesel_operating = diesel.operating;
    MBVarsConv.Vars._1102_I_diesel = _IQmpy(adc.I_diesel,inv_params.I_nom)>>16;
    MBVarsConv.Vars._1103_P_diesel = _IQmpy(adc.P_diesel,inv_params.Pdc_nom)>>16;
    MBVarsConv.Vars._1104_Profile = cmd_logic.status.profile;

	global_time.slow_calc(&global_time);

	dcs_ctrl.slow_calc(&dcs_ctrl);


	if (sw.Reboot & 1) { //команда перезагрузки
		sw.Reboot = 0; //сбрасываем её
		if (dcs_ctrl.state ==SM_DCS_CTRL_STOP) { //перезагружаемся только в останове
			//выполняем сброс проца
			//Перезагружает во флеш!
			propReset();
		}
	}

	//вызов расчета смещения АЦП для токов фаз
	//Делаем расчет только в останове и отсутствии аварии
	if ((sw.AutoOffset & 1) && (dcs_ctrl.state == SM_DCS_CTRL_STOP)){
		AutoOffset.Enabled=1;
	} else
		AutoOffset.Enabled=0;

}
/*@}*/

