/*!
    Copyright 2019 A&D

 \file      v_common.h
 \brief     ���������� �������� ������ ���������� ����������, ������� ��� ������� ���� ��� ����, �����
  �������������� �� � ��������� ������
 \author    A&D
 \version   v 1.0 24/05/2019

 \defgroup  v_common ���������� �������� ������ ���������� ����������

@{*/

#ifndef V_COMMON_H
#define V_COMMON_H


//!������� ���� ��� �������� ������� ������� ����������
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

//!��������� ��� ������� ������� ����������
  typedef union
  {
    int all;
    INV_STATUS_BIT bit;
  }TInvStatus;


//!������� ���� ����� ����������
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

//!��������� ����� ���������� (�������� DRV_STATUS_BIT)
  typedef union
  {
    unsigned int all;
    CMD_BIT bit;
  }TCmd;

  
  //! ���������, ���������� �������� �������
    typedef volatile struct
    {
    	long Id_ref;
    	long Iq_ref;
    	long P_ref;// ������� �������� ��������
    	long Q_ref;// ������� �������� ��������
    	long Um1_ref;// ������� ���������� ����
    } TRefs;

//! ��������� ��� �������� ���������� ������� ������� ������� ����������
  typedef struct
  {

    int I_nom;//!< ����������� (�������) ������ ��� � ������� 16.0
    long _1_I_nom;//!< 1/I_nom
    int U_nom;//!< ����������� (�������) ������ ���������� � ������� 16.0
    long _1_U_nom;//!< 1/U_nom 
    int Udc_nom;//!< ����������� (�������) ���������� ��� � ������� 16.0
    long _1_Udc_nom;//!< 1/Udc_nom

    int U_nom_div_Udc_nom;// used by pwm module to find output comparators

	int freq_nom;//!< ����������� (�������) ������� � ������� 16.0
    int P_nom;//!< ����������� (�������) �������� � ������� 16.0, ����� ���� � ���������
    int Pdc_nom;//!< ����������� (�������) �������� � ������� 16.0, ����� ���� � ���������
    int _1_P_nom;

    long Ls;
    long Rs;
  } TInvParams;

  
//! ��������� ��� ������� "��������������"
typedef struct {
		unsigned short  Reboot;			//!< ����������� ������������
		unsigned short 	AutoOffset;		//!< ������������ ���
		unsigned short 	HardwareType;	//!< ��� ������, ��� ������� ������ ������
		} TSysSwitches;


#endif


