

#ifndef _HAL_DRV_H
#define _HAL_DRV_H

#include "HAL_SPI_MCP3208.h"

extern HAL_SPI_MCP3208 mcp;

struct SHAL_DIO
{
	uint16_t rel_cmd1; //B6
	uint16_t rel_cmd2; //B15
	uint16_t rel_cmd3; //B4
	uint16_t rel_cmd4; //B5
	uint16_t FAN_spd_cmd;	//A10
	uint16_t FAN2_spd_cmd;  //G1

	uint16_t DO_3coil;   //E11  //for K91 control
	uint16_t DO_2coil;   //E15	//for K7 control

//	uint16_t DO_ext_adc_muxA; //SDA0
//	uint16_t DO_ext_adc_muxB; //SCL0

	uint16_t DO_LED1;  //on_board led
	uint16_t DO_LED2;

	uint16_t DO_EXT_LED1; //QEP_A
	uint16_t DO_EXT_LED2;  //QEP_B


	uint16_t DI_1; //E3
	uint16_t DI_2; //C6
	uint16_t DI_3; //E8
	uint16_t DI_4; //E9

	uint16_t DI_6;		//A15
	uint16_t DI_7;		//A14

	uint16_t i1_pow1; //
	uint16_t i1_pow2; //
	uint16_t i2_pow1; //
	uint16_t i2_pow2; //

	uint16_t DI_btn1;		//D10
	uint16_t DI_btn2;		//D11


};

typedef struct
{
Uint16 Udc_adc_reg;
Uint16 Idc_adc_reg;
Uint16 U1_BC_adc_reg;
Uint16 U1_AC_adc_reg;
Uint16 U1_NC_adc_reg;
Uint16 U2_BC_adc_reg;
Uint16 U2_AC_adc_reg;
Uint16 U2_NC_adc_reg;

Uint16 I2_C_adc_reg;
Uint16 I2_B_adc_reg;
Uint16 I2_A_adc_reg;

Uint16 I1_C_adc_reg;
Uint16 I1_B_adc_reg;
Uint16 I1_A_adc_reg;
Uint16 _0p75V_adc_reg;
Uint16 IREF_PWM_adc_reg;

} HAL_ADC_REGS;

struct SHAL_ADC
 {
	HAL_ADC_REGS regs;

//	int16 Ua_inv_gain;
//	int16 Ua_inv_offset;
//	int32 Ua_inv;
//	int16 Ua_invBuf[4];	//массив точек для усреднения
//	int16 Ub_inv_gain;
//	int16 Ub_inv_offset;
//	int32 Ub_inv;
//	int16 Ub_invBuf[4];	//массив точек для усреднения
//	int16 Uc_inv_gain;
//	int16 Uc_inv_offset;
//	int32 Uc_inv;
//	int16 Uc_invBuf[4];	//массив точек для усреднения
//
//	int16 Ua_tr_gain;
//	int16 Ua_tr_offset;
//	int32 Ua_tr;
//	int16 Ua_trBuf[4];	//массив точек для усреднения
//	int16 Ub_tr_gain;
//	int16 Ub_tr_offset;
//	int32 Ub_tr;
//	int16 Ub_trBuf[4];	//массив точек для усреднения
//	int16 Uc_tr_gain;
//	int16 Uc_tr_offset;
//	int32 Uc_tr;
//	int16 Uc_trBuf[4];	//массив точек для усреднения
//
//
//    int16 Ia_inv_gain;
//    int16 Ia_inv_offset;
//    int16 Ia_inv;
//    int32 Ia_invGainNom;
//   volatile int32 Ia_inv_temp;
//   // int16 Ia_invSampleLength;	//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Ia_invPointer;		//номер последней выборки
//	int16 Ia_invBuf[4];			//массив точек для усреднения
//
//    int16 Ib_inv_gain;
//    int16 Ib_inv_offset;
//    int32 Ib_inv;
//    int32 Ib_invGainNom;
//    int32 Ib_inv_temp;
//   // int16 Ib_invSampleLength;	//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Ib_invPointer;		//номер последней выборки
//	int16 Ib_invBuf[4];			//массив точек для усреднения
//
//    int16 Ic_inv_gain;
//    int16 Ic_inv_offset;
//    int32 Ic_inv;
//    int32 Ic_invGainNom;
//    int32 Ic_inv_temp;
//   // int16 Ic_invSampleLength;	//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Ic_invPointer;		//номер последней выборки
//	int16 Ic_invBuf[4];			//массив точек для усреднения
//
//    int16 Ia_tr_gain;
//    int16 Ia_tr_offset;
//    int32 Ia_tr;
//    int32 Ia_trGainNom;
//    int32 Ia_tr_temp;
//   // int16 Ia_trSampleLength;	//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Ia_trPointer;			//номер последней выборки
//	int16 Ia_trBuf[4];			//массив точек для усреднения
//
//	int16 Ib_tr_gain;
//    int16 Ib_tr_offset;
//    int32 Ib_tr;
//    int32 Ib_trGainNom;
//    int32 Ib_tr_temp;
//   // int16 Ib_trSampleLength;	//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Ib_trPointer;			//номер последней выборки
//	int16 Ib_trBuf[4];			//массив точек для усреднения
//
//	int16 Ic_tr_gain;
//    int16 Ic_tr_offset;
//    int32 Ic_tr;
//    int32 Ic_trGainNom;
//    int32 Ic_tr_temp;
//   // int16 Ic_trSampleLength;	//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Ic_trPointer;			//номер последней выборки
//	int16 Ic_trBuf[4];			//массив точек для усреднения
//
//    int16 Idc_meas_gain;
//    int16 Idc_meas_offset;
//    int32 Idc_meas;
//    int32 Idc_GainNom;
//    int16 Idc_temp;
//
//   // int16 Idc_SampleLength;		//длина выборки (кол-во точек на периоде ШИМ)
//	int16 Idc_Pointer;			//номер последней выборки
//	int16 Idc_Buf[4];			//массив точек для усреднения
//
//
//    int16 Udc_meas_gain;
//    int16 Udc_meas_offset;
//    int32 Udc_meas;
//    int32 UdcGainNom;
//    int16 Udc_temp;
//
//  //  int16 UdcSampleLength;		//длина выборки (кол-во точек на периоде ШИМ)
//	int16 UdcPointer;			//номер последней выборки
//	int16 UdcBuf[4];			//массив точек для усреднения
//
//	int16 SampleLength;
	uint16_t irq_id;
};


typedef struct SHAL_ADC HAL_ADC;
typedef struct SHAL_DIO HAL_DIO;


struct SHAL_ENERGY19
{
	HAL_ADC ADC;
	HAL_DIO DIO;
};


typedef struct SHAL_ENERGY19 HAL_ENERGY19;


//!Инициализатор по умолчанию.
//#define HAL_ADC_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,}

void HAL_init();		//global HW dependent initialization

void HAL_ms_update();		//

void HAL_DIO_init();
void HAL_ADC_init();


void HAL_DIO_read(HAL_DIO*p);
void HAL_DIO_write(HAL_DIO*p);

void HAL_ADC_calc(HAL_ADC*p);




#endif

/*@}*/




