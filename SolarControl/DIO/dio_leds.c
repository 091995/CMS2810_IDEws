/*
 * leds.c
 *
 *  Created on: 30 ���. 2018 �.
 *      Author: admin
 */
#ifndef MODEL
#include "V_IQmath.h"
#endif
#ifndef MODEL
#include "dio_leds.h"
#endif
#ifndef MODEL
#include "main.h"
#endif

//������� ��� ���������/���������� ����������� �� ����� ControlCARD
//����� ������������ ������� ���� NT_GPIOC->DATA &= ~(1 << 2) � NT_GPIOC->DATA |= (1 << 2), ��
//����� ������� ����� ������ ��������� �� �����, � ����� 2 ����� (��� ������� � ��������������), �, ����
//������ �������� 2 �������, �������� NT_GPIOC->DATA &= ~(1 << 2) � NT_GPIOC->DATA &= ~(1 << 3), �� ������
//� ������� ������������ �� ���������, ��� ��� ������ � ���� �������������� ������� ������� ����� �����, ���������� �������
//���� � ������� ��� �����. �� ������ �� GPIO ���������� ������� ��������� �����, � � ������� ���������� ������ ������� (������ ������ ��)
//����������� ��������� �� ����� ��������� ���������, ������� ������� ������ �������, ������� ������ ������� ������ ��� ���,
//������� ������ ��������� ������ �������.
//��� ���� �������� ����������� ������ ��� ���������� ������� ����������� �����������. ��� ����������� ���������� ����������
//���������� ����� ������������ ������ ����� ����������� � GPIO � ������������� �������� �����������.

//������ ������ - ��������� � GPIO �� ����� (��. ������������): MASKLOWBYTE - � �������� ����� ��������, MASKHIGHBYTE - � ��������.
//��������, �� ����� ������ "1" �� GPIO2, GPIO3 � GPIO4 ����� C:
//0001 1100		�����, �������� �������� � ������� MASKLOWBYTE
//xxx1 11xx		������������ ��������: � ������ ����� - �������, � ��������� - �� �����, �.�. ��� �� �������� � ����� � �� ����� ��������
//NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 28;	��� �������� ��� �������, ��� �������: NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 0xFF;
//���� ���� �������� GPIO2 � GPIO4 � ��������� GPIO3, ��:
//NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 20;	20 = 0001 0100b
//������ � ����� ����� �� ����� �����������, ��� ������ ����, ������� �� �������� � �����, ����� �� ���������.
//����� ������ �� ����� ��������� ������������ ����� �������� ����������� ��� ���� �����, ���� ��� ���������.

//#define VD1_ON NT_GPIOC->MASKLOWBYTE_bit[8].MASKLB = 0			//NT_GPIOC->DATA &= ~(1 << 3)
//#define VD1_OFF NT_GPIOC->MASKLOWBYTE_bit[8].MASKLB = (1 << 3)			//NT_GPIOC->DATA |= (1 << 3)
//
//#define VD2_ON NT_GPIOC->MASKLOWBYTE_bit[4].MASKLB = 0			//NT_GPIOC->DATA &= ~(1 << 2)
//#define VD2_OFF NT_GPIOC->MASKLOWBYTE_bit[4].MASKLB = (1 << 2)		//NT_GPIOC->DATA |= (1 << 2)
//
//#define VD3_ON NT_GPIOB->MASKLOWBYTE_bit[32].MASKLB = 0			//NT_GPIOB->DATA &= ~(1 << 5)
//#define VD3_OFF NT_GPIOB->MASKLOWBYTE_bit[32].MASKLB =  (1 << 5)		//NT_GPIOB->DATA |= (1 << 5)
//
//#define VD4_ON NT_GPIOB->MASKLOWBYTE_bit[64].MASKLB = 0			//NT_GPIOB->DATA &= ~(1 << 6)
//#define VD4_OFF NT_GPIOB->MASKLOWBYTE_bit[64].MASKLB = (1 << 6)		//NT_GPIOB->DATA |= (1 << 6)
//
//#define VD5_ON NT_GPIOB->MASKLOWBYTE_bit[128].MASKLB = 0		//NT_GPIOB->DATA &= ~(1 << 7)
//#define VD5_OFF NT_GPIOB->MASKLOWBYTE_bit[128].MASKLB = (1<<7)	//NT_GPIOB->DATA |= (1 << 7)

//#define VD1_ON NT_GPIOB->MASKHIGHBYTE_bit[1].MASKHB = 0			//NT_GPIOB->DATA &= ~(1 << 8)
//#define VD1_OFF NT_GPIOB->MASKHIGHBYTE_bit[1].MASKHB = 1		//NT_GPIOB->DATA |= (1 << 8)

#define VD1_ON NT_GPIOH->MASKLOWBYTE_bit[128].MASKLB = 0			//NT_GPIOB->DATA &= ~(1 << 8)
#define VD1_OFF NT_GPIOH->MASKLOWBYTE_bit[128].MASKLB = (1<<7)		//NT_GPIOB->DATA |= (1 << 8)

#define VD2_ON NT_GPIOH->MASKLOWBYTE_bit[1].MASKLB = 0			//NT_GPIOB->DATA &= ~(1 << 8)
#define VD2_OFF NT_GPIOH->MASKLOWBYTE_bit[1].MASKLB = 1		//NT_GPIOB->DATA |= (1 << 8)

#define LED_CMD_NO_CMD	0
#define LED_CMD_ON		1
#define LED_CMD_OFF		2
#define LED_CMD_TOGGLE	3
//������� ������������� ���������� ������� ���������������� ��� ���������� ������������
int LEDS_init(void)
{

}

//������� ������� ������������
int LEDS_set(int led_id, int timout)
{
//������
led_id=led_id&0x3;

leds.led[led_id].timeout=timout;
leds.led[led_id].counter=timout;
leds.led[led_id].mode=LED_CMD_ON;


}

//������� ������� ������������
int LEDS_toggle(int led_id, int timout)
{
//������
led_id=led_id&0x3;
if ((leds.led[led_id].mode==LED_CMD_TOGGLE)&&(leds.led[led_id].timeout==timout)) return 0;

leds.led[led_id].cmd=1;

leds.led[led_id].timeout=timout;
leds.led[led_id].counter=timout;

leds.led[led_id].mode=LED_CMD_TOGGLE;
}


//������� ������� ������������
void LEDS_update()
{int ii;
	//	static int timer;	//���������� �������
	//	static int LEDs;	//���������� ��������� �����������
	//������� 4 ������� ���������� ��
	for (ii=0;ii<4;ii++) {

		if (leds.led[ii].mode == LED_CMD_TOGGLE) {
			if (leds.led[ii].counter > 0)
				leds.led[ii].counter--;
			else {
				leds.led[ii].cmd = (~leds.led[ii].cmd) & 0x1;
				leds.led[ii].counter = leds.led[ii].timeout;
			}
		}
		if (leds.led[ii].mode == LED_CMD_ON) {

			if (leds.led[ii].counter > 0) {
				leds.led[ii].counter--;
			} else
				leds.led[ii].cmd = 0;

		}
	}


}






