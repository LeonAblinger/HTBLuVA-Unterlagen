/************************************************************************
File: RingBuffer.h
Description:
Thread / Interrupt safe ringbuffer for data transfer. The read
and write process can be interrupted at every assembler command.
************************************************************************/

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
