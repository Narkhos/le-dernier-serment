#include "parser/game.h"
#include "menu.h"
#include "language.h"

#include "book.h"

void recipeShiny() {
	printDataText(0, 0);
	printDataText(1, 1);
	printDataText(2, 2);
	printDataText(3, 3);
	printDataText(4, 4);
	printDataText(5, 5);
	// printMessage("-Quand le substrat est jaune,salez", NULL, 0);
	// printMessage("-Mélangez lorsqu'il est orange", NULL, 1);
	// printMessage("-Au rose,incorporez les baies", NULL, 2);
	// printMessage("Pensez à couper le feu,sans quoi,", NULL, 3);
	// printMessage("le substrat reprend ses propriétés", NULL, 4);
	// printMessage("initiales dès qu'il passe au blanc.", NULL, 5);

	clearMenu();
	addMenuOption(_T0129, 0);
	menu();
}

void recipeInvisible() {
	printDataText(6, 0);
	printDataText(7, 1);
	printDataText(8, 2);
	printDataText(9, 3);
    // printMessage("-Au jaune,incorporez les baies", NULL, 0);
	// printMessage("-Mélangez au orange", NULL, 1);
	// printMessage("-Au rose,mettez le poivre", NULL, 2);
	// printMessage("Cette recette est la TRANSPOSITION de la potion de lumière", NULL, 3);

	clearMenu();
	addMenuOption(_T0129, 0);
	menu();
}

void recipeNervous() {
	printDataText(10, 0);
	printDataText(11, 1);
	printDataText(12, 2);
	printDataText(13, 3);
	printDataText(14, 4);
    // printMessage("-Allumez le feu et salez", NULL, 0);
	// printMessage("-Sans attendre incorporez la menthe", NULL, 1);
	// printMessage("-Arrêtez de chauffer", NULL, 2);
	// printMessage("-Au jaune,mélangez.", NULL, 3);
	// printMessage("Si tout s'est bien passé,le liquide de-vrait prendre une couleur verte.", NULL, 4);

	clearMenu();
	addMenuOption(_T0129, 0);
	menu();
}

void recipeSleepy() {
	printDataText(15, 0);
	printDataText(16, 1);
	printDataText(17, 2);
    // printMessage("-TRANSPOSEZ la recette de la potion", NULL, 0);
    // printMessage("stimulante", NULL, 1);
	// printMessage("ATTENTION:ce mélange est indiscernable  de sa TRANSPOSEE", NULL, 2);

	clearMenu();
	addMenuOption(_T0129, 0);
	menu();
}

void recipeBeginning() {
	printDataText(18, 0);
	printDataText(19, 1);
	printDataText(20, 2);
	printDataText(21, 3);
    // printMessage("-Allumez le feu et salez", NULL, 0);
	// printMessage("-Après 1 sablier mettez les amanites", NULL, 1);
	// printMessage("-Ramenez au orange et mélangez", NULL, 2);
	// printMessage("ATTENTION:NE JAMAIS TRANSPOSER CETTE    RECETTE", NULL, 3);

	clearMenu();
	addMenuOption(_T0129, 0);
	menu();
}

void recipeBook() {
    int selected;
    void (*recipes[5])() = {recipeShiny, recipeInvisible, recipeNervous, recipeSleepy, recipeBeginning};
    do {
		clearMenu();
		addMenuOption(_T0130, 0);
		addMenuOption(_T0131, 1);
		addMenuOption(_T0132, 2);
		addMenuOption(_T0133, 3);
		addMenuOption(_T0134, 4);
		addMenuOption(_T0135, 5);
        selected = menu();
        if(selected != 5) {
            (*recipes[selected])();
        } else break;
    } while(1);
}