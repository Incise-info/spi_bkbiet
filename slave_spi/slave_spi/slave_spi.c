
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int x=0;
	DDRB = 0x02;
	DDRD = 0xff;
		spi_init_slave();
		spi_Start_slave();
		x = spi_slave_read();
		PORTD = x;
		_delay_ms(1000);
return 0;
}


