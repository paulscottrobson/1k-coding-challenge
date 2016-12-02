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
#include "sys_processor.h"
#include "sys_debug_system.h"
#include "hardware.h"

// *******************************************************************************************************************************
//														   Timing
// *******************************************************************************************************************************

#define CRYSTAL_CLOCK 	(2000000L)													// Clock cycles per second (2Mhz)
#define CYCLE_RATE 		(CRYSTAL_CLOCK/8)											// Cycles per second (8 clocks per cycle)
#define FRAME_RATE		(60)														// Frames per second (60)
#define CYCLES_PER_FRAME (CYCLE_RATE / FRAME_RATE)									// Cycles per frame (3,728)

// *******************************************************************************************************************************
//														CPU / Memory
// *******************************************************************************************************************************

static BYTE8 ramMemory[MEMORYSIZE];													// R/W Memory

// *******************************************************************************************************************************
//													   Port Interfaces
// *******************************************************************************************************************************


#include "__1802ports.h"															// Default connections.

// *******************************************************************************************************************************
//											 Memory and I/O read and write macros.
// *******************************************************************************************************************************


#define READ() 		MB = ramMemory[MA];
#define WRITE() 	ramMemory[MA] = MB;

#include "__1802support.h"


// *******************************************************************************************************************************
//														Reset the CPU
// *******************************************************************************************************************************

void CPUReset(void) {
	HWIReset();																		// Reset hardware
	__1802Reset();																	// Reset CPU
	Cycles = 2000;																	// So no immediate Interrupt
}

// *******************************************************************************************************************************
//												Execute a single instruction
// *******************************************************************************************************************************

BYTE8 CPUExecuteInstruction(void) {

	FETCH();																		// Read the opcode

	switch(MB) {																	// Execute it.
		#include "__1802opcodes.h"
	}
	Cycles -= 2;																	// Instruction is two cycles
	if ((Cycles & 0x8000) == 0) return 0;											// Not completed a frame.

    if (IE != 0) {                      											// and interrupts are enabled and display on.
		__1802Interrupt();          												// Fire an interrupt
    }
   	HWIEndFrame();																	// End of Frame code
	Cycles = Cycles + CYCLES_PER_FRAME;												// Adjust this frame rate.
	return FRAME_RATE;																// Return frame rate.
}

#ifdef INCLUDE_DEBUGGING_SUPPORT

// *******************************************************************************************************************************
//		Execute chunk of code, to either of two break points or frame-out, return non-zero frame rate on frame, breakpoint 0
// *******************************************************************************************************************************

BYTE8 CPUExecute(WORD16 breakPoint1,WORD16 breakPoint2) { 
	do {
		BYTE8 r = CPUExecuteInstruction();											// Execute an instruction
		if (r != 0) return r; 														// Frame out.
	} while (R[P] != breakPoint1 && R[P] != breakPoint2);							// Stop on breakpoint.
	return 0; 
}

// *******************************************************************************************************************************
//									Return address of breakpoint for step-over, or 0 if N/A
// *******************************************************************************************************************************

WORD16 CPUGetStepOverBreakpoint(void) {
	BYTE8 opcode = CPUReadMemory(R[P]);												// Current opcode.
	if (opcode >= 0xD0 && opcode <= 0xDF) return ((R[P])+1) & 0xFFFF;				// If SEP Rx then step is one after.
	return 0;																		// Do a normal single step
}

// *******************************************************************************************************************************
//												Read/Write Memory
// *******************************************************************************************************************************

BYTE8 CPUReadMemory(WORD16 address) {
	BYTE8 _MB = MB;WORD16 _MA = MA;BYTE8 result;
	MA = address;READ();result = MB;
	MB = _MB;MA = _MA;
	return result;
}

void CPUWriteMemory(WORD16 address,BYTE8 data) {
	BYTE8 _MB = MB;WORD16 _MA = MA;
	MA = address;MB = data;WRITE();
	MB = _MB;MA = _MA;
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
	s.d = D;s.df = DF;s.p = P;s.x = X;s.t = T;s.q = Q;s.ie = IE;					// Registers
	for (int i = 0;i < 16;i++) s.r[i] = R[i];									// 16 bit Registers
	s.cycles = Cycles;s.pc = R[P];													// Cycles and "PC"
	return &s;
}

#endif
