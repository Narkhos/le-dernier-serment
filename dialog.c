#include "parser/game.h"
#include "menu.h"
#include "dialog.h"
#include "lib.h"
#include "alchemy.h"
#include "sound.h"
#include "language.h"

void finEpreuve() {
	clearImage();
	set_paletteMode1(0,13,20,2);
    LoadFile("INDOOR.SCR", currentImage);
    displayImage(false, getPatchId(CHURCH_INDOOR));
	printDataText(22, 0);
	printDataText(23, 1);
    // printMessage("Va,trouve le Sceptre d'Orphée", NULL, 0);
    // printMessage("Il est la clé de la malédiction qui     s'est abattue sur ton peuple", NULL, 1);
	
	menuOk();
	changeLocation(CHURCH_INDOOR);
}

bool hermitEncountered = false;
bool keyKnown = false;

void dialogHermit() {
	int choice;
	int flaskRecipeId;

	if(getState(HERMIT, MASK_DEAD)) {
		setState(HERMIT, MASK_DEAD, false);
		displayImage(true, getPatchId(currentLocationId));
		printDataText(24, 0);
		// printMessage("Mmmh?Euh… Oui… C'est pour quoi?", NULL, 0);
	} else {
		if (hermitEncountered) {
			printDataText(25, 0);
			// printMessage("Que puis-je faire pour vous?", NULL, 0);
		} else {
			hermitEncountered = true;
			printDataText(26, 0);
			printDataText(27, 2);
			// printMessage("Ça fait bien longtemps que je n'ai pas  eu de visite.", NULL, 0);
			// printMessage("Mon nom est Hermès,je suis moine,et   alchimiste à mes heures", NULL, 2);
		}
	}

	do {
		clearMenu();
		if (contains(INVENTORY, AMULET)) {
			addMenuOption(_T0164, 1);
		} else {
			addMenuOption(_T0165, 5);
		}

		addMenuOption(_T0166, 2);

		if (keyKnown) {
			addMenuOption(_T0167, 3);
		}

		addMenuOption(_T0168, 4);

		addMenuOption(_T0169, 0);

		choice = menu();

		switch(choice) {
			case 5:
				printDataText(28, 0);
				// printMessage("Voici une amulette permettant de traver-ser le miroir", NULL, 0);
				moveObjectTo(INVENTORY, AMULET);
				menuOk();
				printDataText(29, 0);
				// printMessage("Vous pouvez la garder", NULL, 0);
				break;
			case 1:
				printDataText(30, 0);
				printDataText(31, 1);
				// printMessage("C'est pour traverser le miroir", NULL, 0);
				// printMessage("L'amulette l'empêche de vous voir", NULL, 1);
				break;
			case 2:
				printDataText(32, 0);
				// printMessage("Ne touchez pas à cet artefact,il est   dangereux", NULL, 0);
				menuOk();
				printDataText(33, 0);
				// printMessage("De toute façon,je l'ai mis sous clef", NULL, 0);
				keyKnown = true;
				break;
			case 3:
				printDataText(34, 0);
				// printMessage("Hors de question,le sceptre est trop   dangereux!", NULL, 0);
				break;
			case 4:
				// Boire le thé si possible
				flaskRecipeId = getFlaskRecipeId();
				if (flaskRecipeId == REC_STIMULATING || flaskRecipeId == REC_CALMING) {
					printDataText(35, 0);
					// printMessage("Du thé à la menthe,mon breuvage préféré Merci beaucoup!", NULL, 0);

					flaskBuffer[0] = 'V';
					flaskBuffer[1] = '\0';
					if (flaskRecipeId == REC_CALMING) {
						menuOk();
						printDataText(36, 0);
						// printMessage("Je me sens un peu fatigué.Je crois que je vais faire une sieste.", NULL, 0);
						setState(HERMIT, MASK_DEAD, true);
						displayImage(true, getPatchId(currentLocationId));
						return;
					} else {
						menuOk();
						printDataText(37, 0);
						// printMessage("Ah!Merci,je me sens revigoré!", NULL, 0);
					}
				} else {
						printDataText(38, 0);
						// printMessage("Je veux bien du thé à la menthe", NULL, 0);
						menuOk();
					if (contains(HERMIT, MINT)) {
						printDataText(39, 0);
						// printMessage("Voici quelques feuilles de menthe pour  le préparer", NULL, 0);
						moveObjectTo(INVENTORY, MINT);
					}
				}
				break;
			default: // case 0, prendre congé
				printMessage(_T0182, NULL, 0);
				break;
		}
	} while(choice);
}

void dialogueDieu() {
	printDataText(40, 0);
    // printMessage("Ma création a été corrompue par Nahash", NULL, 0);
	printDataText(41, 1);
    // printMessage("J'ai créé le monde avec des règles", NULL, 1);
	// printDataText(42, 2);
    printMessage(_T0185, NULL, 2);
	menuOk();
	printDataText(42, 0);
    // printMessage("Il n'y a pas de place pour le libre", NULL, 0);
	// printDataText(43, 1);
    printMessage(_T0187, NULL, 1);
	menuOk();
	printDataText(43, 0);
    // printMessage("Détruis la part de Nahash en toi", NULL, 0);
	printDataText(44, 1);
    // printMessage("pour rendre sa beauté originelle", NULL, 1);
	// printDataText(45, 2);
    printMessage(_T0190, NULL, 2);
	menuOk();
}

void explosion() {
	int i;
	sound(3, 4090, 100, 9, 1, 2, 1);
	for(i=0;i<512;i++) {
		set_paletteMode1(0, (13 + i/10)%26, (3 + (i/10))%26, (16 + (i/10))%26);
	}
}

void endingMessage(int trophyId) {
	// affichage de l'image correspondant à la fin atteinte
	// et afficahge du message en fonction de la fin atteinte et des fins déjà débloquées
	explosion();
	set_paletteMode1(0, 0, 0, 0);
	clearImage();
	clearChoices(9);
	switch(trophyId) {
		case END_FREEDOM:
			set_paletteMode1(0, 13, 3, 16);
			drawTrap(18, 5);
			// printMessage("Nahash:tu m'as aidé à détruire ton    monde.", NULL, 0);
			printDataText(45, 0);
			menuOk();
			printMessage(_T0192, NULL, 0);
			menuOk();
			// printMessage("Pour te remercier,voici ton royaume! Tu es libre d'y rester pour l'éternité…", NULL, 0);
			printDataText(46, 0);
			break;
		case END_ORDER:
			printMessage(_T0194, NULL, 0);
			printMessage(_T0195, NULL, 3);
			set_paletteMode1(0, 13, 3, 16);
			LoadFile("LOOSE.SCR",currentImage);
    		displayImage(false, -1);
			break;
		case END_BALANCE:
		case END_MESSIAH:
			printMessage(_T0196, NULL, 0);
			set_paletteMode1(0, 13, 3, 16);
			LoadFile(
				((trophyId == END_BALANCE) ? "WIN.SCR" : "PERFECT.SCR"),
				currentImage
			);
    		displayImage(false, -1);
			break;
		default: // END_BOMB
			set_paletteMode1(0, 13, 3, 16);
			printMessage(_T0197, NULL, 0);
			break;
	}
}

void ending(int trophyId) {
	int choice;

	trophies[trophyId].unlocked = true;
	endingMessage(trophyId);

	do {
		clearMenu();
		addMenuOption(_T0198, 1);
		addMenuOption(_T0199, 0);

		choice = menu();

		if (choice == 1) {
			trophyMenu();
		}
	} while(choice);

	backToCheckpoint(trophyId);
}

void trophyMenu() {
	// afficher les trophées obtenus et restant à obtenir
	int i;

	for(i = 0; i < ENDING_COUNT; i++) {
		printMessage(trophies[i].title, trophies[i].unlocked ? "+" : " ", i);
	}
	menuOk();
}

void backToCheckpoint(int trophyId) {
	// TODO: réinitialiser le jeu en fonction de la fin atteinte
	if (trophyId) { // toutes les fins à part END_BOMB
		changeLocation(M_CHURCH_INDOOR);
	} else { // END_BOMB
		changeLocation(LABORATORY);
	}
}
