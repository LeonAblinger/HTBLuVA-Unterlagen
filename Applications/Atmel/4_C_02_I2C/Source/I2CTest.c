/*********************************************************************************************************
File: I2CTest.c
Author: AblL / Leon Ablinger
Description:
  I2C (TWI) interface for the AtMega644XX microcontroller.
*********************************************************************************************************/

#include <avr/io.h>
#include "I2C.h"

#define SEND_SIZE	 1
#define RECEIVE_SIZE 5

int main(void)
{
	unsigned char sendBuff[SEND_SIZE] = {1};
	unsigned char receiveBuff[RECEIVE_SIZE];
	i2cInit(1000UL, 16000000UL); // Bitrate, ClkFrequency
	
	while(1) {
		i2cWrite(0xA0,  sendBuff, SEND_SIZE);
		i2cRead(0xA0,  receiveBuff, RECEIVE_SIZE);
	}
}