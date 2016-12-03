// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.c
//		Purpose:	Hardware handling routines 
//		Created:	3rd December 2016
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include "gfx.h"

#include "sys_processor.h"

#define DIRTY_GROUPING 	(4)													// Char grouping dirty flags

static BYTE8 videoRAM[512];													// 32 x 8 TVT Memory
static BYTE8 isInitialised = 0;												// Non zero when initialised
static BYTE8 vRAMPointer = 0;												// offset into video RAM
static BYTE8 videoLast = 0;													// Last value written to TVT
static BYTE8 pendingKey = 0;												// Key ready ?

//	The dirty flag being in character groups of 4 is because the STM7920, the original LCD target,
//	takes 16 bit horizontal words, which with a 3x5 font has 4 characters in it. If using a OLED
//	128x64 this may incur a small time penalty.

// *******************************************************************************************************************************
//													Reset all hardware
// *******************************************************************************************************************************

void HWIReset(void) {
	if (isInitialised == 0) {
		isInitialised = 1;
		for (WORD16 n = 0;n < 512;n++) videoRAM[n] = n; 					// Clear VRAM (wouldn't happen)
		pendingKey = 0;														// Clear keyboard buffer
	}
}

// *******************************************************************************************************************************
//													Handle on end of frame.
// *******************************************************************************************************************************

void HWIEndFrame(void) {
}

// *******************************************************************************************************************************
//														Read video memory 
// *******************************************************************************************************************************

BYTE8 HWIReadVideoMemory(WORD16 offset) {
	return videoRAM[offset];
}

// *******************************************************************************************************************************
//									Debugger key intercept handler
// *******************************************************************************************************************************

int HWIProcessKey(int key,int isRunTime) {
	if (key != 0 && isRunTime != 0) {										// Running and key press
		BYTE8 newKey = GFXToASCII(key,1);									// Convert to ASCII
		if (newKey != 0) pendingKey = newKey;								// Put pending key in buffer
	}
	return key;
}

// *******************************************************************************************************************************
//											Read keyboard
// *******************************************************************************************************************************

BYTE8 HWIReadKeyboard(void) {
	BYTE8 rv = 0;
	if (pendingKey != 0) {													// Key waiting.
		rv = pendingKey | 0x80;												// Return it with bit 7 set
		pendingKey = 0;														// Clear buffer
	}
	return rv;
}

// Implemented so the strobe vanishes immediately on reading. While not technically correct, the
// coder cannot know at IN 0 where it is in the strobe, it *might* finish in the next cycle. Coders
// could read the keyboard and then re-read it to get the key again, but shouldn't !

// *******************************************************************************************************************************
//									Write byte to video memory port
// *******************************************************************************************************************************

void HWIWriteVideoPort(BYTE8 n) {
}