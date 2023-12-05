

#include "DSP.h"
#include "HAL_drv.h"
#include "main.h"


HAL_SPI_MCP3208 mcp = HAL_SPI_MCP3208_DEFAULTS;

void HAL_init()
{
	HAL_SPI_MCP3208_init(&mcp);

	HAL_DIO_init();

	HAL_ADC_init();

// set initial values for temperature regs
mcp.adc_regs[0]=0x200;
mcp.adc_regs[1]=0x200;
mcp.adc_regs[2]=0x200;

mcp.adc_regs[4]=0x200;
mcp.adc_regs[5]=0x200;
mcp.adc_regs[6]=0x200;

mcp.adc_regs[10]=0x200;
mcp.adc_regs[11]=0x200;
mcp.adc_regs[12]=0x200;
mcp.adc_regs[13]=0x200;

}



void HAL_ms_update()
{
	HAL_SPI_MCP3208_update(&mcp); // this module should be uncommented
	switch (mcp.extra_mux) {
	case 0:
		NT_GPIOG->MASKLOWBYTE_bit[(1<<0)].MASKLB=(0<<0);
		NT_GPIOE->MASKLOWBYTE_bit[(1<<0)].MASKLB=(0<<0);
	break;
	case 1:
		NT_GPIOG->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0);
		NT_GPIOE->MASKLOWBYTE_bit[(1<<0)].MASKLB=(0<<0);
	break;
	case 2:
		NT_GPIOG->MASKLOWBYTE_bit[(1<<0)].MASKLB=(0<<0);
		NT_GPIOE->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0);
	break;
	case 3:
		NT_GPIOG->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0);
		NT_GPIOE->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0);
	break;
	} //end switch mcp.extra_mux

	adc.regs.T1_inv1_reg16=mcp.adc_regs[0];
	adc.regs.T2_inv1_reg16=mcp.adc_regs[1];
	adc.regs.T3_inv1_reg16=mcp.adc_regs[2];


	adc.regs.T3_inv2_reg16=mcp.adc_regs[4];
	adc.regs.T1_inv2_reg16=mcp.adc_regs[5];
	adc.regs.T2_inv2_reg16=mcp.adc_regs[6];


	adc.regs.T2_reg16=mcp.adc_regs[10];
	adc.regs.T3_reg16=mcp.adc_regs[11];
	adc.regs.T1_reg16=mcp.adc_regs[12];
	adc.regs.T4_reg16=mcp.adc_regs[13];
	adc.regs.U_fan_ref_reg16=mcp.adc_regs[14];
	adc.regs.U_fan_fdb_reg16=mcp.adc_regs[15];

//	adc.T1=adc.regs.T1_reg16;
//	adc.T2=adc.regs.T2_reg16;
//	adc.T3=adc.regs.T3_reg16;
//	adc.T4=adc.regs.T4_reg16;
//
//	adc.T1_inv1=adc.regs.T1_inv1_reg16;
//	adc.T2_inv1=adc.regs.T2_inv1_reg16;
//	adc.T3_inv1=adc.regs.T3_inv1_reg16;
//
//	adc.T1_inv2=adc.regs.T1_inv2_reg16;
//	adc.T2_inv2=adc.regs.T2_inv2_reg16;
//	adc.T3_inv2=adc.regs.T3_inv2_reg16;


}

void HAL_DIO_init()
{
	//Для каждой дискретной ножки нужно:
	//1)Выключить привязанные к этой ножке спецфункции путем сброса соответствующего бита в регистре спецфункций порта.
	//Для сброса бита нужно записать "1" в соответствующий бит регистра ALTFUNCCLR (CLR - clear - очистить).
	//Если нужно наоборот включить спецфункцию, то следует записать "1" в соответствующий бит регистра ALTFUNCSET (SET - установить).
	//Прочитать текущее состояние регистра спецфункций порта можно, прочитав любой из двух регистров ALTFUNCCLR или ALTFUNCSET.
	//2)Разрешить ножке работать на вывод путем записи "1" в соответствующий бит регистра OUTENSET.
	//NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 2);
	//NT_GPIOC->OUTENSET_bit.OUTENSET |= (1 << 2);

	//rel_cmd1 //B6
	NT_GPIOB->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 6);
	NT_GPIOB->OUTENSET_bit.OUTENSET |= (1 << 6);


	//rel_cmd2 //B15
	NT_GPIOB->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 15);
	NT_GPIOB->OUTENSET_bit.OUTENSET |= (1 << 15);

	//rel_cmd3 //B4
	NT_GPIOB->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 4);
	NT_GPIOB->OUTENSET_bit.OUTENSET |= (1 << 4);

	//rel_cmd4 //B5
	NT_GPIOB->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 5);
	NT_GPIOB->OUTENSET_bit.OUTENSET |= (1 << 5);

	//DI_7		//A14
	NT_GPIOA->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 14);
	//NT_GPIOA->OUTENSET_bit.OUTENSET |= (1 << 14);

	//DI_6		//A15
	NT_GPIOA->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 15);
	//NT_GPIOA->OUTENSET_bit.OUTENSET |= (1 << 15);

	//FAN_spd_cmd	//A10
	NT_GPIOA->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 10);
	NT_GPIOA->OUTENSET_bit.OUTENSET |= (1 << 10);


	//FAN2_spd_cmd	//G1
	NT_GPIOG->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 1);
	NT_GPIOG->OUTENSET_bit.OUTENSET |= (1 << 1);

	//DI_2 //C6
	NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 6);
	//NT_GPIOC->OUTENSET_bit.OUTENSET |= (1 << 6);

	//DI_1 //E3
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 13);
	//NT_GPIOE->OUTENSET_bit.OUTENSET |= (1 << 13);

	//DI_3 //E8
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 8);
	//NT_GPIOE->OUTENSET_bit.OUTENSET |= (1 << 8);

	//DI_4 //E9
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 9);
	//NT_GPIOE->OUTENSET_bit.OUTENSET |= (1 << 9);

	//DO_3coil   //E11
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 11);
	NT_GPIOE->OUTENSET_bit.OUTENSET |= (1 << 11);

	//DO_2coil   //E15
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 15);
	NT_GPIOE->OUTENSET_bit.OUTENSET |= (1 << 15);


	//DO_ext_adc_muxA //SDA0	//G0
	NT_GPIOG->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 0);
	NT_GPIOG->OUTENSET_bit.OUTENSET |= (1 << 0);

	//DO_ext_adc_muxB //SCL0 //E0
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 0);
	NT_GPIOE->OUTENSET_bit.OUTENSET |= (1 << 0);

	//DO_LED1 //QEP_A G10
	NT_GPIOG->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 10);
	NT_GPIOG->OUTENSET_bit.OUTENSET |= (1 << 10);
	//DO_LED2  //QEP_B G11
	NT_GPIOG->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 11);
	NT_GPIOG->OUTENSET_bit.OUTENSET |= (1 << 11);

	//i2_pow2 //CAP_PWM2 E6
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 6);
	//NT_GPIOG->OUTENSET_bit.OUTENSET |= (1 << 0);
	//i2_pow1 //CAP_PWM1 E5
	NT_GPIOE->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 5);
	//NT_GPIOG->OUTENSET_bit.OUTENSET |= (1 << 0);

	//i1_pow1 //A4
	NT_GPIOA->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 4);

	//i1_pow2 //B4
	NT_GPIOB->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 4);


	//LEDs on VECTORBoard H0(green), H7(green) A1(yellow) A0(red)

	NT_GPIOH->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 0);
	NT_GPIOH->OUTENSET_bit.OUTENSET |= (1 << 0);

	NT_GPIOH->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 7);
	NT_GPIOH->OUTENSET_bit.OUTENSET |= (1 << 7);

	NT_GPIOA->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 0);
	NT_GPIOA->OUTENSET_bit.OUTENSET |= (1 << 0);

	NT_GPIOA->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 1);
	NT_GPIOA->OUTENSET_bit.OUTENSET |= (1 << 1);

	//Buttons on on Vector board D10 D11
	NT_GPIOD->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 10);
	NT_GPIOD->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 11);

}

void HAL_DIO_write(HAL_DIO*p) {
//#define VD1_ON NT_GPIOC->MASKLOWBYTE_bit[8].MASKLB = 0			//NT_GPIOC->DATA &= ~(1 << 3)
//#define VD1_OFF NT_GPIOC->MASKLOWBYTE_bit[8].MASKLB = 8			//NT_GPIOC->DATA |= (1 << 3)

	//rel_cmd1 //B6
	if (p->rel_cmd1) NT_GPIOB->MASKLOWBYTE_bit[(1<<6)].MASKLB=(1<<6); else NT_GPIOB->MASKLOWBYTE_bit[(1<<6)].MASKLB = 0;

	//rel_cmd2 //B15
	if (p->rel_cmd2) NT_GPIOB->MASKHIGHBYTE_bit[(1<<(15-8))].MASKHB=(1<<(15-8)); else NT_GPIOB->MASKHIGHBYTE_bit[(1<<(15-8))].MASKHB = 0;

	//rel_cmd3 //B4
	if (p->rel_cmd3) NT_GPIOB->MASKLOWBYTE_bit[(1<<4)].MASKLB=(1<<4); else NT_GPIOB->MASKLOWBYTE_bit[(1<<4)].MASKLB = 0;

	//rel_cmd4 //B5
	if (p->rel_cmd4) NT_GPIOB->MASKLOWBYTE_bit[(1<<5)].MASKLB=(1<<5); else NT_GPIOB->MASKLOWBYTE_bit[(1<<5)].MASKLB = 0;


	//FAN_spd_cmd	//A10
	if (p->FAN_spd_cmd) NT_GPIOA->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB=(1<<(10-8)); else NT_GPIOA->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB = 0;

	//FAN2_spd_cmd	//G1
	if (p->FAN2_spd_cmd) NT_GPIOG->MASKLOWBYTE_bit[(1<<1)].MASKLB=(1<<1); else NT_GPIOG->MASKLOWBYTE_bit[(1<<1)].MASKLB = 0;

	//DO_3coil   //E11
	if (p->DO_3coil) NT_GPIOE->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB=(1<<(11-8)); else NT_GPIOE->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB = 0;

	//DO_2coil   //E15
	if (p->DO_2coil) NT_GPIOE->MASKHIGHBYTE_bit[(1<<(15-8))].MASKHB=(1<<(15-8)); else NT_GPIOE->MASKHIGHBYTE_bit[(1<<(15-8))].MASKHB = 0;

	//DO_ext_adc_muxA //SDA0	//G0 ToDo OK eclude this part, it is controlled by MCP3208 only
	//if (p->DO_ext_adc_muxA) NT_GPIOG->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0); else NT_GPIOG->MASKLOWBYTE_bit[(1<<0)].MASKLB = 0;

	//DO_ext_adc_muxB //SCL0 //E0
	//if (p->DO_ext_adc_muxB) NT_GPIOE->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0); else NT_GPIOE->MASKLOWBYTE_bit[(1<<0)].MASKLB = 0;

	//DO_LED1 //QEP_A G10
	if (p->DO_EXT_LED1) NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB=(1<<(10-8)); else NT_GPIOG->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB = 0;

	//DO_LED2  //QEP_B G11
	if (p->DO_EXT_LED2) NT_GPIOG->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB=(1<<(11-8)); else NT_GPIOG->MASKHIGHBYTE_bit[(1<<(11-8))].MASKHB = 0;



	//LEDs on VECTORBoard H0(green), H7(green) A1(yellow) A0(red)
	//if (p->DO_LED1) NT_GPIOH->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0); else NT_GPIOH->MASKLOWBYTE_bit[(1<<0)].MASKLB = 0;
	//if (p->DO_LED2) NT_GPIOH->MASKLOWBYTE_bit[(1<<7)].MASKLB=(1<<7); else NT_GPIOH->MASKLOWBYTE_bit[(1<<7)].MASKLB = 0;
	if (p->DO_LED1) NT_GPIOA->MASKLOWBYTE_bit[(1<<0)].MASKLB=(1<<0); else NT_GPIOA->MASKLOWBYTE_bit[(1<<0)].MASKLB = 0;
	if (p->DO_LED2) NT_GPIOA->MASKLOWBYTE_bit[(1<<1)].MASKLB=(1<<1); else NT_GPIOA->MASKLOWBYTE_bit[(1<<1)].MASKLB = 0;



}

void HAL_DIO_read(HAL_DIO*p) {

int data_temp_A;
int data_temp_B;
int data_temp_C;
int data_temp_D;
int data_temp_E;

data_temp_A=NT_GPIOA->DATA_bit.DATA;
data_temp_B=NT_GPIOB->DATA_bit.DATA;
data_temp_C=NT_GPIOC->DATA_bit.DATA;
data_temp_D=NT_GPIOD->DATA_bit.DATA;
data_temp_E=NT_GPIOE->DATA_bit.DATA;

		//DI_2 //C6
	p->DI_2=((data_temp_C>>6)&0x1);

		//DI_1 E3
	p->DI_1=((data_temp_E>>3)&0x1);

		//DI_3 //E8
	p->DI_3=((data_temp_E>>8)&0x1);

		//DI_4 //E9
	p->DI_4=((data_temp_E>>9)&0x1);

	p->DI_7=((data_temp_A>>14)&0x1);		//A14 FAN2_spd_in

	p->DI_6=((data_temp_A>>15)&0x1);		//A15 FAN2_spd_in


	p->i1_pow1=((data_temp_A>>4)&0x1); //A4

	p->i1_pow2=((data_temp_B>>4)&0x1); //b4

	p->i2_pow2=((data_temp_E>>6)&0x1); //CAP_PWM2 E6

	p->i2_pow1=((data_temp_E>>5)&0x1); //CAP_PWM1 E5

	//Buttons on Vector board D10 D11
	p->DI_btn1 = (~data_temp_D>>10)&0x1;
	p->DI_btn2 = (~data_temp_D>>11)&0x1;




}
//! Настраиваются секвенсоры и тип оцифровки данных. каналы для оцифровки, частота.
//! В данном случае оцифровка происходит по событию таймера,частота которого
//! равна частоте ШИМ, чтобы измерять ровно посередине периода ШИМ (требуется для шунтовых
//! датчиков тока)
//Запуск оцифровки производится по таймеру NT_PWM3, который синхронизирован с другими таймерами ШИМ.
//Оцифрованные измерения складываются в ФИФО. Каждый канал АЦП настроен на отдельный секвенсор с ФИФО длиной до 16 измерений.
//В прерывании с частотой 10 кГц данные забираются из ФИФО и складываются в кольцевые массивы (старые затираются новыми).
//В том же прерывании из кольцевого массива берется N последних точек и из них вычисляется среднее арифметическое.
//Число выборок для усреднения N зависит от частоты ШИМ и равна Fшим/10кГц. Если частоты ШИМ меньше 10 кГц, то берется одна выборка, если больше 40 кГц - 4 выборки.
//К вычисленному среднему значению добавляется калибровочный сдвиг, и оно умножается на коэффициент измерения, в результате получается окончательный результат измерения.

//! \memberof TAdcDrv
void HAL_ADC_init() {

#ifndef MODEL
	// Запрет всех секвенсоров
	int ii;
	NT_ADC->ACTSS = 0;

	// Сброс счётчиков прерываний и измерений
	NT_ADC->SEQ[0].OP = 0;
	NT_ADC->SEQ[1].OP = 0;
	NT_ADC->SEQ[2].OP = 0;
	NT_ADC->SEQ[3].OP = 0;
	NT_ADC->SEQ[4].OP = 0;
	NT_ADC->SEQ[5].OP = 0;
	NT_ADC->SEQ[6].OP = 0;
	NT_ADC->SEQ[7].OP = 0;

	//Включаем 2, 3 и 4 секвенсоры, по одному на измеряемую величину (длина фифо каждого - 16 ячеек)
	//Примечание – Рекомендуется использовать только один секвенсор, либо несколько, но работающих синхронно (одинаковые события запуска, одинаковые задержки перезапуска измерений).
	NT_ADC->ACTSS_bit.ASEN0 = 1; //включая секвенсор он срабатывает при нуле pwm0
	//NT_ADC->ACTSS_bit.ASEN1 = 1; //включая секвенсор он срабатывает при периоде pwm1
//	NT_ADC->ACTSS_bit.ASEN2 = 1;
//	NT_ADC->ACTSS_bit.ASEN3 = 1;
//	NT_ADC->ACTSS_bit.ASEN4 = 1;
//	NT_ADC->ACTSS_bit.ASEN5 = 1;
//	NT_ADC->ACTSS_bit.ASEN6 = 1;
//	NT_ADC->ACTSS_bit.ASEN7 = 1;

	//Ставим маску прерывания (долько для четвертока секвенсора, нам не надо 3 прерывания, достаточно одного)
	//NT_ADC->IM_bit.MASK0 = 1;
	//NT_ADC->IM_bit.MASK1 = 1;

	//Настраиваем источник запуска

	NT_ADC->EMUX_bit.EM0 = 6; //запуск производится по команде SocA  Блока ШИМ 0 energy19
//	NT_ADC->EMUX_bit.EM1 = 7; //запуск производится по команде SocA  Блока ШИМ 1 energy19
//	NT_ADC->EMUX_bit.EM2 = 8; //запуск производится по команде SocA  Блока ШИМ 3 для vector card
//	NT_ADC->EMUX_bit.EM3 = 8; //запуск производится по команде SocA  Блока ШИМ 3 для vector card
//	NT_ADC->EMUX_bit.EM4 = 8; //запуск производится по команде SocA  Блока ШИМ 3 для vector card
//	NT_ADC->EMUX_bit.EM5 = 8; //запуск производится по команде SocA  Блока ШИМ 3 для vector card
//	NT_ADC->EMUX_bit.EM6 = 8; //запуск производится по команде SocA  Блока ШИМ 3 для vector card
//	NT_ADC->EMUX_bit.EM7 = 8; //запуск производится по команде SocA  Блока ШИМ 3 для vector card

//	NT_ADC->PSSI_bit.SS0 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS1 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS2 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS3 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS4 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS5 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS6 = 1; //разрешить программный запуск секвенсора
//	NT_ADC->PSSI_bit.SS7 = 1; //разрешить программный запуск секвенсора

	//Регистры фаз запуска модулей АЦП SPC0-SPC5 // ADC will start converstion without phase shift 0 delay
	NT_ADC->SPC0=0;NT_ADC->SPC1=0;NT_ADC->SPC2=0;NT_ADC->SPC3=0;NT_ADC->SPC4=0;NT_ADC->SPC5=0;

	//Настраиваем количество перезапусков секвенсора
	//for (ii=0;ii<2;ii++)
	NT_ADC->SEQ[0].CTL_bit.RCNT = 0; //Делаем 1 измерения на периоде 8кГц Перезапуск не требуется
	//NT_ADC->SEQ[1].CTL_bit.RCNT = 0; //Делаем 1 измерения на периоде 8кГц Перезапуск не требуется

	//Настраиваем частоту прерываний
	//for (ii=0;ii<8;ii++)
	NT_ADC->SEQ[0].CTL_bit.ICNT = 0; //Прерывания после каждого запуска
	//NT_ADC->SEQ[1].CTL_bit.ICNT = 0; //Прерывания после каждого запуска

	NT_ADC->SEQ[0].TMR_bit.TMR=0;//375; // 4 измерения на 8кГц = 32кГЦ  Настройка тактирования АЦП 12 МГц, значит 12000/32= 375
	//NT_ADC->SEQ[1].TMR_bit.TMR=0;//375; // 4 измерения на 8кГц = 32кГЦ  Настройка тактирования АЦП 12 МГц, значит 12000/32= 375

	for (ii=0;ii<12;ii++)
		NT_ADC->PP_bit[ii].OM = 0x3; //12 bit ADC unipolar,  OM2-OM0 = ’011’ All blocks active (ADC plus internal buffers plus internal bandgap).

	//Включаем необходимые модули АЦП
	//Настраиваем разрешающую способность модуля АЦП
	for (ii=0;ii<12;ii++)
	NT_ADC->PP_bit[ii].ENA = 1;	//Включаем модуль АЦП

											// index 1 is inceverter, and index 2 is trafo side
	//comparators are disabled
//	NT_ADC->DCCTL_bit[0].CHNL =  0;			//Udc_adc
//	NT_ADC->DCCTL_bit[2].CHNL =  2;			//U1_BC_adc
//	NT_ADC->DCCTL_bit[4].CHNL =  4;			//U1_AC_adc
//	NT_ADC->DCCTL_bit[6].CHNL =  6;			//U1_NC_adc
//	NT_ADC->DCCTL_bit[8].CHNL =  8;			//U2_BC_adc
//	NT_ADC->DCCTL_bit[10].CHNL = 10;		//U2_AC_adc
//	NT_ADC->DCCTL_bit[12].CHNL = 12;		//U2_NC_ADC
//	NT_ADC->DCCTL_bit[14].CHNL = 14;		//I1_C_adc
//	NT_ADC->DCCTL_bit[16].CHNL = 16;		//I1_B_adc
//	NT_ADC->DCCTL_bit[18].CHNL = 18;		//I1_A_adc
//	NT_ADC->DCCTL_bit[20].CHNL = 20;		//Idc_adc
//	NT_ADC->DCCTL_bit[22].CHNL = 22;		//0p75V_adc
//
//	NT_ADC->DCCTL_bit[9].CHNL =  9;			//I2_C_adc from trafo side
//	NT_ADC->DCCTL_bit[11].CHNL =  11;		//I2_B_adc
//	NT_ADC->DCCTL_bit[13].CHNL =  13;		//I2_A_adc
//	NT_ADC->DCCTL_bit[15].CHNL =  15;		//I2_C
//	NT_ADC->DCCTL_bit[17].CHNL =  17;		//I2_B
//	NT_ADC->DCCTL_bit[19].CHNL =  19;		//I2_A
//
//	NT_ADC->DCCTL_bit[23].CHNL =  23;		//I_REF_PWM_adc

	//разрешение работы компараторов
//	NT_ADC->SEQ[0].DCP_bit.CMP1 = 1;
//	NT_ADC->SEQ[1].DCP_bit.CMP2 = 1;
//	NT_ADC->SEQ[2].DCP_bit.CMP3 = 1;
//	NT_ADC->SEQ[3].DCP_bit.CMP4 = 1;
//	NT_ADC->SEQ[4].DCP_bit.CMP5 = 1;
//	NT_ADC->SEQ[5].DCP_bit.CMP6 = 1;
//	NT_ADC->SEQ[6].DCP_bit.CMP7 = 1;
//	NT_ADC->SEQ[7].DCP_bit.CMP8 = 1;

	//выбор каналов для измерений //Sequenser #0 starts all channel
	//NT_ADC->SEQ[0].MUX_bit.CH0 = 1;	//Udc

	NT_ADC->SEQ[0].MUX_bit.CH0=1;	NT_ADC->SEQ[0].MUX_bit.CH1=0;	//Udc			--- x
	NT_ADC->SEQ[0].MUX_bit.CH2=1;	NT_ADC->SEQ[0].MUX_bit.CH3=0;	//U1_BC			--- x
	NT_ADC->SEQ[0].MUX_bit.CH4=1;	NT_ADC->SEQ[0].MUX_bit.CH5=0;	//U1_AC			--- x
	NT_ADC->SEQ[0].MUX_bit.CH6=1;	NT_ADC->SEQ[0].MUX_bit.CH7=0; 	//U1_NC			--- x
	NT_ADC->SEQ[0].MUX_bit.CH8=1;	NT_ADC->SEQ[0].MUX_bit.CH9=1;	//U2_BC 		---I2_C
	NT_ADC->SEQ[0].MUX_bit.CH10=1;	NT_ADC->SEQ[0].MUX_bit.CH11=1;	//U2_AC			---I2_B
	NT_ADC->SEQ[0].MUX_bit.CH12=1;	NT_ADC->SEQ[0].MUX_bit.CH13=1;	//U2_NC			---I2_A
	NT_ADC->SEQ[0].MUX_bit.CH14=1;	NT_ADC->SEQ[0].MUX_bit.CH15=0;	//I1_C			---I2_C
	NT_ADC->SEQ[0].MUX_bit.CH16=1;	NT_ADC->SEQ[0].MUX_bit.CH17=0;	//I1_B			---I2_B
	NT_ADC->SEQ[0].MUX_bit.CH18=1;	NT_ADC->SEQ[0].MUX_bit.CH19=0;	//I1_A			---I2_A
	NT_ADC->SEQ[0].MUX_bit.CH20=1;	NT_ADC->SEQ[0].MUX_bit.CH21=0;	//Idc			--- x
	NT_ADC->SEQ[0].MUX_bit.CH22=1;	NT_ADC->SEQ[0].MUX_bit.CH23=1;	//0.75V			--- IREFPWM
																	//TOTAL 12+4 = 16 measurements


	//NT_ADC->SEQ[0].MUX=0xFFFFFF;



#endif







}


//!Расчет АЦП с частотой основного расчета всей системы управления (обычно 10кГц).


volatile int reg_FLOAD;
volatile unsigned short reg_DATA[32];
volatile int reg_counter=0;

void HAL_ADC_calc(HAL_ADC*p) {

#ifndef MODEL
// ЭТА ЧАСТЬ HAL и должна быть расчитана в зависимости от аппаратуры


	while (NT_ADC->RIS_bit.INR0!=1)
		asm("nop");

	reg_FLOAD = NT_ADC->SEQ[0].FSTAT_bit.FLOAD;

	NT_ADC->ISC_bit.IN0=1;


	reg_counter=0;
	while (reg_FLOAD > 0)	//пока фифо не опустеет
	{	reg_DATA[reg_counter]=(NT_ADC->SEQ[0].FIFO_bit.DATA<<4); //this is a HAL task to receive and convert to 16 bit ADC format, so move left 4 bit
		reg_FLOAD = NT_ADC->SEQ[0].FSTAT_bit.FLOAD;

		reg_counter++;
		if (reg_counter>16)
			reg_counter=16;
//		//несколько точек из фифо измерений одного и того же
		//p->UdcBuf[p->UdcPointer] = NT_ADC->SEQ[0].FIFO_bit.DATA;
		//p->UdcPointer = (++p->UdcPointer) & 3;
	}



	p->regs.Udc_adc_reg=reg_DATA[0];
	p->regs.U1_BC_adc_reg=reg_DATA[1];
	p->regs.U1_AC_adc_reg=reg_DATA[2];
	p->regs.U1_NC_adc_reg=reg_DATA[3];

	p->regs.U2_BC_adc_reg=reg_DATA[4];
	p->regs.I2_C_adc_reg=reg_DATA[5];
	p->regs.U2_AC_adc_reg=reg_DATA[6];
	p->regs.I2_B_adc_reg=reg_DATA[7];
	p->regs.U2_NC_adc_reg=reg_DATA[8];
	p->regs.I2_A_adc_reg=reg_DATA[9];

	//TODO due to mistake in board switch chanel to original setting (A=2,B=3,C=1)
	p->regs.I1_C_adc_reg=reg_DATA[12]; //3 //was 10
			//p->regs.I2_C_adc_reg=reg_DATA[0];
	p->regs.I1_B_adc_reg=reg_DATA[10]; //2 //was 11
			//p->regs.I2_C_adc_reg=reg_DATA[0];
	p->regs.I1_A_adc_reg=reg_DATA[11]; //1 //was 12
			//p->regs.I2_C_adc_reg=reg_DATA[0];
	p->regs.Idc_adc_reg=reg_DATA[13];
	p->regs._0p75V_adc_reg=reg_DATA[14];
	p->regs.IREF_PWM_adc_reg=reg_DATA[15];


	//усреднялка
//	int i;
//	for (i = 0; i < p->SampleLength; i++) {//берем нужное число точек, начиная с самой новой
//		int j = p->Ia_invPointer - i;
//		if (j < 0)	//если перешли через 0 - начинаем с 3-й (массив из 4 точек)
//			j = 4 + j;
//		p->Ia_inv_temp += p->Ia_invBuf[j];
//	}
//	//делим на длину выборки (1-4 точки)
//	p->Ia_inv_temp = p->Ia_inv_temp / p->SampleLength;

//	for (i = 0; i < p->IBSampleLength; i++) {//берем нужное число точек, начиная с самой новой
//		int j = p->IBPointer - i;
//		if (j < 0)	//если перешли через 0 - начинаем с 3-й (массив из 4 точек)
//			j = 4 + j;
//		p->IB_temp += p->IBBuf[j];
//	}
//	//делим на длину выборки (1-4 точки)
//	p->IB_temp = p->IB_temp / p->IBSampleLength;
//
//	for (i = 0; i < p->UdcSampleLength; i++) {//берем нужное число точек, начиная с самой новой
//		int j = p->UdcPointer - i;
//		if (j < 0)	//если перешли через 0 - начинаем с 3-й (массив из 4 точек)
//			j = 4 + j;
//		p->Udc_temp += p->UdcBuf[j];
//	}
//	//делим на длину выборки (1-4 точки), получая колечную величину аналогового сигнала
//	p->Udc_temp = p->Udc_temp / p->UdcSampleLength;

	//p->Ia_inv = p->Ia_invGainNom*((p->Ia_inv_temp + p->Ia_inv_offset));
//	//комплект HW_VECTORCARD_DRV8312_EVM отличается от HW_VECTORCARD_DRV8301_EVM в 5 раз меньшим коэффициентом усиления и другим знаком
//	p->Imeas_a = p->IaGainNom * ((-(p->IA_temp/5) + p->Imeas_a_offset));
//	p->Imeas_b = p->IbGainNom * ((-(p->IB_temp/5) + p->Imeas_b_offset));
//	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
//	p->Imeas_c = -p->Imeas_a - p->Imeas_b;

//#if defined(HW_VECTORCARD_DRV8301_EVM) || defined(HW_VECTOR_MK_40_4)
//	p->Imeas_a = p->IaGainNom * ((p->IA_temp + p->Imeas_a_offset));
//	p->Imeas_b = p->IbGainNom * ((p->IB_temp + p->Imeas_b_offset));
//	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
//	p->Imeas_c = -p->Imeas_a - p->Imeas_b;
//#endif

#else
//#if (defined(HW_VECTORCARD_SIMULATOR)) || (defined(HW_NIIET_BOARD_SIMULATOR))
	//Симулятор формирует значения АЦП в диапазоне 0-4095
//	p->IA_temp=(int16) ((model.adc_code_iA<<4) ^ 0x8000);
//	p->IB_temp=(int16) ((model.adc_code_iB<<4) ^ 0x8000);
//	p->IC_temp=(int16) ((model.adc_code_iC<<4) ^ 0x8000);
//	p->ID_temp=(int16) ((model.adc_code_iD<<4) ^ 0x8000);
//	p->Udc_temp=model.adc_code_Udc;
//
//	p->Imeas_a = p->IaGainNom * ((p->IA_temp + p->Imeas_a_offset));
//	p->Imeas_b = p->IbGainNom * ((p->IB_temp + p->Imeas_b_offset));
//	p->Imeas_c = p->IcGainNom * ((p->IC_temp + p->Imeas_c_offset));
//
//	p->Imeas_d = p->IdGainNom * ((p->ID_temp + p->Imeas_d_offset));
//	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);


//#endif
#endif

//	adc.Ia_inv =
//	adc.Ib_inv =
//	adc.Ic_inv =
//
//	adc.Ia_tr =
//	adc.Ib_tr =
//	adc.Ic_tr =
//
//	adc.Ua_inv =
//	adc.Ub_inv =
//	adc.Uc_inv =
//
//	adc.Ua_tr =
//	adc.Ub_tr =
//	adc.Uc_tr =
//
//	adc.Idc_meas =
//	adc.Udc_meas =

}

//!Медленный расчет.

//!Занимается пересчетом коэффициентов, используемых в скоростной функции расчета,
//!чтобы не занимать процессорное время там. Находит коэффициенты,
//!на которые надо умножить полученное с АЦП значение, чтобы получить
//!относительные единицы с заданной базой.

//! Пример   p->PvalveGainNom=_IQ16mpy(p->Pvalve_gain,_IQ(1.0/100));
//! Pvalve_gain - значение в формате int. задается пользователем в UniCON.
//!Определяет, скольким процентам соответствует полный диапазон АЦП. В простейшем случае
//!равен 100. Т.е. когда на АЦП максимальный сигнал, это соответствует 100%.

//!_IQ(1.0/100) обратное значение для масштабирующего коэффициента. Так как величину процентов
//!естественнее всего перевести в относительные единицы так, что 100% соответствут 1.0,
//!то масштабирующий коэффициент (база) равен 100. Т.е. UniCON, прочитав из системы управления
//! число 1.0 в формате 8.24 должен умножить его на 100, чтобы отобразились проценты.
//! Здесь коэффициент задан явно как 1.0/100, но для ряда случаев базовое значение нужно менять.
//!Так, для токов фаз используется значение _1_I_nom, в формате 8.24, соответствующее единице деленной на
//базовое значение тока, например, 200 А. Так как в зависимости от мощности преобразователя базовый ток может меняться,
//то это значение, в отличие от процентов, сделано настраиваемым. Расчет _1_I_nom идет в другом месте, так как
//занимает много тактов расчета.

//Для беззнакового значения АЦП измеряет число от 0 до 65535. (16 разрядов, где заполнены верхние).
//Для примера с процентами необходимо сделать так, чтобы получилось результирующее значение в формате 8.24,
//где 1.0 это 65535. Таким образом, нужно сдвинуть число 65535 на 24-16=8 разрядов.
//Сдвиг на 8 разрядов - это умножение на число 255. Число 255 - это 1.0 в формате 24.8.

//Таким образом, PvalveGainNom - это коэффициент в формате 24.8. он получается в результате использования функции
//_IQ16mpy, аргумены которой Pvalve_gain (int) и 1.0/100 в формате 8.24. Функция IQ множения
//по сути представляет собой обычное оуможение в 64 разрядах со сдвигом результата вправо на Q разрядов.
//Т.е. _IQ16mpy умножает число в формате IQ24 9второй аргумент) на целочисленный коэффициент (первый аргумент),
//а потом сдвигате результат на 16 разрядов вправо.
//Так, в результате _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); получается целочисленное число 255, являющейся
//1.0 в формате 24.8 из-за сдвига на 16 разрядов вправо.

//Всё вышеприведенное мутево сделано с одной целью - увеличить производитлеьность обработки АЦП.



