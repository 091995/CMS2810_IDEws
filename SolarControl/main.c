
#ifdef __cplusplus
extern "C"
{
#endif

#include "DSP28_Device.h"       //
#include "main.h"
#include "string.h" //��� memcpy
#ifdef __cplusplus
}
#endif
/**
 * main.c
 */

//TPWM_Module pwm = PWM_Module_DEFAULTS;
//TSM_Sys sm_sys = SM_Sys_DEFAULTS;
Uint32 msCounter=0;
Uint32 FastCounter=0;

int main(void)
{
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

    InitFlash();            //���������� ��������   // Initialize the FLASH (FILE: SysCtrl.c)
#endif



    //sm_sys.init(&sm_sys);


    EINT;
    // Enable Global interrupt INTM
    ERTM;
    // Enable Global realtime interrupt DBGM

    while(1){


    }

}

unsigned long prevCpuTimer_ms;
unsigned long T_ms;

/*! 1�� ������  */
//! \memberof main
interrupt void EvbTimer4(void) {
    prevCpuTimer_ms = CpuTimer2Regs.TIM.all; //��� �������� ������
    EINT;

    //sm_sys.ms_calc(&sm_sys); //�������������� ������ �����
    msCounter++;

    T_ms = prevCpuTimer_ms - CpuTimer2Regs.TIM.all;

//    if (T_ms > 140000)
//        dcs_prot.bit_fault1 |= F_PROGRAM_1K; //���� ������ ������� ������, ������

    //��� ������������� ���������� (���� ���-�� �������, � �� �����, ������ ��� ����).
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
/*! 10��� ������  */
//! \memberof main
interrupt void CPUTimer0_isr(void) {
    //���������� ����������
    DINT;
    //�� ������� ������
    //����� ��������� ������������ ������� ����������
    PieCtrlRegs.PIEIER9.all &= ~M_INT5;  //���������� ������ 9 (CAN)
    PieCtrlRegs.PIEIER5.all &= ~M_INT3;  //���������� ������ 5 (1�� - T4UFINT)
    asm(" nop");
    //����� ��������� ����������, ����� �������
    asm(" nop");
    //��������� ������, �����, ���� ���������� ��� �������� �������������� ���������,
    asm(" nop");
    //� �� ��� ��������� ��������� ����, ��������� � ����� ������� ����������
    asm(" nop");
    //������ ����������, ������, �������� ������������ � ������ ������
    asm(" nop");
    //����� ����� ��������� ����� ���� DINT
    IFR &= ~M_INT9;  //������� ����� - ��� ����� ���������� �� �� "nop" (CAN)
    IFR &= ~M_INT5; //������� ����� - ��� ����� ���������� �� �� "nop" (T4UFINT)
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;  //������������, ����� ��� �� ������������ ��� ���( CAN)
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;  //������������, ����� ��� �� ������������ ��� ��� (T4UFINT)
    //  PieCtrlRegs.PIEIER5.bit.INTx3=0;// &= ~M_INT3;
    //  IER &= ~M_INT5;

    //���� ��������� ��� ��������� ������������ ���������
    prevCpuTimer_10k = CpuTimer2Regs.TIM.all; //150��� ������, ��� ������� ���-�� ������

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    EINT;
    IER |= 1;
    FastCounter++;

    //�������� ������ �����, ��� ���� ������� ��� � 10���
   // sm_sys.fast_calc(&sm_sys);
    DINT;

    // Enable more interrupts from this timer
    //  EvbRegs.EVBIMRA.all |= (1<<9);
    //  EvbRegs.EVBIFRA.all |= (1<<9);

    //��������� �����
    PieCtrlRegs.PIEIER9.all |= M_INT5; //CAN
    PieCtrlRegs.PIEIER5.all |= M_INT3; //T4UFINT

    //������� ���-�� ����������� ������
    Tpwm = prevCpuTimer_10k - CpuTimer2Regs.TIM.all;

    if (Tpwm > TpwmMax)//��������� ��������
        TpwmMax = Tpwm;
//
//    if (Tpwm > 14000)
//        sm_prot.bit_fault1 |= F_PROGRAM_10K; //���� ������ ������� ������, ������
}

Uint16 ePWM0_TZ_isr_counter = 0;
static int _TZ[6];
/*! ���������� ������ */
//! \memberof main
interrupt void pdpinta_protect_isr(void) {

    ePWM0_TZ_isr_counter++;
    //pwm.Off(&pwm);

    _TZ[0] = GpioMuxRegs.GPDMUX.bit.T1CTRIP_PDPA_GPIOD0;
    _TZ[2] = GpioMuxRegs.GPDMUX.bit.T3CTRIP_PDPB_GPIOD5;

//    if(_TZ[0] == 0) pwm.PDP_inv1=1;
//    if(_TZ[2] == 0) pwm.PDP_pulses_block_Imax=1;
//
//    if ((_TZ[0]==1)&&(_TZ[2]==1)){ //signal if no source of TZ detected
//        pwm.PDP_inv_ext_lost=1;
//        }



    //���������� ����� ���������� �� ���� �����
    EvaRegs.EVAIMRA.all |= (1 << 0);
    EvaRegs.EVAIFRA.all |= (1 << 0);

    EvbRegs.EVBIMRA.all |= (1 << 0);
    EvbRegs.EVBIFRA.all |= (1 << 0);
//
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

