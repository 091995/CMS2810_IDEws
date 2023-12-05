
#ifndef SM_Protect_H
#define SM_Protect_H

//#ifndef MODEL
#include "build.h"
//#endif


//! Модуль ащит выключен
#define SM_DCS_PROT_INIT 				0
//! Модуль защит включен
#define SM_DCS_PROT_NO_TRIP	 			1
//! Модуль защит в состоянии аварии (сработала защита)
#define SM_DCS_PROT_TRIP 			2


//Флаги аварий для модуля защит

//bit_fault1
#define F_UDC_MAX	          	0x1
#define F_UDC_MIN       	 	0x2
#define F_U_TR_MAX		        0x4
#define F_U_TR_MIN 	        	0x8
#define F_MAX_I_TR_A			0x10
#define F_MAX_I_TR_B			0x20
#define F_MAX_I_TR_C		    0x40
#define F_GRID_SHORT_CIRCUIT   	0x80
#define F_MAX_I_INV_A			0x100
#define F_MAX_I_INV_B			0x200
#define F_MAX_I_INV_C		    0x400

#define P_TEMPERATURE_MAX 	    0x800			//added
#define F_PDP_INV1		       	0x1000
#define F_PDP_IMAX		       	0x2000
#define F_PDP_EXT_LOST 	        0x4000
#define F_PROGRAM_10K		    0x8000

//#define F_PROGRAM_1K	          	0x1000
//#define F_PROGRAM_10K        		0x2000
//#define F_PROGRAM_40K	        	0x4000
//#define F_FLASH_PROGRAM         	0x8000

//bit_fault2
//#define F_RESERVED				0x1
//#define F_RESERVED				0x2
//#define F_RESERVED				0x4
//#define F_RESERVED				0x8
//#define F_RESERVED				0x80
//#define F_RESERVED				0x100
//#define F_CTRL_SPEED_MAX			0x200
//#define F_RESERVED				0x400
//#define F_RESERVED				0x800
//#define F_RESERVED				0x1000
//#define F_RESERVED				0x2000
//#define F_RESERVED				0x4000
//#define F_RESERVED				0x8000



struct SDCS_Protect
{
	int state;//!< Состояние
	int state_prev;//!< Состояние предыдущее
    int E;//!<Флаг первого вхождения
    int counter;


    Uint16 bit_fault1;//!<Слово аварий 1
    Uint16 masked_bit_fault1;//!<Слово аварий после маскирования
    Uint16 mask_fault_pwm1;//!<Маска аварий 1 со снятием импульсов
    Uint16 mask_fault_off;//!<Маска аварий 1 с полным отключением инвертора
    Uint16 masked_fault_off;//!<Маска аварий 1 с полным отключением инвертора
    Uint16 bit_alarm1;
    
	unsigned short bit_fault_written1;

    long Imax; //!<Уставка максимально-токовой защиты
    long Udc_max; //!<Уставка защиты max напряжения на ЗПТ
    long Udc_min;//!<Уставка защиты min напряжения на ЗПТ
    long U1_max;//!<Уставка максимального сетевог напряжения
    long U1_min;//!<Уставка максимального сетевог напряжения
    long Idc_max;
    int T_max; //max temperature


    //Uint16 protect_bit[8]; //8 битовых сигнала для заполенния на экране Unicon и отображения красным/зеленым
    //Uint16 alarm_bit[8]; //8 битовых сигнала для заполенния на экране Unicon и отображения желтым/зеленым

    void (*init)(struct SDCS_Protect*);     /* Pointer to the init funcion           */
    void (*slow_calc)(struct SDCS_Protect*);     /* Pointer to the calc funtion           */
    void (*fast_calc)(struct SDCS_Protect*);     /* Pointer to the calc funtion           */
    void (*ms_calc)(struct SDCS_Protect*);     /* Pointer to the calc funtion           */
  } ;
  typedef struct SDCS_Protect TDCS_Protect;

 //!Инициализатор по умолчанию
#define DCS_PROTECT_DEFAULTS {0,0,0,0,\
							0,0,0,0,0,0,\
							0,\
							0,0,0,0,0,0,\
							0,\
							DCS_Protect_Init,\
							DCS_Protect_Slow_Calc,\
							DCS_Protect_Fast_Calc,\
							DCS_Protect_ms_Calc,\
  }

//! \memberof TSM_Protect
  void DCS_Protect_Init(TDCS_Protect*);
//! \memberof TSM_Protect
  void DCS_Protect_Slow_Calc(TDCS_Protect*);
//! \memberof TSM_Protect
  void DCS_Protect_Fast_Calc(TDCS_Protect*);
//! \memberof TSM_Protect
  void DCS_Protect_ms_Calc(TDCS_Protect*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/






