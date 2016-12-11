	
		cpu		8008new

;
;	Savings : shift to 128 bytes/line or 256 bytes/line
; 	Drop and and xor ? (consequences for math.)
;
;	variables A-Z
; 	keywords in lower case.
;
;
;	Coding:
;		Enter program lines (also empty lines)
;		Auto-enter program [seperate]
;		new run let goto input print call exit (return) view (list) key (character) out (character)
;
;

VariablePage = 	1000h 											; this page has variables offset from A = 0
InputPage = 	1100h 											; text input goes here.

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
		jz 		GetNextCharacter 								; get another one.
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
; 	On exit DE points to the line number if it's a program line (that way round)
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
		sui 	58 												; 58 - 127 are maybe variables.
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
		mov 	d,b 											; put result in D
ExitEvaluate1:		
		mov 	b,d 											; put result in B
		dcr  	l 												; gone too far, go back one.
		mov 	a,b 											; get result to set up program pointer.
		ori 	080h 											; set bit 7 , which will be bit 5 if shift x 2
		rar 													; also CC for this.
		mov 	d,a 											; put shifted right once into D
		mvi 	a,0 											; 
		rar  													; will clear C again.
		mov 	e,a  									
		mov 	a,d 											; now shift DE right once more.
		rar
		mov 	d,a
		mov 	a,e
		rar
		mov		e,a

		ret
;
;		Variable ? A contains variable char - 58.
;		
__IsVariable:
		sui 	91-58 											; if >= 91 this will be +ve
		jp 		ExitEvaluate1 								
		adi 	26 												; if 0-25 then legit.
		jm 		ExitEvaluate1
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

; ***********************************************************************************************
; ***********************************************************************************************
;
;										Execute Command at (HL)
;
; ***********************************************************************************************
; ***********************************************************************************************

CommandExecute:
		rst 	GetNextCharacter 								; get character.
		mov 	b,a 											; save in B
		ral 													; shift left bit 6 into bit 7. basic # test
		ora 	a 												; check if zero, signed.
		rz
		jp 		ProgramLine 									; if +ve it is a

__SkipOverKeyword:
		rst 	GetNextCharacter 								; get character
		adi 	256-97 											; CS if >= 97 e.g. lower case keyword
		jc 		__SkipOverKeyword 
		dcr 	l  												; unpick the last get.
		mov 	a,b 											; get the first character back.

		; 	check first characters

wait1:	jmp 	wait1 			; execute command, 1st letter x 2 in A

; ***********************************************************************************************
;
;									Put a program line into memory.
;
; ***********************************************************************************************
ProgramLine:
		dcr 	l 												; backspace to first character
		rst 	Evaluate 										; get line number into B, address into DE
		mov 	c,l 											; C is the low byte of the input line.
		mov 	a,b 											; exit if the line number is zero
__PLCopy:
		ora 	a
		rz		
		mov 	l,c 											; read next byte from input line.
		mvi 	h,InputPage/256		
		mov 	a,m
		mov 	h,d 											; write it out to address DE
		mov 	l,e
		mov 	m,a
		inr 	c 												; increment two pointers
		inr 	e 
		jmp 	__PLCopy 										; jump back and return if zero.
