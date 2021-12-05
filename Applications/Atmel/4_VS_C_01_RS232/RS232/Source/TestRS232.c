/*************************************************************************************************************
* File: TestRS232.c
* Description:
*	Simple test of the RS232 interface.
*************************************************************************************************************/
#include <windows.h>
#include <stdio.h>
#include "RS232.h"

void
Test1(void);

void
TestEcho(void);

void
main(void)
{
	TestEcho();
}

void
Test1(void)
{
#define BUFFER_SIZE 20
	HANDLE comHandle;
	unsigned int  bytesReceived;
	unsigned char buffer[BUFFER_SIZE];

	comHandle = RS232Open("COM3", 9600);

	while (1)
	{
		bytesReceived = RS232Receive(comHandle, buffer, BUFFER_SIZE);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			printf("%s", buffer);
		}
	}
}

void
TestEcho(void)
{
#define BUFFER_SIZE 20
	HANDLE comHandle;
	unsigned int  bytesReceived;
	unsigned char buffer[BUFFER_SIZE + 1];

	comHandle = RS232Open("COM3", 9600);

	while (1)
	{
		RS232Write(comHandle, "Hallo", 6);

		bytesReceived = RS232Receive(comHandle, buffer, BUFFER_SIZE);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			printf("%s", buffer);
		}
		Sleep(200);
	}
}