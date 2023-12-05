

#ifndef _SIM_H
#define _SIM_H

struct SSimulator
  {
	short dcs_sim_ena;
	short dio_sim_ena;
	long freq;
	long angle;

	long T;	//time constant L/R of phase reactor T=Ts/Tfiltra где - Tfiltra постоянная времени фильтра

	long Um1_tr;
    long Ua_tr;
    long Ub_tr;
    long Uc_tr;

    long Um1_f;
    long Ua_f;
    long Ub_f;
    long Uc_f;

    long Ia_tr;
    long Ib_tr;
    long Ic_tr;
    long Uab_tr;
    long Ubc_tr;
    long Uca_tr;


    long Ia_inv;
    long Ib_inv;
    long Ic_inv;

	long Udc;
	long Udc_ref;
	long Idc;
	long Idc_ref;
	long I_diesel;
	long event;
	long event_timeout;
    void (*init)(volatile struct SSimulator*);
    void (*fast_calc)(volatile struct SSimulator*);
 };

typedef volatile struct SSimulator TSim;

  //! инициализатор по-умолчанию
#define SIM_DEFAULTS {0,0,_IQ16(50),0,\
		  _IQ(0.001),\
  	  	  _IQ(1), 0,0,0, \
		  _IQ(1), 0,0,0, \
		  0,0,0,\
		  0,0,0,\
		  0,0,0,\
		  0,0,0,0,0,\
		  0,0,\
		  TSim_Init,\
		  TSim_FastCalc}

void TSim_Init(TSim*);
void TSim_FastCalc(TSim*);


#endif







