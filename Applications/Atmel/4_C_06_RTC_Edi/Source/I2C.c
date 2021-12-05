/*
 * I2CTest.c
 * Description:
 *    I2C (TWI) interface for the AtMega644X micro controller
 *
 * Created: 23.10.2020 14:29:17
 * Author : Edin Vilic
 *  
 * Connections:
 *  SDA: PC1
 *  SCL: PC0
 */ 

#include "HtlStddef.h"
#include <avr/io.h>
#include "twi.h"

/*#define TW_WRITE (~(1 << 0))
#define TW_READ (1)*/

unsigned char I2CPrescalerValues[] = {1, 4, 16, 64};

//declaration of private functions
static TBool I2CStart(void);
static void I2CStop(void);
static TBool I2CSendAddress(unsigned char aAddress);
static TBool I2CSendByte(unsigned char aByte);
static TBool I2CReadByte(unsigned char * aBuffer);
static TBool I2CReadLastByte(unsigned char * aBuffer);

//Declarations of public functions



//definition of public functions

/************************************************************************
  Name: I2CInit
  Parameters:
    - aBitrate: defines the Bitrate to send the data with
    - aClkFrequency: defines the Frequency wuth whih the Clk-Bus is running
************************************************************************/


TBool I2CInit(unsigned int aBitrate, unsigned long aClkFrequency){
	//Calculate Prescaler value (TWPS) and bit rate register (TWBR) value
	//TWBR < 256
	
	unsigned char tws;
	unsigned long tmp;
	
	//unsigned long twbr;
	//unsigned int twps;
	
	for(tws = 0; tws < sizeof(I2CPrescalerValues); tws++){
		tmp =  ((aClkFrequency/aBitrate)-16)/(2*I2CPrescalerValues[tws]); //(aClkFrequency/(16 + 2 * TWBR * I2CPrescalerValues[tws]));
		
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

/*TBool I2CInit(unsigned long aBitrate, unsigned long aClkFrequency){
//Calculate Prescaler value (TWPS) and bit rate register (TWBR) value
//TWBR < 256
  
  unsigned char tws;
  unsigned long tmp;
  
  //unsigned long twbr;
  //unsigned int twps;
  
  for(tws = 0; tws < sizeof(I2CPrescalerValues); tws++){
    tmp =  ((aClkFrequency/aBitrate)-16)/(2*I2CPrescalerValues[tws]); //(aClkFrequency/(16 + 2 * TWBR * I2CPrescalerValues[tws]));
    
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
}*/

/************************************************************************
  Name: I2CWrite
  Description:
    Writes Bytes to the Data Bus
  Parameters:
    - aSlaveAddress: Address of the slave we want to communicate with
    - aBuffer: the data we want to write on the Data bus
    - aSize: Size of the amount of Bytes we want to write
************************************************************************/

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

/************************************************************************
  Name: I2CRead
  Description:
    Reads Bytes from the Data Bus
  Parameters:
    - aSlaveAddress: Address of the slave we want to communicate with
    - aBuffer: the data we want to read from the Data bus
    - aSize: Size of the amount of Bytes we want to read
************************************************************************/

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

/******
Definition of private functions
*****/

/************************************************************************
  Name: I2CStart
  Description:
    Starts the data-transfer for write and read operations
  Parameters:
    - none
************************************************************************/

static TBool I2CStart(void){
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
  
  while(!(TWCR & (1 << TWINT)));
  if((TWSR & TW_STATUS_MASK) != TW_START && (TWSR & TW_STATUS_MASK) != TW_REP_START){
    return EFALSE;
  }
  
  return ETRUE;
}

static void I2CStop(void){
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/************************************************************************
  Name: I2CStart
  Description:
    Sends the Address to the Data bus
  Parameters:
    - aAdress: the Address you want to write onto the Data bus
************************************************************************/

static TBool I2CSendAddress(unsigned char aAddress) {
	TWDR = aAddress;

	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)))
	;

	// Check wether Slave successfully acknoweledged
	if (aAddress & TW_READ) {
		// Check for Master RECEIVE Slave Acknowledge
		if ((TWSR & TW_STATUS_MASK) != TW_MR_SLA_ACK)
		return EFALSE;
		} else {
		// Check for Master TRANSMIT Slave Acknowledge
		if ((TWSR & TW_STATUS_MASK) != TW_MT_SLA_ACK)
		return EFALSE;
	}

	return ETRUE;
}


/************************************************************************
  Name: I2CSendByte
  Description:
    Send a Byte to the selected Address
  Parameters:
    - aByte: the Byte you want to write onto the Data bus
************************************************************************/

static TBool I2CSendByte(unsigned char aByte){
  TWDR = aByte;
  
  TWCR = (1 << TWINT) | (1 << TWEN);
  
  while(!(TWCR & (1 << TWINT)));
  
  if((TWSR & TW_STATUS_MASK) != TW_MT_DATA_ACK){
    return EFALSE;
  }
  
  return ETRUE;
}

/************************************************************************
  Name: I2CReadByte
  Description:
    Reads a Byte from the DATA bus
  Parameters:
    - aBuffer: the buffer where the read bytes are stored in
************************************************************************/

static TBool I2CReadByte(unsigned char * aBuffer){
   
   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
   
   while(!(TWCR & (1 << TWINT)));
  
  
   if((TWSR & TW_STATUS_MASK) != TW_MR_DATA_ACK){
     return EFALSE;
   }
   
   *aBuffer = TWDR;
  
  return ETRUE;
}

static TBool I2CReadLastByte(unsigned char * aBuffer){
  TWCR = (1 << TWINT) | (1 << TWEN);
  
  while(!(TWCR & (1 << TWINT)));
  
  if((TWSR & TW_STATUS_MASK) != TW_MR_DATA_NACK){
    return EFALSE;
  }
  
  *aBuffer = TWDR;
  
  return ETRUE;
}