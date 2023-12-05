/*!
     Copyright 2023 ��� "��� ������"

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
 \brief     // ������ ������� �������� � ��������� �� ��� �������� �� ��������� �����.
 \author    ��� "��� ������". http://motorcontrol.ru

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
   ��������� ��� ������ � ������� ������� ���������
  ******************************************************************************/
  struct SDPReCAPFLG1_BITS  							// bits
  {
Uint16 AngleMode:
    1;			// 0		����� ������� ����: 0 - 6 ��������, 1 - ������������
Uint16 SpeedMode:
    1;			// 1		����� ������� ��������: 0 - �� ������� �������, 1 - �� ������ �����
Uint16 Dir:
    1;				// 2       	����������� ��������: 0 - �� �������, 1 -  ������.
Uint16 PrevDir:
    1;			// 3       	����������� ��������: 0 - �� �������, 1 -  ������.
Uint16 CAPnumber:
    2;			// 4-5 		����� eCAP, �� �������� ���� ���������� ����������.
Uint16 ZeroFLG:
    1;			// 6		���� ��������� ��������
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
    3;				// 0-2		��� ���� �� �������� �����
Uint16 prevCode:
    3;			// 3-5		���������� �������� ����
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
    Uint32 Ts;				// ������ ��� ������� ������������������ ����
    Uint32 Tspeed;			// ������ ��� ������ ��������
    Uint32 TsNom;			// ������, �������������� ����������� ��������
    Uint32 TsNomMilsec;		// ������, �������������� ����������� �������� ��� ������������ 1 ��
    Uint32 PrevTs;			// ���������� �������� ������� ��� ������� ����.
    Uint32 PrevTspeed;		// ���������� �������� ������� ��� ������� ��������
    Uint32 PrevTspeed1;		// ���������� �������� ������� ��� ������� �������� �� ������� �.
    Uint32 PrevTspeed11;
    Uint32 PrevTspeed2;		// ���������� �������� ������� ��� ������� �������� �� ������� B.
    Uint32 PrevTspeed22;
    Uint32 PrevTspeed3;		// ���������� �������� ������� ��� ������� �������� �� ������� C.
    Uint32 PrevTspeed33;
    Uint32 TimeRising1;		//
    Uint32 TimeRising2;		//
    Uint32 TimeRising3;		//
    Uint32 TimeFalling1;	//
    Uint32 TimeFalling2;	//
    Uint32 TimeFalling3;	//
    Uint32 Timer1;			// ����������� �������� ������� �� ������� �
    Uint32 Timer2;			// ����������� �������� ������� �� ������� B
    Uint32 Timer3;			// ����������� �������� ������� �� ������� C
    _iq speed;				// ����������� ��������
    _iq speedMIN;			// ������� ����������� ��������
    _iq speedMinREF;		// ��������, ��������������� ������� ��� ��������� ��������
    _iq Angle;				// ����������� ����������������� ����
    _iq Angle6;				// ����������� �������������� ����
    _iq AnglePrev;			// ����������� �������������� ���� ����������
    Uint32 cnt;				// ������� ����� ���������� � ������� ����� (������ 2 �� �������).
    Uint32 cnt2;			// ������� ���������� �������� �������.
    Uint32 milsec;			// ����� � �� � ������� ������� ������� �����
    Uint32 milsecFIX;		// ������������� ������� ��� ��������� ��������
    Uint32 milsecREF;		// ������� ��� ��������� ��������
    Uint32 milsecPrevREF;	// ���������� �������� ������� ��� ��������� ��������
    Uint32 AngleFilterT;	//�������� ���������� ������� ������� ���� � �������������, 8.24
    Uint32 AngleFilter_1_T;	//�������� ���������� ������� ������� ���� � ���, ��� ���� ������� �������
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
   ������������� ���������  �� ���������
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
  ��������� �������������.
  ******************************************************************************/
  void DPReCAP_Init(TDPReCAP*);

  /******************************************************************************
   ��������� ������� ����.
  ******************************************************************************/
  void DPReCAP_Angle6Calc(TDPReCAP*);

  /******************************************************************************
   ��������� ���������� ����� ���������� ��������� ����.
  ******************************************************************************/
  void DPReCAP_AngleErrorCalc(TDPReCAP*);

  /******************************************************************************
   ��������� ������� ������������������ ����.
  ******************************************************************************/
  void DPReCAP_AngleCalc(TDPReCAP*);

  /******************************************************************************
   ��������� ������� ��������.
  ******************************************************************************/
  void DPReCAP_SpeedCalc(TDPReCAP*);

  /******************************************************************************
  ������ ���������� 1
  ******************************************************************************/
  void DPReCAP_CAP1Calc(TDPReCAP*);

  /******************************************************************************
  ������ ���������� 2
  ******************************************************************************/
  void DPReCAP_CAP2Calc(TDPReCAP*);

  /******************************************************************************
  ������ ���������� 3
  ******************************************************************************/
  void DPReCAP_CAP3Calc(TDPReCAP*);

  /******************************************************************************
  ��������������� ������, ����� ��� ���� ����������
  ******************************************************************************/
  void DPReCAP_HelpCalc(TDPReCAP*);


  /******************************************************************************
  ��������������� ������ � ����
  ******************************************************************************/
  void DPReCAP_SlowCalc(TDPReCAP*);

  /******************************************************************************
  �������������� ������
  ******************************************************************************/
  void DPReCAP_msCalc(TDPReCAP*);

#ifdef __cplusplus
}
#endif	// extern "C"

#endif	// V_DPR_ECAP_H
