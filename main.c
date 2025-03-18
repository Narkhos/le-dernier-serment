#include "lib.h"
#include "define.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"
#include "parser/parser.h"
#include "parser/game.h"
#include "sound.h"
#include "menu.h"
#include "dialog.h"
#include "book.h"
#include "alchemy.h"
#include "scenes.h"

#define screen(x,y) ((unsigned char*)precalc_vram[y]+(x>>1))

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
    ld c,#0xff          ;; disable all roms
    ld hl, #_start222         ;; execution address for program
    call #0xbd16  ;;mc_start_program    ;; start it

    _start222:: nop

    call #0xbccb  ;;kl_rom_walk     ;; enable all roms

	;; ld c, #7
    ;; call #0xbcce  ;;kl_rom_walk     ;; enable rom 7, supposedly amsdos rom 

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

void game() {
	int i;
	// Init icones
	setBank(BANK_MODE_SCREEN);
	LoadFile("COMPASS.SCR", currentImage);
	displayIcon(15, 0, 6, 24);
	LoadFile("SABLIER.SCR", currentImage);
	displayIcon(58, 0, 6, 24);
	LoadFile("PNORMAL.SCR", currentImage);
	displayIcon(64, 16, 12, 64);

	setBank(BANK_MODE_DATABASE);


	// currentSceneId = SCN_PARSER;
	currentSceneId = SCN_INTRO;
	// turn = 1;
	currentLocationId = NO_OBJECT;
	changeLocation(CHURCH_OUTDOOR);

	// Test des différentes fins
	// menuOk();
	// endingMessage(END_FREEDOM);
	// menuOk();
	// endingMessage(END_ORDER);
	// menuOk();
	// endingMessage(END_BALANCE);
	// menuOk();
	// endingMessage(END_BOMB);
	// menuOk();

	// changeLocation(M_HUT_INDOOR);
	// changeLocation(GOD_ROOM);
	// changeLocation(LABORATORY);
	// changeLocation(SECRET_ROOM);
	// changeLocation(CRYPT);

	// TESTS DIALOG
	// introNahash();
	// introEpreuve();
	// finEpreuve();
	// dialogueErmite();
	// dialogueDieu();
	// badEnding();
	// recipeTea();
	// recipeBook();
	// setHeroStatus(INVISIBLE);
	setBank(BANK_MODE_SCREEN);
	setCursor(0,0);
	printf("\x96\x9A\x9A\x9A\x9A\x9A\x98\r\n");
	printf("\x93\x99");

#if LANGUAGE == 1 // French
	setCursor(1,4);
	printf("LE");
	setCursor(1,6);
	printf("DERNIER");
	setCursor(1,8);
	printf("SERMENT");
#endif
#if LANGUAGE == 2 // English
	setCursor(3,4);
	printf("THE");
	setCursor(3,6);
	printf("LAST");
	setCursor(3,8);
	printf("OATH");
#endif

	setCursor(9,11);
	printf("\x96\x9C\r\n");
	printf("\x93\x9A\x9A\x9A\x9A\x9A\x9A\x9A\x9A\x9A\x99\r\n");


	setCursor(32,0);
	printf("\x92\x9A\x9A\x9A\x9A\x9A\x9A\x9C\r\n");
	setCursor(38,1);
	printf("\x93\x99");

	setCursor(29,11);
	printf("\x96\x9C");
	setCursor(29,12);
	printf("\x93\x9A\x9A\x9A\x9A\x9A\x9A\x9A\x9A\x9A\x99");

	setCursor(0,23);
	for(i=0; i<40;i++) {
		printf("\x9A");
	}
	setBank(BANK_MODE_DATABASE);
	while(1) {
		(*scenes[currentSceneId])();
	}
}

void mainLoop() {
	screen_mode1();
	set_paletteMode1(0,0,0,0);

	// bank switch
	setBank(BANK_MODE_DATABASE);

	LoadFile("DATABASE.BIN", 0xC000);
	objects = (struct Object*)0xC000;

	LoadFile("DATATEXT.BIN", 0xEF10);
	dataText = (struct DataText*)0xEF10;

	setChrTable();
	
	LoadFile("CHARSET.BIN", charset);

	// Test de sauvegarde
	// SaveFile("SAVEAA.BIN", charset, 66*8);

	game();
}

void main(void)
{
	SetupDOS();
	mainLoop();
}