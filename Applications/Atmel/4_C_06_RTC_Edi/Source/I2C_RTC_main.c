#include "HtlStddef.h"
#include "I2C.h"
#include "Logger.h"
#include "RS232.h"
#include <avr/io.h>

#define ADDRESS_PCF8583_READ 0xA1
#define ADDRESS_PCF8583_WRITE 0xA0

TRs232 globalRS232;		//global Rs232 variable

int custom_printf(char character, FILE* file);
int testI2C(void);
void logFunc(const TLogEvent* logEvent,
const void* userData,
const char* message);

/*********************************************************************************************************************
Function: main

Parameters: - none

Description: initializes the program -> creates Logger and calls testI2C_RTC() function
**********************************************************************************************************************/

int main(void) {
	LogInit();
	LogSetLogFunction(logFunc, NULL);

	int result = 0;
	result = testI2C();

	return result;
}

/*********************************************************************************************************************
Function: custom_printf

Description: custom function to replace default printf() function. Sends data for printing over Rs232 interface

**********************************************************************************************************************/

int custom_printf(char character, FILE* file) {
	Rs232SendData((TRs232)globalRS232, (unsigned char*)&character, 1);
	return 1;
}

/*********************************************************************************************************************
Function: logFunc

Parameters: - logEvent	-> ERROR / INFO / WARNING / DEBUG  (depends on what happened. example: LogError() is "ERROR"
						- message		->

Description: reads the elapsed on-time of the Real-Time-Clock via the i2c bus

**********************************************************************************************************************/

void logFunc(const TLogEvent* logEvent,
const void* userData,
const char* message) {
	char* tag;

	switch (logEvent->LogLevel) {
		case LOG_LEVEL_DEBUG:
		tag = "DEBUG:";
		break;

		default:
		case LOG_LEVEL_INFO:
		tag = "INFO:";
		break;

		case LOG_LEVEL_WARNING:
		tag = "WARNING:";
		break;

		case LOG_LEVEL_ERROR:
		tag = "ERROR:";
		break;
	}

	printf("%s\n File: %s\n Function: %s\n Line: %u\n Message: %s\n\n", tag, logEvent->FileName,
	logEvent->FunctionName, logEvent->LineNo, message);
}

/*********************************************************************************************************************
Function: testI2C

Parameters: - none

Description: reads the elapsed on-time of the Real-Time-Clock via the i2c bus

**********************************************************************************************************************/
int testI2C(void) {
	TRs232Config config;
	
	//set config
	config.SendBufferSize = 200;
	config.RecieveBufferSize = 20;
	config.BaudRate = (unsigned int)57600;
	globalRS232 = Rs232Create(ERS232_NO_0, F_CPU, config);

	fdevopen(custom_printf, NULL);
	
	//prepares/initializes i2c communication
	if (!I2CInit(1000UL, F_CPU)) {			//Bitrate = 100000UL | ClkFreq (F_CPU) = 16000000UL
		LogError("Initialization failed...");
		DelayMs(500);
		return -1;
	}
	DelayMs(500);

	unsigned char wakeupSignal[1] = {1};
	unsigned char timeData[5];
	unsigned char timeString[20];

	while (1) {
		//wakes the RTC up
		if (!I2CWrite(ADDRESS_PCF8583_WRITE, wakeupSignal, 1)) {
			LogError("Writing failed...");
			DelayMs(500);
		}
		DelayMs(500);
		//reads the time elapsed until now
		if (!I2CRead(ADDRESS_PCF8583_READ, timeData, 5)) {
			LogError("Reading failed...");
			DelayMs(500);
		}
		DelayMs(500);

		sprintf((char*)timeString, "%02x:%02x:%02x.%02x", timeData[3], timeData[2],
		timeData[1], timeData[0]);

		timeString[19] = '\0';		//	"\0" = end of string (EOS)

		LogInfo((const char*)timeString);
		DelayMs(500);
	}

	Rs232Destroy(globalRS232);

	return 0;
}

