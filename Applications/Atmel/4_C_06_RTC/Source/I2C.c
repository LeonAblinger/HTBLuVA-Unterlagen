/********************************************************************************************************************
File:	 I2C.c
Project: RTC - RealTimeClock
Author:	 Leon Ablinger / AblL
********************************************************************************************************************/

#include "HtlStddef.h"
#include <avr/io.h>
#include "twi.h"

unsigned char I2CPrescalerValues[] = {1, 4, 16, 64};

static TBool I2CStart(void);
static void I2CStop(void);
static TBool I2CSendAddress(unsigned char aAddress);
static TBool I2CSendByte(unsigned char aByte);
static TBool I2CReadByte(unsigned char * aBuffer);
static TBool I2CReadLastByte(unsigned char * aBuffer);

/*******************************************************************************************************************/

TBool I2CInit(unsigned int aBitrate, unsigned long aClkFrequency){
	unsigned char tws;
	unsigned long tmp;

	for(tws = 0; tws < sizeof(I2CPrescalerValues); tws++){
		tmp =  ((aClkFrequency/aBitrate)-16)/(2*I2CPrescalerValues[tws]);
		
		if(tmp < 256){
			PORTC |= (1 << PORTC0) | (1 << PORTC1);
			DDRC &= ~(1 << DDC0) & ~(1 << DDC1);
			TWSR |= (tmp <<TWPS0);
			TWBR = aBitrate;
			break;
		}
	}
	
	if(tmp >= 256){
		return EFALSE;
	}
	
	return ETRUE;
}

/*******************************************************************************************************************/

TBool I2CWrite(unsigned char aSlaveAddress, unsigned char * aBuffer, unsigned int aSize){
	
	unsigned int i;
	
	if(!I2CStart()){
		return EFALSE;
	}
	
	if(!I2CSendAddress(aSlaveAddress & TW_WRITE)){
		I2CStop();
		return EFALSE;
	}
	
	for(i = 0; i < aSize; i++){
		
		if(!I2CSendByte(aBuffer[i])){
			I2CStop();
			return EFALSE;
		}
	}
	
	I2CStop();
	
	return ETRUE;
}

/*******************************************************************************************************************/

TBool I2CRead(unsigned char aSlaveAddress, unsigned char * aBuffer, unsigned int aSize){
	unsigned int i;
	
	if(!I2CStart()){
		return EFALSE;
	}
	
	if(!I2CSendAddress(aSlaveAddress | TW_READ)){
		I2CStop();
		return EFALSE;
	}
	
	for(i = 0; i < aSize - 1; i++){
		if(!I2CReadByte(&aBuffer[i])){
			I2CStop();
			return EFALSE;
		}
	}
	
	if (!I2CReadLastByte(&aBuffer[aSize - 1])) {
		I2CStop();
		return EFALSE;
	}
	
	I2CStop();
	
	return ETRUE;
}

/*******************************************************************************************************************/

static TBool I2CStart(void){
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	
	while(!(TWCR & (1 << TWINT)));
	
	if((TWSR & TW_STATUS_MASK) != TW_START && (TWSR & TW_STATUS_MASK) != TW_REP_START){
		return EFALSE;
	}
	
	return ETRUE;
}

/*******************************************************************************************************************/

static void I2CStop(void){
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/*******************************************************************************************************************/

static TBool I2CSendAddress(unsigned char aAddress) {
	TWDR = aAddress;

	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));

	if (aAddress & TW_READ) {
		if ((TWSR & TW_STATUS_MASK) != TW_MR_SLA_ACK)
		return EFALSE;
		} else {
		if ((TWSR & TW_STATUS_MASK) != TW_MT_SLA_ACK)
		return EFALSE;
	}

	return ETRUE;
}

/*******************************************************************************************************************/

static TBool I2CSendByte(unsigned char aByte){
	TWDR = aByte;
	
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	while(!(TWCR & (1 << TWINT)));
	
	if((TWSR & TW_STATUS_MASK) != TW_MT_DATA_ACK){
		return EFALSE;
	}
	
	return ETRUE;
}

/*******************************************************************************************************************/

static TBool I2CReadByte(unsigned char * aBuffer){
	
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
	while(!(TWCR & (1 << TWINT)));
	
	if((TWSR & TW_STATUS_MASK) != TW_MR_DATA_ACK){
		return EFALSE;
	}
	
	*aBuffer = TWDR;
	
	return ETRUE;
}

/*******************************************************************************************************************/

static TBool I2CReadLastByte(unsigned char * aBuffer){
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	while(!(TWCR & (1 << TWINT)));
	
	if((TWSR & TW_STATUS_MASK) != TW_MR_DATA_NACK){
		return EFALSE;
	}
	
	*aBuffer = TWDR;
	
	return ETRUE;
}