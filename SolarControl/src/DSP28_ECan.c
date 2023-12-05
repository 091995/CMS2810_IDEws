//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_ECan.c
//
// TITLE:	DSP28 Enhanced CAN Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//  0.58| 29 Jun 2002 | L.H. | No change
//  0.59| 23 Dec 2002 | H.J. | Added several initialization routines
//###########################################################################

#include "DSP28_Device.h"


//---------------------------------------------------------------------------
// InitECan: 
//---------------------------------------------------------------------------
// This function initializes the eCAN module to a known state.
//
void InitECan(void)
{

//InitCanDrlong	i;

asm("  EALLOW");

/* Disable Watchdog  */
    
  //     
    
/* Enable clock to CAN module  */   
    
 //   SysCtrlRegs.PCLKCR.all = 0x4000;    
    
/* Set PLL multiplication factor */
    
  //SysCtrlRegs.PLLCR.bit.DIV = 0x000A;	// Set PLL to x10 (/2). A CLKIN of 30 MHz would result in
    							// 30 * 10 = 300 (/2) = 150 MHz SYSCLKOUT.
    							
 /*   for(i=0; i<100000; i++) 	// Delay for PLL to stabilize 
	 	{ asm(" NOP"); }
 */	 								
/* Configure eCAN pins using GPIO regs*/

	GpioMuxRegs.GPFMUX.bit.CANTXA_GPIOF6 = 1;
	GpioMuxRegs.GPFMUX.bit.CANRXA_GPIOF7 = 1;	
	
/* Configure eCAN RX and TX pins for eCAN transmissions using eCAN regs*/  
    
    ECanaRegs.CANTIOC.bit.TXFUNC = 1;
    ECanaRegs.CANRIOC.bit.RXFUNC = 1;   

/* Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31) */
/* HECC mode also enables time-stamping feature*/
				
	ECanaRegs.CANMC.bit.SCM = 1;
	ECanaRegs.CANMC.bit.SUSP = 1;

/* Initialize all bits of 'Master Control Field' to zero */
// Some bits of MCF register come up in an unknown state. For proper operation,
// all bits (including reserved bits) of MCF must be initialized to zero
//также в нем приоритет на передачу и в DLC длина данных 0..8 
    ECanaMboxes.MBOX0.MCF.all = 0x00000000;
    ECanaMboxes.MBOX1.MCF.all = 0x00000000;
    ECanaMboxes.MBOX2.MCF.all = 0x00000000;
    ECanaMboxes.MBOX3.MCF.all = 0x00000000;
    ECanaMboxes.MBOX4.MCF.all = 0x00000000;
    ECanaMboxes.MBOX5.MCF.all = 0x00000000;
    ECanaMboxes.MBOX6.MCF.all = 0x00000000;
    ECanaMboxes.MBOX7.MCF.all = 0x00000000;
    ECanaMboxes.MBOX8.MCF.all = 0x00000000;
    ECanaMboxes.MBOX9.MCF.all = 0x00000000;
    ECanaMboxes.MBOX10.MCF.all = 0x00000000;
    ECanaMboxes.MBOX11.MCF.all = 0x00000000;
    ECanaMboxes.MBOX12.MCF.all = 0x00000000;
    ECanaMboxes.MBOX13.MCF.all = 0x00000000;
    ECanaMboxes.MBOX14.MCF.all = 0x00000000;
    ECanaMboxes.MBOX15.MCF.all = 0x00000000;
    ECanaMboxes.MBOX16.MCF.all = 0x00000000;
    ECanaMboxes.MBOX17.MCF.all = 0x00000000;
    ECanaMboxes.MBOX18.MCF.all = 0x00000000;
    ECanaMboxes.MBOX19.MCF.all = 0x00000000;
    ECanaMboxes.MBOX20.MCF.all = 0x00000000;
    ECanaMboxes.MBOX21.MCF.all = 0x00000000;
    ECanaMboxes.MBOX22.MCF.all = 0x00000000;
    ECanaMboxes.MBOX23.MCF.all = 0x00000000;
    ECanaMboxes.MBOX24.MCF.all = 0x00000000;
    ECanaMboxes.MBOX25.MCF.all = 0x00000000;
    ECanaMboxes.MBOX26.MCF.all = 0x00000000;
    ECanaMboxes.MBOX27.MCF.all = 0x00000000;
    ECanaMboxes.MBOX28.MCF.all = 0x00000000;
    ECanaMboxes.MBOX29.MCF.all = 0x00000000;
    ECanaMboxes.MBOX30.MCF.all = 0x00000000;
    ECanaMboxes.MBOX31.MCF.all = 0x00000000;

// TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
//	as a matter of precaution. 

/* Clear all TAn bits */      
//если после посылки акноледж удачный то ТА =1	
	ECanaRegs.CANTA.all	= 0xFFFFFFFF;

/* Clear all RMPn bits */      
//Если пришло собщение то оно устанавливаетсЯ 
	ECanaRegs.CANRMP.all = 0xFFFFFFFF;
	
/* Clear all interrupt flag bits */      
	
	ECanaRegs.CANGIF0.all = 0xFFFFFFFF;
	ECanaRegs.CANGIF1.all = 0xFFFFFFFF;
	
/* Configure bit timing parameters */

	ECanaRegs.CANMC.bit.CCR = 1 ;            // Set CCR = 1
    
    while(ECanaRegs.CANES.bit.CCE != 1 ) {}   // Wait for CCE bit to be set..
    
    ECanaRegs.CANBTC.bit.BRP = 74;
    ECanaRegs.CANBTC.bit.TSEG2 = 2;
    ECanaRegs.CANBTC.bit.TSEG1 = 11;  
    ECanaRegs.CANBTC.bit.SJW = 2;
    
    ECanaRegs.CANMC.bit.CCR = 0 ;             // Set CCR = 0
    while(ECanaRegs.CANES.bit.CCE == !0 ) {}   // Wait for CCE bit to be cleared..
	
/* Disable all Mailboxes  */
	
 	ECanaRegs.CANME.all = 0;		// Required before writing the MSGIDs
 	
asm("  EDIS");
}	
	
/***************************************************/
/* Bit configuration parameters for 150 MHz SYSCLKOUT*/ 
/***************************************************/
/*

The table below shows how BRP field must be changed to achieve different bit
rates with a BT of 15, for a 80% SP:
---------------------------------------------------
BT = 15, TSEG1 = 10, TSEG2 = 2, Sampling Point = 80% 
---------------------------------------------------
1   Mbps : BRP+1 = 10 	: CAN clock = 15 MHz
500 kbps : BRP+1 = 20 	: CAN clock = 7.5 MHz 
250 kbps : BRP+1 = 40 	: CAN clock = 3.75 MHz 
125 kbps : BRP+1 = 80 	: CAN clock = 1.875 MHz 
100 kbps : BRP+1 = 100 	: CAN clock = 1.5 MHz
50  kbps : BRP+1 = 200 	: CAN clock = 0.75 MHz

The table below shows how to achieve different sampling points with a BT of 25:
-------------------------------------------------------------
Achieving desired SP by changing TSEG1 & TSEG2 with BT = 25  
-------------------------------------------------------------

TSEG1 = 18, TSEG2 = 4, SP = 80% 
TSEG1 = 17, TSEG2 = 5, SP = 76% 
TSEG1 = 16, TSEG2 = 6, SP = 72% 
TSEG1 = 15, TSEG2 = 7, SP = 68% 
TSEG1 = 14, TSEG2 = 8, SP = 64% 

The table below shows how BRP field must be changed to achieve different bit
rates with a BT of 25, for the sampling points shown above: 

1   Mbps : BRP+1 = 6 
500 kbps : BRP+1 = 12 
250 kbps : BRP+1 = 24 
125 kbps : BRP+1 = 48 
100 kbps : BRP+1 = 60
50  kbps : BRP+1 = 120

*/


