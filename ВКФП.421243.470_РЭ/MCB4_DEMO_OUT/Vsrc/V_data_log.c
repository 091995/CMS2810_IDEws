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

 \file      v_data_log.h
 \brief     N-��������� ������ ��� ������������������� � �������� ������� (��. TDataLog).
 � ������ 3.0 ����������� ������������ ����� ������� �������������������.
 �������� ���������:
 ���������� ������� ������������ �������� DLOG_CHANNELS_NUM (���������� �������� ��������� ������).
 ��� SDO-������ ������������ ������ ������������ ����� 32-������ ���������� 'dlog.next_value_var'
 (���, ����� 16-������� ��������, ���� ������ ����). � �� ��������� ��� �����:
 - ����, ��� � ���� "��������" - ������� 16 ��� �����
 - ����, ��� ���������� 16-���������
 ������ ������� ����������� ������� ����� ��������, ����� - ������� � �.�. �� ���� ������.
 ���� ���������� 16-���������, �� ������� ����� �� �������������. ��� �������� ��������:
 �.�. ���� �������� ������ ��������� � ��� 256-��� 16-������� �������, �� ������ ������� �����������
 ������ 256 ���� (128 32-������ �����), ����� - ��������� 256 ����. �.�. ������������ ��� �������� �������.

 \author    ��������� ��� ��� ������
 \version   v 3.0 23/11/2021
 \defgroup  v_data_log �������� ����������� (��. TDataLog)
 @{
 */
/*@{*/

#include "DSP.h"
#include "co_ODvars.h"
#include "V_data_log.h"
#include "CANOpen_drv.h"
#include "main.h"

//! ������� ����������.

/*! �������� � ����. ����� ��� ��������� ������� ���������� ����� CAN.
 ���� ��� CAN, ����� �������� ������ ������ ������� � TDataLog.dlog_iptr  */
//! \memberof TDataLog
void dlog_background_analyzer(TDataLog* p)
{
    p->trig_shift_int = (p->trig_shift & 0xFFFFFF) >> 16;  // ������� ����� ����������� �� % � �����
    if (p->trig_shift_int > 255) p->trig_shift_int = 255;

    if ((p->control & 0x0030) == 0)
    {
        p->control |= (0b11 << 7) | (DLOG_CHANNELS_NUM-1) << 9;
        return;
    }

    // ����� ����� ����������� �������� ����������.
    // ����� �� ����� ������ ���������� ������ �� ����������, ���� ���, � ����, ����, ������, ������ �������.
    // � ����� � ������ ������ ����� ���� �� ������, � ������ - ������� ����������� ��� ��������� �� ������������� ������.
    p->mode_reset = 0;
    p->valid_points_num = 0;    // �.�. ���������� �������������� (mode = 0), �� ����������� �����������, �.�.
                                // 1) �� ����� ����� ����������� ����� ���������� ������������ � ������ ������� ����� ������ �� ������� �
                                // 2) ��������� ������������ ���������� ������ ����� ��������� � ����������� ��������� �� ������, � ����� ������ - �� �����

    for (int i = 0; i < DLOG_CHANNELS_NUM; i++)
    {
        if (p->ind_subind[i] != 0)
        {
            if (co_getObjectInfo(p->pco_vars, p->ind_subind[i], (TObjectInfo*)&p->objectInfo[i]) == 0)
            {
                p->objectInfo[i].varAddr = 0;
            }
        }
        else
        {
            p->objectInfo[i].varAddr = 0;
        }
    }
    p->highPartOfValue = 0;
    p->WriteDelimiter = (p->control >> 16) & 0xFF; // ������������. �������������� 8� ������
    unsigned char mode = (p->control >> 4) & 3; // ����� - 2 ����
    p->control = (0b11 << 7) | (DLOG_CHANNELS_NUM-1) << 9;  // ��� ����������, ��������, ����� ��� ����. ������ �� ������ ������������ �����

    p->mode_reset = mode;
    if (mode == 3) p->Wcounter = 0; // � ������ ����������� ������ 1024 ����� ����� ������ � ������ ����� ������� �������
    p->WriteDelimiterCounter = 0;
    p->highPartOfValue = 0;
}


//! ������� ��� ��������� mode_reset.
//! �������������� ��� ���������� �������� �� ������ �������.
//! ��������� mode_reset �� ���������� � �������� ��������.
//! \memberof TDataLog
int dlog_try_set_mode(Uint16 mode_reset, TDataLog* p)
{
    switch (mode_reset) // ����� ����� ��������?
    {
        case 1: // ����������� ������
            if (p->OneShotOperation == 1)
            {
                if (p->mode_reset == 2) p->mode_reset = 1;
                else return 0;
            }
            else
            {
                p->mode_reset = 1;
            }
            break;

        case 2: // ������ �� ����� ��� ���������
            if (p->mode_reset == 2) return 1;
            p->mode_reset = 2;
            break;

        case 3: // ����������� ������ ����� ���������� ��������������� �� ��� 4 ������� (1024 �����)
            p->mode_reset = 3;
            p->Wcounter = 0;    // � ���� ������ ����� ������ � ������ ����� ������� �������
            break;

        default:
            p->mode_reset = 0;
            return 0;
    }

    // ��� ����� ������ � ����� ������ ���������� ���� "������ ������".
    p->control &= ~(1 << 6);
    p->WriteDelimiterCounter = 0;
    p->highPartOfValue = 0;
    return 1;
}


//! ������� ��� ��������� mode_reset.
//! �������������� ��� ���������� �������� �� ������ �������.
//! ��������� mode_reset �� ���������� � �������� ��������.
//! ��������� ��� ������������� �� ������ ��. ������ �� ������������� ������������ ������� try_set_mode.
//! \memberof TDataLog
void dlog_set_mode(Uint16 mode_reset, TDataLog* p)
{
    dlog_try_set_mode(mode_reset, p);
}


//! ���������� ��������� ����� � ������� �������������.
//! ������ ���������� � �������� �������������� � ���������� ������� ��������,
//! �.�. ��������������� ��������������������. ����� ���������� ������
//! � ������� ��-������� � ����������� �� ���������� ������ ������ ������������
//! \memberof TDataLog
void data_log_update(TDataLog* p)
{
    p->sampling_rate = 10000;
    // ������������ ������. ���� �� �������� ������� WriteDelimiter - �������/
    // WriteDelimiter = 1 - �� �����
    // WriteDelimiter = 2 - ����� ������ ������
    if ((p->WriteDelimiterCounter++ + 1) < p->WriteDelimiter)
        return;
    else
        p->WriteDelimiterCounter = 0;

    if (p->mode_reset != p->mode_reset_prev)
        p->E = 1;
    else
        p->E = 0;
    p->mode_reset_prev = p->mode_reset;

    switch (p->mode_reset)
    {
        case 0:
        {
            p->Wcounter = 0;
            return;
        }

        case 1:  // ����������� ������ - ����� �� ����� � ���� (����� 0)
        {
            // ��� ����� � ����� �������� ����� ������������ �������� (��� ������� Wcounter, � ������� �� ���� �����) � ������������ ������ �����, ����������� � ������ ���� (������ �� ������� ����� � �������� ����� �����������)
            if (p->E == 1)
            {
                p->prehistory_length = p->valid_points_num;     //����� ����������� ����� ���������� �������� �����
                if (p->prehistory_length > p->trig_shift_int)   //���� ����������� ������� ���������, ���������
                    p->prehistory_length = p->trig_shift_int;
                p->first_point_written = (p->Wcounter - p->prehistory_length) & 0xFF;
                p->highPartOfValue = 0;
            }
            p->Wcounter &= 0xFF; // ������ - ���� ����� � counter �� �������� ��������
            for (int i = 0; i < DLOG_CHANNELS_NUM; i++)
            {
                if (p->objectInfo[i].varAddr != 0)
                {
                    p->buff[(i << 8) + p->Wcounter] =
                        p->objectInfo[i].varSize == 16 ? *((int16*)p->objectInfo[i].varAddr) : *((int32*)p->objectInfo[i].varAddr);
                }
            }
            p->Wcounter++;
            p->Wcounter &= 0xFF;  // ���� ������ 256 �����, ���������
            if (p->Wcounter == p->first_point_written)  //���� ����� �� ��������� ������������ �����
            {
                p->mode_reset = 0;              // ����� ����
                p->control |= (0b111 << 6) | ((DLOG_CHANNELS_NUM-1) << 9);  // "������ ������" + "�������������� ������� ��������" + "32-������ ������" + "DLOG_CHANNELS_NUM-1"
            }
            return;
        }

        case 2: // ���������� ��� �� �����
        {
            if (p->E == 1)
            {
                p->highPartOfValue = 0;
            }
            p->valid_points_num++;  // ������� ���������� ���������� �������� ����� �����������
            if (p->valid_points_num > 256)  // ������������
                p->valid_points_num = 256;
            p->Wcounter &= 0xFF; // ������ - ���� ����� � counter �� �������� ��������
            for (int i = 0; i < DLOG_CHANNELS_NUM; i++)
            {
                if (p->objectInfo[i].varAddr != 0)
                {
                    p->buff[(i << 8) + p->Wcounter] =
                        p->objectInfo[i].varSize == 16 ? *((int16*)p->objectInfo[i].varAddr) : *((int32*)p->objectInfo[i].varAddr);
                }
            }
            p->Wcounter++;
            p->Wcounter &= 0xFF;  // ���� ������ 256 �����, ���������
            return;
        }

        case 3: // ����� ����������� ������ DLOG_CHANNELS_NUM x DLOG_SAMPLES_NUMBER �����
        {
            if (p->E == 1)
            {
                p->first_point_written = 0;     // ����� � ������ �����, ����������� �� �����.
                p->highPartOfValue = 0;
            }
            // � ������ ����, ��� ������ � ������ ����������� ���������������,
            // ���������� � ������, "�������" �� ���������
            p->buff[p->Wcounter] =
                    p->objectInfo[0].varSize == 16 ? *((int16*)p->objectInfo[0].varAddr) : *((int32*)p->objectInfo[0].varAddr);
            p->Wcounter++;
            if (p->Wcounter >= (DLOG_CHANNELS_NUM * DLOG_SAMPLES_NUMBER))  // ���� ����� �� �����
            {
                p->mode_reset = 0;                 // ����� ����
                p->control |= (0b111 << 6) | ((DLOG_CHANNELS_NUM-1) << 9);  // "������ ������" + "�������������� ������� ��������" + "32-������ ������" + "DLOG_CHANNELS_NUM-1"
            }
            return;
        }
    }
}

/*@}*/
