/*************************************************************************************************************
* File: RS232.h
* Description:
*
*************************************************************************************************************/
#ifndef RS232_H
#define RS232_H

#include <windows.h>

#define DEFAULT_COM_NAME "COM4"

HANDLE
RS232Open(
	char* aName,
	unsigned int aBaudRate);

void
RS232Close(
	HANDLE aRS232Handle);

unsigned int
RS232Write(
	HANDLE aRS232Handle,
	unsigned char* aBuffer,
	unsigned int aSize);

unsigned int
RS232Receive(
	HANDLE aRS232Handle,
	unsigned char* aBuffer,
	unsigned int aSize);

#endif