#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdlib.h>

#include "HtlStddef.h"

typedef struct RingBufferStruct* TRingBuffer;

TRingBuffer RingBufferCreate(unsigned char aSize);

void RingBufferDestroy(TRingBuffer aRingBuffer);

TBool RingBufferWrite(TRingBuffer aRingBuffer, unsigned char aByte);

TBool RingBufferRead(TRingBuffer aRingBuffer, unsigned char* aByte);

#endif
