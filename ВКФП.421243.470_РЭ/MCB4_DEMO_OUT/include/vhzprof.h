/* =================================================================================
File name:       VHZ_PROF.H  (IQ version)                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the VHZPROF.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2002	Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/
#ifndef VHZPOF_H
#define VHZPOF_H

#ifdef __cplusplus
extern "C" {
#endif

struct 	SVhzProf{ _iq  freq; 		    /* Input: Input frequency (pu)  */
				  _iq  vout;		    /* Output: Output voltage (pu)  */
				  _iq  FL;				/* Parameter: Low frequency (pu)  */			
				  _iq  FH;				/* Parameter: High frequency at rated voltage  (pu) */
				  _iq  Fmax; 			/* Parameter: Maximum frequency (pu) */		
				  _iq  Vmax;			/* Parameter: Rated voltage (pu)  */					  
			      _iq  Vmin;	 		/* Parameter: Voltage at low frequency range (pu) */
		  	  	  void  (*calc)(struct 	SVhzProf*);	    /* Pointer to calculation function */ 
				};	    
				               
typedef struct 	SVhzProf TVhzProf;
/*-----------------------------------------------------------------------------
Default initalizer for the VHZPROF object.
-----------------------------------------------------------------------------*/                     
#define VHZPROF_DEFAULTS { 0,0, \
                           0,0,0,0,0, \
                  		   vhz_prof_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in VHZ_PROF.C
------------------------------------------------------------------------------*/
void vhz_prof_calc(TVhzProf*);

#ifdef __cplusplus
}
#endif

#endif
