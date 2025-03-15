#ifndef __DIALOG__
#define __DIALOG__
#include <stdbool.h>
extern bool hermitEncountered;
extern bool keyKnown;
void badEnding();

void finEpreuve();
void dialogErmit();
void dialogueDieu();

void endingMessage(int trophyId);
void ending(int trophyId);
void trophyMenu();
void backToCheckpoint(int trophyId);
#endif