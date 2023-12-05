/*!
     Copyright 2023 ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_PWM_Module.h
 \brief     Модуль реализации векторной ШИМ (см. TPWM_Module)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru

 \defgroup  V_PWM_Module Модуль реализации векторной ШИМ (см. TPWM_Module)
 @{*/

#ifndef _V_PWM_Module_
#define _V_PWM_Module_

#ifdef __cplusplus
extern "C"
{
#endif

//#include "filter.h"
#include "f28xbmsk.h"
#include "DSP28_Device.h"

/*----------------------------------------------------------------------------
Initialization constant for the F28X Timer TxCON for PWM Generation.
Sets up the timer to run free upon emulation suspend, continuous up-down mode
prescaler 1, timer enabled.
----------------------------------------------------------------------------*/


#define _1_SQRT3 _IQ(0.5773503)
#define _2_SQRT3 _IQ(1.1547005)

//0x0000 обЯзательно так как если нажать не вовремЯ стоп то сгорит ключ
#define PWM_INIT_STATE  (0x0000+\
                       TIMER_CONT_UPDN + \
                       TIMER_CLK_PRESCALE_X_1 + \
                       TIMER_ENABLE_BY_OWN    + \
                       TIMER_ENABLE + \
                       TIMER_ENABLE_COMPARE \
                      )

/*----------------------------------------------------------------------------
Initialization constant for the F28X ACTRx register for PWM Generation.
Sets up PWM polarities.
----------------------------------------------------------------------------*/
#define PWM_ACTR_INIT_STATE ( COMPARE1_AH + \
                            COMPARE2_AL + \
                            COMPARE3_AH + \
                            COMPARE4_AL + \
                            COMPARE5_AH + \
                            COMPARE6_AL )


/*----------------------------------------------------------------------------
Initialization constant for the F28X DBTCONx register for PWM Generation.
Sets up the dead band for PWM and sets up dead band values.
----------------------------------------------------------------------------*/
//DBT_VAL_10*DBTPS_X32=320; 150000000/2=75000000; DB=1/(75000000/320.)=4.2e-6
#define PWM_DBTCON_INIT_STATE ( DBT_VAL_10 +  \
                              EDBT3_EN   +  \
                              EDBT2_EN   +  \
                              EDBT1_EN   +  \
                              DBTPS_X32 )

//! Ограничения частоты ШИМ (кГц) min
#define PWM_FREQ_MIN    _IQ10(2)
//! Ограничения частоты ШИМ (кГц) max
#define PWM_FREQ_MAX    _IQ10(100.0)

//!Векторная 6-ти секторная ШИМ
#define PWM_TYPE_6SECT_NO_SV    0
//!Синусоидальная ШИМ
#define PWM_TYPE_SIN_PWM        1
//!Векторная 12-ти секторная ШИМ
#define PWM_TYPE_12SECT_NO_SV   2
//!ШИМ методом вычисления фазных потенциалов
#define PWM_TYPE_FLY_12SECT     3
//!ШИМ для управления ДПТ
#define PWM_TYPE_DC_DRIVE       4
//!ШИМ для управления SRM
#define PWM_TYPE_SRD            5


//! Ограничения величины "минимальной скважности", мкс, min
#define GAMMA_LIMIT_MIN _IQ(0)
//! Ограничения величины "минимальной скважности", мкс, max
#define GAMMA_LIMIT_MAX _IQ(10)

// Константы загрузки регистров AQCTL# и AQCSFRC (ePWM)
// (определяют настройку событий для выходов ШИМ)
#define AQ_EPWM_DISABLE 0x0000                          //!< все события запрещены

//! Флаг разрешения внутренней привязки ШИМ-выходов
#define ENABLE_PULLUP   0

//!что делать при аппаратной аварии с ножками
#define TZ_STATE  TZ_FORCE_LO

/*! \class TPWM_Module
 \brief Модуль реализации ШИМ

 Класс \a TPWM_Module, основанный на структуре SPWM_Module, реализует
 векторную и скалярную широтно-импульсную модуляцию для управления
 шестиключевым инвертором. Имеет настройки мертвого времени,
 частоты, коррекцию в зависимости от напряжения ЗПТ,
 компенсацию мертвого времени.
 Задание напряжения происходит по двум перпендикулярным осям альфа и бетта.
 При этом ось альфа сонаправлена с осью А трехфазной системы координат. Для задания нового напряжения нужно
 поместить задание в UalphaRef, UbetaRef и вызвать update. В зависимости от того,
 какой тип ШИМ выбран в настройках (настраивается пользователем в переменной PWM_type),
 функция PWM_Module_Update вызовет нужную функцию, реализующую требуемый тип ШИМ.
 В результате этого на трех фазах инвертора в среднем за период ШИМ будет реализован
 такой вектор напряжения, который задан в UalphaRef, UbetaRef. Чтобы создать переменное
 синусоидальное напряжение, требуется вращать вектор задания внешней по отношению к модулю ШИМ программой.
 */

//! см. TPWM_Module
struct SPWM_Module {
    int16 Enabled; //!< Флаг для чтения - включен ШИМ или выключен.
    int32 UalphaRef; //!<Задание по оси асьфа (задается)
    int32 UbetaRef; //!<Задание по оси бетта (задается)
    int32 Udc_meas; // для корректировки по напряжению ЗПТ

    int32 UPhARef; //!<Задание по фазе A (задается)
    int32 UPhBRef; //!<Задание по фазе B (задается)
    int32 UPhCRef; //!<Задание по фазе c (задается)

    int32 k_pwm; //!< Период таймера ШИМ, для чтения.
    int32 U_mag; //!< Текущая амплитуда напряжения, для чтения.
    int32 U_lim; //!< Ограничение вектора напряжения, задается

    int32 GammaA; //!< Скважность фазы А в размерности таймера ШИМ, для чтения.
    int32 GammaB; //!< Скважность фазы B в размерности таймера ШИМ, для чтения.
    int32 GammaC; //!< Скважность фазы C в размерности таймера ШИМ, для чтения.

    int16 PWM_type; //!< Тип ШИМ. Принимает значения констант с префиквом PWM_TYPE_. Задается.
    int16 PWM_typeOld; //!< Предыдущее значения типа ШИМ, служебная переменная.
    int16 sector; //!< Текущий сектор в векторном типе ШИМ. Для чтения.

    int32 UalphaNorm; //!< Нормированное задание, служебная переменная.
    int32 UbetaNorm; //!< Нормированное задание, служебная переменная.
    int32 UdCorTmp; //!<Служебная переменная для корректировки выходного напряжения в зависимости от напряжения ЗПТ
    int32 UdCompK; //!< Коэффициент корректировки выходного напряжения инвертора в зависимости от изменения напряжения ЗПТ от номинального. Задается.
    int32 UdCompEnable; //!< Разрешение корректировки выходного напряжения инвертора в зависимости от изменения напряжения ЗПТ от номинального. Задается.
    int16 ULimitation; //!< флаг о том, что идет ограничение напряжения - выходное напряжение меньше заданного. Для чтения.
    _iq Frequency; //!< Частота ШИМ в кГц. Формат 22.10! Задается.
    _iq FreqPrev; //!< Предудущая частота ШИМ, служебная переменная.
    int32 DeadBand; //!< величина "мёртвого времени", мкс, задается.
    int32 MinGammaLimit; //!< минимальная скважность на ключе, задается.
    int PDP_Fault; //!< Флаг о том, что моудлем ШИМ зафиксирована аппаратная авария от инвертора. Для чтения. По ней необходима реакция модуля защит!
    int ChargingMode; //!< Режем заряда будстрепных конденсаторов. Должен выставляться в еденицу на время 2-10 мс внешней программой перед запуском ШИМ.
    int PDP_inv1;
    int PDP_inv_ext_lost;
    int PDP_pulses_block_Imax;
    volatile struct EVA_REGS *EvXRegs;
    void (*init)(volatile struct SPWM_Module*); /* Pointer to the init function               */
    void (*update)(volatile struct SPWM_Module*); /* Pointer to the update function             */
    void (*slow_calc)(volatile struct SPWM_Module*);
    void (*On)(volatile struct SPWM_Module*); //!< процедура включения (разрешения) ШИМ-выходов
    void (*Off)(volatile struct SPWM_Module*); //!<  процедура отключения (запрещения) ШИМ-выходов
};

typedef volatile struct SPWM_Module TPWM_Module;

//! Инициализатор по-умолчанию.
#define PWM_Module_DEFAULTS  {\
    0,0,0,0, \
    0,0,0, \
    0, \
    0, \
    _IQ(0.866),0, \
    0,0,\
    0,0,\
    0,\
    0,0,0,0,0,0,0x1400,0,0,0,0,0,0,0,0,\
    &EvaRegs,\
    PWM_Module_Init,  \
    PWM_Module_Update, \
    PWM_Module_SlowCalc, \
    PWM_Module_On, \
    PWM_Module_Off, \
  }

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_Update(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *);
//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *);

//векторные функции из библиотеки
void PWM_Module_No_SV_Update(TPWM_Module *);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/

