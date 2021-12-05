/************************************************************************
File: HtlStddef.c
Description: Standard definitions for programs

************************************************************************/

#include "HtlStddef.h"

#ifndef DEBUG
#include <util/delay.h>
#endif

void DelayMs(unsigned int aDelayMs){
	#ifdef DEBUG
	volatile unsigned long counter;
	volatile unsigned int help;
	for(counter = 0; counter < aDelayMs * 150UL; counter++) help++;
	#else
	_delay_ms(aDelayMs);
	#endif
}

void DelayUs(unsigned int aDelayUs){
	#ifdef DEBUG
	volatile unsigned long counter;
	volatile unsigned int help;
	for(counter = 0; counter < aDelayUs ; counter++) help++;
	#else
	_delay_us(aDelayUs);
	#endif
}