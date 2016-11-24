// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_processor.c
//		Purpose:	Processor Emulation.
//		Created:	1st November 2016
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdlib.h>
#ifdef WINDOWS
#include <stdio.h>
#endif
#include "sys_processor.h"
#include "sys_debug_system.h"
#include "hardware.h"

// *******************************************************************************************************************************
//														   Timing
// *******************************************************************************************************************************

#define CRYSTAL_CLOCK 	(1000000L)													// Clock cycles per second (1.Mhz)
#define CYCLE_RATE 		(CRYSTAL_CLOCK/8)											// Cycles per second (8 clocks per cycle)
#define FRAME_RATE		(60)														// Frames per second (60)
#define CYCLES_PER_FRAME (CYCLE_RATE / FRAME_RATE)									// Cycles per frame 
#define SCAN_LINES 		(262) 														// Scan lines per frame (262)
#define CYCLES_PER_LINE  (CYCLES_PER_FRAME / SCAN_LINES)							// Cycles per scan line 

//	Now, if the screen is on in 64x32 mode, 4 scan lines per pixel, then for 128 of these lines the CPU will 
//	be generating video, leaving only 134 for the CPU. We adjust CYCLES_PER_LINE dynamically to cope with this.

// *******************************************************************************************************************************
//														CPU / Memory
// *******************************************************************************************************************************

static BYTE8  D,DF,T,P,X,IE,temp8;
static WORD16 temp16,Cycles,R[16];

static BYTE8 ramMemory[MEMORYSIZE];													// R/W Memory

// *******************************************************************************************************************************
//													   Port Interfaces
// *******************************************************************************************************************************

#include "_1801_ports.h"															// Default connections.

// *******************************************************************************************************************************
//											 Memory and I/O read and write macros.
// *******************************************************************************************************************************

#define READ(a) 	ramMemory[(a) & MEMORYMASK]
#define WRITE(a,d) 	ramMemory[(a) & MEMORYMASK] = (d)
#define FETCH(a)    ramMemory[(R[P]++) & MEMORYMASK]

// *******************************************************************************************************************************
//														Reset the CPU
// *******************************************************************************************************************************

#include "_1801_include.h"

void CPUReset(void) {
	HWIReset();																		// Reset hardware
	_1801Reset();																	// Reset CPU
	Cycles = 2000;																	// So no immediate Interrupt
}

// *******************************************************************************************************************************
//												Execute a single instruction
// *******************************************************************************************************************************

BYTE8 CPUExecuteInstruction(void) {

	switch(FETCH()) {																// Execute it.
		#include "_1801_opcodes.h"
	}
	Cycles -= 2;																	// Instruction is two cycles
	if ((Cycles & 0x8000) == 0) return 0;											// Not completed a frame.
																					// (Cycles is unsigned 16 bit int)
    
    if (IE != 0) _1801Interrupt();                                                  // Interrupt.
	HWISetPageAddress(R[0]);                      									// Set the display address.
	HWIEndFrame();																	// End of Frame code
	Cycles = Cycles + CYCLES_PER_FRAME;												// Adjust this frame rate.
    if (HWIGetScreenOn()) Cycles = Cycles - 32 * 2 * CYCLES_PER_LINE;               // Adjust if screen on for DMA fetch.
	return FRAME_RATE;																// Return frame rate.
}

//
//  Note: we never do any DMA fetching, so we leave R0 untouched, obviously it would in real life increase during the frame
//  and be reset at VSync/Interrupt. Because R0 is never touched, we can assume R0 is top of screen.
//
#ifdef INCLUDE_DEBUGGING_SUPPORT

// *******************************************************************************************************************************
//		Execute chunk of code, to either of two break points or frame-out, return non-zero frame rate on frame, breakpoint 0
// *******************************************************************************************************************************

BYTE8 CPUExecute(WORD16 breakPoint1,WORD16 breakPoint2) { 
	do {
		BYTE8 r = CPUExecuteInstruction();											// Execute an instruction
		if (r != 0) return r; 														// Frame out.
	} while (R[P] != breakPoint1 && R[P] != breakPoint2);								// Stop on breakpoint.
	return 0; 
}

// *******************************************************************************************************************************
//									Return address of breakpoint for step-over, or 0 if N/A
// *******************************************************************************************************************************

WORD16 CPUGetStepOverBreakpoint(void) {
	BYTE8 opcode = CPUReadMemory(R[P]);												// Current opcode.
	if (opcode >= 0xD0 && opcode <= 0xDF) return R[P]+1;                			// If SEP Rx then step is one after.
	return 0;																		// Do a normal single step
}

// *******************************************************************************************************************************
//												Read/Write Memory
// *******************************************************************************************************************************

BYTE8 CPUReadMemory(WORD16 address) {
	return READ(address);
}

void CPUWriteMemory(WORD16 address,BYTE8 data) {
    WRITE(address,data);
}

// *******************************************************************************************************************************
//												Load a binary file into RAM
// *******************************************************************************************************************************

#include <stdio.h>

void CPULoadBinary(const char *fileName) {
	FILE *f = fopen(fileName,"rb");
	fread(ramMemory,1,MEMORYSIZE,f);
	fclose(f);
}

// *******************************************************************************************************************************
//											Retrieve a snapshot of the processor
// *******************************************************************************************************************************

static CPUSTATUS s;																	// Status area

CPUSTATUS *CPUGetStatus(void) {
	s.d = D;s.df = DF;s.p = P;s.x = X;s.t = T;s.ie = IE;                        	// Registers
	for (int i = 0;i < 16;i++) s.r[i] = R[i];                   					// 16 bit Registers
	s.cycles = Cycles;s.pc = R[P];													// Cycles and "PC"
	return &s;
}

#endif
