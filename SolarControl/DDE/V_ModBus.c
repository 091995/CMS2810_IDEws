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

 \file      V_ModBus.h
 \brief      ������� ModBus (��. TModBus)
 \author    ��� "��� ������"
 \version   v.1.1. 02/03/2017

 \defgroup  V_ModBus ������� ModBus (��. TModBus)

 @{
*/

#include "DSP.h"
#include "mbod.h"
#include "V_ModBus.h"
#include "main.h"

int FindVocAddr(volatile MB_Record /*const*/Table[], unsigned int TableSize, int Type, int Index, int NumOfIndexs, int Mid, int Step);

#define RX GpioDataRegs.GPECLEAR.bit.GPIOE2=1
#define TX GpioDataRegs.GPESET.bit.GPIOE2=1
#define RS_CONFIG_DIR_PIN EALLOW;GpioMuxRegs.GPEMUX.bit.XNMI_XINT13_GPIOE2=0;GpioMuxRegs.GPEDIR.bit.GPIOE2=1;EDIS
#define SCIXREGS SciaRegs

//!�������������.

void ModBus_Init(TModBus *p) {

    unsigned int x;

    EALLOW;
    GpioMuxRegs.GPFMUX.bit.SCITXDA_GPIOF4 = 1;
    GpioMuxRegs.GPFMUX.bit.SCIRXDA_GPIOF5 = 1;                                  // Port F MUX - x000 0000 0011 0000
    EDIS;
    RS_CONFIG_DIR_PIN;
    RX;

//      MBInternals.TimeOut1_5=(int)(((long)p->BaudRate*(long)17)/p->ExecutionFreq+2);  // 17 ~ 11*1.5
//      MBInternals.TimeOut2_5=(int)(((long)p->BaudRate*(long)28)/p->ExecutionFreq+2);          // 28 ~ 11*2.5

    MBInternals.TimeOut1_5 = (int) (((long) p->ExecutionFreq * (long) 17) / p->BaudRate + 2);       // 17 ~ 11*1.5
    MBInternals.TimeOut2_5 = (int) (((long) p->ExecutionFreq * (long) 28) / p->BaudRate);          // 28 ~ 11*2.5

    x = p->LowPrescSpeed / 8 * 1000 / p->BaudRate - 1;

    SCIXREGS.SCICTL1.bit.SWRESET = 0;
    SCIXREGS.SCICTL1.bit.SWRESET = 1;

    SCIXREGS.SCICCR.bit.STOPBITS = 1;
    SCIXREGS.SCICCR.bit.PARITY = 0;
    SCIXREGS.SCICCR.bit.PARITYENA = 0;
    SCIXREGS.SCICCR.bit.LOOPBKENA = 0;
    SCIXREGS.SCICCR.bit.ADDRIDLE_MODE = 0;
    SCIXREGS.SCICCR.bit.SCICHAR = 7;

    SCIXREGS.SCICTL1.bit.RXERRINTENA = 0;
    SCIXREGS.SCICTL1.bit.SLEEP = 0;
    SCIXREGS.SCICTL1.bit.RXENA = 1;
    SCIXREGS.SCICTL1.bit.TXENA = 1;

    SCIXREGS.SCIHBAUD = x >> 8;
    SCIXREGS.SCILBAUD = x;

    SCIXREGS.SCICTL2.bit.RXBKINTENA = 0;          //1;
    SCIXREGS.SCICTL2.bit.TXINTENA = 0;          //1;

    MBInternals.RecievedCounter = -1;

////// HR
    // ����� ������� ������� HR
    x = 0;
    while (mbodHR[x].index != 0)
        x++;
    MBInternals.NumOfHRs = x;

    // ����� �������� �������� ������� HR
    MBInternals.MiddleOfHRs = x;
    x = 0;
    while ((MBInternals.MiddleOfHRs >> 1) != 0) {
        MBInternals.MiddleOfHRs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfHRs = x;

    // ����� ���������� ���������� ��� ������ �����������������
    // �����������
    MBInternals.InitialStepOfHRs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfHRs <<= 1;
    }
    MBInternals.InitialStepOfHRs >>= 1;

////// Coils
    // ����� ������� ������� C
    x = 0;
    while (mbodC[x].index != 0)
        x++;
    MBInternals.NumOfCs = x;

    // ����� �������� �������� ������� C
    MBInternals.MiddleOfCs = x;
    x = 0;
    while ((MBInternals.MiddleOfCs >> 1) != 0) {
        MBInternals.MiddleOfCs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfCs = x;

    // ����� ���������� ���������� ��� ������ �����������������
    // �����������
    MBInternals.InitialStepOfCs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfCs <<= 1;
    }
    MBInternals.InitialStepOfCs >>= 1;

// Discrete Inputs
    // ����� ������� ������� DI
    x = 0;
    while (mbodDI[x].index != 0)
        x++;
    MBInternals.NumOfDIs = x;

    // ����� �������� �������� ������� DI
    MBInternals.MiddleOfDIs = x;
    x = 0;
    while ((MBInternals.MiddleOfDIs >> 1) != 0) {
        MBInternals.MiddleOfDIs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfDIs = x;

    // ����� ���������� ���������� ��� ������ �����������������
    // �����������
    MBInternals.InitialStepOfDIs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfDIs <<= 1;
    }
    MBInternals.InitialStepOfDIs >>= 1;

////// IR
    // ����� ������� ������� HR
    x = 0;
    while (mbodIR[x].index != 0)
        x++;
    MBInternals.NumOfIRs = x;

    // ����� �������� �������� ������� HR
    MBInternals.MiddleOfIRs = x;
    x = 0;
    while ((MBInternals.MiddleOfIRs >> 1) != 0) {
        MBInternals.MiddleOfIRs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfIRs = x;

    // ����� ���������� ���������� ��� ������ �����������������
    // �����������
    MBInternals.InitialStepOfIRs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfIRs <<= 1;
    }
    MBInternals.InitialStepOfIRs >>= 1;

    for (x = 0; x < 1000; x++)
        ;
}

extern MODBUS_RS ModBusRS;

#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(ModBus_Execute,"secureRamFuncs");
#endif

//!������

//!������ ��������� ������� ModBus

//! \memberof TModBus
void ModBus_Execute(TModBus *p) {
    unsigned int x;
    volatile unsigned int RxReg;

    ModBusRS.OfflineCounter += 1;

    //����� ��� �������� �� ����?
    if (ModBusRS.OfflineCounter > ModBusRS.OfflineCounterMax) {
        ModBusRS.isOnline = 0;  //�� �� � ����
        ModBusRS.OfflineCounter = ModBusRS.OfflineCounterMax + 1;  //���� �� ������
    } else
        ModBusRS.isOnline = 1;  //� ����

    //�������///////////////////////////////////
    //�������� ������
    if (SCIXREGS.SCICTL1.bit.SWRESET == 0)
        SCIXREGS.SCICTL1.bit.SWRESET = 1;
    if ((SCIXREGS.SCIRXST.bit.RXERR == 1) || (SCIXREGS.SCIRXST.bit.BRKDT == 1))
    {  //���� ����� ������
        ModBusRS.error += 1;
        if (ModBusRS.auto_res == 1)  //���� �������� ���� ����� ������
            SCIXREGS.SCICTL1.bit.SWRESET = 0;  //����� ������
    }
    if (ModBusRS.clear_error == 1)  //���� ��������� ���� ������������ ������� ������ ������
    {
        SCIXREGS.SCICTL1.bit.SWRESET = 0;
        ModBusRS.clear_error = 0;
        ModBusRS.error = 0;
    }

    if (MBInternals.TxState < 1)  //TxState==0 - �������� �� ����
        if (SCIXREGS.SCIRXST.bit.RXRDY == 1) {  //���� ���� ������� ��������� ������ (����)
            ModBusRS.receivedBytes++;
            MBInternals.TimeOut = MBInternals.TimeOut1_5;  //������� ������ ������� �������
            RxReg = SCIXREGS.SCIRXBUF.all;  //����� ���������� �������
            ModBusRS.received_data = RxReg;  //�������������� �������� ������ ��� �������

            if (MBInternals.InCount == MODBUS_MAX_RX_COUNT)  //�������� ������� ����� ����
                return;
            //RxReg=SciaRegs.SCIRXBUF.all;
            MBInternals.In[MBInternals.InCount++] = RxReg;  //�������� ������ � ������
            MBInternals.RxCRC ^= RxReg;  //����� �� ������ ����������� �����
            for (RxReg = 0; RxReg < 8; RxReg++)  //��� ���� ����������� ������� ����������� �����
                if (MBInternals.RxCRC & 0x01) {
                    MBInternals.RxCRC >>= 1;
                    MBInternals.RxCRC ^= MBInternals.MagicNumber;
                } else
                    MBInternals.RxCRC >>= 1;
            //������ ������, ���� ���� �������� ������, �� ��������
            return;
        }
    if (MBInternals.TimeOut == 0)  //����� ������� �����, ��� ������������ ������� MBInternals.TimeOut==1, � ����� ���� �� ���������� ����� ������
    {
        MBInternals.InCount = 0;  //��������� �������� �������
        MBInternals.RxCRC = 0xFFFF;  //������������� ����������� ����� �� �����
        if (SCIXREGS.SCICTL2.bit.TXEMPTY == 1)  //���� ��� ���������� (���� � �������� � ������� ��������)
        {
            RX;  //������������ RS485 �� �����
            MBInternals.TxState = 0;  //TxState==0 - �������� �� ����
            MBInternals.TxCRC = 0xFFFF;  //������������� ����������� ����� �� ��������
        }
        return;
    }
    if (MBInternals.TimeOut == 1) //; ���� ��������, ����� ���� ��������� ���������� ����� � 1,5 �������
        if (MBInternals.InCount != 0) //; ���� ���������� ������� ������ �� ����� ����, �� ������������, ��� ������
        {
            //��������� broadcast �������������� ��� (�� ������� � ������ ��� ���  - �������)
            //����� ������� � �������� - ��� ���� �� �����, ������ ������������ �����
            //������������ ����� ����� ������ ������� �� ������ (0x5 - write coils � 0x6 - write single register).
            if (MBInternals.In[0] == 0)      //������� ������, ���� ������ ����� 0 - �����������������
            {
                //0x5 - write coils
                if (MBInternals.In[1] == 5) {
                    x = (MBInternals.In[4] << 8) + MBInternals.In[5];      //������
                    //0 - ���� �����, 3 - ���� ������ �����������,  2 - ������ � ������
                    MBInternals.temp = FindVocAddr(mbodC, MBInternals.NumOfCs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3], 1,
                            MBInternals.MiddleOfCs, MBInternals.InitialStepOfCs);
                    if ((x != 0xFF00) && (x != 0x0000))          //������ �� �������, ��� ������� ���������� ������ ���� FF00 ��� 0000
                        MBInternals.temp = 3;          //�������� ��� ����� FindVocAddr ������� ������������ ������
                    if (MBInternals.temp == 0)          //���� FindVocAddr ����� �����
                    {
                        if (MBInternals.In[4] == 0)   // reset bit
                            *(unsigned int *) (MBInternals.Addr->addr) &= (0xFFFF - (1 << MBInternals.Addr->type));
                        else
                            // set bit
                            *(unsigned int *) (MBInternals.Addr->addr) |= (1 << MBInternals.Addr->type);
                    }
                }
                if (MBInternals.In[1] == 6)                                                //0x6 - write HR
                {
                    MBInternals.temp = FindVocAddr(mbodHR, MBInternals.NumOfHRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3], 1,
                            MBInternals.MiddleOfHRs, MBInternals.InitialStepOfHRs);
                    if (MBInternals.temp == 0)                                                //���� FindVocAddr ����� �����
                    {
                        *(unsigned int *) (MBInternals.Addr->addr) = (MBInternals.In[4] << 8) + MBInternals.In[5];
                    }
                }

                //������ �� �� �����, ��� � ���� ��� ���������� ���������� ��������� � �������
                MBInternals.InCount = 0;                                                //��������� ������� �������� ����
                MBInternals.TimeOut = 0;                                                //��������� ��������
                MBInternals.RxCRC = 0xFFFF;                                                //������������� ����������� �����
                return;
            }

            if (MBInternals.In[0] != p->RSNodeID) //; ���� ����� ���� �� ������ � �����, �� ���������� �������.
            {
                MBInternals.InCount = 0;
                MBInternals.TimeOut = 0;
                MBInternals.RxCRC = 0xFFFF;
                return;
            }
            if (MBInternals.RxCRC != 0)    //; ���� �� ������� ����������� �����, �� ���������� �������.
            {
                MBInternals.InCount = 0;
                MBInternals.TimeOut = 0;
                MBInternals.RxCRC = 0xFFFF;
                ModBusRS.ErrorCRCCounter++;
                return;
            }
            if (MBInternals.RecievedCounter < 0) //!!!                                                             //; ���� ��� �� ������������������ ������� ����� ������� (-1), ��
            {
                //; �������������� ������� � �������.
                MBInternals.RecievedCounter = MBInternals.TimeOut2_5;
                return;
            }
            if (MBInternals.RecievedCounter > 0) //!!!                                                                        //; ���� ������� ����� ����� ������� ��� �������������, �� ��������� ���
            {
                //; � �������
                MBInternals.RecievedCounter--;
                return;
            }
            ModBusRS.RecievedGoodCounter++;
            if (ModBusRS.RecievedGoodCounter>100)
                ModBusRS.RecievedGoodCounter=0;
            //; ���� ������� RecievedCounter �������� �� ����, �� ����� ������������� �� ��������.
            MBInternals.RecievedCounter = -1;
            TX;    //RS485 �� ��������
            MBInternals.TxState = 1;    //��������
            MBInternals.RxCRC = 0xFFFF;
            MBInternals.TimeOut = MBInternals.TimeOut2_5;
            SCIXREGS.SCITXBUF = MBInternals.In[0];    //���������� ������ ���� - ����� ����������, ������-�� ���� �� ������...

            MBInternals.TxCRC ^= MBInternals.In[0];    //����� ������ ����������� ����� �� ��������
            //� ��� ���� ������ ����������� �����
            for (RxReg = 0; RxReg < 8; RxReg++)
                if (MBInternals.TxCRC & 0x01) {
                    MBInternals.TxCRC >>= 1;
                    MBInternals.TxCRC ^= MBInternals.MagicNumber;
                } else
                    MBInternals.TxCRC >>= 1;
            return;
        } else      //���������� �������� ������ ����� ����.. ������-��
        {
            MBInternals.TimeOut = 0;
            return;
        }
    MBInternals.TimeOut--;      //������������� �������
    if (MBInternals.TxState < 1)      //���� TxState==0 - ��� ��������, � �����, �.�. ���� - ��������.
        return;

    if (SCIXREGS.SCICTL2.bit.TXRDY == 0)      //���� ���������� �����
        return;

    //������������� ��������
    MBInternals.TimeOut = MBInternals.TimeOut2_5;

    // � ����� ������� ���������� ���������� �������
    // ���������
    //p->TxState=0;

    if (MBInternals.TxState == 1)   //��������� �������� 1
    {
        ModBusRS.OfflineCounter = 0;   //������� ��� �������� ������������ ������� ModBus
        MBInternals.temp = MBInternals.In[1];   //�������� ������, ��� ����� �������
        if (MBInternals.temp == 1)    // ������� read Coils
        {
            MBInternals.ToSend = MBInternals.temp;    //��� �������� - ����� �������
            MBInternals.temp = FindVocAddr(mbodC, MBInternals.NumOfCs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfCs, MBInternals.InitialStepOfCs);
            if (MBInternals.temp == 0)    //� ������� ������ �������
            {
                MBInternals.TxState = 10;
            } else    //������, � ������� ������� �� ������
            {
                MBInternals.ToSend |= 0x80;    //����������� ����� ������
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 2)       // ��� ������� read DI
        {
            MBInternals.ToSend = MBInternals.temp;       //��� �������� - ����� �������
            MBInternals.temp = FindVocAddr(mbodDI, MBInternals.NumOfDIs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfDIs, MBInternals.InitialStepOfDIs);
            if (MBInternals.temp == 0)       //� ������� ������ �������
            {
                MBInternals.TxState = 10;
            } else       //������, � ������� ������� �� ������
            {
                MBInternals.ToSend |= 0x80;       //����������� ����� ������
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 3)       // ������� read HR
        {
            MBInternals.ToSend = MBInternals.temp;
            MBInternals.temp = FindVocAddr(mbodHR, MBInternals.NumOfHRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfHRs, MBInternals.InitialStepOfHRs);
            if (MBInternals.temp == 0)       //� ������� ������ �������
            {
                MBInternals.TxState = 7;
            } else       //������, � ������� ������� �� ������
            {
                MBInternals.ToSend |= 0x80;       //����������� ����� ������
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 4)       // ������� read IR
        {
            MBInternals.ToSend = MBInternals.temp;
            MBInternals.temp = FindVocAddr(mbodIR, MBInternals.NumOfIRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfIRs, MBInternals.InitialStepOfIRs);
            if (MBInternals.temp == 0)       //� ������� ������ �������
            {
                MBInternals.TxState = 7;
            } else       //������, � ������� ������� �� ������
            {
                MBInternals.ToSend |= 0x80;       //����������� ����� ������
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 5)       // ������� write Coil
        {
            MBInternals.ToSend = MBInternals.temp;
            x = (MBInternals.In[4] << 8) + MBInternals.In[5];       //������
            MBInternals.temp = FindVocAddr(mbodC, MBInternals.NumOfCs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3], 1, MBInternals.MiddleOfCs,
                    MBInternals.InitialStepOfCs);
            if ((x != 0xFF00) && (x != 0x0000))       //������ �� ������� - ����� ������ 0xFF00 � 0x0000
                MBInternals.temp = 3;       //��� ����� �� FindVocAddr ������� ������
            if (MBInternals.temp == 0)       //� ������� ������ �������
            {
                MBInternals.TxState = 12;
                if (MBInternals.In[4] == 0) // �������� ��� �������� - reset bit
                    *(unsigned int *) (MBInternals.Addr->addr) &= (0xFFFF - (1 << MBInternals.Addr->type));
                else
                    // set bit
                    *(unsigned int *) (MBInternals.Addr->addr) |= (1 << MBInternals.Addr->type);
                p->Refresh = 1;
            } else                                            //������, � ������� ������� �� ������
            {
                MBInternals.ToSend |= 0x80;                                            //����������� ����� ������
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 6)  // ������� write HR
        {
            MBInternals.ToSend = MBInternals.temp;
            MBInternals.temp = FindVocAddr(mbodHR, MBInternals.NumOfHRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3], 1, MBInternals.MiddleOfHRs,
                    MBInternals.InitialStepOfHRs);
            if (MBInternals.temp == 0)  //� ������� ������ �������
            {
                MBInternals.TxState = 12;
                //�������� ��� �������� - ������ ��������
                *(unsigned int *) (MBInternals.Addr->addr) = (MBInternals.In[4] << 8) + MBInternals.In[5];
                MBInternals.Addr->type = MB_VAR_WRITE;
            } else  //������, � ������� ������� �� ������
            {
                MBInternals.ToSend |= 0x80;  //����������� ����� ������
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else  //������� �� �������������� �������
        {
            MBInternals.ToSend = MBInternals.temp | 0x80;  //����������� ����� ������
            MBInternals.TxState = 2;
        }
    } else if (MBInternals.TxState == 12)     // send addr hi for write C
    {
        MBInternals.TxState = 13;
        MBInternals.ToSend = MBInternals.In[2];
    } else if (MBInternals.TxState == 13)     // send addr low for write C
    {
        MBInternals.TxState = 14;
        MBInternals.ToSend = MBInternals.In[3];
    } else if (MBInternals.TxState == 14)     // send data hi for write C
    {
        MBInternals.TxState = 15;
        MBInternals.ToSend = MBInternals.In[4];
    } else if (MBInternals.TxState == 15)     // send data hi for write C
    {
        MBInternals.TxState = 3;
        MBInternals.ToSend = MBInternals.In[5];
    } else if (MBInternals.TxState == 10)     // send length read Coils
    {
        MBInternals.TxState = 11;
        MBInternals.In[5] = MBInternals.In[5] + (MBInternals.In[4] << 8);
        MBInternals.ToSend = (MBInternals.In[5] + 7) >> 3;
    } else if (MBInternals.TxState == 11)  // send data read Coils
    {
        MBInternals.ToSend = 0;
        for (x = 0; x < 8; x++)  //����� ��������� 8 ������� ���������� �� ���
        {
            if (MBInternals.In[5] != 0)  //���������� ������������� ��������� �������
            {
                //�������� �������� �������
                MBInternals.ToSend |= (((*(unsigned int *) (MBInternals.Addr->addr)) >> (MBInternals.Addr->type)) & 0x01) << x;
                MBInternals.Addr++;
                MBInternals.In[5]--;
            }
            if (MBInternals.In[5] == 0)  //���� ��� ���������
                MBInternals.TxState = 3;
        }
    } else if (MBInternals.TxState == 7) // send length read HR
    {
        MBInternals.TxState = 8;
        MBInternals.ToSend = MBInternals.In[5] << 1;
    } else if (MBInternals.TxState == 8) // send HR high word
    {
        MBInternals.TxState = 9;
        //x= *MBInternals.Addr->addr;
        MBInternals.temp = *(unsigned int *) (MBInternals.Addr->addr);

        MBInternals.ToSend = MBInternals.temp >> 8;
    } else if (MBInternals.TxState == 9) // send HR low word
    {
        MBInternals.ToSend = MBInternals.temp & 0xFF;
        MBInternals.Addr->type = MB_VAR_READ;
        MBInternals.Addr += 1;
        MBInternals.In[5]--; //���������� ���-�� ����������� ���������� �� ������� �������
        if (MBInternals.In[5] == 0) //���� ��� ���������� ����� ���� (��� ���������� ���������)
            MBInternals.TxState = 3;
        else
            MBInternals.TxState = 8;
    } else if (MBInternals.TxState == 2)      // no such function
    {
        MBInternals.ToSend = 1;
        MBInternals.TxState = 3;
    } else if (MBInternals.TxState == 5)      // send error 2
    {
        MBInternals.ToSend = 2;
        MBInternals.TxState = 3;
    } else if (MBInternals.TxState == 6)      // send error 3
    {
        MBInternals.ToSend = 3;
        MBInternals.TxState = 3;
    } else if (MBInternals.TxState == 3)      // tx crc low
    {
        MBInternals.ToSend = MBInternals.TxCRC & 0x00FF;
        MBInternals.TxState = 4;
    } else if (MBInternals.TxState == 4)      // tx crc high
    {
        MBInternals.ToSend = MBInternals.TxCRC & 0x00FF;
        MBInternals.TxState = 0;
    } else
        MBInternals.TxState = 0;

    MBInternals.TimeOut = MBInternals.TimeOut2_5;

    SCIXREGS.SCITXBUF = MBInternals.ToSend;

    MBInternals.TxCRC ^= MBInternals.ToSend;
    for (RxReg = 0; RxReg < 8; RxReg++)
        if (MBInternals.TxCRC & 0x01) {
            MBInternals.TxCRC >>= 1;
            MBInternals.TxCRC ^= MBInternals.MagicNumber;
        } else
            MBInternals.TxCRC >>= 1;
    return;

}

//!��������������� ������� ������

//!������� ���� ������� � ������� � ���������� ������ �� ���� � MBInternals.Addr
//!����������:
//!       0 - ���� �����
//!       3 - ���� ������ �����������
//!       2 - ������ � ������

//! \memberof TModBus
int FindVocAddr(volatile MB_Record /*const*/Table[], unsigned int TableSize, int Type, int Index, int NumOfIndexs, int Mid, int Step) {
    int x = 0;
    if (Type == 16) {
        if (NumOfIndexs == 0)
            return (3);
        if (NumOfIndexs > 0x7D)
            return (3);
    } else {
        if (NumOfIndexs == 0)
            return (3);
        if (NumOfIndexs > 0x7D0)
            return (3);
    }
    x += Mid;
    Step <<= 1;
    do {
        Step >>= 1;
        if (Index == Table[x].index) {
            if ((x + NumOfIndexs) > TableSize)
                return (2);
            MBInternals.Addr = &Table[x];
            return (0);
        } else if (Index < Table[x].index)
            x -= Step;
        else {
            x += Step;
            if (x >= TableSize)
                x = (TableSize - 1);
        }
    } while (Step != 0);
    return (2);;
}

/*@}*/

