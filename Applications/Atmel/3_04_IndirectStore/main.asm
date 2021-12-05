;
; 04_IndirectStore.asm
;
; Created: 23.10.2019 13:08:59
; Author : leon8
;

start:
	jmp version2

	ldi r27,0x01 ; R27 auf 0x01 damit RX 0x0100

	ldi r16,0x01 ; R16 soll geschrieben werden
	st X+,r16 ; Store R16 in RX
	inc r16 ; R16++
	st X+,r16
	inc r16
	st X,r16

	ldi r16,0x05 ; R16 mit 5 beschreiben für Addition
	clr r26 ; R26 löschen, damit RX wieder 0x0100
	ld r20,X+ ; RX in R20 schreiben
	add r20,r16
	ld r21,X+
	add r21,r16
	ld r22,X
	add r22,r16

	ldi r26,0x10 ; Addierte Werte wieder in RX 0x0110 schreiben
	st X+,r20
	st X+,r21
	st X,r22

version2:
	ldi r27,0x01 ; R27 auf 0x01 damit RX 0x0100
	ldi r16,0x01 ; R16 soll geschrieben werden

	ldi r19,5 ; Number of loops

loop1:
; Write numbers to memory
	st X+,r16
	inc r16
	inc r20
	cp r20,r19
	brne loop1

	clr r20
	clr r26
	ldi r18,2
	ldi r24,0x10

loop2:
; Get numbers of memory, multiply by 2, store again
	ld r22,X
	mul r22,r18
	mov r22,r0
	add r26,r24
	st X+,r22
	sbc r26,r24

	inc r20
	cp r20,r19
	brne loop2

	rjmp version2