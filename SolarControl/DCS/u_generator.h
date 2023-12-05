

#ifndef U_GENERATOR_H
#define U_GENERATOR_H


#include "V_IQmath.h"

struct SGenerator{
	  	  	  	long  wt;
	  	  	  	long  w_e;
                long  rmp_wt;
                long  Um1_ref;
                long  step;
                void  (*calc)(struct SGenerator*);	//!< Pointer to calculation function
               };	            

typedef struct SGenerator TGenerator;

  //! инициализатор по-умолчанию
#define GENERATOR_DEFAULTS { 0, \
						  _IQ(1),\
							0, \
						  0, \
                          _IQ(Td*0.1), \
              	          generator_calc }


void generator_calc(TGenerator*);


#endif

/*@}*/
