/*!
    Copyright 2019 A&D

 \file      v_common.h
 \brief     Объявление структур данных различного назначения, которые еще слишком малы для того, чтобы
  организовывать их в отдельный модуль
 \author    A&D
 \version   v 1.0 24/05/2019

 \defgroup  v_common Объявление структур данных различного назначения

@{*/

#ifndef V_COMMON_H
#define V_COMMON_H


//!Битовое поле для битового статуса системы управления
  typedef struct
  {
	unsigned int ready:
    1;
    unsigned int running:
    1;
    unsigned int fault:
    1;
    unsigned int alarm:
    1;
    unsigned int testing:
    1;
    unsigned int overheat:
    1;
  } INV_STATUS_BIT;

//!Структура для статуса системы управления
  typedef union
  {
    int all;
    INV_STATUS_BIT bit;
  }TInvStatus;


//!Битовое поле слова управления
  typedef struct
  {
unsigned int start:
    1;
unsigned int stop:
    1;
unsigned int trip_reset:
    1;
unsigned int reserved:
    5;
  } CMD_BIT;

//!Структура слова управления (содержит DRV_STATUS_BIT)
  typedef union
  {
    unsigned int all;
    CMD_BIT bit;
  }TCmd;

  
  //! Структура, содержащия основные задания
    typedef volatile struct
    {
    	long Id_ref;
    	long Iq_ref;
    	long P_ref;// Задание активной мощности
    	long Q_ref;// Задание активной мощности
    	long Um1_ref;// Задание напряжения сети
    } TRefs;

//! Структура для хранения параметров базовых величин системы управления
  typedef struct
  {

    int I_nom;//!< Номинальный (базовый) фазный ток в формате 16.0
    long _1_I_nom;//!< 1/I_nom
    int U_nom;//!< Номинальное (базовое) фазное напряжение в формате 16.0
    long _1_U_nom;//!< 1/U_nom 
    int Udc_nom;//!< Номинальное (базовое) напряжение ЗПТ в формате 16.0
    long _1_Udc_nom;//!< 1/Udc_nom

    int U_nom_div_Udc_nom;// used by pwm module to find output comparators

	int freq_nom;//!< Номинальная (базовая) частота в формате 16.0
    int P_nom;//!< Номинальная (базовая) мощность в формате 16.0, может быть в киловатах
    int Pdc_nom;//!< Номинальная (базовая) мощность в формате 16.0, может быть в киловатах
    int _1_P_nom;

    long Ls;
    long Rs;
  } TInvParams;

  
//! Структура для битовых "переключателей"
typedef struct {
		unsigned short  Reboot;			//!< Программная перезагрузка
		unsigned short 	AutoOffset;		//!< автосмещение АЦП
		unsigned short 	HardwareType;	//!< Тип железа, под который собран проект
		} TSysSwitches;


#endif


