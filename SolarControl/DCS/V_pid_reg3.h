



#ifndef PID_REG3_H
#define PID_REG3_H

typedef struct SPidReg3 {
	long pid_ref_reg3; //!< Input: Reference input
	long pid_fdb_reg3; //!< Input: Feedback input
	long e_reg3; //!<Variable: Error
	long e_reg3Dz; //!<Variable: Error after dead zone

	long Kp_reg3; //!< Parameter: Proportional gain
	long up_reg3; //!< Variable: Proportional output
	long ui_reg3; //!< Variable: Integral output
	long ud_reg3; //!< Variable: Derivative output
	long uprsat_reg3; //!< Variable: Pre-saturated output
	long saterr_reg3Add; //!< Variable: Дополнительная ошибка насыщения от "верхнего уровня"

	long pid_out_max; //!< Parameter: Maximum output
	long pid_out_min; //!< Parameter: Minimum output
	long pid_out_reg3; //!< Output: PID output    */

	long saterr_reg3; //!< Variable: Saturated difference
	long Ki_reg3; //!< Parameter: Integral gain
	long Kc_reg3; //!< Parameter: Integral correction gain
	long Kd_reg3; //!< Parameter: Derivative gain
	long up1_reg3; //!< History: Previous proportional output
	long pid_out_test; //!< Output: PID output for test
	long DeadZone; //!< Мертвая зона
	long Kf_d; //!<Фильтр дифференциальной части
	long e_reg3_filterOut; //!<Выход фильтра дифференциальной части
	long DiffDelim; //!<Делитель для тактирования расчета производной
	long DiffCounter; //!<Счетчик для делителя
	int KdFilterInitFlag; //!<Флаг первого запуска для инициализации фильтра дифф. части
	void (*calc)(struct SPidReg3*); //!< Pointer to calculation function
	void (*reset)(struct SPidReg3*); //!< Pointer to reset function
} TPidReg3;

//! Инициализатор по-умолчанию
#define PIDREG3_DEFAULTS { 0,0,0,0, \
                           _IQ(0.1), \
                           0, 0, 0, 0,0, \
                           _IQ(1.2), \
                           _IQ(-1.2), \
						   0, \
                           0, \
                           _IQ(0.043), \
                           _IQ(0.5), \
                           _IQ(0), \
                           0,0,0,0,0,0,0,0,\
              			  pid_reg3_calc,\
						  pid_reg3_reset}

//! \memberof TPidReg3
void pid_reg3_calc(TPidReg3*);
void pid_reg3_reset(TPidReg3*);

#endif

/*@}*/
