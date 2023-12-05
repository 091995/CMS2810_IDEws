

#include "DSP.h"
#include "V_IQmath.h"
#include "math.h"
#include "main.h"
//#include ""
//!�������������.

//!���������� �������������� �������������, ������������� ������ �������.
//! \memberof TSM_Net
void SM_Net_Init(TSM_Net *p) {
int ii;
	p->state = 0;
	p->state_prev = 0xff;

	//��������� �������� CANOpen
//	co2_vars.settings.LoadParamsFromUserMemory_ena = 1;//��������� ��������� �������� ���������� �� �����
//	co2_vars.settings.CAN_ISR_priority = IRQ_PRIORITY_CAN;//���������� ���������� ��������� CAN (���������� ������ ����������)
//	co2_vars.settings.MultiPDO_ena = 0;//���������� ��������� PDO ��� ����� ������ ���� (����. �������)
//	co2_vars.settings.RX_PDO_Callback_ena = 0; //�� �������� ������� ��������� ������ ��� ������ PDO
//	co2_vars.settings.AutoBusON_ena = 1; //������������� ������������� CAN ��� ������� �� �����
//	co2_vars.settings.BlockTransfer_ena = 1;//��������� ������� �������� (����� ��� ������������)
//	co2_Init(&co2_vars); //������������� �������� CANOpen

	   	co2_vars.settings.LoadParamsFromUserMemory_ena = 1;//��������� ��������� �������� ���������� �� �����
	    co2_vars.CAN_REGS = (NT_CAN_TypeDef *)NT_CAN_BASE;//�������� �������� ����� ��������� ��������� CAN
	    co2_vars.settings.CAN_ISR_priority = IRQ_PRIORITY_CAN;//���������� ���������� ��������� CAN (���������� ������ ����������)
	    co2_vars.settings.CAN_IRQn = CAN2_IRQn;//�������� ����� ���������� CAN2 �� ������� ���������� � ������� CANOpen
	    co2_vars.settings.MultiPDO_ena = 0;//���������� ��������� PDO ��� ����� ������ ���� (����. �������)
	    co2_vars.settings.RX_PDO_Callback_ena = 0; //�� �������� ������� ��������� ������ ��� ������ PDO
	    co2_vars.settings.AutoBusON_ena = 1; //������������� ������������� CAN ��� ������� �� �����
	    co2_vars.settings.BlockTransfer_ena = 1;//��������� ������� �������� (����� ��� ������������)
	    co2_vars.settings.speedCANTablePointer = &canSpeedTable;//�������� �������� ��������� ��� ��������� �������� CAN
	    co2_vars.settings.resetCPU = propReset;//�������� �������� ����� ������� ������ ����������������
	    co2_Init(&co2_vars); //������������� �������� CANOpen

//
//	for (ii=0;ii<7;ii++){
//
//		co2_vars.settings.speedCANTablePointer.co_DIV8[ii]=0;
//		co2_vars.settings.speedCANTablePointer.co_BRP[ii]=7;
//		co2_vars.settings.speedCANTablePointer.co_SJW[ii]=6;
//		co2_vars.settings.speedCANTablePointer.co_TSEG1[ii]=1;
//		co2_vars.settings.speedCANTablePointer.co_TSEG2[ii]=0;
//	}


	//������ �������:
	//	������ ������: 50
	//	��������� ����� � SPI: 3000
	FaultLog.init(&FaultLog, 50, 3000, (Uint32*)&RTCclock.packed_time);//���� ��������� �� ����� ����� ���� ������������� � ����������� �� ������ �����



#ifdef CANTORS_ENA
//������ � CANopen ����� UART (����������� � CAN, ��� ���������)
	CANtoRS.nodeID = (Uint16*)&co2_vars.co_nodeID; //����� ���� �� CANopen
    CANtoRS.callback = Z_co_receiveSDOrequest;//��������� �� ������� ��������� ������ �� �������� CANopen �� ������� SDO ���������
	CANtoRS.init(&CANtoRS);
#endif
#ifdef MODBUS_ENA
	// ����������� MODBUS
	ModBus.ExecutionFreq = 8000;//������� ������ ������� ������ ������ � ���


	ModBus.RSNodeID=0x11; //!< ����� ���� � ����
	ModBus.Init(&ModBus);
	MBVarsConv.init(&MBVarsConv);


#endif

	terminal.init();

	for(ii=0;ii<3;ii++) {
		can_mini.can_io[ii].i_word=0;
		can_mini.can_io[ii].o_word=0;
		can_mini.can_io[ii].a_inp=0;
	}

		co_CAN0Init(0);			//�������������� CAN



}

//!��������� ������.

//! ���������� �������������� �������������, ������� ������ ��������� �������.

//! \memberof TSM_Net
void SM_Net_Slow_Calc(TSM_Net *p) {

	co2_vars.co_scaleNum0 = 1; //��� ���������������
	co2_vars.co_scaleNum1 = 100;	// %
	co2_vars.co_scaleNum2 = (inv_params.freq_nom>>16);	//��
	co2_vars.co_scaleNum3 = (inv_params.U_nom>>16);//���������� ������ ����������� �����������
	co2_vars.co_scaleNum4 = (inv_params.I_nom>>16); //��� ������ �������
	co2_vars.co_scaleNum5 = 1;
	co2_vars.co_scaleNum6 = 1;
	co2_vars.co_scaleNum7 = (inv_params.Udc_nom>>16); //���������� ��� �������
	co2_vars.co_scaleNum8 = (inv_params.P_nom>>10); 	 //18 � ������� 9.6 //��������
	co2_vars.co_scaleNum9 = 1;
	co2_vars.co_scaleNumA = 20; //�����������
	co2_vars.co_scaleNumB = 1;
	co2_vars.co_scaleNumC = 1;
	co2_vars.co_scaleNumD = 1;
	co2_vars.co_scaleNumE = 1;
	co2_vars.co_scaleNumF = 1;
	co2_vars.co_scaleNum10 = 1; //
	co2_vars.co_scaleNum11 = 1; //
	co2_vars.co_scaleNum12 = (inv_params.Pdc_nom>>16); //250 � ������� 16.16 //��������
	co2_vars.co_scaleNum13 = 360; //
	co2_vars.co_scaleNum14 = 1;//inv_params.speed_nom; //����������� ������� ��������
	co2_vars.co_scaleNum15 = 1; //
	co2_vars.co_scaleNum16 = 1; //
	co2_vars.co_scaleNum17 = ((((long) inv_params.Udc_nom) << 6) / (long) inv_params.I_nom); //R��� 10.6
	co2_vars.co_scaleNum18 = 1000;
	co2_vars.co_scaleNum19 = 1;
	co2_vars.co_scaleNum1A = 1;
	co2_vars.co_scaleNum1B = 1;
	co2_vars.co_scaleNum1C = 1;
	co2_vars.co_scaleNum1D = 1;
	co2_vars.co_scaleNum1E = 1;
	co2_vars.co_scaleNum1F = 1;

	//inv_params.U_nom = 0.5759 * inv_params.Udc_nom;//����������� ������ ����������
	///inv_params.PowerS_nom = ((long) 300) << 6; //�������� � ������� 10.6
	//inv_params.freq_nom = 1;//((float) inv_params.speed_nom * inv_params.p) / 60 + 0.5; //����� �������

	co_background_calc(&co2_vars); //������ �������� CANOpen �������
	drv_interface.calc(&drv_interface);
	FaultLog.background_calc(&FaultLog);
#ifdef MODBUS_ENA
	MBVarsConv.slow_calc(&MBVarsConv);
#endif

	Can2BTInterface.slow_calc(&Can2BTInterface);//��������� ������� �������� CANopen, ��������� ������
	UserMem.slow_calc(&UserMem);//���������������� ������ � ��

	dlog.background_analizer(&dlog); //������� ���������� ������ �������������������

	terminal.slow_calc();

	can_mini.slow_update(&can_mini); //Andrei - ������ ��� ����� ��������, ����� ������� ���� ��������� �������� �
									 //������� - �� ���� ���������� ����������.
	Debug1 = can_mini.can_slave.i_long1;
	Debug2 = can_mini.can_slave.i_long2;


//	int res=1;//co_mini.check_sync_msg();
//	if (res==1)
//	{
//		//co_mini.send_msg(&co_mini.params);
//	}


	if (RTCclock.ClockOk)//���� ��������?
		FaultLog.time_ptr = (Uint32*)&RTCclock.packed_time;//����� ��� ����� ������ �� �����
	else
		FaultLog.time_ptr = (Uint32*) &global_time.PowerOn_time;//���� �� ��������, �� �� ������ �������� ������� ���������
}

//!������� ������

//!������� ������ ��������� ������� �������, ����� ������� "�������������" ����� ������ � ��������������
//! \memberof TSM_Net
void SM_Net_ms_Calc(TSM_Net *p) {
	//������� �������� ��������� ������� ���������� � ���������.
	//�� inv_status_code ������������ ������ ������� � UniCON
//	if (inv_status.bit.ready == 1)
//		inv_status_code = INV_STATUS_READY;
//	if (inv_status.bit.running == 1)
//		inv_status_code = INV_STATUS_RUNNING;
//	if (inv_status.bit.testing == 1)
//		inv_status_code = INV_STATUS_TESTING;
//	if (inv_status.bit.fault == 1)
//		inv_status_code = INV_STATUS_FAULT;
//	if (inv_status.bit.alarm == 1)
//		inv_status_code |= INV_STATUS_ALARM;
//	else
//		inv_status_code &= ~INV_STATUS_ALARM;

	//������� �������� ������ ��� ������ (UniCON)
	pult_protect_lister.calc(&pult_protect_lister);
	pult_alarm_lister.calc(&pult_alarm_lister);

	apl.protect_Code 	= 0xFF & pult_protect_lister.output;
	apl.alarm_Code 		= 0xFF & pult_alarm_lister.output;

	co_1ms_calc(&co2_vars);    //������ �������� CANOpen
#ifdef CANTORS_ENA
	CANtoRS.calc(&CANtoRS);
#endif
#ifdef MODBUS_ENA
	MBVarsConv.ms_calc(&MBVarsConv);
#endif

	terminal.ms_calc();
	can_mini.ms_update(&can_mini);

	//������� �������� �������� CANopen. ����� ��, � ���������, �������� ������������� dlog
		Can2BTInterface.ms_calc(&Can2BTInterface, NT_TIMER2->VALUE, &co2_vars);
		UserMem.ms_calc(&UserMem);//���������������� ������ � ��


}

void SM_Net_fast_Calc(TSM_Net *p) {

#ifdef MODBUS_ENA
	ModBus.Execute(&ModBus);
#endif
	terminal.fast_calc();

}

/*@}*/
