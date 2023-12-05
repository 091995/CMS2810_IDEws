/*!
 \file      CANOpen_drv.h
 \brief     ������� CANOpen

 \author	Aliamkin Dmitriy I
 \version   v 3.18 2019_03_06
 \defgroup  CANOpen_drv ������� CANOpen
 @{
*/

#ifndef CAN_OPEN_DRV_H
#define CAN_OPEN_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP.h"
#include "build.h"

//********************************************************************************************
#define CAN_UNSTUCK_ENA			//!< ������� ���� �� ��������� ������� ��������, � ������ ���� ��������� � �������� TRS = 1
//********************************************************************************************
//!���������� CAN A
#define CAN_A_ENABLE
//!���������� CAN B
//#define CAN_B_ENABLE

//********************************************************************************************
//#define USE_ZBEE_FUNCTIONS

//********************************************************************************************
//���������� �������� ��������� ������� � ��� ��� ��������� ������ ��������.
//���������� ��������� ��������� ����� ��������� ���������� ��������,
// �� ������� 720 ���� ��� (������ secureRamFuncs). 
#define CAN_SECURE_RAM_USING_ENABLE

//********************************************************************************************
//!��������� ��������� �� SPI ������ ��� �������������
#define LOAD_PARAMS_FROM_SPI 1 //0

//********************************************************************************************
/*
������� ����������. ������ ������ ������ ��:
1. ������������ �������������� CAN� GPIO
2. ���������� ����� CAN ������
3. ��������� ��������
*/
#define CAN_2810
//#define CAN_28335
//#define CAN_2808
//#define CAN_28035
//#define CAN_28069
//********************************************************************************************
/*
���������� � ���������� ���������� �� ����� ������ PDO 
(��� ����������� ������������� ������), ��� ����
	��� 28335, 280x �� ��������� ����������� EPWM6_INT (1�� ����������).
	��� 281x �� ��������� ����������� T4UFINT (1�� ����������).

������ EPWM6_INT, ��� T4UFINT ������������ ����� �� ����� ������ PDO��������� 
����� ������ ���������� (��� ��������� ����������). ��� ����� ��� ���������������� ���������� �����
�������������� �������:
	CAN_PDOISR_PIEIER_DISABLE		- ��� ������������ ���������� ������������(-��) ����������(-�) � PIEIER 
	CAN_PDOISR_PIEIER_ENABLE		- ��� ������������ ���������� ����������(-�) � PIEIER, �������(-��) ����(-�) ���������(-�) � CAN_PDOISR_PIEIER_DISABLE 
	CAN_PDOISR_IFR_CLEAR			- ��� ��������� IFR ��� ������������(-��) ������(��� ���������� �����) � �������(-��) ���������(-����) �����������(-��) ����������(-�) 
	CAN_PDOISR_PIEACK_ACKNOWLEDGE	- ��� �������� ������������� PIEACK ��� ������������(-��) ������(��� ���������� �����) � �������(-��) ���������(-����) �����������(-��) ����������(-�)
*/
#ifdef 	CAN_2810

    #define CAN_1_ENABLE
    //�� ��������� T4UFINT (����� ���� �������� �������������)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER5.all &= ~M_INT3
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER5.all |= M_INT3
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT5
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5
#endif

#ifdef 	CAN_28335
	//�� ��������� EPWM6_INT (����� ���� �������� �������������)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif

#ifdef 	CAN_2808
	//�� ��������� EPWM6_INT (����� ���� �������� �������������)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif

#ifdef 	CAN_28035
	//�� ��������� EPWM6_INT (����� ���� �������� �������������)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif

#ifdef 	CAN_28069
	//�� ��������� EPWM6_INT (����� ���� �������� �������������)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif
//********************************************************************************************
//���������� ��������� PDO �� ����� ��������� � ����:
//��� ������� RPDO �������� 8 ���������� ����������� ���������������:
//	0x181-0x1FF
//	0x200-0x27F
//	0x280-0x2FF
//		...
//	0x480-0x4FF
//	0x500-0x57F
//������� RPDO ������ ���� ����������� ���� �������� ���������������. 
//��� ������������� ������� RPDO ��������� ��������������� ���������� ���������
//���������������� RPDOxCOBID ����� ������������� ���������� ���������.
//���� RPDO ������ ���������� �� ����� ���� ����������� ���� � ��� �� �������� ��������������� - 
//� ���� ������ ��������� ��������������. 
//#define CAN_MULTI_PDO_ENABLE

//********************************************************************************************
//���������� ������ CallBack ��� ������ PDO.
#define CAN_RX_PDO_CALLBACK_ENABLE

//********************************************************************************************
//���������� CAN ���������� ���������� � ������ ���� ��� ������� �������� ���������� ������ �� ����� CAN.
//� ����� ������� ���������� ��������� �������� ���������� � ������ ����������� �����, �� � ������ - 
//��� ������ � ����������, �������� rx, ���������� ������ ��� ����, ������� ��������� ���� �������...
#define CAN_AUTO_BUS_ON_ENABLE
//********************************************************************************************
//����� (� ������������� ��������) ������� ������� �������� ������� � ����� �������������
//���� �� ��������� ���������� ������� � ������������� ������� �� �������, �� ��������������
//�������  ������������� ������ ���������� �� ������� ���������.
//������������ � ��������:
//				Uint16 co1_Init(TCo_OdVars* ppc);
//				Uint16 co2_Init(TCo_OdVars* ppc);
//				Uint16 co_ReInit(TCo_OdVars* ppc);
//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1. 
#define CAN_MAX_DO_WHILE_TIMES_IN_INIT 500000 
//********************************************************************************************
//���������� ������������� � �������� ������� ������� �������� (���� ������ ����������� � �������
//�� ������������, �� ������ ����� ����� ��������� ��� ���������� ������ ��������)
#define CAN_BLOCK_TRANSFER_ENABLE
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
#ifdef USE_ZBEE_FUNCTIONS
#include "V_zigbee.h"
extern TZigBee    zigbee;
#endif

#ifdef CANTORS_ENA
    typedef struct {
        unsigned long id;
        unsigned char data[8];
        Uint16 dlc;
    } TZCanMsg;

#endif

//!������� �������������� �������� ���������� ������� �������� �� ���������
/*!
����������� ������ ������� �������� �������������� ���������� ����������\n
���� � ���������\n
type - 1 rw-���������\n
		 2 rwp-���������\n
		 3 rwps-���������\n
range - 1 �������������� �������� 1000h-1FFFh\n
		  2,3,4,5\n
������� �� ������� ���������� ��������� � ������ (�������� ������� � ����)\n */
extern void co_ODexpositor_instaurationDefault(TCo_OdVars* ppc, Uint16 type, Uint16 range);
extern Uint16 co_CANInit(TCo_OdVars* ppc);
//!������� ���������� �������� ���������� ������� �������� � SPI ������
/*!����������� ������ ������� �������� ���������� ���������� ����������
���� � ���������\n
type - 1 rw-���������\n
		 2 rwp-���������\n
		 3 rwps-���������\n
range - 1 �������������� �������� 1000h-1FFFh\n
		  2,3,4,5\n
������� �� ������� ���������� ��������� � ������ (�������� ������� � ����).*/
extern void co_ODexpositor_paramConservation(TCo_OdVars* ppc, Uint16 type, Uint16 range);

//!������� �������������� �������� ���������� ������� �������� �� SPI ������
/*! ����������� ������ ������� �������� �������������� ���������� ����������
���� � ���������\n
type - 1 rw-���������\n
		 2 rwp-���������\n
		 3 rwps-���������\n
range - 1 �������������� �������� 1000h-1FFFh\n
		  2,3,4,5\n
��������!!!�������������� ���������� 2-�� � 3-�� ����� �������� ����
���������� co_protectBit = 0. ���� co_protectBit = 1 , �� ������� ������
�� "������".
���� �������������� ���������� ��������� ���� � ��������� ���������
��������(����������� ����� �� �������), �� �������������� ���������
���� � ��������� �����������.���� ����� ���� ������� ��������������
�� ����������� �������, �� ����������� �������������� ���������� ���������
���� � ��������� �� ���������.
������� �� ������� ���������� ��������� � ������ (�������� ������� � ����).*/
extern void co_ODexpositor_paramInstauration(TCo_OdVars* ppc, Uint16 type, Uint16 range);

//!������� ������������ ��� �������� SDO �������� �� ������ ���������� �������
extern void co_SDOrequestRead(TCo_OdVars*);     
//!������� ������������ ��� �������� SDO �������� �� ������ ���������� �������
extern void co_SDOrequestWrite(TCo_OdVars*);   
//!������� �������� CANOpen ���������� � ���������� �������, ������������ ������ ��������
extern void co_PWMPeriodISR(TCo_OdVars*);
//!������� ����������� �������� CANOpen � ������� ���������
extern void co_Background(TCo_OdVars*);

#ifdef CAN_A_ENABLE
extern Uint16 co1_Init(TCo_OdVars* ppc);//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1. 
#endif
#ifdef CAN_B_ENABLE
extern Uint16 co2_Init(TCo_OdVars* ppc);//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1. 
#endif
//������� ����������������� CAN ��� �������������� ���������� �� SPI (����� ���� ������������ ���� ��� ��������� ����-��) 
extern Uint16 co_ReInit(TCo_OdVars* ppc);//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1. 

extern void Z_co_receiveSDOrequest(TCo_OdVars*, TZCanMsg*);

extern Uint16 * co_getAddr(TCo_OdVars* ppc, Uint32 ind_subind);


// ��� ������� � ��������� (�������� �������)
typedef enum EObjAccess
{
	OBJ_ACCESS_READONLY,	// read-only
	OBJ_ACCESS_RW,			// read/write
	OBJ_ACCESS_WP,			// read/writeable protected
	OBJ_ACCESS_SWP,			// read/secret writeable protected
} TObjAccess;

// ��� ��������� (�������� �������)
typedef enum EObjType
{
	OBJ_TYPE_UNKNOWN,
	OBJ_TYPE_ROOT,
	OBJ_TYPE_U8,
	OBJ_TYPE_U16,
	OBJ_TYPE_QU16,
	OBJ_TYPE_I8,
	OBJ_TYPE_I16,
	OBJ_TYPE_QI16,
	OBJ_TYPE_U32,
	OBJ_TYPE_QU32,
	OBJ_TYPE_I32,
	OBJ_TYPE_QI32,
	OBJ_TYPE_BIT_FIELD,
	OBJ_TYPE_FLOAT_ABS,
	OBJ_TYPE_FLOAT_PU,
} TObjType;

// ���������, ���������� ��������� ���������� �� �������.
typedef struct
{
	void* varAddr;		// ����� ���������� � ���
	int varSize;		// ������ ���������� � ����� (16/32)
	TObjAccess access;	// ��� ������� � �������
	TObjType type;		// ��� �������
	Uint16 subIndNum;	// ����� ����������� (��� ROOT)
	Uint16 scaleNum;	// ����� ��������������� ������������ (��� QU16, QI16, QU32, QI32, FLOAT_PU)
	Uint16 Q;			// ����� �������� ������� ����� (��� QU16, QI16, QU32, QI32)
	Uint16 bitOffset;	// �������� �������� ���� (��� BIT_FIELD)
	Uint16 bitNum;		// ������ �������� ���� (��� BIT_FIELD)
	Uint16 precision;	// ����� ������, ������������ ����� ������� (��� FLOAT_ABS)
	Uint16 prefix;		// ������� ����������� (��� FLOAT_ABS)
	Uint16 units;		// ����������� (��� FLOAT_ABS)
} TObjectInfo;

// ������� ��������� ���������� �� ������� � �������� �������.
// ���������� 0, ���� ������ �� ������.
extern int co_getObjectInfo(
	TCo_OdVars* ppc,			// ��������� �� ��������� ������������� ������ CANopen
	Uint32 ind_subind,			// ���� 16-31 - ������, ���� 0-7 - ��������� �������
	TObjectInfo* pObjectInfo	// ��������� �� ���������, ���� ����� �������� ���������� �� �������
	);


//!��������������� ������� ��� ���������� ������������ �������� CANOpen.
/*!������� ���������� ������ ������� �� ���������� �������
� ����������. 
��������!!!���� ������������ ������� � ���������� �� ����������, ��
������� ���������� 0 (��� ����� ����������� �����������). */
extern Uint16 co_getFormat(TCo_OdVars* ppc, Uint16 index,  Uint16 subindex);

#ifdef CAN_RX_PDO_CALLBACK_ENABLE
extern void co_RPDO1_Callback(Uint16 nodeID);
extern void co_RPDO2_Callback(Uint16 nodeID);
extern void co_RPDO3_Callback(Uint16 nodeID);
extern void co_RPDO4_Callback(Uint16 nodeID);
extern void co_RPDO5_Callback(Uint16 nodeID);
extern void co_RPDO6_Callback(Uint16 nodeID);
extern void co_RPDO7_Callback(Uint16 nodeID);
extern void co_RPDO8_Callback(Uint16 nodeID);
#endif

#ifdef CAN_BLOCK_TRANSFER_ENABLE
//������� ������������, ������������ ��������, ��� ����� ����� ������ ����������� 
//������� ������� ��������
extern void CANBlockTransferInitTX(TCo_OdVars* ppc, Uint16 size, Uint16* source_ptr);
extern void CANBlockTransferInitRX(TCo_OdVars* ppc, Uint16 size, Uint16* dest_ptr);
#endif
//*******************************************************************************************************************************************************************

//������� ��������� � ������������� ���������� � ������� ���������!!!

#define PWMFREQ 1 //!< ������� ��� � ��� (���� ������� ���� ������� ������� ������������ ��� ������������ �������� CANOpen)

#define BOOTUP 0			//!< �������� ������!
#define STOPPED 4			//!< �������� ������!
#define OPERATIONAL 5		//!< �������� ������!
#define PREOPERATIONAL 127	//!< �������� ������!

#define HIGH 1   			//!< �������� ������! //���������� ��� ��������������� ������ ������� ��������������
#define LOW 0	 			//!< �������� ������! //������, � ����������� �� �������� ���������� ������

#define RECEIVE 0			//!< �������� ������!
#define TRANSMIT 1			//!< �������� ������!
//********************************************************************************************

// ���������� ����������� ��� ������ ��������� �� ����������� ����������
// ������, �.�. ���������� ������ ������������ � ��������� ���� ��������
// ��� �������, ���������� �� ��������

extern Uint16 co_BRP[6];
extern Uint16 co_TSEG1[6];
extern Uint16 co_TSEG2[6];
extern Uint16 co_SJW[6];
extern Uint16 co_SAM[6];
#ifdef __cplusplus
}
#endif


#endif


/*@}*/

