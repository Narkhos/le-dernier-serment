
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "parser.h"
#include "game.h"
#include "../define.h"
#include "../lib.h"
#include "../language.h"

struct Object* objects;
struct DataText* dataText;

// Masques pour les flags d'état des objets
// Pour des raisons de compatibilités avec certains compilateurs comme sdcc
// on n'utilise pas les literals au format binaire
const unsigned char MASK_CLOSED = 1;			// 0b00000001;
const unsigned char MASK_LOCKED = 2;			// 0b00000010;
const unsigned char MASK_PICKABLE = 4;		// 0b00000100;
const unsigned char MASK_CONTAINER = 8; 	// 0b00001000;
const unsigned char MASK_HIDDEN = 16;		// 0b00010000;
const unsigned char MASK_DEAD = 32; 			// 0b00100000;
const unsigned char MASK_OPENABLE = 64; 		// 0b01000000;
const unsigned char MASK_CUSTOM_STATE = 128; // 0b10000000;

bool getState(unsigned char objectId, unsigned char mask) {
	return (objects[objectId].state | mask) == objects[objectId].state;
}

// Met à true ou false les bits du masque pointé par mask dans le state de l'objet object
void setState(unsigned char objectId, char mask, bool state) {
	if (state) {
		objects[objectId].state = objects[objectId].state | mask;
	} else {
		objects[objectId].state = objects[objectId].state & ~mask;
	}
}

// Met une chaine de caractères en majuscule
void toupperString(char* text) {
	int i = 0;
	while(text[i] != '\0') {
		text[i] = toupper(text[i]);
		i++;
	}
}

// Vérifie si une chaine de caractère est dans un tableau
bool isInArray(char* s, const char** array, int len) {
	int i;
	for(i = 0; i < len; ++i) {
		if(array[i] != NULL && !strcmp(array[i], s)) {
			return true;
		}
	}

	return false;
}

#if LANGUAGE == 1 // French
	// liste des verbes et de leurs synonymes
	const char* verbs[VERB_COUNT][6] = {
		{"", "", "", "", "", ""}, // Empty
		{"NORD", "N", "AVAN", "", "", ""}, // Nord
		{"SUD", "S", "RECU", "ARRI", "", ""}, // Sud
		{"EST", "E", "DROI", "", "", ""}, // Est
		{"OUES", "O", "GAUC", "", "", ""}, // Ouest
		{"MONT","ESCA", "GRIM", "HAUT", "", ""}, // Monter
		{"DESC", "BAS", "", "", "", ""}, // Descendre
		{"REGA", "EXAM", "VOIR", "X", ""}, // Regarder
		{"FOUI", "CHER", "LIST", "", ""}, // Fouiller
		{"PREN", "VOLE", "PORT", "CUEI", "DETA", ""}, // Prendre
		{"UTIL", "COMB", "ACTI", "FRAP", "ATTA", "TAPE"}, // Utiliser
		{"POSE", "FIXE", "DEPO", "METT", "INSE", "AJOU"}, // Poser
		{"TIRE", "", "", "", "", ""}, // Tirer
		{"POUS", "", "", "", "", ""}, // Pousser
		{"TOUR", "", "", "", "", ""}, // Tourner
		{"INVE", "I", "", "", "", ""}, // Inventaire
		{"DORM", "DODO", "PAUS", "REPO", "", ""}, // Dormir
		{"MANG", "DEVO", "BOUF", "BOIR", "RONG", "GRIG"}, // Manger
		{"ENTR", "ALLE", "TRAV", "", "", ""}, // Aller
		{"SORT", "PART", "PARS", "FUIR", "", ""}, // Sortir
		{"OUVR", "", "", "", "", ""}, // Ouvrir
		{"FERM", "", "", "", "", ""}, // Fermer
		{"LIRE", "CONS", "", "", "", ""}, // Lire
		{"PARL", "DISC", "APPE", "DIRE", "DEMA", "INTE"}, // Parler
		{"AIDE", "SECO", "", "", "", ""}, // Aide
		{"ATTE", "ATT", "", "", "", ""}, // Attendre
		{"MELA", "TOUI", "", "", "", ""}, // Melanger
		{"JOUE", "SOUF", "", "", "", ""}, // Jouer
		{"SALE", "", "", "", "", ""}, // Saler
		{"POIV", "", "", "", "", ""}, // Poivrer
		{"REMP", "EMPL", "", "", "", ""}, // Remplir
		{"VIDE", "RENV", "", "", "", ""}, // Vider
		{"DEVE", "", "", "", "", ""}, // Deverrouiller
		{"VERR", "VERO", "", "", "", ""}, // Verrouiller
		{"ALLU", "", "", "", "", ""}, // Allumer
		{"ETEI", "", "", "", "", ""}, // Eteindre
		{"SAUV", "SAVE", "ENRE", "", "", ""}, // Sauver
		{"CHAR", "LOAD", "", "", "", ""} // Charger
	};
#endif

#if LANGUAGE == 2 // English
	// liste des verbes et de leurs synonymes
	const char* verbs[VERB_COUNT][6] = {
		{"", "", "", "", "", ""}, // Empty
		{"NORT", "N", "FORW", "", "", ""}, // Nord
		{"SOUT", "S", "BACK", "", "", ""}, // Sud
		{"EAST", "E", "RIGH", "", "", ""}, // Est
		{"WEST", "W", "LEFT", "", "", ""}, // Ouest
		{"UP","CLIM", "", "", "", ""}, // Monter
		{"DOWN", "", "", "", "", ""}, // Descendre
		{"LOOK", "EXAM", "SEE", "X", ""}, // Regarder
		{"SEAR", "LIST", "", "", ""}, // Fouiller
		{"TAKE", "ROB", "STEA", "PICK", "DETA", "DISC"}, // Prendre
		{"USE", "COMB", "ACTI", "HIT", "ATTA", "KNOC"}, // Utiliser
		{"PUT", "PLAC", "DEPO", "INSE", "ADD", ""}, // Poser
		{"PULL", "", "", "", "", ""}, // Tirer
		{"PUSH", "", "", "", "", ""}, // Pousser
		{"TURN", "", "", "", "", ""}, // Tourner
		{"INVE", "I", "", "", "", ""}, // Inventaire
		{"SLEE", "", "", "", "", ""}, // Dormir
		{"EAT", "DRIN", "", "", "", ""}, // Manger
		{"ENTE", "", "", "", "", ""}, // Aller
		{"LEAV", "FLY", "", "", "", ""}, // Sortir
		{"OPEN", "", "", "", "", ""}, // Ouvrir
		{"CLOS", "", "", "", "", ""}, // Fermer
		{"READ", "", "", "", "", ""}, // Lire
		{"TALK", "SPEA", "CALL", "TELL", "ASK", ""}, // Parler
		{"HELP", "", "", "", "", ""}, // Aide
		{"WAIT", "", "", "", "", ""}, // Attendre
		{"STIR", "BLEN", "MIX", "", "", ""}, // Melanger
		{"PLAY", "PERF", "", "", "", ""}, // Jouer
		{"SALT", "", "", "", "", ""}, // Saler
		{"PEPP", "", "", "", "", ""}, // Poivrer
		{"FILL", "", "", "", "", ""}, // Remplir
		{"EMPT", "DRAI", "", "", "", ""}, // Vider
		{"UNLO", "", "", "", "", ""}, // Deverrouiller
		{"LOCK", "", "", "", "", ""}, // Verrouiller
		{"LIGH", "", "", "", "", ""}, // Allumer
		{"SHUT", "", "", "", "", ""}, // Eteindre
		{"SAVE", "", "", "", "", ""}, // Sauver
		{"LOAD", "", "", "", "", ""} // Charger
	};
#endif

#if LANGUAGE == 3 // Spanish
	// liste des verbes et de leurs synonymes
	const char* verbs[VERB_COUNT][6] = {
		{"", "", "", "", "", ""}, // Empty
		{"NORT", "N", "AVAN", "", "", ""}, // Nord
		{"SUR", "S", "RETR", "VOLV", "", ""}, // Sud
		{"ESTE", "E", "DERE", "", "", ""}, // Est
		{"OEST", "O", "IZQU", "", "", ""}, // Ouest
		{"SUBI","ESCA", "SUBE", "ARRI", "TREP", ""}, // Monter
		{"DESC", "BAJA", "ABAJ", "", "", ""}, // Descendre
		{"MIRA", "EXAM", "VER", "X", "EX", "VE"}, // Regarder
		{"HURG", "BUSC", "INVES", "ESCR", ""}, // Fouiller
		{"COGE", "TOMA", "LLEV", "ROBA", "", ""}, // Prendre
		{"UTIL", "USA", "USAR", "GOLP", "UNIR", "UNE"}, // Utiliser
		{"DEJA", "FIJA", "ECHA", "METE", "PON", "PONE"}, // Poser
		{"TIRA", "ESTI", "", "", "", ""}, // Tirer
		{"PULS", "APRE", "EMPU", "ATRA", "", ""}, // Pousser
		{"GIRA", "MOVE", "MUEV", "", "", ""}, // Tourner
		{"INVE", "I", "", "", "", ""}, // Inventaire
		{"DORM", "", "", "", "", ""}, // Dormir
		{"COME", "BEBE", "TRAG", "", "", ""}, // Manger
		{"ENTR", "PASA", "", "", "", ""}, // Aller
		{"SALI", "HUYE", "HUIR", "", "", ""}, // Sortir
		{"ABRI", "ABRE", "", "", "", ""}, // Ouvrir
		{"CERR", "CIER", "", "", "", ""}, // Fermer
		{"LEER", "LEE", "", "", "", ""}, // Lire
		{"HABL", "DECI", "LLAM", "DI", "PREG", "CLAM"}, // Parler
		{"AYUD", "SOCO", "", "", "", ""}, // Aide
		{"ESPE", "", "", "", "", ""}, // Attendre
		{"MEZC", "REMO", "REMU", "", "", ""}, // Melanger
		{"SOPL", "TOCA", "REPR", "", "", ""}, // Jouer
		{"SALA", "", "", "", "", ""}, // Saler
		{"PIME", "", "", "", "", ""}, // Poivrer
		{"RELL", "LLEN", "", "", "", ""}, // Remplir
		{"VACI", "VERT", "", "", "", ""}, // Vider
		{"DESB", "", "", "", "", ""}, // Deverrouiller
		{"BLOQ", "", "", "", "", ""}, // Verrouiller
		{"ENCE", "ENCI", "", "", "", ""}, // Allumer
		{"APAG", "", "", "", "", ""}, // Eteindre
		{"GRAB", "SAVE", "GUAR", "", "", ""}, // Sauver
		{"CARG", "LOAD", "", "", "", ""} // Charger
	};
#endif

// liste des réponses type pour chaque verbe
const char* responses[VERB_COUNT] = {
	_T0079, // Empty
	_T0080, // Nord
	_T0081, // Sud
	_T0082, // Est
	_T0083, // Ouest
	_T0084, // Monter
	_T0085, // Descendre
	_T0086, // Regarder
	_T0087, // Fouiller
	_T0088, // Prendre
	_T0089, // Utiliser
	_T0090, // Poser
	_T0091, // Tirer
	_T0092, // Pousser
	_T0093, // Tourner
	_T0094, // Inventaire
	_T0095, // Dormir
	_T0096, // Manger
	_T0097, // Aller
	_T0098, // Sortir
	_T0099, // Ouvrir
	_T0100, // Fermer
	_T0101, // Lire
	_T0102, // Parler
	_T0103, // Aide
	_T0104, // Attendre
	_T0105, // Melanger
	_T0106, // Jouer
	_T0107, // Saler
	_T0108, // Poivrer
	_T0109, // Remplir
	_T0110, // Vider
	_T0089, // Deverrouiller
	_T0089, // Verrouiller
	_T0089, // Allumer
	_T0089, // Eteindre
	_T0111, // Sauver
	_T0112  // Charger
};

// Séparateurs de mots
const char* separators = " '_.,;:";

#if LANGUAGE == 1 // French
// Mots inutils à ignorer lors du parsing en français
const char* noiseWords[] = { "", "DE", "D", "DU", "DES", "LES", "LE", "LA", "L", "AVEC", "DANS", "SUR", "TOUS", "TOUT", "ET", "UN", "UNE", "A", "AU", "MON", "MA", "MES", "SON", "SA", "SES", "TON", "TA", "TES", "POUR", "EN", "FAIRE", "FAIT", "FAIS", "FAITES", "JE", "J" };
// Longueur de la liste des mots inutils
const int noiseWordsLen = 36;
#endif

#if LANGUAGE == 2 // English
// Mots inutils à ignorer lors du parsing en anglais
const char* noiseWords[] = { "", "OF", "FROM", "THE", "WITH", "IN", "ON", "ALL", "EVERY", "AND", "A", "ONE", "TO", "MY","HIS", "YOUR", "FOR", "BY", "DO", "DOING", "DONE", "GO" };
// Longueur de la liste des mots inutils
const int noiseWordsLen = 22;
#endif

#if LANGUAGE == 3 // Spanish
// Mots inutils à ignorer lors du parsing en français
const char* noiseWords[] = { "", "DE", "EL", "LA", "LOS", "LAS", "A", "LO", "CON", "EN", "POR", "TODO", "TODOS", "Y", "UN", "UNA", "AL", "DEL", "UNOS", "UNAS", "MIS", "SU", "SUS", "TU", "TUS", "PARA" };
// Longueur de la liste des mots inutils
const int noiseWordsLen = 26;
#endif

// Récupère l'index du verbe. O si non trouvé.
int getVerbId(char* verb) {
	char abrev[5];
	unsigned char i; // verb index
	unsigned char j; // synonym index

	strncpy(abrev, verb, 4);
	abrev[4] ='\0';

	for(i=0; i < VERB_COUNT; i++) {
		j = 0;
		do {
			if (strcmp(verbs[i][j], abrev) == 0) {
				return i; // verb found
			}
			j++;
		} while( j < 6  && strcmp(verbs[i][j], ""));
	}
	
	return 0; // verb not found
}

// Indique si la chaine s peut désigner l'objet "object" en parcourant la liste de ses noms.
bool objectMatch(unsigned char objectId, char* s) {
	int i;

	if (strcmp("", s) == 0) return false;

	// if (strcmp(s, "") == 0) return false;

	for(i=0; i < MAX_NAME_COUNT; i++) {
		if (strcmp(objects[objectId].names[i], s) == 0) return true;
	}

	return false;
}

unsigned char findObject(char* s, int startingFromId) {
	int i;
	
	for(i=startingFromId; i < MAX_OBJECT_COUNT; i++) {
		if (objectMatch(i, s)) return i;
	}

	return NO_OBJECT;
}


bool isAccessibleIn(unsigned char containerId, unsigned char objectId, unsigned char depth) {
	
	if (depth >= MAX_SEARCH_DEPTH) return false;

	if (containerId == NO_OBJECT || objectId == NO_OBJECT) return false;

	if (objectId == containerId) return true;

	if (getState(objectId, MASK_HIDDEN)) {
		return NO_OBJECT;
	}

	if (depth > 0) {
		if (getState(objectId, MASK_CLOSED) || getState(objectId, MASK_LOCKED) || getState(objectId, MASK_HIDDEN)) {
		return NO_OBJECT;
	}
	}

	return isAccessibleIn(containerId, objects[objectId].containerId, depth + 1);
}

unsigned char findObjectIn(unsigned char containerId, char* s) {
	int startingFrom = 0;
	unsigned char objectId;

	if (getState(containerId, MASK_CLOSED) || getState(containerId, MASK_LOCKED) || getState(containerId, MASK_HIDDEN)) {
		return NO_OBJECT;
	}

	while(startingFrom < MAX_OBJECT_COUNT) {
		objectId = findObject(s, startingFrom);
		if(objectId == NO_OBJECT) return NO_OBJECT;

		if (isAccessibleIn(containerId, objectId, 0)) {
			return objectId;
		}

		startingFrom = objectId + 1;
	}

	return NO_OBJECT;
}

struct Object* getContainer(unsigned char objectId) {
	return &(objects[objects[objectId].containerId]);
}

bool moveObjectTo(unsigned char containerId, unsigned char objectId) {
	if(objectId == NO_OBJECT) return false;

	objects[objectId].containerId = containerId;

	return true;
}

bool contains(unsigned char containerId, unsigned char objectId) {
	return (objects[objectId].containerId == containerId);
}

bool isSelf(char* s) {
	return objectMatch(HERO, s);
}

bool isNoiseWord(char* s) {
	return isInArray(s, noiseWords, noiseWordsLen);
}

struct Command currentCommand;

// Parse la commande saisie par l'utilisateur pour la traduire sous forme de struct Command (Verb/Object/complement)
struct Command* parseCommand(char* command) {
	char commandTokens[3][16] = {"", "", ""};
	int tokenCounter = 0;
	char* c = command;
	char * strToken;
	
    while ( 1 ) {
        // On demande le token suivant.
        strToken = strtok ( c, separators );
		
		if (strToken == NULL) break;
		if (!isNoiseWord(strToken)) {
			strcpy(commandTokens[tokenCounter], strToken);
			tokenCounter ++;
		}
		if (tokenCounter == 3) break;
		c = NULL;
    }

	// objet verbe complement
	if (isSelf(commandTokens[0])) {
		strcpy(currentCommand.object, commandTokens[0]);
		strcpy(currentCommand.verb, commandTokens[1]);
	} else { // verbe objet complement
		strcpy(currentCommand.verb, commandTokens[0]);
		strcpy(currentCommand.object, commandTokens[1]);
	}
	currentCommand.verbId = getVerbId(currentCommand.verb);

	strcpy(currentCommand.complement, commandTokens[2]);

	#ifdef __DEBUG__
	setBank(BANK_MODE_SCREEN);
	printf("Verbe(%i): %s\r\n", currentCommand.verbId, currentCommand.verb);
	printf("Objet: %s\r\n", currentCommand.object);
	printf("Complement: %s\r\n", currentCommand.complement);
	setBank(BANK_MODE_DATABASE);
	#endif

	return &currentCommand;
}
