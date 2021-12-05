/******************************************************************************************************
  File: LCDTest.c
  Author: Leon Ablinger / AblL
******************************************************************************************************/


#include <avr/io.h>
#include "LCD.h"
#include "HtlStddef.h"
#include "LcdConstants.h"

int main(void)
{
	lcdInit();
	
	delayMs(250);
	
	char* world = "UwU";
	lcdSetCursor(1, 1);
	delayMs(100);
	lcdWrite(world, 3);
}