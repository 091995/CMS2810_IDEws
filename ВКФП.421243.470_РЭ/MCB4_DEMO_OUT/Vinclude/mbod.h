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
*/


#ifndef MBOD_H
#define MBOD_H
extern int x,y,z;
extern int t,s;



#define MB_VAR_WRITE    1   // признак записи в ModBus-переменную
#define MB_VAR_READ     2   // признак чтения из ModBus-переменной

typedef struct
{
    unsigned int index; // ModBus-адрес
    unsigned int type;  // номер бита для битовых переменных или признак записи/чтения
                        // для HR/IR-переменных (должен сбрасываться пользователем):
                        // 1 - произошла запись
                        // 2 - произошло чтение
    unsigned long addr; // адрес переменной в контроллере
} MB_Record;

extern volatile MB_Record mbodHR[];
extern volatile MB_Record mbodIR[];
extern volatile MB_Record mbodC[];
extern volatile MB_Record mbodDI[];

#endif

