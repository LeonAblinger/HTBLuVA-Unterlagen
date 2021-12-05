; 06_Interrupt.asm
;
; Created: 28.11.2019 14:31:32
; Author : leon8

.def counter = R20
.def tmp	 = R21

start:
	jmp main
	.org 2 ; Set next code address to 2
	jmp Int0Function
	
	.org 0x100

main:
	; Set stackpointer to top of RAM
	ldi r16,high(RAMEND) ; Load high bit of RAMEND in r16
	out SPH,r16 ; Load r16 in StackPointer(High)

	ldi r16,low(RAMEND) ; Load low bit of RAMEND in r16
	out SPL,r16 ; Load r16 in StackPointer(Low)

	clr counter

	; Define and enable external interrupt 0

	ldi xh,0 ; Read EICRA register
	ldi xl,EICRA
	ld r16,x
	ori r16,2<<ISC00
	st x,r16

	ldi r16,1<<INT0
	out EIMSK,r16
	sei

loop:
	jmp loop

Int0Function:
	inc counter
	reti