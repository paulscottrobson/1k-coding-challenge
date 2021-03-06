// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.cpp
//		Purpose:	Hardware Interface
//		Created:	1st November 2016
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdlib.h>
#include "sys_processor.h"
#include "hardware.h"
#include "gfx.h"																// Want the keyboard access.

static WORD16 videoMemoryAddress = 0xFFFF;										// 1802 Video Memory Address
static BYTE8  screenIsOn = 0;													// 1861 turned on
static BYTE8  *videoMemoryPointer;												// Physical screen memory ptr in SRAM

// *******************************************************************************************************************************
//													Hardware Reset
// *******************************************************************************************************************************

void HWIReset(void) {
}

// *******************************************************************************************************************************
//											Process keys passed from debugger
// *******************************************************************************************************************************

BYTE8 HWIProcessKey(BYTE8 key,BYTE8 isRunMode) {
	if (isRunMode) {															// In run mode, push 0-9 A-F
	}
	return key;
}

// *******************************************************************************************************************************
//												Called at End of Frame
// *******************************************************************************************************************************

void HWIEndFrame(void) {
}
