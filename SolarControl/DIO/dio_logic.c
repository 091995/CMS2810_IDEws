#ifndef MODEL
#include "dio_func.h"
#endif

//ѕ–»ћ1. ѕравильно, вне зависимоcти от работы дискретного автомата 
//всегда иметь запись в журнале событий о том, что и как 
//подключено, поэтому перед расчетом дискретного автомата все состояния
//обязательно помещаются в журнал событий записи. ¬ системе этим занимается 
//драйвер ввода вывода ..........с 



void DIO_LOGIC_Init()
{
dio_logic.state=0;
dio_logic.state_prev=-1;

dcdc.state = 0;
dcdc.state_prev = -1;

dio_protect.init(&dio_protect);


cmd_logic.init();

sc_profile.init(&sc_profile);

diesel.init(&diesel);

vacuum.init(&vacuum);

inv.init(&inv);

aux_io.init();



fan_dctrl.init(&fan_dctrl);
fan_spec.init(&fan_spec);



}

extern Uint16 DebugW4;

void DIO_LOGIC_Calc()
{

	// calc equipment status ToDOo - move all aux equipment to some module, may be aux, or others
	//dio_equip._1ms_calc();

	//-------------------------------------------------------------------------------------------
	//Pass data to SC_PROFILE module
	//-------------------------------------------------------------------------------------------
	//sc_profile.in.inv_isla_mode = cmd_logic.cmd.cmd_inv_isla_mode; TODO - add isla mode selector here

	sc_profile.ms_calc(&sc_profile);



	// calc cmd and refs source
	cmd_logic.ms_calc();




	//TODO5 Uncomment after debug precharge state
	dcdc.Udc1=inv.in.DCS_Udc; //pass actual DC voltage to dcdc module. This will be send to DCDC control.

	//data to dcdc passed in DIO_LOGIC_CONNECTORS
	//here we have just calс
	dcdc.ms_calc(&dcdc);

	diesel.ms_calc(&diesel);

	vacuum.ms_calc(&vacuum);

	inv.ms_calc(&inv);

	//calc protections
	dio_protect.trip_reset=cmd_logic.cmd.cmd_trip_reset;
	dio_protect.ms_calc(&dio_protect);

	//independent on all commands if apl request protection with power off do
		if (inv.in.cmd_protect_pwm_off==1)
		{
			inv.out.cmd_DCS_stop=1;
			//only for P_GEN switch off K7 TODO5 - consider AR logic. No need for PRE cycle turning K7
			//TODO 207 - excluded A&D - after AR logic implemented only cmd_protect_pow_off turn of Q7
			//чтобы быть уверенным что защита фильтра работает (если конденстаор пробьет) нужно добавит в
			// u_protect слежение за слишком высоким RMS в течение 2 периодов сети и делать защиту IRMS_TR_MAX
			// Ёта защита вызовет cmd_protect_pow_off
			//if (inv.params.profile==DIO_LOGIC_INV_DCS_PROFILE_P_GEN) aux_K7.cmd_in=CMD_Q_OFF;
		}

		if (inv.in.cmd_protect_pow_off==1)
		{
			inv.out.cmd_DCS_stop=1;
			aux_K7.cmd_in=CMD_Q_OFF;
			aux_Q4.cmd_in=CMD_Q_OFF;
			//NOT - in DCDC fault state TODO5 aux_Q6.cmd_in=CMD_Q_OFF; //TODO2 added to protect dcdc connection
			//dcdc.ena=0; //TODO2 just for preliminary experience. Later logic to stop DCDC should be implemented
		}
//if  (DebugW4==0)
//	aux_Q6.cmd_in = CMD_Q_OFF;
//else aux_Q6.cmd_in = CMD_Q_ON;



	aux_io.calc() ;


	//calc analog controlled FANs
	//fan_actrl.calc(&fan_actrl);

	//cal digital controled FANs;
	fan_dctrl.calc(&fan_dctrl);
	fan_spec.hi=fan_dctrl.set_hi;
	fan_spec.lo=fan_dctrl.set_lo;
	fan_spec.calc(&fan_spec);
	//calc leds
	leds.update();



}


