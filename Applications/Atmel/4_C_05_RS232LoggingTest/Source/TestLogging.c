/************************************************************************
File: TestLogging.c
Description:

************************************************************************/

#include "HtlStddef.h"
#include "RS232.h"
#include "Logger.h"
#include <avr/io.h>
#include <stdio.h>

int
MyPut(char aCharacter, FILE* aFile)
{
	RS232SendData((TRS232) aFile, (unsigned char *)&aCharacter, 1);
	return 1;
}

int main(void)
{
	TRS232 rs232;
	TRS232Config config;
	
	config.Baudrate = 9600;
	config.SendBufferSize = 100;
	config.ReceiveBufferSize = 10;
	
	rs232 = RS232Create(ERS232_NO_0, config, F_CPU);
	
	fdevopen(MyPut, (FILE*)rs232);
	
	//LogInit();
	
	while(1)
	{
		printf("Mei RS232 täst wif efdäfopn");
		delayMs(500);
	}
}