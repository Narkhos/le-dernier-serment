#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "lib.h"
#include "define.h"
#include "sound.h"
#include "parser/game.h"

struct MenuOption currentMenu[8];
unsigned char menuOptionCount = 0;

void clearMenu() {
	menuOptionCount = 0;
}

void addMenuOption(char *text, int id) {
	strcpy(currentMenu[menuOptionCount].text, text);
	currentMenu[menuOptionCount].id = id;
	
	menuOptionCount++;
}

struct MenuOption* getMenuOptionById(int id) {
	int i;
	for(i=0; i < menuOptionCount; i++) {
		if (currentMenu[i].id == id) return &currentMenu[i];
	}
	
	return NULL;
}

void clearChoices(int lineCount) {
    int i;
	setBank(BANK_MODE_SCREEN);
	setCursor(0,14);
    for(i=0; i<lineCount; i++) {
		printf("                                        ");
    }

	setBank(BANK_MODE_DATABASE);
}

void displayMenu(int selected, bool refresh) {
	int y=22;
    int i;

    setBank(BANK_MODE_SCREEN);

	for(i=menuOptionCount - 1; i >=0 ; i--) {
        strcpy(tmpDescription, currentMenu[i].text);
		setCursor(0, y);
		setCursor((40 - strlen(tmpDescription))/2 - 1, y);
        if (refresh) {
            printf("%c", (i == selected) ? '>' : ' ');
        } else {
            printf("%c ",(i == selected) ? '>' : ' ');
            printu(tmpDescription);
        }
		y--;
	}

    setBank(BANK_MODE_DATABASE);
}

int menu ()
{
    bool refresh = false;
    unsigned char key;
    int selected = 0;
 
    do
    {
        displayMenu(selected, refresh);
        refresh = true;
        key = getchar();
        
        sound(3, 239, 2, 9, 0, 0, 0);

        #ifdef __DEBUG__
            setCursor(0,0);
            printf("%u", (unsigned int)key);
        #endif

        switch(key) {
            case 240:    // key up
                if (selected == 0) {
                    selected = menuOptionCount - 1;
                } else {
                    selected = selected - 1;
                }
                break;
            case 241:    // key down
                if (selected == menuOptionCount - 1) {
                    selected = 0;
                } else {
                    selected = selected + 1;
                }
                break;
            case 13:    // enter key
            case 32:    // space key
                clearChoices(9);
                return currentMenu[selected].id;
                break;
            default:
        }
    }
    while ( 1 );
}

// Exemple d'utilisation 
// int main ( void )
// {
//     char* choices[] = {"A--", "B--", "C--"};
//     printf ( "choice : %d\n", menu ( 3, choices ) );
//     return 0;
// }

void menuOk() {
    clearMenu();
	addMenuOption("OK", 0);
	menu();
}
