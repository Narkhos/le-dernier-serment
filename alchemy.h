#ifndef __ALCHEMY__
#define __ALCHEMY__
#include "./parser/game.h"

enum recipeIds{REC_NONE, REC_OSTENTATIOUS, REC_INVISIBLE, REC_STIMULATING, REC_CALMING, REC_BEGINNING, REC_ENDING, REC_ERROR, REC_EMPTY, RECIPE_COUNT};

struct Recipe {
    unsigned char buffer[7];
    unsigned char statusId; // état provoqué chez le héros
    unsigned char color;
};

extern struct Recipe recipes[RECIPE_COUNT];

extern char* colorNames[27];
extern unsigned char temperature;
extern unsigned char alchemyBuffer[7];
extern unsigned char actionNumber;
extern unsigned char substrateColors[6];

extern unsigned char flaskBuffer[7];
bool isFlaskEmpty();

void updateTemperature();

void clearAlchemyBuffer();

unsigned char getSubstrateColor();

int getRecipeId(const unsigned char *buffer);
int getFlaskRecipeId();
int getCauldronRecipeId();
void addIngredient(unsigned char ingredient);

void cauldronToFlask();

void drinkPotion(bool flask);

#endif