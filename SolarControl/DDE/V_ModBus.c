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

 \file      V_ModBus.h
 \brief      ƒрайвер ModBus (см. TModBus)
 \author    ќќќ "Ќѕ‘ ¬≈ “ќ–"
 \version   v.1.1. 02/03/2017

 \defgroup  V_ModBus ƒрайвер ModBus (см. TModBus)

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

//!»нициализация.

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
    // поиск размера массива HR
    x = 0;
    while (mbodHR[x].index != 0)
        x++;
    MBInternals.NumOfHRs = x;

    // поиск среднего элемента массива HR
    MBInternals.MiddleOfHRs = x;
    x = 0;
    while ((MBInternals.MiddleOfHRs >> 1) != 0) {
        MBInternals.MiddleOfHRs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfHRs = x;

    // поиск начального инкремента для метода последовательного
    // приближения
    MBInternals.InitialStepOfHRs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfHRs <<= 1;
    }
    MBInternals.InitialStepOfHRs >>= 1;

////// Coils
    // поиск размера массива C
    x = 0;
    while (mbodC[x].index != 0)
        x++;
    MBInternals.NumOfCs = x;

    // поиск среднего элемента массива C
    MBInternals.MiddleOfCs = x;
    x = 0;
    while ((MBInternals.MiddleOfCs >> 1) != 0) {
        MBInternals.MiddleOfCs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfCs = x;

    // поиск начального инкремента для метода последовательного
    // приближения
    MBInternals.InitialStepOfCs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfCs <<= 1;
    }
    MBInternals.InitialStepOfCs >>= 1;

// Discrete Inputs
    // поиск размера массива DI
    x = 0;
    while (mbodDI[x].index != 0)
        x++;
    MBInternals.NumOfDIs = x;

    // поиск среднего элемента массива DI
    MBInternals.MiddleOfDIs = x;
    x = 0;
    while ((MBInternals.MiddleOfDIs >> 1) != 0) {
        MBInternals.MiddleOfDIs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfDIs = x;

    // поиск начального инкремента для метода последовательного
    // приближения
    MBInternals.InitialStepOfDIs = 1;
    while (x != 0) {
        x >>= 1;
        MBInternals.InitialStepOfDIs <<= 1;
    }
    MBInternals.InitialStepOfDIs >>= 1;

////// IR
    // поиск размера массива HR
    x = 0;
    while (mbodIR[x].index != 0)
        x++;
    MBInternals.NumOfIRs = x;

    // поиск среднего элемента массива HR
    MBInternals.MiddleOfIRs = x;
    x = 0;
    while ((MBInternals.MiddleOfIRs >> 1) != 0) {
        MBInternals.MiddleOfIRs >>= 1;
        x = x + x + 1;
    }
    MBInternals.MiddleOfIRs = x;

    // поиск начального инкремента для метода последовательного
    // приближения
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

//!–асчет

//!‘унция обработки посылок ModBus

//! \memberof TModBus
void ModBus_Execute(TModBus *p) {
    unsigned int x;
    volatile unsigned int RxReg;

    ModBusRS.OfflineCounter += 1;

    //долго нет собщений по сети?
    if (ModBusRS.OfflineCounter > ModBusRS.OfflineCounterMax) {
        ModBusRS.isOnline = 0;  //ћы не в сети
        ModBusRS.OfflineCounter = ModBusRS.OfflineCounterMax + 1;  //чтоб не убежал
    } else
        ModBusRS.isOnline = 1;  //в сети

    //јлямкин///////////////////////////////////
    // онтроль ошибок
    if (SCIXREGS.SCICTL1.bit.SWRESET == 0)
        SCIXREGS.SCICTL1.bit.SWRESET = 1;
    if ((SCIXREGS.SCIRXST.bit.RXERR == 1) || (SCIXREGS.SCIRXST.bit.BRKDT == 1))
    {  //≈сли висит ошибка
        ModBusRS.error += 1;
        if (ModBusRS.auto_res == 1)  //≈сли разрешен авто сброс ошибок
            SCIXREGS.SCICTL1.bit.SWRESET = 0;  //—брос ошибки
    }
    if (ModBusRS.clear_error == 1)  //≈сли выставлен флаг однократного ручного сброса ошибки
    {
        SCIXREGS.SCICTL1.bit.SWRESET = 0;
        ModBusRS.clear_error = 0;
        ModBusRS.error = 0;
    }

    if (MBInternals.TxState < 1)  //TxState==0 - передача не идет
        if (SCIXREGS.SCIRXST.bit.RXRDY == 1) {  //≈сли есть готовые принятные данные (байт)
            ModBusRS.receivedBytes++;
            MBInternals.TimeOut = MBInternals.TimeOut1_5;  //“аймаут равный полтора символа
            RxReg = SCIXREGS.SCIRXBUF.all;  //ѕрием очередного символа
            ModBusRS.received_data = RxReg;  //ѕерекладывание принятых данных для отладки

            if (MBInternals.InCount == MODBUS_MAX_RX_COUNT)  //ѕринятно слишком много байт
                return;
            //RxReg=SciaRegs.SCIRXBUF.all;
            MBInternals.In[MBInternals.InCount++] = RxReg;  //ѕринятые данные в массив
            MBInternals.RxCRC ^= RxReg;  //—разу же расчет контрольной суммы
            for (RxReg = 0; RxReg < 8; RxReg++)  //Ёто тоже продолжение расчета контрольной суммы
                if (MBInternals.RxCRC & 0x01) {
                    MBInternals.RxCRC >>= 1;
                    MBInternals.RxCRC ^= MBInternals.MagicNumber;
                } else
                    MBInternals.RxCRC >>= 1;
            //больше ничего, если есть принятые данные, не делается
            return;
        }
    if (MBInternals.TimeOut == 0)  // огда таймаут вышел, его обрабатывает условие MBInternals.TimeOut==1, а равен нулю он становится после приема
    {
        MBInternals.InCount = 0;  //ќбнуление счетчика массива
        MBInternals.RxCRC = 0xFFFF;  //»нициализация контрольной суммы на прием
        if (SCIXREGS.SCICTL2.bit.TXEMPTY == 1)  //≈сли все отправлено (пуст и основной и тенефой регистры)
        {
            RX;  //ѕереключение RS485 на прием
            MBInternals.TxState = 0;  //TxState==0 - передача не идет
            MBInternals.TxCRC = 0xFFFF;  //»нициализация контрольной суммы на передачу
        }
        return;
    }
    if (MBInternals.TimeOut == 1) //; —юда попадаем, когда межу символами появляется пауза в 1,5 символа
        if (MBInternals.InCount != 0) //; ≈сли количество входных данных не равно нулю, то рассматривем, что пришло
        {
            //поддержка broadcast осуществляется тут (по другому я незнаю как еще  - јлямкин)
            //далее переход в передачу - нам туда не нужно, потому обрабатываем здесь
            //обрабатывать имеет смысл только команды на запись (0x5 - write coils и 0x6 - write single register).
            if (MBInternals.In[0] == 0)      //¬ходной массив, байт адреса равен 0 - широковещательный
            {
                //0x5 - write coils
                if (MBInternals.In[1] == 5) {
                    x = (MBInternals.In[4] << 8) + MBInternals.In[5];      //ƒанные
                    //0 - если нашла, 3 - если запрос некорректен,  2 - ошибка в поиске
                    MBInternals.temp = FindVocAddr(mbodC, MBInternals.NumOfCs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3], 1,
                            MBInternals.MiddleOfCs, MBInternals.InitialStepOfCs);
                    if ((x != 0xFF00) && (x != 0x0000))          //ƒанные не валидны, для битовой переменной должны быть FF00 или 0000
                        MBInternals.temp = 3;          //делается как будто FindVocAddr вернула некорректный запрос
                    if (MBInternals.temp == 0)          //если FindVocAddr нашла адрес
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
                    if (MBInternals.temp == 0)                                                //если FindVocAddr нашла адрес
                    {
                        *(unsigned int *) (MBInternals.Addr->addr) = (MBInternals.In[4] << 8) + MBInternals.In[5];
                    }
                }

                //делаем то же самое, что и ниже для правильной отбраковки сообщения и выходим
                MBInternals.InCount = 0;                                                //обнуление массива принятых байт
                MBInternals.TimeOut = 0;                                                //обнуление таймаута
                MBInternals.RxCRC = 0xFFFF;                                                //инициализация контрольной суммы
                return;
            }

            if (MBInternals.In[0] != p->RSNodeID) //; ≈сли номер узла не совпал с нашим, то выкидываем посылку.
            {
                MBInternals.InCount = 0;
                MBInternals.TimeOut = 0;
                MBInternals.RxCRC = 0xFFFF;
                return;
            }
            if (MBInternals.RxCRC != 0)    //; ≈сли не сошлась контрольная сумма, то выкидываем посылку.
            {
                MBInternals.InCount = 0;
                MBInternals.TimeOut = 0;
                MBInternals.RxCRC = 0xFFFF;
                ModBusRS.ErrorCRCCounter++;
                return;
            }
            if (MBInternals.RecievedCounter < 0) //!!!                                                             //; ≈сли еще не проинициализирован счетчик между фреймов (-1), то
            {
                //; инициализируем счетчик и выходим.
                MBInternals.RecievedCounter = MBInternals.TimeOut2_5;
                return;
            }
            if (MBInternals.RecievedCounter > 0) //!!!                                                                        //; ≈сли счетчик паузы между фреймов еще положительный, то уменьшаем его
            {
                //; и выходим
                MBInternals.RecievedCounter--;
                return;
            }
            ModBusRS.RecievedGoodCounter++;
            if (ModBusRS.RecievedGoodCounter>100)
                ModBusRS.RecievedGoodCounter=0;
            //; ≈сли счетчик RecievedCounter досчитал до нуля, то можно переключаться на передачу.
            MBInternals.RecievedCounter = -1;
            TX;    //RS485 на передачу
            MBInternals.TxState = 1;    //ѕередача
            MBInternals.RxCRC = 0xFFFF;
            MBInternals.TimeOut = MBInternals.TimeOut2_5;
            SCIXREGS.SCITXBUF = MBInternals.In[0];    //ѕередается первый байт - адрес устройства, почему-то взят из приема...

            MBInternals.TxCRC ^= MBInternals.In[0];    //сразу расчет контрольноу суммы на передачу
            //и это тоже расчет контрольной суммы
            for (RxReg = 0; RxReg < 8; RxReg++)
                if (MBInternals.TxCRC & 0x01) {
                    MBInternals.TxCRC >>= 1;
                    MBInternals.TxCRC ^= MBInternals.MagicNumber;
                } else
                    MBInternals.TxCRC >>= 1;
            return;
        } else      //количество принятых данных равно нулю.. почему-то
        {
            MBInternals.TimeOut = 0;
            return;
        }
    MBInternals.TimeOut--;      //отсчитывается таймаут
    if (MBInternals.TxState < 1)      //если TxState==0 - нет передачи, т выход, т.к. ниже - передача.
        return;

    if (SCIXREGS.SCICTL2.bit.TXRDY == 0)      //если передатчик занят
        return;

    //»нициализация таймаута
    MBInternals.TimeOut = MBInternals.TimeOut2_5;

    // с этого момента включается дискретный автомат
    // протокола
    //p->TxState=0;

    if (MBInternals.TxState == 1)   //—остояние передачи 1
    {
        ModBusRS.OfflineCounter = 0;   //—четчик для контроля пересылаемых пакетов ModBus
        MBInternals.temp = MBInternals.In[1];   //ѕринятый массив, тут номер функции
        if (MBInternals.temp == 1)    // ‘ункция read Coils
        {
            MBInternals.ToSend = MBInternals.temp;    //для отправки - номер функции
            MBInternals.temp = FindVocAddr(mbodC, MBInternals.NumOfCs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfCs, MBInternals.InitialStepOfCs);
            if (MBInternals.temp == 0)    //в словаре найден элемент
            {
                MBInternals.TxState = 10;
            } else    //ошибка, в словаре элемент не найден
            {
                MBInternals.ToSend |= 0x80;    //добавляется маска ошибки
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 2)       //  од функции read DI
        {
            MBInternals.ToSend = MBInternals.temp;       //для отправки - номер функции
            MBInternals.temp = FindVocAddr(mbodDI, MBInternals.NumOfDIs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfDIs, MBInternals.InitialStepOfDIs);
            if (MBInternals.temp == 0)       //в словаре найден элемент
            {
                MBInternals.TxState = 10;
            } else       //ошибка, в словаре элемент не найден
            {
                MBInternals.ToSend |= 0x80;       //добавляется маска ошибки
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 3)       // ‘ункция read HR
        {
            MBInternals.ToSend = MBInternals.temp;
            MBInternals.temp = FindVocAddr(mbodHR, MBInternals.NumOfHRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfHRs, MBInternals.InitialStepOfHRs);
            if (MBInternals.temp == 0)       //в словаре найден элемент
            {
                MBInternals.TxState = 7;
            } else       //ошибка, в словаре элемент не найден
            {
                MBInternals.ToSend |= 0x80;       //добавляется маска ошибки
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 4)       // ‘ункция read IR
        {
            MBInternals.ToSend = MBInternals.temp;
            MBInternals.temp = FindVocAddr(mbodIR, MBInternals.NumOfIRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3],
                    (MBInternals.In[4] << 8) + MBInternals.In[5], MBInternals.MiddleOfIRs, MBInternals.InitialStepOfIRs);
            if (MBInternals.temp == 0)       //в словаре найден элемент
            {
                MBInternals.TxState = 7;
            } else       //ошибка, в словаре элемент не найден
            {
                MBInternals.ToSend |= 0x80;       //добавляется маска ошибки
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 5)       // ‘ункция write Coil
        {
            MBInternals.ToSend = MBInternals.temp;
            x = (MBInternals.In[4] << 8) + MBInternals.In[5];       //ƒанные
            MBInternals.temp = FindVocAddr(mbodC, MBInternals.NumOfCs, 1, (MBInternals.In[2] << 8) + MBInternals.In[3], 1, MBInternals.MiddleOfCs,
                    MBInternals.InitialStepOfCs);
            if ((x != 0xFF00) && (x != 0x0000))       //ƒанные не валидны - можно только 0xFF00 и 0x0000
                MBInternals.temp = 3;       // ак будто бы FindVocAddr вернула ошибку
            if (MBInternals.temp == 0)       //в словаре найден элемент
            {
                MBInternals.TxState = 12;
                if (MBInternals.In[4] == 0) // ќперация над словарем - reset bit
                    *(unsigned int *) (MBInternals.Addr->addr) &= (0xFFFF - (1 << MBInternals.Addr->type));
                else
                    // set bit
                    *(unsigned int *) (MBInternals.Addr->addr) |= (1 << MBInternals.Addr->type);
                p->Refresh = 1;
            } else                                            //ошибка, в словаре элемент не найден
            {
                MBInternals.ToSend |= 0x80;                                            //добавляется маска ошибки
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else if (MBInternals.temp == 6)  // ‘ункция write HR
        {
            MBInternals.ToSend = MBInternals.temp;
            MBInternals.temp = FindVocAddr(mbodHR, MBInternals.NumOfHRs, 16, (MBInternals.In[2] << 8) + MBInternals.In[3], 1, MBInternals.MiddleOfHRs,
                    MBInternals.InitialStepOfHRs);
            if (MBInternals.temp == 0)  //в словаре найден элемент
            {
                MBInternals.TxState = 12;
                //ќперация над словарем - запись регистра
                *(unsigned int *) (MBInternals.Addr->addr) = (MBInternals.In[4] << 8) + MBInternals.In[5];
                MBInternals.Addr->type = MB_VAR_WRITE;
            } else  //ошибка, в словаре элемент не найден
            {
                MBInternals.ToSend |= 0x80;  //добавляется маска ошибки
                MBInternals.TxState = MBInternals.temp + 3;
            }
        } else  //никакая из поддерживаемых функций
        {
            MBInternals.ToSend = MBInternals.temp | 0x80;  //добавляется маска ошибки
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
        for (x = 0; x < 8; x++)  //ћожно упаковать 8 битовых переменных за раз
        {
            if (MBInternals.In[5] != 0)  //количество запрашиваемых элементов словаря
            {
                //ќтправка элемента словаря
                MBInternals.ToSend |= (((*(unsigned int *) (MBInternals.Addr->addr)) >> (MBInternals.Addr->type)) & 0x01) << x;
                MBInternals.Addr++;
                MBInternals.In[5]--;
            }
            if (MBInternals.In[5] == 0)  //≈сли все отправили
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
        MBInternals.In[5]--; //уменьшение кол-ва запрошенных переменных во входном массиве
        if (MBInternals.In[5] == 0) //≈сли это количество равно нулю (все переменные отправили)
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

//!¬спомогательная функция поиска

//!функция ищет элемент в таблице и возвращает ссылку на него в MBInternals.Addr
//!возвращает:
//!       0 - если нашла
//!       3 - если запрос некорректен
//!       2 - ошибка в пойске

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

