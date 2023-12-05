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


// пример использования в модуле main
/*  для инициализации
    spimem.init.(&spimem);

    для записи
    spimem.spiaddr=0;
    spimem.startaddr=buff;
    spimem.data_length=1000;
    spimem.writespi(&spimem);
*/

#ifndef V_SPIMEM_H
#define V_SPIMEM_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct SSpiMem
  {
    int spiaddr;
    unsigned int *startaddr;        /*  */
    int data_length;    /* */
    int receivedSpi;
    void (*init)(struct SSpiMem*);     /* Pointer to the init funcion           */
    void (*writespi)(struct SSpiMem*); /* Pointer to the calc funtion           */
    void (*readspi)(struct SSpiMem*);
  };

  typedef struct SSpiMem TSpiMem;

#define USERMEMORY_DEFAULTS { 0,0,0,0,  \
    SPIMEM_Init, \
    SPIMEM_Write,\
    SPIMEM_Read,\
  }



  void SPIMEM_Init(TSpiMem*);
  void SPIMEM_Write(TSpiMem*);
  void SPIMEM_Read(TSpiMem*);

#define CHIP_DESELECT GpioDataRegs.GPFSET.bit.GPIOF3=1;
#define CHIP_SELECT GpioDataRegs.GPFCLEAR.bit.GPIOF3=1;

#define WREN 0x6
#define WRDI 0x4
#define RDSR 0x5
#define WRSR 0x1
#define RD 0x3
#define WR 0x2
#define DUMMY 0x0


#ifdef __cplusplus
}
#endif

#endif




