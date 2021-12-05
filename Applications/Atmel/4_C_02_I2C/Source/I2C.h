/*********************************************************************************************************
File: I2C.h
Author: AblL / Leon Ablinger
Description:
  Definitions for the I2C (TWI) interface.
*********************************************************************************************************/

#include <avr/io.h>
#include "HtlStddef.h"

/********************************** Definition of public functions **************************************/
TBool
i2cInit(
	unsigned long aBitrate,
	unsigned long aClkFrequency );

TBool	
i2cWrite(
	unsigned char	aAdress,
	unsigned char * aBuffer,
	unsigned int	aSize );

TBool
i2cRead(
	unsigned char	aAdress,
	unsigned char * aBuffer,
	unsigned int	aSize );