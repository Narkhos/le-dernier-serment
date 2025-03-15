#include "alchemy.h"
#include "parser/parser.h"
#include "lib.h"
#include "database.h"
#include <string.h>
#include <stdio.h>
#include "language.h"

char* colorNames[27] = {
    _T0113,
    _T0114, // 1
    _T0115,   // 2
    "",
    _T0116, // 4
    _T0116, // 5
    _T0117,  // 6
    "",
    "",
    "",
    "",
    "",
    _T0118,   // 12
    "",
    "",
    _T0119, // 15
    "",
    _T0120,   // 17
    _T0121,   // 18
    "",
    "",
    "",
    "",
    _T0122,// 23
    "",
    _T0123,   // 25
    _T0124    // 26
};

// DEAD, LIVELY, SICK, SHINY, INVISIBLE, NERVOUS, SLEEPY
// REC_OSTENTATIOUS, REC_INVISIBLE, REC_STIMULATING, REC_CALMING, REC_BEGINNING, REC_ENDING, REC_ERROR
struct Recipe recipes[RECIPE_COUNT] = {
    { // REC_NONE
        "",
        NO_EFFECT,
        23
    },
    { // REC_OSTENTATIOUS
        "1s2m3b",
        SHINY,
        2
    },
    { // REC_INVISIBLE
        "1b2m3p",
        INVISIBLE,
        1
    },
    { // REC_STIMULATING
        "1s2f1m",
        NERVOUS,
        18
    },
    { // REC_CALMING
        "1f2p1m",
        SLEEPY,
        18
    },
    { // REC_BEGINNING
        "1s3c2m",
        LIVELY,
        12
    },
    { // REC_ENDING
        "1c3p2m",
        SICK,
        5
    },
    { // REC_ERROR
        "E",
        SICK,
        4
    },
    { // REC_EMPTY
        "V", // Pour vérifier si la fiole est vide
        NO_EFFECT,
        0
    }
};

unsigned char temperature = 0;
unsigned char alchemyBuffer[7] = "\0";
// unsigned char alchemyBuffer[7] = "1c3p\0";
unsigned char actionNumber;
unsigned char substrateColors[6] = {23,25,15,17,6,26};

unsigned char flaskBuffer[7] = "V"; // REC_EMPTY
// unsigned char flaskBuffer[7] = ""; // REC_NONE
// unsigned char flaskBuffer[7] = "1s2m3b"; // REC_OSTENTATIOUS
// unsigned char flaskBuffer[7] = "1b2m3p"; // REC_INVISIBLE
// unsigned char flaskBuffer[7] = "1s2f1m"; // REC_STIMULATING
// unsigned char flaskBuffer[7] = "1f2p1m"; // REC_CALMING
// unsigned char flaskBuffer[7] = "1s3c2m"; // REC_BEGINNING
// unsigned char flaskBuffer[7] = "1c3p2m"; // REC_ENDING
// unsigned char flaskBuffer[7] = "E"; // REC_ERROR

void updateTemperature() {
    if(getState(BUTTON, MASK_CLOSED)) {
        if (temperature > 0) temperature --;
    } else {
        if (temperature < 5) {
            temperature ++;
        }
    }

    if (temperature >= 5) {
        clearAlchemyBuffer();
    }
}

void clearAlchemyBuffer() {
    // remet à 0 le buffer d'actions d'alchimie
    alchemyBuffer[0]='\0';
}

unsigned char getSubstrateColor() {
    int i;
    if(strlen(alchemyBuffer) == 6) {
        // Renvoi de la couleur Erreur
        if (alchemyBuffer[0] == 'E') return recipes[REC_ERROR].color;

        // Renvoyer la couleur de la potion obtenue
        for(i=0; i<RECIPE_COUNT;i++) {
            if(strcmp(alchemyBuffer,recipes[i].buffer) == 0) {
                return recipes[i].color;
            }
        }

        return recipes[REC_ERROR].color;
    }

    return substrateColors[temperature];
}

int getRecipeId(const unsigned char *buffer) {
    int i;
    for(i=0; i<RECIPE_COUNT;i++) {
        if(strcmp(buffer,recipes[i].buffer) == 0) {
            return i;
        }
    }

    return REC_ERROR;
}

int getFlaskRecipeId() {
    return getRecipeId(flaskBuffer);
}

int getCauldronRecipeId() {
    return getRecipeId(alchemyBuffer);
}

void addIngredient(unsigned char ingredient) {
    if (ingredient != 'm') {
        printMessage(_T0125, NULL, 0);
    }
    if(strlen(alchemyBuffer) >= 6) {
        // On a dépassé le nombre d'ingrédients, on met le buffer en erreur
        alchemyBuffer[0] = 'E';
        return;
    }

    sprintf(alchemyBuffer, "%s%i%c", alchemyBuffer, temperature, ingredient);
}

void cauldronToFlask() {
    strcpy(flaskBuffer, alchemyBuffer);
    printMessage(_T0126, NULL, 0);
}

void drinkPotion(bool flask) {
    // Trouver la potion correspondante
    int potionId = flask
        ? getFlaskRecipeId()
        : getCauldronRecipeId();

    // Vider la fiole
    if (flask) {
        if (isFlaskEmpty()) {
            printMessage(_T0127, NULL, 0);
        } else {
            printMessage(_T0128, NULL, 0);
            flaskBuffer[0] = 'V';
            flaskBuffer[1] = '\0';
        }
    }

    // Appliquer son effet au héros ou au monde
    switch(potionId) {
        case REC_BEGINNING:
            turn=0;
            break;
        case REC_NONE:
            break;
        default:
            setHeroStatus(recipes[potionId].statusId);
    }
}

bool isFlaskEmpty() {
    return (flaskBuffer[0] == 'V');
}