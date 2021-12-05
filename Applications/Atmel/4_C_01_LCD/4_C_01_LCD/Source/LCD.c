/******************************************************************************************************
  File: LCD.c
  Author: Leon Ablinger / AblL
  Description:
    Driver for an alpha-numeric LCD-Display.
  Restrictions:
    Microprocessor: ATMega644P
	Only support for 4-bit interface
******************************************************************************************************/

#include <avr/io.h>
#include "LCD.h"
#include "HtlStddef.h"
#include "LcdConstants.h"

/********************************* Declaration of private functions ***********************************/
static void
lcdOut4Bit( unsigned char aByte );

static void
lcdEnable( void );

static void
lcdCommand( unsigned char aCommand );

static void
lcdCheckBusy( void );

static TBool
lcdReadBusyFlag();

static unsigned char
lcdReadStatusRegister();

static unsigned char
lcdRead4();

/********************************** Definitions of public funtions ***********************************/

/******************************************************************************************************
  Function: lcdInit
  Description:
    Initialize the lcd display with the needed parameters to use the rest of the program.
******************************************************************************************************/
lcdInit()
{
	LCD_PORT_DATA &= ~( 0xF << LCD_DB );
	LCD_DDR_DATA  |= ( 0xF << LCD_DB );
	
	LCD_PORT_RS &= ~( 1 << LCD_RS );
	LCD_DDR_RS |= ( 1 << LCD_RS );
	
	LCD_PORT_RW &= ~( 1 << LCD_RW );
	LCD_DDR_RW |= ( 1 << LCD_RW );
	
	LCD_PORT_EN &= ~( 1 << LCD_EN );
	LCD_DDR_EN |= ( 1 << LCD_EN );
	
	/* Software	Reset 3 times */
	lcdOut4Bit( LCD_SOFT_RESET );
	delayMs( LCD_SOFT_RESET_MS1 );
	lcdOut4Bit( LCD_SOFT_RESET );
	delayMs( LCD_SOFT_RESET_MS2 );
	lcdOut4Bit( LCD_SOFT_RESET );
	delayMs( LCD_SOFT_RESET_MS3 );
	
	/* Set to 4-bit mode */
	lcdOut4Bit( LCD_SET_FUNCTION |
				LCD_FUNCTION_4BIT );
	delayMs( LCD_SET_4BITMODE_MS );
	
	/* Initialize 2 lines, 5x7 matrix */
	lcdCommand( LCD_SET_FUNCTION |
				LCD_FUNCTION_4BIT |
				LCD_FUNCTION_2LINE |
				LCD_FUNCTION_5X7 );
				
	/* Initialize the cursor */
	lcdCommand( LCD_SET_DISPLAY |
				LCD_DISPLAY_ON |
				LCD_CURSOR_OFF |
				LCD_BLINKING_OFF );
				
	/* Cursor increment, no scroll */
	lcdCommand( LCD_SET_ENTRY |
				LCD_ENTRY_INCREASE |
				LCD_ENTRY_NOSHIFT );
				
	lcdClear();
}

/******************************************************************************************************
  Function: lcdWrite
  Description:
    Writes a string to the lcd display with the current position of the cursor.
  Parameters:
    aBuffer - The string that should be sent
	aSize   - The size of the string
******************************************************************************************************/
lcdWrite(
  char *       aBuffer,
  unsigned int aSize
  )
{
	int i;
	
	for( i = 0; i < aSize; i++ )
	{
		lcdWriteChar( aBuffer[i] );
	}
}

/******************************************************************************************************
  Function: lcdWriteChar
  Description:
    Writes a single character to the lcd display with the current position of the cursor.
  Parameters:
    aCharacter - A single character that should be sent to the lcd display
******************************************************************************************************/
lcdWriteChar( unsigned char aCharacter )
{
	lcdCheckBusy();
	LCD_PORT_RS |= ( 1 << LCD_RS );
	LCD_PORT_RW &= ~( 1 << LCD_RW );

	lcdOut4Bit( aCharacter );
	lcdOut4Bit( aCharacter << 4);
}

/******************************************************************************************************
  Function: lcdClear
  Description:
    Clears the display and waits for a specific time.
******************************************************************************************************/
lcdClear()
{
	lcdCommand( LCD_CLEAR_DISPLAY );
	delayMs( LCD_CLEAR_DISPLAY_MS );
}


/******************************************************************************************************
  Function: lcdSetCursor
  Description:
    Set the position of the cursor to the specified position.
  Parameters:
    aColumn - The column starting with 1
	aRow    - The line of the display starting with 1
  Return:
    ETRUE if the position can be set, otherwise EFALSE
******************************************************************************************************/
TBool
lcdSetCursor(
  unsigned char aColumn,
  unsigned char aRow
  )
{
	unsigned char address;

	if( aRow == 1 )
		address = (LCD_DDADR_LINE1 + (aColumn - 1));

	else if( aRow == 2 )
		address = (LCD_DDADR_LINE2 + (aColumn - 1));
		
	else
		return EFALSE;

	lcdCommand( address | LCD_SET_DDADR );

	return ETRUE;
}
  
/**************************************** Private Functions ******************************************/

/******************************************************************************************************
  Function: lcdOut4Bit
  Description:
    lcdOut4Bit writes the upper nibble (Bit 4 to Bit 7) out to the data lines. One enable impulse
	triggers the transfer.
  Parameters:
    aByte - The upper 4 bits are written to the data lines.
******************************************************************************************************/
static void
lcdOut4Bit( unsigned char aByte )
{
	LCD_DDR_DATA |= ( 0xF << LCD_DB );
	LCD_PORT_RW	 &= ~( 1 << LCD_RW );
	LCD_PORT_DATA &= ~( 0xF << LCD_DB );
	LCD_PORT_DATA |= (( aByte & 0xF0 ) >> ( 4 - LCD_DB ));
	lcdEnable();
}

/******************************************************************************************************
  Function: lcdEnable
  Description:
    Writes an high impulse to the enable line for LCD_EN us. (Normally: 10us)
******************************************************************************************************/
static void
lcdEnable()
{
	LCD_PORT_EN &= ~( 1 << LCD_EN );
	delayUs( LCD_ENABLE_US );
	LCD_PORT_EN |= ( 1 << LCD_EN );
	delayUs( LCD_ENABLE_US );
	LCD_PORT_EN &= ~( 1 << LCD_EN );
}

/******************************************************************************************************
  Function: lcdCommand
  Description:
    Send a command to the LCD-Display.
******************************************************************************************************/
static void
lcdCommand( unsigned char aCommand )
{
	lcdCheckBusy();
	
	LCD_PORT_RS &= ~( 1 << LCD_RS );
	lcdOut4Bit( aCommand );
	lcdOut4Bit( aCommand << 4);
	
	delayUs( LCD_COMMAND_US );
}

/******************************************************************************************************
  Function: lcdCheckBusy
  Description:
    Checks the busy flag in the status register of the LCD-Display.
******************************************************************************************************/
static void
lcdCheckBusy()
{
	unsigned int busyCounter = 0;
	
	while( lcdReadBusyFlag() )
	{
		busyCounter++;
		if( busyCounter > LCD_MAX_BUSY_COUNTER )
			break;
		delayUs( 1 );
	}
}

/******************************************************************************************************
  Function: lcdReadBusyFlag
  Description:
    Reads the busy flag from the status register.
******************************************************************************************************/
static TBool
lcdReadBusyFlag()
{
	unsigned char statusRegister;
	
	statusRegister = lcdReadStatusRegister();
	
	return (( statusRegister & 0x80 ) != 0);
}

/******************************************************************************************************
  Function: lcdReadStatusRegister
  Description:
    Reads the status register.
******************************************************************************************************/
static unsigned char
lcdReadStatusRegister()
{
	unsigned char statusRegister;
	
	LCD_PORT_RS &= ~( 1 << LCD_RS );
	statusRegister = lcdRead4();
	statusRegister = statusRegister << 4;
	statusRegister |= ( lcdRead4() & 0xF );
	return statusRegister;
}

/******************************************************************************************************
  Function: lcdRead4
  Description:
    Read 4 bit, stored in the lower nibble.
******************************************************************************************************/
static unsigned char
lcdRead4()
{
	unsigned char tmp;
	
	LCD_DDR_DATA &= ~( 0x0F << LCD_DB );
	LCD_PORT_RW |= ( 1 << LCD_RW );
	LCD_PORT_EN |= ( 1 << LCD_EN );
	delayUs( LCD_ENABLE_US );
	
	tmp = LCD_PIN_DATA;
	LCD_PORT_EN &= ~( 1 << LCD_EN );
	
	tmp = ( tmp >> LCD_DB ) & 0xF;
	LCD_DDR_DATA |= ( 0x0F << LCD_DB );
	
	return tmp;
}