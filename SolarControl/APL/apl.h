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


unsigned short protect_Code;	//!< //����������� ��� �����
unsigned short alarm_Code;		//!< //����������� ��� ��������������

int powered_okCounter;//!< ������� ��� �������� �������� ������ ����� ����� �������������

void (*init)();
void (*ms_calc)();
} APL;

// ����� ����������� �������� �� ��������� ��� ���
#define APL_DEFAULTS { 0,0,0,0,\
				0,0,\
				0,\
                (void (*)) APL_Init,\
                (void (*)) APL_ms_Calc,\
                 }

// ����� ��������� ��������� ������� ������
void APL_Init(APL*p);
void APL_ms_Calc(APL*p);

#endif
