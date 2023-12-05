

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
	//��� ������ ���������� ����� �����:
	//1)��������� ����������� � ���� ����� ����������� ����� ������ ���������������� ���� � �������� ����������� �����.
	//��� ������ ���� ����� �������� "1" � ��������������� ��� �������� ALTFUNCCLR (CLR - clear - ��������).
	//���� ����� �������� �������� �����������, �� ������� �������� "1" � ��������������� ��� �������� ALTFUNCSET (SET - ����������).
	//��������� ������� ��������� �������� ����������� ����� �����, �������� ����� �� ���� ��������� ALTFUNCCLR ��� ALTFUNCSET.
	//2)��������� ����� �������� �� ����� ����� ������ "1" � ��������������� ��� �������� OUTENSET.
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
//! ������������� ���������� � ��� ��������� ������. ������ ��� ���������, �������.
//! � ������ ������ ��������� ���������� �� ������� �������,������� ��������
//! ����� ������� ���, ����� �������� ����� ���������� ������� ��� (��������� ��� ��������
//! �������� ����)
//������ ��������� ������������ �� ������� NT_PWM3, ������� ��������������� � ������� ��������� ���.
//������������ ��������� ������������ � ����. ������ ����� ��� �������� �� ��������� ��������� � ���� ������ �� 16 ���������.
//� ���������� � �������� 10 ��� ������ ���������� �� ���� � ������������ � ��������� ������� (������ ���������� ������).
//� ��� �� ���������� �� ���������� ������� ������� N ��������� ����� � �� ��� ����������� ������� ��������������.
//����� ������� ��� ���������� N ������� �� ������� ��� � ����� F���/10���. ���� ������� ��� ������ 10 ���, �� ������� ���� �������, ���� ������ 40 ��� - 4 �������.
//� ������������ �������� �������� ����������� ������������� �����, � ��� ���������� �� ����������� ���������, � ���������� ���������� ������������� ��������� ���������.

//! \memberof TAdcDrv
void HAL_ADC_init() {

#ifndef MODEL
	// ������ ���� �����������
	int ii;
	NT_ADC->ACTSS = 0;

	// ����� ��������� ���������� � ���������
	NT_ADC->SEQ[0].OP = 0;
	NT_ADC->SEQ[1].OP = 0;
	NT_ADC->SEQ[2].OP = 0;
	NT_ADC->SEQ[3].OP = 0;
	NT_ADC->SEQ[4].OP = 0;
	NT_ADC->SEQ[5].OP = 0;
	NT_ADC->SEQ[6].OP = 0;
	NT_ADC->SEQ[7].OP = 0;

	//�������� 2, 3 � 4 ����������, �� ������ �� ���������� �������� (����� ���� ������� - 16 �����)
	//���������� � ������������� ������������ ������ ���� ���������, ���� ���������, �� ���������� ��������� (���������� ������� �������, ���������� �������� ����������� ���������).
	NT_ADC->ACTSS_bit.ASEN0 = 1; //������� ��������� �� ����������� ��� ���� pwm0
	//NT_ADC->ACTSS_bit.ASEN1 = 1; //������� ��������� �� ����������� ��� ������� pwm1
//	NT_ADC->ACTSS_bit.ASEN2 = 1;
//	NT_ADC->ACTSS_bit.ASEN3 = 1;
//	NT_ADC->ACTSS_bit.ASEN4 = 1;
//	NT_ADC->ACTSS_bit.ASEN5 = 1;
//	NT_ADC->ACTSS_bit.ASEN6 = 1;
//	NT_ADC->ACTSS_bit.ASEN7 = 1;

	//������ ����� ���������� (������ ��� ���������� ����������, ��� �� ���� 3 ����������, ���������� ������)
	//NT_ADC->IM_bit.MASK0 = 1;
	//NT_ADC->IM_bit.MASK1 = 1;

	//����������� �������� �������

	NT_ADC->EMUX_bit.EM0 = 6; //������ ������������ �� ������� SocA  ����� ��� 0 energy19
//	NT_ADC->EMUX_bit.EM1 = 7; //������ ������������ �� ������� SocA  ����� ��� 1 energy19
//	NT_ADC->EMUX_bit.EM2 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
//	NT_ADC->EMUX_bit.EM3 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
//	NT_ADC->EMUX_bit.EM4 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
//	NT_ADC->EMUX_bit.EM5 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
//	NT_ADC->EMUX_bit.EM6 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
//	NT_ADC->EMUX_bit.EM7 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card

//	NT_ADC->PSSI_bit.SS0 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS1 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS2 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS3 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS4 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS5 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS6 = 1; //��������� ����������� ������ ����������
//	NT_ADC->PSSI_bit.SS7 = 1; //��������� ����������� ������ ����������

	//�������� ��� ������� ������� ��� SPC0-SPC5 // ADC will start converstion without phase shift 0 delay
	NT_ADC->SPC0=0;NT_ADC->SPC1=0;NT_ADC->SPC2=0;NT_ADC->SPC3=0;NT_ADC->SPC4=0;NT_ADC->SPC5=0;

	//����������� ���������� ������������ ����������
	//for (ii=0;ii<2;ii++)
	NT_ADC->SEQ[0].CTL_bit.RCNT = 0; //������ 1 ��������� �� ������� 8��� ���������� �� ���������
	//NT_ADC->SEQ[1].CTL_bit.RCNT = 0; //������ 1 ��������� �� ������� 8��� ���������� �� ���������

	//����������� ������� ����������
	//for (ii=0;ii<8;ii++)
	NT_ADC->SEQ[0].CTL_bit.ICNT = 0; //���������� ����� ������� �������
	//NT_ADC->SEQ[1].CTL_bit.ICNT = 0; //���������� ����� ������� �������

	NT_ADC->SEQ[0].TMR_bit.TMR=0;//375; // 4 ��������� �� 8��� = 32���  ��������� ������������ ��� 12 ���, ������ 12000/32= 375
	//NT_ADC->SEQ[1].TMR_bit.TMR=0;//375; // 4 ��������� �� 8��� = 32���  ��������� ������������ ��� 12 ���, ������ 12000/32= 375

	for (ii=0;ii<12;ii++)
		NT_ADC->PP_bit[ii].OM = 0x3; //12 bit ADC unipolar,  OM2-OM0 = �011� All blocks active (ADC plus internal buffers plus internal bandgap).

	//�������� ����������� ������ ���
	//����������� ����������� ����������� ������ ���
	for (ii=0;ii<12;ii++)
	NT_ADC->PP_bit[ii].ENA = 1;	//�������� ������ ���

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

	//���������� ������ ������������
//	NT_ADC->SEQ[0].DCP_bit.CMP1 = 1;
//	NT_ADC->SEQ[1].DCP_bit.CMP2 = 1;
//	NT_ADC->SEQ[2].DCP_bit.CMP3 = 1;
//	NT_ADC->SEQ[3].DCP_bit.CMP4 = 1;
//	NT_ADC->SEQ[4].DCP_bit.CMP5 = 1;
//	NT_ADC->SEQ[5].DCP_bit.CMP6 = 1;
//	NT_ADC->SEQ[6].DCP_bit.CMP7 = 1;
//	NT_ADC->SEQ[7].DCP_bit.CMP8 = 1;

	//����� ������� ��� ��������� //Sequenser #0 starts all channel
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


//!������ ��� � �������� ��������� ������� ���� ������� ���������� (������ 10���).


volatile int reg_FLOAD;
volatile unsigned short reg_DATA[32];
volatile int reg_counter=0;

void HAL_ADC_calc(HAL_ADC*p) {

#ifndef MODEL
// ��� ����� HAL � ������ ���� ��������� � ����������� �� ����������


	while (NT_ADC->RIS_bit.INR0!=1)
		asm("nop");

	reg_FLOAD = NT_ADC->SEQ[0].FSTAT_bit.FLOAD;

	NT_ADC->ISC_bit.IN0=1;


	reg_counter=0;
	while (reg_FLOAD > 0)	//���� ���� �� ��������
	{	reg_DATA[reg_counter]=(NT_ADC->SEQ[0].FIFO_bit.DATA<<4); //this is a HAL task to receive and convert to 16 bit ADC format, so move left 4 bit
		reg_FLOAD = NT_ADC->SEQ[0].FSTAT_bit.FLOAD;

		reg_counter++;
		if (reg_counter>16)
			reg_counter=16;
//		//��������� ����� �� ���� ��������� ������ � ���� ��
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


	//����������
//	int i;
//	for (i = 0; i < p->SampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
//		int j = p->Ia_invPointer - i;
//		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
//			j = 4 + j;
//		p->Ia_inv_temp += p->Ia_invBuf[j];
//	}
//	//����� �� ����� ������� (1-4 �����)
//	p->Ia_inv_temp = p->Ia_inv_temp / p->SampleLength;

//	for (i = 0; i < p->IBSampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
//		int j = p->IBPointer - i;
//		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
//			j = 4 + j;
//		p->IB_temp += p->IBBuf[j];
//	}
//	//����� �� ����� ������� (1-4 �����)
//	p->IB_temp = p->IB_temp / p->IBSampleLength;
//
//	for (i = 0; i < p->UdcSampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
//		int j = p->UdcPointer - i;
//		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
//			j = 4 + j;
//		p->Udc_temp += p->UdcBuf[j];
//	}
//	//����� �� ����� ������� (1-4 �����), ������� �������� �������� ����������� �������
//	p->Udc_temp = p->Udc_temp / p->UdcSampleLength;

	//p->Ia_inv = p->Ia_invGainNom*((p->Ia_inv_temp + p->Ia_inv_offset));
//	//�������� HW_VECTORCARD_DRV8312_EVM ���������� �� HW_VECTORCARD_DRV8301_EVM � 5 ��� ������� ������������� �������� � ������ ������
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
	//��������� ��������� �������� ��� � ��������� 0-4095
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

//!��������� ������.

//!���������� ���������� �������������, ������������ � ���������� ������� �������,
//!����� �� �������� ������������ ����� ���. ������� ������������,
//!�� ������� ���� �������� ���������� � ��� ��������, ����� ��������
//!������������� ������� � �������� �����.

//! ������   p->PvalveGainNom=_IQ16mpy(p->Pvalve_gain,_IQ(1.0/100));
//! Pvalve_gain - �������� � ������� int. �������� ������������� � UniCON.
//!����������, �������� ��������� ������������� ������ �������� ���. � ���������� ������
//!����� 100. �.�. ����� �� ��� ������������ ������, ��� ������������� 100%.

//!_IQ(1.0/100) �������� �������� ��� ��������������� ������������. ��� ��� �������� ���������
//!������������ ����� ��������� � ������������� ������� ���, ��� 100% ������������ 1.0,
//!�� �������������� ����������� (����) ����� 100. �.�. UniCON, �������� �� ������� ����������
//! ����� 1.0 � ������� 8.24 ������ �������� ��� �� 100, ����� ������������ ��������.
//! ����� ����������� ����� ���� ��� 1.0/100, �� ��� ���� ������� ������� �������� ����� ������.
//!���, ��� ����� ��� ������������ �������� _1_I_nom, � ������� 8.24, ��������������� ������� �������� ��
//������� �������� ����, ��������, 200 �. ��� ��� � ����������� �� �������� ��������������� ������� ��� ����� ��������,
//�� ��� ��������, � ������� �� ���������, ������� �������������. ������ _1_I_nom ���� � ������ �����, ��� ���
//�������� ����� ������ �������.

//��� ������������ �������� ��� �������� ����� �� 0 �� 65535. (16 ��������, ��� ��������� �������).
//��� ������� � ���������� ���������� ������� ���, ����� ���������� �������������� �������� � ������� 8.24,
//��� 1.0 ��� 65535. ����� �������, ����� �������� ����� 65535 �� 24-16=8 ��������.
//����� �� 8 �������� - ��� ��������� �� ����� 255. ����� 255 - ��� 1.0 � ������� 24.8.

//����� �������, PvalveGainNom - ��� ����������� � ������� 24.8. �� ���������� � ���������� ������������� �������
//_IQ16mpy, �������� ������� Pvalve_gain (int) � 1.0/100 � ������� 8.24. ������� IQ ��������
//�� ���� ������������ ����� ������� ��������� � 64 �������� �� ������� ���������� ������ �� Q ��������.
//�.�. _IQ16mpy �������� ����� � ������� IQ24 9������ ��������) �� ������������� ����������� (������ ��������),
//� ����� �������� ��������� �� 16 �������� ������.
//���, � ���������� _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); ���������� ������������� ����� 255, ����������
//1.0 � ������� 24.8 ��-�� ������ �� 16 �������� ������.

//�� ��������������� ������ ������� � ����� ����� - ��������� ������������������ ��������� ���.



