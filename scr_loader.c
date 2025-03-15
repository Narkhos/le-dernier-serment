////////////////////////////////////////////////////////////////////////
// Load01.c
// Mochilote - www.cpcmania.com
////////////////////////////////////////////////////////////////////////
#include "scr_loader.h"

////////////////////////////////////////////////////////////////////////
//SetupDOS - Prepare DOS for file load
////////////////////////////////////////////////////////////////////////
void SetupDOS()
{
	//Based on http://cpctech.cpc-live.com/source/loader.html
	__asm
		ld l, 2 (ix) ;stack return address
		ld h, 3 (ix) ;stack return address
		ld (_stack+1), hl

		;;------------------------------------------------------------------------
		;; store the drive number the loader was run from
		ld hl,(#0xbe7d)
		ld a,(hl)                  
		ld (_drive+1),a

		;;------------------------------------------------------------------------
		ld c,#0xff					;; disable all roms
		ld hl, #_start222					;; execution address for program
		call #0xbd16	;;mc_start_program		;; start it

		_start222:: nop

		call #0xbccb 	;;kl_rom_walk			;; enable all roms 

		;;------------------------------------------------------------------------
		;; when AMSDOS is enabled, the drive reverts back to drive 0!
		;; This will restore the drive number to the drive the loader was run from
		_drive: ld a, #0x00
		ld hl,(#0xbe7d)
		ld (hl),a		  

		_stack: ld hl, #0x0000
		push hl //one for sdcc ix pop
		push hl //two for return address
	__endasm;
}


////////////////////////////////////////////////////////////////////////
//Load filename to address
////////////////////////////////////////////////////////////////////////
unsigned char nFileNameLen = 0;
void LoadFile(char *sFileName, char *pLoadAddress)
{
	nFileNameLen = strlen(sFileName);
    // printf("%s\r\n", nFileNameLen);
    // return;
	__asm
		;; B = length of the filename in characters
		ld hl, #_nFileNameLen;
		ld b, (hl)

		;; HL = address of the start of the filename
		LD L, 4 (IX) ;sFileName
		LD H, 5 (IX) ;sFileName

		;; DE = address of a 2k buffer
		;; in disc mode: this buffer is not used when CAS IN DIRECT
		;; firmware function is used, so it is safe to put it anywhere
		;; you want.
		ld de, #0x0

		;; firmware function to open a file for reading
		call #0xbc77 ;;cas_in_open

		;; firmware function to load the entire file
		;; this will work with files that have a AMSDOS header (ASCII
		;; files do not have a header)
		;; HL = load address
		LD L, 6 (IX) ;pLoadAddress
		LD H, 7 (IX) ;pLoadAddress

		;; read file
		call #0xbc83 ;;cas_in_direct

		;; firmware function to close a file opened for reading
		call #0xbc7a ;;cas_in_close

	__endasm;
}