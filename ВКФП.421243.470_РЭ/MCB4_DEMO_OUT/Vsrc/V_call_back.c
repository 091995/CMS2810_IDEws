/*!
 \file      v_call_back.c
 \brief     ���� �������, ���������� ��������� CANOpen

 ������� CANOpen ����� �������� �������� ������������� �������
 ��� ��������� � ��������� �������. ��� ������� �� ������ ���� ��������� � ������-���� ������.
 � ���� ����� ������� ��� ����� �������

 \author	Drozdov Andrey V
 \version   v 1.1 27/02/2010
 */

/** \addtogroup v_call_back */
/*@{*/

#include "DSP28_Device.h"
#include "IQmathLib.h"
#include "main.h"

//!��������� � ����� ��������� �������.

//!���� ���������� ������, �� ��������������� ������ �� ��������� �����.
void callback_RTC(unsigned int par) {

}

//!��������� � ���������� next_value_var � ������� ��������� ������������.

//!���������� ����������� ���������, ����������� ���������������� ���������� ������������������� ����������
//!������ TDataLog. ��� ������� ���������� ��� ��������� � ����������, ����� ������� �������� ������� ����������
//!�������������. ������ � ��� ���������� ������������� ��������� ����� ������ (���� � 4�) � ����� ����������� �����.
//!��� ������ �� � ��� ���������� ������������ ���� ����������������������� ������.
#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(callback_dlog,"secureRamFuncs");
#endif
void callback_dlog(Uint16 par)
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



/*@}*/

