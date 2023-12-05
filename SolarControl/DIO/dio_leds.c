/*
 * leds.c
 *
 *  Created on: 30 окт. 2018 г.
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

//Макросы для включения/выключения светодиодов на плате ControlCARD
//Можно использовать команды вида NT_GPIOC->DATA &= ~(1 << 2) и NT_GPIOC->DATA |= (1 << 2), но
//таким образом порты меняют состояние не сразу, а через 2 такта (это связано с синхронизацией), и, если
//подряд написать 2 строчки, например NT_GPIOC->DATA &= ~(1 << 2) и NT_GPIOC->DATA &= ~(1 << 3), то первая
//с большой вероятностью не сработает, так как доступ к биту осуществляется сначала чтением всего слова, изменением нужного
//бита и записью его назад. Но чтение из GPIO возвращает текущее состояние порта, и к моменту выполнения второй команды (второй строки Си)
//прочитанное состояние не будет содержать изменений, которые сделала первая команда, поэтому вторая команда затрет тот бит,
//который хотела выставить первая команда.
//При этом проблема проявляется только при включенной высокой оптимизации компилятора. Без оптимизации компилятор генерирует
//достаточно много ассемблерных команд между обращениями к GPIO и синхронизация успевает выполниться.

//Другой способ - обращение к GPIO по маске (см. документацию): MASKLOWBYTE - к младшему байту регистра, MASKHIGHBYTE - к старшему.
//Допустим, мы хотим выдать "1" на GPIO2, GPIO3 и GPIO4 порта C:
//0001 1100		маска, является индексом в массиве MASKLOWBYTE
//xxx1 11xx		записываемое значение: в нужных битах - единицы, в остальных - не важно, т.к. они не попадают в маску и не будут изменены
//NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 28;	так выглядит код команды, как вариант: NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 0xFF;
//если надо включить GPIO2 и GPIO4 и выключить GPIO3, то:
//NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 20;	20 = 0001 0100b
//Доступ к битам порта по маске гарантирует, что другие биты, которые не попадают в маску, будут не затронуты.
//Также доступ по маске позволяет одновременно одной командой переключить два бита порта, если это требуется.

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
//Функция инициализации дискретных выходов микроконтроллера для управления светодиодами
int LEDS_init(void)
{

}

//Функция мигания светодиодами
int LEDS_set(int led_id, int timout)
{
//защита
led_id=led_id&0x3;

leds.led[led_id].timeout=timout;
leds.led[led_id].counter=timout;
leds.led[led_id].mode=LED_CMD_ON;


}

//Функция мигания светодиодами
int LEDS_toggle(int led_id, int timout)
{
//защита
led_id=led_id&0x3;
if ((leds.led[led_id].mode==LED_CMD_TOGGLE)&&(leds.led[led_id].timeout==timout)) return 0;

leds.led[led_id].cmd=1;

leds.led[led_id].timeout=timout;
leds.led[led_id].counter=timout;

leds.led[led_id].mode=LED_CMD_TOGGLE;
}


//Функция мигания светодиодами
void LEDS_update()
{int ii;
	//	static int timer;	//переменная таймера
	//	static int LEDs;	//переменная состояния светодиодов
	//считаем 4 таймера независимо от
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






