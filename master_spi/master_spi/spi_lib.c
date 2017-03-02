/*
 * SPI.c
 *
 * Created: 13-Jan-17 3:03:30 PM
 *  Author: Agarwal-pc
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "spi_lib.h"

/************************************************************************/
/*     spi_init Initialize Master the SPI                                      */
/************************************************************************/

void spi_init()
{
	PORTB = SCL<<0 | MOSI<<1 | MISO<<2 | SS<<3;
	_delay_ms(2000);
	PORTD = 0x01;
	SPI_CR = 0b00000001;
	SPI_ST = 0b00000001;
}

/************************************************************************/
/*     spi_init Initialize Slave the SPI                                      */
/************************************************************************/

void spi_init_slave()
{
	if(PINB == 0x09)
	{
		SPI_CR=0x03;
		SPI_ST=0x04;
	}
}

/************************************************************************/
/*     clock toggling the clock         
                                */
/************************************************************************/

void clock (int x)
{
	SCL = x;
	PORTB = SCL<<0 | MOSI<<1 | SS<<3;
	_delay_ms(500);
}
/************************************************************************/
/*     spi_Start Mater_Start the SPI                                          */
/************************************************************************/
void spi_Start(void)
{
	SS = 0;
	_delay_ms(100);
	PORTB = SCL<<0 | MOSI<<1 | SS<<3;
	_delay_ms(100);
	PORTD = 0x02;
	SPI_CR = 0b00000010;
	SPI_ST = 0b00000010;
}
/************************************************************************/
/*     spi_Start Slave_Start the SPI                                          */
/************************************************************************/
void spi_Start_slave()
{
	if(SPI_CR==0x03|SPI_ST==0x04)
	{
		while((PINB & 0x08 )!=0);
		{
			SPI_CR=0x05;
			SPI_ST=0x06;
		}
	}
}
/************************************************************************/
/*     spi_write Write the SPI                                          */
/************************************************************************/

void spi_Master_Write(unsigned char data)
{
	SPI_DR1 = data;
	if ((SPI_ST == 0x02) && (SPI_CR == 0x02) && (SCL == 1))
	for (unsigned char c=1; c<=8; c++)
	{
		//clock(1);
		MOSI = (SPI_DR1 >> 7);
		PORTB = SCL<<0 | MOSI<<1 | SS<<3;
		_delay_ms(100);
		SPI_DR1 = SPI_DR1 << 1;
		clock(0);
		_delay_ms(100);
		spi_Master_Read();
	}
	SS = 1;
	PORTB = SS<<3;
	PORTD = SPI_DR2;
	_delay_ms(100);
}
/************************************************************************/
/*     spi_read Read the SPI                                            */
/************************************************************************/
int spi_Master_Read()
{
	DDRB = 0x0B;
	clock(1);
	if((PINB & 0x04) == 4)
	{
		SPI_DR2 += 1;
	}
	else
	{
		SPI_DR2 += 0;
	}
	PORTD = (PINB & 0x04);
	if (a<8)
	{
		SPI_DR2 = SPI_DR2 <<1;
	}
	a++;
	return SPI_DR2;
}

/************************************************************************/
/*     data_slave Slave the SPI                                            */
/************************************************************************/
void spi_slave_read()
{
	unsigned char i, ready = 1, check;
	if(SPI_CR==0x05|SPI_ST==0x06)
	{
		for(i=0;i<8;)
		{
			if((PINB & 0x08 ) == 0)
			{
				if(((PINB & 0x01) == 1) && (ready == 1))
				{
					ready = 0;
				}
				if(((PINB & 0x01) == 0) && (ready == 0))
				{
					check = 1;
					ready = 1;
				}
				if (check == 1)
				{
					if((PINB & 0x04)== 4)
					{
						SPI_DR |= 1;
						SPI_DR =SPI_DR<<1;
					}
					else
					{
						SPI_DR |= 0;
						SPI_DR =SPI_DR<<1;
					}
					i++;
					check = 0;
					_delay_ms(100);
					PORTB = (SPI_BFF & 0x01)<<1;
					SPI_BFF = SPI_BFF<<1;
				}
				
			}
			else
			i++;
			
		}
	}
}