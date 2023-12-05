#include "apl_func.h"
#include "..\dde\dde_func.h"

/*ѕ–»ћ1.*/


void APL_ALARM_Init()
{
int ii;
apl_alarm.state=0;
apl_alarm.state_prev=-1;

/**apl_alarm.p_mask_word_statcom1[0]=0x3F00;
*apl_alarm.p_mask_word_statcom1[1]=0x81FF;
*apl_alarm.p_mask_word_statcom1[2]=0x81FF;
*apl_alarm.p_mask_word_statcom1[3]=0xFFFF;
*apl_alarm.p_mask_word_statcom1[4]=0x000B;
*apl_alarm.p_mask_word_statcom1[5]=0xFBC7;
*apl_alarm.p_mask_word_statcom1[6]=0x00FF;
*apl_alarm.p_mask_word_statcom1[7]=0x0077;

*apl_alarm.p_mask_word_statcom2[0]=0xFFFF;
*apl_alarm.p_mask_word_statcom2[1]=0xBFFF;
*apl_alarm.p_mask_word_statcom2[2]=0xFFFF;
*apl_alarm.p_mask_word_statcom2[3]=0xFFFF;
*apl_alarm.p_mask_word_statcom2[4]=0xFFFF;
*apl_alarm.p_mask_word_statcom2[5]=0xDfff;
*apl_alarm.p_mask_word_statcom2[6]=0xFFFF;
*apl_alarm.p_mask_word_statcom2[7]=0xFFFF;
*/
for (ii=0;ii<8;ii++) {
	apl_alarm.prev_alarm_word_statcom1[ii] = 0;
	apl_alarm.prev_alarm_word_statcom2[ii] = 0;
}
}
                 
void APL_ALARM_Calc()
{ 
int ii;

for (ii=0;ii<8;ii++) {
	apl_alarm.p_masked_word_statcom1[ii] = (*apl_alarm.p_alarm_word_statcom1[ii])&(*apl_alarm.p_mask_word_statcom1[ii]);
	apl_alarm.p_masked_word_statcom2[ii] = (*apl_alarm.p_alarm_word_statcom2[ii])&(*apl_alarm.p_mask_word_statcom2[ii]);	
	}



/* сохраняем признак перехода от состояние                  */
/* к состоянию для выполнения ENTRY	                         */
/* if (apl_alarm.state_prev!=apl_alarm.state) apl_alarm.E=1;  */
/* else apl_alarm.E=0;                                        */
/* apl_alarm.state_prev=apl_alarm.state;                      */
/*                                                            */
/* switch (apl_alarm.state)                                   */
/* {                                                          */
/* case SM_APL_ALARM_INIT:                                    */
/*                                                            */
/* 	if (apl_alarm.E==1)  //ENTRY                            */
/* 		{                                                     */
/*         apl_alarm.counter=0;                               */
/*     	}			                                          */
/* 	break;                                                    */
/* default: break;                                            */
/* } //end switch (dcs_alarm.state)                         */

}

