//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_Adc.c
//
// TITLE:	DSP28 ADC Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//  0.58| 29 Jun 2002 | L.H. | Added InitAdc Function 
//###########################################################################

#include "DSP28_Device.h"

#define ADC_usDELAY  5000L
#define ADC_usDELAY2 20L

//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
      // To powerup the ADC the ADCENCLK bit should be set first to enable
      // clocks, followed by powering up the bandgap and reference circuitry.
      // After a 5ms delay the rest of the ADC can be powered up. After ADC
      // powerup, another 20us delay is required before performing the first
      // ADC conversion. Please note that for the delay function below to
      // operate correctly the CPU_CLOCK_SPEED define statement in the
      // DSP28_Device.h file must contain the correct CPU clock period in
      // nanoseconds. For example:
      //
      // #define CPU_CLOCK_SPEED  6.6667L      // for a 150MHz CPU clock speed
	
	//This was done in the InitSysCtrl() function in DSP28_SysCtrl.c
	//asm("	EALLOW");
	//SysCtrlRegs.PCLKCR.bit.ADCENCLK = 1;     // Power up clocks to ADC
	//SysCtrlRegs.WDCR = 0x6F;                 // Disable WD
	//asm("	EDIS");

	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// Power up bandgap/reference circuitry
	DELAY_US(ADC_usDELAY);                    // Delay before powering up rest of ADC
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;		// Power up rest of ADC
	DELAY_US(ADC_usDELAY2);                   // Delay after powering up ADC
}	
//---------------------------------------------------------
//---------------My functions------------------------------
//---------------------------------------------------------

//===========================================================================
// No more.
//===========================================================================
