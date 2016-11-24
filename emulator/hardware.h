// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.h
//		Purpose:	Hardware Interface (header)
//		Created:	1st November 2016
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _HARDWARE_H
#define _HARDWARE_H

void HWISetPageAddress(WORD16 r0);
WORD16 HWIGetPageAddress(void);
void HWISetScreenOn(BYTE8 isOn);
BYTE8 HWIGetScreenOn(void); 
BYTE8 HWIProcessKey(BYTE8 key,BYTE8 isRunMode);
void HWIEndFrame(void);
void HWIReset(void);

#endif
