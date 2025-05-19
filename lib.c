#include "lib.h"
#include "define.h"
#include "patch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTI 1

unsigned char char1,char2,char3,char4;
unsigned char aKeyboard[KEYBOARD_HW_LINES];
unsigned int precalc_vram[200];
unsigned char flags;
int err;
unsigned char dx,dy;

unsigned char get_key(enum _eKey eKey)
{
  unsigned char nKeyLine = eKey / 8;
  unsigned char nBit = eKey % 8;
  
  if(((unsigned char)1 << nBit & aKeyboard[nKeyLine]) == 0)
    return 1;
  
  return 0;
}


void check_controller()
{
  __asm
    di
    ld hl, #_aKeyboard
    ld bc,#0xf782
    out (c),c
    ld bc,#0xf40e
    ld e,b
    out (c),c
    ld bc,#0xf6c0
    ld d,b
    out (c),c
    ld c,#0x00
    out (c),c
    ld bc,#0xf792
    out (c),c
    ld a,#0x40
    ld c,#0x4a
    _loop:
    ld b,d
    out (c),a
    ld b,e
    ini
    inc a
    cp c
    jr c,_loop
    ld bc,#0xf782
    out (c),c
    ei
  __endasm;
}

void init_cpc_lib()
{
	unsigned char i;
	
	for (i=0;i<200;i++)
	{
		precalc_vram[i]=(0xC000 + ((i / 8u) * 80u) + ((i % 8u) * 2048u));		
		
	}
}

void intern_screen_mode1()
{
  __asm
    ld a, #1
    call #0xBC0E
  __endasm;
  
  //PALETE
  __asm
    ld a, #0
    ld b, #0 ;black
    ld c, b
    call #0xBC32 ;SCR SET INK

    ld a, #1
    ld b, #12 ;Yellow
    ld c, b
    call #0xBC32 ;SCR SET INK

    ld a, #2
    ld b, #25 ;Pastel Yellow    
    ld c, b
    call #0xBC32 ;SCR SET INK

    ld a, #3
    ld b, #24 ;Bright Yellow
    ld c, b
    call #0xBC32 ;SCR SET INK
  __endasm;

  //SCR SET BORDER 0
  __asm
    ld b, #0 ;#1 blue (#0 pour remettre en noir)
    ld c, b
    call #0xBC38
  __endasm;  
}

void screen_mode1()
{
	intern_screen_mode1();
	init_cpc_lib();
}

unsigned int get_time()
{
  unsigned int nTime = 0;

  __asm
    CALL #0xBD0D ;KL TIME PLEASE
    PUSH HL
    POP DE
    LD HL, #_char3
    LD (HL), D
    LD HL, #_char4
    LD (HL), E
  __endasm;

  nTime = (char3 << 8) + char4;

  return nTime;
}

void set_pixel_color0(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
{
  unsigned char nByte = *pByteAddress;

  if(nPixel == 0)
  {
    nByte &= 85;

    if(nColor & 1)
      nByte |= 128;

    if(nColor & 2)
      nByte |= 8;

    if(nColor & 4)
      nByte |= 32;

    if(nColor & 8)
      nByte |= 2;
  }
  else
  {
    nByte &= 170;

    if(nColor & 1)
      nByte |= 64;

    if(nColor & 2)
      nByte |= 4;

    if(nColor & 4)
      nByte |= 16;

    if(nColor & 8)
      nByte |= 1;
  }

  *pByteAddress = nByte;
}

void set_color(unsigned char nColorIndex, unsigned char nPaletteIndex)
{
  __asm
    ld a, 4 (ix)
    ld b, 5 (ix)
    ld c, b
    call #0xBC32 ;SCR SET INK
    __endasm;
}

void set_palette(const unsigned char *pPalette)
{
  unsigned char nColor = 0;

  for(nColor = 0; nColor < 16; nColor++)
    set_color(nColor, pPalette[nColor]);
}

void set_paletteMode1(const unsigned char a, const unsigned char b, const unsigned char c, const unsigned char d)
{
    set_color(0, a);
    set_color(1, b);
    set_color(2, c);
    set_color(3, d);
}

void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *pSprite)
{
  __asm
    LD L, 4(IX) 
    LD H, 5(IX) 
    LD C, 6(IX) 
    LD B, 7(IX)            
    LD E, 8(IX) 
    LD D, 9(IX) 

    _loop_alto:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho:
       LD A,(DE)			; Met dans A un octet de de la source
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_ancho		; D�cr�mente B qui contient la largeur. Si on � pas finit de copier 
							; l'�quivalent de la largeur on saute � _loop_ancho.
       POP HL				; r�cup�re l'adresse de la cible sauvegard� sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 � A --> Permet de passer � la ligne suivante
       LD H,A				; R�injecte A dans H, HL nous donne ainsi l'adresse de d�but de la ligne suivante
       SUB #0xC0			; On v�rifie que la ligne suivante en m�moire n'est pas � remonter ... 
       JP NC, _sig_linea	; Non, elle est � la suite en m�moire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par d�faut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute �a dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea:
       POP BC				; R�cup�re BC --> pour r�cup�rer la hauteur
       DJNZ _loop_alto		; Enl�ve 1 � la hauteur, si on � pas tout trait�, on reboucle au d�but _loop_alto
  __endasm;
}

void cmemcpy( void *dst, void *src, short len )
{
	__asm
		ld e, 4(ix)
		ld d, 5(ix)
		ld l, 6(ix)
		ld h, 7(ix)
		ld c, 8(ix)
		ld b, 9(ix)
		ldir
	__endasm;
}

void vsync()
{
  __asm
    ld b,#0xf5          ;; PPI port B input
    _wait_vsync:
    in a,(c)            ;; [4] read PPI port B input
                        ;; (bit 0 = "1" if vsync is active,
                        ;;  or bit 0 = "0" if vsync is in-active)
    rra                 ;; [1] put bit 0 into carry flag
    jp nc,_wait_vsync   ;; [3] if carry not set, loop, otherwise continue
  __endasm;
}

void put_frameXOR(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *pSprite)
{
  __asm
    LD L, 4(IX) 
    LD H, 5(IX) 
    LD C, 6(IX) 
    LD B, 7(IX)            
    LD E, 8(IX) 
    LD D, 9(IX) 

    _loop_altox:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_anchox:
       LD A,(DE)			; Met dans A un octet de de la source
	   XOR (HL)				; Inverse la destination
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_anchox		; D�cr�mente B qui contient la largeur. Si on � pas finit de copier 
							; l'�quivalent de la largeur on saute � _loop_ancho.
       POP HL				; r�cup�re l'adresse de la cible sauvegard� sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 � A --> Permet de passer � la ligne suivante
       LD H,A				; R�injecte A dans H, HL nous donne ainsi l'adresse de d�but de la ligne suivante
       SUB #0xC0			; On v�rifie que la ligne suivante en m�moire n'est pas � remonter ... 
       JP NC, _sig_lineax	; Non, elle est � la suite en m�moire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par d�faut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute �a dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_lineax:
       POP BC				; R�cup�re BC --> pour r�cup�rer la hauteur
       DJNZ _loop_altox		; Enl�ve 1 � la hauteur, si on � pas tout trait�, on reboucle au d�but _loop_alto
  __endasm;
}

void setCursor(unsigned char x, unsigned char y)
{
	__asm
		ld l, 5 (IX)
		ld h, 4 (IX)
		inc h
		inc l
		call #0xBB75
	__endasm;
}

void setTransparentMode(unsigned char transparent)
{
	__asm
		ld a, 4 (IX)
		call #0xBB9F
	__endasm;
}

void setPen(unsigned char transparent)
{
	__asm
		ld a, 4 (IX)
		call #0xBB90
	__endasm;
}

char commandLine[35];

char* readLine(unsigned char max_index) {
	int index = 0;
	char inputChar = ' ';
	while(1) {
		inputChar = getchar();
		if (inputChar == '\r') {
			commandLine[index] = '\0';
			break;
		}
		if (inputChar == 127) {
			if (index > 0) {
				printf("\b \b");
				commandLine[index] = '\0';
				index --;
			} else {
				putchar(0x07);
			}
		} else {
			if (index > max_index) continue;
			printf("%c", inputChar);
			commandLine[index] = inputChar;
			index ++;
		}
		
	}
  // playerInput[index]='\0';
	return commandLine;
}

//
void setBank(unsigned char bankPatternId)
{
	__asm
		ld a, 4 (IX)
    ld bc, #0x7F00
    OUT (c), a
	__endasm;
}

////////////////////////////////////////////////////////////////////////
//Load filename to address
////////////////////////////////////////////////////////////////////////
unsigned char nFileNameLen = 0;
void LoadFile(char *sFileName, char *pLoadAddress)
{
  if (sFileName == NULL) return;

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

void SaveFile(char *sFileName, char *pLoadAddress, unsigned int dataLength) {
  nFileNameLen = strlen(sFileName);

  __asm
  nop
    ;; B = length of the filename in characters
    ld hl, #_nFileNameLen
		ld b, (hl)

    ;; HL = address of the start of the filename
		LD L, 4 (IX) ;sFileName
		LD H, 5 (IX) ;sFileName

    ;; DE = address of a 2k buffer
    ;; 
    ;; in disc mode: this buffer is not used when CAS IN DIRECT
    ;; firmware function is used, so it is safe to put it anywhere
    ;; you want.
    ld de, #0x0

    ;; firmware function to open a file for writing
    call #0xbc8c ;; cas_out_open

    ;; firmware function to write the entire file
    ;; this will automatically generate a AMSDOS header
    ;; and write it before the the file data.

    ;; HL = load address
    LD L, 6 (IX) ;pLoadAddress
		LD H, 7 (IX) ;pLoadAddress
    
    ;; DE = length
    LD E, 8 (IX) ;dataLength
		LD D, 9 (IX) ;dataLength

    ;; BC = execution address
    ld bc, #0x0000
    ;; A = file type (2 = binary)
    ld a, #0x2

    ;; write file
    call #0xbc98 ;; cas_out_direct

    ;; firmware function to close a file opened for writing
    call #0xbc8f ;; cas_out_close
  __endasm;
}

unsigned char convertUnicode(unsigned char* c, char* ignoreNext) {
	*ignoreNext = 1;
	switch(c[0]) {
    case 0xC2:
      switch(c[1]) {
        case 0xA1: // ¡
          return 0x87;
        case 0xBF: // ¿
          return 0x88;
        default:
          return c[1];
      }
		case 0xC3:
			switch(c[1]) {
				case 0xA0: // à
					return 0x40;
				case 0xA2: // â
					return 0x7E;
				case 0xAE: // î
					return 0x7F;
				case 0xB9: // ù
					return 0x7C;
				case 0xA9: // é
					return 0x7B;
				case 0xA8: // è
					return 0x7D;
				case 0xAA: // ê n'existe pas sur amstrad mais je pourrais redéfinir le caractère ^
					return 0x5E;
				case 0xA7: // ç
					return 0x5C;
        case 0x87: // Ç
          return 0x81;
        case 0xA1: // á
          return 0x82;
        case 0xAD: // í
          return 0x83;
        case 0xB3: // ó
          return 0x84;
        case 0xBA: // ú
          return 0x85;
        case 0xB1: // ñ
          return 0x86;
				default:
					return c[1];
			}
		case 0xC5:
			switch(c[1]) {
				case 0x93: // œ
					return 0xB0; // ce caractère n'existe pas sur amstrad, je prend le alpha qui ressemble vaguement
				default:
					return c[1];
			}
    case 0xE2:
      // …
      if (c[1] == 0x80 && c[2] == 0xA6) {
        *ignoreNext = *ignoreNext + 1;
        return 0x80;
      }
      return c[2];
	}

	*ignoreNext = 0;
	return c[0];
}

void printu(char* text) {
  int i;
  char ignoreNext;
  for(i=0; i < strlen(text); i++) {
    if (strchr(",.;", text[i]) != NULL) {
      printf("%c ", text[i]);
    } else if(strchr("!?:", text[i]) != NULL) {
      #if LANGUAGE == 1 // French
        printf(" %c ", text[i]);
      #endif
      #if LANGUAGE == 2 // English
        printf("%c ", text[i]);
      #endif
      #if LANGUAGE == 3 // Spanish
        printf("%c ", text[i]);
      #endif
    } else {
		  printf("%c", convertUnicode(text + i, &ignoreNext));
    }

		if (ignoreNext) {
      i+=ignoreNext;
			ignoreNext = 0;
			// i++;
		}
	}
}

unsigned char charset[191*8];

void setChrTable()
{
	__asm
		ld de, #SYMBOLE_AFTER
		;;ld hl, #CHAR_TABLE_ADRESS
		ld hl, #_charset
		call #0xBBAB
	__endasm;
}

void setChrMatrix(unsigned char character, unsigned char* character_matrix)
{
	__asm
		ld a, 4 (IX)
		ld l, 5 (IX)
		ld h, 6 (IX)
		call #0xBBA8
	__endasm;
}

char currentImage[3501];

unsigned char reverse(unsigned char b) {
	unsigned char result;
	result  = (b & 136) >> 3; // 0b10001000
	result |= (b & 68) >> 1;  // 0b01000100
	result |= (b & 34) << 1;  // 0b00100010
	result |= (b & 17) << 3;  // 0b00010001

   return result;
}

void displayImage(bool mirrored, int patchId) {
	char x;
	char y;
  char offsetx = 22;
  struct Patch* patch = NULL;

  if (patchId >= 0) {
    patch = &patches[patchId];
  }

  setBank(BANK_MODE_SCREEN);

	for(y=0; y < 100; y ++) {
		for(x=0; x < 35; x++) {
			if (mirrored) {
        if (patch && x >= patch->x && x < patch->x + patch->w && y >= patch->y && y < patch->y + patch->h) {
				  *(precalc_vram[y] + (unsigned char*)(34-x+offsetx)) = reverse(patch->data[(x - patch->x)+((y - patch->y)*patch->w)]);
			  } else {
				  *(precalc_vram[y] + (unsigned char*)(34-x+offsetx)) = reverse(currentImage[x+(y*35)]);
        }
			} else {
        if (patch && x >= patch->x && x < patch->x + patch->w && y >= patch->y && y < patch->y + patch->h) {
				  *(precalc_vram[y] + (unsigned char*)(x+offsetx)) = patch->data[(x - patch->x)+((y - patch->y)*patch->w)];
			  } else {
				  *(precalc_vram[y] + (unsigned char*)(x+offsetx)) = currentImage[x+(y*35)];
        }
			}
		}
	}
  setBank(BANK_MODE_DATABASE);
}

void displayIcon(char x, char y, char w, char h) {
  char i;
	char j;
  setBank(BANK_MODE_SCREEN);
  // icon 6*24
  // portrait 12*64
	for(j=0; j < h; j ++) {
		for(i=0; i < w; i++) {
      *(precalc_vram[y+j] + (unsigned char*)(x+i)) = currentImage[i+(j*w)];
    }
  }

  setBank(BANK_MODE_DATABASE);
}

// void displayPortrait(char x, char y) {
//   char i;
// 	char j;
//   setBank(BANK_MODE_SCREEN);

// 	for(j=0; j < 64; j ++) {
// 		for(i=0; i < 12; i++) {
//       *(precalc_vram[y+j] + (unsigned char*)(x+i)) = currentImage[i+(j*12)];
//     }
//   }

//   setBank(BANK_MODE_DATABASE);
// }

// void displayImage(bool mirrored) {
// 	char x;
// 	char y;

//   setBank(BANK_MODE_SCREEN);

// 	for(y=0; y < 100; y ++) {
// 		for(x=0; x < 35; x++) {
// 			if (mirrored) {
// 				*(precalc_vram[y] + (unsigned char*)(34-x)) = reverse(currentImage[x+(y*35)]);
// 			} else {
// 				*(precalc_vram[y] + (unsigned char*)x) = currentImage[x+(y*35)];
// 			}
			
// 		}
// 	}
//   setBank(BANK_MODE_DATABASE);
// }

void clearImage() {
	char x;
	char y;
  char offsetx = 22;
  setBank(BANK_MODE_SCREEN);
	for(y=0; y < 100; y ++) {
		for(x=0; x < 35; x++) {
				*(precalc_vram[y] + (unsigned char*)(x+offsetx)) = 0;
		}
	}
  setBank(BANK_MODE_DATABASE);
}
