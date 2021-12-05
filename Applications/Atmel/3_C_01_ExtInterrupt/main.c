/*
 * TimerTest.c
 *
 * Created: 15.01.2020 13:02:49
 * Author : leon8
 */

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int intCounter = 0;

int main(void)
{
	unsigned i = 0;
    PCICR |= ( 1 << PCIE0 );
	PCMSK0 = 0x0F;
	sei();
	
    while (1)
    {
		i++;
    }
}

ISR( PCINT0_vect )
{
	intCounter++; // Breakpointer notwendig (Zeile anklicken)
}