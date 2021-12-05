/************************************************************************
File: RingBuffer.c
Description:
Thread / Interrupt safe ringbuffer for data transfer. The read
and write process can be interrupted at every assembler command.
************************************************************************/

#include "RingBuffer.h"

struct RingBufferStruct {
	unsigned char readIndex;	// Index of the read position
	unsigned char writeIndex;	// Index of the write position
	unsigned char* buffer;	// Buffer for data content
	unsigned char size;		// Size of the buffer
};

TRingBuffer RingBufferCreate(unsigned char aSize) {
	TRingBuffer ringBuffer;

	/* Allocate memory and set the content to 0 */
	ringBuffer = calloc( 1, sizeof(struct RingBufferStruct) );

	if (!ringBuffer)
		return NULL;
	
	ringBuffer->buffer = malloc( aSize );
	if ( !ringBuffer->buffer ) {
		RingBufferDestroy(ringBuffer);
		return NULL;
	}
	
	ringBuffer->size = aSize;
	return ringBuffer;
}

void RingBufferDestroy(TRingBuffer aRingBuffer) {
	// assert( aRingBuffer );

	if ( !aRingBuffer )
		return;

	if ( aRingBuffer->buffer )
		free( aRingBuffer->buffer );
	
	free ( aRingBuffer );
}

TBool RingBufferWrite(TRingBuffer aRingBuffer, unsigned char aByte) {
	unsigned char locWriteIndex = aRingBuffer->writeIndex;
	
	locWriteIndex++;
	
	if ( locWriteIndex > aRingBuffer->size )
		locWriteIndex = 0;
	
	if ( locWriteIndex == aRingBuffer->readIndex )
		return EFALSE;
	
	aRingBuffer->buffer[aRingBuffer->writeIndex] = aByte;
	aRingBuffer->writeIndex = locWriteIndex;
	
	return ETRUE;
}

TBool RingBufferRead(TRingBuffer aRingBuffer, unsigned char* aByte) {
	unsigned char locReadIndex = aRingBuffer->readIndex;

	if ( locReadIndex == aRingBuffer->writeIndex )
		return EFALSE;
	
	locReadIndex++;
	
	if ( locReadIndex > aRingBuffer->size )
		locReadIndex = 0;

	*aByte = aRingBuffer->buffer[aRingBuffer->readIndex];
	aRingBuffer->readIndex = locReadIndex;
	
	return ETRUE;
}