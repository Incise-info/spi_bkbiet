#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>

int main(void)
{
	DDRB = 0x0B;
	DDRD = 0xff;
	
		spi_init();
		spi_Start();
		spi_Master_Write(0xf2);
	
}
