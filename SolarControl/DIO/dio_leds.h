/*
 * leds.h
 *
 *  Created on: 30 окт. 2018 г.
 *      Author: admin
 */

#ifndef _LEDS_H_
#define _LEDS_H_

typedef struct
{
int cmd;
int mode;
int counter;
int timeout;
} TSM_LED;


struct sLEDS	{
				TSM_LED led[4];
				int (*init)();
				int (*set)(int led_id, int timout_ms);
				int (*toggle)(int led_id, int timout_ms);
				void  (*update)();
				};

typedef struct sLEDS TLEDS;

  //! инициализатор по-умолчанию
#define TLEDS_DEFAULTS	{ {0},\
								LEDS_init,\
								LEDS_set,\
								LEDS_toggle,\
								LEDS_update}








int LEDS_init();
int LEDS_set(int led_id, int timout_ms);
int LEDS_toggle(int led_id, int timout_ms);
void LEDS_update();



//extern TLEDS leds;
#endif /* INCLUDE_LEDS_H_ */
