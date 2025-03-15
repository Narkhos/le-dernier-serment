#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <stdbool.h>
#include <stddef.h>

#define MAX_OBJECT_COUNT 87
#define MAX_DESCRIPTION_LENGTH 64
#define MAX_NAME_COUNT 5
// Décrit un objet du jeu (le héros, l'inventaire, un lieu, une arme, un coffre, une porte...)
struct Object {
	char names[MAX_NAME_COUNT][11];
    char displayName[16];
	unsigned char objectId;
	unsigned char containerId;
	char description[MAX_DESCRIPTION_LENGTH];
	char state;
};

// Liste des objets
enum objectIds{
    // Système
    NO_OBJECT,
    CONTEXT,
    // Protagoniste
    HERO,
    INVENTORY,
    // Personnages
    HERMIT,
    NAHASH,
    GOD,
    // Objets
    FLUTE,
    M_FLUTE,
    STOVE,
    M_BUTTON,
    IVY,
    LADDER,
    TOWER,
    M_TOWER,
    HUT,
    M_HUT,
    BASRELIEF,
    M_BASRELIEF,
    BUSH,
    AMULET,
    BERRY,
    TRAPPE,
    M_TRAPPE,
    BUTTON,
    BOOK,
    MINT,
    TIBIA,
    FLASK,
    MUSHROOMS,
    BONES,
    SALT,
    PEPPER,
    ARTEFACT,
    GONG,
    CAULDRON,
    M_CAULDRON,
    STATUETTE,
    M_STATUETTE,
    WHISTLE,
    PARTITION,
    DOOR,
    M_DOOR,
    CHURCH,
    CHEST,
    M_CHEST,
    KEY,
    FIREBRAND,
    MIRROR,
    M_MIRROR,
    // Simulation locations
    NW_ROOM,
    N_ROOM,
    NE_ROOM,
    W_ROOM,
    CENTER_ROOM,
    E_ROOM,
    SW_ROOM,
    S_ROOM,
    SE_ROOM,
    // Simulation objects
    SIM_CLUB,
    SIM_GUARD,
    SIM_CHEST,
    SIM_KEY,
    SIM_DOOR,
    // Lieux
    GOD_ROOM,
    FOREST,
    M_FOREST,
    CHURCH_OUTDOOR,
    M_CHURCH_OUTDOOR,
    CHURCH_INDOOR,
    M_CHURCH_INDOOR,
    CRYPT,
    M_CRYPT,
    LABORATORY,
    M_LABORATORY,
    MIRROR_ROOM,
    M_MIRROR_ROOM,
    HUT_OUTDOOR,
    M_HUT_OUTDOOR,
    HUT_INDOOR,
    M_HUT_INDOOR,
    CAVERN_OUTDOOR,
    M_CAVERN_OUTDOOR,
    CAVERN_INDOOR,
    M_CAVERN_INDOOR,
    SECRET_ROOM,
    M_SECRET_ROOM,
    OBJECT_COUNT
};

extern struct Object objectDatabase[MAX_OBJECT_COUNT];

#endif
