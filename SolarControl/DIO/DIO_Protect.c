#ifndef MODEL

//#include "DSP.h"
#include "main.h"
//#include "stdlib.h"
#include "dio_func.h"
#endif



void DIO_Protect_Init(TDIO_PROTECT *p) {
	p->state_prev = 0xff;
	p->state = 0x00;

	p->mask_fault_pwm1=0xffff;
	p->mask_fault_off=0xffff; //TDOO 206 все защиты автоматики должны отключать инвертора.
							  //иначе см dio_logic_inv  if ((inv.in.cmd_protect_pow_off!=0)) 	//TODO 206 - was ||(inv.in.cmd_protect_pwm_off!=0))
							  //inv.state = SM_DIO_LOGIC_INV_FAULT;
}

int cntrtest=0;
void DIO_Protect_ms_Calc(TDIO_PROTECT *p){


	if (aux_K7.bk_fail) p->bit_fault1|=P_K7_BK_FAIL;
	if (aux_Q4.bk_fail) p->bit_fault1|=P_Q4_BK_FAIL;
    if (aux_Q6.bk_fail) p->bit_fault1|=P_Q6_BK_FAIL;
    //if (aux_Q26.bk_fail) p->bit_fault1|=P_Q26_BK_FAIL;

    if (aux_K91.bk_fail) p->bit_fault1|=P_K91_BK_FAIL;

	if (aux_K7.switch_fail) p->bit_fault1|=P_K7_SW_FAIL;
	if (aux_Q4.switch_fail) p->bit_fault1|=P_Q4_SW_FAIL;
	if (aux_Q6.switch_fail) p->bit_fault1|=P_Q6_SW_FAIL;
	//if (aux_Q26.switch_fail) p->bit_fault1|=P_Q26_SW_FAIL;

	if (aux_K91.switch_fail) p->bit_fault1|=P_K91_SW_FAIL;


//	if (sc_profile.profile == SM_PROFILE_ISLA_BATT_DIESEL && DebugW3 == 0)
//	if (vacuum.fail) p->bit_fault1|=P_BMS_PROTECTION;

	if(((adc.T3)>(adc.T1_inv1+80))||((adc.T3)>(adc.T2_inv1+80))||((adc.T3)>(adc.T3_inv1+80)))
		p->bit_fault1|=P_DIFF_TEMP;
	else
		p->bit_fault1&=~P_DIFF_TEMP;



	if(pll.fs >_IQ(1.03)&&inv.state==5)
		p->bit_fault1|=P_OVER_FREQUENCY_GRID;
	else
		p->bit_fault1&=~P_OVER_FREQUENCY_GRID;

	if(pll.fs < _IQ(0.95)&&inv.state==5)
			p->bit_fault1|=P_UNDER_FREQUENCY_GRID;
	else
		p->bit_fault1&=~P_UNDER_FREQUENCY_GRID;



//#define A_ISOLATION_LEVEL1			0x0001
//#define A_ISOLATION_LEVEL2			0x0002
//#define A_OPN_DC					0x0004
//#define A_OPN_AC					0x0008
//#define A_K60_FAIL					0x0010
//#define A_F60_FAIL					0x0020
//#define A_F61_FAIL					0x0040
//#define A_DOOR_OPEN					0x0080
//#define A_CAN_IO_1_NO_LINK			0x0100
//#define A_CAN_IO_2_NO_LINK			0x0200
//#define A_CAN_IO_3_NO_LINK			0x0400


	//ADD2 when dcdc signals about HW protection we call alarm to show on HMI
	if (dcdc.regs.stat_protect_Q_off==1) p->bit_alarm1|=A_DCDC_EXT_PROTECTION;


	if(cntrtest>1000)
	{
	if (can_io.link1!=1) p->bit_alarm1|=A_CAN_IO_1_NO_LINK; else p->bit_alarm1&=~A_CAN_IO_1_NO_LINK;
	if (can_io.link2!=1) p->bit_alarm1|=A_CAN_IO_2_NO_LINK; else p->bit_alarm1&=~A_CAN_IO_2_NO_LINK;
	if (can_io.link3!=1) p->bit_alarm1|=A_CAN_IO_3_NO_LINK; else p->bit_alarm1&=~A_CAN_IO_3_NO_LINK;
	if (can_io.F60_aux!=1) p->bit_alarm1|=A_F60_FAIL; else p->bit_alarm1&=~A_F60_FAIL;
	if (can_io.K60_aux==1) p->bit_alarm1|=A_K60_FAIL; else p->bit_alarm1&=~A_K60_FAIL;
	if (can_io.F61_aux!=1) p->bit_alarm1|=A_F61_FAIL; else p->bit_alarm1&=~A_F61_FAIL;
	if (can_io.S100200300==0) p->bit_alarm1 |=A_DOOR_OPEN; else p->bit_alarm1&=~A_DOOR_OPEN;

	if (can_io.bender_iso_inp1==0) p->bit_alarm1|=A_ISOLATION_LEVEL1; else p->bit_alarm1&=~A_ISOLATION_LEVEL1;
	if (can_io.bender_iso_inp2==0) p->bit_alarm1|=A_ISOLATION_LEVEL2; else p->bit_alarm1&=~A_ISOLATION_LEVEL2;
	if (can_io.opn_DC==1) p->bit_alarm1|=A_OPN_DC; else p->bit_alarm1&=~A_OPN_DC;
	if (can_io.opn_AC==0) p->bit_alarm1|=A_OPN_AC; else p->bit_alarm1&=~A_OPN_AC;

	if (can_io.Q26_aux==1) p->bit_alarm1|=A_Q26_OFF; else p->bit_alarm1&=~A_Q26_OFF;

	if (fan_spec.fail)	p->bit_alarm1|=A_FAN_FAIL;  else p->bit_alarm1&=~A_FAN_FAIL;

	if ((adc.T1_inv1<(-10<<4))||(adc.T2_inv1<(-10<<4))||(adc.T3_inv1<(-10<<4))||(adc.T3<(-10<<4)))
		p->bit_alarm1|=A_TEMPERATURE_LO;
	else
		p->bit_alarm1&=~A_TEMPERATURE_LO;

	if ((adc.T3>(60<<4))||(adc.T4>(60<<4)))
			p->bit_alarm1|=A_TEMPERATURE_HI;
		else
			p->bit_alarm1&=~A_TEMPERATURE_HI;

	if (sc_profile.profile == SM_PROFILE_ISLA_BATT_DIESEL)
	{
		if (vacuum.fail == 1)
				p->bit_alarm1|=A_INV_MAX_ATTEMPTS;
			else
				p->bit_alarm1&=~A_INV_MAX_ATTEMPTS;
	}
	else
		p->bit_alarm1&=~A_INV_MAX_ATTEMPTS;


	}
	else
		cntrtest++;

	DINT; //Запрещение прерываний //Аварии, требующие полного останова
	p->masked_bit_fault1 = p->bit_fault1 & p->mask_fault_pwm1;//маскирование флагов аварийK7
	p->masked_fault_off = p->masked_bit_fault1 & p->mask_fault_off;//маскирование флагов аварийQ4


	EINT;      //Разрешение прерываний

	//NOTE!!!
	//This SM is not used as protection logic controlled by APL
	//считаем дискретный автомат защит
	if (p->state_prev != p->state)  p->E = 1; else p->E = 0;
	p->state_prev = p->state;

	switch (p->state) {
	case SM_DIO_PROTECT_OFF: { //Защита выключена
		if (p->E == 1) {
			p->powered_okCounter=0;
		}

		//Обнуляем все аварии
		p->bit_fault1 = 0;

		//Пропускаем 100ms после включения контроллера
		//чтобы не ловить ложные срабатывания защит
		if (p->powered_okCounter++ > 100)  p->state = SM_DIO_PROTECT_ON;
		break;
	}

	case SM_DIO_PROTECT_ON:
		if (p->E == 1) {

		}

		if (p->masked_bit_fault1 != 0) p->state = SM_DIO_PROTECT_TRIP;

		break;


	case SM_DIO_PROTECT_TRIP:
		if (p->E == 1) {

		}

		if (p->trip_reset == 1) {
			p->state = SM_DIO_PROTECT_ON;
			p->bit_fault1 = 0;
			}

		break;
	default: break;

	} //end switch
}




void DIO_Protect_Slow_Calc(TDIO_PROTECT *p) {


}

