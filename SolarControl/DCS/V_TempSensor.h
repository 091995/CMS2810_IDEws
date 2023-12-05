
#ifndef _V_TEMPSENSOR_NTC_H_
#define _V_TEMPSENSOR_NTC_H_



  struct STEMPSENSOR_NTC
  {
	Uint16 adc_reg16;
	int16 T;	//IQ12.4
	int fail;
	float T_fp_value;

	int NTC10K;
	int NTC5K;


	void (*slow_calc)(volatile struct STEMPSENSOR_NTC*);//указатель на функцию расчета
  };

  typedef volatile struct STEMPSENSOR_NTC TTEMPSENSOR_NTC;

  //! инициализатор по-умолчанию
#define TEMPSENSOR_NTC_10K_DEFAULTS {0,0,0,0, \
		1,0,\
		TTEMPSENSOR_NTC_SlowCalc}

  #define TEMPSENSOR_NTC_5K_DEFAULTS {0,0,0,0, \
		0,1,\
		TTEMPSENSOR_NTC_SlowCalc}

 //! \memberof TFilter
void TTEMPSENSOR_NTC_SlowCalc(TTEMPSENSOR_NTC*);




#endif

/*@}*/





