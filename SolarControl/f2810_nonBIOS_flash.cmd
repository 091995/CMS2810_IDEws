/**********************************************************************
* File: f2812.cmd -- Linker command file for Boot to Flash bootmode.
* History: 09/08/03 - original (based on DSP28 header files v1.00, D. Alter)
**********************************************************************/


MEMORY
{
PAGE 0:    /* Program Memory */
   /*ZONE0       : origin = 0x002000, length = 0x002000     /* XINTF zone 0 */
   /*ZONE1       : origin = 0x004000, length = 0x002000     /* XINTF zone 1 */
   RAML01       : origin = 0x008000, length = 0x002000     /* on-chip RAM block L0 */
   /*ZONE2       : origin = 0x080000, length = 0x080000     /* XINTF zone 2 */
   /*ZONE6       : origin = 0x100000, length = 0x080000     /* XINTF zone 6 */
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   FLASHABCDE   : origin = 0x3E8000, length = 0x00FFF0     /* on-chip FLASH */

  
   /*CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Reserved when CSM is in use. */
   BEGIN_FLASH : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to flash" bootloader mode. */
   PASSWORDS   : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations. */
/*   BEGIN_H0    : origin = 0x3F8000, length = 0x000002     /* Part of H0.  Used for "boot to H0" bootloader mode. */
/*   RAMH0       : origin = 0x3F8002, length = 0x001FFE     /* H0 SARAM */
/*   ZONE7       : origin = 0x3FC000, length = 0x003FC0     /* XINTF zone 7 available if MP/MCn=1 */ 
   ROM         : origin = 0x3FF000, length = 0x000FC0     /* boot ROM available if MP/MCn=0 */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */

PAGE 1 :   /* Data Memory */
   RAMM0       : origin = 0x000000, length = 0x000400     /* on-chip RAM block M0 */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
 /*  RAML1       : origin = 0x009000, length = 0x001000     /* on-chip RAM block L1 */

   DEV_EMU     : origin = 0x000880, length = 0x000180     /* Device emulation registers */
   FLASH_REGS  : origin = 0x000A80, length = 0x000060     /* FLASH registers */
   CSM         : origin = 0x000AE0, length = 0x000010     /* Code security module registers */
   CPU_TIMER0  : origin = 0x000C00, length = 0x000008     /* CPU Timer0 registers (CPU Timer1 and Timer2 are reserved for BIOS)*/
   CPU_TIMER2  : origin = 0x000C10, length = 0x000008     /* CPU Timer2 registers (CPU Timer1 and Timer2 are reserved for BIOS)*/
   PIE_CTRL    : origin = 0x000CE0, length = 0x000020     /* PIE control registers */
   PIE_VECT    : origin = 0x000D00, length = 0x000100     /* PIE vector table */
   ECAN_A      : origin = 0x006000, length = 0x000040     /* eCAN registers */
   ECAN_LAM    : origin = 0x006040, length = 0x0000C0
   ECAN_AMBOX  : origin = 0x006100, length = 0x000100     /* eCAN mailboxes */
   SYSTEM      : origin = 0x007010, length = 0x000020     /* System control registers */
   SPI_A       : origin = 0x007040, length = 0x000010     /* SPI registers */
   SCI_A       : origin = 0x007050, length = 0x000010     /* SCI-A registers */
   XINTRUPT    : origin = 0x007070, length = 0x000010     /* External interrupt registers */
   GPIOMUX     : origin = 0x0070C0, length = 0x000020     /* GPIO mux registers */
   GPIODAT     : origin = 0x0070E0, length = 0x000020     /* GPIO data registers */
   ADC         : origin = 0x007100, length = 0x000020     /* ADC registers */
   EV_A        : origin = 0x007400, length = 0x000040     /* Event Manager A registers */
   EV_B        : origin = 0x007500, length = 0x000040     /* Event Manager B registers */
   SCI_B       : origin = 0x007750, length = 0x000010     /* SCI-B registers */
   MCBSP_A     : origin = 0x007800, length = 0x000040     /* McBSP registers */
   CSM_PWL     : origin = 0x3F7FF8, length = 0x000008     /* CSM password locations in FLASHA */
   
  /* OD1		   : origin = 0x3f8000, length = 0x000100
   OD2		   : origin = 0x3f8100, length = 0x000400*/
   RAMH0       : origin = 0x3F8000, length = 0x002000     /* on-chip RAM block H0 */

}

 
SECTIONS
{
/*** Compiler Required Sections ***/
  /* Program memory (PAGE 0) sections */
   codestart         : > BEGIN_FLASH,      PAGE = 0                /* Used by file CodeStartBranch.asm */
   .text             : > FLASHABCDE,         PAGE = 0
   .cinit            : > FLASHABCDE,         PAGE = 0
   .pinit            : > FLASHABCDE,         PAGE = 0
   .reset            : > RESET,           PAGE = 0, TYPE = DSECT  /* We are not using the .reset section */

  /* Data Memory (PAGE 1) sections */
   .cio              : > RAMM0,            PAGE = 1
   .bss              : > RAMM0,            PAGE = 1                /* Should be empty with large memory model */
   .ebss             : > RAMH0,            PAGE = 1
   .const            : > FLASHABCDE         PAGE = 0                /* Should be empty with large memory model */
   .econst           : > FLASHABCDE         PAGE = 0
   .stack            : > RAMM1,            PAGE = 1
   .sysmem           : > RAMM0,            PAGE = 1                /* Should be empty with large memory model */
   .esysmem          : > RAMM0,            PAGE = 1
   .switch           : > FLASHABCDE         PAGE = 0


/*** User Defined Sections ***/

   pie_vect          : > PIE_VECT,         PAGE = 1
   secureRamFuncs    :   LOAD = FLASHABCDE,  PAGE = 0                /* Used by InitFlash() in SysCtrl.c */
                         RUN = RAML01, PAGE = 0 
                         LOAD_START(_secureRamFuncs_loadstart),
                         LOAD_END(_secureRamFuncs_loadend),
                         RUN_START(_secureRamFuncs_runstart)

   /* Allocate IQ math areas: */
   IQmath		    :   LOAD = FLASHABCDE,  PAGE = 0                /* Used by InitFlash() in SysCtrl.c */
                        RUN = RAML01, PAGE = 0 
                        LOAD_START(_secureMathFuncs_loadstart),
                        LOAD_END(_secureMathFuncs_loadend),
                        RUN_START(_secureMathFuncs_runstart)

   /* Allocate IQ math areas: */
   /*IQmath           : > FLASHC      PAGE = 0                  /* Math Code */
   
   
   IQmathTables     : > ROM         PAGE = 0, TYPE = NOLOAD   /* Math Tables In ROM */

/* ------------------------------------------------------------- */
/* The following allocations are required for the DSP28 Header file
   examples.  Each allocation maps a structure defined in the DSP28 
   header files to the memory location of those registers.  
*/
      
   /* Allocate Peripheral Frame 0 Register Structures:   */
   DevEmuRegsFile      : > DEV_EMU     PAGE = 1
   FlashRegsFile       : > FLASH_REGS  PAGE = 1
   CsmRegsFile         : > CSM         PAGE = 1
   /* XintfRegsFile    : > XINTF       PAGE = 1     */
   CpuTimer0RegsFile   : > CPU_TIMER0  PAGE = 1      
   CpuTimer2RegsFile   : > CPU_TIMER2  PAGE = 1  

   PieCtrlRegsFile     : > PIE_CTRL    PAGE = 1      
   PieVectTableFile    : > PIE_VECT    PAGE = 1

   /* Allocate Peripheral Frame 2 Register Structures:   */
   ECanaRegsFile       : > ECAN_A      PAGE = 1   
   ECanaMboxesFile     : > ECAN_AMBOX  PAGE = 1
   ECanaLamsFile	   : > ECAN_LAM    PAGE = 1 		  /* eCAN LAMS */
   co_StructsFile	   : > RAMH0	   PAGE = 1  /* ???? ?????? ?? ????*/	
   
   /* Allocate Peripheral Frame 1 Register Structures:   */
   SysCtrlRegsFile     : > SYSTEM      PAGE = 1
   SpiaRegsFile        : > SPI_A       PAGE = 1
   SciaRegsFile        : > SCI_A       PAGE = 1
   XIntruptRegsFile    : > XINTRUPT    PAGE = 1
   GpioMuxRegsFile     : > GPIOMUX     PAGE = 1
   GpioDataRegsFile    : > GPIODAT     PAGE = 1
   AdcRegsFile         : > ADC         PAGE = 1
   EvaRegsFile         : > EV_A        PAGE = 1
   EvbRegsFile         : > EV_B        PAGE = 1
   ScibRegsFile        : > SCI_B       PAGE = 1
   McbspaRegsFile      : > MCBSP_A     PAGE = 1

   /* CSM Password Locations */
   CsmPwlFile          : > CSM_PWL     PAGE = 1

}
