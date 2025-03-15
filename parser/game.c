#include "game.h"
#include "../define.h"
#include "../lib.h"
#include "../alchemy.h"
#include "../scenes.h"
#include "../sound.h"
#include "../language.h"

unsigned int turn = 1;

unsigned char heroStatus=LIVELY;
unsigned char heroStatusTimer=0;

char tmpDescription[MAX_DESCRIPTION_LENGTH];

void displayStatus() {
    setBank(BANK_MODE_SCREEN);
    // setCursor(29,4);
    // printf("Etat:");
    setCursor(31,11);
    printf("         ");
    setCursor(31,11);
    switch(heroStatus) {
        // case DEAD:
        //     printf("MORT");
        //     break;
        case LIVELY:
            // printf("OK");
            LoadFile("PNORMAL.SCR", currentImage);
            break;
        case SICK:
            printf(_T0057);
            LoadFile("PSICK.SCR", currentImage);
            break;
        case SHINY:
            printf(_T0058);
            LoadFile("PSHINY.SCR", currentImage);
            break;
        case INVISIBLE:
            printf(_T0059);
            LoadFile("PINVISIB.SCR", currentImage);
            break;
        case NERVOUS:
            printf(_T0060);
            LoadFile("PNERVOUS.SCR", currentImage);
            break;
        case SLEEPY:
            printf(_T0061);
            LoadFile("PSLEEPY.SCR", currentImage);
            break;

    }

    displayIcon(64, 16, 12, 64);
    LoadFile(imageFile[getLocationImageIndex(currentLocationId)], currentImage);
    setBank(BANK_MODE_DATABASE);
}

void setHeroStatus(const unsigned char newStatus) {
    if(newStatus == NO_EFFECT) return;

    heroStatus=newStatus;
    setLocationPalette(currentLocationId);

    if(newStatus == LIVELY) {
        heroStatusTimer = 0;
    } else {
        heroStatusTimer = 5;
    }

    displayStatus();
}

void updateHeroStatus() {
    if (heroStatusTimer > 0) {
        heroStatusTimer--;
        if(heroStatusTimer == 0) setHeroStatus(LIVELY);
    }
}

// - Même le néant détale (fin du monde) : provoquer la fin du monde avec la bombe sainte
// - Epris de liberté (mauvaise fin) rester emprisonné dans le monde de Nahash
// - Graine de sans âme (fin intermédiaire) : tuer nahash (ce qui tue par la même occasion notre libre arbitre)
// - Mais non ! (bonne fin) : équilibrer le monde (capturer nahash, ou le persuader de partager son pouvoir)
// - Messie ! (fin parfaite) : atteindre la bonne fin au tour 1 et donc sauver tout le monde
struct Trophy trophies[ENDING_COUNT] = {{
	.title = _T0062,
	.unlocked = false
},
{
	.title = _T0063,
	.unlocked = false
},
{
	.title = _T0064,
	.unlocked = false
},
{
	.title = _T0065,
	.unlocked = false
},
{
	.title = _T0066,
	.unlocked = false
}};

unsigned char currentLocationId;
unsigned char currentSceneId;

char strBuffer[256];
void printMessage(char* message, char* param, int line) {
    char str[32];
    strcpy(str, param);
    setBank(BANK_MODE_SCREEN);
    setCursor(0, 14 + line);
    printf("                                        ");
    printf("                                        ");
    setCursor(0, 14 + line);
    sprintf(strBuffer, message, str);
    printu(strBuffer);
    setBank(BANK_MODE_DATABASE);
}

void printDataText(int textId, int line) {
    strcpy(strBuffer, dataText[textId].str);

    setBank(BANK_MODE_SCREEN);
    setCursor(0, 14 + line);
    printf("                                        ");
    printf("                                        ");
    setCursor(0, 14 + line);
    printu(strBuffer);
    setBank(BANK_MODE_DATABASE);
}

void printMessage2(char* message, char* param1, char* param2) {
    char str1[32];
    char str2[32];
    strcpy(str1, param1);
    strcpy(str2, param2);
    setBank(BANK_MODE_SCREEN);
    setCursor(0, 14);
    printf(message, str1, str2);
    setBank(BANK_MODE_DATABASE);
}

void changeLocation(unsigned char locationId) {
    // unsigned char palette[] = {0,25,3,9,11,16,22,26,0,0,0,0,0,0,0,0};
    // objects[currentLocationId].containerId = NO_OBJECT;
    moveObjectTo(NO_OBJECT, currentLocationId);
    // objects[locationId].containerId = CONTEXT;
    moveObjectTo(CONTEXT, locationId);

    currentLocationId = locationId;

    strcpy(tmpDescription, objects[currentLocationId].description);

    if(currentLocationId >= NW_ROOM && currentLocationId <= SE_ROOM) {
        printMessage(tmpDescription, NULL, 0);
    } else {
        printMessage(tmpDescription, NULL, 0);
        // printMessage("", NULL);
        clearImage();
        // set_palette(palette);
        setLocationPalette(currentLocationId);

        if (
            (currentLocationId == MIRROR_ROOM && isSecretRoomOpen())
            || (currentLocationId == M_MIRROR_ROOM && isMSecretRoomOpen())
        ) {
            LoadFile("OMIRROR.SCR", currentImage);
        } else {
            LoadFile(imageFile[getLocationImageIndex(currentLocationId)], currentImage);
        }
        displayImage(isInversedLocation(currentLocationId), getPatchId(currentLocationId));
    }
}

bool isInInventory(unsigned char objectId) {
    return objects[objectId].containerId == INVENTORY;
}

int listContent(unsigned char objectId) {
    int i;
    int count = 0;
    int n=0;

    for(i = 0; i < MAX_OBJECT_COUNT; i++) {
        if (contains(objectId, i) && !getState(i,MASK_HIDDEN)) {
            printMessage("- %s", objects[i].names[0], n%6 + 2);
            n ++;
            count ++;
            if (n%6 == 0) {
                menuOk();
            }
        }
    }
    if (count == 0) {
        printMessage(responses[Fouiller], NULL, 1);
    }
    if (n > 0) menuOk();

    return n;
}

bool take(unsigned char objectId) {
    if(objectId == NO_OBJECT || isInInventory(objectId)) {
        printMessage(_T0067, objects[objectId].displayName, 0);
        return false;
    }

    if (getState(objectId, MASK_PICKABLE)) {
        // objects[objectId].containerId = INVENTORY;
        moveObjectTo(INVENTORY, objectId);
        printMessage(_T0068, objects[objectId].displayName, 0);

        if(currentLocationId < NW_ROOM || currentLocationId > SE_ROOM) {
            displayImage(isInversedLocation(currentLocationId), getPatchId(currentLocationId));
        }

        return true;
    }

    // Si on essai de prendre le lieu dans lequel ou se trouve ou qu'on ne précise pas d'objet
    // on affiche un message générique.
    if (objectId == currentLocationId) {
        printMessage(_T0069, NULL, 0);
    } else {
        printMessage(_T0070, objects[objectId].displayName, 0);
    }
    return false;
}

bool standardExecute(struct Command* command, unsigned char objectId) {
    unsigned char complementId;
    
	switch(command->verbId) {
		case Regarder:
            if (getState(objectId, MASK_HIDDEN)) {
                return false;
            }
            strcpy(tmpDescription, objects[objectId].description);
            printMessage(tmpDescription, NULL, 0);
			return true;
        case Prendre:
            take(objectId);
            return true;
        case Ouvrir:
            if (getState(objectId, MASK_OPENABLE)) {
                if(!getState(objectId, MASK_LOCKED)) {
                    if(getState(objectId, MASK_CLOSED)) {
                        setState(objectId, MASK_CLOSED, false);
                        printMessage(_T0071, objects[objectId].displayName, 0);
                    } else {
                        printMessage(_T0072, objects[objectId].displayName, 0);
                    }
                } else {
                    printMessage(_T0073,  objects[objectId].displayName, 0);
                }
                return true;
            }
            break;
        case Fermer:
            if (getState(objectId, MASK_OPENABLE)) {
                if(!getState(objectId, MASK_CLOSED)) {
                    setState(objectId, MASK_CLOSED, true);
                    printMessage(_T0074, objects[objectId].displayName, 0);
                } else {
                    printMessage(_T0075, objects[objectId].displayName, 0);
                }
                return true;
            }
            break;
        case Poser:
            if(isInInventory(objectId) && getState(objectId, MASK_PICKABLE)) {
                complementId = findObjectIn(CONTEXT, command->complement);
                if (complementId == NO_OBJECT) {
                    // objects[objectId].containerId = currentLocationId;
                    // moveObjectTo(currentLocationId, objectId);
                    return false;
                } else {
                    if (!getState(complementId, MASK_CLOSED)) {
                        if (getState(complementId, MASK_CONTAINER)) {
                            // objects[objectId].containerId = complementId;
                            moveObjectTo(complementId, objectId);
                            printMessage2(
                                _T0076,
                                objects[objectId].displayName,
                                objects[complementId].displayName
                            );
                        } else {
                            printMessage(_T0077, NULL, 0);
                        }
                    } else {
                        printMessage(_T0078, objects[complementId].displayName, 0);
                    }
                }
            } else {
                return false;
            }

            return true;
        case Fouiller:
            if(!getState(objectId, MASK_CLOSED)) {
                listContent(objectId);
            } else {
                printMessage(_T0078, objects[objectId].displayName, 0);
            }
            return true;
	}
	
	return false;
}

bool execute(struct Command* command, unsigned char objectId) {
    if(!behave[objectId] || !behave[objectId](command)) {
       return standardExecute(command, objectId);
    }

    return true;
}

void drawTrap(int x, int y) {
    int i;
    char trap[4][6] = {
        "+---+",
        "\x95...\x95",
        "\x95.\xF8.\x95",
        "+---+"
    };

    setBank(BANK_MODE_SCREEN);
	for(i = 0; i < 4; i++) {
		setCursor(x, y + i);
		printf("%s\r\n",trap[i]);
	}
	setBank(BANK_MODE_DATABASE);
}

void drawSimulation(int x, int y, bool drawPlayer) {
	int i;
	char tuto[10][14] = {
		"+---+- -+---+",
		"\x95...\x95...\x95...\x95",
		"\x95...\x95...\x95...\x95",
		"+- -+- -+- -+",
		"\x95...\x95...\x95...\x95",
		"\x95... ...\x95...\x95",
		"+- -+---+- -+",
		"\x95...\x95...\x95...\x95",
		"\x95... ... ...\x95",
		"+---+---+---+"
	};
		
	// colonnes héros : 2 6 10
	// lignes héros : 2 5 8
	unsigned char heroX[9] = { 2,  6, 10,  2,  6, 10,  2,  6, 10};
	unsigned char heroY[9] = { 2,  2,  2,  5,  5,  5,  8,  8,  8};
	unsigned char heroPosIndex = currentLocationId - NW_ROOM;

    // printf("%u %c\r\n", getState(SIM_DOOR, MASK_CLOSED), tuto[3][10]);
	// Afficher la porte
	tuto[3][10] = getState(SIM_DOOR, MASK_CLOSED) ? 0xA5:' ';
	
	// Afficher la clef
	tuto[1][10] = contains(NE_ROOM, SIM_KEY) ? '?':'.';
	
	// Afficher le garde
	tuto[1][6] = contains(N_ROOM, SIM_GUARD) ? '*':'.';
	
	// Afficher le coffre
	tuto[1][2] = getState(SIM_CHEST, MASK_CLOSED) ? '$' :'S';
	
	// Afficher le joueur
	if (drawPlayer) tuto[heroY[heroPosIndex]][heroX[heroPosIndex]] = 0xF8;
	
	setBank(BANK_MODE_SCREEN);
	for(i = 0; i < 10; i++) {
		setCursor(x, y + i);
		printf("%s\r\n",tuto[i]);
	}
	setBank(BANK_MODE_DATABASE);
}

const char* imageFile[] = {
	"GOD.SCR", // GOD_ROOM
    "FOREST.SCR", // FOREST
    "MFOREST.SCR", // M_FOREST
    "OUTDOOR.SCR", // CHURCH_OUTDOOR
    "OUTDOOR.SCR", // M_CHURCH_OUTDOOR
    "INDOOR.SCR", // CHURCH_INDOOR
    "MINDOOR.SCR", // M_CHURCH_INDOOR
    "CRYPT.SCR", // CRYPT
    "CRYPT.SCR", // M_CRYPT
    "LABO.SCR", // LABORATORY
    "NOBOOK.SCR", // M_LABORATORY
    "CMIRROR.SCR", // MIRROR_ROOM
    "CMIRROR.SCR", // M_MIRROR_ROOM
    "OUTHUT.SCR", // HUT_OUTDOOR
    "OUTHUT.SCR", // M_HUT_OUTDOOR
    "NINHUT.SCR", // HUT_INDOOR
    "INHUT.SCR", // M_HUT_INDOOR
    "RUIN.SCR", // CAVERN_OUTDOOR
    "MRUIN.SCR", // M_CAVERN_OUTDOOR
    "CAVERN.SCR", // CAVERN_INDOOR
    "CAVERN.SCR", // M_CAVERN_INDOOR
    "SECRET.SCR", // SECRET_ROOM
    "MSECRET.SCR", // M_SECRET_ROOM
};

int getLocationImageIndex(int locationId) {
    if (locationId == LABORATORY && !contains(LABORATORY, BOOK)) {
        locationId = M_LABORATORY; // on utilise NOBOOK.SCR
    }
    return locationId - GOD_ROOM;
}

void setLocationPalette(int locationId) {
    // PERFECT ENDING : 0, 13, 3, 16
    switch(locationId) {
        case GOD_ROOM:
            set_paletteMode1(0, 17, 11, 26);
            break;
        case FOREST:
            set_paletteMode1(0, 25, 3, 9);
            break;
        case M_FOREST:
            set_paletteMode1(0, 12, 3, 9);
            break;
        case CHURCH_OUTDOOR:
        case M_CHURCH_OUTDOOR:
            set_paletteMode1(0, 14, 3, 9);
            break;
        case CHURCH_INDOOR:
            set_paletteMode1(0, 13, 0,2);
            break;
        case M_CHURCH_INDOOR:
            set_paletteMode1(0, 12, 24,3);
            break;
        case LABORATORY:
            if (getState(BUTTON, MASK_CLOSED)) {
                set_paletteMode1(0, 13, getSubstrateColor(), 0);
            } else {
                set_paletteMode1(0, 13, getSubstrateColor(), 3);
            }
            break;
        case M_LABORATORY:
            set_paletteMode1(0, 13, 0, 0);
            break;
        case HUT_OUTDOOR:
        case M_HUT_OUTDOOR:
            set_paletteMode1(0, 16, 3, 9);
            break;
        case HUT_INDOOR:
        case M_HUT_INDOOR:
            set_paletteMode1(0, 16, 1, 3);
            break;
        case SECRET_ROOM:
        case M_SECRET_ROOM:
            set_paletteMode1(0, 13, 12, 26);
            break;
        case CAVERN_INDOOR:
        case M_CAVERN_INDOOR:
            set_paletteMode1(0, 13, 3, 12);
            break;
        case CAVERN_OUTDOOR:
        case M_CAVERN_OUTDOOR:
            set_paletteMode1(0, 10, 3, 9);
            break;
        case CRYPT:
            if(getState(DOOR, MASK_CLOSED)) {
                set_paletteMode1(0, 13, 3, 12);
            } else {
                set_paletteMode1(0, 13, 0, 0);
            }
            break;
        case M_CRYPT:
            if(getState(M_DOOR, MASK_CLOSED)) {
                set_paletteMode1(0, 13, 3, 12);
            } else {
                set_paletteMode1(0, 13, 0, 0);
            }
            break;
        case MIRROR_ROOM:
        case M_MIRROR_ROOM:
            set_paletteMode1(0, 13, ((heroStatus == SHINY) ? 26 : 23), 26);
            break;
        default:
            set_paletteMode1(0, 13, 12, 26);
    }
}

int getPatchId(unsigned char locationId) {
    switch(locationId) {
        case LABORATORY:
            return getState(BUTTON, MASK_CLOSED) ? -1 : 0;
        case CRYPT:
            return getState(STATUETTE, MASK_CUSTOM_STATE) ? -1 : 1;
        case M_CRYPT:
            return getState(M_STATUETTE, MASK_CUSTOM_STATE) ? -1 : 1;
        case CAVERN_INDOOR:
            return getState(CHEST, MASK_CLOSED) ? -1 : 2;
        case M_CAVERN_INDOOR:
            return getState(M_CHEST, MASK_CLOSED) ? -1 : 2;
        case SECRET_ROOM:
            return (contains(BASRELIEF, WHISTLE)) ? 3 : -1;
        case M_SECRET_ROOM:
            return (contains(M_BASRELIEF, PARTITION)) ? 4 : -1;
        case M_HUT_INDOOR:
            return getState(HERMIT, MASK_DEAD) ? 5 : -1;
        case CHURCH_INDOOR:
            return getState(TRAPPE, MASK_CLOSED) ? -1 : 6;
        case M_CHURCH_INDOOR:
            return getState(M_TRAPPE, MASK_CLOSED) ? -1 : 6;
    }

    return -1;
}

bool isInversedLocation(unsigned char locationId) {
	if (locationId == GOD_ROOM) return false;

	return (locationId - GOD_ROOM) % 2 == 0; 
}

bool isSecretRoomOpen() {
    return (getState(M_STATUETTE, MASK_CUSTOM_STATE) && getState(STATUETTE, MASK_CUSTOM_STATE));
}

bool isMSecretRoomOpen() {
    return (!getState(M_STATUETTE, MASK_CUSTOM_STATE) && !getState(STATUETTE, MASK_CUSTOM_STATE));
}

void updateDoorsState(bool mirrored) {
    setState(DOOR, MASK_CLOSED, !getState(M_STATUETTE, MASK_CUSTOM_STATE));
	setState(M_DOOR, MASK_CLOSED, getState(STATUETTE, MASK_CUSTOM_STATE));

    setLocationPalette(currentLocationId);
	displayImage(mirrored, getPatchId(currentLocationId));
}
