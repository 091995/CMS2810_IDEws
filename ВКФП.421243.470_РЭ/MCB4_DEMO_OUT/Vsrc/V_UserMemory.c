/*!
     Copyright 2017     јќ "Ќ»»Ё“" и ќќќ "Ќѕ‘ ¬≈ “ќ–"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_UserMemory.h
 \brief     –абота с энергонезависимой памятью
 \author    ќќќ "Ќѕ‘ ¬ектор". http://motorcontrol.ru
 \addtogroup
 @{*/

/** \addtogroup V_spimem */
/*@{*/

// пример использования
/*  для инициализации
 spimem.init.(&spimem);

 для записи
 spimem.spiaddr=0;
 spimem.startaddr=buff;
 spimem.data_length=1000;
 spimem.writespi(&spimem);
 */

#include "DSP28_Device.h"
#include "DSP28_GlobalPrototypes.h"
#include "V_UserMemory.h"

int receivedSpi = 0;

void spi_xmit(int);

void SPIMEM_Init(TSpiMem *p) {

    EALLOW;
    //настраиваем мультиплицированные выходы на SPI
    GpioMuxRegs.GPFMUX.all |= 0x0007;
    GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3 = 0;
    GpioMuxRegs.GPFDIR.bit.GPIOF3 = 1;
    EDIS;

//настраиваем модуль SPI
//--------------------------------
    SpiaRegs.SPICCR.all = 0x0007;             // Reset on, rising edge, 8-bit char bits

    SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;

    SpiaRegs.SPICTL.all = 0x0007;    // Enable master mode, normal phase,
    // enable talk, and SPI int disabled.
    SpiaRegs.SPIBRR = 0x007F;
    //SpiaRegs.SPIRXEMU
    SpiaRegs.SPICCR.bit.RESET = 1; //reset to SPI

}

void SPIMEM_Write(TSpiMem *p) {
    int var = -1;
    int*data;
    int addr = p->spiaddr;
    int addrh = 0;
    int addrl = 0;
    int temp = 0;
    CHIP_SELECT
    ;
    spi_xmit(WRSR); //write
    spi_xmit(0x2);
    CHIP_DESELECT
    ;

    DSP28x_usDelay(200L);

    CHIP_SELECT
    ;
    spi_xmit(WREN); //write enable
    CHIP_DESELECT
    ;

    data = (int*) p->startaddr;
    while (var < (p->data_length - 1)) {
        DSP28x_usDelay(200L);
        CHIP_SELECT
        ;
        spi_xmit(WREN); //write enable
        CHIP_DESELECT
        ;
        addrl = (int) (addr & 0xff);
        addrh = (unsigned int) (addr & 0xff00) >> 8;
        addr++;
        DSP28x_usDelay(200L);
        CHIP_SELECT
        ;
// пишем младшую часть
        spi_xmit(WR); //write
        spi_xmit(addrh); //addr
        spi_xmit(addrl); //addr
        spi_xmit(*(data)); //data
        CHIP_DESELECT
        ;
        DSP28x_usDelay(200L);
        do {
            CHIP_SELECT
            ;
            spi_xmit(RDSR); //write
            spi_xmit(DUMMY);
            CHIP_DESELECT
            ;
        } while (receivedSpi & 0x1);
        var++;
//если остаток не 1 то пишем старшую
        if ((p->data_length - var) != 1) {
            CHIP_SELECT
            ;
            spi_xmit(WREN); //write enable
            CHIP_DESELECT
            ;
            DSP28x_usDelay(200L);
            CHIP_SELECT
            ;
            addrl = (int) (addr & 0xff);
            addrh = (int) ((addr & 0xff00) >> 8);
            addr++;
            temp = ((*(data)) >> 8) & 0x00ff;
            data++;
            spi_xmit(WR); //write
            spi_xmit(addrh); //addr
            spi_xmit(addrl); //addr
            spi_xmit(temp); //data
            CHIP_DESELECT
            ;
            DSP28x_usDelay(200L);
            do {
                CHIP_SELECT
                ;
                spi_xmit(RDSR); //write
                spi_xmit(DUMMY);
                CHIP_DESELECT
                ;
            } while (receivedSpi & 0x1);
            var++;
        }

    }

}

void SPIMEM_Read(TSpiMem *p) {
    int var = -1;
    int addr = p->spiaddr;
    int addrh = 0;
    int addrl = 0;

    while (var < (p->data_length - 1)) {
        addrl = (int) (addr & 0xff);
        addrh = (int) ((addr & 0xff00) >> 8);
        addr++;
        CHIP_SELECT
        ;
        spi_xmit(RD);
        spi_xmit(addrh); //addr
        spi_xmit(addrl); //addr
        spi_xmit(DUMMY); //read data
        CHIP_DESELECT
        ;
        *p->startaddr = receivedSpi;
        var++;

        if ((p->data_length - var) != 1) {
            addrl = (int) (addr & 0xff);
            addrh = (unsigned int) ((addr & 0xff00) >> 8);
            addr++;
            CHIP_SELECT
            ;
            spi_xmit(RD);
            spi_xmit(addrh); //addr
            spi_xmit(addrl); //addr
            spi_xmit(DUMMY); //read data
            //spi_xmit(DUMMY);//read data
            //(*p->startaddr)=(int)receivedSpi<<8;
            (*p->startaddr) += (int) receivedSpi << 8;
            CHIP_DESELECT
            ;
            p->startaddr++;
            var++;
        }
    }
}
///////////////////////////////
/////////////////////////////
/////////////////////////////

void spi_xmit(int a) {

    while (SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1) {
    }
    SpiaRegs.SPITXBUF = a << 8;
    while (SpiaRegs.SPISTS.bit.INT_FLAG == 0) {
    }
    a = SpiaRegs.SPIRXBUF;
    receivedSpi = a;

}

/*@}*/
