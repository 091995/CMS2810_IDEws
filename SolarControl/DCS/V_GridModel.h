/*
 \file      V_GridModel.h
 \brief     Модуль сети
 \author    A&D
 \version   v 1.0 13/03/2019

 \defgroup  V_GridModel.h

 @{
*/


#ifndef V_GRID_MODEL_H
#define V_GRID_MODEL_H

#ifndef MODEL
#include "DSP.h"
#include "V_IQmath.h"
#endif

// faults
#define MODEL_WRONG_PARAMETERS 1
#define MODEL_MAX_CURRENT_FAULT 2
#define MODEL_MAX_SPEED_FAULT 3


#define MODEL_PI 3.1415926f
#define _1_DIV_2PI 0.15915494f

//структура с параметрами сет и преобразователя
struct Sgrid
{
	int cmpr0, cmpr1, cmpr2, cmpr3; 							//!< уставки сравнения ШИМ
	int tpr;													//!< период ШИМ
	float inv_tpr; 												//!< 1/период ШИМ
	int dt;														//!< величина мертвого времени в тактах
	int dta, dtb, dtc, dtf;										//!< влияние мертвого времени на потенциалы фаз
	float udc;													//!< напряжение ЗПТ
	float fia, fib, fic, fiav;									//!< потенциалы фаз и средней точки
	float ua, ub, uc;											//!< фазные напряжения
	float isa, isb, isc, isd, isq;								//!< фазные токи в осях альфа, бетта
	float usa, usb, usd, usq, urd, urq;							//!< напряжения в ортогональных осях
	float ird, irq, ira, irb;									//!< токи в ортогональных осях
	float omega,omega_rpm,torque;								//!< скорость (частота вращения), момент
	float torque_a, torque_b, torque_c;							//!< момент от каждой фазы (SRD)
	float j, inv_j;												//!< момент инерции и обратная величина
	float MechLoss;												//!< момент инерции
	float pp;													//!< число пар полюсов
	float inv_pp;												//!<  1/pp
	float tetaR;												//!< угол положения ротора, электрический
	float tetaRM;												//!< угол положения ротора, механический
	float cosTetaR, sinTetaR;									//!< cos и sin угла положения ротора
	float lm, lr, ls, lsd, lsq;									//!< индуктивности - взаимная, ротора, статора
	float lmin, lmax, dls;										//!< минимальная индуктивность (зуб-паз), максимальная индуктивность (зуб-зуб), амплитуда изменения индуктивности
	float inv_lmin;												//!<  1/lmin
	float l;													//!< текущая индуктивнасть
	float lp;													//!< индуктивнасть в окрестности текущего положения
	float ip, im;												//!< токи в окрестности текущего положения
	float wp, wm;												//!< магнитные энергии фазной катушки в окрестности текущего положения
	float isat;													//!< ток насыщения
	float rr, rs;												//!< сопротивление ротра и статора
	float ks, kr, km;											//!< коэффициенты индуктивностей
	float psa, psb, psc, psd, psq, prd, prq, pra, prb;			//!< потокосцепления статора и ротора в ортогональных осях или фазные
	float ppsa, ppsb, ppsd, ppsq, pprd, pprq, ppra, pprb;		//!< предикторы потокосцеплений в ортогональных осях
	float dpsa, dpsb, dpsd, dpsq, dprd, dprq;					//!< производные потокосцеплений в ортогональных осях
	int type;													//!< тип двигателя
	float t, t2;												//!< период дискретизации, половина периода дискретизации
	float speedK;												//!< коэффициент датчика скорости
	float iSenseK, ifSenseK, udSenseK, iSenseR, iSenseN;		//!< коэффициент датчика тока, сопротивление измерительного резистора ДТ, количество витков провода через ДТ
	float RatedPower;											//!< номинальная мощность (справочная величина, не используется в расчетах)
	float RatedSpeed;											//!< номинальная скорость (справочная величина, не используется в расчетах)
	float RatedCurrent;											//!< номинальный ток
	float RatedFluxCurrent;										//!< номинальный ток возбуждения
	int  iADCk, ifADCk;
	float QEPResolution;										//!< число меток ДПР
	float m;													//!< потокосцепление ротора синхронной машины
	float i_a, i_f, u_a, u_f, u_an;
	float r_a, r_f, r_ad, l_a, l_f;
	float _1_l_a, _1_l_f;
	float _1_lsd, _1_lsq;
	float dia, dif, dpa, dpf, pia, pif;
	float l_m,kf;												//!< коэффициент тока ОВ, потов ОВ
	int dcm_pm;													//!< флаг, что ДПТ с ПМ.
	int syncm_pm;												//!< флаг, что СД с ПМ.
	float isPhaseA,isPhaseB,isPhaseC,isPhaseD;							//!< ток фазы A,B,C
	float isPhaseA_prev,isPhaseB_prev,isPhaseC_prev;			//!< ток фазы A,B,C предыдущие значения
	int CurrentInvertedFlag;									//!< Флаг о том, что после выклчюения инвертора токи фаз один раз сменили свой знак
	float cos30;												//!< cos 30 градусов
	float pisa,dprb,disa;										//!< предиктор тока статора альфа, приращения потокосцепления ротора по оси бета, тока статора по оси альфа
	float ThetaMax, PsiMax, IMax;								//!< максимальный угол, поток и ток SRM (для интерполяции)
	float ThetaStep, PsiStep, IStep;							//!< шаг по углу, потоку и току SRM (для интерполяции)
	float ThetaStep_inv, PsiStep_inv, IStep_inv;				//!< обратные значения шага по углу, потоку и току SRM (для интерполяции)
	float power;												//!< Мощность на валу
	long iAtemp, iBtemp, iCtemp, iDtemp, Udc_temp, adcSpeedtemp;//!<Временные переменные для расчета модели
	float hallSensorOmegaPrev; 									//!< Для имитации измерения частоты вращения с датчика Холла
};
typedef volatile struct Sgrid Tgrid;


//Структура с данными модели. является интерфейсом между основной программой и моделью двигателя.
//Принимает уставки сравнения, период ШИМ и величину мертвого времени, момент нагрузки. Выдает показания датчиков.
struct SGridModel
{
	unsigned short MotorType;		    //!< Тип двигателя в модели (для симулятора)
	unsigned short MotorParametersNum;	//!< Номер параметров двигателя из таблицы
	unsigned short MotorParametersNumMax; // Максимальный возможный номер параметров из таблицы
	unsigned short cmpr0;				//!< уставки сравнения ШИМ
	unsigned short cmpr1;
	unsigned short cmpr2;
	unsigned short cmpr3;
	unsigned short InvertorEna;			//!< Флаг включения инвертора (если нет, то ключи не управляются)
	unsigned short tpr;					//!< период ШИМ
	unsigned short dt;					//!< мертвое время в тиках таймера
	unsigned short adc_code_Speed;		//!< измеренная скорость
	unsigned short qepCounter;			//!< положение с энкодера
	unsigned short hallSensor;			//!< Дискретный сигнал с датчика положения Холла (три первых бита)
	float hallSensorInterpAdd;  //!< Для имитации интерполяции датчика Холла
	float hallSensorOmega; 		//!< Для имитации измерения частоты вращения с датчика Холла
	unsigned short adc_code_iA;			//!< измеренные токи
	unsigned short adc_code_iB;
	unsigned short adc_code_iC;
	unsigned short adc_code_iD;
	unsigned short adc_code_Udc;		//!< измеренное значение напряжения звена постоянного тока (ЗПТ)
	unsigned short fault;				//!< ошибка модели
	float load;					//!< момент нагрузки
	float loadTmp;				//!< момент нагрузки временная переменная
	void (*Init)(volatile struct SGridModel*);        //!< Pointer to the init function
	void (*Execute)(volatile struct SGridModel*);      //!<  Pointer to the update function
	Tgrid gridInternals;		//!< Внутренние переменные для расчета модели двигателя
};

typedef volatile struct SGridModel TGridModel;

#define GRID_MODEL_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,GridModel_Init, GridModel_Execute}

void GridModel_Init(TGridModel*);
void GridModel_Execute(TGridModel*);



#endif

/*@}*/


