
#ifndef _DIO_Protect_H_
#define _DIO_Protect_H_

#ifdef __cplusplus
extern "C"
{
#endif

//#include "build.h"

//! Модуль ащит выключен
#define SM_DIO_PROTECT_OFF 			0
//! Модуль защит включен
#define SM_DIO_PROTECT_ON	 		1
//! Модуль защит в состоянии аварии (сработала защита)
#define SM_DIO_PROTECT_TRIP 		2

#define P_K7_BK_FAIL				    0x0001
#define P_Q26_BK_FAIL		       		0x0002
#define P_Q4_BK_FAIL					0x0004
#define P_K91_BK_FAIL		       		0x0008
#define P_K7_SW_FAIL				    0x0010
#define P_Q26_SW_FAIL		       		0x0020
#define P_Q4_SW_FAIL					0x0040
#define P_K91_SW_FAIL		       		0x0080
#define P_OVER_FREQUENCY_GRID			0x0100
#define P_DIFF_TEMP 					0x0200
#define P_UNDER_FREQUENCY_GRID			0x0800

#define P_DAY_MODE_ALGO_FAIL			0x1000
#define P_Q6_BK_FAIL		       		0x2000
#define P_Q6_SW_FAIL		       		0x4000
#define P_BMS_PROTECTION		       	0x8000


#define A_ISOLATION_LEVEL1			0x0001
#define A_ISOLATION_LEVEL2			0x0002
#define A_OPN_DC					0x0004
#define A_OPN_AC					0x0008
#define A_K60_FAIL					0x0010
#define A_F60_FAIL					0x0020
#define A_F61_FAIL					0x0040
#define A_DOOR_OPEN					0x0080
#define A_CAN_IO_1_NO_LINK			0x0100
#define A_CAN_IO_2_NO_LINK			0x0200
#define A_CAN_IO_3_NO_LINK			0x0400
#define A_Q26_OFF					0x0800
#define A_TEMPERATURE_HI			0x1000
#define A_TEMPERATURE_LO			0x2000
#define A_INV_MAX_ATTEMPTS			0x4000
#define A_FAN_FAIL					0x8000

//TODO 2 not enought space in word so i use temporaly A_CAN_IO_2_NO_LINK to signal about DCDC ext protection
#define A_DCDC_EXT_PROTECTION		0x0200
//TODO 2 same as above
#define A_DCDC_DIESEL_NO_POWER		0x0400




 struct SDIO_PROTECT
  {
    Uint16 state;
    Uint16 state_prev;
    Uint16 E;
    Uint32 counter;

    Uint16 bit_fault1;//!<Слово аварий 1
    Uint16 masked_bit_fault1;//!<Слово аварий после маскирования
    Uint16 masked_fault_off;//!<Слово аварий после маскирования

    Uint16 mask_fault_pwm1;//!<Маска аварий 1 со снятием импульсов
    Uint16 mask_fault_off;//!<Маска аварий 1 с полным отключением инвертора

    
    Uint16 bit_fault_written1;

    int powered_okCounter;
    int trip_reset;

    //Uint16 protect_bit[8]; //8 битовых сигнала для заполенния на экране Unicon и отображения красным/зеленым
    Uint16 bit_alarm1; // битовых сигнала для заполенния на экране Unicon и отображения желтым/зеленым

    void (*init)(struct SDIO_PROTECT*);
    void (*slow_calc)(struct SDIO_PROTECT*);
    void (*ms_calc)(struct SDIO_PROTECT*);
  } ;
  typedef struct SDIO_PROTECT TDIO_PROTECT;

 //!Инициализатор по умолчанию
#define DIO_PROTECT_DEFAULTS {0,0,0,0,\
							0,0,0,0,0,\
							0,0,0,\
							0,\
							DIO_Protect_Init,\
							DIO_Protect_Slow_Calc,\
							DIO_Protect_ms_Calc,\
  	  	  	  	  	  	  	 }

  void DIO_Protect_Init(TDIO_PROTECT*);
  void DIO_Protect_Slow_Calc(TDIO_PROTECT*);
  void DIO_Protect_ms_Calc(TDIO_PROTECT*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/






