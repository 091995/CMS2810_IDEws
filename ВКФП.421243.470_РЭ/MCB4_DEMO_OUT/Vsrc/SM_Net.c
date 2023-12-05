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

 \file      SMNet.c
 \brief     ������ ������ ���������� ��� ������ � �����.  (��. TSM_Net)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup SMNet */
/*@{*/

#include "DSP28_Device.h"
#include "IQmathLib.h"
#include "main.h"

//!�������������.
//!
void SM_Net_Set_PDO_Mapping(TSM_Net *p, TCo_OdVars *ppc) {

    //��������� PDO ������� CANOpen
    //�� ��������
    co1_vars.co_TPDO1_1Mapping = 0x51210100;
    co1_vars.co_TPDO1_2Mapping = 0x51210200;
    co1_vars.co_TPDO1_3Mapping = 0x00000000;
    co1_vars.co_TPDO1_4Mapping = 0x00000000;
    co1_vars.co_TPDO1ITime = 100;
    co1_vars.co_TPDO1EventTimer = 20;//����� � �� ����� �����������

    co1_vars.co_TPDO2_1Mapping = 0x51210300;
    co1_vars.co_TPDO2_2Mapping = 0x51210400;
    co1_vars.co_TPDO2_3Mapping = 0x00000000;
    co1_vars.co_TPDO2_4Mapping = 0x00000000;
    co1_vars.co_TPDO2ITime = 100;
    co1_vars.co_TPDO2EventTimer = 100;

    co1_vars.co_TPDO3_1Mapping = 0x51210500;
    co1_vars.co_TPDO3_2Mapping = 0x51210600;
    co1_vars.co_TPDO3_3Mapping = 0x00000000;
    co1_vars.co_TPDO3_4Mapping = 0x00000000;
    co1_vars.co_TPDO3ITime = 100;
    co1_vars.co_TPDO3EventTimer = 100;

    co1_vars.co_TPDO4_1Mapping = 0x51210700;
    co1_vars.co_TPDO4_2Mapping = 0x51210800;
    co1_vars.co_TPDO4_3Mapping = 0x00000000;
    co1_vars.co_TPDO4_4Mapping = 0x00000000;
    co1_vars.co_TPDO4ITime = 100;
    co1_vars.co_TPDO4EventTimer = 1000;

    co1_vars.co_TPDO5_1Mapping = 0x51210900;
    co1_vars.co_TPDO5_2Mapping = 0x51210A00;
    co1_vars.co_TPDO5_3Mapping = 0x00000000;
    co1_vars.co_TPDO5_4Mapping = 0x00000000;
    co1_vars.co_TPDO5ITime = 100;
    co1_vars.co_TPDO5EventTimer = 1000;

    co1_vars.co_TPDO6_1Mapping = 0x00000000;
    co1_vars.co_TPDO6_2Mapping = 0x00000000;
    co1_vars.co_TPDO6_3Mapping = 0x00000000;
    co1_vars.co_TPDO6_4Mapping = 0x00000000;
    co1_vars.co_TPDO7_1Mapping = 0x00000000;
    co1_vars.co_TPDO7_2Mapping = 0x00000000;
    co1_vars.co_TPDO7_3Mapping = 0x00000000;
    co1_vars.co_TPDO7_4Mapping = 0x00000000;
    co1_vars.co_TPDO8_1Mapping = 0x00000000;
    co1_vars.co_TPDO8_2Mapping = 0x00000000;
    co1_vars.co_TPDO8_3Mapping = 0x00000000;
    co1_vars.co_TPDO8_4Mapping = 0x00000000;

    //�� �����
    co1_vars.co_RPDO1_1Mapping = 0x51210B00; //RPDO11
    co1_vars.co_RPDO1_2Mapping = 0x51210C00; //RPDO12
    co1_vars.co_RPDO1_3Mapping = 0x00000000;
    co1_vars.co_RPDO1_4Mapping = 0x00000000;
    co1_vars.co_RPDO1COBID = 0x0180;

    co1_vars.co_RPDO2_1Mapping = 0x51210D00; //RPDO21
    co1_vars.co_RPDO2_2Mapping = 0x51210E00; //RPDO22
    co1_vars.co_RPDO2_3Mapping = 0x00000000;
    co1_vars.co_RPDO2_4Mapping = 0x00000000;
    co1_vars.co_RPDO2COBID = 0x0280;

    co1_vars.co_RPDO3_1Mapping = 0x51210F00; //RPDO31
    co1_vars.co_RPDO3_2Mapping = 0x51211000; //RPDO32
    co1_vars.co_RPDO3_3Mapping = 0x00000000;
    co1_vars.co_RPDO3_4Mapping = 0x00000000;
    co1_vars.co_RPDO3COBID = 0x0180;

    co1_vars.co_RPDO4_1Mapping = 0x51211100; //RPDO41
    co1_vars.co_RPDO4_2Mapping = 0x51211200; //RPDO42
    co1_vars.co_RPDO4_3Mapping = 0x00000000;
    co1_vars.co_RPDO4_4Mapping = 0x00000000;
    co1_vars.co_RPDO4COBID = 0x0480;
    co1_vars.co_RPDO5_1Mapping = 0x00000000;
    co1_vars.co_RPDO5_2Mapping = 0x00000000;
    co1_vars.co_RPDO5_3Mapping = 0x00000000;
    co1_vars.co_RPDO5_4Mapping = 0x00000000;
    co1_vars.co_RPDO5COBID = 0x0200;
    co1_vars.co_RPDO6_1Mapping = 0x00000000;
    co1_vars.co_RPDO6_2Mapping = 0x00000000;
    co1_vars.co_RPDO6_3Mapping = 0x00000000;
    co1_vars.co_RPDO6_4Mapping = 0x00000000;
    co1_vars.co_RPDO6COBID = 0x0300;
    co1_vars.co_RPDO7_1Mapping = 0x00000000;
    co1_vars.co_RPDO7_2Mapping = 0x00000000;
    co1_vars.co_RPDO7_3Mapping = 0x00000000;
    co1_vars.co_RPDO7_4Mapping = 0x00000000;
    co1_vars.co_RPDO7COBID = 0x0400;
    co1_vars.co_RPDO8_1Mapping = 0x00000000;
    co1_vars.co_RPDO8_2Mapping = 0x00000000;
    co1_vars.co_RPDO8_3Mapping = 0x00000000;
    co1_vars.co_RPDO8_4Mapping = 0x00000000;
    co1_vars.co_RPDO8COBID = 0x0500;

    //�� ��������� ��� �������
    p->CANPDO1_DropCounter = ONLINE_TIMEOUT_MAX;
    p->CANPDO2_DropCounter = ONLINE_TIMEOUT_MAX;
    p->CANPDO3_DropCounter = ONLINE_TIMEOUT_MAX;
    p->CANPDO4_DropCounter = ONLINE_TIMEOUT_MAX;
    p->CANPDO5_DropCounter = ONLINE_TIMEOUT_MAX;
    p->CANPDO6_DropCounter = ONLINE_TIMEOUT_MAX;
}

//!���������� �������������� �������������, ������������� ������ �������.
//! \memberof TSM_Net
void SM_Net_Init(TSM_Net *p) {

	p->state = 0;
	p->state_prev = 0xff;

	//��� � ������ ���������� ��� �������� CANOpen
	co1_vars.co_productCode = 150;
	co1_vars.co_revisionNumber = 0x0070;    // ������ 0.7
	co1_vars.co_revisionNumber |= (25L << 16) | (4L << 21) | (23L << 25);  // 25/4/23 - day/month/year

	//��������� �������� CANOpen_1
    co1_Init(&co1_vars); //������������� �������� CANOpen

    //��������� PDO ������� CANOpen
    SM_Net_Set_PDO_Mapping(p, &co1_vars);
    //�������� ���������, ����������������� �������� CANOpen
    p->CANOpenReinitFlag = 1;

	//������ �������:
	//	������ ������: 50
	//	��������� ����� � SPI: 3000
	FaultLog.init((TLogger*)&FaultLog, 50, 3000,(Uint32*) &RTCclock.packed_time);//���� ��������� �� ����� ����� ���� ������������� � ����������� �� ������ �����

#if (defined(CANTORS_ENA)) || (defined(CANTOUSB_ENA))
//������ � CANopen ����� UART (����������� � CAN, ��� ���������)
//    co1_vars.co_nodeID = 15;
    CANtoRS.nodeID = (Uint16*)&co1_vars.co_nodeID; //����� ���� �� CANopen
    CANtoRS.callback = Z_co_receiveSDOrequest;//��������� �� ������� ��������� ������ �� �������� CANopen �� ������� SDO ���������
    CANtoRS.init(&CANtoRS);
#endif

#ifdef MODBUS_ENA
	// ����������� MODBUS
    ModBus.BaudRate = 38400;
    ModBus.LowPrescSpeed = 37500;
    ModBus.ExecutionFreq = 10000;
    ModBusRS.auto_res = 1;
    ModBus.RSNodeID = 1;
    ModBus.Init(&ModBus);
#endif
    SM_Net_Slow_Calc(p);
}

//!��������� ������.

//! ���������� �������������� �������������, ������� ������ ��������� �������.

//! \memberof TSM_Net
void SM_Net_Slow_Calc(TSM_Net *p) {


#ifdef CAN_1_ENABLE
	co1_vars.co_scaleNum0 = 1; //��� ���������������
	co1_vars.co_scaleNum1 = 100;	// %
	co1_vars.co_scaleNum2 = drv_params.freq_nom;	//��
	co1_vars.co_scaleNum3 = drv_params.U_nom;//���������� ������ ����������� �����������
	co1_vars.co_scaleNum4 = drv_params.I_nom; //��� ������ �������
	co1_vars.co_scaleNum5 = 1;
	co1_vars.co_scaleNum6 = 1;
	co1_vars.co_scaleNum7 = drv_params.Udc_nom; //���������� ��� �������
	co1_vars.co_scaleNum8 = drv_params.power; //18 � ������� 9.6 //��������
	co1_vars.co_scaleNum9 = 1;
	co1_vars.co_scaleNumA = 20; //�����������
	co1_vars.co_scaleNumB = 1;
	co1_vars.co_scaleNumC = 1;
	co1_vars.co_scaleNumD = 1;
	co1_vars.co_scaleNumE = 1;
	co1_vars.co_scaleNumF = 1;
	co1_vars.co_scaleNum10 = 1; //
	co1_vars.co_scaleNum11 = 1; //
	co1_vars.co_scaleNum12 = drv_params.power; //18 � ������� 10.6 //��������
	co1_vars.co_scaleNum13 = 360; //
	co1_vars.co_scaleNum14 = drv_params.speed_nom; //����������� ������� ��������
	co1_vars.co_scaleNum15 = 1; //
	co1_vars.co_scaleNum16 = 1; //
	co1_vars.co_scaleNum17 = ((((long) drv_params.Udc_nom) << 6) / (long) drv_params.I_nom); //R��� 10.6
	co1_vars.co_scaleNum18 = 1000;
	co1_vars.co_scaleNum19 = 1;
	co1_vars.co_scaleNum1A = 1;
	co1_vars.co_scaleNum1B = 1;
	co1_vars.co_scaleNum1C = 1;
	co1_vars.co_scaleNum1D = 1;
	co1_vars.co_scaleNum1E = 1;
	co1_vars.co_scaleNum1F = 1;

	co_Background(&co1_vars);
#endif

	drv_params.U_nom = 0.5759 * drv_params.Udc_nom;//����������� ������ ����������
	drv_params.power = ((long) 300) << 6; //�������� � ������� 10.6
	drv_params.freq_nom = ((float) drv_params.speed_nom * drv_params.p) / 60 + 0.5; //����� �������
	drv_interface.calc(&drv_interface);
	FaultLog.background_calc(&FaultLog);


/*
#ifdef MODBUS_ENA
	MBVarsConv.slow_calc(&MBVarsConv);
#endif
*/

	if (RTCclock.ClockOk)//���� ��������?
		FaultLog.time_ptr = (Uint32*) &RTCclock.packed_time; //����� ��� ����� ������ �� �����
	else
		FaultLog.time_ptr = (Uint32*) &global_time.PowerOn_time;//���� �� ��������, �� �� ������ �������� ������� ���������
    //���� ������ �����������������
    if (p->CANOpenReinitFlag)
        if (co_ReInit(&co1_vars))    //����������������� ������� 1 - �������
            p->CANOpenReinitFlag = 0;    //����� ����� ������� �����������������
}

//!������� ������

//!������� ������ ��������� ������� �������, ����� ������� "�������������" ����� ������ � ��������������
//! \memberof TSM_Net
void SM_Net_ms_Calc(TSM_Net *p) {
	//������� �������� ��������� ������� ���������� � ���������.
	//�� drv_status_code ������������ ������ ������� � UniCON
	if (drv_status.bit.ready == 1)
		drv_status_code = DRV_STATUS_READY;
	if (drv_status.bit.running == 1)
		drv_status_code = DRV_STATUS_RUNNING;
	if (drv_status.bit.testing == 1)
		drv_status_code = DRV_STATUS_TESTING;
	if (drv_status.bit.fault == 1)
		drv_status_code = DRV_STATUS_FAULT;
	if (drv_status.bit.alarm == 1)
		drv_status_code |= DRV_STATUS_ALARM;
	else
		drv_status_code &= ~DRV_STATUS_ALARM;
	if (drv_status.bit.overheat == 1)
		drv_status_code = DRV_STATUS_OVERHEAT;
	else
		drv_status_code &= ~DRV_STATUS_OVERHEAT;
	//������� �������� ������ ��� ������ (UniCON)
	pult_faults_lister.calc(&pult_faults_lister);
	sm_prot.Main_ErrorCode = 0xFF & pult_faults_lister.output;

    co_PWMPeriodISR(&co1_vars);  //������� CANOpen ������ �� �������
	//������� �������� �������� CANopen. ����� ��, � ���������, �������� ������������� dlog
    Can1BTInterface.calc(&Can1BTInterface, CpuTimer2Regs.TIM.all, &co1_vars);

#if (defined(CANTORS_ENA)) || (defined(CANTOUSB_ENA))
    CANtoRS.calc_1k(&CANtoRS);
#endif
/*
#ifdef MODBUS_ENA
	MBVarsConv.calc(&MBVarsConv);
#endif
*/

}

void SM_Net_fast_Calc(TSM_Net *p) {

#ifdef MODBUS_ENA
	ModBus.Execute(&ModBus);
#endif
}

/*@}*/
