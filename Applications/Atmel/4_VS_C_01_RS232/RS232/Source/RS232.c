/*************************************************************************************************************
* File: RS232.c
* Description:
*	Simple interface to the RS232 Win-API to 
*************************************************************************************************************/
#include <windows.h>
#include "RS232.h"

/************************************************************************************************************/
/*********************************** Declaration of private Functions ***************************************/
static void
RS232Config(
	HANDLE aRS232Handle,
	unsigned int aBaudrate);

/************************************************************************************************************/

HANDLE
RS232Open(
	char* aName,
	unsigned int aBaudRate)
{
	HANDLE comOpen;
	char* name;

	if (aName == NULL)
		name = DEFAULT_COM_NAME;
	else
		name = aName;

	comOpen = CreateFile(aName, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	
	RS232Config(comOpen, aBaudRate);

	return comOpen;
}

void 
RS232Close(
	HANDLE aRS232Handle)
{
	CloseHandle(aRS232Handle);
}

unsigned int
RS232Write(
	HANDLE aRS232Handle,
	unsigned char* aBuffer,
	unsigned int aSize)
{
	BOOL success;
	unsigned int aNoOfCharsWritten;

	success = WriteFile(aRS232Handle, aBuffer, aSize, &aNoOfCharsWritten, NULL);

	if (!success)
		return 0;

	return aNoOfCharsWritten;
}

unsigned int
RS232Receive(
	HANDLE aRS232Handle,
	unsigned char* aBuffer,
	unsigned int aSize)
{
	BOOL success;
	unsigned int bytesRead;

	success = ReadFile(aRS232Handle, aBuffer, aSize, &bytesRead, NULL);

	if (!success)
		return 0;

	return bytesRead;
}

/************************************************************************************************************/
/******************************************* Private Functions **********************************************/
static void
RS232Config(
	HANDLE aRS232Handle,
	unsigned int aBaudrate)
{
	DCB dcbSetting;

	GetCommState(aRS232Handle, &dcbSetting);

	dcbSetting.BaudRate = aBaudrate;

	SetCommState(aRS232Handle, &dcbSetting);
}