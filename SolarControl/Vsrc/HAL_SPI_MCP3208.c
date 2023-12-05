

#include "DSP.h"
#include "main.h"
#include "HAL_SPI_MCP3208.h"

//prototypes
void HAL_SPI_MCP3208_Write(HAL_SPI_MCP3208*p,Uint16 reg);
void HAL_SPI_MCP3208_Read(HAL_SPI_MCP3208*p);


void HAL_SPI_MCP3208_init(HAL_SPI_MCP3208*p){
int ii;
	//init SPI for master mode
		volatile long delay;
		volatile Uint32 tempREG;

		// ��������� ��� SPI C11-TX A7-RX A6-CLK A5-nCS
		NT_GPIOC->ALTFUNCSET =  (1 << 11);
		NT_COMMON_REG->GPIOPCTLC_bit.PIN11 = 1;

		NT_GPIOA->ALTFUNCSET =  ((1 << 5)|(1 << 6)|(1 << 7));
		NT_COMMON_REG->GPIOPCTLA_bit.PIN5 = 0;
		NT_COMMON_REG->GPIOPCTLA_bit.PIN6 = 0;
		NT_COMMON_REG->GPIOPCTLA_bit.PIN7 = 0;


		// ��������� ������������ SSP ������
		// ����� 4 ������, �� ������ ������ �� 8 ��� �� �������� SSP_CLK_CTRL � �� ��� ���� �� UART_SSP_CLK_SEL

		// UART_SSP_CLK_SEL
		// �� ������ ����� ����� �� ������ �� 4-�� ������� SSP ��������� �� ��� ���� ��� ������ ��������� ������������ 0x0000XX00
		// "00" - � �������� �������� ������������ ������ SSP ���������� ��������� ������� 100 ���, ����� ������� f_SSP_IN = SysClk = 100 MHz

		// SSP_CLK_CTRL
		// ������� ��� ��������� ������������ (1 - ���������)
		// ������ ��� ��������� ������� ������� f_SSP_IN ��������� ��������� ������� (0 - �� ������, 1 - ������)
		// ������� ����� �������� �������� ������� ����� ���������:
		//  X - ������� �� ������� SSPclk = f_SSP_IN /( 2 * (X +1) )
		// �� ������������ �� ���� SSP - ����������� ������� ��� ������ ������ � ������� � ������ � �����,
		// f_SSP_IN > 22.12 MHz, ������� 25 ��� �������
		tempREG = NT_COMMON_REG->UART_SPI_CLK_SEL;// ����� tempREG, ����� �� ������ ������ ����, ���������� �� ������������ UART'a
		tempREG &= 0xFFFF00FF;
		NT_COMMON_REG->UART_SPI_CLK_SEL = tempREG;

		//MCP is 2MHz max spi clk - let set 1MHz SPI_CLK=100Mhz/(2*(x+1)) x=49
		NT_COMMON_REG->SPI_CLK = (1<<2)|0x3;// ��������� ������������, ��������� ������� �������, ������ �� 4 - 25 ���

		// ��������� ������ ������ SPI
		// ����������� ��������� ������������.
		// ���������� ����� ������� f_SSP_IN �������� ��� ����� ��� ��������.
		// SSPCPSR - ������ ��������, � ��������� 2 ... 254, ����� ���� ������ ������ (������� ��� ������ ��������� ����� 0)
		// SSPCR0.bit.SCR - ������ �������� �� 0 �� 255.
		// ������� � ����� BitRate = f_SSP_IN / ( SSPCPSR * (SCR + 1) )

		NT_SPI0->SPI_CR1 = 0;		// ����� - ������, LoopBack ��������, ��� ������ SSP ���� ��������
		NT_SPI0->SPI_IMSC = 0x0;	// ��������� ��� ����������
		NT_SPI0->SPI_DMACR = 0;		// ��������� DMA
		NT_SPI0->SPI_ICR = 0x3;		// ������� ���������� ("������������ FIFO �����" � "������������� FIFO �����")

		NT_SPI0->SPI_CPSR = 25;			// ������� ������� ������� �� 25 -> 1 MHz
		NT_SPI0->SPI_CR0_bit.DSS = 0xF;	// ������ ������ - 16 ��� ������������
		NT_SPI0->SPI_CR0_bit.SCR = 0x2; //0x3F;	// ������ �������� = 15 -> f_SPI = 416 kHz
		NT_SPI0->SPI_CR0_bit.FRF = 0x0;	// �������� SPI
		NT_SPI0->SPI_CR0_bit.SPH = 0x1;	// ������� ������ �� ��������� ������ �������������, � ��������� �� �������
		NT_SPI0->SPI_CR0_bit.SPO = 0x0;	// 0 � ������ �������� ����� SPI_CLK ������������ � ��������� ����������� ����
		NT_SPI0->SPI_CR1_bit.SSE = 1;	// ��������� ������

//		// ��������� ��� ��� ����� ������ �� DRV8301: �4 - Fault, C5 - OCTW
//		NT_GPIOC->ALTFUNCCLR = (1 << 4) | (1 << 5);
//		NT_GPIOC->OUTENCLR = (1 << 4) | (1 << 5);
//
//		// ��������� ���� ��� ��������� DRV8301: G8 - EN_GATE
//		NT_GPIOG->ALTFUNCCLR = (1 << 8);
//		NT_GPIOG->OUTENSET |= (1 << 8);	//����� ���, ����� �� ��������� ��������� ��� ����� G
//		NT_GPIOG->DATA |= (1 << 8);	//DATA.bit.GPIO8 = 1

		// ������� 10 �� ����� ����������
		delay = 10000000;
		while (delay > 0)
			delay--;

		for (ii=0;ii<16;ii++)
		mcp.adc_regs[ii]=0xA55A;

}



void HAL_SPI_MCP3208_update(HAL_SPI_MCP3208*p) {
Uint32 adc_reg;
	mcp.adc_ch++;
	mcp.adc_ch&=0x7;

	//mcp.adc_ch=0;
	HAL_SPI_MCP3208_Write(&mcp,mcp.adc_ch);

	//adc_reg = mcp.readWord.all;
	adc_reg = (mcp.readWord1<<3)|(mcp.readWord2>>13); //

	if (mcp.adc_ch==0) {
	mcp.adc_regs[mcp.extra_mux]=adc_reg;
	}
	else
	if (mcp.adc_ch==1) {
	mcp.adc_regs[mcp.extra_mux+4]=adc_reg;
	mcp.extra_mux++;
	mcp.extra_mux&=0x3;
	}
	else
	mcp.adc_regs[mcp.adc_ch+8]=adc_reg;

	//HAL_SPI_MCP3208_Read(&mcp);

}

void HAL_SPI_MCP3208_Write(HAL_SPI_MCP3208*p,Uint16 reg) {
	Uint16 trash;

	mcp.writeWord.bit.START = 1;					//we are initiating a write
	mcp.writeWord.bit.SINGLE_OR_DIFF=1;
	mcp.writeWord.bit.ADDRESS = reg;				//load the address
	mcp.writeWord.bit.NUL_REG=0;			//data to be written;

	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
	NT_SPI0->SPI_DR = 0;					//send out the data


	while (NT_SPI0->SPI_SR_bit.BSY == 1)
		;		//wait for the packet to complete

	mcp.readWord1 = NT_SPI0->SPI_DR;//read returned value of Status Register 1 and clear the INT_FLAG bit
	mcp.readWord2 = NT_SPI0->SPI_DR;//read returned value of Status Register 1 and clear the INT_FLAG bit


}

void HAL_SPI_MCP3208_Read(HAL_SPI_MCP3208*p) {

	Uint16 trash;

	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data

	while (NT_SPI0->SPI_SR_bit.BSY == 1)
		;		//wait for the packet to complete

	// � ��� ����� DRV ��� ������� ����� (���� ��� �� ������ ���)
	trash = NT_SPI0->SPI_DR;			//dummy read to clear the INT_FLAG bit


//	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
//
//	while (NT_SPI0->SPI_SR_bit.BSY == 1)
//		;		//wait for the packet to complete
//
//	// � ��� ����� DRV ��� ������� ����� �� ������� ������ - �� ���� ���������� ������� ��������
//	mcp.readWord.all = NT_SPI0->SPI_DR;		//dummy read to clear the INT_FLAG bit
//
//	// ������ �������, ��� ������
//	mcp.writeWord.bit.R_W = 1;						//we are initiating a read
//	mcp.writeWord.bit.ADDRESS = 0x2;				//load the address
//	mcp.writeWord.bit.DATA = 0;							//dummy data;
//
//	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
//
//	while (NT_SPI0->SPI_SR_bit.BSY == 1)
//		;		//wait for the packet to complete
//
//	// � ��� ����� DRV ��� ������� ����� �� ������� ������ - �� ���� ���������� ������� ��������
//	mcp.readWord.all = NT_SPI0->SPI_DR;

}

/*! EXAMPLE AREA
 *
 */
//void DRV8301_Interface_Init(Tdrv8301interface*p) {
//#ifdef HW_VECTORCARD_DRV8301_EVM
//	volatile long delay;
//	volatile Uint32 tempREG;
//
//	// ��������� ��� SPI
//	NT_GPIOC->ALTFUNCSET = (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11);
//	NT_COMMON_REG->GPIOPCTLC_bit.PIN8 = 1;
//	NT_COMMON_REG->GPIOPCTLC_bit.PIN9 = 1;
//	NT_COMMON_REG->GPIOPCTLC_bit.PIN10 = 1;
//	NT_COMMON_REG->GPIOPCTLC_bit.PIN11 = 1;
//
//	// ��������� ������������ SSP ������
//	// ����� 4 ������, �� ������ ������ �� 8 ��� �� �������� SSP_CLK_CTRL � �� ��� ���� �� UART_SSP_CLK_SEL
//
//	// UART_SSP_CLK_SEL
//	// �� ������ ����� ����� �� ������ �� 4-�� ������� SSP ��������� �� ��� ���� ��� ������ ��������� ������������ 0x0000XX00
//	// "00" - � �������� �������� ������������ ������ SSP ���������� ��������� ������� 100 ���, ����� ������� f_SSP_IN = SysClk = 100 MHz
//
//	// SSP_CLK_CTRL
//	// ������� ��� ��������� ������������ (1 - ���������)
//	// ������ ��� ��������� ������� ������� f_SSP_IN ��������� ��������� ������� (0 - �� ������, 1 - ������)
//	// ������� ����� �������� �������� ������� ����� ���������:
//	//  X - ������� �� ������� SSPclk = f_SSP_IN /( 2 * (X +1) )
//	// �� ������������ �� ���� SSP - ����������� ������� ��� ������ ������ � ������� � ������ � �����,
//	// f_SSP_IN > 22.12 MHz, ������� 25 ��� �������
//	tempREG = NT_COMMON_REG->UART_SPI_CLK_SEL;// ����� tempREG, ����� �� ������ ������ ����, ���������� �� ������������ UART'a
//	tempREG &= 0xFFFF00FF;
//	NT_COMMON_REG->UART_SPI_CLK_SEL = tempREG;
//	NT_COMMON_REG->SPI_CLK = 0x07070707;// ��������� ������������, ��������� ������� �������, ������ �� 4 - 25 ���
//
//	// ��������� ������ ������ SPI
//	// ����������� ��������� ������������.
//	// ���������� ����� ������� f_SSP_IN �������� ��� ����� ��� ��������.
//	// SSPCPSR - ������ ��������, � ��������� 2 ... 254, ����� ���� ������ ������ (������� ��� ������ ��������� ����� 0)
//	// SSPCR0.bit.SCR - ������ �������� �� 0 �� 255.
//	// ������� � ����� BitRate = f_SSP_IN / ( SSPCPSR * (SCR + 1) )
//
//	NT_SPI0->SPI_CR1 = 0;// ����� - ������, LoopBack ��������, ��� ������ SSP ���� ��������
//	NT_SPI0->SPI_IMSC = 0x0;		// ��������� ��� ����������
//	NT_SPI0->SPI_DMACR = 0;		// ��������� DMA
//	NT_SPI0->SPI_ICR = 0x3;	// ������� ���������� ("������������ FIFO �����" � "������������� FIFO �����")
//
//	NT_SPI0->SPI_CPSR = 4;			// ������� ������� ������� �� 4 -> 6,25 MHz
//	NT_SPI0->SPI_CR0_bit.DSS = 0xF;	// ������ ������ - 16 ���
//	NT_SPI0->SPI_CR0_bit.SCR = 0x3F;	// ������ �������� = 15 -> f_SPI = 416 kHz
//	NT_SPI0->SPI_CR0_bit.FRF = 0x0;	// �����-�� "����" ��� ��������� Motorola SPI
//	NT_SPI0->SPI_CR0_bit.SPH = 0x1;	// �����-�� "����������" ��� ��������� Motorola SPI
//	NT_SPI0->SPI_CR0_bit.SPO = 0x0;	// ����� ������� ����� Motorola/TI/Microwire. "0" - �� ��������� Motorola SPI
//	NT_SPI0->SPI_CR1_bit.SSE = 1;	// ��������� ������
//
//	// ��������� ��� ��� ����� ������ �� DRV8301: �4 - Fault, C5 - OCTW
//	NT_GPIOC->ALTFUNCCLR = (1 << 4) | (1 << 5);
//	NT_GPIOC->OUTENCLR = (1 << 4) | (1 << 5);
//
//	// ��������� ���� ��� ��������� DRV8301: G8 - EN_GATE
//	NT_GPIOG->ALTFUNCCLR = (1 << 8);
//	NT_GPIOG->OUTENSET |= (1 << 8);	//����� ���, ����� �� ��������� ��������� ��� ����� G
//	NT_GPIOG->DATA |= (1 << 8);	//DATA.bit.GPIO8 = 1
//
//	// ������� 10 �� ����� ����������
//	delay = 10000000;
//	while (delay > 0)
//		delay--;
//
//	// ��������� ������ DRV8301
//	mcp.CTRL1.bit.GATE_CURRENT = 0;		// full current 1.7A
////			mcp.CTRL1.bit.GATE_CURRENT = 1;		// med current 0.7A
////			mcp.CTRL1.bit.GATE_CURRENT = 2;		// min current 0.25A
//	mcp.CTRL1.bit.GATE_RESET = 0;			// Normal Mode
//	mcp.CTRL1.bit.PWM_MODE = 0;			// six independant PWMs
////			mcp.CTRL1.bit.OC_MODE = 0;				// current limiting when OC detected
//	mcp.CTRL1.bit.OC_MODE = 1;				// latched OC shutdown
////			mcp.CTRL1.bit.OC_MODE = 2;				// Report on OCTWn pin and SPI reg only, no shut-down
////			mcp.CTRL1.bit.OC_MODE = 3;				// OC protection disabled
////			mcp.CTRL1.bit.OC_ADJ_SET = 0;			// OC @ Vds=0.060V
////			mcp.CTRL1.bit.OC_ADJ_SET = 4;			// OC @ Vds=0.097V
////			mcp.CTRL1.bit.OC_ADJ_SET = 6;			// OC @ Vds=0.123V
////			mcp.CTRL1.bit.OC_ADJ_SET = 9;			// OC @ Vds=0.175V
//	mcp.CTRL1.bit.OC_ADJ_SET = 15;			// OC @ Vds=0.358V
////			mcp.CTRL1.bit.OC_ADJ_SET = 16;			// OC @ Vds=0.403V
////			mcp.CTRL1.bit.OC_ADJ_SET = 17;			// OC @ Vds=0.454V
////			mcp.CTRL1.bit.OC_ADJ_SET = 18;			// OC @ Vds=0.511V
//	mcp.CTRL1.bit.Reserved = 0;
//
////			mcp.CTRL2.bit.OCTW_SET = 0;			// report OT and OC
//	mcp.CTRL2.bit.OCTW_SET = 1;			// report OT only
//
////			mcp.CTRL2.bit.GAIN = 0;				// CS amplifier gain = 10
//	mcp.CTRL2.bit.GAIN = 1;				// CS amplifier gain = 20
////			mcp.CTRL2.bit.GAIN = 2;				// CS amplifier gain = 40
////			mcp.CTRL2.bit.GAIN = 3;				// CS amplifier gain = 80
//
//	mcp.CTRL2.bit.DC_CAL_CH1 = 0;			// not in CS calibrate mode
//	mcp.CTRL2.bit.DC_CAL_CH2 = 0;			// not in CS calibrate mode
//	mcp.CTRL2.bit.OC_TOFF = 0;				// normal mode
//	mcp.CTRL2.bit.Reserved = 0;
//
//	// �������
//
//	mcp.write(p, CNTRL_REG_1_ADDR);
//	mcp.write(p, CNTRL_REG_2_ADDR);
//	mcp.read(p);
//#endif
//}
//
//void DRV8301_Interface_Write(Tdrv8301interface*p, Uint16 reg) {
//#ifdef HW_VECTORCARD_DRV8301_EVM
//	Uint16 trash;
//
//	mcp.writeWord.bit.R_W = 0;						//we are initiating a write
//	mcp.writeWord.bit.ADDRESS = reg;				//load the address
//
//	if (reg == CNTRL_REG_1_ADDR)
//		mcp.writeWord.bit.DATA = mcp.CTRL1.all;			//data to be written;
//	else
//		mcp.writeWord.bit.DATA = mcp.CTRL2.all;
//	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
//
//	while (NT_SPI0->SPI_SR_bit.BSY == 1)
//		;		//wait for the packet to complete
//
//	trash = NT_SPI0->SPI_DR;//read returned value of Status Register 1 and clear the INT_FLAG bit
//#endif
//}
//
//void DRV8301_Interface_Read(Tdrv8301interface*p) {
//#ifdef HW_VECTORCARD_DRV8301_EVM
//	Uint16 trash;
//	// ������� �������, ��� ����� ������ ������ �������
//	mcp.writeWord.bit.R_W = 1;						//we are initiating a read
//	mcp.writeWord.bit.ADDRESS = STAT_REG_1_ADDR;		//load the address
//	mcp.writeWord.bit.DATA = 0;						//dummy data;
//
//	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
//
//	while (NT_SPI0->SPI_SR_bit.BSY == 1)
//		;		//wait for the packet to complete
//
//	// � ��� ����� DRV ��� ������� ����� (���� ��� �� ������ ���)
//	trash = NT_SPI0->SPI_DR;			//dummy read to clear the INT_FLAG bit
//
//	// ������ �������, ��� �������� ������ �������
//	mcp.writeWord.bit.R_W = 1;						//we are initiating a read
//	mcp.writeWord.bit.ADDRESS = STAT_REG_2_ADDR;				//load the address
//	mcp.writeWord.bit.DATA = 0;							//dummy data;
//
//	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
//
//	while (NT_SPI0->SPI_SR_bit.BSY == 1)
//		;		//wait for the packet to complete
//
//	// � ��� ����� DRV ��� ������� ����� �� ������� ������ - �� ���� ���������� ������� ��������
//	mcp.STS1.all = NT_SPI0->SPI_DR;		//dummy read to clear the INT_FLAG bit
//
//	// ������ �������, ��� ������
//	mcp.writeWord.bit.R_W = 1;						//we are initiating a read
//	mcp.writeWord.bit.ADDRESS = STAT_REG_2_ADDR;				//load the address
//	mcp.writeWord.bit.DATA = 0;							//dummy data;
//
//	NT_SPI0->SPI_DR = mcp.writeWord.all;					//send out the data
//
//	while (NT_SPI0->SPI_SR_bit.BSY == 1)
//		;		//wait for the packet to complete
//
//	// � ��� ����� DRV ��� ������� ����� �� ������� ������ - �� ���� ���������� ������� ��������
//	mcp.STS2.all = NT_SPI0->SPI_DR;
//#endif
//}
