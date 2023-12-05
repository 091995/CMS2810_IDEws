

#ifndef U_INV_SYNC_H
#define U_INV_SYNC_H


#include "V_IQmath.h"

struct SInvSync{
				long ena;
				long state;
				long state_prev;
				long E;
				long counter;

				long sig_RX;
				long sig_RX_prev;
				long dout;


				long wt;
	  	  	  	long wt_e;
                long Q_sign;
                long I_meas;
                long I_max;
                long sync_timeout;
                long sync_ready; //if sync is OK flag is 1, if not flag goes to 0 or err code

				long alpha;
				long beta;

                void  (*init)();
                void  (*calc)();	//!< Pointer to calculation function
               };	            

typedef struct SInvSync TInvSync;

  //! инициализатор по-умолчанию
#define INV_SYNC_DEFAULTS { 0,0,0,0,0,\
							0,0,\
							0,0,0,0,0,0,0,\
							0,0,\
							inv_sync_init,\
							inv_sync_calc }



void inv_sync_init();
void inv_sync_calc();


#endif

/*@}*/
