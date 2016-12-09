	
		cpu		8008new

;
;	Savings : shift to 128 bytes/line or 256 bytes/line
; 	Drop and and xor ? (consequences for math.)
;	Dump NEW.

VariablePage = 	0400h 											; this page has variables offset from ASCII 58
InputPage = 	0500h 											; text input goes here.

ProgramMemory = 2000h 											; 127 program lines go here. 64 bytes each.
																; line 1 at 2040h, 2 at 2080h etc.
		org 	0

; ***********************************************************************************************
; ***********************************************************************************************
;
;									Main command loop
;
; ***********************************************************************************************
; ***********************************************************************************************

NextCommand:
		mvi	 	b,']' 											; print a ] prompt
		rst 	PrintCharacter 									
		rst 	InputLine 										; get the line.
		call 	CommandExecute 									; execute it
		rst 	NextCommand 									; loop back.

; ***********************************************************************************************
; ***********************************************************************************************
;
;							Read next non space character from (HL)
;
; ***********************************************************************************************
; ***********************************************************************************************

		org 	8
GetNextCharacter:
		mov 	a,m 											; read character.
		inr 	l 												; and advance.
		cpi 	' '												; if space
		jz 		NextCharacter 									; get another one.
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;
;							Print Character in B, returned in A+B
;
; ***********************************************************************************************
; ***********************************************************************************************

PrintCharacter:
		in 		1 												; check the ready to send flag
		ora 	a
		jp 		PrintCharacter 									; jump back if not ready
		mov 	a,b 											; send B to port 8.
		out 	8
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;	
;								Input a line to InputPage, ASCIIZ.
;
;	On exit HL points to line buffer.
;
; ***********************************************************************************************
; ***********************************************************************************************

InputLine:
		mvi 	h,InputPage/256 								; HL points to input buffer
__CLStartLine:		
		mvi 	l,1  											; point to start of line+1
__CLPreviousCharacter:		
		dcr 	l 												; go back 1
		jm 		__CLStartLine 									; gone too far, restart.
__CLNextCharacterInput:
		in 		0 												; read keyboard
		ora 	a
		jz 		__CLNextCharacterInput
		mov 	b,a 											; echo it
		rst 	PrintCharacter
		mov 	a,b 											; get character back.
		cpi 	8 												; is it BS
		jz 		__CLPreviousCharacter
		mov 	m,a 											; write it out
		inr 	l 												; next slot
		xri 	13   											; if CR then this will set A = 0
		jnz 	__CLNextCharacterInput
		dcr 	l 												; replace last character with 00
		mov 	m,a 
		mov 	l,a 											; point HL to start of line.
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;
;							Evaluate string at HL. Returns result in B. 
;
;	Operators are + - * / and , (xor) . (and). Terms are variables a-zA-Z and integer constants
;
;	Not awfully syntax checked :) x/0 returns 0. Technically : and up are all variables.
;
;	On exit HL points to found unknown character.
; 	On exit ED points to the line number if it's a program line (that way round)
;
; ***********************************************************************************************
; ***********************************************************************************************

		org 	038h
Evaluate:
		xra 	a
		mov 	b,a 											; b is current left value
		mov 	d,a 											; d is current right value
		mvi 	c,1 											; c is current operator (+ = 1)
AddDigit:
		mov 	e,a 											; save new value in E
		mov 	a,d 											; multiply D by 10
		add 	a
		add 	a
		add 	d 												; A is now D x 5
		add 	a 												; A is now D x 10
		add 	e 												; add the new digit.
		mov 	d,a 											; put back in D.
NextCharacter:
		rst 	GetNextCharacter 								; get next character.
		sui 	58 												; 58 - 127 are ALL variables.
		jp  	__IsVariable
		adi 	10 												; 0-9 for digits.
		jp 		AddDigit 										; if that, add to current right and goback.
		adi 	6 												; 0-5 for * + , - . /
		mov 	e,a 											; save next operator in E.
		call 	SubEvaluator 									; do operation 0-5.
		mov 	b,a 											; save the result in B
		mvi 	d,0  											; clear the right hand side.
		mov 	c,e 											; put next operator in C 
		mov 	a,c 											; look at that operator
		ora 	a 												; if +ve loop back next calculation
		jp 		NextCharacter 
		dcr  	l 												; gone too far, go back one.

		mov 	a,b 											; get result to set up program pointer.
		ori 	080h 											; set bit 7 , which will be bit 5 if shift x 2
		rar 													; also CC for this.
		mov 	e,a 											; put shifted right once into E.
		mov 	a,d 											; D is already zero, why it is ED not DE
		rar  													; will clear C again.
		mov 	d,a  									
		mov 	a,e 											; now shift ED right once more.
		rar
		mov 	e,a
		mov 	a,d
		rar
		mov		d,a

		ret
;
;		Contains 0-69 which are the variables.
;		
__IsVariable:
		mov 	e,l 											; save L in E
		mov 	l,a 											; L is variable index
		mov 	a,h 											; save H in A
		mvi 	h,VariablePage/256 								; HL points to variable
		mov 	d,m 											; read value into D
		mov 	h,a 											; restore HL from AE
		mov 	l,e
		jmp 	NextCharacter 									; and get the next character
;
;	We want to do B <op:D> C D = 0:* 1:+ 2:, 3:- 4:. 5:/ into A - don't change E 
;
SubEvaluator:
		dcr 	c 												; check for multiply (0:*)
		jm 		__SEMultiply 
		mov 	a,b 											; work out add (1:+)
		add 	d
		dcr 	c
		rm 
		mov 	a,b 											; work out logical xor (2:,)
		xra 	d
		dcr 	c
		rm 
		mov 	a,b 											; work out subtract (3:-)
		sub 	d
		dcr 	c
		rm
		mov 	a,b 											; work out and (4:.)
		ana 	d
		dcr 	c
		rm
																; so it must be divide (5:/)
		call 	__SEDivide 										; the result is in C so saves a jump.
		mov 	a,c
		ret
;
;	subtractive division.
;
__SEDivide:	
		mov 	a,d 											; check divide by zero.
		ora 	a 
		rz  													; will return $FF
		mov 	a,b 											; subtract D from this N times. C = 0
__SEDivide1:
		sub 	d
		rc
		inr 	c
		rz
		jmp 	__SEDivide1
;
;	additive multiply
;
__SEMultiply:	
		xra 	a 												; total. (*0 becomes *256)
__SEMultiply1:		
		add 	b 												; add B to 0 D times.
		dcr 	d
		jnz 	__SEMultiply1
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;
;									Print D as an integer
;
;	Breaks A,B,C,D
; ***********************************************************************************************
; ***********************************************************************************************

PrintInteger:
		mvi 	c,100 											; initial divisor
__PILoop:
		mvi 	b,'0'-1 										; character to print/count division
		mov 	a,d 											; get integer
__PIDivide:
		inr 	b 												; one more 
		mov 	d,a 											; put pre-subtract back.
		sub 	c												; subtract divisor
		jnc  	__PIDivide 										; keep going till a borrow.
		rst 	PrintCharacter 									; print the result.
		mov 	a,c  											; convert 100-10
		sui 	90
		mov 	c,a
		jnc 	__PILoop 										; keep going if 10.
		mov 	a,d 											; get what is left
		ori 	'0'												; make ASCII and print
		mov 	b,a 											; it out.
		rst 	PrintCharacter
		ret

		org 	0200h

; ***********************************************************************************************
; ***********************************************************************************************
;
;										Execute Command at (HL)
;
; ***********************************************************************************************
; ***********************************************************************************************

CommandExecute:
		rst 	Evaluate
		mov 	d,b
		call 	PrintInteger
		ret
