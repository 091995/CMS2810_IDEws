/*!
 \file      co_ODvars.h
 \brief     ОбъЯвлЯет некоторые служебные структуры длЯ драйвера CANOpen

 \author	Aliamkin Dmitriy I
 \version   v 1.19 04/05/2012
 @{
 */

#ifndef CO_OD_VARS_H
#define CO_OD_VARS_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "DSP.h"
//#include "CANOpen_drv.h"
//#include "V_eFIFO.h"
//****************************************************************************************************************************************
//! Начальный адрес длЯ сохранениЯ в SPI памЯти словарЯ 1-го CAN
#define CO1_SPI_START_ADDR 0
//! Начальный адрес длЯ сохранениЯ в SPI памЯти словарЯ 2-го CAN
#define CO2_SPI_START_ADDR 3500

//!здесь указываетсЯ количество "замеппированных" объектов длЯ каждого PDO
#define RPDO1NUMOFPARAMS 4
#define RPDO2NUMOFPARAMS 4
#define RPDO3NUMOFPARAMS 4
#define RPDO4NUMOFPARAMS 4
#define RPDO5NUMOFPARAMS 4
#define RPDO6NUMOFPARAMS 4
#define RPDO7NUMOFPARAMS 4
#define RPDO8NUMOFPARAMS 4

#define TPDO1NUMOFPARAMS 4
#define TPDO2NUMOFPARAMS 4
#define TPDO3NUMOFPARAMS 4
#define TPDO4NUMOFPARAMS 4
#define TPDO5NUMOFPARAMS 4
#define TPDO6NUMOFPARAMS 4
#define TPDO7NUMOFPARAMS 4
#define TPDO8NUMOFPARAMS 4
#define TPDO1MASK	0x01
#define TPDO2MASK	0x02
#define TPDO3MASK	0x04
#define TPDO4MASK	0x08
#define TPDO5MASK	0x10
#define TPDO6MASK	0x20
#define TPDO7MASK	0x40
#define TPDO8MASK	0x80
#define RPDO1MASK	0x01
#define RPDO2MASK	0x02
#define RPDO3MASK	0x04
#define RPDO4MASK	0x08
#define RPDO5MASK	0x10
#define RPDO6MASK	0x20
#define RPDO7MASK	0x40
#define RPDO8MASK	0x80
// !!!данные параметры должны быть выставлены в соответствии с количеством объектов
//"замэппированных" в словаре объектов

//!Конфигурирование полей SDO
struct SDOcommSpecifier
{
	Uint16 s :1; //!< 0 - если s=1, то размер передаваемых данных известен и указан
	Uint16 e :1; //!< 1 - expedited или нет
	Uint16 n :2; //!< 3:2 - количество байт данных не содержащих данных
	Uint16 X :1; //!< 4 - reserved
	Uint16 cs :3; //!< 7:5 - SDO команда
	Uint16 reserved :8; //
};

//! Нулевой байт мейл-бокса
union MBOXByte0
{
	struct SDOcommSpecifier SDO_Spicifier;
	Uint16 byte0;
};
//! Байты мейл-бокса, используемого длЯ альтернативной CAN свЯзи (ZigBee, USB)
typedef struct
{
	union MBOXByte0 MByte0;
	Uint16 byte1;
	Uint16 byte2;
	Uint16 byte3;
	Uint16 byte4;
	Uint16 byte5;
	Uint16 byte6;
	Uint16 byte7;
	Uint16 senderNodeID;
} Z_MBytes;

///сообщение в виде полей SDO
struct SDOmsg
{
	Uint32 s :1; //!< 0 - если s=1, то размер передаваемых данных известен и указан
	Uint32 e :1; //!< 1 - expedited или нет
	Uint32 n :2; //!< 3:2 - количество байт данных не содержащих данных
	Uint32 X :1; //!< 4 - reserved
	Uint32 cs :3; //!< 7:5 - SDO команда
	Uint32 index :16;
	Uint32 subindex :8;
	Uint32 data :32;
};
//сообщение в виде байтов
struct MBOX_bytes
{
	Uint16 byte0 :8;
	Uint16 byte1 :8;
	Uint16 byte2 :8;
	Uint16 byte3 :8;
	Uint16 byte4 :8;
	Uint16 byte5 :8;
	Uint16 byte6 :8;
	Uint16 byte7 :8;
};
//сообщение в виде слов
struct MBOX_words
{
	Uint16 word0;
	Uint16 word1;
	Uint16 word2;
	Uint16 word3;
};
//сообщение в виде MDRL, MDRH
struct MBOX_Uint32
{
	Uint32 MDRL;
	Uint32 MDRH;
};
//все представлениЯ накладываем друг на друга
union MBOX_data
{
	struct MBOX_Uint32 u32;
	struct MBOX_words u16;
	struct MBOX_bytes u8;
	struct SDOmsg SDO;
};
typedef volatile union MBOX_data TMBOX_data;

struct MID_bits
{
	Uint32 rsvd1 :18; 		//пока не используем
	Uint32 senderNodeID :7; 	//номер узла
	Uint32 rsvd2 :7; 		//пока не используем
};
union MID_data
{
	Uint32 all;
	struct MID_bits bit;
};
// мейл-бокс
struct MData
{
	union MBOX_data data;
	union MID_data MID;
};

//! Сборник данных всех мейл-боксов
struct CO_MBOXDATA
{
	struct MData MBOX_0;
	struct MData MBOX_1;
	struct MData MBOX_2;
	struct MData MBOX_3;
	struct MData MBOX_4;
	struct MData MBOX_5;
	struct MData MBOX_6;
	struct MData MBOX_7;
	struct MData MBOX_8;
	struct MData MBOX_9;
	struct MData MBOX_10;
	struct MData MBOX_11;
	struct MData MBOX_12;
	struct MData MBOX_13;
	struct MData MBOX_14;
	struct MData MBOX_15;
	struct MData MBOX_16;
	struct MData MBOX_17;
	struct MData MBOX_18;
	struct MData MBOX_19;
	struct MData MBOX_20;
	struct MData MBOX_21;
	struct MData MBOX_22;
	struct MData MBOX_23;
	struct MData MBOX_24;
	struct MData MBOX_25;
	struct MData MBOX_26;
	struct MData MBOX_27;
	struct MData MBOX_28;
	struct MData MBOX_29;
	struct MData MBOX_30;
	struct MData MBOX_31;
};

typedef volatile struct CO_MBOXDATA TCo_MboxData;

//****************************************************************************************************************************************
//структуры модулЯ блочной передачи
#define BT_FIFO_SIZE 8		//8 сообщений должно хватить длЯ 1Мбит/с, если обработка производитсЯ в 1мс
//внутримодульные дефайны
#define BT_FIFO_SUCCESSFUL 0
#define BT_FIFO_EMPTY 1
#define BT_FIFO_FULL 2
#define BT_FIFO_BUSY 3

struct S_BT_FIFO
{
	Uint16 busy_flag;			//флаг занЯтости ФИФО, показывает количество инстанций, использующих ФИФО в данный момент
	Uint16 size;
	Uint16 number_of_msgs;
	Uint16 read_ptr;
	Uint16 write_ptr;
	TMBOX_data msg_array[BT_FIFO_SIZE];
	Uint16 (*read)(volatile struct S_BT_FIFO*, TMBOX_data*);
	Uint16 (*write)(volatile struct S_BT_FIFO*, TMBOX_data*);
	Uint16 (*clear)(volatile struct S_BT_FIFO*);
};

typedef volatile struct S_BT_FIFO T_BT_FIFO;

#define T_BT_FIFO_DEFAULTS {0,\
    BT_FIFO_SIZE,\
    0,0,0,\
    {0},\
    BT_FIFO_Read,\
    BT_FIFO_Write,\
    BT_FIFO_Clear}

Uint16 BT_FIFO_Read(T_BT_FIFO*, TMBOX_data*);
Uint16 BT_FIFO_Write(T_BT_FIFO*, TMBOX_data*);
Uint16 BT_FIFO_Clear(T_BT_FIFO* p);

#define CANBT_STATE_FREE 0
#define CANBT_STATE_RX 1
#define CANBT_STATE_TX 2

#define CANBT_STATUS_IDLE		0
#define CANBT_STATUS_BUSY	    1
#define CANBT_STATUS_SUCCESSFUL 2
#define CANBT_STATUS_TIMEOUT 	3
#define CANBT_STATUS_CRC_ERR 	4
#define CANBT_STATUS_ANY_ERR 	5

struct SBlockTransfer
{
	Uint16 state;		//СостоЯние.
	Uint16 state_shadow;		//Теневое состоЯние.
	Uint16 state_prev;	//Предыдущее состоЯние (на один такт)
	Uint16 E;			//Флаг первого вхождениЯ.
	Uint32 state_time;	//времЯ нахождениЯ в текущем состоЯнии, в мс.
	Uint16 RX_block_size;	//размер принимаемого блока (определЯетсЯ пользователем перед приемом)
	Uint16 TX_block_size;   //размер отправлЯемого блока (определЯетсЯ пользователем перед отправкой)
	Uint16 firstTXmsg;		//флаг, показывающий, что 1-е сообщение блока еще не отправлЯлось.
	Uint16* RX_dest_ptr;
	Uint16* TX_source_ptr;
	int RX_index;
	int TX_index;
	T_BT_FIFO RXmsgFIFO;
	T_BT_FIFO TXmsgFIFO;
	Uint16 blockCRC;
	Uint16 rx_status;	//обратнаЯ свЯзь длЯ внешней программы использующей блочную передачу
	Uint16 tx_status;	//
	Uint32 timeout;
};

typedef volatile struct SBlockTransfer TBlockTransfer;

#define TBLOCK_TRANSFER_DEFAULTS {CANBT_STATE_FREE,\
								  CANBT_STATE_FREE,0xff,1,\
								  0,\
								  0,0,0,0,0,0,0,\
								  T_BT_FIFO_DEFAULTS,T_BT_FIFO_DEFAULTS,\
								  0,\
								  CANBT_STATUS_IDLE,CANBT_STATUS_IDLE,\
								  ((Uint32)500)/*500мс*/,\
                				  }

//! Стандартные переменные словарЯ CANOpen

//! Все перечисленные переменные должны быть добавлены в словаре CANOpen.
//!Так как CAN'а у контроллера два, то длЯ каждого словарЯ должны быть свои объекты,
//!чтобы иметь возможность настроить CANOpen по-разному. Поэтому делаетсЯ два экземплЯра этой структуры,
//!если это требуетсЯ.

struct SCo_OdVars
{
	Uint32 co_deviceType;		//1000.0
	Uint16 co_errorRegister;		//1001.0 Регистр ошибки
	Uint32 co_deviceState;		//1002.0
	Uint32 co_emcyCOBID;			//1014.0
	Uint32 co_CHBT;				//1016.1 Consumer heartbeat time
	Uint32 co_PHBT;				//1017.0 Producer heartbeat time
	Uint32 co_vendorID;			//1018.1
	Uint32 co_productCode;		//1018.2
	Uint32 co_revisionNumber;	//1018.3
	Uint32 co_serialNumber;		//1018.4
	Uint32 co_csrxCOBID;			//1200.1
	Uint32 co_sctxCOBID;			//1200.2
	Uint32 co_cstxCOBID;			//1280.1
	Uint32 co_scrxCOBID;			//1280.2
	Uint16 co_ssNODEID;			//1280.3
	Uint32 co_RPDO1COBID;		//1400.1
	Uint16 co_transType;			//1400.2 , 1401.2 , 1402.2 , 1403.2
	Uint32 co_RPDO2COBID;		//1401.1
	Uint32 co_RPDO3COBID;		//1402.1
	Uint32 co_RPDO4COBID;		//1403.1
//2007_03_14
	Uint32 co_RPDO5COBID;		//1404.1 rwp
	Uint32 co_RPDO6COBID;		//1405.1 rwp
	Uint32 co_RPDO7COBID;		//1406.1 rwp
	Uint32 co_RPDO8COBID;		//1407.1 rwp
//
	Uint32 co_RPDO1_1Mapping;	//1600.1
	Uint32 co_RPDO1_2Mapping;	//1600.2
	Uint32 co_RPDO1_3Mapping;	//1600.3
	Uint32 co_RPDO1_4Mapping;	//1600.4
	Uint32 co_RPDO2_1Mapping;	//1601.1
	Uint32 co_RPDO2_2Mapping;	//1601.2
	Uint32 co_RPDO2_3Mapping;	//1601.3
	Uint32 co_RPDO2_4Mapping;	//1601.4
	Uint32 co_RPDO3_1Mapping;	//1602.1
	Uint32 co_RPDO3_2Mapping;	//1602.2
	Uint32 co_RPDO3_3Mapping;	//1602.3
	Uint32 co_RPDO3_4Mapping;	//1602.4
	Uint32 co_RPDO4_1Mapping;	//1603.1
	Uint32 co_RPDO4_2Mapping;	//1603.2
	Uint32 co_RPDO4_3Mapping;	//1603.3
	Uint32 co_RPDO4_4Mapping;	//1603.4
//2007_03_14
	Uint32 co_RPDO5_1Mapping;	//1604.1 rwp
	Uint32 co_RPDO5_2Mapping;	//1604.2 rwp
	Uint32 co_RPDO5_3Mapping;	//1604.3 rwp
	Uint32 co_RPDO5_4Mapping;	//1604.4 rwp
	Uint32 co_RPDO6_1Mapping;	//1605.1 rwp
	Uint32 co_RPDO6_2Mapping;	//1605.2 rwp
	Uint32 co_RPDO6_3Mapping;	//1605.3 rwp
	Uint32 co_RPDO6_4Mapping;	//1605.4 rwp
	Uint32 co_RPDO7_1Mapping;	//1606.1 rwp
	Uint32 co_RPDO7_2Mapping;	//1606.2 rwp
	Uint32 co_RPDO7_3Mapping;	//1606.3 rwp
	Uint32 co_RPDO7_4Mapping;	//1606.4 rwp
	Uint32 co_RPDO8_1Mapping;	//1607.1 rwp
	Uint32 co_RPDO8_2Mapping;	//1607.2 rwp
	Uint32 co_RPDO8_3Mapping;	//1607.3 rwp
	Uint32 co_RPDO8_4Mapping;	//1607.4 rwp
//
	Uint32 co_TPDO1COBID;		//1800.1
	Uint16 co_TPDO1ITime;		//1800.3 rw
	Uint16 co_compatEntry;		//1800.4 rw
	Uint16 co_TPDO1EventTimer;	//1800.5 rw
	Uint32 co_TPDO2COBID;		//1801.1
	Uint16 co_TPDO2ITime;		//1801.3 rw
	Uint16 co_TPDO2EventTimer;	//1800.5 rw
	Uint32 co_TPDO3COBID;		//1802.1
	Uint16 co_TPDO3ITime;		//1802.3 rw
	Uint16 co_TPDO3EventTimer;	//1800.5 rw
	Uint32 co_TPDO4COBID;		//1803.1
	Uint16 co_TPDO4ITime;		//1803.3 rw
	Uint16 co_TPDO4EventTimer;	//1800.5 rw
//2007_03_14
	Uint32 co_TPDO5COBID;		//1804.1 r
	Uint16 co_TPDO5ITime;		//1804.3 rw
	Uint16 co_TPDO5EventTimer;	//1804.5 rw
	Uint32 co_TPDO6COBID;		//1805.1 r
	Uint16 co_TPDO6ITime;		//1805.3 rw
	Uint16 co_TPDO6EventTimer;	//1805.5 rw
	Uint32 co_TPDO7COBID;		//1806.1 r
	Uint16 co_TPDO7ITime;		//1806.3 rw
	Uint16 co_TPDO7EventTimer;	//1806.5 rw
	Uint32 co_TPDO8COBID;		//1807.1 r
	Uint16 co_TPDO8ITime;		//1807.3 rw
	Uint16 co_TPDO8EventTimer;	//1807.5 rw
//
	Uint32 co_TPDO1_1Mapping;	//1A00.1
	Uint32 co_TPDO1_2Mapping;	//1A00.2
	Uint32 co_TPDO1_3Mapping;	//1A00.3
	Uint32 co_TPDO1_4Mapping;	//1A00.4
	Uint32 co_TPDO2_1Mapping;	//1A01.1
	Uint32 co_TPDO2_2Mapping;	//1A01.2
	Uint32 co_TPDO2_3Mapping;	//1A01.3
	Uint32 co_TPDO2_4Mapping;	//1A01.4
	Uint32 co_TPDO3_1Mapping;	//1A02.1
	Uint32 co_TPDO3_2Mapping;	//1A02.2
	Uint32 co_TPDO3_3Mapping;	//1A02.3
	Uint32 co_TPDO3_4Mapping;	//1A02.4
	Uint32 co_TPDO4_1Mapping;	//1A03.1
	Uint32 co_TPDO4_2Mapping;	//1A03.2
	Uint32 co_TPDO4_3Mapping;	//1A03.3
	Uint32 co_TPDO4_4Mapping;	//1A03.4
//2007_03_14
	Uint32 co_TPDO5_1Mapping;	//1A04.1 rwp
	Uint32 co_TPDO5_2Mapping;	//1A04.2 rwp
	Uint32 co_TPDO5_3Mapping;	//1A04.3 rwp
	Uint32 co_TPDO5_4Mapping;	//1A04.4 rwp
	Uint32 co_TPDO6_1Mapping;	//1A05.1 rwp
	Uint32 co_TPDO6_2Mapping;	//1A05.2 rwp
	Uint32 co_TPDO6_3Mapping;	//1A05.3 rwp
	Uint32 co_TPDO6_4Mapping;	//1A05.4 rwp
	Uint32 co_TPDO7_1Mapping;	//1A06.1 rwp
	Uint32 co_TPDO7_2Mapping;	//1A06.2 rwp
	Uint32 co_TPDO7_3Mapping;	//1A06.3 rwp
	Uint32 co_TPDO7_4Mapping;	//1A06.4 rwp
	Uint32 co_TPDO8_1Mapping;	//1A07.1 rwp
	Uint32 co_TPDO8_2Mapping;	//1A07.2 rwp
	Uint32 co_TPDO8_3Mapping;	//1A07.3 rwp
	Uint32 co_TPDO8_4Mapping;	//1A07.4 rwp
//
	Uint16 co_nodeID;			//2000.0 номер данного узла
	Uint16 co_bitRate;			//2001.0
	Uint16 co_specialData1;		//2003.1
	Uint16 co_specialData2;		//2003.2
	Uint16 co_specialData3;		//2003.3
	Uint16 co_specialData4;		//2003.4
	Uint32 co_secretCode;		//2004.0
	Uint16 co_protectBit;		//2005.0 - ?
	Uint32 co_devicePresentFlag0;
	Uint32 co_devicePresentFlag1;
	Uint32 co_devicePresentFlag2;
	Uint32 co_devicePresentFlag3;
	Uint32 co_deviceGlobalPresent0;
	Uint32 co_deviceGlobalPresent1;
	Uint32 co_deviceGlobalPresent2;
	Uint32 co_deviceGlobalPresent3;
	Uint32 co_heartbeatFlag0;	//2010.1 Флаги heartbeat с 0 по 31-е устройство
	Uint32 co_heartbeatFlag1;	//2010.2 Флаги heartbeat с 32 по 63-е устройство
	Uint32 co_heartbeatFlag2;	//2010.3 Флаги heartbeat с 64 по 95-е устройство
	Uint32 co_heartbeatFlag3;	//2010.4 Флаги heartbeat с 96 по 127-е устройство
	Uint32 co_heartbeatMask0;	//2011.1 Маски heartbeat с 0 по 31-е устройство (0110b)
	Uint32 co_heartbeatMask1;	//2011.2 Маски heartbeat с 32 по 63-е устройство
	Uint32 co_heartbeatMask2;	//2011.3 Маски heartbeat с 64 по 95-е устройство
	Uint32 co_heartbeatMask3;	//2011.4 Маски heartbeat с 96 по 127-е устройство
	Uint16 co_heartbeatAutoStart;	//2012.0 Параметр, определЯющий возможен ли автозапуск сети
	Uint16 co_heartbeatAutoRecovery;	//2014.0 Параметр, определЯющий возможен ли перезапуск системы из состоЯниЯ STOPPED
	Uint16 co_nodeState;			//2015.0 состоЯние данного узла - вначале BOOTUP
	Uint16 co_emergencyErrorCode;	//2016.0 Код аварии
	Uint32 co_deviceErrorState;		//2017.0 Статусный регистр ошибок производителЯ
	Uint16 co_ODCommand;		 	//2080.1
	Uint16 co_currentODIndex;	//2080.2
	Uint16 co_currentODSubIndex; //2080.3
	Uint16 co_currentODEText; 	//2080.4
	Uint16 co_currentODEFormat;  //2080.5
	Uint16 co_currentODEMin; 	//2080.6
	Uint16 co_currentODEMax; 	//2080.7
	Uint16 co_currentODEDefault; //2080.8
	Uint16 co_currentODEMinLow;  //2080.9
	Uint16 co_currentODEMaxLow;  //2080.10
	Uint16 co_currentODEDefaultLow; 	 //2080.11
	Uint16 co_currentODEAddrHigh;	  	 //2080.12
	Uint16 co_currentODEAddrLow;
	Uint16 co_currentODEType;
	Uint16 co_odIndexSize;
	Uint32 co_defaultIndex1;	   //2082.1 rw
	Uint32 co_defaultIndex2;	   //2082.2 rw
	Uint16 co_maskElement01;	   //2083.1,2 rw
	Uint16 co_maskElement23;	   //2083.3,4 rw
	Uint16 co_maskElement45;	   //2083.5,6 rw
	Uint16 co_maskElement67;	   //2083.7,8 rw
	Uint16 co_maskElement89;	   //2083.9,A rw
	Uint16 co_maskElementAB;	   //2083.B,C rw
	Uint16 co_maskElementCD;	   //2083.D,E rw
	Uint16 co_maskElementEF;	   //2083.F,10 rw
	Uint16 co_profileAccessMask;   //2081.0 rw
	Uint16 co_scaleNum0;		 		 //2100.1
	Uint16 co_scaleNum0Format;	 	 //2100.2
	Uint16 co_scaleNum1;		    //2101.1
	Uint16 co_scaleNum1Format;	//2101.2
	Uint16 co_scaleNum2;		 	//2102.1
	Uint16 co_scaleNum2Format;	//2102.2
	Uint16 co_scaleNum3;		 	//2103.1
	Uint16 co_scaleNum3Format;	//2103.2
	Uint16 co_scaleNum4;		 	//2104.1
	Uint16 co_scaleNum4Format;	//2104.2
	Uint16 co_scaleNum5;		 	//2105.1
	Uint16 co_scaleNum5Format;	//2105.2
	Uint16 co_scaleNum6;		 	//2106.1
	Uint16 co_scaleNum6Format;	//2106.2
	Uint16 co_scaleNum7;		 	//2107.1
	Uint16 co_scaleNum7Format;	//2107.2
	Uint16 co_scaleNum8;		 	//2108.1
	Uint16 co_scaleNum8Format;	//2108.2
	Uint16 co_scaleNum9;		 	//2109.1
	Uint16 co_scaleNum9Format;	//2109.2
	Uint16 co_scaleNumA;		 	//210A.1
	Uint16 co_scaleNumAFormat;	//210A.2
	Uint16 co_scaleNumB;		 	//210B.1
	Uint16 co_scaleNumBFormat;	//210B.2
	Uint16 co_scaleNumC;		 	//210C.1
	Uint16 co_scaleNumCFormat;	//210C.2
	Uint16 co_scaleNumD;		 	//210D.1
	Uint16 co_scaleNumDFormat;	//210D.2
	Uint16 co_scaleNumE;			//210E.1
	Uint16 co_scaleNumEFormat;	//210E.2
	Uint16 co_scaleNumF;		 	//210F.1
	Uint16 co_scaleNumFFormat;	 //210F.2
	Uint16 co_scaleNum10;		 //2110.1
	Uint16 co_scaleNum10Format;	 //2110.2
	Uint16 co_scaleNum11;		 //2111.1
	Uint16 co_scaleNum11Format;	 //2111.2
	Uint16 co_scaleNum12;		 //2112.1
	Uint16 co_scaleNum12Format;	 //2112.2
	Uint16 co_scaleNum13;		 //2113.1
	Uint16 co_scaleNum13Format;	 //2113.2
	Uint16 co_scaleNum14;		 //2114.1
	Uint16 co_scaleNum14Format;	 //2114.2
	Uint16 co_scaleNum15;		 //2115.1
	Uint16 co_scaleNum15Format;	 //2115.2
	Uint16 co_scaleNum16;		 //2116.1
	Uint16 co_scaleNum16Format;	 //2116.2
	Uint16 co_scaleNum17;		 //2117.1
	Uint16 co_scaleNum17Format;	 //2117.2
	Uint16 co_scaleNum18;		 //2118.1
	Uint16 co_scaleNum18Format;	 //2118.2
	Uint16 co_scaleNum19;		 //2119.1
	Uint16 co_scaleNum19Format;	 //2119.2
	Uint16 co_scaleNum1A;		 //211A.1
	Uint16 co_scaleNum1AFormat;	 //211A.2
	Uint16 co_scaleNum1B;		 //211B.1
	Uint16 co_scaleNum1BFormat;	 //211B.2
	Uint16 co_scaleNum1C;		 //211C.1
	Uint16 co_scaleNum1CFormat;	 //211C.2
	Uint16 co_scaleNum1D;		 //211D.1
	Uint16 co_scaleNum1DFormat;	 //211D.2
	Uint16 co_scaleNum1E;		 //211E.1
	Uint16 co_scaleNum1EFormat;	 //211E.2
	Uint16 co_scaleNum1F;		 //211F.1
	Uint16 co_scaleNum1FFormat;	 //211F.2

	Uint16 co_blockTransferCommand;	 //2700

	//Указатели
	Uint16 *co_currentWordODTbl1;	 //данные указатели ипользуютсЯ длЯ работы интерпретатора
	Uint16 *co_currentWordODTbl2;	 //команд в прерывании ШИМ (длЯ обработки быстрых команд)
	Uint16 co_currentAccessMask;  //маска доступа индекса на который указывает co_currentWordODTbl1

	Uint16 *co_shadow_currentWordODTbl1;  //данные указатели ипользуютсЯ длЯ работы интерпретатора
	Uint16 *co_shadow_currentWordODTbl2;  //команд в фоновой программе (длЯ обработки медленных команд)

	Uint16 *co_SDOcurrentWordODTbl1;
	Uint16 *co_SDOcurrentWordODTbl2;

	//ZBee
	Uint16 *Z_co_SDOcurrentWordODTbl1;
	Uint16 *Z_co_SDOcurrentWordODTbl2;

	Uint16 *co_PDOcurrentWordODTbl1;
	Uint16 *co_PDOcurrentWordODTbl2;
	Uint16 *co_PDOMAPcurrentWordODTbl1;
	Uint16 *co_PDOMAPcurrentWordODTbl2;

	Uint16 *co_endODTbl1;  //указывает на последний элемент индекс в таблице ODTbl1
	TCo_MboxData co_MboxesData;
	Uint32 co_MailboxMDRL;
	Uint32 co_MailboxMDRH;
	Uint32 co_MailboxMID;

	Uint32 co_flagBackUp0;  //
	Uint32 co_flagBackUp1;  // предыдущие состоЯниЯ флагов
	Uint32 co_flagBackUp2;  //
	Uint32 co_flagBackUp3;  //

	Uint32 co_backupEEC;  	// Предыдущее состоЯние кода аварии
	Uint32 co_backupER;   	// Предыдущее состоЯние регистра ошибки
	Uint32 co_backupDES;  	// Предыдущее состоЯние статусного регистра ошибок производителЯ

	Uint32 co_consHBTimeCounter;  	// изначально должен быть равен co_CHBT
	Uint32 co_prodHBTimeCounter;  	// изначально должен быть равен co_PHBT
	Uint32 co_emcyNewState; // СостоЯние в которое перешел узел после ошибки
	Uint32 co_msDevisor;		// делитель частоты длЯ получениЯ 1мс - используетсЯ длЯ отправки Heartbeat

	Uint16 co_shadow_currentODIndex;
	Uint16 co_shadow_currentODSubIndex;
	Uint16 co_shadow_currentODEText;
	Uint16 co_shadow_currentODEFormat;
	Uint16 co_shadow_currentODEMin;
	Uint16 co_shadow_currentODEMax;
	Uint16 co_shadow_currentODEDefault;
	Uint16 co_shadow_currentODEMinLow;
	Uint16 co_shadow_currentODEMaxLow;
	Uint16 co_shadow_currentODEDefaultLow;
	Uint16 co_shadow_currentODEAddrLow;
	Uint16 co_shadow_currentODEAddrHigh;
	Uint16 co_shadow_currentODEType;
	//переменные необходимые длЯ  работы SDO служб
	Uint16 co_SDOrequestIndex;
	Uint16 co_SDOrequestSubIndex;
	Uint16 co_SDOrequestData;
	Uint16 co_SDOrequestDataH;
	Uint16 co_SDOrequestStatus;
	Uint16 co_SDOrequestFlag;
	Uint16 requestR;
	Uint16 requestW;
	Uint16 co_SDOSuspendedSend;

	//временнаЯ переменнаЯ защиты секретных параметров от несанкционированного доступа
	Uint16 co_secretProtectBit;

	//переменные необходимые длЯ работы PDO служб
	Uint16 co_PDOMappingFlags;		//RRRR RRRR TTTT TTTT - "T" - TPDO;- "R" - RPDO

	Uint16 co_PDO1Devisor;		// делитель длЯ получениЯ заданной скорости передачи PDO1
	Uint16 co_PDO2Devisor;
	Uint16 co_PDO3Devisor;
	Uint16 co_PDO4Devisor;
	Uint16 co_PDO5Devisor;
	Uint16 co_PDO6Devisor;
	Uint16 co_PDO7Devisor;
	Uint16 co_PDO8Devisor;
	//
	Uint16 co_NumOfNextPDO;
	Uint16 co_PDOTransmitFlags;		//0000 0000 TTTT TTTT
	Uint16 co_PDOTransmitEna;	//0000 0000 TTTT TTTT
	Uint16 co_PDOReceiveEna;	//0000 0000 RRRR RRRR

	Uint16 co_my_PDO1TransmitFlags;
	Uint16 co_my_PDO2TransmitFlags;
	Uint16 co_my_PDO3TransmitFlags;
	Uint16 co_my_PDO4TransmitFlags;
	Uint16 co_my_PDO5TransmitFlags;
	Uint16 co_my_PDO6TransmitFlags;
	Uint16 co_my_PDO7TransmitFlags;
	Uint16 co_my_PDO8TransmitFlags;

	Uint32 co_RPDO1_addr[RPDO1NUMOFPARAMS];
	Uint32 co_RPDO2_addr[RPDO2NUMOFPARAMS];
	Uint32 co_RPDO3_addr[RPDO3NUMOFPARAMS];
	Uint32 co_RPDO4_addr[RPDO4NUMOFPARAMS];
	//2007_03_14
	Uint32 co_RPDO5_addr[RPDO5NUMOFPARAMS];
	Uint32 co_RPDO6_addr[RPDO6NUMOFPARAMS];
	Uint32 co_RPDO7_addr[RPDO7NUMOFPARAMS];
	Uint32 co_RPDO8_addr[RPDO8NUMOFPARAMS];
	//

	Uint16 co_RPDO1_startBit[RPDO1NUMOFPARAMS];
	Uint16 co_RPDO2_startBit[RPDO2NUMOFPARAMS];
	Uint16 co_RPDO3_startBit[RPDO3NUMOFPARAMS];
	Uint16 co_RPDO4_startBit[RPDO4NUMOFPARAMS];
	//2007_03_14
	Uint16 co_RPDO5_startBit[RPDO5NUMOFPARAMS];
	Uint16 co_RPDO6_startBit[RPDO6NUMOFPARAMS];
	Uint16 co_RPDO7_startBit[RPDO7NUMOFPARAMS];
	Uint16 co_RPDO8_startBit[RPDO8NUMOFPARAMS];
	//

	Uint16 co_RPDO1_numOfBits[RPDO1NUMOFPARAMS];
	Uint16 co_RPDO2_numOfBits[RPDO2NUMOFPARAMS];
	Uint16 co_RPDO3_numOfBits[RPDO3NUMOFPARAMS];
	Uint16 co_RPDO4_numOfBits[RPDO4NUMOFPARAMS];
	//2007_03_14
	Uint16 co_RPDO5_numOfBits[RPDO5NUMOFPARAMS];
	Uint16 co_RPDO6_numOfBits[RPDO6NUMOFPARAMS];
	Uint16 co_RPDO7_numOfBits[RPDO7NUMOFPARAMS];
	Uint16 co_RPDO8_numOfBits[RPDO8NUMOFPARAMS];
	//

	Uint32 co_TPDO1_addr[TPDO1NUMOFPARAMS];
	Uint32 co_TPDO2_addr[TPDO2NUMOFPARAMS];
	Uint32 co_TPDO3_addr[TPDO3NUMOFPARAMS];
	Uint32 co_TPDO4_addr[TPDO4NUMOFPARAMS];
	//2007_03_14
	Uint32 co_TPDO5_addr[TPDO5NUMOFPARAMS];
	Uint32 co_TPDO6_addr[TPDO6NUMOFPARAMS];
	Uint32 co_TPDO7_addr[TPDO7NUMOFPARAMS];
	Uint32 co_TPDO8_addr[TPDO8NUMOFPARAMS];
	//

	Uint16 co_TPDO1_startBit[TPDO1NUMOFPARAMS];
	Uint16 co_TPDO2_startBit[TPDO2NUMOFPARAMS];
	Uint16 co_TPDO3_startBit[TPDO3NUMOFPARAMS];
	Uint16 co_TPDO4_startBit[TPDO4NUMOFPARAMS];
	//2007_03_14
	Uint16 co_TPDO5_startBit[TPDO5NUMOFPARAMS];
	Uint16 co_TPDO6_startBit[TPDO6NUMOFPARAMS];
	Uint16 co_TPDO7_startBit[TPDO7NUMOFPARAMS];
	Uint16 co_TPDO8_startBit[TPDO8NUMOFPARAMS];
	//

	Uint16 co_TPDO1_numOfBits[TPDO1NUMOFPARAMS];
	Uint16 co_TPDO2_numOfBits[TPDO2NUMOFPARAMS];
	Uint16 co_TPDO3_numOfBits[TPDO3NUMOFPARAMS];
	Uint16 co_TPDO4_numOfBits[TPDO4NUMOFPARAMS];
	//2007_03_14
	Uint16 co_TPDO5_numOfBits[TPDO5NUMOFPARAMS];
	Uint16 co_TPDO6_numOfBits[TPDO6NUMOFPARAMS];
	Uint16 co_TPDO7_numOfBits[TPDO7NUMOFPARAMS];
	Uint16 co_TPDO8_numOfBits[TPDO8NUMOFPARAMS];
	//
	Uint16 load_params_from_SPI;
	Uint16 ParamRestorationError;
	Uint16 co_requestCANInit;

	Uint32 ISRDroppingCounter;
	//данные из coodedit-а
	//Uint16 co_numOfInd;
	int16* OD_TBL1;
	Uint16* OD_TBL2;
	int32* OD_TBL3;
	Uint16* TYPE_DEF_TABLE;
	int32* OD_CALLBACK_TBL;

	Uint16 co_SPIrange1rw;
	Uint16 co_SPIrange1rwCRC;
	Uint16 co_SPIrange1rwp;
	Uint16 co_SPIrange1rwpCRC;
	Uint16 co_SPIrange1rwps;
	Uint16 co_SPIrange1rwpsCRC;
	Uint16 co_SPIrange2rw;
	Uint16 co_SPIrange2rwCRC;
	Uint16 co_SPIrange2rwp;
	Uint16 co_SPIrange2rwpCRC;
	Uint16 co_SPIrange2rwps;
	Uint16 co_SPIrange2rwpsCRC;
	Uint16 co_SPIrange3rw;
	Uint16 co_SPIrange3rwCRC;
	Uint16 co_SPIrange3rwp;
	Uint16 co_SPIrange3rwpCRC;
	Uint16 co_SPIrange3rwps;
	Uint16 co_SPIrange3rwpsCRC;
	Uint16 co_SPIrange4rw;
	Uint16 co_SPIrange4rwCRC;
	Uint16 co_SPIrange4rwp;
	Uint16 co_SPIrange4rwpCRC;
	Uint16 co_SPIrange4rwps;
	Uint16 co_SPIrange4rwpsCRC;
	Uint16 co_SPIrange5rw;
	Uint16 co_SPIrange5rwCRC;
	Uint16 co_SPIrange5rwp;
	Uint16 co_SPIrange5rwpCRC;
	Uint16 co_SPIrange5rwps;
	Uint16 co_SPIrange5rwpsCRC;
	Uint16 co_first1000;
	Uint16 co_first2000;
	Uint16 co_first3000;
	Uint16 co_first4000;
	Uint16 co_first5000;
	//указатели длЯ работы с регистрами и функциЯми, привЯзанными к аппаратной части
	volatile struct ECAN_REGS* ECanRegs;
	volatile struct ECAN_MBOXES* ECanMboxes;
	volatile struct LAM_REGS* ECanLAMRegs;
	void (*GpioInit)();
	void (*CANINTDisable)();
	void (*CANINTEnable)();
// #ifdef CAN_BLOCK_TRANSFER_ENABLE
	TBlockTransfer* BT;			//указатель делаем чтоб легко инициализировать структуру TBlockTransfer
// #endif

};

typedef volatile struct SCo_OdVars TCo_OdVars;

extern TCo_OdVars co1_vars;
extern TCo_OdVars co2_vars;
extern TBlockTransfer CANaBlockTransfer;
extern TBlockTransfer CANbBlockTransfer;

//***************************************************************************************************************************************************
#ifdef __cplusplus
}
#endif
#endif

/*@}*/

