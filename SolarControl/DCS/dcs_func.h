/*
 * dio_func.h
 *
 *  Created on: 9 θών. 2019 γ.
 *      Author: admin
 */

#ifndef DCS_DIO_FUNC_H_
#define DCS_DIO_FUNC_H_

#include "V_IQmath.h"

#include "DCS/V_common.h"

#include "DCS/DCS_ctrl.h"
#include "DCS/u_Protect.h"

#include "DCS/clarke.h"
#include "DCS/iclarke.h"
#include "DCS/park.h"
#include "DCS/ipark.h"
#include "DCS/V_pid_reg3.h"
#include "DCS/V_MPPT.h"
#include "DCS/V_rmp_ctrl.h"
#include "DCS/V_adc.h"
#include "DCS/V_TempSensor.h"
#include "DCS/V_PWM_Module.h"
#include "DCS/V_CurPar.h"
#include "DCS/V_AutoOffset.h"
#include "DCS/V_GridModel.h"
#include "DCS/V_relay_reg.h"
#include "DCS/u_PLL.h"
#include "DCS/u_freqmeter.h"
#include "DCS/u_sim.h"
#include "DCS/mean_filter.h"

#include "DCS/u_generator.h"
#include "DCS/u_inv_sync.h"




#include "DCS/DCS_base.h"
//#include "DCS_ctrl.h"

#define DCS_PROFILE_DO_SYNC				1
#define DCS_PROFILE_SYNCED_P_GEN		2
#define DCS_PROFILE_GENERATOR			3







extern TClarke 		clarke;
extern TPark 		park;
extern TIPark 		ipark;
extern TPidReg3 	pid_id;
extern TPidReg3 	pid_iq;
extern TPidReg3 	pid_ud;
extern TPidReg3 	pid_uq;

extern TPidReg3 	pid_Udc;

extern TMeanFilter fmIdc;
extern TMeanFilter fmUdc;

extern PLL 			pll;
extern TMPPT 		mppt;
extern TDCS_Protect dcs_prot;
extern TRMPCtrl 	rmp;
extern TRMPCtrl 	rmp_pow;

extern TDCS_Ctrl 	dcs_ctrl;
extern TAdcDrv  	adc;
extern TPWM_Module pwm;
extern TCurPar cur_par;
extern TAutoOffset AutoOffset;
extern TGridModel model;
//extern TInvStatus inv_status;
extern TInvParams inv_params;
extern TRefs 	   dcs_refs;
extern TSysSwitches   sw;

extern FREQMETER freqmeter;
extern PLL pll;

extern TSim sim;
extern TTEMPSENSOR_NTC temp_NTC10K;
extern TTEMPSENSOR_NTC temp_NTC5K;

extern TGenerator gen;
extern TInvSync isync;
#endif /* DCS_DIO_FUNC_H_ */
