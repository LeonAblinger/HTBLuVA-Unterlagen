/********************************************************************************************************************
File:	 RTC.c
Project: RTC - RealTimeClock
Author:	 Leon Ablinger / AblL
Dependencies:
	- RS232
	- Logger
	- RingBuffer
	- I2C

Description:
	This project opens the possibility to communicate with the PCF8583
	real time clock via I2C interface and show the desired values/
	states in a custom message.
********************************************************************************************************************/

#include "HtlStddef.h"
#include "RS232.h"
#include "I2C.h"
#include "Logger.h"
#include <avr/io.h>

#define ADDRESS_WRITE 0xA0
#define ADDRESS_READ 0xA1

TRs232 gRS232;

int
printfOverride(char character, FILE* file);
void
testRTC(void);
void
logFunc(const TLogEvent* logEvent, const char* message);

/*******************************************************************************************************************/

int main(void) {
	
	initLog();
	setLogFunction(logFunc, NULL);

	testRTC();

	return 0;
}

/*******************************************************************************************************************/

void testRTC(void) {
	TRs232Config config;
	config.SendBufferSize = 250;
	config.RecieveBufferSize = 20;
	config.BaudRate = (unsigned int) 19200;

	unsigned char wakeup[1] = {1};
	unsigned char outDta[5];
	unsigned char outStr[20];

	gRS232 = Rs232Create(ERS232_NO_0, F_CPU, config);

	fdevopen(printfOverride, NULL);

	if (!I2CInit(1000UL, F_CPU)) {
		LogError("I2C initialization failed");
		DelayMs(1500);
		return;
	}

	while (1) {
		if (!I2CWrite(ADDRESS_WRITE, wakeup, 1)) {
			LogError("Initialization failed...");
			DelayMs(1500);
		}
		if (!I2CRead(ADDRESS_READ, outDta, 5)) {
			LogError("Reading failed...");
			DelayMs(1500);
		}
		sprintf((char*)outStr, "Read: %02x:%02x:%02x.%02x", outDta[3], outDta[2], outDta[1], outDta[0]);
		outStr[19] = '\0';

		LogInfo((const char*)outStr);
		DelayMs(3000);
	}

	Rs232Destroy(gRS232);
}

/*******************************************************************************************************************/

int printfOverride(char character, FILE* file) {
	Rs232SendData((TRs232)gRS232, (unsigned char*)&character, 1);
	return 1;
}

/*******************************************************************************************************************/

void logFunc(const TLogEvent* logEvent, const char* message) {
	char* loglevel;

	switch (logEvent->logLevel) {
		case LOG_LEVEL_DEBUG:
		loglevel = "\nDEBUG:\n";
		break;

		case LOG_LEVEL_INFO:
		loglevel = "\nINFO:\n";
		break;

		case LOG_LEVEL_WARNING:
		loglevel = "\nWARNING:\n";
		break;

		case LOG_LEVEL_ERROR:
		loglevel = "\nERROR:\n";
		break;
	}
	printf("%s File: %s\n Function: %s\n Line: %u\n Message: %s\n", loglevel, logEvent->fileName, logEvent->functionName, logEvent->lineNo, message);
}
