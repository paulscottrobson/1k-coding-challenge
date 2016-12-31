	
		cpu		8008new

;
;	variables A-Z, operators + - * / . (and) , (xor), 1 byte values all.
;
; 	keywords in lower case, variables in upper case.
;	: seperates program lines.
;
;	NOTE: Some commands have been renamed because only the first character matters
; 		  so RUN is now XECUTE and LIST is now VIEW
;
;	goto <expression>					Go to line number.
;	input <variable>					Input a number
;	key <variable>						Input a single keystroke (ASCII value)
; 	let <variable> = <expression> 		Assignment.
;	new 								Erase current program.
;	out <expression> 					Print character <expression> (e.g. out 42 prints '*')
;	print "<string>",<expression>[;] 	Print to terminal
;	stop 								Stop Program
;	view [<start line>] 				List 12 lines of current program.
;	xecute  							Run Program (BS breaks into a running program)
;
;	Coding to do:
;
;		call <line>
;		return
;		if [!]<expr> [command] 
;

VariablePage = 	1000h 											; this page has variables offset from A = 0
InputPage = 	1100h 											; text input goes here.
UpdatePage = 	1200h 											; code to do ld (hl),x goes here+misc

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
__LineNumberToDE:		
		ori 	080h 											; set bit 7 , which will be bit 5 if shift x 2
		rar 													; also CC for this.
		mov 	d,a 											; put shifted right once into D
		mvi 	a,0 											; 
		rar  													; will clear C again.
		mov 	e,a  									
		mov 	a,d 											; now shift DE right once more.
		rar
		mov 	d,a
		mov 	a,e 											; note :__LineNumberToDE is only used by the program
		rar 													; loader code.
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
;
;								Print line at HL as its line number
;
; ***********************************************************************************************

PrintLineNumber:
		mov 	a,h
		ani 	20h 											; if not in program memory
		rz 														; don't print it.
		mov 	a,l
		add 	a
		mov 	c,a
		mov 	a,h
		adc 	h
		mov 	d,a
		mov 	a,c
		add 	c
		mov 	a,d
		adc 	d
		ani 	07Fh
		mov 	d,a

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

		cpi 	'g' 											; these ones come first, they change HL page.
		jz 		COMMAND_Goto

		call 	__CExecOne 										; execute one command.
		rst 	GetNextCharacter 								; next is :
		cpi 	':'
		jz 		CommandExecute
		ret

__CExecOne:
		cpi 	'o' 											; commands which won't change HL page.
		jz 		COMMAND_Out 
		cpi 	'l'
		jz 		COMMAND_Let
		cpi 	'p'
		jz 		COMMAND_Print 	
		cpi 	'k'
		jz 		COMMAND_Key
		cpi 	'i'
		jz 		COMMAND_Input
		cpi 	'x' 											; these ones are not speed important
		jz 		COMMAND_eXecute
		cpi 	'v' 	
		jz 		COMMAND_View
		cpi 	'n'
		jz 		COMMAND_New
		cpi 	's' 
		jz 		COMMAND_Stop
		mvi 	c,'C' 											; command error.

; ***********************************************************************************************
;
;								Report error, character code in C
;
; ***********************************************************************************************

Error: 	mvi 	b,'?' 											; print ?
		rst 	PrintCharacter
		mov 	b,c
		rst 	PrintCharacter 									; print error code
		mvi 	b,'@' 											; print @
		rst 	PrintCharacter 
		call 	PrintLineNumber 								; print line number
		rst 	NextCommand 									; go to command loop.

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

; ***********************************************************************************************
; ***********************************************************************************************
;
;									view [<start line>] : list program
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_View:
		rst 	Evaluate 										; line number in B, address in DE.
		mov 	h,d 											; put line address in HL.
		mov 	l,e 							 
		mvi 	e,12 											; E is the number to print.
__CL_Loop:
		mov 	a,m 											; look at the code
		ora 	a 												; if zero don't list it
		jz 		__CL_Next
		call 	PrintLineNumber 								; line
		mvi 	b,' ' 											; space
__CL_Print:
		rst 	PrintCharacter 									; print
		mov 	b,m 											; put char in B for printing
		inr 	l 												; advance pointer
		mov 	a,b 											; loop back if nz
		ora 	a
		jnz 	__CL_Print
		mvi 	b,13 											; print new line.
		rst 	PrintCharacter
		dcr 	e 												; do 12 lines.
		jz 		NextCommand
__CL_Next:
		call 	NextLine
		jnz 	__CL_Loop 										; go back. 
		rst 	NextCommand

; ***********************************************************************************************
;
;			Advance pointer HL to next line. Return Z flag set if end of program
;
; ***********************************************************************************************

NextLine:
		mov 	a,l 											; go to next line. 
		ani 	0C0h
		adi 	64
		mov 	l,a
		mov 	a,h
		aci 	0
		mov 	h,a
		cpi 	40h 											; reached end of program memory
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;
;							out <expression> prints a character
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_Out:
		rst 	Evaluate 										; out what ?
		mov 	a,b 											; check not zero
		ani 	07Fh
		rz  													; if so, exit.
		rst 	PrintCharacter
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;
;									Xecute : Run program
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_eXecute:
		mvi 	h,ProgramMemory / 256 							; start from here
		mvi 	l,0 
__CR_Loop:
		in 		0 												; check for Backspaces which exits.
		cpi 	8
		jz 		COMMAND_Stop
		call 	CommandExecute 									; execute one line
		call 	NextLine 										; go to next line
		jnz 	__CR_Loop 											
COMMAND_Stop:		
		rst   	NextCommand 									; end of program, go to next command.

; ***********************************************************************************************
; ***********************************************************************************************
;
;										Go to a new line
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_Goto:
		rst 	Evaluate 										; evaluate line to go to
		mov 	l,e 											; copy address to DE
		mov 	h,d
		mov 	a,b 											; if number found.
		ora 	a
		jnz 	CommandExecute 									; then go there.
		rst 	NextCommand 									; goto 0 [stop]

; ***********************************************************************************************
; ***********************************************************************************************
;
;									let <variable> = <expression>
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_Let:
		call 	SetUpSaveVariable 								; code to set up variable update.
		rst 	GetNextCharacter  								; check for equal
		cpi 	'='
		jnz 	SyntaxError
		rst 	Evaluate 										; evaluate RHS.

; ***********************************************************************************************
;
;								Save value in B in preset variable
;
; ***********************************************************************************************

SaveBInVar:
		mov 	d,h 					 						; save HL
		mov 	e,l
		call 	UpdatePage 										; load L.
		mvi 	h,VariablePage/256 								; and H.
		mov 	m,b 											; write result out.
		mov 	h,d 											; restore HL
		mov 	l,e
		ret  													; and done.

; ***********************************************************************************************
;
;										Report Syntax Error
;
; ***********************************************************************************************

SyntaxError: 													; (S)yntax error
		mvi 	c,'S'
		jmp 	Error

; ***********************************************************************************************
;
;				Set up to save a value in next variable in line. (puts MVI L,nn;RET)
;
; ***********************************************************************************************

SetUpSaveVariable:
		rst 	GetNextCharacter 								; get the character
		sui 	65+26 											; check if > 'Z'.
		jp 		__SUSError
		adi 	26 												; check if < 'A'
		jm 		__SUSError
		mov 	d,h 											; save HL.
		mov 	e,l
		mvi 	h,UpdatePage/256 								; HL points to update page.
		mvi 	l,0
		mvi 	m,036h 											; MVI L command
		inr 	l
		mov 	m,a 											; address to load into L
		inr 	l
		mvi 	m,7 											; RET
		mov 	h,d 											; restore HL
		mov 	l,e
		ret
__SUSError:
		mvi 	c,'V' 											; report (V)ariable error.
		jmp 	Error

; ***********************************************************************************************
; ***********************************************************************************************
;
;											input <variable>
;
; ***********************************************************************************************
; ***********************************************************************************************

Command_Input:
		call 	SetUpSaveVariable 								; get ready to set up.
		mov 	d,h 											; save HL in DE
		mov 	e,l
		mvi 	h,UpdatePage/256 								; save HL in update page
		mvi 	l,10h
		mov 	m,d
		inr 	l
		mov 	m,e
		mvi 	b,'?'											; prompt
		rst 	PrintCharacter
		rst 	InputLine 										; read line.
		rst 	Evaluate 										; evaluate, result now in B.
		call 	SaveBInVar 										; save the result
		mvi 	l,10h 											; restore HL
		mvi 	h,UpdatePage/256 				
		mov 	a,m
		inr 	l
		mov 	l,m
		mov 	h,a
		ret 													; and exit.

; ***********************************************************************************************
; ***********************************************************************************************
;
;										key <variable>
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_Key:
		call 	SetUpSaveVariable 								; get ready to set up.
__CK_Get:		
		in 		0 												; read keyboard
		ora 	a
		jz 		__CK_Get 										; loop if no key
		mov 	b,a 											; put B in A
		call 	SaveBInVar 										; save code
		ret

; ***********************************************************************************************
; ***********************************************************************************************
;
;								print <variable> "<string>" ; 
;
; ***********************************************************************************************
; ***********************************************************************************************

Command_Print:
		rst 	GetNextCharacter 								; get character
		cpi 	'"' 											; if " then it is a string.
		jz 		__CP_String 									
		ora 	a 												; if zero then command ends.
		jz 		__CP_EndPrint
		cpi 	':'												; if colon, then command ends.
		jz 		__CP_EndPrint
		cpi 	';' 											; if not semicolon then expression
		jnz 	__CP_Expression
;
;		Found a semicolon so if followed by : or NULL, exit without newline
;
		rst 	GetNextCharacter 								; semicolon found, get next char and undo incr
		dcr 	l
		ora 	a 												; if end of command exit.
		rz 
		cpi 	':' 											; which is either end of line or semicolon.
		rz
		jmp 	Command_Print 									; no, go and print again.
;
;		Found colon or NULL, so exit with newline
;
__CP_EndPrint: 													; end of command
		dcr 	l 												; undo the get.
__CP_CRAndExit:		
		mvi 	b,13 											; print CR
		rst 	PrintCharacter
		ret 													; and exit.
;
;		Quoted String
;
__CP_String:
		mov 	a,m 											; read next characted, not skipping spaces.
		ora 	a 
		jz 		__CP_CRAndExit 									; end of line, print CR and exit.
		inr 	l 												; advance pointer 
		cpi 	'"'												; if closing quote start again
		jz 		Command_Print 
		mov 	b,a 											; otherwise print and loop
		rst 	PrintCharacter
		jmp 	__CP_String
;
;		Numerical expression.
;		
__CP_Expression:
		dcr 	l 												; start of expression
		mvi 	b,' '											; print a space
		rst 	PrintCharacter
		rst 	Evaluate 										; get expression
		mov 	d,b 											; move value into D
		call 	PrintInteger 									; print it
		jmp 	COMMAND_Print 									; and loop back.

; ***********************************************************************************************
; ***********************************************************************************************
;
;										new : erase program completely
;
; ***********************************************************************************************
; ***********************************************************************************************

COMMAND_New:
		mvi 	h,ProgramMemory/256+0C0h 						; address has 2 MSB sets for zero check.
		xra 	a 												; zero A and L
		mov 	l,a
__CN_Loop: 														; fill memory with zeros.
		mov 	m,a
		inr 	l
		jnz 	__CN_Loop
		inr 	h
		jnz 	__CN_Loop
		call 	400h 											; this autoloads a program.
		rst   	NextCommand


; ***********************************************************************************************
; ***********************************************************************************************
;
;		This code is not part of the interpreter, it just quick-loads a program in to save
; 		typing it in :)
;
; ***********************************************************************************************
; ***********************************************************************************************

		org 	400h

		mvi 	c,lcode & 255 									; BC = loading code.
		mvi 	b,lcode / 256
__LC_Loop:
		mov 	l,c 											; look at next character
		mov 	h,b
		mov 	a,m 											; exit if zero.
		ora 	a 
		rz
		inr 	c 												; skip over line number
		call 	__LineNumberToDE								; DE is where it goes.
__LC_Copy:
		mov 	l,c 											; read (BC) and bump C
		mov 	h,b
		mov 	a,m		
		inr 	c
		mov 	l,e 											; write to (DE) and bump E
		mov 	h,d
		mov 	m,a 
		inr 	e
		ora 	a 												; copy whole line.
		jnz 	__LC_Copy
		jmp 	__LC_Loop 										; next line.

		org 	500h
lcode:	db 		10,"let A=42",0
		db 		20,"print A,A",0
		db 		30,"stop",0
		db 		100,"print \"fred\"",0
		db 		110,"return",0

		db 		0