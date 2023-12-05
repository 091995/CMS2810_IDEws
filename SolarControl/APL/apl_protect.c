#include "apl_func.h"


//prototype
void AR_calc(APL_PROTECT_AR*p);


void APL_PROTECT_Init()
{
int ii;


//apl_protect.AR1.ena=0; //to restore saved
apl_protect.AR1.ready_time=2000; //2s
apl_protect.AR1.acting_time_pre=20; //20 ms

apl_protect.AR1.acting_time1=400; //400ms
apl_protect.AR1.acting_time2=4000; //4s
apl_protect.AR1.acting_time3=9000; //9sec


apl_protect.AR1.AR_acting = 0;

//DR 21_06_2016 b's sometimes after reboot AR.trip_reset stuck in non0 forawhile
apl_protect.AR1.trip_reset=0;


apl_protect.AR1.state = 0;

}
 
#pragma CODE_SECTION(APL_PROTECT_Calc,"FastRunFunc");

void APL_PROTECT_Calc()
{
int ii;

for (ii=0;ii<2;ii++) {
	// считываем защиты от модулей
	apl_protect.masked_word[ii] = (*apl_protect.p_prot_word[ii]);
	// считываем защиты с маской на отключение головного автомата
	apl_protect.masked_off_word[ii] = (*apl_protect.p_prot_off_word[ii]);
	// ћаски на јѕ¬
	apl_protect.AR_word[ii] = (apl_protect.masked_word[ii]&apl_protect.mask_apv_word[ii]);
}

//--------------------------------------------------------------------------------------------------
																				//APL for STATCOM #1
if (apl_protect.state_prev1!=apl_protect.state1) apl_protect.E1=1;
else apl_protect.E1=0;
apl_protect.state_prev1=apl_protect.state1;

switch (apl_protect.state1)
{
case SM_PROTECT_INIT:  
//ѕервое состояние после запуска программы.  
	if (apl_protect.E1==1) 
	{
    apl_protect.counter1=0;
    //apl_protect.AR1.trip_reset=1;
	}

	apl_protect.counter1++;
	if (apl_protect.counter1>100)
	apl_protect.state1 = SM_PROTECT_NO_TRIP;

	break;

case SM_PROTECT_NO_TRIP:  
	if (apl_protect.E1==1){
    	apl_protect.counter1=0;
	}

	//сканируем на наличие защит, если есть разрешенная 
	//масками авария то авария
	if ((apl_protect.masked_word[0]!=0)||\
			(apl_protect.masked_word[1]!=0))
	{
	apl_protect.state1=SM_PROTECT_TRIP;
	apl_protect.flag_protect1=1;
	}

	break;

case SM_PROTECT_TRIP:  
	if (apl_protect.E1==1){
	    apl_protect.counter1=0;
	}

	if ((apl_protect.masked_word[0]!=0)||\
			(apl_protect.masked_word[1]!=0))
	apl_protect.flag_protect1=1;
	else
	apl_protect.flag_protect1=0;

	
// ќтключение головного автомата
	if ((apl_protect.masked_off_word[0]==0)&&\
		(apl_protect.masked_off_word[1]==0))
	apl_protect.flag_protect1_Q_off=0;
	else
	apl_protect.flag_protect1_Q_off=1;

	if ((apl_protect.flag_protect1_Q_off==0)&&\
			(apl_protect.flag_protect1==0))
		apl_protect.state1=SM_PROTECT_NO_TRIP;

	//ждем сброса защит
	if (apl_protect.cmd_trip_reset1==1)
	apl_protect.state1=SM_PROTECT_TRIP_RESET;
	break;



case SM_PROTECT_TRIP_RESET:  
	if (apl_protect.E1==1)  
	{
		for (ii=0;ii<2;ii++) *apl_protect.p_prot_word[ii]=0;
	    apl_protect.counter1=0;
	}
    apl_protect.counter1++;
	if (apl_protect.counter1==3){
		apl_protect.state1=SM_PROTECT_NO_TRIP;
		apl_protect.flag_protect1=0;
		for (ii=0;ii<2;ii++){
			if ((apl_protect.masked_word[ii])!=0) {
				apl_protect.flag_protect1=1;}
		}
	}
	apl_protect.flag_protect1_Q_off=0;
	break;

default: break; 

} //end switch
//--------------------------------------------------------------------------------------------------




} 




 

void APL_PROTECT_ms_Calc() {
int ii;

apl_protect.AR1.AR_word[0]=apl_protect.AR_word[0];
apl_protect.AR1.AR_word[1]=apl_protect.AR_word[1];

apl_protect.AR1.in_trip_reset=apl_protect.cmd_trip_reset1;

apl_protect.AR1.flag_protect=apl_protect.flag_protect1;
apl_protect.AR1.flag_protect_Q_off=apl_protect.flag_protect1_Q_off;
apl_protect.AR1.ctrl_status=apl_protect.dcs_ctrl_running;


AR_calc(&apl_protect.AR1);

}

void AR_calc(APL_PROTECT_AR*p) {

static int flag_protect_AR;
//NOTE - this is correct  bit is 0 for AR acting
	//BUT not good for all logic. flag_protect_AR shuld be 1 only if selected protections acting
if ((apl_protect.masked_word[0]!=0)||(apl_protect.masked_word[1]!=0))
	flag_protect_AR = ((p->AR_word[0]==0)&&(p->AR_word[1]==0));
else
	flag_protect_AR=0; //i.e. no any protection;

//	p->AR_acting=0; //A&D 4_09_2015 before all set AR_acting=0. See changes in wait state

if (p->ena==0)
{
	p->pulses_on=0;
	p->state=AR_STATE_INIT;
	p->trip_reset=0;
	p->AR_acting=0;

}else 
{
if ((p->flag_protect_Q_off==1)||(p->in_cmd_stop==1)) { //DR 21_06_2016 sometimes trip_reset latch to 1 forawhile
	p->pulses_on=0;
	p->trip_reset=0;
	//p->AR_acting=0;
	p->state=AR_STATE_STOP;
	return; //not to proceed next. Or loop in AR forever. Next ctrl_status==0 and this stops AR
}

if (p->state!=p->state_prev) p->E=1; else p->E=0;
p->state_prev=p->state;

switch (p->state) {
case AR_STATE_INIT:
	if (p->E==1) { p->counter=0; }
	p->state = AR_STATE_STOP;
	
	break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
case AR_STATE_STOP:
	if (p->E==1) {p->counter=0;}

 	if (p->ctrl_status==1) //only when ctlr is running goes to WAIT_PROTECT_PRE
	p->state = AR_STATE_WAIT_PROTECT_PRE;

	break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
case AR_STATE_WAIT_PROTECT_PRE:  
	if (p->E==1){ p->counter=0;}


	p->AR_acting = 0;
	// ==0 b's AR acting only when protect under mask
	
	if (p->ctrl_status==0) { // if pulses stops
    	p->counter++;	
		if (p->counter>2) { // wait 2ms and go AR or STOP depends on flag_protect_AR
		if (flag_protect_AR==1){
			//wait 20ms time so over protections becom active 
		   	if (p->acting_time_pre==0) p->state=AR_STATE_WAIT_TIME1; //to disable PRE set pre time to zero in settings
			else if (p->counter>p->acting_time_pre) p->state=AR_STATE_TRIP_RESET_PRE; 
			}
			else p->state = AR_STATE_STOP;
		}
	}
	break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
case AR_STATE_TRIP_RESET_PRE:  
	if (p->E==1){
	p->counter=0;
	p->trip_reset=1;
	}
	//give 2 ms pulse for trip_reset
	p->counter++;
	if (p->counter==2) p->trip_reset=0;
	
	//check no protect on 4 ms
	if (p->counter==4){
		if (p->flag_protect==0)
		p->state=AR_STATE_PULSES_ON_PRE;  // go to pulse ena
		else
		p->state=AR_STATE_WAIT_TIME1;	// GO to time1 b's cant reset protect
	}
	break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
case AR_STATE_PULSES_ON_PRE:  
	if (p->E==1){
	p->counter=0;
	p->pulses_on=1;
	p->AR_acting=0; // DO NOT SHOW PRE_AR were acting
	}
	p->counter++;
	
	if (p->counter==2)	//wait 1 ms
		p->pulses_on=0;

 //wait ready_time (apprx 2secs)
if (p->counter>p->ready_time) p->state=AR_STATE_WAIT_PROTECT_PRE; 
		
if (flag_protect_AR==1)
		p->state=AR_STATE_WAIT_TIME1;	// GO to time1
		//p->state=AR_STATE_FAIL;// TODO 5 - one cycle AR for debug only
break;

/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 1*/
case AR_STATE_WAIT_TIME1:  
	if (p->E==1){ p->counter=0;}
	p->counter++;


	if (p->counter>p->acting_time1) {
	if (flag_protect_AR==1) p->state=AR_STATE_TRIP_RESET1;
    else p->state=AR_STATE_FAIL;
	}

break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 1*/

case AR_STATE_TRIP_RESET1:  
	if (p->E==1){p->counter=0;p->trip_reset=1;}
	p->counter++;
	if (p->counter==2) p->trip_reset=0;
	
	if (p->counter==4){ //check no protect on 4 ms
		if (p->flag_protect==0) p->state=AR_STATE_PULSES_ON1;  // go to pulse ena
		else p->state=AR_STATE_WAIT_TIME2;	// GO to time2
	}
break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 1*/
case AR_STATE_PULSES_ON1:  
	if (p->E==1){ p->counter=0;p->pulses_on=1;p->AR_acting=1;}
	p->counter++;
	if (p->counter==2)	p->pulses_on=0;
	
	if (p->counter>p->ready_time) p->state=AR_STATE_WAIT_PROTECT_PRE;  // go to AR_PRE ready
	if (flag_protect_AR==1) p->state=AR_STATE_WAIT_TIME2;	// GO to time 2	 
break;


/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 2*/
case AR_STATE_WAIT_TIME2:  
	if (p->E==1){ p->counter=0;}
	p->counter++;


	if (p->counter>p->acting_time2) {
	if(flag_protect_AR==1) p->state=AR_STATE_TRIP_RESET2;
    else p->state=AR_STATE_FAIL;
	}


break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 2*/

case AR_STATE_TRIP_RESET2:  
	if (p->E==1){p->counter=0;p->trip_reset=1;}
	p->counter++;
	if (p->counter==2) p->trip_reset=0;
	
	if (p->counter==4){ //check no protect on 4 ms
		if (p->flag_protect==0) p->state=AR_STATE_PULSES_ON2;  // go to pulse ena
		else p->state=AR_STATE_WAIT_TIME3;	// GO to time23
	}
break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 2*/
case AR_STATE_PULSES_ON2:  
	if (p->E==1){ p->counter=0;p->pulses_on=1;p->AR_acting=1;}
	p->counter++;
	if (p->counter==2)	p->pulses_on=0;
	
	if (p->counter>p->ready_time) p->state=AR_STATE_WAIT_PROTECT_PRE;  // go to AR_PRE ready
	if (flag_protect_AR==1) p->state=AR_STATE_WAIT_TIME3;	// GO to time 3	 
break;

/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 3*/
case AR_STATE_WAIT_TIME3:  
	if (p->E==1){ p->counter=0;}
	p->counter++; 


	if (p->counter>p->acting_time3) {
	if(flag_protect_AR==1) p->state=AR_STATE_TRIP_RESET3;
    else p->state=AR_STATE_FAIL;
	}
break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 3*/

case AR_STATE_TRIP_RESET3:  
	if (p->E==1){p->counter=0;p->trip_reset=1;}
	p->counter++;
	if (p->counter==2) p->trip_reset=0;
	
	if (p->counter==4){ //check no protect on 4 ms
		if (p->flag_protect==0) p->state=AR_STATE_PULSES_ON3;  // go to pulse ena
		else p->state=AR_STATE_FAIL;	// GO to AR_FAIL
	}
break;
/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	TIME 3*/
case AR_STATE_PULSES_ON3:  
	if (p->E==1){ p->counter=0;p->pulses_on=1;p->AR_acting=1;}
	p->counter++;
	if (p->counter==2)	p->pulses_on=0;
	
	if (p->counter>p->ready_time) p->state=AR_STATE_WAIT_PROTECT_PRE;  // go to AR_PRE ready
	if (p->flag_protect==1) p->state=AR_STATE_FAIL;	// GO to AR_FAIL	 
break;

/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
case AR_STATE_FAIL:  
	if (p->E==1){

	}
	//TODO 209 если три попытки включени€ неудачные то это системна€ авари€,
	// и восстановить напр€жени€ на шинах 10к¬ не удалось длительное врем€
	//что делать дальше? как перезапустить все поле?
	//нужно отправить всю систему в состо€ние SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION

	// TODO209 - здесь может висеть сигнал защиты, дл€ перезапуска его нужно сбросить вручную
	//или будущие поколени€ дополн€т здесь логику, так, чтобы перед переходом системы в SM_DIO_LOGIC_INV_WAIT_ALL_CONDITION
	//прошел сброс защит
	//ƒумать нужно так -
	// 			если мы здесь значит 3 цикла јѕ¬ не помогли. —амое веро€тное погасла полностью сеть или неисправен инвертор
	//			если неисправен инвертор до это аппаратна€ защита с отключением Q4 и  7
	//			если это сеть пропала, то ....
	//			возможно нужно сделать защиту от пропадани€ сети...

	//¬озможно самое правильно решение - переходить в ночной режим и ждать "утра" и делать сброс защиты из контура dio_logic_inv.

	p->pulses_on=0;
	p->trip_reset=0;
	if (p->flag_protect==0) {
	p->state=AR_STATE_STOP;
	p->AR_acting = 0;
	}
	break;

/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/

default: break; 

} //end switch AR state

} // end if AR_ena == 1

}

// end file



