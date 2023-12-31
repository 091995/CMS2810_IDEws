/*!
     Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 
 \file      V_RTC_Clock.c
 \brief     ������ ��� ������ � ������ ��������� �������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/*

 *
 *  ���� DS1340 �������� � ������ ������ � ����� 10 ��������� ������/�������� (0x0 ... 0x9).
 * ����� � ���� ����� � ��������� 0x0 ... 0x6.
 * ������� �������� �����, ������� ������ ���., � ������� ������ ����� � 0x7 ... 0x9.
 * ��������� �� ������� ������� ����� ��������, �������� � ���� ��������������� ����� .
 * ����� ��������� ���-�� �� �����, ������� ����� ���������� � ����� � ������ ������ � �������� �����
 * ��������, � �������� ����� ������� ������. ����� ����� ����� ����� ���������� � �����, �� ���
 * � ������ ������. ����� ���� ������ ����� ���������� ���� ��������� �� �������, ������� � ����
 * ��������, ����� �������� ��� ������� � ���������� ���������. ��� ����� "���������" ��������
 * ��������� �� ������� ������� ����� ����������������������, ������ � ����� ������������������
 * (�����������, ��� ���������� ����� 0x5)
 * 0x5 -> 0x6 -> 0x7 -> 0x0 -> 0x1 -> ... -> 0x7 -> 0x0
 * ����� ������� � ��������� ��� ��������, ����� �������� �� ������ ����.
 *
 * ��� ����, ����� �������� � ������ �����, ����� ��������� �������� �� �� �����.
 * � ������ ������ ������������ ������� ����� ��������, � ������� ����� �������� ���-��, � �����
 * ������, ������� ����� ���� ��������. ��������� �� �������� ��� ��������� �������� ����������������
 * ��� ��, ��� � ��� ������.
 *
 * ������ �������� � �������-���������� �������.
 */

//�������������� ������� ������ ���������� �� ������ ���������� (NT_RTC � RTC_REG). ����� �� �������������� - �� ����.
#include <DSP.h>
#include <main.h>
// ���������� ����������� ���������� ������� � ���. ���� ������ ���������� - ���������� ������������ ������ ��� �������, � �����
// ����� ��������� ����������. ���� ������������ - ������ ������� ����� ��������� � ����� (������� ������������� � ��)
#define USE_RTC

/* �������������  RTC */
void RTC_Clock_Init(TRTCClock *p) {

}

/* ������� ���������� �������� ������� */
void RTC_Clock_Read_Time(TRTCClock *p) {
	Uint16 tempSec, tempMin, tempHour, tempDOW, tempDay, tempMonth, tempYear;

	/* ���������� ���������� ������� ��������� */
	NT_RTC->SHDW = 0x0;

	/* ��������� ����� */
	tempSec = NT_RTC->SECOND;
	tempMin = NT_RTC->MINUTE;
	tempHour = NT_RTC->HOUR;
	tempDOW = NT_RTC->WDAY;
	tempDay = NT_RTC->DAY;
	tempMonth = NT_RTC->MONTH;
	tempYear = NT_RTC->YEAR;

	/* ��������� ���������� ������� ��������� */
	NT_RTC->SHDW = 0x80;

	// ����� ����� ��������������� ��������� ������, �.�. ��� �������� � ���� �������-���������� ����� (������)
	p->second = (tempSec & 0xF) + (((tempSec & 0x70) >> 4) * 10);
	p->minute = (tempMin & 0xF) + (((tempMin & 0x70) >> 4) * 10);
	p->hour = (tempHour & 0xF) + (((tempHour & 0x30) >> 4) * 10);
	p->DOW = tempDOW;//(tempDOW & 0x7);
	p->day = (tempDay & 0xF) + (((tempDay & 0x30) >> 4) * 10);
	p->month = (tempMonth & 0xF) + (((tempMonth & 0x10) >> 4) * 10);
	p->year = (tempYear & 0xF) + (((tempYear & 0xF0) >> 4) * 10);

	// �������, �������� �������� ����������� � ����������
	p->packed_time = ((Uint32) p->day << 27) + ((Uint32) p->month << 23)
			+ ((Uint32) p->year << 17) + ((Uint32) p->hour << 12)
			+ ((Uint32) p->minute << 6) + (Uint32) p->second;

}

/* ������� ��������� ������� */
void RTC_Clock_Set_Time(TRTCClock *p) {
	// ��������� ���������� (�������, ������, ����...)
	unsigned char tempSec, tempMin, tempHour, tempDOW, tempDay, tempMonth,
			tempYear;
	p->tryCounter = 0;

	// ������� ����� ����������� ����
	p->second = p->timeToSet & 0x3F;
	p->minute = (p->timeToSet >> 6) & 0x3F;
	p->hour = (p->timeToSet >> 12) & 0x1F;
	p->year = (p->timeToSet >> 17) & 0x3F;
	p->month = (p->timeToSet >> 23) & 0xF;
	p->day = (p->timeToSet >> 27) & 0x1F;
	// ������ ��� ������ (���������)
	int16 a = (14 - p->month) / 12;
	int16 y = p->year - a;
	int16 m = p->month + 12 * a - 2;
	int16 c = (p->year+2000)/100;
	p->DOW = (p->day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)% 7;


	tempSec = ((p->second / 10) << 4) + ((p->second % 10) & 0xF);
	tempMin = ((p->minute / 10) << 4) + ((p->minute % 10) & 0xF);
	tempHour = ((p->hour / 10) << 4) + ((p->hour % 10) & 0xF);
	tempDOW = p->DOW; //& 0x3;
	tempDay = ((p->day / 10) << 4) + ((p->day % 10) & 0xF);
	tempMonth = ((p->month / 10) << 4) + ((p->month % 10) & 0xF);
	tempYear = ((p->year / 10) << 4) + ((p->year % 10) & 0xF);

	p->msInDay = (Uint32) p->hour * 3600000 + (Uint32) p->minute * 60000
			+ (Uint32) p->second * 1000;



	NT_RTC->YEAR = tempYear;
	NT_RTC->MONTH = tempMonth;
	NT_RTC->DAY = tempDay;
	NT_RTC->WDAY = tempDOW;
	NT_RTC->HOUR = tempHour;
	NT_RTC->MINUTE = tempMin;
	NT_RTC->SECOND = tempSec;
}

void RTC_Clock_Ms_Calc(TRTCClock *p) {
	p->ms++;
	p->msInDay++;
#ifdef USE_RTC
	if (p->ms > 999) {
		p->ms = 0;
		p->readTimeFlag = 1;
	}

	//�������� ������ ����� ��������� ������� � ���������, � ����������� �� �����, ��������� ��� ����� ������
	if (p->secondPrev == p->second)	//������� �� ��������
		p->stoppedCounter++;				//�������, ��� �����
	else										//���������, ������ ���� ��������
		p->stoppedCounter = 0;

	if ((p->stoppedCounter < RTC_SECOND_WAITING_TIMEOUT) && (p->year<48))		//���� �������� - ������ � ��� �� 2048 (��� ����� ��� ���������)
		p->ClockOk=1;

	else
	{
		p->ClockOk=0;
		p->stoppedCounter = RTC_SECOND_WAITING_TIMEOUT;
	}
	p->secondPrev = p->second;





#else

	if (p->ms == 1000) {
		p->ms = 0;
		p->second++;

		if (p->second == 60) {
			p->second = 0;
			p->minute++;
			if (p->minute == 60) {
				p->minute = 0;
				p->hour++;
				if (p->hour == 24) {
					p->hour = 0;
					p->msInDay = 0;
					p->day++;
				}
			}
		}
		p->packed_time = ((Uint32)p->day << 27) + ((Uint32)p->month << 23) + ((Uint32)p->year << 17) +
		((Uint32)p->hour << 12) + ((Uint32)p->minute << 6) + (Uint32)p->second;
	}

#endif

}

void RTC_Clock_Slow_Calc(TRTCClock *p) {
	if (p->setTimeFlag == 1) {
		p->timeToSet = p->packed_time;
		p->set(p);
		p->read(p);
		p->msInDay = (Uint32) p->hour * 3600000 + (Uint32) p->minute * 60000
				+ (Uint32) p->second * 1000;
		p->setTimeFlag = 0;
	} else if (p->readTimeFlag == 1) {
		p->read(p);
		p->readTimeFlag = 0;
	}
}


