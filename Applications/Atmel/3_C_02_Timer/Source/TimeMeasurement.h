/************************************************************************************************************************************************
	
	File: TimeMeasurement.h
	Author: AblL / Leon Ablinger
	Description: Timer interface for the AtMega644P micro controller
	
	Restrictions:
	
************************************************************************************************************************************************/
#include "Timer.h"

typedef void ( * TTimeMeasurementPeriodFunction )(
	void *		  aUserData,
	unsigned long aPeriodUs );

typedef enum
{
	ERISING_EDGE,
	EFALLING_EDGE,
	EBOTH_EDGE
} TTimeMeasurementMode;

void
TimeMeasurementInit(
unsigned long aCpuClk );

TBool
TimeMeasurementStop( unsigned long * aTimeDifferenceUs );

TBool
TimeMeasurementPeriodStart(
	unsigned long aCpuClk,
	TTimeMeasurementPeriodFunction aFunction,
	void * aUserData,
	TTimeMeasurementMode aMode );