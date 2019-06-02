#ifndef _RAD_IO

#define _RAD_IO

#include <stdlib.h>
#include <avr/io.h>


/******************************************************************************
 * Defines                                                                    *
 ******************************************************************************/

#define RADIO_SI4464_SELECT (1 << PORTB1) 
#define ATMEGA_SLAVE_SELECT (1 << PORTB2) 
#define ATMEGA_MOSI (1 << PORTB3)
#define ATMEGA_MISO (1 << PORTB4)
#define ATMEGA_SCK (1 << PORTB5) 

#define RADIO_DEFUALT_DATA_SIZE 64
#define RADIO_DEFUALT_CHANNEL 0


/******************************************************************************
 * Typedefs                                                                   *
 ******************************************************************************/

typedef enum RadIO_Network_Star_Role {
	MASTER,
	SLAVE
} RadIO_Network_Star_Role;

typedef struct RadIO_Network_Star_Packet {
	uint16_t version;
	uint16_t address;
	uint16_t checksum;
	uint16_t data;
} RadIO_Network_Star_Packet;

typedef struct RadIO_Network_Star {
	void (*send)( struct RadIO_Network_Star*, uint8_t* );
	uint8_t* (*recv)( struct RadIO_Network_Star* );
	RadIO_Network_Star_Role role;
	RadIO_Network_Star_Packet to_send;
	RadIO_Network_Star_Packet recieved;
	void (*free)(struct RadIO_Network_Star*);
	uint8_t data_size;
	uint8_t channel;
} RadIO_Network_Star;

typedef enum {
	STAR,	
	NONE
} RadIO_Network_Type;

typedef union RadIO_Network_Generic {
	RadIO_Network_Star* star;	
} RadIO_Network_Generic;

typedef struct RadIO_Network {
	RadIO_Network_Generic* generic;
	RadIO_Network_Type type;
	RadIO_Network_Star* (*star_factory)(struct RadIO_Network*, 
					    uint8_t, uint8_t);
	void (*free)(struct RadIO_Network*);
} RadIO_Network;


/******************************************************************************
 * Function Declarations                                                      *
 ******************************************************************************/

void _radio_network_star_send( RadIO_Network_Star*, uint8_t* );

uint8_t* _radio_network_star_recv( RadIO_Network_Star* );

void _radio_network_free( RadIO_Network* );

void _radio_network_star_free( RadIO_Network_Star* );


uint8_t radio_write_property( uint8_t, uint8_t, uint8_t );

uint8_t radio_read_property( uint8_t, uint8_t );

uint8_t radio_write_spi( uint8_t );

uint8_t radio_read_spi();

void radio_configure_uart();

void radio_configure_spi();

void radio_configure_si4464();

void radio_write_uart( uint8_t );


RadIO_Network* radio_network_factory( RadIO_Network_Type );

RadIO_Network_Star* _radio_network_star_factory( RadIO_Network*,
						 uint8_t, uint8_t );


/******************************************************************************
 * Function Definitions                                                       * 
 ******************************************************************************/

/**********************************************
 * A bit of a funny implementation, fix later *
 **********************************************/
void radio_reboot_select() 
{
	PORTB |= RADIO_SI4464_SELECT;	

	/*****************************
	 * Just needs a delay > 80ns *
	 *****************************/

	asm volatile ("nop;");
	/*********************************************
	 * TODO: Extended delay, remove later, DEBUG *
	 *********************************************/
	for (volatile int i = 0; i < 100; i++);

	PORTB ^= RADIO_SI4464_SELECT;	

	/*********************************************
	 * TODO: Extended delay, remove later, DEBUG *
	 *********************************************/
	asm volatile ("nop;");
	for (volatile int i = 0; i < 100; i++);

	/******************************************************************
	 * TODO: Fix this function: Want to toggle the SS on and off with *
	 *	 two functions.						  *
	 ******************************************************************/
}

uint8_t radio_wait_for_cts() 
{
	uint8_t cts = radio_read_spi();
	while ( cts != 0xFF ) {
		radio_reboot_select();
		radio_write_spi(0x44);	
		cts = radio_read_spi();
	}
	return cts;
} 

uint8_t radio_write_property(uint8_t group, uint8_t number, 
				       uint8_t value)
{
	
	/********************************************************************
	 * Use the SET_PROPERTY command to write [value] to property number *
	 * [number] in group [group]					    *
	 ********************************************************************/
	radio_reboot_select();	

	radio_write_spi(0x11);
	radio_write_spi(group);
	radio_write_spi(1);
	radio_write_spi(number);
	radio_write_spi(value);
	
	radio_wait_for_cts();

	return 0;
}

uint8_t radio_read_property(uint8_t group, uint8_t number)
{

	/*******************************************************************
	 * Use the GET_PROPERTY command to read a value in property number *
	 * [number] in group [group]					   *
	 *******************************************************************/
	radio_reboot_select();	

	radio_write_spi(0x12);
	radio_write_spi(group);
	radio_write_spi(1);
	radio_write_spi(number);
	
	radio_wait_for_cts();

	uint8_t value = radio_read_spi();

	return value;

}

void radio_configure_si4464() 
{
	/****************************
	 * Wait for POR to complete *
	 ****************************/

	/****************************************
	 * TODO: Removed this for debug, unsure *
	 ****************************************/
	/*
	radio_reboot_select();
	radio_write_spi(0x44);
	radio_wait_for_cts();
	*/

	/********************
	* Power up commmand *
	*********************/
	radio_reboot_select();
	radio_write_spi(0x02);
	/***************
	* Default mode *
	****************/
	radio_write_spi(0x01);
	/*****************
	* External clock *
	******************/
	radio_write_spi(0x01);
	/**************
	* Clock speed *
	***************/
	uint32_t CLOCK_FREQ = 30000000;
	uint8_t clock_freqs[4] = {(uint8_t)(CLOCK_FREQ & 0xFF000000),
				  (uint8_t)(CLOCK_FREQ & 0x00FF0000),
				  (uint8_t)(CLOCK_FREQ & 0x0000FF00),
				  (uint8_t)(CLOCK_FREQ & 0x000000FF)};
	for (int byte_num = 0; byte_num < 4; byte_num += 1) {
		radio_write_spi(clock_freqs[byte_num]);
	}


	/*************************
	 * Configure Si4464 GPIO *
	 *************************/
	radio_reboot_select();	
	radio_write_spi(0x13);
	/**************************
	 * Set GPIO0 as TX switch *
	 **************************/
	radio_write_spi(32);
	/**************************
	 * Set GPIO1 as RX switch *
	 **************************/
	radio_write_spi(33);
	/***************************************
	 * Set GPIO2,3, nIRQ, SDO as default   *
	 ***************************************/
	radio_write_spi(0);
	radio_write_spi(0);
	radio_write_spi(0);
	radio_write_spi(0);
	/*********************************
	 * Set drive strength as default *
	 *********************************/
	radio_write_spi(0);
	radio_wait_for_cts();


	/****************************************
	 * Write properties from generated code *
	 ****************************************/
	/**********************************************************************
	 * TODO: Currently good except for a large power decrease, 0x01 power * 
	 *	 level instead of maximum, low data rate, and some other      *
	 *	 params have been messed with too.			      *
	 **********************************************************************/
	radio_write_property(0x00, 0x00, 0x52);
	radio_write_property(0x02, 0x00, 0x00);
	radio_write_property(0x02, 0x01, 0x00);
	radio_write_property(0x02, 0x02, 0x00);
	radio_write_property(0x02, 0x03, 0x00);
	radio_write_property(0x01, 0x00, 0x00);
	radio_write_property(0x00, 0x03, 0x60);
	radio_write_property(0x00, 0x01, 0x00);
	radio_write_property(0x22, 0x00, 0x08);
	radio_write_property(0x22, 0x01, 0x01);
	radio_write_property(0x22, 0x02, 0x00);
	radio_write_property(0x20, 0x4c, 0x00);
	radio_write_property(0x20, 0x4a, 0xFF);
	radio_write_property(0x10, 0x00, 0x08);
	radio_write_property(0x10, 0x01, 0x14);
	radio_write_property(0x10, 0x02, 0x00);
	radio_write_property(0x10, 0x03, 0x0F);
	radio_write_property(0x10, 0x04, 0x31);
	radio_write_property(0x10, 0x05, 0x00);
	radio_write_property(0x10, 0x06, 0x00);
	radio_write_property(0x10, 0x07, 0x00);
	radio_write_property(0x10, 0x08, 0x00);
	radio_write_property(0x11, 0x00, 0x01);
	radio_write_property(0x11, 0x01, 0xB4);
	radio_write_property(0x11, 0x02, 0x2B);
	radio_write_property(0x11, 0x03, 0x00);
	radio_write_property(0x11, 0x04, 0x00);
	radio_write_property(0x12, 0x00, 0x84);
	radio_write_property(0x12, 0x01, 0x01);
	radio_write_property(0x12, 0x02, 0x08);
	radio_write_property(0x12, 0x03, 0xFF);
	radio_write_property(0x12, 0x04, 0xFF);
	radio_write_property(0x12, 0x05, 0x00);
	radio_write_property(0x12, 0x06, 0x02);
	radio_write_property(0x12, 0x08, 0x00);
	radio_write_property(0x12, 0x09, 0x00);
	radio_write_property(0x12, 0x0a, 0x00);
	radio_write_property(0x12, 0x0b, 0x30);
	radio_write_property(0x12, 0x0c, 0x30);
	radio_write_property(0x12, 0x0d, 0x00);
	radio_write_property(0x12, 0x0e, 0x40);
	radio_write_property(0x12, 0x0f, 0x04);
	radio_write_property(0x12, 0x10, 0x80);
	radio_write_property(0x12, 0x11, 0x00);
	radio_write_property(0x12, 0x12, 0x00);
	radio_write_property(0x12, 0x13, 0x00);
	radio_write_property(0x12, 0x14, 0x00);
	radio_write_property(0x12, 0x15, 0x00);
	radio_write_property(0x12, 0x16, 0x00);
	radio_write_property(0x12, 0x17, 0x00);
	radio_write_property(0x12, 0x18, 0x00);
	radio_write_property(0x12, 0x19, 0x00);
	radio_write_property(0x12, 0x1a, 0x00);
	radio_write_property(0x12, 0x1b, 0x00);
	radio_write_property(0x12, 0x1c, 0x00);
	radio_write_property(0x12, 0x1d, 0x00);
	radio_write_property(0x12, 0x1e, 0x00);
	radio_write_property(0x12, 0x1f, 0x00);
	radio_write_property(0x12, 0x20, 0x00);
	radio_write_property(0x12, 0x21, 0x00);
	radio_write_property(0x12, 0x22, 0x00);
	radio_write_property(0x12, 0x23, 0x00);
	radio_write_property(0x12, 0x24, 0x00);
	radio_write_property(0x12, 0x25, 0x00);
	radio_write_property(0x12, 0x26, 0x00);
	radio_write_property(0x12, 0x27, 0x00);
	radio_write_property(0x12, 0x28, 0x00);
	radio_write_property(0x12, 0x29, 0x00);
	radio_write_property(0x12, 0x2a, 0x00);
	radio_write_property(0x12, 0x2b, 0x00);
	radio_write_property(0x12, 0x2c, 0x00);
	radio_write_property(0x12, 0x2d, 0x00);
	radio_write_property(0x12, 0x2e, 0x00);
	radio_write_property(0x12, 0x2f, 0x00);
	radio_write_property(0x12, 0x30, 0x00);
	radio_write_property(0x12, 0x31, 0x00);
	radio_write_property(0x12, 0x32, 0x00);
	radio_write_property(0x12, 0x33, 0x00);
	radio_write_property(0x12, 0x34, 0x00);
	radio_write_property(0x30, 0x00, 0x00);
	radio_write_property(0x30, 0x01, 0x00);
	radio_write_property(0x30, 0x02, 0x00);
	radio_write_property(0x30, 0x03, 0x00);
	radio_write_property(0x30, 0x04, 0x00);
	radio_write_property(0x30, 0x05, 0x00);
	radio_write_property(0x30, 0x06, 0x00);
	radio_write_property(0x30, 0x07, 0x00);
	radio_write_property(0x30, 0x08, 0x00);
	radio_write_property(0x30, 0x09, 0x00);
	radio_write_property(0x30, 0x0a, 0x00);
	radio_write_property(0x30, 0x0b, 0x00);
	radio_write_property(0x20, 0x00, 0x02);
	radio_write_property(0x20, 0x01, 0x00);
	radio_write_property(0x20, 0x02, 0x07);
	radio_write_property(0x20, 0x51, 0x0A);
	radio_write_property(0x23, 0x00, 0x2C);
	radio_write_property(0x23, 0x01, 0x0E);
	radio_write_property(0x23, 0x02, 0x0B);
	radio_write_property(0x23, 0x03, 0x04);
	radio_write_property(0x23, 0x04, 0x0C);
	radio_write_property(0x23, 0x05, 0x73);
	radio_write_property(0x23, 0x06, 0x03);
	radio_write_property(0x20, 0x03, 0x00);
	radio_write_property(0x20, 0x04, 0x27);
	radio_write_property(0x20, 0x05, 0x10);
	radio_write_property(0x20, 0x06, 0x01);
	radio_write_property(0x20, 0x07, 0xC9);
	radio_write_property(0x20, 0x08, 0xC3);
	radio_write_property(0x20, 0x09, 0x80);
	radio_write_property(0x20, 0x0a, 0x00);
	radio_write_property(0x20, 0x0b, 0x05);
	radio_write_property(0x20, 0x0c, 0x76);
	radio_write_property(0x20, 0x18, 0x01);
	radio_write_property(0x22, 0x03, 0x3D);
	radio_write_property(0x40, 0x00, 0x38);
	radio_write_property(0x40, 0x01, 0x0D);
	radio_write_property(0x40, 0x02, 0xDD);
	radio_write_property(0x40, 0x03, 0xDD);
	radio_write_property(0x40, 0x04, 0x08);
	radio_write_property(0x40, 0x05, 0x31);
	radio_write_property(0x40, 0x06, 0x20);
	radio_write_property(0x40, 0x07, 0xFE);
	radio_write_property(0x20, 0x19, 0x80);
	radio_write_property(0x20, 0x1a, 0x08);
	radio_write_property(0x20, 0x1b, 0x03);
	radio_write_property(0x20, 0x1c, 0x80);
	radio_write_property(0x20, 0x1d, 0x00);
	radio_write_property(0x20, 0x1e, 0x20);
	radio_write_property(0x20, 0x1f, 0x10);
	radio_write_property(0x20, 0x22, 0x09);
	radio_write_property(0x20, 0x23, 0xC4);
	radio_write_property(0x20, 0x24, 0x00);
	radio_write_property(0x20, 0x25, 0x34);
	radio_write_property(0x20, 0x26, 0x6E);
	radio_write_property(0x20, 0x27, 0x00);
	radio_write_property(0x20, 0x28, 0x1A);
	radio_write_property(0x20, 0x29, 0x02);
	radio_write_property(0x20, 0x2a, 0xC2);
	radio_write_property(0x20, 0x2c, 0x04);
	radio_write_property(0x20, 0x2d, 0x36);
	radio_write_property(0x20, 0x2e, 0x80);
	radio_write_property(0x20, 0x2f, 0x03);
	radio_write_property(0x20, 0x30, 0x51);
	radio_write_property(0x20, 0x31, 0xE3);
	radio_write_property(0x20, 0x32, 0x80);
	radio_write_property(0x20, 0x35, 0xE2);
	radio_write_property(0x20, 0x38, 0x11);
	radio_write_property(0x20, 0x39, 0xFF);
	radio_write_property(0x20, 0x3a, 0xFF);
	radio_write_property(0x20, 0x3b, 0x00);
	radio_write_property(0x20, 0x3c, 0x02);
	radio_write_property(0x20, 0x3d, 0xFF);
	radio_write_property(0x20, 0x3e, 0xFF);
	radio_write_property(0x20, 0x3f, 0x00);
	radio_write_property(0x20, 0x40, 0x2B);
	radio_write_property(0x20, 0x42, 0xA4);
	radio_write_property(0x20, 0x43, 0x02);
	radio_write_property(0x20, 0x44, 0xD6);
	radio_write_property(0x20, 0x45, 0x83);
	radio_write_property(0x20, 0x46, 0x01);
	radio_write_property(0x20, 0x47, 0xFF);
	radio_write_property(0x20, 0x48, 0x01);
	radio_write_property(0x20, 0x49, 0x80);
	radio_write_property(0x20, 0x4e, 0x40);
	radio_write_property(0x21, 0x00, 0xFF);
	radio_write_property(0x21, 0x01, 0xBA);
	radio_write_property(0x21, 0x02, 0x0F);
	radio_write_property(0x21, 0x03, 0x51);
	radio_write_property(0x21, 0x04, 0xCF);
	radio_write_property(0x21, 0x05, 0xA9);
	radio_write_property(0x21, 0x06, 0xC9);
	radio_write_property(0x21, 0x07, 0xFC);
	radio_write_property(0x21, 0x08, 0x1B);
	radio_write_property(0x21, 0x09, 0x1E);
	radio_write_property(0x21, 0x0a, 0x0F);
	radio_write_property(0x21, 0x0b, 0x01);
	radio_write_property(0x21, 0x0c, 0xFC);
	radio_write_property(0x21, 0x0d, 0xFD);
	radio_write_property(0x21, 0x0e, 0x15);
	radio_write_property(0x21, 0x0f, 0xFF);
	radio_write_property(0x21, 0x10, 0x00);
	radio_write_property(0x21, 0x11, 0x0F);
	radio_write_property(0x21, 0x12, 0xFF);
	radio_write_property(0x21, 0x13, 0xBA);
	radio_write_property(0x21, 0x14, 0x0F);
	radio_write_property(0x21, 0x15, 0x51);
	radio_write_property(0x21, 0x16, 0xCF);
	radio_write_property(0x21, 0x17, 0xA9);
	radio_write_property(0x21, 0x18, 0xC9);
	radio_write_property(0x21, 0x19, 0xFC);
	radio_write_property(0x21, 0x1a, 0x1B);
	radio_write_property(0x21, 0x1b, 0x1E);
	radio_write_property(0x21, 0x1c, 0x0F);
	radio_write_property(0x21, 0x1d, 0x01);
	radio_write_property(0x21, 0x1e, 0xFC);
	radio_write_property(0x21, 0x1f, 0xFD);
	radio_write_property(0x21, 0x20, 0x15);
	radio_write_property(0x21, 0x21, 0xFF);
	radio_write_property(0x21, 0x22, 0x00);
	radio_write_property(0x21, 0x23, 0x0F);
}

void radio_configure_spi() 
{
	/******************
	 * Configure GPIO *
	 ******************/
	DDRB |= RADIO_SI4464_SELECT | ATMEGA_SLAVE_SELECT | ATMEGA_SCK |
		ATMEGA_MOSI;
	DDRB &= ~(ATMEGA_MISO);

	/**********************************************************************
	 * interrupts disabled, SPI0 enabled, MSB first, Master, IDLE low     *
	 * Leading edge sample, divide by 16 or 8 dependong on if double data *
	 * rate is set.                                                       *
	 **********************************************************************/
	// SPCR = (1 << MSTR) | (1 << SPE) | (0 << SPR1) | (1 << SPR0); 
	/*******************************************************************
	 * TODO: Change this back Actually gonna go 128 or 64 depending on *
	 *	 double data rate for debug.				   *
	 *******************************************************************/
	SPCR = (1 << MSTR) | (1 << SPE) | (1 << SPR1) | (1 << SPR0); 
	
	/*****************************************************************
	 * read only, read only, reserved, reserved, reserved, reserved, * 
	 * reserved, double clock rate enabled.                          *
	 *****************************************************************/
	SPSR |= (1 << SPI2X);
}	


void _radio_network_star_send ( RadIO_Network_Star* self, uint8_t* data)
{
	/************************************
	 * Write packet data to the TX FIFO *
	 ************************************/
	radio_reboot_select();	
	radio_write_spi(0x66);

	for (int data_num = 0; data_num < self->data_size; data_num += 1) {
		radio_write_spi(data[data_num]);
	}
	radio_write_uart('a');
	radio_wait_for_cts();
	// Gets here
	radio_write_uart('b');
	
	/**************************
	 * Start the transmission *
	 **************************/
	radio_reboot_select();
	radio_write_spi(0x31);
	radio_write_spi( self->channel );
	/********************************************************************
	 * Go ready after TX, transmit the FIFO packet, start tx right away *
	 ********************************************************************/
	radio_write_spi(0x00);
	/***********************************************************
	 * use the tx length specified in the packet configuration *
	 ***********************************************************/
	/***********************************************************
	 * actually use a length of 64 byte just to make it easier *
	 ***********************************************************/
	radio_write_spi(0x00);
	radio_write_spi(64);
	/*******************************
	 * Wait for the TX to start up *
	 *******************************/
	radio_write_uart('c');
	radio_wait_for_cts();
	// Doesn't  quite get here
	radio_write_uart('d');
	
	/**********************************
	 * Wait for chip to exit TX state *
	 **********************************/
	uint8_t state = 7;
	while (state == 7) {
		/************************
		 * Request device state *
		 ************************/
		radio_reboot_select();
		radio_write_spi(0x33);
		radio_wait_for_cts();
		state = radio_read_spi();
	}
	radio_write_uart('e');
}

uint8_t* _radio_network_star_recv ( RadIO_Network_Star* self )
{
	/**************************************************************
	 * Start receive 					      *
	 * TODO: Consider going into ready state to not have a double *
	 **************************************************************/
	radio_reboot_select();	
	radio_write_spi(0x32);
	radio_write_spi( self->channel );
	/***********************
	 * Start RX right away *
	 ***********************/
	radio_write_spi(0x0);
	/****************************************************
	 * Recieve length specified by packet configuration *
	 ****************************************************/
	radio_write_spi(0x0);
	/*******************************************************
	 * Go to ready state regardless of errors or finishes  *
	 *******************************************************/
	radio_write_spi(3);
	radio_write_spi(3);
	radio_write_spi(3);

	radio_wait_for_cts();
	
	/**********************************
	 * Wait for chip to exit RX state *
	 **********************************/
	uint8_t state = 8;
	while (state == 8) {
		/************************
		 * Request device state *
		 ************************/
		radio_reboot_select();
		radio_write_spi(0x33);
		radio_wait_for_cts();
		state = radio_read_spi();
	}

	uint8_t* data = malloc(sizeof(uint8_t) * self->data_size);
	/*************************************
	 * Read packet data from the RX FIFO *
	 *************************************/
	radio_reboot_select();	
	radio_write_spi(0x77);
	for (int data_num = 0; data_num < self->data_size; data_num += 1) {
		data[data_num] = radio_read_spi();
	}
	radio_wait_for_cts();

	return data;
}

void radio_configure_uart()
{
	/******************************************************************
	 * UCSR0A (writable reset 0x00) :                                 *
	 * Read only, interrupt cleared, read only, read only, read only, *
	 * read only, double speed, no "multi processor" mode.            *
	 ******************************************************************/
	UCSR0A |= 1 << U2X0;

	/******************************************************************
	 * UCSR0B (writable reset 0x00) :                                 *
	 * Interrupt disabled, interrupt disabled, interrupt disabled,    * 
	 * reciever disabled, transmitter enabled, 8-bit character size,  *
	 * read only, 9th data bit unset.                                 *
	 ******************************************************************/
	UCSR0B |= (1 << TXEN0);

	/******************************************************************
	 * UCSR0C (writable reset 0x06) :                                 *
	 * Async USART, Asyn USART, parity check disabled, parity check   *
	 * disabled, 1 stop bit (minimum number), 8-bit character size,   *
	 * 8-bit character size, falling edge transmit.                   * 
	 ******************************************************************/
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 

	/******************************************************************
	 * UBRR0 (writeable reset 0x00) :                                 *
	 * BAUD = Fosc / (16 * (UBRR0 + 1)) = 12M / 16 = 750K  maximum.   *
	 * BAUD = 1.5M  maximum in double data rate mode (useable?)       *
	 ******************************************************************/
	//UBRR0L = 155; // 9600, off by a bit.
	UBRR0L = 0; // Full speed, exactly 1.5 MHz
}

void radio_write_uart(uint8_t byte)
{
	/*************************************
	 * Wait for last uart write to clear *
	 *************************************/
	while ( !( UCSR0A & ( 1 << UDRE0 )) );

	UDR0 = byte;
}

uint8_t radio_read_spi()
{
	/**********************************
	 * clock out data with dummy data *
	 **********************************/
	return radio_write_spi(0);	
}

uint8_t radio_write_spi( uint8_t data_sent) 
{
	/*****************************
	 * writes SPI0 data register *
	 *****************************/
	SPDR = data_sent;

	/******************************
	 * checks for write collision *
	 ******************************/
	if ( SPSR & (1 << WCOL) ) {
		while (1) {
			radio_write_uart('@');	
		}
	}

	/*********************************
	 * wait for transfer to complete *
	 ********************************/
	uint8_t data_recv = SPDR;
	while ( !(SPSR & (1 << SPIF)) ) {
		data_recv = SPDR;
	} 
	
	return data_recv;
}

RadIO_Network* radio_network_factory( RadIO_Network_Type type )
{
	RadIO_Network* network = (RadIO_Network*) malloc(sizeof(RadIO_Network));
	network->free = &_radio_network_free;
	network->star_factory = &_radio_network_star_factory;

	RadIO_Network_Generic* generic = (RadIO_Network_Generic*)
					 malloc(sizeof(RadIO_Network_Generic));
	network->generic = generic;
	network->type = type;

	if (type == STAR) {
		generic->star = network->star_factory( network,
						      RADIO_DEFUALT_DATA_SIZE,
						      RADIO_DEFUALT_CHANNEL);
	}

	return network;
}

RadIO_Network_Star* _radio_network_star_factory( RadIO_Network* self, 
						 uint8_t data_size, 
						 uint8_t channel )
{
	RadIO_Network_Star* star = (RadIO_Network_Star*) 
				   malloc(sizeof(RadIO_Network_Star));

	star->send = &_radio_network_star_send;
	star->recv = &_radio_network_star_recv;
	star->free = &_radio_network_star_free;

	star->data_size = data_size;
	star->channel = channel;

	return star;
}


void _radio_network_star_free(RadIO_Network_Star* self) {
	/************************************************
	 * TODO: Nothing to free as of yet. May delete. *
	 ************************************************/
}

void _radio_network_free(RadIO_Network* self) {
	if (self->type == STAR) {
		self->generic->star->free(self->generic->star);
		free(self->generic->star);
	}
	free(self->generic);
}

#endif
