/*--------------------------------------------------------------------------------------------------------------------------------------------
File: Logger.c

Description:
	Test different methods for loggings on the PC.

--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "Logger.h"

typedef struct {
	TLoggerFunction Function;
	void*						UserData;
}TLogger;

TLogger Logger;		//gloabal Logger Variable

/*********************************************************************************
Function: LogInit

Parameters: none
**********************************************************************************/

void LogInit(void) {		//initialize Logger
	memset(&Logger, 0, sizeof(Logger));
}

/*********************************************************************************
Function: LogSetLogFunction

Parameters: - aFunction -> a Logger function
						- aUserData -> custom user data
**********************************************************************************/

void LogSetLogFunction(TLoggerFunction aFunction, void* aUserData) {
	Logger.Function = aFunction;
	Logger.UserData = aUserData;
}

/*********************************************************************************
Function: LogEvent_

Parameters: - aFileName			-> Name of the File where the Logger gets called
						- aFunctionName	-> Name of the Function where the Logger gets called
						- aLineNo				-> Number of the Line where the Logger gets called
						- aLogLevel			-> ERROR / INFO / WARNING / DEBUG
						- aMessage			-> custom message from user
**********************************************************************************/

void LogEvent_(const char* aFileName, const char* aFunctionName, unsigned int aLineNo, TLogLevel aLogLevel, const char* aMessage) {
	TLogEvent logEvent;

	if (!Logger.Function) {
		return;
	}

	memset(&logEvent, 0, sizeof(logEvent));

	logEvent.FileName = aFileName;
	logEvent.FunctionName = aFunctionName;
	logEvent.LineNo = aLineNo;
	logEvent.LogLevel = aLogLevel;

	if (Logger.Function) {
		Logger.Function(&logEvent, Logger.UserData, aMessage);
	}
}

/****************************************************************
Function: LogInit

Parameters: - aMessageFormat	-> format of the message
						- ...							-> unlimited following parameters
*****************************************************************/

void LogErrorFormattedExtended1(const char* aMessageFormat, ...) {		// Syntax "...": beliebig viele folgende Parameter
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