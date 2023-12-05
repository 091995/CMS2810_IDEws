void TEST_MEML0L1_LED();
void PROGRAM_STOP();
//void TEST_PWM();
//void TEST_PWM2();
void TEST_ADC();
void TEST_QEP();
void TEST_CAN();
void TEST_RS485();
void TEST_SPI_RTC();

void spi_xmit(int);
void CHIP_SELECT();
void CHIP_DESELECT();
void TEST_SPI_RTC();
void TEST_SPI_EEPROM();
void TEST_RS232();
void TEST_SPI_DAC();

void scia_transmit(int);
void scib_transmit(int);
void scib_receive(int);
void scia_receive(int);
void error(int);
void scia_init_transmit();
void scib_init_transmit();
void scia_init_receive();
void scib_init_receive();
void sci_a_b_fifo_init();

