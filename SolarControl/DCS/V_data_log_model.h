//


#ifndef V_DATA_LOG_MODEL_H
#define V_DATA_LOG_MODEL_H


// Размер значений, передаваемых через логгер (бит)
//#define DLOG_DATA_SIZE 16
#define DLOG_DATA_SIZE 32


#if DLOG_DATA_SIZE == 16
typedef int16 type_data;
#elif DLOG_DATA_SIZE == 32
typedef long type_data;
#endif


#define NUMBER_SAMPLES  256


struct SDataLogModel {
	int StartBits;
	int mode_reset;
    void (*update)(volatile struct SDataLogModel *);			//!<Pointer to update function
    void (*set_mode)(unsigned short mode_reset,volatile struct SDataLogModel *);	//!<Pointer to set_mode function
    void (*background_analizer)(volatile struct SDataLogModel *);	//!<Pointer to background_analizer function
  } ;

typedef volatile struct SDataLogModel TDataLogModel;





#define DATALOG_MODEL_DEFAULTS { 0, 0,\
		dlog_model_update,\
		dlog_model_set_mode,\
		dlog_model_background_analizer }



//! \memberof TDataLog
  void dlog_model_update(TDataLogModel *);
//! \memberof TDataLog
  void dlog_model_set_mode(unsigned short mode_reset,TDataLogModel *);
//! \memberof TDataLog
  void dlog_model_background_analizer(TDataLogModel *);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/


