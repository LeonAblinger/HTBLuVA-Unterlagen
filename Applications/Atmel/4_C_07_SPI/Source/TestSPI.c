/********************************************************************************************************************
File:	 TestSPI.c
Project: SPI - Bus
Author:	 Leon Ablinger / AblL

Description:
	This project opens the possibility to communicate over the SPI-Bus of the AtMega 644 device.
********************************************************************************************************************/

#define F_CPU 16000000UL
#include "HtlStddef.h"

int main(void) {
	SPI_Init();
	unsigned char rvar;
	
	while(1) {
		for(unsigned char i = 0x00; i < 0xFF; i++) {
			rvar = SPI_Transmit(i);
			DelayMs(2000);
		}
		DelayMs(5000);
	}
	
	
	return 0;
}