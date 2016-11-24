// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_debug_cc.c
//		Purpose:	Debugger Code (System Dependent)
//		Created:	24th November 2016
//		Author:		Paul Robson (paul@robsons->org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gfx.h"
#include "sys_processor.h"
#include "debugger.h"
#include "hardware.h"

static const char*_mnemonics[256] = {												// Mnenonics array.
#include "_1801_disasm.h"
};

#define DBGC_ADDRESS 	(0x0F0)														// Colour scheme.
#define DBGC_DATA 		(0x0FF)														// (Background is in main.c)
#define DBGC_HIGHLIGHT 	(0xFF0)

// *******************************************************************************************************************************
//											This renders the debug screen
// *******************************************************************************************************************************

static const char *labels[] = { "D","DF","P","X","T","IE","RP","RX","CY","BP", NULL };

void DBGXRender(int *address,int showDisplay) {
	int n = 0;
	char buffer[32];
	CPUSTATUS *s = CPUGetStatus();
	GFXSetCharacterSize(32,23);
	DBGVerticalLabel(15,0,labels,DBGC_ADDRESS,-1);									// Draw the labels for the register

	#define DN(v,w) GFXNumber(GRID(18,n++),v,16,w,GRIDSIZE,DBGC_DATA,-1)			// Helper macro

	n = 0;
	DN(s->d,2);DN(s->df,1);DN(s->p,1);DN(s->x,1);DN(s->t,2);DN(s->ie,1);	// Registers
	DN(s->pc,4);DN(s->r[s->x],4);DN(s->cycles,4);DN(address[3],4);					// Others

	for (int i = 0;i < 16;i++) {													// 16 bit registers
		sprintf(buffer,"R%x",i);
		GFXString(GRID(i % 4 * 8,i/4+12),buffer,GRIDSIZE,DBGC_ADDRESS,-1);
		GFXString(GRID(i % 4 * 8+2,i/4+12),":",GRIDSIZE,DBGC_HIGHLIGHT,-1);
		GFXNumber(GRID(i % 4 * 8+3,i/4+12),s->r[i],16,4,GRIDSIZE,DBGC_DATA,-1);
	}

	int a = address[1];																// Dump Memory.
	for (int row = 17;row < 23;row++) {
		GFXNumber(GRID(2,row),a,16,4,GRIDSIZE,DBGC_ADDRESS,-1);
		GFXCharacter(GRID(6,row),':',GRIDSIZE,DBGC_HIGHLIGHT,-1);
		for (int col = 0;col < 8;col++) {
			GFXNumber(GRID(7+col*3,row),CPUReadMemory(a),16,2,GRIDSIZE,DBGC_DATA,-1);
			a = (a + 1) & 0xFFFF;
		}		
	}

	int p = address[0];																// Dump program code. 
	int opc;

	for (int row = 0;row < 11;row++) {
		int isPC = (p == ((s->pc) & 0xFFFF));										// Tests.
		int isBrk = (p == address[3]);
		GFXNumber(GRID(0,row),p,16,4,GRIDSIZE,isPC ? DBGC_HIGHLIGHT:DBGC_ADDRESS,	// Display address / highlight / breakpoint
																	isBrk ? 0xF00 : -1);
		opc = CPUReadMemory(p);p = (p + 1) & 0xFFFF;								// Read opcode.
		strcpy(buffer,_mnemonics[opc]);												// Work out the opcode.
		char *at = buffer+strlen(buffer)-1;											// 2nd char from end
		if (*at == '*') {															// Operand ?
			sprintf(at,"%02x",CPUReadMemory(p));
			p = (p+1) & 0xFFFF;
		}
		GFXString(GRID(5,row),buffer,GRIDSIZE,isPC ? DBGC_HIGHLIGHT:DBGC_DATA,-1);	// Print the mnemonic
	}

	if (showDisplay) {
		p = HWIGetPageAddress();														// wherever the screen is, it's now in R0.
		SDL_Rect rc;rc.x = _GFXX(0);rc.y = _GFXY(14)/2;									// Whole rectangle.
		int vLines = 32;
		rc.w = 32 * GRIDSIZE * 6;rc.h = 16 *GRIDSIZE * 8; 										
		rc.w = rc.w/64*64;rc.h = rc.h/vLines*vLines;									// Make it /64 /32 (etc)
		SDL_Rect rcPixel;rcPixel.h = rc.h/vLines;rcPixel.w = rc.w / 64;					// Pixel rectangle.
        SDL_Rect rcDraw;rcDraw.h = rcPixel.h/2;rcDraw.w = rcPixel.w/2;
		GFXRectangle(&rc,0x0);															// Fill it black
		if (p != 0xFFFF && HWIGetScreenOn() != 0) {										// If actually valid.
			for (int i = 0;i < 32*vLines;i++) {
				int bt = CPUReadMemory(p+i);
				rcDraw.x = rc.x + rcPixel.w * 8 * (i % 8);								// Horizontal position
				rcDraw.y = rc.y + i / 8 * rcPixel.h;
				for (int b = 0;b < 8;b++) {
					if (bt & (0x80 >> b)) GFXRectangle(&rcDraw,0xF80);
					rcDraw.x += rcPixel.w;
				}			
			}
		}
	}
}	
