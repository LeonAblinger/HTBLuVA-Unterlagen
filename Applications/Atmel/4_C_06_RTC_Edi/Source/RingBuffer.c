/************************************************************************
File: RingBuffer.c
Description: creates and handles a ring buffer
************************************************************************/

#include "RingBuffer.h"

struct RingBufferStruct {
  unsigned char readIndex;   // Index of the read position
  unsigned char writeIndex;  // Index of the write position
  unsigned char* buffer;     // Buffer for data content
  unsigned char size;        // Buffersize
};

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

void RingBufferDestroy(TRingBuffer aRingBuffer) {
  if (!aRingBuffer)
    return;

  if (aRingBuffer->buffer)
    free(aRingBuffer->buffer);

  free(aRingBuffer);
}

TBool RingBufferWrite(TRingBuffer aRingBuffer, unsigned char aByte) {
  unsigned char writeIndex = aRingBuffer->writeIndex;

  writeIndex++;
  if (writeIndex >= aRingBuffer->size)
		writeIndex = 0;
   
  if (writeIndex == aRingBuffer->readIndex)
    return EFALSE;

  aRingBuffer->buffer[aRingBuffer->writeIndex] = aByte;
  aRingBuffer->writeIndex = writeIndex;

  return ETRUE;
}

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
