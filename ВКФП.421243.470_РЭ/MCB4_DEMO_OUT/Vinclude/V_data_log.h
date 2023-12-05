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

/* Callback-������� �� ���������� "dlog.next_value_var" ������ ��������� ���:
 * (��� ������� ������ ����������� � ����� "v_call_back.c" ��� "CANOpenUDfuncs.c")

void callback_dlog(Uint16 par, Uint16 tag_CANnum)
{
    // ���� ��������� ������ � ����������, �� ��������� ����� �� ������ �����.
    if (par == 1)
    {
        //  � ���������� next_value_var ������������ �������� ��������, ����� ������, �� �������� ����� ������,
        // � ����� ������������ (��������)
        int n_old = (int)((dlog.next_value_var >> 24) & 3);     // ����������� ����� ������ ("������" 4-��������� ������)
        int n_new = (int)((dlog.next_value_var >> 28) & 0xF);   // ����������� ����� ������ ("�����" N-��������� ������)
        dlog.buff_num = n_new != 0 ? n_new : n_old;
        dlog.highPartOfValue = (int)((dlog.next_value_var >> 26) & 1); // �������� ������� ����� 32-������� ��������?
        dlog.Rcounter = (dlog.next_value_var >> 16) & 0xFF; // ����� ����� ���� ��������
        // ��������� ����� �� ������������ ������� ��������
        if ((dlog.next_value_var & 0xffff) == 1)
        {
            if (dlog.pco_vars->co_blockTransferCommand == CANBT_INTERFACE_FREE)
                dlog.pco_vars->co_blockTransferCommand = CANBT_INTERFACE_DATALOG1;
        }
        if ((dlog.next_value_var & 0xffff) == 2)
        {
            if (dlog.pco_vars->co_blockTransferCommand == CANBT_INTERFACE_FREE)
                dlog.pco_vars->co_blockTransferCommand = CANBT_INTERFACE_DATALOG2;
        }
    }

    //��������� ������:
    int32 val32 = dlog.buff[(dlog.buff_num << 8) + ((dlog.Rcounter + dlog.first_point_written) & 0xFF)];
    int varSizeIs16 = (int)(dlog.objectInfo[dlog.buff_num].varSize == 16);
    dlog.next_value_var = (dlog.highPartOfValue != 0 ? val32 >> 16 : val32) & 0x0000FFFF;
    dlog.next_value_var |= ((Uint32)dlog.Rcounter) << 16;
    dlog.next_value_var |= ((Uint32)(dlog.buff_num & 3)) << 24;
    dlog.next_value_var |= ((Uint32)dlog.highPartOfValue) << 26;
    dlog.next_value_var |= ((Uint32)varSizeIs16) << 27;
    dlog.next_value_var |= ((Uint32)(dlog.buff_num & 0xF)) << 28;

    if ((dlog.highPartOfValue != 0) || varSizeIs16)
    {
        // ��� ��������� ������� ������� ������� ����� ��������� �����.
        dlog.Rcounter++;
        dlog.Rcounter &= 0xFF;
        dlog.highPartOfValue = 0;
    }
    else
    {
        // ��� ��������� ������� ������� ������� ����� ���� �� �����.
        dlog.highPartOfValue = 1;
    }
}

*/

#ifndef V_DATA_LOG_H
#define V_DATA_LOG_H

#include "co_ODvars.h"
#include "CANOpen_drv.h"

#ifdef __cplusplus
extern "C"
{
#endif

//! ����� ������� ������������������� (4...16):
#define DLOG_CHANNELS_NUM   4
#if (DLOG_CHANNELS_NUM < 4) || (DLOG_CHANNELS_NUM > 16)
    #error ����� ������� ������������������� ������� �� �������� [4...16]
#endif


//! ������ �������� ��� �������������������.
//! ���� ����� ������, �� ��� ������ ���� �� ������ ��� - ������� ����� �������� �� ��� �����
//! ���������� ������, ��� ��� �� ��� ����� ������� ���������: ��������, ��� ��������� ������
//! ����������� ����� �����������: p->Wcounter&=0xFF, ��� FF - ����� (������������� 256 �����)
#define DLOG_SAMPLES_NUMBER 256


#define DLOG_DATA_SIZE      32  // ��� ������������� � ������� CANBlockTransferInterface.c


/*! \class TDataLog
 \brief N-��������� ������ ��� ������������������� � �������� �������

 ����� \a TDataLog, ���������� �� ��������� SDataLog, ��������� ���������� ��������� N ���������� � �������
 �� 255 ����� � �������� �������������� �� �������. ����� ����, �����
 ����� � ��������� CANOpen ��� ������������� �������� ���� ����������: �����
 "��������" � ���������� ����� ������������ ������� �������.*/

//! ��. TDataLog
struct SDataLog
{
    int32 buff[DLOG_CHANNELS_NUM * DLOG_SAMPLES_NUMBER];    //!< ������ ��� �������� ������������
    Uint16 Wcounter;            //!< ������� �� ������� ��� ������
    Uint16 Rcounter;            //!< ������� �� ������� ��� ������

    int32 upload_buff[DLOG_SAMPLES_NUMBER]; //!< ������ ��� �������� ������������� � ������
    Uint32 trig_shift;  //!< ����� ������ ����� ����� ������������ ��������. ������������, ����� ������, ������� ����� ����������� ���������.
    Uint16 trig_shift_int;      //!< �� ��, ������������ � �����
    Uint16 first_point_written; //!< ������ �����, ����������� � ������������ ������������� � ������ ����� ����������� � ����� ������������ ��������
    Uint16 prehistory_length;   //!< ����� ���������� ����������� (���� ���������� ��������������������� ������� "��������", ��� ����������)
    Uint16 valid_points_num;    //!< ������� �������� ����� �����������, ���������� ����� ����������������� ������� "��������" � �������

    /*!  ������� ������ ������:
     0 - ����
     1 - ����������� ������
     2 - ������ �� ����� ��� ���������
     3 - ����������� ������ ����� ���������� �� ��� 4 ������� ���������������, ��� ��������� ������� �������������.
     ������������� ���������� ���� ������ ������� ������� set_mode! */
    Uint16 mode_reset;             //!< �������� ����� ������
    Uint16 mode_reset_prev;        //!< ���������� ����� ������
    int E;                         //!< ���� ������� ��������� � ���������

    /*! "control": ������� 16 ��� - ��������� ��������, ������� 16 ��� - �����:
    F E D C B A 9 8 7 6 5 4 3 2 1 0
    | | | | | | | | | | | | | | | |
    | | | | | | | | | | | | ������ 4 ���� - ����� �� 4� ��������� ���������� (��� "�������" 4-���������� �������)
    | | | | | | | | | | 2 ���� - �������� ����� �����������: 0, 1, 2
    | | | | | | | | | ��� "������ ������" - ��������������� ������������
    | | | | | | | | ��� "�������������� ������� ��������"
    | | | | | | | ��� "32-������ ������"
    | | | ����� ������� ������������������� ����� 1 (��� "������" N-���������� �������)
    ������
    */
    Uint32 control;                  //!< ���������� ������������ ����� ������� ���������

    Uint32 ind_subind[DLOG_CHANNELS_NUM];   //!< ������.��������� ������������������ �������� (��������������� ������� ��, ��������, ��������)

    unsigned int WriteDelimiter;        //!<�������� ������ ��� ������
    unsigned int WriteDelimiterCounter; //!<������� ��� ��������
    unsigned long next_value_var;   //!<����� ��� ���������� ������������ ���������� �������� ��� ���������� ������� ��:
                                    //!<���� 0-15: �������� �����
                                    //!<���� 16-23: Rcounter (���������� �����)
                                    //!<���� 24-25: buff_num (0...3 - ��� "�������" 4-���������� �������)
                                    //!<��� 26: ����, ��� � ���� "��������" - ������� 16 ��� �����
                                    //!<��� 27: ����, ��� ���������� 16-���������
                                    //!<���� 28-31: buff_num (0...15 - ��� "������" N-���������� �������)
    Uint16 StartBits;
    int buff_num;               //!<����� ������, �� �������� ���� ���������� �������� � next_value_var
    Uint16 OneShotOperation;    //!<���� ������������� ������������ ������ �� ������� ������� (������� � 1 �������� ������ �� 2)
    TCo_OdVars *pco_vars;       //!<����� ��������� �������� CANopen
    Uint32 sampling_rate;       // ������� ������� ������ (������ ������� 'update'), ��
    int highPartOfValue;        //!<���� ������ ������� �����
    TObjectInfo objectInfo[DLOG_CHANNELS_NUM];  //!<���������� �� ������������������ �������� �������

    void (*update)(volatile struct SDataLog *);         //!<Update function
    int (*try_set_mode)(Uint16 mode_reset, volatile struct SDataLog *); //!<Function to change working mode. Returns 1 on success.
    void (*set_mode)(Uint16 mode_reset, volatile struct SDataLog *);    //!<Function to change working mode (deprecated - use try_set_mode function).
    void (*background_analyzer)(volatile struct SDataLog *);    //!<Background analyzer function
};

typedef volatile struct SDataLog TDataLog;

#if defined(CAN_1_ENABLE) || defined(CAN_A_ENABLE)
#define DLOG_CO_VARS co1_vars
#endif

//! ������������� ��-��������� ��� ������� ������
#define DATALOG_DEFAULTS \
{ \
    .buff = { 0 }, \
    .Wcounter = 0, \
    .Rcounter = 0, \
    .upload_buff = { 0 }, \
    .trig_shift = 0, \
    .trig_shift_int = 0, \
    .first_point_written = 0, \
    .prehistory_length = 0, \
    .valid_points_num = 0, \
    .mode_reset = 2, \
    .mode_reset_prev = 2, \
    .E = 0, \
    .control = (DLOG_CHANNELS_NUM-1) << 9, \
    .ind_subind = { 0 }, \
    .WriteDelimiter = 0, \
    .WriteDelimiterCounter = 0, \
    .next_value_var = 0, \
    .StartBits = 0, \
    .buff_num = 0, \
    .OneShotOperation = 0, \
    .pco_vars = &DLOG_CO_VARS, \
    .sampling_rate = 10000, \
    .highPartOfValue = 0, \
    .objectInfo = { 0 }, \
    .update = data_log_update, \
    .try_set_mode = dlog_try_set_mode, \
    .set_mode = dlog_set_mode, \
    .background_analyzer = dlog_background_analyzer, \
}

//! \memberof TDataLog
void data_log_update(TDataLog*);
//! \memberof TDataLog
int dlog_try_set_mode(Uint16 mode_reset, TDataLog*);
//! \memberof TDataLog
void dlog_set_mode(Uint16 mode_reset, TDataLog*);
//! \memberof TDataLog
void dlog_background_analyzer(TDataLog*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/

