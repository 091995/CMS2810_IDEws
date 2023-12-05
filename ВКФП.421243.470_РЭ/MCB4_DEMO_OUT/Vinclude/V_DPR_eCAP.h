/*!
     Copyright 2023 ќќќ "Ќѕ‘ ¬≈ “ќ–"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_DPR_eCAP.h
 \brief     // ћодуль расчЄта скорости и положения по трЄм датчикам на элементах ’олла.
 \author    ќќќ "Ќѕ‘ ¬ектор". http://motorcontrol.ru

 \addtogroup
 @{*/

#ifndef V_DPR_ECAP_H
#define V_DPR_ECAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "filter.h"

  /******************************************************************************
   —труктуры для работы с модулем расчЄта координат
  ******************************************************************************/
  struct SDPReCAPFLG1_BITS  							// bits
  {
Uint16 AngleMode:
    1;			// 0		–ежим расчета угла: 0 - 6 секторов, 1 - интерполяция
Uint16 SpeedMode:
    1;			// 1		–ежим расчета скорости: 0 - по каждому датчику, 1 - по каждой метке
Uint16 Dir:
    1;				// 2       	Ќаправление движения: 0 - по часовой, 1 -  против.
Uint16 PrevDir:
    1;			// 3       	Ќаправление движения: 0 - по часовой, 1 -  против.
Uint16 CAPnumber:
    2;			// 4-5 		Ќомер eCAP, по которому было предыдущее прерывание.
Uint16 ZeroFLG:
    1;			// 6		‘лаг обнуления скорости
Uint16 SpeedMinFLG:
    1;		// 7
Uint16 rsvd:
    8;				// 8-15		reserved;
  };

  union SDPReCAP_FLG1
  {
    Uint16              all;
    struct SDPReCAPFLG1_BITS  bit;
  };

  struct SDPReCAPCODE_BITS  							// bits
  {
Uint16 Code:
    3;				// 0-2		 од угла по датчикам ’олла
Uint16 prevCode:
    3;			// 3-5		ѕредыдущее значение кода
Uint16 rsvd:
    10;				// 6-15		reserved;
  };

  union SDPReCAP_CODE
  {
    Uint16              all;
    struct SDPReCAPCODE_BITS  bit;
  };


  
  struct S_ARR_COUNTERS  							// bits
  {
Uint16 Counter1:
    3;			
Uint16 Counter2:
    3;	
Uint16 Counter3:
    3;
  };


  struct SDPReCAP
  {
    Uint32 Ts;				// ѕериод для расчЄта интерполированного угла
    Uint32 Tspeed;			// ѕериод для расчЄт скорости
    Uint32 TsNom;			// ѕериод, соответсвующий номинальной скорости
    Uint32 TsNomMilsec;		// ѕериод, соответсвующий номинальной скорости при тактировании 1 мс
    Uint32 PrevTs;			// ѕредыдущая величина периода для расчЄта угла.
    Uint32 PrevTspeed;		// ѕредыдущая величина периода для расчЄта скорости
    Uint32 PrevTspeed1;		// ѕредыдущая величина периода для расчЄта скорости по датчику ј.
    Uint32 PrevTspeed11;
    Uint32 PrevTspeed2;		// ѕредыдущая величина периода для расчЄта скорости по датчику B.
    Uint32 PrevTspeed22;
    Uint32 PrevTspeed3;		// ѕредыдущая величина периода для расчЄта скорости по датчику C.
    Uint32 PrevTspeed33;
    Uint32 TimeRising1;		//
    Uint32 TimeRising2;		//
    Uint32 TimeRising3;		//
    Uint32 TimeFalling1;	//
    Uint32 TimeFalling2;	//
    Uint32 TimeFalling3;	//
    Uint32 Timer1;			// «ахваченное значение таймера по датчику ј
    Uint32 Timer2;			// «ахваченное значение таймера по датчику B
    Uint32 Timer3;			// «ахваченное значение таймера по датчику C
    _iq speed;				// –асчитанная скорость
    _iq speedMIN;			// ”ставка минимальной скорости
    _iq speedMinREF;		// —корость, соответствующая уставке для обнуления скорости
    _iq Angle;				// –аститанный интерполированный угол
    _iq Angle6;				// –асчитанный декодированный угол
    _iq AnglePrev;			// –асчитанный декодированный угол предыдущий
    Uint32 cnt;				// —чЄтчик числа прерываний с момента пуска (дальше 2 не считает).
    Uint32 cnt2;			// —чЄтчик прерываний смомента реверса.
    Uint32 milsec;			// ¬ремя в мс с момента прихода прошлой метки
    Uint32 milsecFIX;		// ѕереститанная уставка для обнуления скорости
    Uint32 milsecREF;		// ”ставка для обнуления скорости
    Uint32 milsecPrevREF;	// ѕредыдущее значение уставки для обнуления скорости
    Uint32 AngleFilterT;	//«начение постоянной времени фильтра угла в миллисекундах, 8.24
    Uint32 AngleFilter_1_T;	//«начение постоянной времени фильтра угла в том, что надо формуле фильтра
    union SDPReCAP_FLG1	DPReCAP_FLG1;
    union SDPReCAP_CODE	DPReCAP_CODE;
	int CAPCalcEna1;
	int CAPCalcEna2;
	int CAPCalcEna3;
	int CAP_WrongEdgeCnt;
	int CAP_WrongEdgeCnt1;
	int CAP_WrongEdgeCnt2;
	int CAP_WrongEdgeCnt3;
	int CAP_WrongEdgeCntPrev;
	int ErrorLevel;
	int ErrorLevelCounter;
	int ErrorLevelTimeCounterBig;
	int ErrorLevelTimeCounter;
	long AngleOffset;
	int Direction;
	int SensorFault;
	int NumOfBadChannel;
	Uint16 WrongCodeCounter;
	Uint16 WrongCodeCounterPerSec;
	Uint16 WrongCodeCounterLimitPerSec;
	Uint16 ErrorExternalSpeedEstimatorCounter;
	Uint16 ErrorExternalSpeedEstimatorCounterLimitPerSec;
	Uint16 ErrorOtherCounter;
	Uint16 ErrorOtherCounterLimitPerSec;
	Uint16 WrongPowerCounter;
	Uint16 Channel2Inversion;
    void (*Init)(volatile struct SDPReCAP*);
    void (*AngleCalc)(volatile struct SDPReCAP*);
    void (*Angle6Calc)(volatile struct SDPReCAP*);
    void (*AngleErrorCalc)(volatile struct SDPReCAP*);
    void (*SpeedCalc)(volatile struct SDPReCAP*);
    void (*CAP1Calc)(volatile struct SDPReCAP*);
    void (*CAP2Calc)(volatile struct SDPReCAP*);
    void (*CAP3Calc)(volatile struct SDPReCAP*);
    void (*HelpCalc)(volatile struct SDPReCAP*);
    void (*slow_calc)(volatile struct SDPReCAP*);
    void (*ms_calc)(volatile struct SDPReCAP*);
  };
  typedef volatile struct SDPReCAP TDPReCAP;

  /******************************************************************************
   »нициализация структуры  по умолчанию
  ******************************************************************************/
#define DPRECAP_DEFAULTS  \
  {\
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 5000, 500, 0,0,0, 0x0001, 0,\
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
    &DPReCAP_Init, \
    &DPReCAP_AngleCalc, \
    &DPReCAP_Angle6Calc, \
    &DPReCAP_AngleErrorCalc, \
    &DPReCAP_SpeedCalc, \
    &DPReCAP_CAP1Calc, \
    &DPReCAP_CAP2Calc, \
    &DPReCAP_CAP3Calc, \
    &DPReCAP_HelpCalc, \
    &DPReCAP_SlowCalc, \
    &DPReCAP_msCalc \
  }

  /******************************************************************************
  ѕроцедура инициализации.
  ******************************************************************************/
  void DPReCAP_Init(TDPReCAP*);

  /******************************************************************************
   ѕроцедура расчЄта угла.
  ******************************************************************************/
  void DPReCAP_Angle6Calc(TDPReCAP*);

  /******************************************************************************
   ѕроцедура вычислени€ факта ошибочного изменени€ угла.
  ******************************************************************************/
  void DPReCAP_AngleErrorCalc(TDPReCAP*);

  /******************************************************************************
   ѕроцедура расчЄта интерполированного угла.
  ******************************************************************************/
  void DPReCAP_AngleCalc(TDPReCAP*);

  /******************************************************************************
   ѕроцедура расчЄта скорости.
  ******************************************************************************/
  void DPReCAP_SpeedCalc(TDPReCAP*);

  /******************************************************************************
  –асчЄт прерывания 1
  ******************************************************************************/
  void DPReCAP_CAP1Calc(TDPReCAP*);

  /******************************************************************************
  –асчЄт прерывания 2
  ******************************************************************************/
  void DPReCAP_CAP2Calc(TDPReCAP*);

  /******************************************************************************
  –асчЄт прерывания 3
  ******************************************************************************/
  void DPReCAP_CAP3Calc(TDPReCAP*);

  /******************************************************************************
  ¬спомогательные расчЄт, общий для всех прерываний
  ******************************************************************************/
  void DPReCAP_HelpCalc(TDPReCAP*);


  /******************************************************************************
  ¬спомогательные расчЄт в фоне
  ******************************************************************************/
  void DPReCAP_SlowCalc(TDPReCAP*);

  /******************************************************************************
  ћиллисекундный расчет
  ******************************************************************************/
  void DPReCAP_msCalc(TDPReCAP*);

#ifdef __cplusplus
}
#endif	// extern "C"

#endif	// V_DPR_ECAP_H
