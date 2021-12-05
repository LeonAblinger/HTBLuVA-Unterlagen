#include "HtlStddef.h"
#include "Ringbuffer.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#ifndef RS232_H
#define RS232_H

typedef struct TRs232Struct * TRs232;

typedef struct{
	unsigned char SendBufferSize;
	unsigned char RecieveBufferSize;
	unsigned int BaudRate;
}TRs232Config;

typedef enum{
	ERS232_NO_0,
	ERS232_NO_1,
	ERS232_NO_LAST
}TRs232Number;

typedef enum{
	ERS232_ERROR_NONE,
	ERS232_ERROR
}TRs232Error;

void Rs232ConfigDefaultInit(TRs232Config * Config);

TRs232 Rs232Create(TRs232Number aRs232Number, unsigned long aCpuClk, TRs232Config aConfig);

void Rs232Destroy(TRs232 aRs232);

unsigned char Rs232SendData(TRs232 aRs232, unsigned char * aBuffer, unsigned char aSize);

unsigned char Rs232RecieveData(TRs232 aRs232, unsigned char * aBuffer, unsigned char aBufferSize);
#endif