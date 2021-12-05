/*********************************************************************************************************
File: I2C.c
Author: AblL / Leon Ablinger
Description:
  I2C (TWI) interface for the AtMega644XX microcontroller.
Connections:
  - SDA: PC0
  - SCL: PC1
*********************************************************************************************************/

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "I2C.h"
#include "twi.h"
#include "HtlStddef.h"

/******************************************* Global variables *******************************************/
#define TW_WRITE	(~( 1 << 0 ))
#define TW_READ		1
const unsigned char i2cPrescalerValues[] = { 1, 4, 16, 64 };
	
/*********************************** Declaration of private functions ***********************************/
static TBool i2cStart( void );
static void i2cStop( void );
static TBool i2cSendAddress( unsigned char aAddress );
static TBool i2cSendByte( unsigned char aByte );
static TBool i2cReadByte( unsigned char * aBuffer );
static TBool i2cReadLastByte( unsigned char * aBuffer );

/******************************************* Public functions *******************************************/
/*********************************************************************************************************
Function: i2cInit
Description:
  Initialize the I2C (TWI) interface. Calculates prescaler value (TWPS) and
  bit rate register (TWBR) value.
Parameters:
  - aBitrate	  - Given bitrate of the i2c bus
  - aClkFrequency - Frequency-Clock
*********************************************************************************************************/
TBool
i2cInit(
	unsigned long aBitrate,
	unsigned long aClkFrequency )
{
	// TWBR <= 255
	unsigned long twb;
	unsigned char tws;
	
	for( tws = 0; tws < sizeof(i2cPrescalerValues); tws++ )
	{
		twb = (( aClkFrequency / aBitrate ) - 16 ) / ( 2 * i2cPrescalerValues[tws] );
		
		if( twb <= 255 )
			break;
	}
	
	DDRC &= (( 1 << DDC0 ) | ( 1 << DDC1 ));
	/* Switch on pullup resistors */
	PORTC |= ( 1 << PC0 ) | ( 1 << PC1 );
	
	TWBR |= ( twb << 0 );
	TWSR |= ( tws << TWPS0 );
	
	return ETRUE;
}

/*********************************************************************************************************
Function: i2cWrite
Description:
  Writes a byte to the given address of a I2C device and filters faulty transmissions.
Parameters:
  - aSlaveAdress - The address of the I2C device
  - aBuffer		 - The data which should be transfered
  - aSize		 - The size of the buffer
*********************************************************************************************************/
TBool
i2cWrite(
	unsigned char	aSlaveAdress,
	unsigned char * aBuffer,
	unsigned int	aSize )
{
	unsigned int i;
	
	if( !i2cStart() )
		return EFALSE;
		
	if( !i2cSendAddress( aSlaveAdress & TW_WRITE ))
	{
		i2cStop();
		return EFALSE;
	}
	
	for( i = 0; i < aSize; i++)
	{
		if( !i2cSendByte( aBuffer[i] ))
		{
			i2cStop();
			return EFALSE;
		}
	}
	
	i2cStop();
	return EFALSE;
}

/*********************************************************************************************************
Function: i2cRead
Description:
  Reads some bytes from a I2C device.
Parameters:
  - aAddress - The address of the I2C device which should be read
  - aBuffer	 - The variable in which the data should be stored
  - aSize	 - The size of the read data
*********************************************************************************************************/
TBool
i2cRead(
	unsigned char	aAddress,
	unsigned char * aBuffer,
	unsigned int	aSize )
{
	unsigned int i;
	
	if( !i2cStart() )
	return EFALSE;
	
	if( !i2cSendAddress( aAddress | TW_READ ))
	{
		i2cStop();
		return EFALSE;
	}
	
	for( i = 0; i < aSize - 1; i++)
	{
		if( !i2cReadByte( aBuffer + i ))
		{
			i2cStop();
			return EFALSE;
		}
	}

	if( !i2cReadLastByte( aBuffer + i ))
	{
		i2cStop();
		return EFALSE;
	}

	i2cStop();
	return EFALSE;
}

/******************************************* Private functions ******************************************/
/*********************************************************************************************************
Function: i2cStart
Description:
  Starts the TWI (I2C) interface & transmission.
*********************************************************************************************************/
static TBool
i2cStart( void )
{
	TWCR = ( 1 << TWINT ) | ( 1 << TWSTA ) | ( 1 << TWEN );
	
	while( !( TWCR & ( 1 << TWINT )));
	
	if(( TWSR & TW_STATUS_MASK ) != TW_START )
		return EFALSE;
		
	return ETRUE;
}

/*********************************************************************************************************
Function: i2cStop
Description:
  Stops the TWI (I2C) interface & transmission.
*********************************************************************************************************/
static void
i2cStop( void )
{
	TWCR = ( 1 << TWINT ) | ( 1 << TWSTO ) | ( 1 << TWEN );
}

/*********************************************************************************************************
Function: i2cSendAddress
Description:
  Sends the address to the TWD register to be sent to the device.
Parameters:
  - aAddress - The address which should be loaded
*********************************************************************************************************/
static TBool
i2cSendAddress(
	unsigned char aAddress )
{
	if(( TWSR != TW_START ) | ( TWSR != TW_REP_START ))
		return EFALSE;
		
	TWDR = aAddress;
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
	
	while( !( TWCR & ( 1 << TWINT )));
	
	if(( TWSR & 0xF8 ) != TW_MT_SLA_ACK )
		return EFALSE;
		
	return ETRUE;
}

/*********************************************************************************************************
Function: i2cSendByte
Description:
  Sends a single byte to a device. Other parameters were defined earlier.
Parameters:
  - aByte - The byte which should be sent to the device
*********************************************************************************************************/
static TBool
i2cSendByte(
	unsigned char aByte )
{
	if(( TWSR != TW_START ) | ( TWSR != TW_REP_START ))
		return EFALSE;
		
	TWDR = aByte;
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
	
	while( !( TWCR & ( 1 << TWINT )));
	
	if(( TWSR & 0xF8 ) != TW_MT_DATA_ACK )
		return EFALSE;
		
	return ETRUE;
}

/*********************************************************************************************************
Function: i2cReadByte
Description:
  Reads a single byte from a device.
Parameters:
  - aBuffer - The data pointer in which the data should be stored
*********************************************************************************************************/
static TBool
i2cReadByte(
	unsigned char * aBuffer )
{
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN ) | ( 1 << TWEA );
	
	while( !( TWCR & ( 1 << TWINT )));
	
	if(( TWSR & 0xF8 ) != TW_MR_DATA_ACK )
		return EFALSE;
	
	*aBuffer = TWDR;
	
	return ETRUE;
}

/*********************************************************************************************************
Function: i2cReadLastByte
Description:
  Reads the last byte from a device. Acknowledge bit not sent.
Parameters:
  - aBuffer - The data pointer in which the data should be stored
*********************************************************************************************************/
static TBool
i2cReadLastByte(
	unsigned char * aBuffer )
{
	TWCR = (( 1 << TWINT ) | ( 1 << TWEN )) & ~( 1 << TWEA );
	
	while( !( TWCR & ( 1 << TWINT )));
	
	if(( TWSR & 0xF8 ) != TW_MR_DATA_NACK )
		return EFALSE;
	
	*aBuffer = TWDR;
	
	return ETRUE;
}