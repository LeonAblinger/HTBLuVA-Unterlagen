/********************************************************************************************************************
File:	 Logger.h
Project: RTC - RealTimeClock
Author:	 Leon Ablinger / AblL
********************************************************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_DEBUG

#ifndef LOGGER_H
#define LOGGER_H

#ifdef _DEBUG
#define LOG1(message) printf("%s | Line: %4u | msg: %s\n",__FILE__,__LINE__,message)
#define LOG2(message) printf("FILE: %s | FUNC: %s | LINE: %4u | MSG: %s\n",__FILE__,__func__,__LINE__,message)
#endif

#ifdef LOG_DEBUG
#define LogDebug(message) LogEvent_(__FILE__,__func__,__LINE__,LOG_LEVEL_DEBUG,message)
#define LogInfo(message) LogEvent_(__FILE__,__func__,__LINE__,LOG_LEVEL_INFO,message)

#else

#define LOG1(message)
#define LOG2(message)
#define LogDebug(message)
#define LogInfo(message)

#endif

#define LogError(message) LogEvent_(__FILE__,__func__,__LINE__,LOG_LEVEL_ERROR,message)

typedef enum {
	LOG_LEVEL_ERROR = 4,
	LOG_LEVEL_WARNING = 3,
	LOG_LEVEL_INFO = 2,
	LOG_LEVEL_DEBUG = 1
}TLogLevel;

typedef struct {
	const char*		fileName;
	const char*		functionName;
	unsigned int	lineNo;
	TLogLevel		logLevel;
} TLogEvent;


void LogEvent_(const char* aFileName, const char* aFunctionName, unsigned int aLineNo, TLogLevel aLogLevel, const char* aMessage);

typedef void (*TLoggerFunction)(TLogEvent* logEvent, void* userData, const char* message);

void initLog(void);

void setLogFunction(TLoggerFunction aFunction, void* aUserData);

void LogErrorFormattedExtended1(const char* aMessageFormat, ...);

#endif