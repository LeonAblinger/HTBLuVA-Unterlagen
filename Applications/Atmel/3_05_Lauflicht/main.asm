;
; 05_Lauflicht.asm
;
; Created: 13.11.2019 12:38:25
; Author : leon8
;

start:
	clr r18
    ldi r20,0x01
	ldi r16,0xFF
	out DDRA,r16
	ldi r17,8 ; Number of loops

loop:
	out PORTA,r20
	lsl r20
	inc r18
	cp r18,r17
	brne loop
	rjmp start
