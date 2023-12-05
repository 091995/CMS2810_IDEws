/*
 * APL.c
 *
 *  Created on: 20 рту. 2019 у.
 *      Author: admin
 */

#include "APL_func.h"


APL_PROTECT apl_protect = APL_PROTECT_DEFAULTS;

void APL_Init(APL*p)
{

	apl_protect.init(&apl_protect);
}


void APL_ms_Calc(APL*p)
{
	apl_protect.calc(&apl_protect);
	apl_protect.ms_calc(&apl_protect);

}
