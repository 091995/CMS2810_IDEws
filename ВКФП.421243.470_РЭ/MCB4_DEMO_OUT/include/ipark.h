/* =================================================================================
File name:       IPARK.H   (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the IPARK.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2002		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/
#ifndef IPARK_H
#define IPARK_H

#ifdef __cplusplus
extern "C" {
#endif

struct SIPark{  _iq  ds;  	/* Output: stationary d-axis stator variable */
				  _iq  qs;		/* Output: stationary q-axis stator variable */
				  _iq  ang;		/* Input: rotating angle (pu) */
				  _iq  de;		/* Input: rotating d-axis stator variable */
				  _iq  qe;		/* Input: rotating q-axis stator variable */
		 	 	  void  (*calc)(struct SIPark*);	/* Pointer to calculation function */ 
				 };	            

typedef struct SIPark TIPark;
/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  ipark_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in IPARK.C
------------------------------------------------------------------------------*/
void ipark_calc(TIPark*);

#ifdef __cplusplus
}
#endif

#endif


