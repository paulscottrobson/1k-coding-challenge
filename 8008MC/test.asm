	
		cpu		8008new

TVPort = 0eh
CassetteOutputPort = 08h
CassetteInputPort = 01h
KeyboardPort = 00h

CWWriteHeader = 0101h 									; header loop count ($FFFF)
CWTrailerCount = 0101h 									; trailer loop count ($7FFF)
CWBitLength = 01o 										; length of one bit write. (40o)
CWByteSpacing = 01o 									; gap between bytes. (100o)

		org 	0
		rst 	8
		db 		255
		org 	8
		;jmp 	Speeding
		;jmp	CassetteRead2	
		;jmp 	CassetteWrite
		jmp 	RunningDisplay
		jmp 	KBToMemory
		jmp 	TVTest

;		db		"Hello world !!!!!"
;		db 		0,1,2,3,4,5
;		db 		255,254,253,252,251

Speeding:
		call 	HomeErase
SPNext:
		mvi 	h,Counter/256
		mvi 	l,Counter&255
		mvi 	a,0FFh
		out 	TVPort
		xra 	a
		out 	TVPort
SPPaint:mov 	a,m
		ori 	080h!'0'
		out 	TVPort
		xra 	a
		out 	TVPort
		inr 	l
		mov 	a,l
		cpi 	(Counter&255)+8
		jnz 	SPPaint
SPDec:	dcr 	l
		mov 	a,m
		adi 	1
		mov 	m,a
		cpi 	10
		jnz 	SPNext
		mvi 	m,0
		jmp 	SPDec


Counter:

; *****************************************************************************************************
;									TV Character Generator Test
; *****************************************************************************************************

		org 	0200o
TVTest:
		mvi 	a,0FFh									; home cursor first time (0xFF)
		out 	TVPort
		xra 	a
		out		TVPort
		mov 	b,a
TVTLoop:
		mov 	a,b										; get number
		ori 	080h									; set bit 7
		out 	TVPort 									; write to TVT
		xra 	a
		out 	TVPort
		inr 	b 										; next char
		jnz 	TVTLoop
		hlt

; *****************************************************************************************************
;										Keyboard to Memory
; *****************************************************************************************************

		org		0230o
KBToMemory:
		mvi 	l,0 									; point HL to $100
		mvi 	h,1
KBToMemoryLoop:
		in 		KeyboardPort 							; wait for keyboard press
		cpi 	0200o 									; bit 7 high
		jc 		KBToMemoryLoop 							; keep going until it is.
		nop												; wait for sync.
		nop
		mov 	m,a 									; save to memory

		mvi 	b,0 									; delay makes sure the keyboard strobe is clear.
KBStrobe:
		inr 	b
		jnz 	KBStrobe

		mov 	a,l 									; write L to the display LEDs
		out 	15
		inr 	l 										; next byte
		jnz 	KBToMemoryLoop 							
		inr 	h 										; next page
		mov 	a,h 									; reached page 3 ?
		cpi 	3
		jnz 	KBToMemoryLoop 							; if no, try again.
		hlt 	

; *****************************************************************************************************
;											Running TV Display
; *****************************************************************************************************

		org 	01000o
RunningDisplay:
		call 	HomeErase
		mvi 	e,0150o
		call 	Spacer
		mvi 	h,RDMessage / 256
		mvi 	l,RDMessage & 255
		mvi 	e,022o
		call 	Writer
;		call 	Timer
		mvi 	h,0 									; HL to 340
		mvi 	l,0340o
		mvi 	a,0240o						
RDFill:	mov 	m,a 									; fill 340 to 377
		inr 	l
		jnz 	RDFill

RDMainLoop:
		mvi 	d,0341o									; D points to 341
RDKey:	in 	 	KeyboardPort 							; get key
		cpi 	200o
		jc 		RDKey
		mov 	e,a 									; save key in E

RDShift:
		mov 	l,d 									; HL points to buffer
		mov 	a,m 									; make room in buffer
		dcr 	l
		mov 	m,a 
		inr 	d
		jnz 	RDShift
		mvi 	l,0377o 								; character in end of buffer		
		mov 	m,e

		mvi 	a,0377o 								; home cursor
		out 	TVPort
		xra 	a
		out 	TVPort

		mvi 	l,340o 									; point L to typed string
RDOutText:												; output the buffer.
		mov 	a,m
		out 	TVPort
		xra 	a
		out 	TVPort
		inr 	l
		jnz 	RDOutText
		jmp 	RDMainLoop

RDMessage:
		db	 	"Running TV Display"

; *****************************************************************************************************
;								Cassette Dumper (Read into memory)
; *****************************************************************************************************

		org 	03000o

CassetteRead:
		mvi 	h,0										; put start address intl HL
		mvi 	l,0
CRNextByte:
		mvi 	c,8 									; bits to read in
		mvi 	d,0										; byte read in
CRWaitStartBit:
		in 		CassetteInputPort 						; check level
		ani 	1
		jnz 	CRWaitStartBit 							; read until a bit '0' found (start bit)
		mvi 	b,CWBitLength * 3 / 2 					; time till half way through next bit - stablised
CRWaitBit0:
		dcr 	b
		jnz 	CRWaitBit0

CRGetNextBit:
		in 		CassetteInputPort 						; read bit into A
		add 	d 										; add to D
		rrc 											; rotate right circularly.
		mov 	d,a 									; put back in D.

		mvi 	b,CWBitLength 							; go to next bit
CRWaitNextBit:
		dcr 	b
		jnz 	CRWaitNextBit
		dcr 	c 										; read all 8 bits of byte in.
		jnz 	CRGetNextBit 							; no, go till complete.
		mov 	m,d 									; store result in.
		inr 	l 										; increment Low ptr
		jnz 	CRNextByte
		inr 	h
		mov 	a,h 									; read all in (1024 bytes)
		cpi 	4
		jnz 	CRNextByte
		hlt

; *****************************************************************************************************
;										Utility functions
; *****************************************************************************************************

		org 	03100o
HomeErase:												; clear screen home cursor
		mvi 	a,0FFh
		out 	TVPort
		xra 	a
		mov 	b,a
		out 	TVPort
		out 	15
HELoop:
		mvi 	a,0240o
		out 	TVPort
		xra 	a
		out 	TVPort
		inr 	b
		jnz 	HELoop
		ret

Spacer:													; print E spaces
		mvi 	a,0240o
		out 	TVPort
		xra 	a
		out 	TVPort
		dcr 	e
		jnz 	Spacer
		ret

Writer:													; print string at HL length D
		mov 	a,m
		ori 	080h									; **** added so we can use DS, bit 7 not set.
		out 	TVPort
		xra 	a
		out 	TVPort
		inr 	l
		dcr 	e
		jnz 	Writer
		ret

		org 	03150o
		db 		"Dumped OK"

		org 	03162o

Timer:	mvi 	b,0 									; delay of about 5 seconds.
		mvi 	c,0
TMRLoop:
		inr 	c
		jnz 	TMRLoop
		inr 	b
		jnz 	TMRLoop
		ret

; *****************************************************************************************************
;						Cassette Loader (Note, loads ONTO cassette)
; *****************************************************************************************************

		org 	3200o
CassetteWrite:
		mvi 	a,1										; cassette out on
		out 	CassetteOutputPort 
		nop
		mvi 	b,CWWriteHeader & 255 					; writeheader -> BC
		mvi 	c,CWWriteHeader / 256
CWHeader: 												; write the header out, pausing.
		dcr 	c
		jnz 	CWHeader
		dcr 	b
		jnz 	CWHeader

		mvi 	h,0 									; HL to start $0000
		mvi 	l,0
		mvi 	d,3 									; DE to end $3FFF
		mvi 	e,0377o

CWMainLoop:
		mvi 	c,011o 									; C = %00 001 001

		mov 	a,c 									; retrieve C
		ral 											; rotate left through carry (first time C = 0)
		mov 	a,m 									; read location to write out.
		ral 											; put msb bit into carry,  0 into bit 0
CWNextBitOut:
		out 	CassetteOutputPort 						; write to tape output (0 first time)
		mvi 	b,CWBitLength
CWBitDelay:												; time to write the bit to tape.
		dcr 	b
		jnz 	CWBitDelay
		rar 											; rotate byte right (first time, byte is back)
		dcr 	c 										; done it 9 times (1 start bit [0], 8 data bits)
		jnz 	CWNextBitOut 							; no, go back and try again.	

		mvi 	a,1										; tape out back on which is the default state
		out 	CassetteOutputPort
		mvi 	b,CWByteSpacing							; spacing delay
CWSpacing:	
		dcr 	b
		jnz 	CWSpacing

		mov 	a,h 									; check if done all the writing
		cmp 	d
		jz 		CWCheckEnd

		inr 	l 										; go to next byte.
		jnz 	CWMainLoop
		inr 	h
		jmp 	CWMainLoop

CWCheckEnd:
		mov 	a,l 									; do LSBs match ?
		cmp 	e
		jz 		CWCompleted
		inr 	l 										; no , inc l only required.
		jmp 	CWMainLoop

CWCompleted:
		mvi 	c,CWTrailerCount/256 					; write the end header
		mvi 	b,CWTrailerCount&255
CWTrailer:
		dcr 	b
		jnz 	CWTrailer
		dcr 	c
		jnz 	CWTrailer
		xra 	a
		out		CassetteOutputPort 						; cassette o/p off
		hlt

; *****************************************************************************************************
;								Cassette Dumper (Read into memory)
; *****************************************************************************************************

		align 	256

CassetteRead2:
		mvi 	h,0										; put start address $0000 into HL
		mvi 	l,0 									; (not needed if run from boot)
		mvi 	d,4 									; number of pages to load.

C2NextByte:
		mvi 	c,8 									; bits to read in
		mvi	 	m,0										; byte read in (H is always zero)

C2WaitStartBit:
		in 		CassetteInputPort 						; check level which is in cassette bit 0
		rrc
		jc 		C2WaitStartBit 							; read until a bit '0' found (start bit)
		mvi 	b,CWBitLength * 3 / 2 					; time till half way through next bit - stablised
C2WaitBit:												; short delay till next bit sampled.
		dcr 	b
		jnz 	C2WaitBit

		in 		CassetteInputPort 						; read bit into A
		add 	m 										; add to M (current value)
		rrc 											; rotate right circularly.
		mov 	m,a 									; put back in M.

		mvi 	b,CWBitLength 							; set delay till next bit
		dcr 	c 										; read all 8 bits of byte in.
		jnz 	C2WaitBit 								; no, go till complete.

		inr 	l 										; increment Low ptr
		jnz 	C2NextByte
		rst 	0

		inr 	h 										; increment High ptr
		dcr 	d 										; decrement page-to-load counter
		jnz 	C2NextByte
		hlt

; *****************************************************************************************************
;								Cassette Dumper (Read into memory)
;
;	This fits into a single 32x8 8223 ROM. It is identical in format to the 2 ROM Cassette Dumper
;	but it only loads 256 bytes into Page 0, after which it transfers control to the code at Page 0
;
;	The core of the code is identical to Dr. Suding's but it removes duplicate code and simplifies
;	removing one delay loop and the final h-register test.
;
;	Effectively it is a double-boot loader ; it loads either a short program or a more complex tape
;	loader which could have check summing and loading into different pages.
;
;	It is exactly 32 bytes long. 
;
; *****************************************************************************************************

		align 	256

CassetteRead32Byte:
		mvi 	h,0										; put start address $0000 into HL
		mov 	l,h 									; (not needed if run from boot)

C3NextByte:
		mvi 	c,8 									; bits to read in
		mov	 	m,h										; byte read in (H is always zero)

C3WaitStartBit:
		in 		CassetteInputPort 						; check level which is in cassette bit 0
		rrc
		jc 		C3WaitStartBit 							; read until a bit '0' found (start bit)
		mvi 	b,CWBitLength * 3 / 2 					; time till half way through next bit - stablised
C3WaitBit:												; short delay till next bit sampled.
		dcr 	b
		jnz 	C3WaitBit

		in 		CassetteInputPort 						; read bit into A
		add 	m 										; add to M (current value)
		rrc 											; rotate right circularly.
		mov 	m,a 									; put back in M.

		mvi 	b,CWBitLength 							; set delay till next bit
		dcr 	c 										; read all 8 bits of byte in.
		jnz 	C3WaitBit 								; no, go till complete.

		inr 	l 										; increment Low ptr
		jnz 	C3NextByte
		rst 	0										; "jmp 0000" - in one instruction.
		
