/*
* TestRingbuffer.c
*
* Created: 18/12/2020 3:53:30 pm
* Author : Leon
*/

#include <avr/io.h>
#include "Ringbuffer.h"

unsigned int TestRingBuffer1();
unsigned int TestRingBuffer2();

int main(void)
{
	unsigned int errors;
	// Test-Cases
	errors = TestRingBuffer1();
	errors = TestRingBuffer2();
	
	while (1)
	{
	}
}

/**********************************************************************************
Function: TestRingbuffer1
Description:
Write 1 Byte and read 1 Byte, check the result.
Repeat this for 3 times of the size of the ringbuffer.
**********************************************************************************/
unsigned int
TestRingBuffer1() {
	unsigned char bufferSize = 4;
	unsigned int errors = 0;
	unsigned char readByteVal = 0x00;
	unsigned char *readByte = &readByteVal;
	TRingBuffer bufferCheck = RingBufferCreate(bufferSize);
	
	for ( int i = 0; i <= bufferSize*3; i++) {
		RingBufferWrite(bufferCheck, i);
		RingBufferRead(bufferCheck, readByte);
		if ( *readByte != i )
		errors++;
	}
	RingBufferDestroy(bufferCheck);
	return errors;
}

/**********************************************************************************
Function: TestRingbuffer2
Description:
Write Bytes until the buffer is full and read all Bytes, check the result.
Repeat this for so many times as the size of the ringbuffer.
**********************************************************************************/
unsigned int
TestRingBuffer2() {
	unsigned char bufferSize = 4;
	unsigned int errors = 0;
	unsigned char readByte[] = {0, 0, 0, 0};
	TRingBuffer bufferCheck = RingBufferCreate(bufferSize);
	
	for ( int i = 0; i <= bufferSize; i++)
		RingBufferWrite(bufferCheck, i);
	
	for ( int i = 0; i <= bufferSize; i++)
		RingBufferRead(bufferCheck, &readByte[i]);
	
	for ( int i = 0; i < bufferSize; i++) {
		if ( readByte[i] != i )
		errors++;
	}

	RingBufferDestroy(bufferCheck);
	return errors;
}