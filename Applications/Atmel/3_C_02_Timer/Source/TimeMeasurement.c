/************************************************************************************************************************************************
	
	File: TimeMeasurement.c
	Author: AblL / Leon Ablinger
	Description: This module provides time difference measurements with a 16-Bit-Timer.
	
	Restrictions:
	- Only Timer 1 ( 16 Bit ) supported
	
	Problems:
	- Overflow of timer counter
	
************************************************************************************************************************************************/
#include "Timer.h"
#include "TimeMeasurement.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#define CPU_CLK 16000000UL

// Definition of the states for the time measurement.
typedef enum
{
  EMEASUREMENT_STATE_MEASURING,
  EMEASUREMENT_STATE_START,
  EMEASUREMENT_STATE_FINISHED
} TMeasurementState;

typedef enum
{
	EMEASUREMENT_PERIOD_STATE_START,
	EMEASUREMENT_PERIOD_STATE_MEASURING
} TMeasurementPeriodState;

typedef struct 
{
	TMeasurementState State;
	unsigned int	  Index;
	unsigned int      TimeStampBegin;
	unsigned int      TimeStampEnd;
	unsigned int      Overflow;
	unsigned int	  ScaleFactor;
} TTimeMeasurementUserData;

typedef struct  
{
	TMeasurementPeriodState		   State;
	unsigned int				   Index;
	unsigned int				   LastTimeStamp;
	unsigned int				   Overflow;
	unsigned int				   ScaleFactor;
	TTimeMeasurementPeriodFunction Callback;
	void *						   CallbackUserData;
} TTimeMeasurementPeriodUserData;

/* DECLARATION OF PRIVATE FUNCTIONS */
static void
TimeMeasurementFunction(
void * aUserData,
unsigned int aTimeStamp );

static void
TimeMeasurementPeriodFunction(
void * aUserData,
unsigned int aTimeStamp );

/* STATIC VARIABLES */
TTimeMeasurementUserData TimeMeasurementUserData;
TTimeMeasurementPeriodUserData TimeMeasurementPeriodUserData;

/***************************************************   Definition of Public Functions   ********************************************************/
/***********************************************************************************************************************************************/

void
TimeMeasurementInit( unsigned long aCpuClk )
{
	TimerInit( aCpuClk, 1, 0, 0, TIMER_MODE_INPUT_CAPTURE_ICP1, TIMER_NO_1 );
	
	memset( &TimeMeasurementUserData, 0, sizeof ( TimeMeasurementUserData ));
	TimeMeasurementUserData.ScaleFactor = aCpuClk / 1000000;
	TimerSetInterruptFunction( TimeMeasurementFunction, &TimeMeasurementUserData, TIMER_MODE_INPUT_CAPTURE_ICP1, TIMER_NO_1 );
}

void
TimeMeasurementStart( void )
{
	TimeMeasurementUserData.State = EMEASUREMENT_STATE_START;
	DDRD |= ( 1 << DDD6 );
	
	PORTD |= ( 1 << PORTD6 );
	PORTD &= ~( 1 << PORTD6 );
}

TBool
TimeMeasurementStop( unsigned long * aTimeDifferenceUs )
{
	PORTD |= ( 1 << PORTD6 );
	PORTD &= ~( 1 << PORTD6 );
	
	while( TimeMeasurementUserData.State != EMEASUREMENT_STATE_FINISHED );
	
	*aTimeDifferenceUs = ( TimeMeasurementUserData.TimeStampEnd - TimeMeasurementUserData.TimeStampBegin ) / TimeMeasurementUserData.ScaleFactor;
	
	return ETRUE;
}

static void
TimeMeasurementFunction( void * aUserData, unsigned int aTimeStamp )
{
	TTimeMeasurementUserData * userData = ( TTimeMeasurementUserData * ) aUserData;
	
	switch( userData->State )
	{
		case EMEASUREMENT_STATE_START:
			userData->TimeStampBegin = aTimeStamp;
			userData->State = EMEASUREMENT_STATE_FINISHED;
		break;
		
		case EMEASUREMENT_STATE_MEASURING:
			userData->TimeStampEnd = aTimeStamp;
			userData->State = EMEASUREMENT_STATE_FINISHED;
		break;
		
		default:
		break;
	}
}

static void
TimeMeasurementPeriodFunction( void * aUserData, unsigned int aTimeStamp )
{
	unsigned long period;
	
	TTimeMeasurementPeriodUserData * userData = ( TTimeMeasurementPeriodUserData * ) aUserData;
	
	switch( userData->State )
	{
		case EMEASUREMENT_PERIOD_STATE_START:
			userData->LastTimeStamp = aTimeStamp;
			userData->State = EMEASUREMENT_PERIOD_STATE_MEASURING;
		break;
		
		case EMEASUREMENT_PERIOD_STATE_MEASURING:
			period = ( aTimeStamp - userData->LastTimeStamp ) / userData->ScaleFactor;
			userData->Callback( userData->CallbackUserData, period );
			userData->LastTimeStamp = aTimeStamp;
		break;
		
		default:
		break;
	}
}