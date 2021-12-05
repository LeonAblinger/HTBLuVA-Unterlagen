/*************************************************************************************************************
File: Logger.h
Description:
  Test different methods for loggings.
*************************************************************************************************************/
#include <stdio.h>

#ifndef LOGGER_H
#define LOGGER_H

#ifdef _DEBUG
#define LOG1(message) printf("%s Line %3u %s\n", __FILE__, __LINE__, message)
#define LOG2(message) printf("%s Line %3u %s\n", __FILE__, __func__, __LINE__, message)
#define LogDebug(message) LogEvent_(__FILE__, __func__, __LINE__, LOG_LEVEL_DEBUG, message)

#else
#define LOG1(message)
#define LOG2(message)
#define LogEvent(message)

#endif

typedef enum
{
	LOG_LEVEL_ERROR,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DEBUG
} TLogLevel;

typedef struct
{
	char*		 FileName;
	char*		 FunctionName;
	unsigned int LineNo;
	TLogLevel	 LogLevel;
} TLogEvent;

typedef void (*TLoggerFunction)(TLogEvent* aLogEvent, char* aMessage, void* aUserData);

LogInit(void);
LogSetLogFunction(TLoggerFunction aFunction, void* aUserData);
void LogEvent_(char* aFileName, char* aFunctionName, unsigned int aLineNo, TLogLevel aLogLevel, char* aMessage);
void LogErrorFormatedExtended1(const char* aMessageFormat, ...);

#endif