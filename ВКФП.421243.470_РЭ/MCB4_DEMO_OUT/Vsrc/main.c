/*!
    Copyright 2023 ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      main.h
 \brief     ������� ������������ ���� �������.
���������� � ���� ��� ������������ ����� ���� �������,
�������� ���������� (extern) ���� �������� ������
���������� �������� � ����������.

 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  MAIN ������� ���� �������

@{*/
/*@{*/

#ifdef __cplusplus
extern "C"
{
#endif
#include "IQmathLib.h"         	// ���������� IQmath
#include "DSP28_Device.h"		//
#include "main.h"
#include "string.h" //��� memcpy
#ifdef __cplusplus
}
#endif

TClarke clarke = CLARKE_DEFAULTS; //!<������ ��������������
TPark park = PARK_DEFAULTS; //!<������������ ��������������
TIPark ipark = IPARK_DEFAULTS; //!<�������� ������������ ��������������
TPidReg3 pid_id = PIDREG3_DEFAULTS; //!<���. ���� �� ��� d
TPidReg3 pid_iq = PIDREG3_DEFAULTS; //!<���. ���� �� ��� q
TPidReg3 pid_ia = PIDREG3_DEFAULTS; //!<���. ���� ����� ���
TPidReg3 pid_spd = PIDREG3_DEFAULTS; //!<���. ��������
TPidReg3_pos pid_pos = PIDREG3_DEFAULTS_POS; //!<���. ���������
TRelayReg i_a_reg = RELAY_REG_DEFAULTS; //!<��������� ���� ���� A (��� ������ SRM)
TRelayReg i_b_reg = RELAY_REG_DEFAULTS; //!<��������� ���� ���� A (��� ������ SRM)
TRelayReg i_c_reg = RELAY_REG_DEFAULTS; //!<��������� ���� ���� A (��� ������ SRM)
TVhzProf vhz = VHZPROF_DEFAULTS;    //!< ����� U/f=const
TSM_Sys sm_sys = SM_Sys_DEFAULTS; //!< ������� �������� ��� ������ ���� �������
Uint16 disp_group_number = 0;   //!< ���������� ��� �������� CANOpen � Unicon
TDataLog dlog = DATALOG_DEFAULTS; //!< ������ ������������������� ���������� CANOpen
TSM_Protect sm_prot = SM_PROTECT_DEFAULTS;  //!< ������ �����
TBitsToEnumNums pult_faults_lister = BITS_TO_ENUM_NUMS_DEFAULTS; //!<�������� ������ ��� Unicon
TSM_Ctrl sm_ctrl = SM_CTRL_DEFAULTS; //!< ������� ���������� �������, ��������� ��������� ����������
TSM_CmdLogic sm_cmd_logic = SM_CMD_LOGIC_DEFAULTS; //!< ��������� ���������������� ������ ����������
TSM_Net sm_net = SM_NET_DEFAULTS;   //!< �������� ��� ������ ������� ���������
TRMPCtrl rmp = V_RMP_CTRL_DEFAULTS;     //!< �������� �������������
TAdcDrv adc = ADC_DRV_DEFAULTS;     //!< ������ ���
TPWM_Module pwm = PWM_Module_DEFAULTS;  //!< ������ ���
Texcitation pwm_ex = excitation_DEFAULTS;   //!< ������ ����������� ��
TDPReCAP DPReCAP = DPRECAP_DEFAULTS; //!< ������ ��� �� ��������� �����
TEncoder posspeedEqep = ENCODER_DEFAULTS; //!< ������ ��� ���� �������                              //!<������ ��������� ���������������� ��������
TCurPar cur_par = TCUR_PAR_DEFAULTS; //!< ������ ������� � �������� ������� ����������� ������� - ��������, ��������
TSpiMem spimem = USERMEMORY_DEFAULTS; //!< ������ ������ � ����������������� �������.
Tled leds = LED_DEFAULTS; //!< ������ ��� ��������� ������� ������������
TCanBTInterface Can1BTInterface = T_CANBT_INTERFACE_DEFAULTS;//!<�������� �������� CANopen
//TCanBTInterface Can2BTInterface = T_CANBT_INTERFACE_DEFAULTS;//!<�������� �������� CANopen
TRTCClock RTCclock = RTC_CLOCK_DEFAULTS; //!< ������ ������ � ������ ����������������. "spi" - �� ������������ �������� �������������
TAutoOffset AutoOffset = AUTO_OFFSET_DEFAULTS;  //!<�������������� ���������� �������� ����� ���
TSSI_Encoder SSI_Encoder = SSI_ENCODER_DEFAULTS; //!<������� ��������� ������� ��������� � SSI �����������
TRotorObserver RotorObserver = ROTOR_OBSERVER_DEFAULTS; //!<���������� ����������� ��������������� ������ ������������ ���������
//TCANtoRS CANtoRS = CAN_TO_RS_DEFAULTS; //!<������ ��� ������ � ��������� CANopen ����� UART (RS). ������� CAN �������������� � UART

TModBus ModBus = MODBUS_DEFAULTS;                        //!<������� ModBus
MODBUS_INT MBInternals = MODBUS_INT_DEFAULTS;   //!<������� ModBus �����. �����.
MODBUS_RS ModBusRS = MODBUS_RS_DEFAULTS;            //!<������� ModBus ������ RS
TMBVarsConv MBVarsConv = MBVARSCONV_DEFAULTS;//!< ������ �������������� ������ �� ������� 16 �������� Modbus � ������ ������� ���������� (IQ 24)

TCANtoRS CANtoRS = CAN_TO_RS_DEFAULTS; //!<������ ��� ������ � ��������� CANopen ����� UART (RS). ������� CAN �������������� � UART

//TMBVarsConv MBVarsConv = MBVARSCONV_DEFAULTS;//!< ������ �������������� ������ �� ������� 16 �������� Modbus � ������ ������� ���������� (IQ 24)
TDrvInterface drv_interface = DRV_INTERFACE_DEFAULTS;   //!<��������� ��� ������ � ������� ������, ������� � �.�.
TLogger FaultLog = LOGGER_DEFAULTS;         //!<���������������� ������
TGlobalTime global_time = GLOBAL_TIME_DEFAULTS; //!<������ � ������
TUdControl udControl = UD_CONTROL_DEFAULTS; //!<������� ������� ��� ����� ����������
TFanControl FanControl = FAN_CONTROL_DEFAULTS; //!<����������

TRefs refs; //!< ��������� � ��������� (����, ��������)
TCmd cmd = { 0 }; //!< ��������� � ��������� ����������
TDrvStatus drv_status = { 0 }; //!< ������� ������ �������
TDrvParams drv_params; //!< ��������� ���������
TSysSwitches sw; //!< ��������� ���������� ��������� ������� ����������

TPDO_PACK_1 TPDO_pack1 = PDO_PACK_DEFAULTS;
TPDO_PACK_2 TPDO_pack2 = PDO_PACK_DEFAULTS;
TPDO_PACK_3 TPDO_pack3 = PDO_PACK_DEFAULTS;
TPDO_PACK_4 TPDO_pack4 = PDO_PACK_DEFAULTS;
TPDO_PACK_1 RPDO_pack3 = PDO_PACK_DEFAULTS;
RPDO_PACK_1 RPDO_pack1 = PDO_PACK_DEFAULTS;
RPDO_PACK_2 RPDO_pack2 = PDO_PACK_DEFAULTS;

Uint32 VendorToken=0x33333333;//!< ���������� ���� �������������, ������ ��� ��������� UniCON � COODEdit ��� ��������� ������� ������� ������ ���������������
int drv_status_code; //!<������ ������� ���������� � ���� ��������� (�����, ������ � �.�.)

//���������� ��� ������� - �������� � ������� CANOpen,
//� ��� ����� ����������� ����� ������ ���������� � ��������� �
//� UniCon, � ����� ������������ �� �������� � �� ��� ������� � ������ �� ����.
volatile long Debug1 = 0;
volatile long Debug2 = 0;
volatile Uint16 Debug3 = 0;
volatile Uint16 Debug4 = 0;
volatile long DebugW1 = 0;
volatile long DebugW2 = 0;
volatile long DebugW3 = 0;
volatile long DebugW4 = 0;

//�������� ���������� ������ �������
Uint16 CounterCAP_isr = 0;
Uint16 cap0_counter = 0;
Uint16 cap1_counter = 0;
Uint16 cap2_counter = 0;

Uint16 LoopCounter = 0; //!< ������� �������� �������� �����

Uint32 msCounter=0;
Uint32 FastCounter=0;
Uint32 TIsr10;
Uint32 TIsr1;

/*! ������ ����������� ��������� - main()  */
//! \memberof main
int main(void) {
	/***********************************/
	/* ������ ������������� ���������� */
	/***********************************/

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

	InitFlash();			//���������� ��������	// Initialize the FLASH (FILE: SysCtrl.c)
#endif

	pwm.Off(&pwm); //��������� ��� (�� ������ ������)


    //�������������, ����������, �����.
    sm_sys.init(&sm_sys);
    sm_sys.IntEna=1;//������������� ���������

	EINT;
	// Enable Global interrupt INTM
	ERTM;
	// Enable Global realtime interrupt DBGM

	/********************************************************/
	/************ ������� ��������� ���� ********************/
	/********************************************************/
	for (;;) {
	    LoopCounter++;
		sm_sys.slow_calc(&sm_sys);//������ ����� ����������
	}
}


unsigned long prevCpuTimer_ms;
unsigned long T_ms;

/*! 1�� ������  */
//! \memberof main
interrupt void EvbTimer4(void) {
    prevCpuTimer_ms = CpuTimer2Regs.TIM.all; //��� �������� ������
    EINT;

    sm_sys.ms_calc(&sm_sys); //�������������� ������ �����
    msCounter++;

    T_ms = prevCpuTimer_ms - CpuTimer2Regs.TIM.all;

    if (T_ms > 140000)
        sm_prot.bit_fault1 |= F_PROGRAM_1K; //���� ������ ������� ������, ������

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
	sm_sys.fast_calc(&sm_sys);
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

	if (Tpwm > 14000)
        sm_prot.bit_fault1 |= F_PROGRAM_10K; //���� ������ ������� ������, ������
}

Uint16 ePWM0_TZ_isr_counter = 0;
/*! ���������� ������ ��������� ������� "a"  */
//! \memberof main
interrupt void pdpinta_protect_isr(void) {

    ePWM0_TZ_isr_counter++;

    pwm.Off(&pwm);

    if (sm_ctrl.state!=CTRL_STOP)
    {
        sm_prot.bit_fault1|= F_PDPINT;
    }
    sm_ctrl.state=CTRL_STOP;

    //���������� ����� ���������� �� ���� �����
	EvaRegs.EVAIMRA.all |= (1 << 0); //EvaRegs.EVAIMRA.bit.PDPINTA = 1;
	EvaRegs.EVAIFRA.all |= (1 << 0); //EvaRegs.EVAIFRA.bit.PDPINTA = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(cap1_interrupt_isr,"secureRamFuncs");
#endif
/*! ���������� ��� �����1  */
//! \memberof main
interrupt void cap1_interrupt_isr(void) {


    if (DPReCAP.CAPCalcEna1 == 0) { //���� ������� ��������� ��������
        DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
        DPReCAP.CAP_WrongEdgeCnt1++;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
        return;
    }
    DPReCAP.CAPCalcEna1 = 0;//������ ����� ��������, ����� ������ ���������� 10���. ���� ������� ��� ������, ��� ������

    CounterCAP_isr++;//����� ������� ���� ���������� ������ �������
    CounterCAP_isr = CounterCAP_isr & 0xF;
    cap0_counter++;//������� ���������� ������ ����� ������
    //������ �� ��������� ��� ���� �������� ����� ����������� ������� ���� � ��������� 60 ��������.
    //������� ������� ��������  DPReCAP.Angle6 - ���� � ��������� 60 ��������.
    DPReCAP.Timer1 = CpuTimer2Regs.TIM.all;
    DPReCAP.Angle6Calc(&DPReCAP);
    //���������� ������ ������� ������1 (0, ���� ������� � ����, �� �� ��������������� �� ������� ��� �������, � ����������� �� ������ ������������ ������...).
    //�������� ����� ����� ���� ��������� � ����������� ��� ������� ������������� ���� � ������� �������� (��������)
    DPReCAP.CAP1Calc(&DPReCAP);

	EvbRegs.EVBIFRC.bit.CAP4INT = 1; // ���������� ���� ����������
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

}


#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(cap2_interrupt_isr,"secureRamFuncs");
#endif
/*! ���������� ��� �����2  */
//! \memberof main
interrupt void cap2_interrupt_isr(void) {

    if (DPReCAP.CAPCalcEna2 == 0) { //���� ������� ��������� ��������
        DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
        DPReCAP.CAP_WrongEdgeCnt2++;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
        return;
    }
    DPReCAP.CAPCalcEna2 = 0;

    CounterCAP_isr++;
    CounterCAP_isr = CounterCAP_isr & 0xF;
    cap1_counter++;
    DPReCAP.Timer2 = CpuTimer2Regs.TIM.all;
    DPReCAP.Angle6Calc(&DPReCAP);
    DPReCAP.CAP2Calc(&DPReCAP);

    EvbRegs.EVBIFRC.bit.CAP5INT = 1; // ���������� ���� ����������
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}


#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(cap3_interrupt_isr,"secureRamFuncs");
#endif
/*! ���������� ��� �����3  */
//! \memberof main
interrupt void cap3_interrupt_isr(void) {

    if (DPReCAP.CAPCalcEna3 == 0) { //���� ������� ��������� ��������
        DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
        DPReCAP.CAP_WrongEdgeCnt3++;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
        return;
    }
    DPReCAP.CAPCalcEna3 = 0;

    CounterCAP_isr++;
    CounterCAP_isr = CounterCAP_isr & 0xF;
    cap2_counter++;
    DPReCAP.Timer3 = CpuTimer2Regs.TIM.all;
    DPReCAP.Angle6Calc(&DPReCAP); //���� ������, �� � ������ ������� ����� �� ���� ������ ��� �����, ��� ��� ���������� �����������, � Angle6Calc ���
    DPReCAP.CAP3Calc(&DPReCAP);

    EvbRegs.EVBIFRC.bit.CAP6INT = 1; // ���������� ���� ����������
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

Uint16 scib_rx_isr_counter=0;
Uint16 scib_tx_isr_counter=0;

interrupt void scib_rx_isr(void)
{
    scib_rx_isr_counter++;
    EINT;

    CANtoRS.receive(&CANtoRS);

    CANTORS_SCIXREGS.SCIFFRX.bit.RXFFINTCLR=1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
/*@}*/
