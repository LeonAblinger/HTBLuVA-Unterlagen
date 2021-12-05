/******************************************************************************************************
  File: HtlStddef.h
  Author: Leon Ablinger / AblL
  Description:
    Standard definitions for programs.
******************************************************************************************************/

#ifndef HTLSTDDEF_H
#define HTLSTDDEF_H

#ifndef F_CPU
#define F_CPU 16000000
#endif

#define PRIVATE static
typedef enum
{
  EFALSE = 0,
  ETRUE  = 1
} TBool;

void
delayMs( unsigned int aDelayMs );

void
delayUs( unsigned int aDelayUs );

#endif