/***************************************************************************
 * NOTE: Main testing file, mostly just a mess right now. Will be fixed up *
 *	 later.								   *
 ***************************************************************************/

#include <stdint.h>
#include <avr/io.h>
#include "RadIO.h"


void uint_to_uart(uint8_t value);

int main()
{
	/*
	RadIO_Network* network = radio_network_factory(STAR);

	network->generic->star->recv(network->generic->star);

	network->free(network);

	free(network);

	while (1){}
	*/


	radio_configure_uart();

	radio_configure_spi();

	uint_to_uart(DDRB);	

/*
while (1) {
	for (volatile uint32_t i = 0; i < 10000; i++);		
	// This seems to output fine at least.
	radio_write_spi(0x12);
	radio_write_uart('$');
}
*/


	for (volatile uint32_t i = 0; i < 1000000; i++);

	radio_write_uart('?');
	radio_write_uart('\n');

	radio_configure_si4464();

	radio_write_uart('!');
	radio_write_uart('\n');

	for (volatile uint32_t i = 0; i < 100000; i++);

	radio_write_uart('!');
	radio_write_uart('\n');

	RadIO_Network* network = radio_network_factory(STAR);
	RadIO_Network_Star* star = network->generic->star;
	
	uint8_t data[64] = { 'h',  'e',  'l',  'l',  'o',  ' ',  'w',  'o',
			     'r',  'l',  'd',  ' ',  ' ',  ' ',  ' ',  ' ',
			     ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
			     ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
			     ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
			     ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
			     ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
			     ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' '};
	while (1) {
		//uint8_t value = radio_read_property(0x00, 0x00);
		//uint_to_uart(value);
		//for (volatile uint32_t i = 0; i < 100000; i++);
		uint_to_uart(';');
		for (volatile uint32_t i = 0; i < 10000; i++);
		star->send(star, data);	
	}
}

void uint_to_uart(uint8_t value) 
{
	uint8_t digit_1 = value / 100;
	uint8_t digit_2 = (value - 100 * digit_1) / 10;
	uint8_t digit_3 = (value - 100 * digit_1 - 10 * digit_2) / 1;
	radio_write_uart(digit_1 + 48);
	radio_write_uart(digit_2 + 48);
	radio_write_uart(digit_3 + 48);
	radio_write_uart('\n');
}
