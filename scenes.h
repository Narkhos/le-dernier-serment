#ifndef __SENCES_H__
#define __SCENES_H__

#include <stdbool.h>

void introMenu();

void parser();

void introNahash();

enum sceneIds {SCN_PARSER, SCN_INTRO, SCN_INTRO_NAHASH};
extern void (*scenes[3])();

/**
	Exécute la commande passée en paramètre.
	La fonction envoie la commande aux méthodes execute de tous les objets,
	jusqu'à ce qu'un des objet la traite.
	Si aucun objet n'est concerné, elle affiche un message d'erreur générique.
*/
bool executeCommand(char* commandLine);

#endif