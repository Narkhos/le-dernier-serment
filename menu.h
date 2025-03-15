#ifndef __MENU_H__ 
#define __MENU_H__

struct MenuOption {
	char text[32];
	int id;
};

extern struct MenuOption currentMenu[8];
extern unsigned char menuOptionCount;

void clearMenu();
void addMenuOption(char *text, int id);

struct MenuOption* getMenuOptionById(int id);
void clearChoices(int lineCount);
int menu ();

void menuOk();
#endif
