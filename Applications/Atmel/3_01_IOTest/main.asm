; 01_IOTest.asm
;
; Created: 07.10.2019 11:02:27
; Author : leon8

start:
	ldi r16,0xFF ; Register 16 auf 0xFF setzen
	out DDRA,r16 ; Register 16 in DDRA schreiben
	out DDRB,r16
	ldi r16,0
loop:
	inc r16 ; Register 16 + 1
	out PORTA,r16 ; Auf Port A schreiben, aus Register 16
	nop
	in r1,PORTA ; In Register 16 schreiben, aus Port A
	out PORTB,r1
    rjmp loop ; Zu loop: springen