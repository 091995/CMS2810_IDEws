/*!
    Copyright 2017  �� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      X_CANFlashProgData.h
 \brief     �������� ���� ������������� - �������� � ��� � ��� ���������� ����������, ����� �� CANopen ����� �������� ��������� �� flash.
 \author    ������� �.
 \version   v 1.0 30/05/2017

 \defgroup X_CANFlashProgData */
/*@{*/

/* ==================================================================================
//File name:       X_CANFlashProgData.h
//
//Originator:	Aliamkin Dmitriy I
//
//Description:   �������������� ������� ������� �� CAN�
//����������:    
//=====================================================================================
//-------------------------------------------------------------------------------------
// 16.12.2011	Release	Rev 1.0
//----------------------------------------------------------------------------------*/
#ifndef X_CANFLASHPROGDATA_H
#define X_CANFLASHPROGDATA_H

#ifdef __cplusplus
extern "C"
{
#endif
//����� ��������� ��������
extern Uint32 const FPSettingsAddr;
//����� ������ ��������� �������������
extern Uint32 const FPStartAddr;
//���������� ������� � ������� FPAddrs
extern Uint16 const FPNumOfAddrs;
//������ ������ ������ �������������
extern Uint32 const FPAddrs[];
//����� ������ �������������
extern Uint16 const FPPartsLength[];
//������ �������������
extern Uint16 const FPData[];
#ifdef __cplusplus
}
#endif

#endif
