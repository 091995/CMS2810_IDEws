
#ifndef MODEL
#include "DSP.h"
#include "V_IQmath.h"
#include "main.h"
#endif

#include "DCS_base.h"


void DCS_Ctrl_Init(TDCS_Ctrl *p) {
	p->state_prev = -1;
	p->state = SM_DCS_CTRL_INIT;

	inv_params.U_nom = _IQ16(250*_sqrt2_sqrt3); // mag of phase voltage same as Um1
	inv_params.Udc_nom = _IQ16(700); // Udc_base is specialy as nominal of PV modules
	inv_params.I_nom = _IQ16(600*_sqrt_2);
	inv_params.P_nom = _IQ16(600.0*250*_sqrt_3*0.001); //in kW

	inv_params.Pdc_nom = _IQ16(700.0*600*_sqrt_2*0.001); //in kW 592KW

	inv_params.freq_nom=_IQ16(50);


	pid_ud.pid_out_max = _IQ(1.5);
	pid_ud.pid_out_min = -_IQ(1.5);
	pid_uq.pid_out_max = _IQ(1.5);
	pid_uq.pid_out_min = -_IQ(1.5);

	pid_ud.Kp_reg3=_IQ(0.05);
	pid_uq.Kp_reg3=_IQ(0.05);
	pid_ud.Ki_reg3=_IQ(0.02);
	pid_uq.Ki_reg3=_IQ(0.02);


	pid_id.pid_out_max = _IQ(1.5);
	pid_id.pid_out_min = -_IQ(1.5);

	pid_iq.pid_out_max = _IQ(1.5);
	pid_iq.pid_out_min = -_IQ(1.5);

	pid_id.Kp_reg3=_IQ(0.1);
	pid_iq.Kp_reg3=_IQ(0.1);
	pid_id.Ki_reg3=_IQ(0.02);
	pid_iq.Ki_reg3=_IQ(0.02);
	

	pid_Udc.Kp_reg3=_IQ(0.39);
	pid_Udc.Ki_reg3=_IQ(0.0017);//_IQ(0.015);
	pid_Udc.Kd_reg3=_IQ(0.0015);
	pid_Udc.pid_out_max = _IQ(0.8); //TODO4 do change for low limit for commisioning
	pid_Udc.pid_out_min = _IQ(0);


	mppt.init(&mppt);


	adc.init(&adc);
	pll.init(&pll);
	freqmeter.init(&freqmeter);

	rmp_pow.T=_IQ(1);

	dcs_ctrl.test_param2=0;//1000; //single period plus 1/4
	dcs_ctrl.test_param1=0;

}


void DCS_Ctrl_Slow_Calc(TDCS_Ctrl *p) {

	static int adc_slow_calc_counter=0;

	dcs_prot.slow_calc(&dcs_prot);//модуль защит
	rmp.slow_calc(&rmp); //пересчет интенсивности разгона из пользовтельской во внутреннее представление
	rmp_pow.slow_calc(&rmp_pow);
	pwm.slow_calc(&pwm); //фоновый обработчик модуля ШИМ (пересчет пользовательских заданий)

	//в модуле много работы с плавающей точкой поэтому считаем через 10 раз
	adc_slow_calc_counter++;
	if (adc_slow_calc_counter>10) {
	adc.slow_calc(&adc); //Фоновый обработчик АЦП
	adc_slow_calc_counter=0;
	}
	//TODO cur_par.slow_calc(&cur_par); //Расчет текущих показателей привода
	AutoOffset.slow_calc(&AutoOffset);


	//Пересчет коэффициентов для масштабирования токов и напряжений
	inv_params._1_Udc_nom = _IQdiv(_IQ16(1), inv_params.Udc_nom);
	inv_params._1_I_nom = _IQdiv(_IQ16(1), inv_params.I_nom);
	inv_params._1_U_nom = _IQdiv(_IQ16(1), inv_params.U_nom);
	inv_params._1_P_nom = _IQdiv(_IQ16(1), inv_params.P_nom);
	inv_params.U_nom_div_Udc_nom= _IQmpy(_IQ(_sqrt_3),(_IQmpy(inv_params.U_nom,inv_params._1_Udc_nom)<<8)); //move from IQ16 to IQ24 format fro using in pwm module


#ifndef MODEL
	temp_NTC10K.adc_reg16=adc.regs.T3_reg16 ;
	temp_NTC10K.slow_calc(&temp_NTC10K);
	adc.T3 =  temp_NTC10K.T;

	temp_NTC10K.adc_reg16=adc.regs.T4_reg16 ;
	temp_NTC10K.slow_calc(&temp_NTC10K);
	adc.T4 =  temp_NTC10K.T;
//TODO LAB_MODE
//	temp_NTC5K.adc_reg16=adc.regs.T1_inv1_reg16;
//	temp_NTC5K.slow_calc(&temp_NTC5K);
//	adc.T1_inv1 =  temp_NTC5K.T;
//
//	temp_NTC10K.adc_reg16=adc.regs.T2_inv1_reg16;
//	temp_NTC10K.slow_calc(&temp_NTC5K);
//	adc.T2_inv1 =  temp_NTC5K.T;
//
//	temp_NTC5K.adc_reg16=adc.regs.T3_inv1_reg16;
//	temp_NTC5K.slow_calc(&temp_NTC5K);
//	adc.T3_inv1 =  temp_NTC5K.T;

#ifndef LAB_MODE_GLOBAL_DEFINE
	temp_NTC5K.adc_reg16=adc.regs.T1_inv1_reg16;
	temp_NTC5K.slow_calc(&temp_NTC5K);
	adc.T1_inv1 =  temp_NTC5K.T;

	temp_NTC10K.adc_reg16=adc.regs.T2_inv1_reg16;
	temp_NTC10K.slow_calc(&temp_NTC5K);
	adc.T2_inv1 =  temp_NTC5K.T;

	temp_NTC5K.adc_reg16=adc.regs.T3_inv1_reg16;
	temp_NTC5K.slow_calc(&temp_NTC5K);
	adc.T3_inv1 =  temp_NTC5K.T;
#else
	adc.T1_inv1=20<<4;
	adc.T2_inv1=20<<4;
	adc.T3_inv1=20<<4;
#endif
#endif

}

//!Миллисекундный расчет

//! \memberof TSM_Ctrl
void DCS_Ctrl_ms_Calc(TDCS_Ctrl *p) {
	//adc.ms_calc(&adc); //АЦП
	//dcs_prot.ms_calc(&dcs_prot); //Защиты
	//AutoOffset.ms_calc(&AutoOffset); //авто смещение некоторых каналов АЦП

}


volatile int deb_irq_id[16];
volatile int _gammaA[16];
volatile int _gammaB[16];
volatile int _gammaC[16];
volatile int _sector[16];



//! \memberof TSM_Ctrl
void DCS_Ctrl_Fast_Calc(TDCS_Ctrl *p) {

	long sync_mag;
	static int16 _ctrl_mode_synced_P_gen=-1;
	static int16 _E;

#ifndef MODEL
//обрабатываем данные из АЦП - они пришли из HAL


	if (sim.dcs_sim_ena)
	{
		sim.fast_calc(&sim);
		adc.Ua_tr=sim.Ua_tr;
		adc.Ub_tr=sim.Ub_tr;
		adc.Uc_tr=sim.Uc_tr;
		adc.Uab_tr = sim.Uab_tr;
		adc.Ubc_tr = sim.Ubc_tr;
		adc.Uca_tr = sim.Uca_tr;

		adc.Ia_inv=sim.Ia_inv;
		adc.Ib_inv=sim.Ib_inv;
		adc.Ic_inv=sim.Ic_inv;

		adc.Ia_tr=sim.Ia_tr;
		adc.Ib_tr=sim.Ib_tr;
		adc.Ic_tr=sim.Ic_tr;


		adc.Udc=sim.Udc;
		adc.Idc = sim.Idc;
		adc.I_diesel = sim.I_diesel;

	}
	else
		adc.fast_calc(&adc);


#endif
	adc.fast_calc_rms(&adc);

//	adc.fUdc.input=adc.Udc;
//	adc.fUdc.calc(&adc.fUdc);
//
//	adc.fIdc.input=adc.Idc;
//	adc.fIdc.calc(&adc.fIdc);

	fmUdc.input=adc.Udc;
	fmUdc.calc(&fmUdc);

	fmIdc.input=adc.Idc;
	fmIdc.calc(&fmIdc);


//always pass Udc for pwm module
	pwm.Udc_meas=fmUdc.output;//adc.Udc;

	mppt.I=fmIdc.output;//adc.fIdc.output;
	mppt.V=fmUdc.output;//adc.fUdc.output;
	mppt.calc(&mppt);
	cur_par.Pdc=mppt.P;

//сначала считаем защиты
	dcs_prot.fast_calc(&dcs_prot); //Защиты


//всегда ищем синхронизацию и сетевое напряжение

	freqmeter.Ua		= pll.Ua_conv;
	freqmeter.Uc		= pll.Uc_conv;
	freqmeter.Fl_Us		= pll.Fl_Us;
freqmeter.calc(&freqmeter);

	pll.Ua				= adc.Ua_tr;
	pll.Ub				= adc.Ub_tr;
	pll.Uc				= adc.Uc_tr;
	pll.Udc				= 0;//p->adc->Udc;
	pll.Ua220			= 0;//p->adc->Ua220;
	pll.Ub220			= 0;//p->adc->Ub220;
	pll.Uc220			= 0;//p->adc->Uc220;
	pll.Ts				= freqmeter.Ts_out;
	pll.fs				= freqmeter.fs_out;
	pll.Il_Alfa			= 0;//p->adc->Il_Alfa;
	pll.Il_Beta			= 0;//p->adc->Il_Beta;
pll.calc(&pll);
pll.alpha-=_IQ(0.25); //из-за особенностей реализации фазных преобразований в PLL, переход из abc в dq сделан так, что Um1 сонаправен с осью q, поэтому корректируем добавляя 90
pll.alpha&=0xffffff;

//for generator mode alsways rotate wt with w

gen.calc(&gen);

//allways pass to pwm module actual Udc
//pwm.Udc_meas=adc.fUdc.output;

	p->out.Udc= adc.Udc;
	p->out.Urms=pll.Um1;
	p->out.freq=freqmeter.fs_out;

	//два тока фаз из АЦП в модуль фазных преобразований
	clarke.as = adc.Ia_tr;
	clarke.bs = adc.Ib_tr;
	clarke.calc(&clarke);

	//из фазных преобразований в координатные преобразования.
	park.ds = clarke.ds;
	park.qs = clarke.qs;
	park.ang = pll.alpha;
	park.calc(&park);


	adc.Id=park.de;
	adc.Iq=park.qe;

//если система находится в перееинициализации,
//то пропускаем контур управления if (sm_sys.state == SYS_INIT) {p->state=SM_CTRL_INIT; return;}

//формируем флаг готовности для работы в различных профилях

if (p->cmd_set_mode==SM_DCS_CTRL_RUN_DO_SYNC)
 p->out.ready = pll.Fl_Us; // сетевое напряжение есть.  TODO ready flag also depends on HW ready which is not considered here, requered correction
if (p->cmd_set_mode==SM_DCS_CTRL_RUN_SYNCED_P_GEN)
 p->out.ready = pll.Fl_Us; // сетевое напряжение есть.

if (p->cmd_stop == 1) p->state = SM_DCS_CTRL_STOP;

// если есть авария, то переходим в стоп. Ускорение на 1 такт.
// Иногда состояние защиты становится PROT_TRIP а битового сигнла нет, тогда на экране не понятно, почему не запускается система
// кроме того все счетчики пеерехода из ночного режима работают
if (dcs_prot.state == SM_DCS_PROT_TRIP)
	p->state = SM_DCS_CTRL_STOP;


//p->state=SM_DCS_CTRL_RUN_SYNCED_P_GEN;

if (p->state_prev != p->state) p->E = 1; else p->E = 0;
p->state_prev = p->state;


switch (p->state) {
case SM_DCS_CTRL_STOP:  //Состояние импульсы отключены
		if (p->E == 1) {
			//global_time.WtiteSPI_flag = 1;    //записать времЯ работы ToDo не забыть раскментировать
			//при переходе в стоп и работающем
			//осциллографе переводим его в режим
			//однократной записи, чтобы зафиксир. возможную аварию.
			if (dlog.StartBits & (1 << 8))    //Если пользователь задал этот бит
				dlog.set_mode(1, &dlog); //запускаем осциллограф по этому событию

			if (dcs_prot.state==SM_DCS_PROT_TRIP) //если мы перешли в стоп, а модуль защит в аварии
				if (dlog.mode_reset==2)  //и даталоггер крутился
					dlog.mode_reset=1;   //то остановим осц, пусть будет осца аварии

		}
		p->out.running=0;

		pwm.Off(&pwm);            //Выкл ШИМ


		dcs_ctrl.cmd_Udc_ctrl_ena=0;

		pwm.UalphaRef = 0;
		pwm.UbetaRef = 0;

		
		pid_id.reset(&pid_id);
		pid_iq.reset(&pid_iq);


		if (p->cmd_run==1)
		{
			p->out.running=1;
			if (p->cmd_set_mode==SM_DCS_CTRL_RUN_TEST)
				p->state=SM_DCS_CTRL_RUN_TEST;
			else

			p->state=SM_DCS_CTRL_RUN;
		}

		//mppt.ena=0;
		pid_Udc.pid_ref_reg3=adc.Udc;
		//mppt.D=mppt.V;
		pid_Udc.pid_fdb_reg3=mppt.D;


break;


case SM_DCS_CTRL_RUN:      //этот режим нужен на 1 такт, чтобы выбрать конкретный профиль работы.
		if (p->E == 1) {
			//inv_status.bit.running = 1;
			p->counter = 0;

			if (dlog.StartBits & (1 << 0))    //Если пользователь задал этот бит
				dlog.set_mode(1, &dlog); //запускаем осциллограф по этому событию
		}

		dcs_ctrl.cmd_Udc_ctrl_ena=1;

		p->counter++;

		p->state=SM_DCS_CTRL_STOP; //if no mode selected go STOP
		if (p->cmd_set_mode==SM_DCS_CTRL_RUN_DO_SYNC) 		p->state=SM_DCS_CTRL_RUN_DO_SYNC;
		if (p->cmd_set_mode==SM_DCS_CTRL_RUN_SYNCED_P_GEN)	p->state=SM_DCS_CTRL_RUN_SYNCED_P_GEN;
		if (p->cmd_set_mode==SM_DCS_CTRL_RUN_GENERATOR)		p->state=SM_DCS_CTRL_RUN_GENERATOR;

		break;

    case SM_DCS_CTRL_RUN_GENERATOR:
		if (p->E == 1) {
			p->counter=1;
			rmp.output=0;
			//pid_ud.reset(&pid_ud);
			//pid_uq.reset(&pid_uq);
			if (dlog.StartBits & (1 << 1))
				dlog.set_mode(1, &dlog);
			//if some voltage exist (due maybe back EMF of motor) and freq >0.8 and <1.2 adjust w_e
//			if ((pll.Um1>_IQ(0.4))&&(pll.w_e>_IQ(0.8))&&(pll.w_e<_IQ(1.2)))
//			{
//			gen.w_e=pll.w_e;
//
//			clarke.as = adc.Ua_inv;
//			clarke.bs = adc.Ub_inv;
//			clarke.calc(&clarke);
//
//			rmp.output=_IQ24mag(clarke.ds,clarke.qs);
//			gen.wt=_IQ24atan2PU(clarke.qs,clarke.ds); //TODO5 - check this should align d-axe with Um1
//
//			}
//			else
			{   //Start from 0
				rmp.output=0;
			}

		}


		//Turn PWM on with 2nd calc cycle
		if (p->counter<0x7fff) p->counter++;
		#ifndef MODEL
				if (((p->counter==3)||(p->counter==4))&&(HAL.ADC.irq_id==1)) pwm.On(&pwm);
		#else
				if (p->counter==3) pwm.On(&pwm);
		#endif

	if (dcs_ctrl.test_param2>0) // for time limited pulses test
			if (p->counter>dcs_ctrl.test_param2) {
			pwm.Off(&pwm);
			p->state=SM_DCS_CTRL_STOP;
		}



		if (p->cmd_stop==1) p->state=SM_DCS_CTRL_STOP;

		gen.Um1_ref=sim.Um1_tr;// _IQ(1);
		//задание требуемого выходного напряжения на фильтре на вход задатчика интенсивности
		rmp.input = gen.Um1_ref;
		rmp.calc(&rmp);//расчет задатчика
		//обратные фазные преобразования.
		ipark.de =  rmp.output;
		ipark.qe =  0;
		ipark.ang = gen.wt;
		ipark.calc(&ipark);

		//получившиеся задания напряжения по осям альфа и бета отправляем на модуль ШИМ
		pwm.UalphaRef = ipark.ds;
		pwm.UbetaRef = ipark.qs;
		pwm.update(&pwm);





		break;

	case SM_DCS_CTRL_RUN_DO_SYNC:  //Режим синхронизации с сетью CHECK NOTES ON THIS MODE
		/*! NOTES
		 * Filter capacitors are very sensitive to PWM , so i have to run very smooth sin wave and very slowly increase magnitude
		 * I run it in an very very slow PID setting. Ramp is faster then PID, but no other solution for today
		 */

		if (p->E == 1) {
			p->counter=1;
			rmp.output=0;
			pid_ud.reset(&pid_ud);
			pid_uq.reset(&pid_uq);
			if (dlog.StartBits & (1 << 1))
				dlog.set_mode(1, &dlog);


		}

		//Turn PWM on with 2nd calc cycle
		if (p->counter<0x7fff) p->counter++;
#ifndef MODEL
		if (((p->counter==3)||(p->counter==4))&&(HAL.ADC.irq_id==1)) pwm.On(&pwm);
#else
		if (p->counter==3) pwm.On(&pwm);
#endif

		if (dcs_ctrl.test_param2>0) // for time limited pulses test
				if (p->counter>dcs_ctrl.test_param2) {
				pwm.Off(&pwm);
				p->state=SM_DCS_CTRL_STOP;
			}

		clarke.as = adc.Ua_inv;
		clarke.bs = adc.Ub_inv;
		clarke.calc(&clarke);



		park.ds = clarke.ds;
		park.qs = clarke.qs;
		park.ang = pll.alpha;
		park.calc(&park);



		//задание требуемого выходного напряжения на фильтре на вход задатчика интенсивности
		rmp.input = pll.Um1;
		rmp.calc(&rmp);//расчет задатчика

		pid_ud.pid_ref_reg3 = rmp.output;
		pid_ud.pid_fdb_reg3 = park.de;
		pid_ud.calc(&pid_ud);

//		if (p->counter>(160*10))
//			pid_uq.pid_ref_reg3=_IQ(0.1); //TODO OK this is reactive power control. Just for testing
//		else
		pid_uq.pid_ref_reg3 = 0;
		pid_uq.pid_fdb_reg3 = park.qe;
		pid_uq.calc(&pid_uq);

//		sync_mag=_IQ24mag(park.de,park.qe); A&D TODO 200 это делал видимо Макс для проверки что выходное напряжение больше
//											определенного уровня. Это не работало т.к.
//		if(p->counter>4000)
//			if(sync_mag<_IQ(0.1))			в этой строке стояло сравнение с 0.1 без преведения к _IQ
//				dcs_prot.bit_fault1|=F_PROGRAM_10K;

		#ifndef MODEL
		if (p->counter<160*2) { //this for discharging DC volatage of FCB after previous pulses off
			pid_ud.reset(&pid_ud);
			pid_uq.reset(&pid_uq);
		}
#endif


		//обратные фазные преобразования.
		ipark.de =  pid_ud.pid_out_reg3;
		ipark.qe =  pid_uq.pid_out_reg3;
		ipark.ang = pll.alpha;
		ipark.calc(&ipark);

		//получившиеся задания напряжения по осям альфа и бета отправляем на модуль ШИМ
		pwm.UalphaRef = ipark.ds;//+adc.fIalpha_tr_dc.output;
		pwm.UbetaRef = ipark.qs;//+adc.fIbeta_tr_dc.output;
		pwm.update(&pwm);
		if (p->cmd_stop==1) p->state=SM_DCS_CTRL_STOP;
		if (p->cmd_set_mode==SM_DCS_CTRL_RUN_SYNCED_P_GEN) p->state=SM_DCS_CTRL_RUN_SYNCED_P_GEN;

		//mppt.ena=0;
		pid_Udc.pid_ref_reg3=adc.Udc;
	    pid_Udc.pid_fdb_reg3=mppt.D;

		break;



	case SM_DCS_CTRL_RUN_SYNCED_P_GEN:  //Режим частотно-токового управления - вращающийся вектор тока.
		if (p->E == 1) {
			p->counter=1;
			rmp_pow.output = 0;

			if (dlog.StartBits & (1 << 2))
				dlog.set_mode(1, &dlog);



			pid_Udc.reset(&pid_Udc);
			pid_iq.ui_reg3 = pid_ud.pid_out_reg3; 	//устанавливаем интегральные каналы равным последнему синхронизирующему напряжению
			pid_id.ui_reg3 = pid_uq.pid_out_reg3; 	//чтобы включение имульсов произошло без броска тока
													//сюда можно попасть без синхронизации, когда работает АПВ.
													//если сетевое нарпяжение измениться сильно по сравнению с последней синхронизацией,
													//то ругялторы могу не справится с броском тока
													//тогда снова будет АПВ. Как вычислить уставки регулятора для такого включения?
													// оставил эту задачу будущим поколениям )

			//mppt.ena=1; 							//TODO 201 Должно ли MPPT автоматически включатся или нужно его включать через профиль?
													//если режим работы с генератором, то включать MPPT не нужно
													//TODO 201 профиль должен контролиовать переход в состояние работа и управлять режимом MPPT
			//mppt.D_prev=mppt.D;	TODO 207 exluded это реализовано в MPPT
		}

		//Turn PWM on with 2nd calc cycle
		if (p->counter!=0) p->counter++;
		if (p->counter==3) pwm.On(&pwm);

		if (dcs_ctrl.test_param1>0) // for time limited pulses test
				if (p->counter>dcs_ctrl.test_param1) {
				pwm.Off(&pwm);
				p->state=SM_DCS_CTRL_STOP;
			}

//			//два тока фаз из АЦП в модуль фазных преобразований
//			clarke.as = adc.Ia_tr;
//			clarke.bs = adc.Ib_tr;
//			clarke.calc(&clarke);
//
//			//из фазных преобразований в координатные преобразования.
//			park.ds = clarke.ds;
//			park.qs = clarke.qs;
//			park.ang = pll.alpha;
//			park.calc(&park);
//
//
//			adc.Id=park.de;
//			adc.Iq=park.qe;

			//A&D update 12.01.2022
			rmp_pow.input=dcs_refs.P_ref; //TODO - Id=P/Um1  this is not considereed here
			rmp_pow.calc(&rmp_pow);
			//select configuration to operate
			if (dcs_ctrl.ctrl_mode_synced_P_gen!=_ctrl_mode_synced_P_gen) _E=1;else _E=0;
				_ctrl_mode_synced_P_gen=dcs_ctrl.ctrl_mode_synced_P_gen;

			switch (dcs_ctrl.ctrl_mode_synced_P_gen)
			{
			case 0: // main day mode = mppt.ena =1 pid_Udc
				if (_E==1) {pid_Udc.ui_reg3=0;mppt.ena=1;mppt.D=adc.Udc;mppt.D_prev=mppt.D;}//trick for pid_Udc 1st cycle

				pid_Udc.pid_ref_reg3=fmUdc.output;
				pid_Udc.pid_fdb_reg3=mppt.D;
				pid_Udc.pid_out_max = rmp_pow.output;//dcs_refs.P_ref;
				pid_Udc.calc(&pid_Udc);
				dcs_refs.Id_ref = pid_Udc.pid_out_reg3;

			break;

			case 1:// main evening mode	or night mode					//A&D update 10.12.2021
				if (_E==1) {mppt.ena=0;rmp_pow.output = 0;}
			//TODO 204 проситься сюда рещить вопрос
			//TODO 204 - решили вопрос сделали селектор режима управляемый из профиля

			dcs_refs.Id_ref = _IQdiv(rmp_pow.output,pll.Um1);//TODO - Id=P/Um1  this is not considereed here as Uabc is stable


			break;
			case 2:


			break;
			default:break;
			}


			//in generating mode limit power if DC voltage drops bellow some limit

			if ((fmUdc.output < inv.params.Udc_min_lim_power)&&(rmp_pow.output>0)) {
				dcs_refs.Id_ref = dcs_refs.Id_ref-_IQmpy(_IQ(10),(inv.params.Udc_min_lim_power-fmUdc.output ));
				if (dcs_refs.Id_ref<0) dcs_refs.Id_ref=0; //limit current to 0
				pid_Udc.ui_reg3=0; //hold pid_Udc integral at zero to get back to mppt mode
			}


			if ((fmUdc.output > inv.params.Udc_max_lim_power)&&(rmp_pow.output<0)) {
				dcs_refs.Id_ref = dcs_refs.Id_ref-_IQmpy(_IQ(10),(inv.params.Udc_max_lim_power-fmUdc.output ));
				if (dcs_refs.Id_ref>0) dcs_refs.Id_ref=0; //limit current to 0
				pid_Udc.ui_reg3=0; //hold pid_Udc integral at zero to get back to mppt mode
			}


			pid_id.pid_ref_reg3 = dcs_refs.Id_ref;


			pid_id.pid_fdb_reg3 = adc.Id;
			//if (p->counter<(160*4))
			pid_id.calc(&pid_id);


			pid_iq.pid_ref_reg3 = dcs_refs.Iq_ref;
			pid_iq.pid_fdb_reg3 = -adc.Iq;
			//if (p->counter<(160*4))
			pid_iq.calc(&pid_iq);

			//обратные фазные преобразования.
			ipark.de = pid_iq.pid_out_reg3;
			ipark.qe = pid_id.pid_out_reg3;
			ipark.ang = pll.alpha;
			ipark.calc(&ipark);

			//получившиеся задания напряжения по осям альфа и бета отправляем на модуль ШИМ
			pwm.UalphaRef = ipark.ds;//-adc.fIalpha_tr_dc.output;
			pwm.UbetaRef =  ipark.qs;//-adc.fIbeta_tr_dc.output;


			if (p->cmd_stop==1) p->state=SM_DCS_CTRL_STOP;


	break;


	case SM_DCS_CTRL_RUN_TEST:  // Testing mode , depends on  test mode and parameter may do pwm pulses or do nothing

	/*
	 * This testing mode used for PWM testing, if no PWM testing, then DCS did nothing and just wait
	 */
#ifndef MODEL
						switch (dcs_ctrl.test_param1) {
						case DCS_TEST_PARAM_TEST_PWM:
									if (p->E == 1) {
										p->counter=0;
										dcs_refs.Um1_ref=_IQ(0.25);
										ipark.ang=0;

									}

									//Turn PWM on with 2nd calc cycle
									if (p->counter<0x7fff) p->counter++;
									if (((p->counter==3)||(p->counter==4))&&(HAL.ADC.irq_id==1)) pwm.On(&pwm);

									deb_irq_id[p->counter&0xf]=HAL.ADC.irq_id;

									if (dcs_ctrl.test_param2>0) // for time limited pulses test
										if (p->counter>dcs_ctrl.test_param2) {
										pwm.Off(&pwm);
										p->state=SM_DCS_CTRL_STOP;
									}
									pwm.Udc_meas=_IQ(1);

									ipark.de = dcs_refs.Um1_ref;
									ipark.qe = 0;
									ipark.ang+=107647;//(long)_IQmpy(_IQ(1),_IQ(Td))*50;
									//if (ipark.ang>_IQ(1)) ipark.ang=0;



//									if (dcs_ctrl.test_param2==-1) ipark.ang=_IQ(0.01);
//									if (dcs_ctrl.test_param2==-2) ipark.ang=_IQ(0.33);
//									if (dcs_ctrl.test_param2==-3) ipark.ang=_IQ(0.67);

									//if (ipark.ang>(0x00ffffff-105000)) ipark.ang=0;
									ipark.ang&=0x00ffffff;

									ipark.calc(&ipark);

									pwm.UalphaRef = ipark.ds;
									pwm.UbetaRef = ipark.qs;

									break;
						default:
									pwm.Off(&pwm);
								break;
						}

#endif
		if (p->cmd_stop==1) p->state=SM_DCS_CTRL_STOP;
		break;

	default: {
		p->state=SM_DCS_CTRL_STOP;
		break;
	}
	}


//always update PWM in DCS_CTRL
pwm.update(&pwm);



}



/*@}*/

