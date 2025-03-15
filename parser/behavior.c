#include "../lib.h"
#include "behavior.h"
#include "game.h"
#include "../book.h"
#include "../alchemy.h"
#include "../scenes.h"
#include "../dialog.h"
#include "../sound.h"
#include "../language.h"

const char * messageDeverrouillerCoffre = _T0001;

bool hermitReaction() {
	if (!getState(HERMIT, MASK_DEAD)) {
		if (heroStatus == INVISIBLE) {
			printMessage(_T0002, NULL, 0);
		} else {
			printMessage(_T0003, NULL, 0);
		}
		return true;
	}

	return false;
}

bool heroExecute(struct Command* command) {
	switch(command->verbId) {
		case Parler:
			printMessage(_T0004, NULL, 0);
			return true;
		case Fouiller:
			return inventoryExecute(command);
	}
	
	return false;
}

bool inventoryExecute(struct Command* command) {
	switch(command->verbId) {
		case Inventaire:
		case Regarder:
		case Fouiller:
			strcpy(tmpDescription, objects[INVENTORY].description);
			printMessage(tmpDescription, NULL, 0);
			listContent(INVENTORY);

			return true;
	}

	return false;
}

bool pnj_hermitExecute(struct Command* command) {
	switch(command->verbId) {
		case Parler:
			dialogHermit();
			return true;
		case Fouiller:
			return hermitReaction();
	}
	return false;
}

bool pnj_godExecute(struct Command* command) {
	switch(command->verbId) {
		case Parler:
			dialogueDieu();
			return true;
	}
	return false;
}

bool obj_artefactExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Poser:
			printMessage(_T0005, NULL, 0);
			return true;
		case Utiliser:
		case Jouer:
			if(!isInInventory(ARTEFACT)) return false;
			if (strcmp(command->complement,"") == 0) {
				if (contains(ARTEFACT, WHISTLE)) {
					// Jouer do, ré, mi
					sound(3, 239, 60, 10, 0, 0, 0);
					sound(3, 213, 60, 10, 0, 0, 0);
					sound(3, 190, 60, 10, 0, 0, 0);
					printMessage(_T0006, NULL, 0);
				} else {
					printMessage(_T0007, NULL, 0);
				}
				return true;
            } else {
                complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
					case PARTITION:
						// pour forcer le déclenchement de
						// utiliser PARTITION SCEPTRE
						return false;
                    case GONG:
						changeLocation(GOD_ROOM);
						dialogueDieu();
						return true;
					case GOD:
						ending(END_FREEDOM);
						return true;
					case HERO:
						if (currentLocationId == GOD_ROOM) {
							ending(END_ORDER);
						} else {
							printMessage(_T0008, NULL, 0);
						}
						return true;
                }
            }
	}
	return false;
}
bool obj_gongExecute(struct Command* command) {
	unsigned char complementId;
	switch(command->verbId) {
		case Utiliser:
			if (strcmp(command->complement,"") == 0) {
				printMessage(_T0009, NULL, 0);
			    return true;
            } else {
                complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
                    case TIBIA:
					case FIREBRAND:
						printMessage(_T0010, NULL, 0);
						return true;
				}
			}
			break;
	}
	return false;
}
bool obj_cauldronExecute(struct Command* command) {
	switch(command->verbId) {
		case Manger:
		printMessage(_T0011, NULL, 0);
			drinkPotion(false);
			return true;
		case Regarder:
			printMessage(_T0012, colorNames[getSubstrateColor()], 0);
			return true;
		default:
			return laboratoryLocationExecute(command);
	}
	return false;
}

bool obj_statuetteExecute(struct Command* command) {
	unsigned char objectId = findObjectIn(CONTEXT, command->object);
	unsigned char otherStatuetteId = (objectId == STATUETTE ? M_STATUETTE : STATUETTE);

    switch(command->verbId) {
        case Tourner:
            if (!contains(objectId, FIREBRAND)) {
				printMessage(_T0013, NULL, 0);
                setState(
					objectId,
					MASK_CUSTOM_STATE,
					!getState(objectId, MASK_CUSTOM_STATE)
				);

                if (!contains(otherStatuetteId, FIREBRAND)) {
                    setState(
						otherStatuetteId, MASK_CUSTOM_STATE,
						!getState(otherStatuetteId, MASK_CUSTOM_STATE)
					);
                }

                updateDoorsState(objectId == M_STATUETTE);
            } else {
                printMessage(_T0014, NULL, 0);
            }

            return true;
    }
    return false;
}

bool obj_whistleExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Utiliser:
		case Jouer:
		case Poser:
			if(!isInInventory(WHISTLE)) return false;
			if (strcmp(command->complement,"") == 0) {
				if (command->verbId == Utiliser || command->verbId == Jouer) {
					// Téléportation
					changeLocation(getInversedLocationId(currentLocationId));
					return true;
				}
				return false;
            } else {
                complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
                    case ARTEFACT:
						if(contains(INVENTORY, complementId)) {
							moveObjectTo(ARTEFACT, WHISTLE);

							printMessage(_T0015, NULL, 0);
							return true;
						}
                }
            }
	}
	return false;
}

bool obj_partitionExecute(struct Command* command) {
	if (findObjectIn(CONTEXT, command->complement) != ARTEFACT) return false;
	switch(command->verbId) {
		case Jouer:
		case Utiliser:
			if (contains(INVENTORY, ARTEFACT)
				&& contains(ARTEFACT, WHISTLE)) {
					// Jouer un morceau de musique
					sound(3, 239, 30, 10, 0, 0, 0);
					sound(3, 239, 15, 0, 0, 0, 0);
					sound(3, 159, 30, 10, 0, 0, 0);
					sound(3, 119, 120, 10, 0, 0, 0);
					printMessage(_T0016, NULL, 0);
					menuOk();
					if (currentLocationId == GOD_ROOM) {
						ending(turn == 1 ? END_MESSIAH : END_BALANCE);
					}
				return true;
			}
			break;
	}

	return false;
}

bool sim_chestExecute(struct Command* command) {
	switch(command->verbId) {
		case Ouvrir:
		case Deverrouiller:
			if (isInInventory(SIM_KEY)) {
				setState(SIM_CHEST, MASK_CLOSED, false);
				setState(SIM_CHEST, MASK_LOCKED, false);
				printMessage(messageDeverrouillerCoffre, NULL, 0);
				printMessage(_T0017, NULL, 1);
				return true;
			}
			break;
		case Verrouiller:
			if (isInInventory(SIM_KEY)) {
				setState(SIM_CHEST, MASK_CLOSED, true);
				setState(SIM_CHEST, MASK_LOCKED, true);
				printMessage(_T0018, NULL, 0);
				return true;
			}
			break;
	}

	return false;
}

bool obj_stoveExecute(struct Command* command) {
	switch(command->verbId) {
		case Allumer:
		case Eteindre:
			return obj_buttonExecute(command);
	}
	return false;
}

bool obj_m_buttonExecute(struct Command* command) {
	switch(command->verbId) {
		case Tourner:
		case Pousser:
		case Tirer:
		case Utiliser:
			printMessage(_T0019, NULL, 0);
			return true;
	}
	return false;
}

bool obj_ivyExecute(struct Command* command) {
	switch(command->verbId) {
		case Monter:
			changeLocation(LABORATORY);
			return true;
	}

	return false;
}

bool obj_ladderExecute(struct Command* command) {
	switch(command->verbId) {
		case Monter:
			changeLocation(M_HUT_OUTDOOR);
			return true;
	}

	return false;
}

bool obj_towerExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
		case Aller:
		case Descendre:
			changeLocation(CAVERN_INDOOR);
			return true;
		case Monter:
			changeLocation(LABORATORY);
			return true;
	}

	return false;
}

bool obj_m_towerExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
		case Aller:
		case Descendre:
			changeLocation(M_CAVERN_INDOOR);
			return true;
	}

	return false;
}

bool obj_hutExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
		case Monter:
		case Aller: // entrer
			changeLocation(HUT_INDOOR);
			return true;
	}

	return false;
}

bool obj_m_hutExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
		case Monter:
		case Aller: // entrer
			changeLocation(M_HUT_INDOOR);
			return true;
	}

	return false;
}

bool obj_basReliefExecute(struct Command* command) {
	switch(command->verbId) {
		case Regarder:
			strcpy(tmpDescription, objects[BASRELIEF].description);
			printMessage(tmpDescription, NULL, 0);
			if (contains(BASRELIEF, WHISTLE)) {
				printMessage(_T0020, NULL, 1);
			}
			return true;
	}

	return false;
}

bool obj_m_basReliefExecute(struct Command* command) {
	switch(command->verbId) {
		case Regarder:
			strcpy(tmpDescription, objects[M_BASRELIEF].description);
			printMessage(tmpDescription, NULL, 0);
			if (contains(M_BASRELIEF, PARTITION)) {
				printMessage(_T0021, NULL, 1);
			}
			return true;
	}

	return false;
}

char* escalierTrappe = _T0022;

bool obj_trappeExecute(struct Command* command) {
	unsigned char objectId = findObjectIn(CONTEXT, command->object);
	bool mirrored = (currentLocationId == M_CHURCH_INDOOR);
	switch(command->verbId) {
		case Fouiller:
			if (!getState(objectId, MASK_CLOSED)) {
				printMessage(escalierTrappe, NULL, 0);
				return true;
			}
			break;
		case Ouvrir:
			setState(objectId, MASK_CLOSED, false);
			displayImage(mirrored, getPatchId(currentLocationId));
			printMessage(escalierTrappe, NULL, 0);
			return true;
		case Fermer:
			setState(objectId, MASK_CLOSED, true);
			displayImage(mirrored, getPatchId(currentLocationId));
			return true;
		case Aller:
		case Descendre:
			if(getState(objectId, MASK_CLOSED)) {
				printMessage(_T0023, NULL, 0);
			} else {
				changeLocation(currentLocationId == CHURCH_INDOOR ? CRYPT : M_CRYPT);
			}
			return true;
	}
	return false;
}

bool obj_buttonExecute(struct Command* command) {
	switch(command->verbId) {
		case Tourner:
		case Pousser:
		case Tirer:
		case Utiliser:
		case Allumer:
		case Eteindre:
			if (command->verbId == Allumer && !getState(BUTTON, MASK_CLOSED)) {
				printMessage(_T0024, NULL, 0);

				return true;
			}

			if (command->verbId == Eteindre && getState(BUTTON, MASK_CLOSED)) {
				printMessage(_T0025, NULL, 0);

				return true;
			}

			if (getState(BUTTON, MASK_CLOSED)) {
				printMessage(_T0026, NULL, 0);
			} else {
				printMessage(_T0027, NULL, 0);
			}

			setState(BUTTON, MASK_CLOSED, !getState(BUTTON, MASK_CLOSED));
			displayImage(false, getPatchId(currentLocationId));
			setLocationPalette(LABORATORY);

			return true;
	}
	return false;
}

bool obj_bookExecute(struct Command* command) {
	switch(command->verbId) {
		case Lire:
			recipeBook();
			return true;
		case Prendre:
		case Poser:
			if (currentLocationId == LABORATORY) {
				if(command->verbId == Prendre) {
					moveObjectTo(INVENTORY, BOOK);
				} else {
					moveObjectTo(LABORATORY, BOOK);
				}
				LoadFile(imageFile[getLocationImageIndex(LABORATORY)], currentImage);
				displayImage(false, getPatchId(LABORATORY));
				return true;
			}
			break;
	}

	return false;
}

bool ingredientExecute(struct Command* command, const unsigned char ingredientCode) {
	unsigned char complementId;

	switch(command->verbId) {
		case Utiliser:
		case Poser:
		case Saler:
		case Poivrer:
			complementId = findObjectIn(CONTEXT, command->complement);
			if(complementId == NO_OBJECT && currentLocationId == LABORATORY) {
				complementId = CAULDRON;
			}

			switch(complementId) {
				case CAULDRON:
					addIngredient(ingredientCode);
					return true;
				default:
					return false;
			}
	}
	return false;
}

bool obj_berryExecute(struct Command* command) {
	return ingredientExecute(command, 'b');
}

bool obj_mintExecute(struct Command* command) {
	return ingredientExecute(command, 'f');
}

bool obj_mushroomsExecute(struct Command* command) {
	return ingredientExecute(command, 'c');
}

bool obj_saltExecute(struct Command* command) {
	return ingredientExecute(command, 's');
}

bool obj_pepperExecute(struct Command* command) {
	return ingredientExecute(command, 'p');
}

void mixSubstrate() {
	printMessage(_T0028, NULL, 0);
	addIngredient('m');

	if (getRecipeId(alchemyBuffer) == REC_ENDING) {
		ending(END_BOMB);
	}
}

bool obj_tibiaExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Utiliser:
			complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
                    case CAULDRON:
						mixSubstrate();
						return true;
                }
	}
	return false;
}

bool obj_flaskExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Regarder:
		if (isFlaskEmpty()) {
			printMessage(_T0029, NULL, 0);
		} else {
			printMessage(_T0030, colorNames[recipes[getFlaskRecipeId()].color], 0);
		}
			return true;
		case Utiliser:
			complementId = findObjectIn(CONTEXT, command->complement);

			switch(complementId) {
				case CAULDRON:
					cauldronToFlask();
					return true;
			}
			break;
		case Manger:
			drinkPotion(true);
			return true;
		case Vider:
			if(strcmp(flaskBuffer, "V") == 0) {
				printMessage(_T0031, NULL, 0);
			} else {
				printMessage(_T0032, NULL, 0);
				flaskBuffer[0] = 'V';
				flaskBuffer[1] = '\0';
			}
			return true;
		case Remplir:
			if (currentLocationId == LABORATORY) {
				if (strcmp(flaskBuffer, "V") == 0) {
					cauldronToFlask();
				} else {
					printMessage(_T0033, NULL, 0);
				}
			}
			return true;
	}
	return false;
}

bool obj_churchExecute(struct Command* command) {
	switch(command->verbId) {
        case Aller: // entrer
            changeLocation(CHURCH_INDOOR);
			return true;
	}
	
	return false;
}

bool obj_chestExecute(struct Command* command) {
	int closed = getState(CHEST, MASK_CLOSED);
	switch(command->verbId) {
		case Ouvrir:
			if(!closed) return false;
			if (getState(CHEST, MASK_LOCKED)) {
				printMessage(_T0034, NULL, 0);
			} else {
				setState(CHEST, MASK_CLOSED, false);
				displayImage(false, getPatchId(currentLocationId));
			}
			return true;
		case Deverrouiller:
		case Verrouiller:
			if (isInInventory(KEY)) {
				printMessage(_T0035, NULL, 0);
				return true;
			}
			break;
		case Fermer:
			if(closed) return false;
			setState(CHEST, MASK_CLOSED, true);
			displayImage(false, getPatchId(currentLocationId));
			return true;
	}
	return false;
}

bool obj_m_chestExecute(struct Command* command) {
	int closed = getState(M_CHEST, MASK_CLOSED);

	switch(command->verbId) {
		case Ouvrir:
			if(!closed) return false;
			if (!getState(M_CHEST, MASK_LOCKED)) {
				setState(M_CHEST, MASK_CLOSED, false);
				displayImage(true, getPatchId(currentLocationId));
				return true;
			}
			// sinon on essai de Deverrouiller
		case Deverrouiller:
			if (isInInventory(KEY)) {
				setState(M_CHEST, MASK_CLOSED, false);
				setState(M_CHEST, MASK_LOCKED, false);
				setState(CHEST, MASK_CLOSED, false);
				setState(CHEST, MASK_LOCKED, false);
				printMessage(messageDeverrouillerCoffre, NULL, 0);
				displayImage(true, getPatchId(currentLocationId));
				return true;
			}
			break;
		case Fermer:
			if(closed) return false;
			setState(M_CHEST, MASK_CLOSED, true);
			displayImage(true, getPatchId(currentLocationId));
			return true;
		case Verrouiller:
			if (isInInventory(KEY)) {
				setState(M_CHEST, MASK_CLOSED, true);
				setState(M_CHEST, MASK_LOCKED, true);
				printMessage(_T0036, NULL, 0);
				displayImage(true, getPatchId(currentLocationId));
				return true;
			}
			break;
	}
	
	return false;
}

bool obj_keyExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Utiliser:
			if (!isInInventory(KEY)) return false;
			if (strcmp(command->complement,"") != 0) {
                complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
                    case CHEST:
					 	printMessage(_T0037, NULL, 0);
						return true;
                    case M_CHEST:
                        setState(M_CHEST, MASK_LOCKED, false);
                        setState(CHEST, MASK_LOCKED, false);

                        printMessage(_T0038, objects[complementId].displayName, 0);
                        return true;
                }
            }
			return false;
		case Prendre:
		case Regarder:
			if (contains(HERMIT, KEY)) {
				return hermitReaction();
			}
			break;
	}
	
	return false;
}

bool obj_firebrandExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Prendre:
			if (contains(STATUETTE, FIREBRAND)) {
				setState(STATUETTE, MASK_CUSTOM_STATE,
					!getState(M_STATUETTE, MASK_CUSTOM_STATE));

				updateDoorsState(false);
			} else if (contains(M_STATUETTE, FIREBRAND)) {
				setState(M_STATUETTE, MASK_CUSTOM_STATE,
					!getState(STATUETTE, MASK_CUSTOM_STATE));

				updateDoorsState(true);
			}
			break;
		case Utiliser:
		case Poser:
			if (strcmp(command->complement,"") != 0) {
                complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
                    case STATUETTE:
                    case M_STATUETTE:
						if (isInInventory(FIREBRAND)) {
							printMessage(_T0039, NULL, 0);
							// objects[FIREBRAND].containerId = complementId;
							moveObjectTo(complementId, FIREBRAND);
						} else {
							printMessage(_T0040, NULL, 0);
						}
						return true;
                }
            }
			return false;
	}
	
	return false;
}

bool mirrorExecute(struct Command* command) {
	switch(command->verbId) {
		case Tirer:
		case Prendre:
			printMessage(_T0041, NULL, 0);
			return true;
		case Pousser:
		case Aller:
		case Nord:
			if (canPassMirror()) {
				changeLocation(currentLocationId == MIRROR_ROOM ? M_MIRROR_ROOM : MIRROR_ROOM);
				return true;
			} else {
				printMessage(_T0042, NULL, 0);
				printMessage(_T0043, NULL, 1);
			}
			return true;
	}
	
	return false;
}

// Lieux

bool forestLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			changeLocation(CHURCH_OUTDOOR);
			return true;
		case Sud:
			printMessage(_T0044, NULL, 0);
			menuOk();
			return true;
	}
	
	return false;
}

bool churchOutdoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
			changeLocation(FOREST);
			return true;
		case Est:
			changeLocation(CAVERN_OUTDOOR);
			return true;
		case Nord:
		case Aller: // entrer (TODO : séparer aller et entrer ?)
			changeLocation(CHURCH_INDOOR);
			return true;
	}
	
	return false;
}

bool churchIndoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
			changeLocation(CHURCH_OUTDOOR);
			return true;
		case Est:
		case Descendre:
			return obj_trappeExecute(command);
		case Parler:
			if (currentSceneId == SCN_INTRO) {
				currentSceneId = SCN_INTRO_NAHASH;
			} else {
				printMessage(_T0045, NULL, 0);
			}
			return true;
	}
	
	return false;
}

bool cryptLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Est:
		case Sortir:
		case Monter:
			setState(TRAPPE, MASK_CLOSED, false);
			changeLocation(CHURCH_INDOOR);
			return true;
		case Ouest:
			if (getState(DOOR, MASK_CLOSED)) {
				printMessage(_T0046, NULL, 0);
			} else {
				changeLocation(MIRROR_ROOM);
			}
			return true;
	}
	
	return false;
}

bool laboratoryLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
		case Descendre:
			changeLocation(CAVERN_OUTDOOR);
			return true;
		case Melanger:
			if (findObjectIn(CONTEXT, _T0047)) {
				mixSubstrate();
			} else {
				printMessage(_T0048, NULL, 0);
			}
			return true;
		case Saler:
			if (findObjectIn(CONTEXT, _T0049)) {
				return ingredientExecute(command, 's');
			}
			break;
		case Poivrer:
			if (findObjectIn(CONTEXT, _T0050)) {
				return ingredientExecute(command, 'p');
			}
			break;
		case Manger:
			return obj_cauldronExecute(command);
		case Allumer:
		case Eteindre:
			return obj_buttonExecute(command);
	}

	return false;
}

bool canPassMirror() {
	return (
		contains(INVENTORY, AMULET)
		|| heroStatus == INVISIBLE
	);
}

bool mirrorRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
			if (getState(DOOR, MASK_CLOSED)) {
				printMessage(_T0046, NULL, 0);
			} else {
				changeLocation(CRYPT);
			}
			return true;
		case Ouest:
			if (isSecretRoomOpen()) {
				changeLocation(SECRET_ROOM);
				return true;
			}
			break;
		case Nord:
			return mirrorExecute(command);
	}
	
	return false;
}

bool m_cryptLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Ouest:
		case Sortir:
		case Monter:
			setState(M_TRAPPE, MASK_CLOSED, false);
			changeLocation(M_CHURCH_INDOOR);
			return true;
		case Est:
			if (getState(M_DOOR, MASK_CLOSED)) {
				printMessage(_T0046, NULL, 0);
			} else {
				changeLocation(M_MIRROR_ROOM);
			}
			return true;
	}
	
	return false;
}

bool m_mirrorRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
			if (getState(M_DOOR, MASK_CLOSED)) {
				printMessage(_T0046, NULL, 0);
			} else {
				changeLocation(M_CRYPT);
			}
			return true;
		case Est:
			if (isMSecretRoomOpen()) {
				changeLocation(M_SECRET_ROOM);
				return true;
			}
			break;
		case Nord:
			return mirrorExecute(command);
	}
	
	return false;
}

bool m_churchIndoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
			changeLocation(M_CHURCH_OUTDOOR);
			return true;
		case Ouest:
		case Descendre:
			// return obj_m_trappeExecute(command);
			return obj_trappeExecute(command);
	}
	
	return false;
}

bool m_churchOutdoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
			changeLocation(M_FOREST);
			return true;
		case Ouest:
			changeLocation(M_CAVERN_OUTDOOR);
			return true;
		case Nord:
		case Aller: // entrer (TODO : séparer aller et entrer ?)
			changeLocation(M_CHURCH_INDOOR);
			return true;
	}
	
	return false;
}

bool m_forestLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			changeLocation(M_CHURCH_OUTDOOR);
			return true;
		case Monter:
			return obj_ladderExecute(command);
	}

	return false;
}

bool hutOutdoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
		case Monter:
		case Aller: // entrer
			return obj_hutExecute(command);
		case Descendre:
			printMessage(_T0051, NULL, 0);
			return true;
	}
	
	return false;
}

bool m_hutOutdoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
		case Monter:
		case Aller: // entrer
			return obj_m_hutExecute(command);
		case Descendre:
			changeLocation(M_FOREST);
			return true;
	}
	
	return false;
}

bool hutIndoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
		case Descendre:
			changeLocation(HUT_OUTDOOR);
			return true;
	}
	
	return false;
}

bool m_hutIndoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
		case Descendre:
			changeLocation(M_HUT_OUTDOOR);
			return true;
		case Parler:
			pnj_hermitExecute(command);
			return true;
	}
	
	return false;
}

bool cavernOutdoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Ouest:
				changeLocation(CHURCH_OUTDOOR);
				return true;
		case Nord:
		case Aller:
		case Monter:
		case Descendre:
			return obj_towerExecute(command);
	}

	return false;
}

bool m_cavernOutdoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Est:
				changeLocation(M_CHURCH_OUTDOOR);
				return true;
		case Nord:
		case Aller:
		case Descendre:
				return obj_m_towerExecute(command);
	}

	return false;
}

bool cavernIndoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
		case Monter:
			changeLocation(CAVERN_OUTDOOR);
			return true;
	}

	return false;
}

bool m_cavernIndoorLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
		case Monter:
			changeLocation(M_CAVERN_OUTDOOR);
			return true;
	}

	return false;
}
bool secretRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
			if (isSecretRoomOpen()) {
				changeLocation(MIRROR_ROOM);
				return true;
			}
			break;
	}
	return false;
}

bool m_secretRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
		case Sortir:
			if (isMSecretRoomOpen()) {
				changeLocation(M_MIRROR_ROOM);
				return true;
			}
			break;
	}
	return false;
}

// Simulation locations
bool nwRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
			changeLocation(W_ROOM);
			return true;
	}

	return false;
}

bool nRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
			changeLocation(CENTER_ROOM);
			return true;
		case Nord:
			if (!contains(N_ROOM, SIM_GUARD)) {

				// TODO: transition vers le début du mode parser dans le monde réel
				// objects[SIM_CLUB].containerId = NO_OBJECT;
				moveObjectTo(NO_OBJECT, SIM_CLUB);

				finEpreuve();
				// On enlève la clé de l'inventaire et on remet ce que le joueur avait avant le tuto
				// objects[SIM_KEY].containerId = NO_OBJECT;
				moveObjectTo(NO_OBJECT, SIM_KEY);
			} else {
				printMessage(_T0052, NULL, 0);
			}
			return true;
	}

	return false;
}

bool neRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Sud:
			if (!getState(SIM_DOOR,MASK_CLOSED)) {
				changeLocation(E_ROOM);
				return true;
			}
			break;
	}

	return false;
}

bool wRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			changeLocation(NW_ROOM);
			return true;
		case Sud:
			changeLocation(SW_ROOM);
			return true;
		case Est:
			changeLocation(CENTER_ROOM);
			return true;
	}
	return false;
}

bool centerRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			changeLocation(N_ROOM);
			return true;
		case Ouest:
			changeLocation(W_ROOM);
			return true;
	}

	return false;
}

bool eRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			if (!getState(SIM_DOOR,MASK_CLOSED)) {
				changeLocation(NE_ROOM);
				return true;
			}
			break;
		case Sud:
			changeLocation(SE_ROOM);
			return true;
	}

	return false;
}

bool swRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			changeLocation(W_ROOM);
			return true;
		case Est:
			changeLocation(S_ROOM);
			return true;
	}

	return false;
}

bool sRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Ouest:
			changeLocation(SW_ROOM);
			return true;
		case Est:
			changeLocation(SE_ROOM);
			return true;
	}

	return false;
}

bool seRoomLocationExecute(struct Command* command) {
	switch(command->verbId) {
		case Nord:
			changeLocation(E_ROOM);
			return true;
		case Ouest:
			changeLocation(S_ROOM);
			return true;
	}

	return false;
}

// Simulation objects
bool sim_clubExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Utiliser:
			complementId = findObjectIn(CONTEXT, command->complement);

			switch(complementId) {
				case SIM_GUARD:
					printMessage(_T0053, NULL, 0);
					objects[SIM_GUARD].containerId = NO_OBJECT;
					return true;
			}
			break;
	}

	return false;
}

bool sim_guardExecute(struct Command* command) {
	switch(command->verbId) {
		case Parler:
			printMessage(_T0054, NULL, 0);
			return true;
	}

	return false;
}

bool sim_keyExecute(struct Command* command) {
	unsigned char complementId;

	switch(command->verbId) {
		case Utiliser:
			if (strcmp(command->complement,"") != 0) {
                complementId = findObjectIn(CONTEXT, command->complement);

                switch(complementId) {
                    case SIM_CHEST:
                        setState(complementId, MASK_LOCKED, false);

                        printMessage(_T0055,  objects[complementId].displayName, 0);
                        return true;
                }
            } else {
				printMessage(_T0056, NULL, 0);
				return true;
			}
			break;
	}

	return false;
}

bool (*behave[OBJECT_COUNT])(struct Command* command) = {
	// Système
	NULL, // NO_OBJECT
	NULL, // CONTEXT

	// Protagoniste
	heroExecute, // HERO
	inventoryExecute, // INVENTORY

	// Personnages
	pnj_hermitExecute, // HERMIT
    NULL, // NAHASH
    pnj_godExecute, // GOD
	// Objets
	NULL, // FLUTE
	NULL, // M_FLUTE
	obj_stoveExecute, // STOVE
	obj_m_buttonExecute, // M_BUTTON
	obj_ivyExecute, // IVY
	obj_ladderExecute, // LADDER
    obj_towerExecute, // TOWER
    obj_m_towerExecute, // M_TOWER
    obj_hutExecute, // HUT
    obj_m_hutExecute, // M_HUT
	obj_basReliefExecute, // BASRELIEF
	obj_m_basReliefExecute, // M_BASRELIEF
	NULL, // BUSH
	NULL, // AMULET
	obj_berryExecute, // BERRY
	obj_trappeExecute, // TRAPPE
	obj_trappeExecute, // M_TRAPPE
	obj_buttonExecute, // BUTTON
	obj_bookExecute, // BOOK
	obj_mintExecute, // MINT
	obj_tibiaExecute, // TIBIA
	obj_flaskExecute, // FLASK
	obj_mushroomsExecute, // MUSHROOMS
	NULL, // BONES
	obj_saltExecute, // SALT
	obj_pepperExecute, // PEPPER
	obj_artefactExecute, // ARTEFACT
    obj_gongExecute, // GONG
    obj_cauldronExecute, // CAULDRON
    NULL, // M_CAULDRON
    obj_statuetteExecute, // STATUETTE
    obj_statuetteExecute, // M_STATUETTE
    obj_whistleExecute, // WHISTLE
    obj_partitionExecute, // PARTITION
    NULL, // DOOR
    NULL, // M_DOOR
	obj_churchExecute, // CHURCH
	obj_chestExecute, // CHEST
	obj_m_chestExecute, // M_CHEST
	obj_keyExecute, // KEY
	obj_firebrandExecute, // FIREBRAND
	mirrorExecute, // MIRROR
	mirrorExecute, // M_MIRROR

	// Simulation locations
    nwRoomLocationExecute, // NW_ROOM
    nRoomLocationExecute, // N_ROOM
    neRoomLocationExecute, // NE_ROOM
    wRoomLocationExecute, // W_ROOM
    centerRoomLocationExecute, // CENTER_ROOM
    eRoomLocationExecute, // E_ROOM
    swRoomLocationExecute, // SW_ROOM
    sRoomLocationExecute, // S_ROOM
    seRoomLocationExecute, // SE_ROOM

	// Simulation objects
	sim_clubExecute, // SIM_CLUB
    sim_guardExecute, // SIM_GUARD
    sim_chestExecute, // SIM_CHEST
    sim_keyExecute, // SIM_KEY
    NULL, // SIM_DOOR

	// Lieux
	NULL, // GOD_ROOM

	forestLocationExecute, // FOREST
	m_forestLocationExecute, // M_FOREST
	churchOutdoorLocationExecute, // CHURCH_OUTDOOR
	m_churchOutdoorLocationExecute, // M_CHURCH_OUTDOOR
	churchIndoorLocationExecute, // CHURCH_INDOOR
	m_churchIndoorLocationExecute, // M_CHURCH_INDOOR
	cryptLocationExecute, // CRYPT
	m_cryptLocationExecute, // M_CRYPT
	laboratoryLocationExecute, // LABORATORY
	NULL, // M_LABORATORY
	mirrorRoomLocationExecute, // MIRROR_ROOM
	m_mirrorRoomLocationExecute, // M_MIRROR_ROOM
	hutOutdoorLocationExecute, // HUT_OUTDOOR
	m_hutOutdoorLocationExecute, // M_HUT_OUTDOOR
	hutIndoorLocationExecute, // HUT_INDOOR
	m_hutIndoorLocationExecute, // M_HUT_INDOOR
	cavernOutdoorLocationExecute, // CAVERN_OUTDOOR
	m_cavernOutdoorLocationExecute, // M_CAVERN_OUTDOOR
	cavernIndoorLocationExecute, // CAVERN_INDOOR
	m_cavernIndoorLocationExecute, // M_CAVERN_INDOOR
	secretRoomLocationExecute, // SECRET_ROOM
	m_secretRoomLocationExecute // M_SECRET_ROOM
};

unsigned char getInversedLocationId(unsigned char locationId) {
	if (locationId == GOD_ROOM) return GOD_ROOM;

	return locationId + 1 + ((OBJECT_COUNT - locationId) % 2) * -2; 
}
