#ifndef _APL_H
#define _APL_H


//#include "APL_protect.h"
//#include "APL_alarm.h"
//
//
//extern APL_PROTECT apl_protect;


typedef struct
{
int counter;
int state;
int state_prev;
int E;


unsigned short protect_Code;	//!< //листающийс€ код защит
unsigned short alarm_Code;		//!< //листающийс€ код предупреждений

int powered_okCounter;//!< —четчик дл€ ожидани€ включен€ модул€ защит после инициализации

void (*init)();
void (*ms_calc)();
} APL;

// «десь присваиваем значения по умолчанию для них
#define APL_DEFAULTS { 0,0,0,0,\
				0,0,\
				0,\
                (void (*)) APL_Init,\
                (void (*)) APL_ms_Calc,\
                 }

// «десь объявляем прототиты функций модуля
void APL_Init(APL*p);
void APL_ms_Calc(APL*p);

#endif
