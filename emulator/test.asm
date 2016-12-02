
	cpu 	1802

r0 = 0
r1 = 1
r2 = 2
r3 = 3
r4 = 4
r5 = 5
rd = 13
re = 14
rf = 15

	dis
	ldi 	01Eh
	plo 	r2							; working stack.
	ldi 	00h
	phi 	r2
	ldi 	start & 255
	plo 	r4
	ldi 	start / 256
	phi 	r4
	sep 	r4

	org 	100h

v2 = 0FFFFh
v1 = 00001h

start:
	sex 	r2
	dec 	r2
	ldi 	v1/256 						; set up for 0+ pending
	stxd 								; X+2 = high byte
	ldi 	v1&255
	stxd
	ldi 	'*'
	str 	r2

;
;	get next term into RF.
;
	ldi 	0 							; RE is used for the counter/total for multiply/divide
	phi 	re
	plo 	re
	phi 	rf 							; the RF value is initialised to zero for digit constants.
	plo 	rf

	ldi 	v2/256
	phi 	rf
	ldi 	v2&255
	plo 	rf

;
;	Now we have the right hand term in RF, R(X) points to the operator, then low left then high left
;

	lda 	r2 							; restore the operator and pop off the stack.
	xri 	'+'							; is it + (add)
	bnz 	__NotPlus
;
;	16 bit addition
;	
	glo 	rf 							; low byte
	add		
	str 	r2
	ghi 	rf 							; high byte
	inc 	r2
	adc
	br 		__WriteHighAndExit

__NotPlus:
	xri 	'+'!'*'						; is it * (multiply)
	bnz 	__NotMultiply
;
;	16 bit multiplication....... slow but compact. 1 x 65535 about 16 seconds :)
;	
__MultiplyLoop:
	glo 	rf 							; check completed (e.g. RF = 0)
	bnz 	__MultiplyContinuing
	ghi 	rf
	bz 		__SaveREtoResult
__MultiplyContinuing:
	dec 	rf 				 			; one fewer add
	glo 	re
	add
	plo 	re
	ghi 	re
	inc 	r2
	adc
	phi 	re
	dec 	r2
	br 		__MultiplyLoop


__NotMultiply:
	xri 	'*'!'/'						; check if it is divide.
	bnz 	__NotAddMulDiv 				; it is not + * or /
;
;	16 bit division. like multiply, 65535 / 1 takes about 16 seconds :)
;
	glo 	rf 							; check divide by zero (e.g. RF = 0)
	bnz 	__DivideLoop 
	ghi 	rf
	bz 		__SaveREToResult 			; if RF is zero then return 0 - so n/0 = 0 in this.
__DivideLoop:
	glo 	rf 							; subtract once.
	sd 
	plo 	rd 							; save result in RD in case we borrow out.
	ghi 	rf
	inc 	r2
	sdb 		
	bnf 	__DivideCompleted 			; if DF = 0 we have finished the division.	
	stxd 								; save a-b back on stack space.	
	glo 	rd
	str 	r2
	inc 	re 							; we've done it once.
	br 		__DivideLoop

__DivideCompleted:
	ldn 	r2 							; this is remainder high - TODO: save it
	dec 	r2 							
	ldn 	r2 							; this is remainder low. - TODO: save it.

__SaveREToResult:
	glo 	re 							; copy RE to the final result.
	str 	r2
	inc 	r2
	ghi 	re
	br 		__WriteHighAndExit						

__NotAddMulDiv: 						; we don't know, so we do -, it's probably - > < =
	glo 	rf 							
	sd 
	str 	r2
	ghi 	rf
	inc 	r2
	sdb
__WriteHighAndExit:	
	stxd
;
;	Subtraction.
;
EndEvaluate:							; R2 points to the result.
	br 		EndEvaluate