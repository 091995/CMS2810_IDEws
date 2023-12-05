
#ifndef V_CURPAR_H
#define V_CURPAR_H

#include "filter.h"


    /*! \class TCurPar
      \brief Расчет наблюдаемых текущих параметров 

      Класс \a TCurPar, основанный на структуре SCurPar, содержит
      ряд разрозненных вычислений для отображения текущих параметров привода.
      Например, расчет действующих токов фаз, текущей мощности и т.п.
      */

//! см. TCurPar
struct SCurPar{

    long Pdc; // active power frough dc bus
    long Pac;
	long Qac;

    long Ia_rms;
    long Ib_rms;
    long Ic_rms;

    long Uab_rms;
    long Ubc_rms;
    long Uca_rms;

	long Udc_meas;
    long Idc_meas;

    long cos_fi;
    long S;
    long E_day;
    long operating_time;
    long E_total;
    long Freq;



   // TFilter fPower; //!< Фильтр мощности

    void (*init)(volatile struct SCurPar*);
    void (*calc)(volatile struct SCurPar*);
    void (*slow_calc)(volatile struct SCurPar*);
};

typedef volatile struct SCurPar TCurPar;


#define TCUR_PAR_DEFAULTS {0,0,0,\
						0,0,0,\
						0,0,0,\
						0,0,\
						0,0,0,0,0,0,\
						&CurPar_init, \
						&CurPar_fast_calc, \
						&CurPar_slow_calc, \
}


//! \memberof TCurPar
void CurPar_init(TCurPar*);
//! \memberof TCurPar
void CurPar_fast_calc(TCurPar*);
//! \memberof TCurPar
void CurPar_slow_calc(TCurPar*);




#endif


