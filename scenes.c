#include <stdio.h>
#include <string.h>
#include "scenes.h"
#include "menu.h"
#include "parser/game.h"
#include "parser/parser.h"
#include "parser/behavior.h"
#include "database.h"
#include "lib.h"
#include "define.h"
#include "alchemy.h"
#include "language.h"

void introMenu() {
	int choice;

	setBank(BANK_MODE_SCREEN);
    setCursor(32, 1);
    printf("      ");
    setCursor(32, 1);
    printf("%u", turn);
	setBank(BANK_MODE_DATABASE);

	clearMenu();
	addMenuOption(_T0207, 0);
	addMenuOption(_T0208, 1);
	addMenuOption(_T0209, 2);

	choice = menu();

	executeCommand(getMenuOptionById(choice)->text);
}

void parser() {
	if(currentLocationId >= NW_ROOM && currentLocationId <= SE_ROOM) {
        drawSimulation(13,1, true);
    }

    setBank(BANK_MODE_SCREEN);
    setCursor(32, 1);
    printf("      ");
    setCursor(32, 1);
    printf("%u", turn);
    // fgets (commandLine, 255, stdin);
    setCursor(0, 24);
    printf(">                                       ");
    setCursor(1,24);
    readLine(33); // renseigne la variable globale commandLine
    setBank(BANK_MODE_DATABASE);

    commandLine[strcspn(commandLine, "\r\n")] = 0;

	clearChoices(3);
	executeCommand(commandLine);
}

void introNahash() {
	// printMessage("Des gravats se détachent des murs et    quelques pierres tombent du plafond", NULL, 0);
	printDataText(47, 0);
	menuOk();
	set_paletteMode1(0,13,20,2);
	// printMessage("Je suis le Dieu Nahash et j'ai entendu  ta prière", NULL, 0);
	printDataText(48, 0);
	menuOk();
	currentSceneId = SCN_PARSER;
	clearImage();

	drawSimulation(13,1, false);
	// printMessage("Ce monde est une épreuve", NULL, 0);
	printDataText(49, 0);
	menuOk();

	// printMessage("Dompte ses règles et trouve la sortie", NULL, 0);
	printDataText(50, 0);
	menuOk();

	changeLocation(S_ROOM);
}

char p;
void saveBufferPush(char* data, bool invert) {
	if (invert) {
		data[0] = strBuffer[p];
	} else {
		strBuffer[p]=data[0];
	}
	p ++;
}

void saveBuffer(bool invert) {
	int i;
	bool fileExistFlag = 1;
	p = 0;

	// Ce flag permet de savoir si des données ont été récupérée ou non
	// S'il reste à 0, c'est que le chargement a échoué
	// car lorsqu'on sauvegarde, il est enregistré à 1
	saveBufferPush(&fileExistFlag, invert);

	// Etat des objets
	for(i = 0; i < GOD_ROOM; i++) {
		saveBufferPush(&(objects[i].containerId), invert);
		saveBufferPush(&(objects[i].state), invert);
	}

	// Variables d'état général du jeu
	saveBufferPush(&heroStatus, invert);
	saveBufferPush(&heroStatusTimer, invert);
	saveBufferPush(&(((char*)&turn)[0]), invert);
	saveBufferPush(&(((char*)&turn)[1]), invert);
	saveBufferPush(&currentLocationId, invert);
	saveBufferPush(&currentSceneId, invert);

	// Fin débloquées
	for(i = 0; i < ENDING_COUNT; i++) {
		saveBufferPush(&(trophies[i].unlocked), invert);
	}

	// Alchimie
	saveBufferPush(temperature, invert);

	for(i = 0; i < 7; i++) {
		saveBufferPush(&(alchemyBuffer[i]), invert);
	}

	saveBufferPush(actionNumber, invert);
	for(i = 0; i < 6; i++) {
		saveBufferPush(&(substrateColors[i]), invert);
	}

	for(i = 0; i < 7; i++) {
		saveBufferPush(&(flaskBuffer[i]), invert);
	}
}
void saveGameState() {
	saveBuffer(false);

	SaveFile("SAVE01.BIN", strBuffer, p);
	printMessage(_T0204, NULL, 0);
	menuOk();
}

void loadGameState() {
	strBuffer[0] = 0;
	LoadFile("SAVE01.BIN", strBuffer);
	if (strBuffer[0] == 0) {
		printMessage(_T0205, NULL, 0);
	} else {
		saveBuffer(true);
		printMessage(_T0206, NULL, 0);
	}
	menuOk();

	if (strBuffer[0]) {
		clearImage();
		changeLocation(currentLocationId);
		displayStatus();
	}
}

void (*scenes[3])() = {
	parser,
	introMenu,
	introNahash
};

/**
	Exécute la commande passée en paramètre.
	La fonction envoie la commande aux méthodes execute de tous les objets,
	jusqu'à ce qu'un des objet la traite.
	Si aucun objet n'est concerné, elle affiche un message d'erreur générique.
*/
bool executeCommand(char* commandLine) {
	bool result = false;
	unsigned char objectId;
	char cl[35];
    struct Command* command;
	strcpy(cl, commandLine);
    toupperString(cl);
    command = parseCommand(cl);

	if (strcmp(command->object, "") == 0) {
		switch(command->verbId) {
			case Inventaire:
				result = inventoryExecute(command);
				break;
			// case Aide:
			// 	result = aideExecute();
			// 	break;
			case Attendre:
				result = true;
				break;
			case Sauver:
				saveGameState();
				result = true;
				break;
			case Charger:
				loadGameState();
				result = true;
				break;
			default: // Regarder, Nord, Sud...
				result = execute(command, currentLocationId);
		}
	} else {
		// if (objectMatch(HERO, command->object)) {
		// 	result = execute(command, HERO);
		// } else
		// if (objectMatch(INVENTORY, command->object)) {
		// 	result = execute(command, INVENTORY);
		// } else
		{
			objectId = findObjectIn(CONTEXT, command->object);
			if (objectId != NO_OBJECT) {
				result = execute(command, objectId);
				// Si la commande comporte un complement et qu'elle n'a pas aboutit,
				// on essai en inversant l'objet et le complement
				if (!result && strcmp(command->complement, "") != 0) {
					// TODO : trouver un moyen de faire ça plus proprement
					// peut-être simplement en mettant ce code dans une méthode
					char tmp_object[16];
					strcpy(tmp_object,command->object);
					strcpy(command->object,command->complement);
					strcpy(command->complement,tmp_object);
					objectId = findObjectIn(CONTEXT, command->object);
					result = execute(command, objectId);
				}
			}
			// else {
			// 		// Exécution de la commande directement sur le lieu si aucun objet n'a été trouvé
			// 		result = execute(command, currentLocationId);
			// }
		}
	}

	if (!result) printMessage("%s\r\n", responses[command->verbId], 0);

	if (result) {
		// On incrémente le temps à chaque tour
		// Sauf si le héros est nerveux, dans ce cas c'est 1 tour sur 2
		// On ne compte pas de tour pour le verbe Regarder
		if (command->verbId != Regarder) {
			if (heroStatus != NERVOUS || heroStatusTimer%2 == 0) {
				turn ++;
				updateTemperature();
			}

			// Si le héros est fatigué, il passe un tour supplémentaire
			if (heroStatus == SLEEPY) {
				turn ++;
				updateTemperature();
			}
		}

		updateHeroStatus();
		if (
			currentLocationId == LABORATORY
			|| currentLocationId == CRYPT
			|| currentLocationId == M_CRYPT
		) {
			setLocationPalette(currentLocationId);
		}

		if (heroStatus == SICK) {
			printMessage("¡BURP!", NULL, 0);
		}
	}

	return result;
}
