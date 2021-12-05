/********************************************************************************************************************
File:	 Logger.c
Project: RTC - RealTimeClock
Author:	 Leon Ablinger / AblL
********************************************************************************************************************/

#include "Logger.h"

typedef struct {
	TLoggerFunction Function;
	void*						UserData;
}TLogger;

TLogger Logger;

/*******************************************************************************************************************/

void initLog(void) {
	memset(&Logger, 0, sizeof(Logger));
}

/*******************************************************************************************************************/

void setLogFunction(TLoggerFunction aFunction, void* aUserData) {
	Logger.Function = aFunction;
	Logger.UserData = aUserData;
}

/*******************************************************************************************************************/

void LogEvent_(const char* aFileName, const char* aFunctionName, unsigned int aLineNo, TLogLevel aLogLevel, const char* aMessage) {
	TLogEvent logEvent;

	if (!Logger.Function) {
		return;
	}

	memset(&logEvent, 0, sizeof(logEvent));

	logEvent.fileName = aFileName;
	logEvent.functionName = aFunctionName;
	logEvent.lineNo = aLineNo;
	logEvent.logLevel = aLogLevel;

	if (Logger.Function) {
		Logger.Function(&logEvent, Logger.UserData, aMessage);
	}
}

/*******************************************************************************************************************/

void LogErrorFormattedExtended1(const char* aMessageFormat, ...) {
	#ifdef _DEBUG
	#define MESSAGE_SIZE 256
	va_list arguments;
	TLogEvent logEvent;
	char formattedMessage[MESSAGE_SIZE];

	memset(&logEvent, 0, sizeof(logEvent));

	va_start(arguments, aMessageFormat);
	vsprintf_s(formattedMessage, MESSAGE_SIZE, aMessageFormat, arguments);

	va_end(arguments);

	Logger.Function(&logEvent, formattedMessage, Logger.UserData);
	#endif
}