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

 \file      SMSys.h
 \brief     ������-������� ��� ������� ��������� �������. (��. TSM_Sys)
 \author    ��� "��� ������". http://motorcontrol.ru

 \defgroup  SMSys ������-������� ��� ������� ��������� �������. (��. TSM_Sys)
 @{
*/

/*@{*/
#include "DSP28_Device.h"
#include "IQmathLib.h"
#include "main.h"

//! ������������� ������� ���������� ����� ���������

//!������������� ��������� ������� � ��������� ���������� �������.
//!����� ������������� ����������� ����������, ������ ��������� �������������
//!� ���������� ������� (���������, CANOpen).
//! \memberof TSMSys
void SM_Sys_Init(TSM_Sys *p) {

    sw.HardwareType = 3;

    spimem.init(&spimem);
    cmd.all = 0;
    drv_status.all = 0;

    adc.init(&adc_calibration); /* Call init function for adc1 */

    sm_net.init(&sm_net); //������� �����
    sm_prot.init(&sm_prot); //������
    sm_cmd_logic.init(&sm_cmd_logic); //������ ���������/����������
    sm_ctrl.init(&sm_ctrl); //��������� ������� ����������
    pwm.init(&pwm); //������ ���
    cur_par.init(&cur_par); //������ ������� ����������� �������
    leds.init(&leds);//����������
    udControl.init(&udControl); //������� ������� ��� ����� ����������
    DIO_Init(); //���������� �����/������
    FanControl.init(&FanControl); //����������
    //���������� ����� (������� ��� �����. ����)
    global_time.init(&global_time);

    drv_params.sens_type = drv_params.sens_type & 7; //�������� ������� ����� ����������, ��� �����
    if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //� ���� ������� ������ ��� �� ��������� �����
        DPReCAP.Init(&DPReCAP); //��� ����.
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER){ //� ���� ������� ������ �������
        //�������� ������������ �������
        //posspeedEqep.speed_nom = drv_params.speed_nom;    //������� ��������
        posspeedEqep.pole_pairs = drv_params.p;    //���-�� ��� ������� ���������
        posspeedEqep.direction = 1;    //����������� ��������
        posspeedEqep.RevolutionCounter=0;
        posspeedEqep.init(&posspeedEqep);//������������� ������ ��������
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //� ���� ������� ������ ������ � SSI �����������. ������� ������������ ������ ����� ��������������!
        //�������� ������ ������� ��������� SSI
        SSI_Encoder.speed_nom = drv_params.speed_nom;    //������� ��������
        SSI_Encoder.pole_pairs = drv_params.p;    //���-�� ��� ������� ���������
        SSI_Encoder.rotation_dir = 0;    //����������� ��������
        SSI_Encoder.RevolutionCounter=0;
        SSI_Encoder.init(&SSI_Encoder);//������ ��������� SSI
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_ENC_HALL){
        //�������� ������������ �������
        DPReCAP.Init(&DPReCAP); //��� ����.
        //posspeedEqep.speed_nom = drv_params.speed_nom;    //������� ��������
        posspeedEqep.pole_pairs = drv_params.p;    //���-�� ��� ������� ���������
        posspeedEqep.direction = 1;    //����������� ��������
        posspeedEqep.RevolutionCounter=0;
        posspeedEqep.init(&posspeedEqep);//������������� ������ ��������
    }

    //�������� ������ ��� ����������� �� ������ ���������� (UniCON)
    pult_faults_lister.num_of_words = 2;
    pult_faults_lister.out_refresh_devisor = 1000; //��� ������ � �� ������� ������ ���������� ����� ����� 1���
    pult_faults_lister.w_ptrs[0] = (Uint16*) &sm_prot.masked_bit_fault1;//������������ ��� ����� ������ ������ �����
    pult_faults_lister.w_ptrs[1] = (Uint16*) &sm_prot.masked_bit_fault2;

    AutoOffset.FilterK = _IQ(0.00001);//���������� ������� ������� ��� ������������ ���
    AutoOffset.init(&AutoOffset); //���� �������� ��������� ������� ��� (����)

	//��������� ������ CPU0
	CpuTimer0Regs.PRD.all = 14999;
	CpuTimer0Regs.TCR.bit.SOFT = 1;
	CpuTimer0Regs.TCR.bit.FREE = 1;
	CpuTimer0Regs.TCR.bit.TIE = 1;

	//��������� ������ CPU2
	CpuTimer2Regs.PRD.all = 0xFFFFFFFF;
	CpuTimer2Regs.TCR.bit.SOFT = 1;
	CpuTimer2Regs.TCR.bit.FREE = 1;
	CpuTimer2Regs.TCR.bit.TIE = 1;

	//��������� 1�� �������
	EvbRegs.T4PR = 4688; //;9375;
	EvbRegs.T4CON.all = 0x1440; //16x

	EvbRegs.EVBIMRB.bit.T4UFINT = 1;
	EvbRegs.EVBIFRB.bit.T4UFINT = 1;

	EvbRegs.EVBIMRA.bit.CMP6INT = 1;
	EvbRegs.EVBIFRA.bit.CMP6INT = 1;

	EALLOW;

	PieVectTable.T4UFINT = &EvbTimer4;
	PieVectTable.PDPINTA = &pdpinta_protect_isr;
	PieVectTable.CAPINT4 = &cap1_interrupt_isr;
	PieVectTable.CAPINT5 = &cap2_interrupt_isr;
	PieVectTable.CAPINT6 = &cap3_interrupt_isr;
	PieVectTable.TINT0 = &CPUTimer0_isr;

	EDIS;
	// Enable PIE  interrupt 3 for T4UFINT
	PieCtrlRegs.PIEIER5.all |= M_INT3;
	// Enable CPU INT5 for T4UFINT:
	IER |= M_INT5;

	// Enable CPU INT1 for PDPINTA:
	PieCtrlRegs.PIEIER1.all |= M_INT1;
	IER |= M_INT1;
	// Enable PIE interrupt 7 for TINT0
	PieCtrlRegs.PIEIER1.all |= M_INT7;
	IER |= M_INT1;
	// Enable CPU INT1 for CAP4INT:
	PieCtrlRegs.PIEIER5.all |= M_INT5;
	IER |= M_INT5;
	// Enable CPU INT2 for CAP5INT:
	PieCtrlRegs.PIEIER5.all |= M_INT6;
	IER |= M_INT5;
	// Enable CPU INT3 for CAP6INT:
	PieCtrlRegs.PIEIER5.all |= M_INT7;
	IER |= M_INT5;

	//����� �������� ����� ���������� ������ (���� ����)
	EvaRegs.EVAIFRA.all = (1 << 0);
	EvbRegs.EVBIFRA.all = (1 << 0);

    sm_sys.state = SYS_READY;

}

//!��������� ������ (�������).

//!����� ��������� �������� ��������� �������
//! \memberof TSMSys
void SM_Sys_Slow_Calc(TSM_Sys *p) {


    //spimem.slow_calc(&UserMem);//���������������� ������ � ��
    RTCclock.slowCalc(&RTCclock);//���� ��������� �������
    sm_prot.slow_calc(&sm_prot);//������ �����
    sm_net.slow_calc(&sm_net); //������� ��� ������ ���������������� ���������
    dlog.background_analyzer(&dlog); //������� ���������� ������ �������������������
    global_time.slow_calc(&global_time);
    rmp.slow_calc(&rmp); //�������� ������������� ������� �� ��������������� �� ���������� �������������
    pwm.slow_calc(&pwm); //������� ���������� ������ ��� (�������� ���������������� �������)
    adc.slow_calc(&adc); //������� ���������� ���
    cur_par.slow_calc(&cur_par); //������ ������� ����������� �������
    AutoOffset.slow_calc(&AutoOffset);
    posspeedEqep.slow_calc(&posspeedEqep);//������������� ������ ��������
    RotorObserver.slow_calc(&RotorObserver);//����������� ������ ������ ��
    DIO_slow_calc(); //���������� �����/������
    FanControl.slow_calc(&FanControl);//����������

    //�������� ������������� ��� ��������������� ����� � ����������
    drv_params._1_Udc_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.Udc_nom));
    drv_params._1_I_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.I_nom));
    drv_params._1_U_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.U_nom));

    if (sw.Reboot & 1) { //������� ������������
        sw.Reboot = 0; //���������� �
        if (sm_ctrl.state == CTRL_STOP) { //��������������� ������ � ��������
            //��������� ����� ����� � ������� WatchDog
            EALLOW;
            SysCtrlRegs.WDCR = 0x28;
            SysCtrlRegs.WDKEY = 0xFF;       //���������� �������� reset ��� ��� ���� ������������
            EDIS;
        }
    }

    //����� ������� �������� ��� ��� ����� ���
    //������ ������ ������ � �������� � ���������� ������
    if ((sw.AutoOffset & 1) &&
        (sm_ctrl.state == CTRL_STOP)){
        AutoOffset.Enabled=1;
    } else
        AutoOffset.Enabled=0;

}

void SM_Sys_ms_Calc(TSM_Sys *p) {
    sm_cmd_logic.ms_calc(&sm_cmd_logic); //��������� ������ ����������
    sm_net.ms_calc(&sm_net); //������� ��� ������ ���������������� ���������
    adc.ms_calc(&adc); //���
    sm_prot.ms_calc(&sm_prot); //������
    AutoOffset.ms_calc(&AutoOffset); //���� �������� ��������� ������� ���

    leds.msCalc(&leds);//����������
    RTCclock.msCalc(&RTCclock);//����
    //spimem.ms_calc(&UserMem);//���������������� ������ � ��
    if ((drv_params.sens_type == 2) || (drv_params.sens_type == 3)){ //� ���� ������� ������ ��� �����
        DPReCAP.ms_calc(&DPReCAP);
    }
    global_time.ms_calc(&global_time);

    DIO_fast_calc(); //���������� �����/������
}

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(SM_SYS_Fast_Calc,"secureRamFuncs");
#endif

//!������� ������ (������ 10���).
//!����� ������� �������� ��������� �������
//! \memberof TSMSys
void SM_Sys_Fast_Calc(TSM_Sys *p) {
    sm_net.fast_calc(&sm_net);//������ ���������������� ���������
    if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER) //� ���� ������� ������ �������
        posspeedEqep.calc(&posspeedEqep); //��� �������
    if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //� ���� ������� ������ ��� �����

        DPReCAP.Angle6Calc(&DPReCAP); //��� ����, ��������� ���� � ��������� 60 �������� (��������� � DPReCAP.Angle6)
        DPReCAP.AngleErrorCalc(&DPReCAP);
        if (DPReCAP.CAPCalcEna1==0){
            DPReCAP.CAPCalcEna1=1;
            EvbRegs.EVBIFRC.bit.CAP4INT = 1; // ���������� ���� ����������
        }
        if (DPReCAP.CAPCalcEna2==0){
            DPReCAP.CAPCalcEna2=1;
            EvbRegs.EVBIFRC.bit.CAP5INT = 1; // ���������� ���� ����������
        }
        if (DPReCAP.CAPCalcEna3==0){
            DPReCAP.CAPCalcEna3=1;
            EvbRegs.EVBIFRC.bit.CAP6INT = 1; // ���������� ���� ����������
        }

        DPReCAP.AngleCalc(&DPReCAP); //��� ����, ������������ ���� ��������� (��������� � DPReCAP.Angle)
        DPReCAP.SpeedCalc(&DPReCAP); //��� ����, ������ �������� �������� (DPReCAP.speed)
        //DPReCAP.calc_10k(&DPReCAP); //��� ����, ��������� �������
    }
    if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //������ � ����������� SSI. ����� ������������� ������� ������������ ����!
        SSI_Encoder.calc(&SSI_Encoder);//������ ��������� SSI
    }

    adc.fast_calc(&adc); //���
    dlog.update(&dlog); //������������������� ������
    sm_prot.fast_calc(&sm_prot); //������
    sm_ctrl.fast_calc(&sm_ctrl); //������� ���������� ������� ������� ����������
    udControl.calc(&udControl);//������� ������� ��� ����� ����������

    CANtoRS.calc_10k(&CANtoRS);

    global_time.calc(&global_time);

    cur_par.calc(&cur_par); //������ ������� ����������� �������
    drv_params.sens_type = drv_params.sens_type & 7; //�������� ������� ����� ����������, ��� �����

#ifdef WATCHDOG_ON
    WatchDog.calc();//���� ���������� ������ ������������, ���������� ��� �����
#endif //WATCHDOG_ON
}

/*@}*/

