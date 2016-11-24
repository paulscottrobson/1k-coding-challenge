
	cpu 	1802
	
r0 = 0
r1 = 1
r2 = 2
r3 = 3
r4 = 4
r5 = 5

	dis
ShowIt:
	ldi 	080h
	plo 	r3
	sex 	r3
	inp 	4
	out 	4
	br 		ShowIt