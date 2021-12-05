/********************************************************************************************************************
File:	 RingBuffer.c
Project: RTC - RealTimeClock
Author:	 Leon Ablinger / AblL
********************************************************************************************************************/

#include "RingBuffer.h"

struct RingBufferStruct {
	unsigned char readIndex;
	unsigned char writeIndex;
	unsigned char* buffer;
	unsigned char size;
};

/*******************************************************************************************************************/

TRingBuffer RingBufferCreate(unsigned char aSize) {
	TRingBuffer ringBuffer;

	ringBuffer = (TRingBuffer)calloc(1, sizeof(struct RingBufferStruct));

	if (!ringBuffer)
	return NULL;

	ringBuffer->buffer = (unsigned char*)malloc(aSize);

	if (!ringBuffer->buffer) {
		RingBufferDestroy(ringBuffer);
		return NULL;
	}

	ringBuffer->size = aSize;

	return ringBuffer;
}

/*******************************************************************************************************************/

void RingBufferDestroy(TRingBuffer aRingBuffer) {
	if (!aRingBuffer)
	return;

	if (aRingBuffer->buffer)
	free(aRingBuffer->buffer);

	free(aRingBuffer);
}

/*******************************************************************************************************************/

TBool RingBufferWrite(TRingBuffer aRingBuffer, unsigned char aByte) {
	unsigned char writeIndex = aRingBuffer->writeIndex;

	writeIndex++;
	if (writeIndex >= aRingBuffer->size)
	
	if (writeIndex == aRingBuffer->readIndex)
	return EFALSE;

	aRingBuffer->buffer[aRingBuffer->writeIndex] = aByte;
	aRingBuffer->writeIndex = writeIndex;

	return ETRUE;
}

/*******************************************************************************************************************/

TBool RingBufferRead(TRingBuffer aRingBuffer, unsigned char* aByte) {
	unsigned char readIndex = aRingBuffer->readIndex;

	if (readIndex == aRingBuffer->writeIndex)
	return EFALSE;

	readIndex++;
	if (readIndex >= aRingBuffer->size)
	readIndex = 0;

	*aByte = aRingBuffer->buffer[aRingBuffer->readIndex];
	aRingBuffer->readIndex = readIndex;

	return ETRUE;
}
