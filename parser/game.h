#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "parser.h"
#include "behavior.h"

enum heroStateIds{NO_EFFECT, DEAD, LIVELY, SICK, SHINY, INVISIBLE, NERVOUS, SLEEPY};

extern char strBuffer[256];

void printMessage(char* message, char* param, int line);
void printMessage2(char* message, char* param1, char* param2);

void printDataText(int textId, int line);

void changeLocation(unsigned char locationId);

bool isInInventory(unsigned char objectId);

int listContent(unsigned char objectId) ;

bool take(unsigned char objectId);

// méthode d'exécution d'objet standard à utiliser comme alternative pour les verbes non gérés par l'objet
// Cette méthode doit être appelée en fin de méthode execute d'un objet afin de gérer certains verbes
// de manière standard s'ils ne sont pas explicitement gérés par la méthode execute de l'objet.
// Notamment, regarder aura toujours plus ou moins le même comportement : afficher la description de
// l'objet.
bool standardExecute(struct Command* command, unsigned char objectId);

// Execute la fonction behave d'un objet si elle existe, sinon, execute standardExecute()
bool execute(struct Command* command, unsigned char objectId);

enum Endings{END_BOMB, END_FREEDOM, END_ORDER, END_BALANCE, END_MESSIAH, ENDING_COUNT};
struct Trophy {
	char title[40];
	bool unlocked;
};

void drawTrap(int x, int y);
void drawSimulation(int x, int y, bool drawPlayer);

extern const char* imageFile[];
int getLocationImageIndex(int locationId);
void setLocationPalette(int locationId);
bool isInversedLocation(unsigned char locationId);
int getPatchId(unsigned char locationId);

bool isSecretRoomOpen();
bool isMSecretRoomOpen();

void updateDoorsState(bool mirrored);

// TODO: GERER LA SAUVEGARDE
// En principe, tout ce qui doit être sauvegardé devrait se trouver ci-dessous
// Les objets

#include "../database.h"

extern unsigned char heroStatus;
extern unsigned char heroStatusTimer;
void displayStatus();
void setHeroStatus(const unsigned char newStatus);
void updateHeroStatus();
// Nombre de tours écoulés depuis le début de la partie
extern unsigned int turn;

// index du lieu ou le héros se trouve actuellement
extern unsigned char currentLocationId;

extern struct Trophy trophies[ENDING_COUNT];

extern unsigned char currentSceneId;

// Buffer pour stocker la description d'un objet ou d'un lieu
extern char tmpDescription[MAX_DESCRIPTION_LENGTH];
#endif