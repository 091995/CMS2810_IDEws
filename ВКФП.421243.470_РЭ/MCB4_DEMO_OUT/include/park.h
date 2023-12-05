/* =================================================================================
File name:       PARK.H (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the PARK.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2002		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/
#ifndef PARK_H
#define PARK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "IQmathLib.h"

struct SPark{  _iq  ds;  		/* Input: stationary d-axis stator variable */
			  _iq  qs;		    /* Input: stationary q-axis stator variable */
			  _iq  ang;			/* Input: rotating angle (pu) */
			  _iq  de;			/* Output: rotating d-axis stator variable */
			  _iq  qe;			/* Output: rotating q-axis stator variable */
	 	 	  void  (*calc)(struct SPark*);	/* Pointer to calculation function */ 
			 };	            

typedef struct SPark TPark;
/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define PARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  park_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void park_calc(TPark*);

#ifdef __cplusplus
}
#endif

#endif
