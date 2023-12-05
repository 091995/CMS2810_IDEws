// auxalary dio_logic function
// control Q and auxQ states and commands 
#ifndef MODEL
#include "dio_func.h"
#endif



void DIO_AUX_IO_Init(){

aux_K7.time_on_ms	  = 100;
aux_K7.time_off_ms  = 100;
aux_Q26.time_on_ms  = 50;
aux_Q26.time_off_ms = 50;
aux_Q4.time_on_ms	  = 2000;
aux_Q4.time_off_ms  = 10000;

aux_K91.time_on_ms=50;
aux_K91.time_off_ms=1000; //very slow offf

aux_Q6.time_on_ms	  = 2000;
aux_Q6.time_off_ms  = 5000;



//release all on|off command
aux_K7.cmd_in=0;
aux_Q26.cmd_in=0;
aux_Q4.cmd_in=0;
aux_K91.cmd_in=0;
aux_Q6.cmd_in=0;

aux_K7.state_prev=-1;
aux_Q26.state_prev=-1;
aux_Q4.state_prev=-1;
aux_K91.state_prev=-1;
aux_Q6.state_prev=-1;

aux_K7.state=STATE_Q_INIT;
aux_Q26.state=STATE_Q_INIT;
aux_Q4.state=STATE_Q_INIT;
aux_K91.state=STATE_Q_INIT;
aux_Q6.state=STATE_Q_INIT;



}

void DIO_AUX_IO_Calc(){
int trip_reset=0; 


if ((inv.in.cmd_trip_reset==1)){
	trip_reset=1;
}

aux_K7.cmd_trip_reset=trip_reset;
aux_Q4.cmd_trip_reset=trip_reset;
aux_Q26.cmd_trip_reset=trip_reset;
aux_K91.cmd_trip_reset=trip_reset;

aux_Q6.cmd_trip_reset=trip_reset;

aux_Q4.calc(&aux_Q4);
aux_Q26.calc(&aux_Q26);
aux_K7.calc(&aux_K7);
aux_K91.calc(&aux_K91);
aux_Q6.calc(&aux_Q6);

//copain_aux_QS1.cmd_trip_reset=trip_reset;
//copain_aux_QS2.cmd_trip_reset=trip_reset;




//copain_aux_QS1.calc(&copain_aux_QS1);
//copain_aux_QS2.calc(&copain_aux_QS2);



//release all on|off command
aux_K7.cmd_in=0;
aux_Q4.cmd_in=0;
aux_K91.cmd_in=0;


aux_Q6.cmd_in=0;

}

void DIO_AUX_Q_Init(DIO_AUX_Q*p)
{  
p->state=STATE_Q_INIT;

p->log[0]=p->state;

}

//дискретные автоматы которы следят за правильностью включения
// и выключения выключаетеля. 

void DIO_AUX_Q_Calc(DIO_AUX_Q*p)
{

// ќпределение состояния аппарата для индикации (вкл-откл-неопределено)
if ((p->aux_on==1)&&(p->aux_off==0)) p->status=STATUS_Q_ON;
if ((p->aux_on==0)&&(p->aux_off==1)) p->status=STATUS_Q_OFF;

if (p->cmd_trip_reset==1) p->switch_fail=0;

if (p->state_prev!=p->state) {
	p->E=1;
	p->log_counter++;
	p->log_counter&=0x7;
	p->log[p->log_counter]=p->state;
}
else p->E=0;

p->state_prev=p->state;

switch (p->state)
{
case STATE_Q_INIT: 
	if (p->E==1){
	p->counter=0;
	} 
	p->cmd_on=0;
	p->cmd_off=0;
	p->hold_on=0;p->hold_off=0;
	p->switch_fail=0;
	//wait 200ms to read data from PLC and then go to state
	//A&D need more time for CAN-IO to send data - try 1sec
	p->counter++;
	if (p->counter>200) {
	if ((p->aux_on==0)&&(p->aux_off==1)) p->state=STATE_Q_OFF;
	if ((p->aux_on==1)&&(p->aux_off==0)) p->state=STATE_Q_ON;
	if (p->aux_on==p->aux_off) p->state=STATE_Q_TURNING_FAILED;
	}
	break;

case STATE_Q_OFF:  
	if (p->E==1){
	}
	p->hold_on=0;p->hold_off=1;
	if (p->cmd_in==CMD_Q_ON) p->state=STATE_Q_GO_ON;
	if ((p->cmd_in==CMD_Q_OFF)&&(p->cmd_in_prev!=CMD_Q_OFF))
		p->state=STATE_Q_GO_OFF;

	if ((p->aux_off==0)&&(p->aux_on==1)) {p->state=STATE_Q_ON;p->switch_fail=1;}
	
	if (p->aux_on==p->aux_off){
	p->status=STATUS_Q_UNDEFINED;
	p->bk_fail=1;
	}
	else p->bk_fail=0;

    break;

case STATE_Q_GO_ON:  
	if (p->E==1){
		p->cmd_on=1;
		p->cmd_off=0;	
		p->counter=0;
	}
	p->hold_on=1;p->hold_off=0;	
	if (p->cmd_in==CMD_Q_OFF) p->state=STATE_Q_GO_OFF;
	
	//ускорение вы€вления сост вкл
//	if ((p->aux_on==1)&&(p->aux_off==0)) p->counter2++; else p->counter2=0;
//	if (p->counter2>=20) p->state=STATE_Q_ON;


	if (p->counter>AUX_Q_CMD_TIME_MS) p->cmd_on=0;//limit time for cmd_on pulse

	p->counter++;
	if (p->counter>=p->time_on_ms){
		p->counter=p->time_on_ms;
		p->cmd_on=0;
		if ((p->aux_on==1)&&(p->aux_off==0)) 
		p->state=STATE_Q_ON;
		else
		p->state=STATE_Q_TURNING_FAILED;//если прошло p->Lim_t_on и доп. б/к не разомкнулся то фиксируем аварию;	 
	}
    break;
    
case STATE_Q_ON:  
	if (p->E==1){
	}
	p->hold_on=1;p->hold_off=0;
	if (p->cmd_in==CMD_Q_OFF) p->state=STATE_Q_GO_OFF;
	if ((p->cmd_in==CMD_Q_ON)&&(p->cmd_in_prev!=CMD_Q_ON)) p->state=STATE_Q_GO_ON;

	if ((p->aux_off==1)&&(p->aux_on==0)) {p->state=STATE_Q_OFF;p->switch_fail=1;}
    
    if (p->aux_on==p->aux_off) {
	p->status=STATUS_Q_UNDEFINED;
	p->bk_fail=1;
	}
	else p->bk_fail=0;

    break;

case STATE_Q_GO_OFF:  
	if (p->E==1){
		p->cmd_on=0;
		p->cmd_off=1;	
		p->counter=0;
	}
	p->hold_on=0;p->hold_off=1;

		//ускорение вы€вления сост откл
//	if ((p->aux_on==0)&&(p->aux_off==1)) p->counter2++; else p->counter2=0;
//	if (p->counter2>=20) p->state=STATE_Q_OFF;

	p->counter++;
	if (p->counter>AUX_Q_CMD_TIME_MS) p->cmd_off=0;	//limit time for cmd_off pulse

	if (p->counter>=p->time_off_ms) {
		p->counter=p->time_off_ms;
		p->cmd_off=0;
		if ((p->aux_off==1)&&(p->aux_on==0)) p->state=STATE_Q_OFF;
		else p->state=STATE_Q_TURNING_FAILED; //если прошло p->Lim_t_off и доп. б/к не разомкнулся то фиксируем аварию;	 
	}
    break;

case STATE_Q_TURNING_FAILED:
// если отказывает любое из переключений, то даем команду отключение и ждем сброса защиты
	if (p->E==1)  
	{
		p->cmd_on=0;
		p->cmd_off=1;
		p->counter=0;
	}	 

	p->counter++;
	if (p->counter>AUX_Q_CMD_TIME_MS) p->cmd_off=0;	//limit time for cmd_off pulse

	p->hold_on=0;p->hold_off=1;
	p->switch_fail=1;
	if (p->cmd_trip_reset==1) {
		p->cmd_off=0;
		p->switch_fail=0;
		p->state=STATE_Q_OFF;
	}
    break; 
    
default: p->state=STATE_Q_TURNING_FAILED; break;
} // end switch (dio_logic.stateQ)   

p->cmd_in_prev=p->cmd_in;
 // end for


}

