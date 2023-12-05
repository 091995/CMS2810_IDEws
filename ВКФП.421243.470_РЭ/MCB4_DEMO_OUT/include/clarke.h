/* =================================================================================
File name:       CLARKE.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the CLARKE.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2002		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/
#ifndef CLARKE_H
#define CLARKE_H

#ifdef __cplusplus
extern "C" {
#endif

struct SClarke{  long  as;  		/* Input: phase-a stator variable  */
				  long  bs;			/* Input: phase-b stator variable  */
				  long  ds;			/* Output: stationary d-axis stator variable  */
				  long  qs;			/* Output: stationary q-axis stator variable  */
		 	 	  void  (*calc)(struct SClarke*);	/* Pointer to calculation function */
				  long  cs;
				  long  zero0s;
				 };	            

typedef struct SClarke TClarke;
/*-----------------------------------------------------------------------------
Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
              			  clarke_calc,0,0 }

/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void clarke_calc(TClarke*);

#ifdef __cplusplus
}
#endif


#endif
