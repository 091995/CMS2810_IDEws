
#include "IQmathLib.h"          // библиотека IQmath
#include "V_PWM_Module.h"
#include "main.h"

#if defined(HW_MOTORCONTROLBOARD)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

//! Ограничения величины "мёртвого времени"
#if defined(HW_MOTORCONTROLBOARD)
//! для одноплатного инвертора нельзя меньше 3мкс, чтобы не сжечь
#define DEAD_BAND_MIN   _IQ(3)
#define DEAD_BAND_MAX   _IQ(10)
#else
#define DEAD_BAND_MIN   _IQ(0)
#define DEAD_BAND_MAX   _IQ(10)
#endif
*/
//! Инициализация

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {



}


//! Медленный расчет

//! Пересчитываются введенные пользователем величины
//! Величина мертвого времени, частота ШИМ и т.п.

//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *p) {

}


//! Функция включения ШИМ (включение инвертора)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {


}

//! Функция выключения ШИМ (выключение инвертора)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

}

void PWM_Module_PDP_trip_reset(TPWM_Module *p)
{

}


//! Нормирование входных величин.

//!Учитывает компенсацию напряжения при изменении Ud,
//!выполняет вписывание вектора в окружность, если требуется, и
//!выполняет смену базиса, относительно которого идет нормировка.
//! \memberof TPWM_Module
void PWM_Module_NormInput(TPWM_Module* p) {

}


//! Функция 6ти секторной векторной ШИМ

//! \memberof TPWM_Module
//volatile long TBCTR_reg;

//volatile int gam1[256];
//volatile int gam2[256];
//volatile int gam1_pos=0;
//volatile int gam2_pos=0;
//volatile int gam_state=0;




void PWM_Module_No_SV_Update(TPWM_Module *p) {

}



void PWM_Module_Aux_Update(TPWM_Module*p)
{


}



/*@}*/
