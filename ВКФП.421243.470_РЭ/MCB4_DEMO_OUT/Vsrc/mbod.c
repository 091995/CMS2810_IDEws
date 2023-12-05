/*!
    Copyright 2023 	��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      mbod.c
 \brief     ������� �������� MODBUS
 \author    ��� "��� ������". http://motorcontrol.ru
*/

/** \addtogroup MODBUS */
/*@{*/

#include "mbod.h"
#include "main.h"


/* �������� �������
 * ������ ���� � �������:
 * ����� ���� 1 ����, ������� 1 ����, ����� 2 �����, ������/���-�� ���������� 2 �����, ����������� ����� CRC16(LH)
 * ������ �����������, ��������, ���������� COMpump
 *
01 06 07 D0 00 64 88 AC // ������ � �������� 2000 ����� 100
01 03 07 D0 00 01 84 87 // ������ ��������� 2000

� ��������:
mbodHR - ���������� Holding Registers (�� ������ � ������). ��� �������	0x03(�� ������) 0x06(�� ������)
mbodIR - ���������� Input Registers (�� ������). ��� �������	0x04
mbodC - ������� ���������� Coil (��� ������). ��� ������� 0x05(�� ������)
mbodDI - ������� ���������� Discrete Inputs (��� ������). ��� ������� 0x02(�� ������)

������ ����� ������� - ����� ���������� � �������  ModBus.
������ - ����� ���� ��� ������� ���������� � ���������� �����������.
������ - ����� ����������.


*/

#warning ��������� ������� ��� �������������
volatile MB_Record mbodHR[] = {\
		2000,  0,(long)(&DebugW1),/*�������� ���������� ��� �������� ������ ModBus */\
        0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
};

volatile MB_Record mbodIR[] = {\
                           	0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
                           	};

volatile MB_Record mbodC[] =  {\
                           	0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
                            };



volatile MB_Record mbodDI[] =  {0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
                          	};

/*@}*/
