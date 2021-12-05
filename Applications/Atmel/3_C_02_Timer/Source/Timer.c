/************************************************************************************************************************************************
	
	File: Timer.c
	Author: AblL / Leon Ablinger
	Description: Timer interface for the AtMega644P micro controller
	
	Restrictions:
	
************************************************************************************************************************************************/

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_MAX_PRESCALER_INDEX 6

unsigned int TimerPrescalerValues[TIMER_MAX_PRESCALER_INDEX] = { 1, 1, 8, 64, 256, 1024 };

unsigned int TimerOverflowCounter = 0;
unsigned int TimerCompareMatchCounter = 0;
unsigned int PWMLevelIn, PWMLevelOut;

/* Interrupt function pointer for the timer */
TTimerFunction	TimerFunctionTimer0CTC;
void *			TimerFunctionTimer0CTCUserData;

TTimerFunction	TimerFunctionTimer1CTC;
void *			TimerFunctionTimer1CTCUserData;

TTimerFunction	TimerFunctionTimer1Capture;
void *			TimerFunctionTimer1CaptureUserData;

/* Declaration of private functions */
static void TimerCalculatePrescalerNormalMode( unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned long * aPrescaler);
void TimerCalculateCompareRegister( unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned long * aCompareRegister, unsigned long * aPrescaler );
void TimerCalculateCompareRegisterHigh( unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned long * aCompareRegister, unsigned long * aPrescaler );
static TBool TimerInit0(unsigned long aCpuClk, unsigned long aTimerIntervall, TTimerMode aMode);
static TBool TimerInit1(unsigned long aCpuClk, unsigned long aTimerIntervall, TTimerMode aMode);
TBool TimerSetPwmLevel(TTimerNumber aTimerNo, unsigned int aPwmLevel);

/************************************************************************************************************************************************

	Function: TimerInit
	Description: Initialize the timer of the AtMega644P controller.
	Parameters:
		- aCpuClk			-	The clock frequency of the controller
		- aTimerIntervall	-   The interrupt interval of the timer
		- aMode				-	The mode of the timer
		- aTimerNo			-	The timer number of the controller

************************************************************************************************************************************************/

TBool success;
TBool
TimerInit(unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned int aPWMLevelIn, unsigned int aPWMLevelOut, TTimerMode aMode, TTimerNumber aTimerNo)
{
  PWMLevelIn = aPWMLevelIn;
  PWMLevelOut = aPWMLevelOut;
  switch( aTimerNo )
  {
    case TIMER_NO_0:
      success = TimerInit0( aCpuClk, aTimerIntervall, aMode );
      break;
   
    case TIMER_NO_1:
      success = TimerInit1( aCpuClk, aTimerIntervall, aMode );
      break;
   
    default:
      return EFALSE;
      break;
  }
  
  return success;
}

/************************************************************************************************************************************************

	Function: TimerSetInterruptFunction
	Description:
	Parameters:
		- aFunction	- This function is called by the interrupt
		- aUserData - This parameter is transfered to the function
		- aMode		- The mode of the timer
		- aTimerNo	- The timer number of the controller

	Return:
		- ETRUE if the interrupt is supported for calling user functions otherwise EFALSE
		
************************************************************************************************************************************************/

TBool
TimerSetInterruptFunction(TTimerFunction aFunction, void * aUserData, TTimerMode aMode, TTimerNumber aTimerNo)
{

	switch( aTimerNo )
	{
		case TIMER_NO_0:
		  switch( aMode )
		  {
			  case TIMER_MODE_CTC:
			    TimerFunctionTimer0CTC		   = aFunction;
				TimerFunctionTimer0CTCUserData = aUserData;
			    break;
				
			  default:
			  return EFALSE;
			  break;
		  }
		break;
		
		case TIMER_NO_1:
		  switch( aMode )
		  {
			  case TIMER_MODE_CTC:
			    TimerFunctionTimer1CTC		   = aFunction;
			    TimerFunctionTimer1CTCUserData = aUserData;
			    break;
				
			  case TIMER_MODE_INPUT_CAPTURE_ICP1:
			    TimerFunctionTimer1Capture	       = aFunction;
			    TimerFunctionTimer1CaptureUserData = aUserData;
				break;
				
			  default:
			  return EFALSE;
			  break;
		  }
		break;
		
		default:
		return EFALSE;
		break;
	}
	
	return ETRUE;
}

/************************************************************************************************************************************************

	Function: TimerInit0
	Description: Initialize the timer TIMER_NO_0 of the AtMega644P controller.
	Parameters:
		- aCpuClk			-	The clock frequency of the controller
		- aTimerIntervall	-	The interrupt interval of the timer
		- aMode				-	The mode of the timer

************************************************************************************************************************************************/

static TBool
TimerInit0(unsigned long aCpuClk, unsigned long aTimerIntervall, TTimerMode aMode)
{
  unsigned long compareRegister, prescaler;
  
  TimerFunctionTimer0CTC = 0;
    
  switch( aMode )
  {
    case TIMER_MODE_NORMAL:
      TimerCalculatePrescalerNormalMode( aCpuClk, aTimerIntervall, &prescaler );
      TCCR0A &= ~(( 1 << WGM00 ) | ( 1 << WGM01 ));
      TCCR0B |= ( prescaler << CS00);
      TIMSK0 |= ( 1 << TOIE0 );
      sei();
      break;
      
    case TIMER_MODE_CTC:
      TimerCalculateCompareRegister( aCpuClk, aTimerIntervall, &compareRegister, &prescaler );
      OCR0A = compareRegister;
      //prescaler = 0x04; // HARDCODE
      TCCR0B |= ( prescaler << CS00 );
      TCCR0A &= ~(( 1 << WGM00 ) | ( 1 << WGM01 ));
      TCCR0A |= ( 1 << WGM01 );
      TIMSK0 |= ( 1 << OCIE0A );
      sei();
      break;
      
    case TIMER_MODE_PWM_FAST:
	  DDRB = 0xFF; // Set PortB as output -> PINB3 for OC0A
	  TimerCalculatePrescalerNormalMode( aCpuClk, aTimerIntervall, &prescaler );
	  TimerSetPwmLevel( TIMER_NO_0, PWMLevelIn );
	  TCCR0A |= ( 1 << WGM00 ) | ( 1 << WGM01 );
	  TCCR0A = ( 1 << COM0A0 ); // without | to clear error
      TCCR0B |= ( prescaler << CS00);
	  TCCR0B |= ( 1 << WGM02 );
      TIMSK0 |= ( 1 << TOIE0 );
      sei();
	  
      break;
	  
	  case TIMER_MODE_PWM_CORR:
	  DDRD = 0xFF;
	  TimerCalculatePrescalerNormalMode( aCpuClk, aTimerIntervall, &prescaler );
	  TimerSetPwmLevel( TIMER_NO_0, PWMLevelIn );
	  TCCR0A |= ( 1 << WGM00 );
	  TCCR0A =  ( 1 << COM0A1 ) | ( 1 << COM0A0 );
	  TCCR0B |= ( prescaler << CS00);
	  TCCR0B |= ( 1 << WGM02 );
	  TIMSK0 |= ( 1 << TOIE0 );
	  sei();
	  
	  break;
      
    default:
      return EFALSE;
  }
  return EFALSE;
}

/************************************************************************************************************************************************

	Function: TimerInit1
	Description: Initialize the timer TIMER_NO_1 of the AtMega644P controller.
	Parameters:
		- aCpuClk			-	The clock frequency of the controller
		- aTimerIntervall	-	The interrupt interval of the timer
		- aMode				-	The mode of the timer

************************************************************************************************************************************************/

static TBool
TimerInit1(unsigned long aCpuClk, unsigned long aTimerIntervall, TTimerMode aMode)
{
	unsigned long compareRegister, prescaler;
	
	  TimerFunctionTimer1CTC = 0;
	
	switch( aMode )
	{
	  case TIMER_MODE_NORMAL:
	    TimerCalculatePrescalerNormalMode( aCpuClk, aTimerIntervall, &prescaler );
		TCCR1B |= ( prescaler << CS10 );
		TIMSK1 |= ( 1 << TOIE1 );
		sei();
		break;
		
	  case TIMER_MODE_CTC:
		TimerCalculateCompareRegisterHigh( aCpuClk, aTimerIntervall, &compareRegister, &prescaler );
		OCR1A = compareRegister;
		TCCR1B |= ( prescaler << CS10 );
		TCCR1B |= ( 1 << WGM12 );
		TIMSK1 |= ( 1 << OCIE1A );
		sei();
		break;
		
	  case TIMER_MODE_INPUT_CAPTURE_ICP1:
		DDRD &= ~( 1 << DDD6 );
		TimerCalculatePrescalerNormalMode(aCpuClk, aTimerIntervall, &prescaler);
		TCCR1B |= ( prescaler << CS10 );
		TCCR1B |= ( 1 << ICES1 );  //rising edge
		TIMSK1 |= ( 1 << ICIE1 );
		sei();
		break;
		
		default:
		return EFALSE;
	}
	return EFALSE;
}

/************************************************************************************************************************************************

	Function: TimerCalculateCompareRegister
	Description: Calculate the prescaler and the compare register (OCRA) of the 8-Bit-Timer (0).
	Parameters:
		- aCpuClk			-	The clock frequency of the controller
		- aTimerIntervall	-	The interrupt interval of the timer
	Return:
		- aCompareRegister	-	The calculated value of the compare register
		- aPrescaler		-   The calculated value of the prescaler

************************************************************************************************************************************************/

void TimerCalculateCompareRegister( unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned long * aCompareRegister, unsigned long * aPrescaler )
{
  unsigned long ocra;
  unsigned int prescalerIndex;
  
  for ( prescalerIndex = 0; prescalerIndex < TIMER_MAX_PRESCALER_INDEX; prescalerIndex++ )
  {
    ocra = ( aTimerIntervall * ( (double) aCpuClk / TimerPrescalerValues[prescalerIndex] / 1000000.0 )) - 1;
    if ( ocra < 256) break;
  }
  
  *aCompareRegister = ocra;
  *aPrescaler = prescalerIndex;
}

/************************************************************************************************************************************************

	Function: TimerCalculateCompareRegisterHigh
	Description: Calculate the prescaler and the compare register (OCRA) of the 16-Bit-Timer (1).
	Parameters:
		- aCpuClk			-	The clock frequency of the controller
		- aTimerIntervall	-	The interrupt interval of the timer
	Return:
		- aCompareRegister	-	The calculated value of the compare register
		- aPrescaler		-   The calculated value of the prescaler

************************************************************************************************************************************************/

void TimerCalculateCompareRegisterHigh( unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned long * aCompareRegister, unsigned long * aPrescaler )
{
	unsigned long ocra;
	unsigned int prescalerIndex;
	
	for ( prescalerIndex = 0; prescalerIndex < TIMER_MAX_PRESCALER_INDEX; prescalerIndex++ )
	{
		ocra = ( aTimerIntervall * ( (double) aCpuClk / TimerPrescalerValues[prescalerIndex] / 1000000.0 )) - 1;
		if ( ocra < 65536) break;
	}
	
	*aCompareRegister = ocra;
	*aPrescaler = prescalerIndex;
}

/************************************************************************************************************************************************

	Function: TimerCalculatePrescalerNormalMode
	Description: Calculate the prescaler of the chosen timer.
	Parameters:
		- aCpuClk			-	The clock frequency of the controller
		- aTimerIntervall	-	The interrupt interval of the timer
	Return:
		- aPrescaler		-   The calculated value of the prescaler

************************************************************************************************************************************************/

static void TimerCalculatePrescalerNormalMode( unsigned long aCpuClk, unsigned long aTimerIntervall, unsigned long * aPrescaler )
{
    float timerIntervall;
    unsigned char prescalerIndex;
    
    for ( prescalerIndex = TIMER_MAX_PRESCALER_INDEX - 1; prescalerIndex > 0; prescalerIndex-- )
    {
        timerIntervall = (256.0 * 1000000.0) / (double)aCpuClk * TimerPrescalerValues[prescalerIndex];
        
        if ( timerIntervall < aTimerIntervall ) break;
    }
    
    *aPrescaler = prescalerIndex;
}

/************************************************************************************************************************************************

	Function: TimerSetPwmLevel
	Description: Calculate the prescaler of the chosen timer.
	Parameters:
		- aTimerNo	- The number of the timer
	Return:
		- aPwmLevel	- The value in percent which the signal should be activated

************************************************************************************************************************************************/

TBool TimerSetPwmLevel( TTimerNumber aTimerNo, unsigned int aPwmLevel )
{	
    switch( aTimerNo )
    {
    case TIMER_NO_0:
	OCR0A = (255 * aPwmLevel) / 100;
      break;
    
    default:
      return EFALSE;
      break;    
    }

    return success;
}

// TIMER 0 Overflow
ISR( TIMER0_OVF_vect )
{
  TimerOverflowCounter++;
  PORTA += 0x01;
}

// TIMER 1 Compare Register A
ISR( TIMER0_COMPA_vect )
{
  TimerCompareMatchCounter++;
  PORTA += 0x01;
  if(PORTA >= 127) PORTA = 0x00;
  
  if ( TimerFunctionTimer0CTC != 0 )
    TimerFunctionTimer0CTC( TimerFunctionTimer0CTCUserData, 0 );
}

// TIMER 1 Overflow
ISR( TIMER1_OVF_vect )
{
  TimerOverflowCounter++;
}

// TIMER 1 Compare Register A
ISR( TIMER1_COMPA_vect )
{
  TimerCompareMatchCounter++;
	
  if ( TimerFunctionTimer1CTC )
    TimerFunctionTimer1CTC( TimerFunctionTimer1CTCUserData, 0 );
}

// TIMER 1 Input Capture 1
ISR( TIMER1_CAPT_vect )
{
  if( TimerFunctionTimer1Capture )
    TimerFunctionTimer1Capture( TimerFunctionTimer1CaptureUserData, ICR1);
}