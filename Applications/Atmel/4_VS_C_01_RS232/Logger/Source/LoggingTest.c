/*************************************************************************************************************
File: LoggingTest.c
Description:
  Test different methods for loggings.
*************************************************************************************************************/
#include <stdio.h>
#include <Windows.h>
#include "Logger.h"

void
LogTest1(void);

void
LogTest2(void);

void
main(void)
{
	//LOG1("mei först lohging");
	//LOG2("mei fank lohging");

	//LogTest1();
	LogTest2();
}

void
TestLogFunction1(
	TLogEvent* aLogEvent,
	char* aMessage,
	void* aUserData)
{
	if (aLogEvent->LogLevel == LOG_LEVEL_DEBUG)
		printf("\nDEBUG: \nFile: %s \nFunction: %s \nLine: %u \nMessage: %s \n",
			aLogEvent->FileName, aLogEvent->FunctionName, aLogEvent->LineNo, aMessage);
}

void
TestLogFunction2(
	TLogEvent* aLogEvent,
	char* aMessage,
	void* aUserData)
{
	printf(aMessage);
}

void
LogTest1(void)
{
	LogInit();
	LogSetLogFunction(TestLogFunction1, NULL);

	LogDebug("Mei föhrst deback lohging");
}

void
LogTest2(void)
{
	unsigned int var1 = 3;
	char* text = "BlaBla";

	LogInit();
	LogSetLogFunction(TestLogFunction2, NULL);

	LogErrorFormatedExtended1("My first variable logging: Var1 = %u Comment = %s", var1, text);
}