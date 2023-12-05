/*!
 \file      CANOpen_drv.h
 \brief     ƒрайвер CANOpen

 \author	Aliamkin Dmitriy I
 \version   v 3.18 2019_03_06
 \defgroup  CANOpen_drv ƒрайвер CANOpen
 @{
*/

#ifndef CAN_OPEN_DRV_H
#define CAN_OPEN_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP.h"
#include "co_ODvars.h"
//#include "build.h"

//********************************************************************************************
#define CAN_UNSTUCK_ENA			//!< попытка уйти от зависания функций отправки, в случае если сообщение в процессе TRS = 1
//********************************************************************************************
//!¬ключатель CAN A
#define CAN_A_ENABLE
//!¬ключатель CAN B
//#define CAN_B_ENABLE

//********************************************************************************************
//#define USE_ZBEE_FUNCTIONS

//********************************************************************************************
//–азрешение драйверу загружать функции в ќ«” для ускорения работы драйвера.
//–азрешение позволяет сократить время обработки прерываний драйвера,
// но требует 720 слов ќ«” (секция secureRamFuncs). 
#define CAN_SECURE_RAM_USING_ENABLE

//********************************************************************************************
//!«агружать параметры из SPI памяти при инициализации
#define LOAD_PARAMS_FROM_SPI 1 //0

//********************************************************************************************
/*
“екущее устройство. ƒанная строка влияет на:
1.  онфигурацию соответсвующих CANу GPIO
2. –азрешение клока CAN модуля
3. Ќастройку скорости
*/
#define CAN_2810
//#define CAN_28335
//#define CAN_2808
//#define CAN_28035
//#define CAN_28069
//********************************************************************************************
/*
«апрещение и разрешение прерываний на время приема PDO 
(для обеспечения синхронизации данных), при этом
	для 28335, 280x по умолчанию запрещается EPWM6_INT (1мс прерывание).
	для 281x по умолчанию запрещается T4UFINT (1мс прерывание).

¬место EPWM6_INT, или T4UFINT пользователь может на время приема PDOзапрещать 
любое другое прерывание (или несколько прерываний). ƒля этого для соответствующего процессора нужно
переопределить макросы:
	CAN_PDOISR_PIEIER_DISABLE		- тут производится запрещение необходимого(-ых) прерывания(-й) в PIEIER 
	CAN_PDOISR_PIEIER_ENABLE		- тут производится разрешение прерывания(-й) в PIEIER, которое(-ые) было(-и) запрещено(-ы) в CAN_PDOISR_PIEIER_DISABLE 
	CAN_PDOISR_IFR_CLEAR			- тут очищается IFR для процессорной(-ых) группы(или нескольких групп) в которой(-ых) находится(-ятся) необходимое(-ые) прерывание(-я) 
	CAN_PDOISR_PIEACK_ACKNOWLEDGE	- тут ставится подтверждение PIEACK для процессорной(-ых) группы(или нескольких групп) в которой(-ых) находится(-ятся) необходимое(-ые) прерывание(-я)
*/
#ifdef 	CAN_2810

    #define CAN_1_ENABLE
    //по умолчанию T4UFINT (может быть изменено пользователем)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER5.all &= ~M_INT3
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER5.all |= M_INT3
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT5
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5
#endif

#ifdef 	CAN_28335
	//по умолчанию EPWM6_INT (может быть изменено пользователем)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif

#ifdef 	CAN_2808
	//по умолчанию EPWM6_INT (может быть изменено пользователем)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif

#ifdef 	CAN_28035
	//по умолчанию EPWM6_INT (может быть изменено пользователем)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif

#ifdef 	CAN_28069
	//по умолчанию EPWM6_INT (может быть изменено пользователем)
	#define CAN_PDOISR_PIEIER_DISABLE 		PieCtrlRegs.PIEIER3.all &= ~M_INT6
	#define CAN_PDOISR_PIEIER_ENABLE 		PieCtrlRegs.PIEIER3.all |= M_INT6
	#define CAN_PDOISR_IFR_CLEAR 			IFR &= ~M_INT3
	#define CAN_PDOISR_PIEACK_ACKNOWLEDGE 	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3
#endif
//********************************************************************************************
//разрешение принимать PDO от любых устройств в сети:
//для каждого RPDO доступны 8 диапазонов принимаемых идентификаторов:
//	0x181-0x1FF
//	0x200-0x27F
//	0x280-0x2FF
//		...
//	0x480-0x4FF
//	0x500-0x57F
// аждому RPDO должен быть сопоставлен свой диапазон идентификаторов. 
//ƒля сопоставления данному RPDO диапазона идентификаторов необходимо присвоить
//соответствующему RPDOxCOBID любой идентификатор требуемого диапазона.
//ƒвум RPDO одного устройства не может быть сопоставлен один и тот же диапазон идентификаторов - 
//в этом случае поведение непредсказуемо. 
//#define CAN_MULTI_PDO_ENABLE

//********************************************************************************************
//разрешение вызова CallBack при приеме PDO.
#define CAN_RX_PDO_CALLBACK_ENABLE

//********************************************************************************************
//разрешение CAN устройству оставаться в работе даже при наличии большого количества ошибок на линии CAN.
//— одной стороны разрешение позволяет работать устройству в сильно зашумленной линии, но с другой - 
//при отказе в устройстве, например rx, устройство забьет всю сеть, пытаясь отправить свою посылку...
#define CAN_AUTO_BUS_ON_ENABLE
//********************************************************************************************
//время (в относительных единицах) которое драйвер пытается попасть в режим инициализации
//≈сли по истечении указанного времени в инициализацию попасть не удалось, то соответсвующая
//функция  инициализации вернет управление во внешнюю программу.
//»спользуется в функциях:
//				Uint16 co1_Init(TCo_OdVars* ppc);
//				Uint16 co2_Init(TCo_OdVars* ppc);
//				Uint16 co_ReInit(TCo_OdVars* ppc);
//¬ случае если инициализация не удалась функции возвращают 0, иначе 1. 
#define CAN_MAX_DO_WHILE_TIMES_IN_INIT 500000 
//********************************************************************************************
//разрешение использования в драйвере функций блочной передачи (если данные возможности в проекте
//не используются, то данную опцию лучше отключить для уменьшения объема драйвера)
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

//!‘ункция восстановления значений параметров словаря объектов по умолчанию
/*!
–езультатом работы функции является восстановление параметров указанного\n
типа и диапазона\n
type - 1 rw-параметры\n
		 2 rwp-параметры\n
		 3 rwps-параметры\n
range - 1 восстановление индексов 1000h-1FFFh\n
		  2,3,4,5\n
‘ункция по времени выполнения относится к длиным (вызывать следует в фоне)\n */
extern void co_ODexpositor_instaurationDefault(TCo_OdVars* ppc, Uint16 type, Uint16 range);
extern Uint16 co_CANInit(TCo_OdVars* ppc);
//!‘ункция сохранения значений параметров словаря объектов в SPI память
/*!–езультатом работы функции является сохранение параметров указанного
типа и диапазона\n
type - 1 rw-параметры\n
		 2 rwp-параметры\n
		 3 rwps-параметры\n
range - 1 восстановление индексов 1000h-1FFFh\n
		  2,3,4,5\n
‘ункция по времени выполнения относится к длиным (вызывать следует в фоне).*/
extern void co_ODexpositor_paramConservation(TCo_OdVars* ppc, Uint16 type, Uint16 range);

//!‘ункция восстановления значений параметров словаря объектов из SPI памяти
/*! –езультатом работы функции является восстановление параметров указанного
типа и диапазона\n
type - 1 rw-параметры\n
		 2 rwp-параметры\n
		 3 rwps-параметры\n
range - 1 восстановление индексов 1000h-1FFFh\n
		  2,3,4,5\n
¬нимание!!!¬осстановление параметров 2-го и 3-го типов возможно если
переменная co_protectBit = 0. ≈сли co_protectBit = 1 , то функция ничего
не "делает".
≈сли восстановление параметров заданного типа и диапазона произошло
неудачно(контрольная сумма не сошлась), то восстановление заданного
типа и диапазона повторяется.≈сли после трех попыток восстановление
не завершилось успехом, то выполняется восстановление параметров заданного
типа и диапазона по умолчанию.
‘ункция по времени выполнения относится к длиным (вызывать следует в фоне).*/
extern void co_ODexpositor_paramInstauration(TCo_OdVars* ppc, Uint16 type, Uint16 range);

//!функция ѕќЋ№«ќ¬ј“≈Ћя для отправки SDO запросов на чтение параметров сервера
extern void co_SDOrequestRead(TCo_OdVars*);     
//!функция ѕќЋ№«ќ¬ј“≈Ћя для отправки SDO запросов на запись параметров сервера
extern void co_SDOrequestWrite(TCo_OdVars*);   
//!функция драйвера CANOpen вызываемая в прерывании таймера, тактирующего работу драйвера
extern void co_PWMPeriodISR(TCo_OdVars*);
//!функция обработчика драйвера CANOpen в фоновой программе
extern void co_Background(TCo_OdVars*);

#ifdef CAN_A_ENABLE
extern Uint16 co1_Init(TCo_OdVars* ppc);//¬ случае если инициализация не удалась функция возвращает 0, иначе 1. 
#endif
#ifdef CAN_B_ENABLE
extern Uint16 co2_Init(TCo_OdVars* ppc);//¬ случае если инициализация не удалась функция возвращают 0, иначе 1. 
#endif
//‘ункция переинициализации CAN без восстановления параметров из SPI (может быть использована лишь для ѕќ¬“ќ–Ќќ… иниц-ии) 
extern Uint16 co_ReInit(TCo_OdVars* ppc);//¬ случае если инициализация не удалась функция возвращают 0, иначе 1. 

extern void Z_co_receiveSDOrequest(TCo_OdVars*, TZCanMsg*);

extern Uint16 * co_getAddr(TCo_OdVars* ppc, Uint32 ind_subind);


// “ип доступа к параметру (согласно формату)
typedef enum EObjAccess
{
	OBJ_ACCESS_READONLY,	// read-only
	OBJ_ACCESS_RW,			// read/write
	OBJ_ACCESS_WP,			// read/writeable protected
	OBJ_ACCESS_SWP,			// read/secret writeable protected
} TObjAccess;

// “ип параметра (согласно формату)
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

// —труктура, содержаща€ различную информацию об объекте.
typedef struct
{
	void* varAddr;		// адрес переменной в ќ«”
	int varSize;		// размер переменной в битах (16/32)
	TObjAccess access;	// тип доступа к объекту
	TObjType type;		// тип объекта
	Uint16 subIndNum;	// число подындексов (дл€ ROOT)
	Uint16 scaleNum;	// номер масштабирующего коэффициента (дл€ QU16, QI16, QU32, QI32, FLOAT_PU)
	Uint16 Q;			// число разр€дов дробной части (дл€ QU16, QI16, QU32, QI32)
	Uint16 bitOffset;	// смещение битового пол€ (дл€ BIT_FIELD)
	Uint16 bitNum;		// размер битового пол€ (дл€ BIT_FIELD)
	Uint16 precision;	// число знаков, отображаемых после зап€той (дл€ FLOAT_ABS)
	Uint16 prefix;		// префикс размерности (дл€ FLOAT_ABS)
	Uint16 units;		// размерность (дл€ FLOAT_ABS)
} TObjectInfo;

// ‘ункци€ получени€ информации об объекте с заданным адресом.
// ¬озвращает 0, если объект не найден.
extern int co_getObjectInfo(
	TCo_OdVars* ppc,			// указатель на структуру используемого модул€ CANopen
	Uint32 ind_subind,			// биты 16-31 - индекс, биты 0-7 - подындекс объекта
	TObjectInfo* pObjectInfo	// указатель на структуру, куда будет помещена информаци€ об объекте
	);


//!¬спомогательная функция для приложений пользователя драйвера CANOpen.
/*!‘ункция возвращает формат объекта по переданным индексу
и подындексу. 
¬Ќ»ћјЌ»≈!!!≈сли запрошенного индекса и подиндекса не существует, то
функция возвращает 0 (это нужно обязательно отслеживать). */
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
//функции ѕќЋ№«ќ¬ј“≈Ћя, инициирующие передачу, или прием блока данных посредством 
//сервиса блочной передачи
extern void CANBlockTransferInitTX(TCo_OdVars* ppc, Uint16 size, Uint16* source_ptr);
extern void CANBlockTransferInitRX(TCo_OdVars* ppc, Uint16 size, Uint16* dest_ptr);
#endif
//*******************************************************************************************************************************************************************

//¬носить изменения в нижеописанные переменные и массивы «јѕ–≈ў≈Ќќ!!!

#define PWMFREQ 1 //!< частота Ў»ћ в к√ц (либо частота того таймера который используется для тактирования драйвера CANOpen)

#define BOOTUP 0			//!< изменять Ќ≈Ћ№«я!
#define STOPPED 4			//!< изменять Ќ≈Ћ№«я!
#define OPERATIONAL 5		//!< изменять Ќ≈Ћ№«я!
#define PREOPERATIONAL 127	//!< изменять Ќ≈Ћ№«я!

#define HIGH 1   			//!< изменять Ќ≈Ћ№«я! //необходимы для соответствующей работы функций интерпретатора
#define LOW 0	 			//!< изменять Ќ≈Ћ№«я! //команд, в зависимости от скорости выполнения команд

#define RECEIVE 0			//!< изменять Ќ≈Ћ№«я!
#define TRANSMIT 1			//!< изменять Ќ≈Ћ№«я!
//********************************************************************************************

// переменные необходимые для работы программы со статическим выделением
// памяти, т.е. переменные должны существовать и сохранять свои значения
// вне функций, изменяющих их значения

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

