/*************************************************************************************************************
File: Logger.c
Description:
  Test different methods for loggings.
*************************************************************************************************************/
#include <stdarg.h>
#include <string.h>
#include "Logger.h"

typedef struct
{
	TLoggerFunction Function;
	void* UserData;
} TLogger;

TLogger Logger;

LogInit(void)
{
	memset(&Logger, 0, sizeof(Logger));
}

LogSetLogFunction(
	TLoggerFunction aFunction,
	void* aUserData)
{
	Logger.Function = aFunction;
	Logger.UserData = aUserData;
}

void
LogEvent_(
	char*		 aFileName,
	char*		 aFunctionName,
	unsigned int aLineNo,
	TLogLevel	 aLogLevel,
	char*		 aMessage)
{
	TLogEvent logEvent;

	memset(&logEvent, 0, sizeof(logEvent));

	logEvent.FileName = aFileName;
	logEvent.FunctionName = aFunctionName;
	logEvent.LineNo = aLineNo;
	logEvent.LogLevel = aLogLevel;

	Logger.Function(&logEvent, aMessage, Logger.UserData);
}

void
LogErrorFormatedExtended1(
	const char* aMessageFormat,
	...)
{
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