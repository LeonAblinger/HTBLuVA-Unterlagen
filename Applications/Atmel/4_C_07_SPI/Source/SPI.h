/********************************************************************************************************************
File:	 SPI.h
Project: SPI - Bus
Author:	 Leon Ablinger / AblL

Description:
	This project opens the possibility to communicate over the SPI-Bus of the AtMega 644 device.
********************************************************************************************************************/

#define PORTSPI PORTB
#define DDRSPI  DDRB
#define MOSI PB5
#define MISO PB6
#define SCK  PB7
#define nSS  PB4

/*******************************************************************************************************************/

void SPI_Init(void);
unsigned char SPI_Transmit(const unsigned char cData);