//this file is for support MODEL
#ifdef MODEL
#include "../DCS/u_Protect.h"
#include "../DCS/DCS_Ctrl.h"
#include "../DCS/clarke.h"
#include "../DCS/park.h"
#include "../DCS/ipark.h"
#include "../DCS/V_pid_reg3.h"
#include "../DCS/V_MPPT.h"
#include "../DCS/V_rmp_ctrl.h"
#include "../DCS/V_adc.h"
#include "../DCS/V_PWM_Module.h"
#include "../DCS/V_CurPar.h"
#include "../DCS/V_AutoOffset.h"
#include "../DCS/V_GridModel.h"
#include "../DCS/V_relay_reg.h"
#include "../DCS/u_PLL.h"
#include "../DCS/u_freqmeter.h"
#include "../DCS/v_common.h"
#include "../DCS/filter.h"
#include "../DCS/mean_filter.h"

#include "../DCS/V_data_log_model.h"
#include "../DCS/V_TempSensor.h"


#define Td	(1.0/8000)

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
extern TInvStatus inv_status;
extern TInvParams inv_params;
extern TRefs refs;
//extern TSysSwitches   sw;

extern FREQMETER freqmeter;
extern PLL plc;

extern TMeanFilter fmIdc;
extern TMeanFilter fmUdc;


extern TTEMPSENSOR_NTC temp_NTC10K ;
extern TTEMPSENSOR_NTC temp_NTC5K ;


extern TDataLogModel dlog;

// this is C file to directly show compiler modules paths

#include "../DCS/u_Protect.c"
#include "../DCS/DCS_Ctrl.c"
#include "../DCS/clarke.c"
#include "../DCS/park.c"
#include "../DCS/ipark.c"
#include "../DCS/V_MPPT.c"
#include "../DCS/V_pid_reg3.c"
#include "../DCS/V_rmp_ctrl.c"
#include "../DCS/V_adc.c"
#include "../DCS/V_PWM_Module.c"
#include "../DCS/V_CurPar.c"
#include "../DCS/V_AutoOffset.c"
#include "../DCS/V_GridModel.c"
#include "../DCS/V_relay_reg.c"
#include "../DCS/u_PLL.c"
#include "../DCS/u_freqmeter.c"
#include "../DCS/filter.c"
#include "../DCS/mean_filter.c"
#include "../DCS/V_TempSensor.c"




#include "../DCS/V_data_log_model.c"
#endif

