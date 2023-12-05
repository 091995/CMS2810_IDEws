//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_SysCtrl.c
//
// TITLE:	DSP28 Device System Control Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 24 May 2002 | L.H. | Added initialization of RAM control registers
//      |             |      | for TMX samples.
//  0.58| 29 Jun 2002 | L.H. | Added InitFlash function.  Must be run from RAM
//###########################################################################


#include "DSP28_Device.h"

// Functions that will be run from RAM need to be assigned to 
// a different section.  This section will then be mapped using
// the linker cmd file.



//---------------------------------------------------------------------------
// InitSysCtrl: 
//---------------------------------------------------------------------------
// This function initializes the System Control registers to a known state.
//
void InitSysCtrl(void)
{
   Uint16 i;
   EALLOW;
   
// On TMX samples, to get the best performance of on chip RAM blocks M0/M1/L0/L1/H0 internal
// control registers bit have to be enabled. The bits are in Device emulation registers.
//   DevEmuRegs.M0RAMDFT = 0x0300;
//   DevEmuRegs.M1RAMDFT = 0x0300;
//   DevEmuRegs.L0RAMDFT = 0x0300;
//   DevEmuRegs.L1RAMDFT = 0x0300;
//   DevEmuRegs.H0RAMDFT = 0x0300;
   
           
// Disable watchdog module
   SysCtrlRegs.WDCR= 0x0068;
// Initalize PLL
   SysCtrlRegs.PLLCR.bit.DIV = 0xA;
   // Wait for PLL to lock
   for(i= 0; i< 5000; i++){}
       
// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
   SysCtrlRegs.HISPCP.all = 0x0001; 
   SysCtrlRegs.LOSPCP.all = 0x0002;	
// Peripheral clock enables set for the selected peripherals.   
   SysCtrlRegs.PCLKCR.bit.EVAENCLK=1;
   SysCtrlRegs.PCLKCR.bit.EVBENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SCIENCLKA=1;
   SysCtrlRegs.PCLKCR.bit.SCIENCLKB=1;
   SysCtrlRegs.PCLKCR.bit.MCBSPENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SPIENCLK=1;
   SysCtrlRegs.PCLKCR.bit.ECANENCLK=1;
   SysCtrlRegs.PCLKCR.bit.ADCENCLK=1;
   EDIS;
	
}

// This function initializes the Flash Control registers

//                   CAUTION 
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(InitFlash, "secureRamFuncs");
#endif




void InitFlash(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1;
   
   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI. 
   //Refer to the datasheet for the latest information.  

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;
   
   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;
   
   //                CAUTION
   //Minimum cycles required to move between power states
   //at a given CPU rate must be characterized by TI. 
   //Refer to the datasheet for the latest information.
     
   //For now use the default count
   
   //Set number of cycles to transition from sleep to standby
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;       
   
   //Set number of cycles to transition from standby to active
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;   
   EDIS;
}	


//---------------------------------------------------------------------------
// KickDog: 
//---------------------------------------------------------------------------
// This function resets the watchdog timer.
// Enable this function for using KickDog in the application 
/*
void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}
*/

void Disable_WD(void)
{
 SysCtrlRegs.WDCR= 0x0068;

}


	
//===========================================================================
// No more.
//===========================================================================
