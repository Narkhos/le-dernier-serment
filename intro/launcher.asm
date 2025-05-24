;----------------
;--- CODE ASM ---
;----------------
;MEMOIRE
;&4000-&7FFF figurine.scr lg=&4000
;&8000-&895F DERNIER.VOX lg=&960
voix_donnees EQU &8000
voix_longueur EQU &960

ORG &8960
	LD A,10
	CALL DELAY

	CALL hommage

	LD A,250
	CALL DELAY

	CALL AFF_COULEURS

	LD A,10
	CALL DELAY

	CALL affscreen

	LD A,20
	CALL DELAY

	CALL voix_fr

	LD A,20
	CALL DELAY

	RET


; -----------------------------------------------------------------------------
; Sprites bouche ouverte + bouche fermée
; -----------------------------------------------------------------------------
ouvert
	LD HL,sprite_bouche_ouverte
	CALL AFFICHAGE_SPRITES
	RET

ferme
	LD HL,sprite_bouche_ferme
	CALL AFFICHAGE_SPRITES
	RET

AFFICHAGE_SPRITES
	LD A,9 ;hauteur
	LD DE,&FA1A ;adresse de destination a l'écran
spr_loop4
	PUSH AF
	PUSH DE

	;on va utiliser 6 LDI pour gérer la largeur du sprite
	LDI
	LDI
	LDI
	LDI
	LDI
	LDI

	POP DE
	CALL calcul_ligne_suivante_DE
	POP AF
	DEC A
	JR NZ, spr_loop4
	RET

calcul_ligne_suivante_DE
	LD A,D	;on recopie D dans A
	ADD A,&08	;on ajoute #08 a A
	LD D,A	;on recopie A dans D
			;DE contient la nouvelle adresse
	RET NC	;si pas de debordement alors on arrete là le calcul
			;et on revient juste apres le call
	;si debordement on continue donc ici cela signifie qu'on doit ajouter #C050 a notre adresse
	EX HL,DE	;on a besoin que notre adresse soit dans HL pour pouvoir lui additionner
			;quelque chose
	;l'adresse est maintenant dans HL
	LD BC,&C050	;on met &C050 dans BC
	ADD HL,BC	;on additionne HL et BC
	;HL contient maintenant l'adresse de la ligne inferieure mais on la veut dans DE
	EX HL,DE	;on refait l'echange et DE contient donc l'adresse
	RET

sprite_bouche_ferme
DB #0C, #80, #FC, #FC, #FC, #84
DB #0C, #48, #FC, #FC, #E8, #48
DB #0C, #48, #FC, #D4, #E8, #84
DB #0C, #48, #D4, #FC, #C0, #0C
DB #0C, #0C, #D4, #FC, #84, #84
DB #0C, #48, #E8, #C0, #C0, #0C
DB #0C, #80, #FC, #FC, #E8, #0C
DB #C0, #D4, #54, #FC, #FC, #C0
DB #48, #A8, #FC, #FC, #FC, #E8

sprite_bouche_ouverte
DB #0C, #C0, #C0, #C0, #C0, #84
DB #0C, #48, #C0, #C0, #C0, #48
DB #0C, #C0, #C0, #C0, #C0, #84
DB #0C, #80, #FC, #FC, #FC, #84
DB #0C, #48, #FC, #FC, #E8, #84
DB #0C, #48, #FC, #D4, #E8, #84
DB #0C, #C0, #D4, #FC, #C0, #0C
DB #C0, #D4, #D4, #FC, #D4, #C0
DB #48, #A8, #E8, #C0, #D4, #E8

; -----------------------------------------------------------------------------
; Message d'hommage
; -----------------------------------------------------------------------------
hommage
	CALL symbol_perso
	CALL WaitSyncho
	;MODE 2
	LD A,2
	CALL &BC0E
	;BORDER 0,0
	LD BC,0
	CALL &BC38
	;INK 0,0,0
	XOR A
	LD BC,&0000
	CALL &BC32
	;INK 1,3,3
	LD A,1
	LD BC,&0303
	CALL &BC32
	;PEN 1
	;LD A,1
	;CALL &BB90
	;LOCATE 30,11
	;LD H,30 ;colonne
	;LD L,11 ;ligne
	;CALL &BB75

	LD HL,hommage_texte
boucle_affichage_texte
	LD A,(HL)
	CP 0    ;si 0
	RET Z   ;on sort
	CALL &BB5A
	INC HL
	JR boucle_affichage_texte

hommage_texte
	DB &0F,1        ;PEN 1 avec token ASCII
	DB &1F,30,11    ;LOCATE 30,11
	DEFM "A mon fr"
	DB 254
	DEFM "re St"
	DB 255
	DEFM "phane"
	DB &1F,36,12    ;LOCATE 36,12
	DEFM "1984-2023"
	DB 0 ;fin du texte


; -----------------------------------------------------------------------------
; Redéfinition de caractères
; -----------------------------------------------------------------------------
symbol_perso
	LD A,254
	LD HL,char254
	CALL &BBA8
	LD A,255
	LD HL,char255
	CALL &BBA8
	RET
char254
	DB &X10000,&X1000,&X111100,&X1100110,&X1111110,&X1100000,&X111100,&X0 ;è
char255
	DB &X1000,&X10000,&X111100,&X1100110,&X1111110,&X1100000,&X111100,&X0 ;é


; -----------------------------------------------------------------------------
; LE DERNIER SERMENT - DERNIER.VOX
; -----------------------------------------------------------------------------
voix_fr
	;adresse du son
;	LD HL,voix_donnees
	;longueur
;	LD DE,voix_longueur
;	CALL DIGITALISATION_VOCALE
;	RET

	;le son a lire fait &960 (2400 octets) -> si 400 octets c'est 6 fois (200 ouvrir + 200 fermer)
	LD HL,voix_donnees
	CALL repetition_ouvrir_ferme
	CALL repetition_ouvrir_ferme
	CALL repetition_ouvrir_ferme
	CALL repetition_ouvrir_ferme
	CALL repetition_ouvrir_ferme
	CALL repetition_ouvrir_ferme
	RET

repetition_ouvrir_ferme
	PUSH HL
	LD DE,200
	PUSH DE
	CALL DIGITALISATION_VOCALE
	CALL ouvert
	
	POP BC	;c'est le DE qu'on récupéré dans BC
	POP HL
	ADD HL,BC ;block suivant la longueur déjà lu pour la digit vocale
	PUSH BC
	POP DE

	PUSH HL
	LD DE,200
	PUSH DE
	CALL DIGITALISATION_VOCALE
	CALL ferme

	POP BC	;c'est le DE qu'on récupéré dans BC
	POP HL
	ADD HL,BC ;block suivant la longueur déjà lu pour la digit vocale
	PUSH BC
	POP DE
	RET



; -----------------------------------------------------------------------------
; MODE + BORDER + PALETTE
; -----------------------------------------------------------------------------
AFF_COULEURS
	;MODE 0
	XOR A
	CALL &BC0E
	;Border 26,26
	LD BC,&1A1A
	CALL &BC38
	LD HL,DATACOULEURS
	XOR A
loopcouleurs
	PUSH AF
	PUSH HL
	LD B,(HL)
	LD C,B
	CALL &BC32
	POP HL
	INC HL
	POP AF
	INC A
	CP 16
	JR NZ,loopcouleurs
	RET
DATACOULEURS
	DB 26,0,1,13,3,6,2,16,9,18,12,24,7,10,4,5


;------------------------------------------------------------------------------
;Affichage style Moon Cresta
;------------------------------------------------------------------------------
affscreen
	LD HL,&4000     ;adresse de debut de notre image
	LD DE,&0FA1     ;incrementation
	LD BC,&4000     ;taille de l'image
AffEffetMoonCresta
	LD A,(HL)       ;lire en &4000
	SET 6,H         ;bit 6 a 1 = &4000 en &C000
	SET 7,H         ;bit 7 a 1
	LD (HL),A       ;ecrire a l'ecran
	ADD HL,DE       ;adresse suivante
	LD A,H          ;charger le &C0
	AND %01111111   ;&C0 en &40 - part 1
	OR %1000000     ;&C0 en &40 - part 2
	LD H,A          ;&C000 de nouveau en &4000
	LD A,C
	RRA
	DEC BC          ;taille de l'image -1

	;ralentir (codé comme un cochon)
	PUSH HL
	POP HL
	PUSH HL
	POP HL
	PUSH HL
	POP HL
	PUSH HL
	POP HL
	PUSH HL
	POP HL

	LD A,B
	OR C
	JR NZ,AffEffetMoonCresta
	RET


; -----------------------------------------------------------------------------
; Syncho - Remplace &BD19
; -----------------------------------------------------------------------------
WaitSyncho
	LD B,&F5
WaitSyncho1
	IN A,(C)
	RRA
	JR C,WaitSyncho1
	LD B,&F5
WaitSyncho2
	IN A,(C)
	RRA
	JR NC,WaitSyncho2
	RET


;------------------------------------------------------------------------------
; DELAY SUBROUTINE (0,05s a 12,75s)
; A = Timeout / 50ms
;------------------------------------------------------------------------------
DELAY
	LD B,15       ; 15 x 1/300eme ms (HALT) = 50ms
DELAY_2
	HALT          ; attendre 1/300eme s
	DJNZ DELAY_2  ; boucler pour 50ms
	DEC A
	JR NZ,DELAY   ; boucler pour A x 50ms
	RET


; -----------------------------------------------------------------------------
; DIGITALISATION VOCALE
; -----------------------------------------------------------------------------
DIGITALISATION_VOCALE
	;volume
	LD A,15
	LD(voxvol+1),A
	;vitesse
	LD A,9
	LD(voxvit+1),A
	CALL loopvox
	RET

loopvox
	DI
	LD C,&08
	CALL Lecture
	INC HL
	DEC DE
	LD A,D
	OR E
	JR NZ,loopvox
	EI
	RET

Lecture
	PUSH DE
	LD E,(HL)
vox3
	SLA E
	LD A,0
	JR NC,vox1
voxvol
	LD A,15	;volume
vox1
	LD B,&F4
	LD D,9
	OUT (C),D
	LD D,A
	LD B,&F6
	IN A,(C)
	OR &C0
	OUT (C),A
	AND &3F
	OUT (C),A
	LD B,&F4
	OUT (C),D
	LD B,&F6
	LD D,A
	OR &80
	OUT (C),A
	OUT (C),D
voxvit
	LD A,5	;vitesse
vox2
	DEC A
	JR NZ,vox2
	DEC C
	JR NZ,vox3
	POP DE
	RET