/*!

*/


#ifndef V_ADC_H
#define V_ADC_H


#include "filter.h"
//#include "V_IQmath.h"

typedef struct {
int16 Ia_inv_reg16;
int16 Ib_inv_reg16;
int16 Ic_inv_reg16;

int16 Ia_tr_reg16;
int16 Ib_tr_reg16;
int16 Ic_tr_reg16;

int16 I_diesel_reg16;

int16 Uac_inv_reg16;
int16 Ubc_inv_reg16;
int16 Unc_inv_reg16;

int16 Uac_tr_reg16;
int16 Ubc_tr_reg16;
int16 Unc_tr_reg16;

Uint16 Udc_reg16;
Uint16 Idc_reg16;
Uint16 _075V_ref_reg16;
Uint16 IREF_PWM_adc_reg16;

//next is external
Uint16 T1_reg16;
Uint16 T2_reg16;
Uint16 T3_reg16;
Uint16 T4_reg16;

Uint16 T1_inv1_reg16;
Uint16 T2_inv1_reg16;
Uint16 T3_inv1_reg16;

Uint16 T1_inv2_reg16;
Uint16 T2_inv2_reg16;
Uint16 T3_inv2_reg16;

Uint16 U_fan_ref_reg16;
Uint16 U_fan_fdb_reg16;



} ADC_REG16;


//TODO 109 - Ќеобходимо добавить возможность измен€ть измер€емые значени€, а так же задаваемые величины(мощность, напр€жение и т.д.)
//дл€ корректировки заданных параметров с фактическими.
typedef struct
{
	int16 gain;
	int16 more;
	int16 less;
	int16 more_prev;
	int16 less_prev;

}
ADC_CALIBRATION;

typedef struct
{
	int32	_100to1V_gain;		//IQ16
	int32	_1Vto16bit_gain;	//IQ16
	int32	gain;				//IQ16
	int16	offset;				//IQ24
	int32	offset_32bit;				//IQ8.24
	int32 	value;
	ADC_CALIBRATION 	calibration;		//  100% - in range 90 - 110%
} ADC_PARAMS;
#define ADC_PARAMS_DEFAULT {_IQ16(100),_IQ24(10/0x7fff),0,0,0,0,{100,0,0,0,0}}


typedef struct
{
	int32 Ia_tr;
	int32 Ib_tr;
	int32 Ic_tr;
	int32 Ia_inv;
	int32 Ib_inv;
	int32 Ic_inv;

	int32 Uab_tr;
	int32 Ubc_tr;
	int32 Uca_tr;
	int32 Uab_inv;
	int32 Ubc_inv;
	int32 Uca_inv;
} RMS_VALUE;


struct SAdcDrv
  {
	ADC_PARAMS sUbc_inv;
	ADC_PARAMS sUac_inv;
	ADC_PARAMS sUnc_inv;
	ADC_PARAMS sUbc_tr;
	ADC_PARAMS sUac_tr;
	ADC_PARAMS sUnc_tr;
	ADC_PARAMS sIa_inv;
	ADC_PARAMS sIb_inv;
	ADC_PARAMS sIc_inv;
	ADC_PARAMS sIa_tr;
	ADC_PARAMS sIb_tr;
	ADC_PARAMS sIc_tr;

    ADC_PARAMS	sIdc;
    ADC_PARAMS	sUdc;

    ADC_PARAMS	sI_diesel;


	//TFilter fUdc;
	//TFilter fIdc;
	TFilter fI_diesel;
	TFilter fP_diesel;
	TFilter fIalpha_tr_dc;
	TFilter fIbeta_tr_dc;

	int16 T1;
	int16 T2;
	int16 T3;
	int16 T4;

	int16 T1_inv1;
	int16 T2_inv1;
	int16 T3_inv1;
	int16 T1_inv2;
	int16 T2_inv2;
	int16 T3_inv2;

	int32 Ia_inv;
	int32 Ib_inv;
	int32 Ic_inv;
	int32 Ia_tr;
	int32 Ib_tr;
	int32 Ic_tr;
	int32 Ua_inv;
	int32 Ub_inv;
	int32 Uc_inv;
	int32 Ua_tr;
	int32 Ub_tr;
	int32 Uc_tr;


	int32 Uab_inv;
	int32 Ubc_inv;
	int32 Uca_inv;
	int32 Uab_tr;
	int32 Ubc_tr;
	int32 Uca_tr;

	int32 I_diesel;

	int32	Idc;
	int32	Udc;
	int32 	Pdc;
	int32 	P_diesel;
	Uint32 	Edc_day;
	float  Edc_total;

	Uint16 I_REF_PWM_adc;
	Uint16 _0p75V_REF_adc;
	Uint16 debug;

	int32 U_fan_ref;
	int32 U_fan_fdb;
	Uint16 auto_offset_ena;

	int32 Id;
	int32 Iq;

	RMS_VALUE rms;
	ADC_REG16 regs;

	void (*init)(struct SAdcDrv *);
    void (*fast_calc)(struct SAdcDrv*);
    void (*fast_calc_rms) (struct SAdcDrv*);
    void (*ms_calc)(struct SAdcDrv*);   
    void (*slow_calc)(struct SAdcDrv*);
  };


  typedef struct SAdcDrv TAdcDrv;

//!»нициализатор по умолчанию.
#define ADC_DRV_DEFAULTS { ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
		ADC_PARAMS_DEFAULT,\
	FILTER_DEFAULTS,\
	FILTER_DEFAULTS,\
	FILTER_DEFAULTS,\
	FILTER_DEFAULTS,\
	0,0,0,0,\
	0,0,0,0,0,0,\
	0,0,0, 0,0,0, 0,0,0, 0,0,0,\
	0,0,0,0,0,0,\
	0,\
	0,0,0,0,0,\
	0,0,0,0,\
	0,0,0,\
	0,0,\
	{0},\
	{0},\
	AdcDrv_init,\
    AdcDrv_fast_calc,\
	AdcDrv_fast_calc_rms,\
    AdcDrv_ms_calc,\
    AdcDrv_slow_calc,\
	}


//! \memberof TAdcDrv
  void AdcDrv_init(TAdcDrv*);
//! \memberof TAdcDrv
  void AdcDrv_slow_calc(TAdcDrv*);
//! \memberof TAdcDrv
  void AdcDrv_fast_calc(TAdcDrv*);
  void AdcDrv_fast_calc_rms(TAdcDrv*);
  //
//! \memberof TAdcDrv
  void AdcDrv_ms_calc(TAdcDrv*);
  


#endif






