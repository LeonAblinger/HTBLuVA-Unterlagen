/************************************************************************
File: RS232.c
Description:
Driver for the serial RS232 interface of the ATMega644X microcontroller.
************************************************************************/

#include "RingBuffer.h"
#include "RS232.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

struct TRS232Struct {
	TRS232Number RS232Number;
	TRingBuffer	 SendBuffer;
	TRingBuffer  ReceiveBuffer;
};

/************************************************************************
Static variables
************************************************************************/
static TRS232 RS232[ ERS232_NO_LAST ] = { NULL, NULL };

/************************************************************************
Declaration of private functions
************************************************************************/
static void
RS232InitCon0(
	TRS232		   aRS232,
	unsigned long  aCpuClk,
	TRS232Config * aConfig );

static void
RS232InitCon1(
	TRS232		   aRS232,
	unsigned long  aCpuClk,
	TRS232Config * aConfig );

unsigned int
RS232CalculateBaudrateRegValue(
	unsigned long aCpuClk,
	unsigned int  Baudrate,
	TBool       * aDoubleSpeed );

/***********************************************************************/

/************************************************************************
Function: RS232Create
Description:
	The created RS232 object must be destroyed with the function
	RS232 destroy if it will not be used anymore.
Parameters:
	aRS232Number - The number of the used hardware interface
	aCpuClk		 - The CPU clock
	aConfig		 - The created config to be used
Return:
	The created object - rs232 - if initialization failed - NULL
************************************************************************/
TRS232
RS232Create(
	TRS232Number  aRS232Number,
	TRS232Config  aConfig,
	unsigned long aCpuClk )
{
	TRS232 rs232;
	
	if ( aRS232Number >= ERS232_NO_LAST )
		return NULL;
	
	rs232 = calloc( 1, sizeof( struct TRS232Struct ));
	if ( rs232 == NULL )
		return NULL;
	
	rs232->RS232Number	 = aRS232Number;
	rs232->SendBuffer	 = RingBufferCreate( aConfig.SendBufferSize );
	rs232->ReceiveBuffer = RingBufferCreate( aConfig.ReceiveBufferSize );
	
	if ( !rs232->SendBuffer || !rs232->ReceiveBuffer )
	{
		RS232Destroy( rs232 );
		return NULL;
	}
	
	cli(); // Disable all interrupts
	
	switch ( aRS232Number )
	{
		case ERS232_NO_0:
		default:
			RS232InitCon0( rs232, aCpuClk, &aConfig );
			break;
		case ERS232_NO_1:
			RS232InitCon1( rs232, aCpuClk, &aConfig );
			break;
	}
	
	if ( RS232[aRS232Number] )
		RS232Destroy( RS232[aRS232Number] );
	
	RS232[aRS232Number] = rs232;
	
	sei(); // Enable all interrupts
	
	return rs232;
}

/************************************************************************
Function: RS232Destroy
Description:
	Destroys the given RS232 object and frees its memory.
Parameters:
	aRS232 - 
Return:
	The created object - rs232 - if initialization failed - NULL
************************************************************************/
void
RS232Destroy(
	TRS232 aRS232 )
{
	if ( !aRS232 ) return;
	
	cli();
	
	if ( aRS232->SendBuffer )
		RingBufferDestroy( aRS232->SendBuffer );
	if ( aRS232->ReceiveBuffer )
		RingBufferDestroy( aRS232->ReceiveBuffer );
	
	switch( aRS232->RS232Number )
	{
		case ERS232_NO_0:
		default:
			UCSR0B = 0;
			break;
		case ERS232_NO_1:
			UCSR1B = 0;
			break;
	}
	
	RS232[ aRS232->RS232Number ] = NULL;
	free( aRS232 );
	sei();
}

unsigned char
RS232SendData(
	TRS232			aRS232,
	unsigned char * aBuffer,
	unsigned char	aSize )
{
	unsigned char byteNo;
	
	for ( byteNo = 0; byteNo < aSize; byteNo++ )
	{
		if ( !RingBufferWrite( aRS232->SendBuffer, aBuffer[byteNo] )) break;
	}
	
	if ( byteNo )
	{
		switch ( aRS232->RS232Number )
		{
			case ERS232_NO_0:
				UCSR0B |= ( 1 << UDRIE0 );
				break;
			
			case ERS232_NO_1:
				UCSR1B |= ( 1 << UDRIE1 );
				break;
		}
	}
	
	
	return byteNo;
}

unsigned char
RS232ReceiveData(
	TRS232			aRS232,
	unsigned char * aBuffer,
	unsigned char	aBufferSize)
{
	unsigned int data;
	unsigned char i;
	
	for ( i = 0; i < aBufferSize; i++ )
	{
		if ( RingBufferRead( aRS232->ReceiveBuffer, &data ))
			aBuffer[i] = data;
		else
			break;
	}
	return i;
}

TRS232Error
RS232GetLatestError(
	TRS232 Error )
{
}

/************************************************************************
Definition of private functions
************************************************************************/
static void
RS232InitCon0(
	TRS232		   aRS232,
	unsigned long  aCpuClk,
	TRS232Config * aConfig )
{
	TBool doubleSpeed; // U2X bit int ... register
	
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	
	UBRR0 = RS232CalculateBaudrateRegValue( aCpuClk, aConfig->Baudrate, &doubleSpeed );
	
	if ( doubleSpeed )
		UCSR0A |= ( 1 << U2X0 );

	UCSR0C |= ( 3 << UCSZ00 );
	UCSR0B |= ( 1 << RXCIE0 ) | ( 1 << RXEN0 ) | ( 1 << TXEN0 );
}

static void
RS232InitCon1(
TRS232		   aRS232,
unsigned long  aCpuClk,
TRS232Config * aConfig )
{
	TBool doubleSpeed; // U2X bit int ... register
	
	UCSR1A = 0;
	UCSR1B = 0;
	UCSR1C = 0;
	
	UBRR0 = RS232CalculateBaudrateRegValue( aCpuClk, aConfig->Baudrate, &doubleSpeed );
	
	if ( doubleSpeed )
	UCSR1A |= ( 1 << U2X1 );

	UCSR1C |= ( 3 << UCSZ10 );
	UCSR1B |= ( 1 << RXCIE1 ) | ( 1 << RXEN1 ) | ( 1 << TXEN1 );
}

unsigned int
RS232CalculateBaudrateRegValue(
	unsigned long aCpuClk,
	unsigned int  Baudrate,
	TBool       * aDoubleSpeed )
{
	unsigned int ubrr;
	
	ubrr = ( aCpuClk / ( 16UL * Baudrate ) - 1 );
	
	*aDoubleSpeed = EFALSE;
	
	if ( ubrr > 4096 ) {
		*aDoubleSpeed = ETRUE;
		ubrr = ubrr / 2;
	}

	return ubrr;
}

ISR( USART0_UDRE_vect )
{
	unsigned char data;
	
	if ( RingBufferRead( RS232[ ERS232_NO_0 ]->SendBuffer, &data ))
		UDR0 = data;
	else
		UCSR0B &= ~( 1 << UDRIE0 );
}

ISR( USART1_UDRE_vect )
{
	unsigned char data;
	
	if ( RingBufferRead( RS232[ ERS232_NO_1 ]->SendBuffer, &data ))
	UDR1 = data;
	else
	UCSR1B &= ~( 1 << UDRIE1 );
}

ISR( USART0_RX_vect )
{
	RingBufferWrite( RS232[ERS232_NO_0]->ReceiveBuffer, UDR0 );
}

ISR( USART1_RX_vect )
{
	RingBufferWrite( RS232[ERS232_NO_1]->ReceiveBuffer, UDR1 );
}