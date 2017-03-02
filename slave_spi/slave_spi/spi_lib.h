/*
 * spi_lib.h
 *
 * Created: 13-Jan-17 3:23:24 PM
 *  Author: Agarwal-pc
 */ 


#ifndef SPI_LIB_H_
#define SPI_LIB_H_

uint8_t SPI_ST = 0;
uint8_t SPI_CR = 0;
uint8_t SPI_DR = 0;
uint8_t SPI_DR1 = 0;
uint8_t SPI_DR2 = 0;
uint8_t SPI_BFF = 0x77;

int SCL = 1;
int MOSI = 0;
int MISO = 0;
int SS = 1;
int x = 0;
int a = 1;

void spi_init();
void clock (int x);
void spi_Start(void);
void spi_Write(unsigned char data);


void init_slave();
void start_slave();
void data_slave();



#endif /* SPI_LIB_H_ */