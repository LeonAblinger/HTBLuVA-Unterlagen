/************************************************************************
File: HtlStddef.h
Description: Standard definitions for programs

************************************************************************/

#ifndef HTLSTDDEF_H
#define HTLSTDDEF_H

#ifndef F_CPU
#define F_CPU 16000000
#endif

#define PRIVATE static

typedef enum{
	EFALSE = 0,
	ETRUE = 1
} TBool;

void DelayMs(unsigned int aDelayMs);

void DelayUs(unsigned int aDelayUs);

#endif
