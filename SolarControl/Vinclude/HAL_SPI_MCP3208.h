

#ifndef _HAL_SPI_MCP3208_H
#define _HAL_SPI_MCP3208_H


// MCP3208 SPI Input Data bit definitions:
struct  MCP3208_SPI_WRITE_WORD_BITS {
   Uint16 NUL_REG:11;
   Uint16 ADDRESS:3;
   Uint16 SINGLE_OR_DIFF:1;
   Uint16 START:1;
};

union MCP3208_SPI_WRITE_WORD_REG {
   Uint16               				all;
   struct MCP3208_SPI_WRITE_WORD_BITS	bit;
};

// MCP3208 SPI Input Data bit definitions:
struct  MCP3208_SPI_READ_WORD_BITS {       // bit    	description
   Uint16 NULL_BIT:4;
   Uint16 ADC_REG:12;
};

union MCP3208_SPI_READ_WORD_REG {
   Uint16               				all;
   struct MCP3208_SPI_READ_WORD_BITS	bit;
};

// MCP3208 SPI Status Reister 1 bit definitions:
//struct  DRV8301_STATUS_REG_1_BITS {		// bit    	description
//   Uint16 FETLC_OC:1;					// 0		Phase C, low-side FET OC
//   Uint16 FETHC_OC:1;					// 1		Phase C, high-side FET OC
//   Uint16 FETLB_OC:1;					// 2		Phase B, low-side FET OC
//   Uint16 FETHB_OC:1;					// 3		Phase B, high-side FET OC
//   Uint16 FETLA_OC:1;					// 4		Phase A, low-side FET OC
//   Uint16 FETHA_OC:1;					// 5		Phase A, high-side FET OC
//   Uint16 OTW:1;	        			// 6		Over-temperature warning
//   Uint16 OTSD:1;	          			// 7		Over-temperature shut down
//   Uint16 PVDD_UV:1;					// 8		PVDD < 6V
//   Uint16 GVDD_UV:1;					// 9		GVDD < 8V
//   Uint16 FAULT:1;						// 10		FAULTn pin is asserted
//   Uint16 Reserved:5;					// 15:11
//};

struct SHAL_SPI_MCP3208
{

    int state;
    int state_prev;
    int E;
    int counter;

	union MCP3208_SPI_WRITE_WORD_REG writeWord;

	//union MCP3208_SPI_READ_WORD_REG readWord;
	Uint16 readWord1;
	Uint16 readWord2;

    unsigned long adc_regs[16];
    int adc_ch;
    int extra_mux;
};


typedef struct SHAL_SPI_MCP3208 HAL_SPI_MCP3208;


#define HAL_SPI_MCP3208_DEFAULTS {0,0,0,0,\
		{0},\
		0,0}

void HAL_SPI_MCP3208_init(HAL_SPI_MCP3208*p);

void HAL_SPI_MCP3208_update(HAL_SPI_MCP3208*p);




#endif

/*@}*/




