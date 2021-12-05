/************************************************************************************************************************************************
	
	File: TestTimer.c
	Author: AblL / Leon Ablinger
	Description: Test the timer module for the AtMega644 micro controller.
	
*************************************************************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"

#define CPU_CLK 16000000UL
#define TIMER_INTERVALL 500UL

void TestTimerInterruptFunctions();

/*************************************************************
  Set PWM Level in % for Fast PWM & Phasecorrected PWM mode
*************************************************************/
#define PWM_LEVEL_IN	50
#define PWM_LEVEL_OUT	30
/************************************************************/

unsigned int tmp = 0;

typedef struct  
{
  unsigned int Counter;
  unsigned int Index;
  unsigned int TimeStamp;
} TUserData;

void
TestFunction( void * aUserData, unsigned int aTimeStamp )
{
  TUserData * userData = aUserData;
  
  userData->TimeStamp = aTimeStamp;
  userData->Counter++;
}

int main(void)
{
  /* Replace with your application code */
  
  TimerInit(CPU_CLK, TIMER_INTERVALL, 0, 0, TIMER_MODE_CTC, TIMER_NO_0);
  DDRA = 0xFF;
  
  while(1)
  {}

}

void
TestTimerInterruptFunctions()
{
  TUserData myUserData;
	
  myUserData.Counter = 0;
  myUserData.Index = 3;
	
  TimerInit( CPU_CLK, TIMER_INTERVALL, PWM_LEVEL_IN, PWM_LEVEL_OUT, TIMER_MODE_INPUT_CAPTURE_ICP1, TIMER_NO_1 );
  TimerSetInterruptFunction( TestFunction, &myUserData, TIMER_MODE_INPUT_CAPTURE_ICP1, TIMER_NO_1 );
}

void
TestTimeMeasurement( void )
{
	unsigned long tmp = 0;
	unsigned long timeDiff;
	
	TimeMeasurementInit( 16000000 );
	TimeMeasurementStart();
	
	tmp++;
	tmp++;
	tmp++;
	tmp++;
	TimeMeasurementStop( &timeDiff );
}