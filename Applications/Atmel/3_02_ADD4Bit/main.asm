;
; 02_ADD4Bit.asm
;
; Created: 14.10.2019 08:24:39
; Author : Leon Ablinger
;

start:
	
	
loop:
	ldi r20,0xFF
	out DDRA,r20
	out DDRB,r20
	ldi r16,0b00010110
	ldi r17,0x00
	ldi r18,0x0F
	out PORTA,r16

	mov r17,r16
	and r17,r18
	out PORTA,r17
	lsr r16
	lsr r16
	lsr r16
	lsr r16
	out PORTA,r16
	add r16,r17
	out PORTB,r16
	in r16,PINA
    rjmp loop	