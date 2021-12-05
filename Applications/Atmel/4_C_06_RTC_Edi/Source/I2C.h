#ifndef I2C_H
#define I2C_H

#include "HtlStddef.h"
#include "Logger.h"
#include "twi.h"
#include <avr/io.h>

TBool I2CWrite(unsigned char aSlaveAddress, unsigned char * aBuffer, unsigned int aSize);
TBool I2CRead(unsigned char aSlaveAddress, unsigned char * aBuffer, unsigned int aSize);
TBool I2CInit(unsigned int aBitrate, unsigned long aClkFrequency);

#endif
