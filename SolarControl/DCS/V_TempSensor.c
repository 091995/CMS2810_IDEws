

#ifndef MODEL
#include "DSP.h"
#include "V_TempSensor.h"
#include "V_IQmath.h"
#endif


//int16 NTC_T2V[16][2] = {\
//			  {-55, 3.91},\
//			  {-50, 5.53},\
//			  {-45,	7.84},\
//			  {-40,	11.03},\
//			  {-35,	15.41},\
//			  {-30,	21.37},\
//			  {-10,	73},\
//			  {10,	217},\
//			  {40,	751},\
//			  {65,	1550},\
//			  {85,	2170},\
//			  {110,	3030},\
//			  {135,	3480},\
//			  {155,	3740},\
//			  };

int16 NTC_T2V_5K[16][2] = {\
		{-55,	13.5},\
		{-40,	39.1},\
		{-30,	71.71},\
		{-20,	122},\
		{-10,	197.33},\
		{0,		303.1},\
		{10,	450},\
		{30,	877},\
		{40,	1160},\
		{60,	1810},\
		{85,	2600},\
		{110,	3200},\
		{125,	3450},\
		{126,	3500},\
		{127,	3600},\
		{128,	3700},\

};



int16 NTC_T2V_10K[16][2] = {\
			  {-55, 3.91},\
			  {-50, 5.53},\
			  {-45,	7.84},\
			  {-40,	11.03},\
			  {-35,	15.41},\
			  {-30,	21.37},\
			  {-10,	73},\
			  {10,	217},\
			  {40,	751},\
			  {65,	1550},\
			  {85,	2170},\
			  {110,	3030},\
			  {135,	3480},\
			  {155,	3740},\
			  {155,	3740},\
			  {155,	3740},\
			  };


//float NTC_T2V_6K8[16][2] = {\
//		{-55, 5.71},\
//		{-50, 8.28},\
//		{-30,32.7},\
//		{-10, 108.77},\
//		{5, 239.4},\
//		{25, 580},\
//		{40, 995},\
//		{55, 1520},\
//		{65, 1900},\
//		{85, 2600},\
//		{100, 3020},\
//		{115, 3430},\
//		{125, 3500},\
//		{125, 3500},\
//		{125, 3500},\
//		{125, 3500},\
//};
//
int16 (*NTC_T2V)[16][2];

void TTEMPSENSOR_NTC_SlowCalc(TTEMPSENSOR_NTC *p) {
volatile int left;
volatile int right;
volatile int node;

volatile float adc_mV;
volatile float dKM;

if (p->NTC10K) NTC_T2V=&NTC_T2V_10K;
else if (p->NTC5K) NTC_T2V=&NTC_T2V_5K;
else  NTC_T2V=&NTC_T2V_10K;

//check if circuit is no less then -40degree
if (p->adc_reg16<0x1f) { p->fail=1; p->T=0x7fff; return;} //return maximum pos value
else p->fail=0;



//scale to mV range 3.3V=12bit (ie 0xfff)
adc_mV=(float)p->adc_reg16*(3300.0/0xfff);

//table lookup by half-division algo
// ниже алгоритм бинарного поиска требуемого интервала
left=0;right=16-1;
		while(left<right-1)
		{
			node = (left+right)>>1;
			if(adc_mV>=(*NTC_T2V)[node][1]) left=node;
			else right=node;
		}
//		right = right;
		dKM=(adc_mV-(*NTC_T2V)[right-1][1])/((*NTC_T2V)[right][1]-(*NTC_T2V)[right-1][1]);
		//масштабирование
		p->T_fp_value=(*NTC_T2V)[right-1][0]+(((*NTC_T2V)[right][0]-(*NTC_T2V)[right-1][0])*dKM);

		p->T= (p->T_fp_value*16.0);// scale to IQ12.4 format

}

