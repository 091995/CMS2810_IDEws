/*!
    Copyright 2017 	АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file        filter.h
 \brief  Инерционное звено в IQ математике (см. TFilter)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  filter Инерционный фильтр (см. TFilter)

 @{
*/


#ifndef _MEAN_FILTER_H
#define _MEAN_FILTER_H



struct SMeanFilter
{
	long input;//! Вход
	long output;//! Выход
	long integral;
	long pos;
	long buff[32];
	void (*calc)(volatile struct SMeanFilter*);//указатель на функцию расчета
};

typedef volatile struct SMeanFilter TMeanFilter;

#define MEAN_FILTER_DEFAULTS {0,0,0,0, \
		{0},\
		TMeanFilter_Calc}

void TMeanFilter_Calc(TMeanFilter*);



#endif

/*@}*/





