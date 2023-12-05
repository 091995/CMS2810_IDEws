/* ==================================================================================
//File name:       CANBlockTransferInterface.h
//
//Originator:	Aliamkin Dmitriy I
//
//Description:   ��� �������������� � ������� ��������� �� CAN ��������������
				 � �� ������� �����
//����������:    
//=====================================================================================
//-------------------------------------------------------------------------------------
// 16.09.2019	Release	Rev 1.05
//----------------------------------------------------------------------------------*/
#ifndef CANBLOCKTRANS_INTERFACE_H
#define CANBLOCKTRANS_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "DSP.h"

#define CANBT_INTERFACE_FREE 		0
#define CANBT_INTERFACE_BUSY 		0x8000
#define CANBT_INTERFACE_FLASH_PROG  1
#define CANBT_INTERFACE_DATALOG1  	2
#define CANBT_INTERFACE_DATALOG2  	3	// ������������ ��� 32-������� �����������

struct SCanBTInterface{
		Uint16 alreadyInit;	// ������� ������� ������ ���������� ��������
	    Uint16 state_shadow;// ������� ���������
	    Uint16 state_prev;	// ���������� ��������� (�� ���� ����)
	    Uint16 E;			// ���� ������� ���������
	    Uint32 time_prev;
	    Uint64 state_time;	// ����� ���������� � ������� ���������, � ����� �����. ��� 150��� ������������ ����� ����� 4 ���. ��� :)
		Uint16 BlockTransferCommand;
		void (*calc)(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr);
		};

typedef volatile struct SCanBTInterface TCanBTInterface;

#define T_CANBT_INTERFACE_DEFAULTS {0,CANBT_INTERFACE_FREE,0xFF,1,\
									 0,0,0,\
							   		 SMCanBTInterface}

void SMCanBTInterface(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr);

//������� ��� 2700.00 
void co1_callback_BTcmd(unsigned int par);
void co2_callback_BTcmd(unsigned int par);
#ifdef __cplusplus
}
#endif

#endif
