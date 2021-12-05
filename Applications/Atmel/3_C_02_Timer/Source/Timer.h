/************************************************************************************************************************************************
	
	File: Timer.h
	Author: AblL / Leon Ablinger
	Description: nothin
	
*************************************************************************************************************************************************/

#ifndef TIMER_H
#define TIMER_H

typedef enum
{
  EFALSE = 0,
  ETRUE = 1
} TBool;

typedef enum
{
  TIMER_MODE_NORMAL,
  TIMER_MODE_CTC,
  TIMER_MODE_PWM_FAST,
  TIMER_MODE_PWM_CORR,
  TIMER_MODE_INPUT_CAPTURE_ICP1
} TTimerMode;

typedef enum
{
  TIMER_NO_0,
  TIMER_NO_1,
  TIMER_NO_2
} TTimerNumber;

typedef enum
{
  COMP_A,
  COMP_B
} TCompareOutput;

typedef enum
{
  TIMER_OUTPUT_NORMAL,
  TIMER_OUTPUT_INVERTED,
  TIMER_OUTPUT_TOGGLE
} TTimerOutputMode;

// Rückgabewert (Name des Typs)	 (Übergabeparameter)
typedef void ( * TTimerFunction )( void * aUserData,
  unsigned int aTimeStamp );

/************************************************************************************************************************************************

	Function: TimerInit
	Description: Initialize the timer of the AtMega644P controller.
	Parameters:
		- aCpuClk	-	The clock frequency of the controller
    - aTimerIntervall - The interrupt interval of the timer
		- aMode		-	The mode of the timer
		- aTimerNo	-	The timer number of the controller

************************************************************************************************************************************************/

TBool
TimerInit(
    unsigned long aCpuClk,
    unsigned long aTimerIntervall,
	unsigned int  aPWMLevelIn,
	unsigned int  aPWMLevelOut,
    TTimerMode    aMode,
    TTimerNumber  aTimerNo );

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
TimerSetInterruptFunction(
	TTimerFunction aFunction,
	void *         aUserData,
	TTimerMode     aMode,
	TTimerNumber   aTimerNo );

#endif