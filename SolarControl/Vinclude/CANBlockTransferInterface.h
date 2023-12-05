/* ==================================================================================
//File name:       CANBlockTransferInterface.h
//
//Originator:	Aliamkin Dmitriy I
//
//Description:   все взаимодействия с блочной передачей по CAN осуществляются
				 в ƒј данного файла
//ѕ–»ћ≈„јЌ»≈:    
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
#define CANBT_INTERFACE_DATALOG2  	3	// используетс€ дл€ 32-битного даталоггера

struct SCanBTInterface{
		Uint16 alreadyInit;	// признак первого вызова дискетного автомата
	    Uint16 state_shadow;// теневое состо€ние
	    Uint16 state_prev;	// предыдущее состо€ние (на один такт)
	    Uint16 E;			// флаг первого вхождени€
	    Uint32 time_prev;
	    Uint64 state_time;	// врем€ нахождени€ в текущем состо€нии, в тиках проца. ƒл€ 150ћгц максимальное врем€ около 4 тыс. лет :)
		Uint16 BlockTransferCommand;
		void (*calc)(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr);
		};

typedef volatile struct SCanBTInterface TCanBTInterface;

#define T_CANBT_INTERFACE_DEFAULTS {0,CANBT_INTERFACE_FREE,0xFF,1,\
									 0,0,0,\
							   		 SMCanBTInterface}

void SMCanBTInterface(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr);

//колбэки для 2700.00 
void co1_callback_BTcmd(unsigned int par);
void co2_callback_BTcmd(unsigned int par);
#ifdef __cplusplus
}
#endif

#endif
