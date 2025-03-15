#ifndef __PARSER_H__
#define __PARSER_H__

#include "../database.h"
#include "../datatext.h"

// #define __DEBUG__

#define MAX_SEARCH_DEPTH 4

extern struct Object* objects;
extern struct DataText* dataText;

// Met une chaine de caractères en majuscule
void toupperString(char* text);

// Vérifie si une chaine de caractère est dans un tableau
bool isInArray(char* s, const char** array, int len);

// Représente une commande une fois parsée.
struct Command {
    int verbId;
    char verb[16];
	char object[16];
	char complement[16];
};

// Liste des index des verbes possibles
enum verbIds{Empty, Nord, Sud, Est, Ouest, Monter, Descendre, Regarder, Fouiller, Prendre, Utiliser, Poser, Tirer, Pousser, Tourner, Inventaire, Dormir, Manger, Aller, Sortir, Ouvrir, Fermer, Lire, Parler, Aide, Attendre, Melanger, Jouer, Saler, Poivrer, Remplir, Vider, Deverrouiller, Verrouiller, Allumer, Eteindre, Sauver, Charger, VERB_COUNT};

// liste des verbes et de leurs synonymes
extern const char* verbs[VERB_COUNT][6];

// liste des réponses type pour chaque verbe
extern const char* responses[VERB_COUNT];

// Séparateurs de mots
extern const char* separators;

// Mots inutils à ignorer lors du parsing
extern const char* noiseWords[];

// Longueur de la liste des mots inutils
extern const int noiseWordsLen ;

// Récupère l'index du verbe. O si non trouvé.
int getVerbId(char* verb);

// Indique si la chaine s peut désigner l'objet "object" en parcourant la liste de ses noms.
bool objectMatch(unsigned char objectId, char* s);

// retourne l'id du premier objet qui match avec le nom passé en paramètre
unsigned char findObject(char* s, int startingFromId);

// Vérifie si un objet est accessible depuis un container donné
bool isAccessibleIn(unsigned char containerId, unsigned char objectId, unsigned char depth);

// Recherche un objet dans un container récursivement
unsigned char findObjectIn(unsigned char containerId, char* s);

// Cherche un objet dans un container récursivement
// Remarque : on test aussi l'objet container lui-même
// unsigned char findObjectIn(struct Object* object, char* s);

// Récupère un pointeur sur le container courrant d'un objet donné
struct Object* getContainer(unsigned char objectId);

// Déplacer un objet d'un conteneur à un autre
bool moveObjectTo(unsigned char containerId, unsigned char objectId);
bool contains(unsigned char containerId, unsigned char objectId);

bool isSelf(char* s);

bool isNoiseWord(char* s);


// Commande en cours de traitement
extern struct Command currentCommand;

// Parse la commande saisie par l'utilisateur pour la traduire sous forme de struct Command (Verb/Object/complement)
struct Command* parseCommand(char* command);


// Masques pour les flags d'état des objets
extern const unsigned char MASK_CLOSED;
extern const unsigned char MASK_LOCKED;
extern const unsigned char MASK_PICKABLE;
extern const unsigned char MASK_CONTAINER;
extern const unsigned char MASK_HIDDEN;
extern const unsigned char MASK_DEAD;
extern const unsigned char MASK_OPENABLE;
extern const unsigned char MASK_CUSTOM_STATE;

// Retourne l'état d'un flag dans le state d'un objet
// par exemple getState(monObjetId, MASK_CLOSED);
bool getState(unsigned char objectId, char mask);

// Met à true ou false les bits du masque pointés par mask dans le state de l'objet object
void setState(unsigned char objectId, char mask, bool state);

#endif
