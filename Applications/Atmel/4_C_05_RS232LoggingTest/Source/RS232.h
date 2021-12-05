/************************************************************************
File: RS232.h
Description:
Driver for the serial RS232 interface of the ATMega644X microcontroller.
************************************************************************/

#ifndef RS232_H
#define RS232_H

typedef struct TRS232Struct * TRS232;

typedef struct {
	unsigned char ReceiveBufferSize;
	unsigned char SendBufferSize;
	unsigned int  Baudrate;
} TRS232Config;

typedef enum {
	ERS232_NO_0,
	ERS232_NO_1,
	ERS232_NO_LAST
} TRS232Number;

typedef enum {
	ERS232_ERROR_NONE,
	ERS232_ERROR
} TRS232Error;

TRS232
RS232Create(
	TRS232Number  aRS232Number,
	TRS232Config  aConfig,
	unsigned long aCpuClk );

void
RS232Destroy(
	TRS232 aRS232 );

unsigned char
RS232SendData(
	TRS232			sRS232,
	unsigned char * aBuffer,
	unsigned char	aSize );

unsigned char
RS232ReceiveData(
	TRS232			sRS232,
	unsigned char * aBuffer,
	unsigned char	aBufferSize );

TRS232Error
RS232GetLatestError(
	TRS232 Error );

#endif