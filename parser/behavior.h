#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "game.h"
#include "parser.h"
#include "../menu.h"

bool ingredientExecute(struct Command* command, const unsigned char ingredientCode);

bool canPassMirror();

// FONCTIONS "EXECUTE" DES OBJETS DU JEU
// Protagoniste
bool heroExecute(struct Command* command);
bool inventoryExecute(struct Command* command);

// Personnages
bool pnj_hermitExecute(struct Command* command);
// bool pnj_nahashExecute(struct Command* command);
bool pnj_godExecute(struct Command* command);

// Objets
bool obj_stoveExecute(struct Command* command);
bool obj_m_buttonExecute(struct Command* command);
bool obj_ivyExecute(struct Command* command);
bool obj_ladderExecute(struct Command* command);
bool obj_towerExecute(struct Command* command);
bool obj_m_towerExecute(struct Command* command);
bool obj_hutExecute(struct Command* command);
bool obj_m_hutExecute(struct Command* command);
bool obj_basReliefExecute(struct Command* command);
bool obj_m_basReliefExecute(struct Command* command);
// bool obj_bushExecute(struct Command* command);
// bool obj_amuletExecute(struct Command* command);
bool obj_berryExecute(struct Command* command);
bool obj_trappeExecute(struct Command* command); // POUR TRAPPE et M_TRAPPE
// bool obj_m_trappeExecute(struct Command* command);
bool obj_buttonExecute(struct Command* command);
bool obj_bookExecute(struct Command* command);
bool obj_mintExecute(struct Command* command);
bool obj_tibiaExecute(struct Command* command);
bool obj_flaskExecute(struct Command* command);
bool obj_mushroomsExecute(struct Command* command);
// bool obj_bonesExecute(struct Command* command);
bool obj_saltExecute(struct Command* command);
bool obj_pepperExecute(struct Command* command);
bool obj_bellExecute(struct Command* command);
bool obj_chestExecute(struct Command* command);
bool obj_m_chestExecute(struct Command* command);
bool obj_keyExecute(struct Command* command);
bool obj_firebrandExecute(struct Command* command);
bool mirrorExecute(struct Command* command); // pour MIRROR et M_MIRROR

// Lieux
bool forestLocationExecute(struct Command* command);
bool churchOutdoorLocationExecute(struct Command* command);
bool churchIndoorLocationExecute(struct Command* command);
bool cryptLocationExecute(struct Command* command);
bool laboratoryLocationExecute(struct Command* command);
bool mirrorRoomLocationExecute(struct Command* command);
bool m_cryptLocationExecute(struct Command* command);
bool m_mirrorRoomLocationExecute(struct Command* command);
// bool m_laboratoryLocationExecute(struct Command* command);
bool m_churchIndoorLocationExecute(struct Command* command);
bool m_churchOutdoorLocationExecute(struct Command* command);
bool m_forestLocationExecute(struct Command* command);
bool hutOutdoorLocationExecute(struct Command* command);
bool m_hutOutdoorLocationExecute(struct Command* command);
bool hutIndoorLocationExecute(struct Command* command);
bool m_hutIndoorLocationExecute(struct Command* command);

bool cavernOutdoorLocationExecute(struct Command* command);
bool m_cavernOutdoorLocationExecute(struct Command* command);
bool cavernIndoorLocationExecute(struct Command* command);
bool m_cavernIndoorLocationExecute(struct Command* command);

bool secretRoomLocationExecute(struct Command* command);

bool m_secretRoomLocationExecute(struct Command* command);

// bool godRoomLocationExecute(struct Command* command);

bool obj_artefactExecute(struct Command* command);
bool obj_gongExecute(struct Command* command);
bool obj_cauldronExecute(struct Command* command);
// bool obj_m_cauldronExecute(struct Command* command);
bool obj_statuetteExecute(struct Command* command);
// bool obj_m_statuetteExecute(struct Command* command);
bool obj_whistleExecute(struct Command* command);
bool obj_partitionExecute(struct Command* command);
// bool obj_doorExecute(struct Command* command);
// bool obj_m_doorExecute(struct Command* command);

// Simulation locations
bool nwRoomLocationExecute(struct Command* command);
bool nRoomLocationExecute(struct Command* command);
bool neRoomLocationExecute(struct Command* command);
bool wRoomLocationExecute(struct Command* command);
bool centerRoomLocationExecute(struct Command* command);
bool eRoomLocationExecute(struct Command* command);
bool swRoomLocationExecute(struct Command* command);
bool sRoomLocationExecute(struct Command* command);
bool seRoomLocationExecute(struct Command* command);

// Simulation objects
bool sim_clubExecute(struct Command* command);
bool sim_chestExecute(struct Command* command);
bool sim_guardExecute(struct Command* command);
bool sim_keyExecute(struct Command* command);
// bool sim_doorExecute(struct Command* command);


extern bool (*behave[OBJECT_COUNT])(struct Command* command);

unsigned char getInversedLocationId(unsigned char locationId);

#endif
