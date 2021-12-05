/********************************************************************************************************************
File:	 SPI.c
Project: SPI - Bus
Author:	 Leon Ablinger / AblL

Description:
	This project opens the possibility to communicate over the SPI-Bus of the AtMega 644 device.
********************************************************************************************************************/

#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void SPI_Init(void) {
	DDRSPI |= ( 1 << MOSI ) | ( 1 << SCK ) | ( 1 << nSS );
	DDRSPI &= ~( 1 << MISO );
	SPCR |= ( 1 << SPE ) | ( 1 << MSTR ) | ( 1 << SPR0 );
	
	PORTSPI |= ( 1 << nSS );
}

unsigned char SPI_Transmit(const unsigned char data) {
	PORTSPI &= ~( 1 << nSS );
	SPDR = data;
	while(!(SPSR & ( 1 << SPIF )));
	PORTSPI |= ( 1 << nSS );

	return SPDR;
}