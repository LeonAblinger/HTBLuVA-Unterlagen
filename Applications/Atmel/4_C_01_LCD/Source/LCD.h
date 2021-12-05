/******************************************************************************************************
  File: LCD.c
  Author: Leon Ablinger / AblL
  Description:
    Driver for an alpha-numeric LCD-Display.
  Restrictions:
    Microprocessor: ATMega644P
	Only support for 4-bit interface
******************************************************************************************************/

#ifndef LCD_H
#define LCD_H
#endif

#include "HtlStddef.h"

/********************************** Definitions of public funtions ***********************************/

void
lcdInit();

void
lcdWrite(
  char *       aBuffer,
  unsigned int aSize
  );
  
void
lcdWriteChar( unsigned char aCharacter );

void
lcdClear();

TBool
lcdSetCursor(
  unsigned char aColumn,
  unsigned char aRow
  );