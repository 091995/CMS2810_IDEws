#ifndef APL_ALARM_H
#define APL_ALARM_H

//#include "DCS_func.h"

#define SM_APL_ALARM_INIT 0
   
typedef struct
{
//������: ������ ��� �������� 1 � 2
int * p_alarm_word_statcom1[18];
int * p_alarm_word_statcom2[18];
int * p_mask_word_statcom1[18];
int * p_mask_word_statcom2[18];
int prev_alarm_word_statcom1[18];
int prev_alarm_word_statcom2[18];
int p_masked_word_statcom1[18];
int p_masked_switch_word_statcom1[18];
int p_AR_word_statcom1[18];
int p_masked_word_statcom2[18];
int p_masked_switch_word_statcom2[18];
int p_AR_word_statcom2[18];
int counter;
int state;
int state_prev;
int E;
void (*init)();
void (*calc)();
} APL_ALARM;

// ����� ����������� �������� �� ��������� ��� ���
#define APL_ALARM_DEFAULTS {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},\
				0,0,0,0,\
                (void (*)(long))APL_ALARM_Init,\
                (void (*)(long))APL_ALARM_Calc,\
                 }

// ����� ��������� ��������� ������� ������
void APL_ALARM_Init();
void APL_ALARM_Calc();
#endif
