#include "database.h"

// On n'utilise pas la syntaxe .name = {""} dans l'initalisation des tableaux de structure
// car cette syntaxe n'est pas connue de certains compilateurs comme SDCC
struct Object objectDatabase[MAX_OBJECT_COUNT] = {
    // Système
    { // NO_OBJECT
        {"EMPTY"},
        "rien",
        NO_OBJECT,
        NO_OBJECT,
        "",
        0
    },
    { // CONTEXT
        {"CONTEXT"},
        "contexte",
        CONTEXT,
        NO_OBJECT,
        "",
        0
    },
    // Protagoniste
    { // HERO
        // Liste des mots pouvant désigner le joueur en tant qu'objet d'une commande (avant ou après le verbe)
        {"ME", "SE", "M", "SOI", "MOI"},
        "vous",
        HERO,
        CONTEXT,
        "C'est bien vous",
        0
    },
    { // INVENTORY
        {"SAC"},
        "votre sac",
        INVENTORY,
        CONTEXT,
        "Vos possessions:",
        0
    },
    // Personnages
    { // HERMIT
        {"MOINE", "HOMME", "POCHE", "HERMES"},
        "le moine",
        HERMIT,
        M_HUT_INDOOR,
        "Un vieux moine",
        0b00000000
    },
    { // NAHASH
        {"NAHASH", "ANGE"},
        "Nahash",
        NAHASH,
        NO_OBJECT,
        "Un ange passe",
        0
    },
    { // GOD
        {"CREATEUR","SPHERE","DIEU", "BOULE"},
        "le créateur",
        GOD,
        GOD_ROOM,
        "Le dieu créateur",
        0
    },
    // Objets
    { // FLUTE (BAS-RELIEF)
        {"FLUTE"},
        "la flute",
        FLUTE,
        BASRELIEF,
        "La flute et la musicienne sont sculptées d'un seul tenant",
        0
    },
    { // FLUTE (BAS-RELIEF)
        {"FLUTE"},
        "la flute",
        M_FLUTE,
        M_BASRELIEF,
        "La flute et la musicienne sont sculptées d'un seul tenant",
        0
    },
    { // STOVE
        {"POELE", "FOUR", "FEU"},
        "le poêle",
        STOVE,
        LABORATORY,
        "Un vieux poêle",
        0
    },
    { // M_BUTTON
        {"BOUTON", "LEVIER"},
        "le bouton",
        M_BUTTON,
        M_LABORATORY,
        "Un petit levier rouillé",
        0
    },
    { // IVY
        {"LIERRE"},
        "le lierre",
        IVY,
        CAVERN_OUTDOOR,
        "Le lierre monte jusqu'à une ouverture",
        0
    },
    { // LADDER
        {"ECHELLE"},
        "l'échelle",
        LADDER,
        M_FOREST,
        "L'échelle disparaît dans le feuillage   des arbres",
        0
    },
    { // TOWER
        {"TOUR","RUINE","CHATEAU"},
        "la tour",
        TOWER,
        CAVERN_OUTDOOR,
        "Une tour en ruine envahie par le lierre",
        0
    },
    { // M_TOWER
        {"TOUR","RUINE","CHATEAU"},
        "la tour",
        M_TOWER,
        M_CAVERN_OUTDOOR,
        "Une tour en ruine",
        0
    },
    { // HUT
        {"CABANE","MAISON","CHALET"},
        "la cabane",
        HUT,
        HUT_OUTDOOR,
        "Une cabane dans les arbres",
        0
    },
    { // M_HUT
        {"CABANE","MAISON","CHALET"},
        "la cabane",
        M_HUT,
        M_HUT_OUTDOOR,
        "Une cabane dans les arbres",
        0
    },
    { // BASRELIEF
        {"BAS-RELIEF", "BASRELIEF"},
        "le bas-relief",
        BASRELIEF,
        SECRET_ROOM,
        "Un bas-relief montrant une musicienne",
        0b00001000
    },
    { // M_BASRELIEF
        {"BAS-RELIEF", "BASRELIEF"},
        "le bas-relief",
        M_BASRELIEF,
        M_SECRET_ROOM,
        "Un bas-relief montrant une musicienne",
        0b00001000
    },
    { // BUSH
        {"BUISSON","PLANTE","ARBRE","BUISSONS"},
        "le buisson",
        BUSH,
        CAVERN_OUTDOOR,
        "Un buisson plein de baies",
        0b00001000
    },
    { // AMULET
        {"AMULETTE","BIJOU", "PENDANTIF", "TALISMAN"},
        "l'amulette",
        AMULET,
        HERMIT,
        "Un pendentif",
        4 // 0b00000100
    },
    { // BERRY
        {"BAIES","FRUITS","BAIE"},
        "les baies",
        BERRY,
        BUSH,
        "De baies rouges",
        4 // 0b00000100
    },
    { // TRAPPE
        {"TRAPPE","ESCALIER"},
        "la trappe",
        TRAPPE,
        CHURCH_INDOOR,
        "Une trappe",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_TRAPPE
        {"TRAPPE","ESCALIER"},
        "la trappe",
        M_TRAPPE,
        M_CHURCH_INDOOR,
        "Une trappe",
        0
    },
    { // BUTTON
        {"BOUTON", "LEVIER"},
        "le bouton",
        BUTTON,
        LABORATORY,
        "Un petit levier",
        1 // 0b00000001, MASK_CLOSED
    },
    { // BOOK
        {"LIVRE", "GRIMOIRE", "BOUQUIN"},
        "le grimoire",
        BOOK,
        LABORATORY,
        "Un vieux grimoire",
        4 // 0b00000100
    },
    { // MINT
        {"MENTHE", "MENTE"},
        "la menthe",
        MINT,
        HERMIT,
        "De la menthe",
        4 // 0b00000100
    },
    { // TIBIA
        {"TIBIA"},
        "le tibia",
        TIBIA,
        BONES,
        "Il ressemble à une cuillère",
        4 // 0b00000100
    },
    { // FLASK
        {"FIOLE", "FLASQUE", "POTION"},
        "la fiole",
        FLASK,
        BONES,
        "Une petite fiole",
        4 // 0b00000100
    },
    { // MUSHROOMS
        {"AMANITES", "AMANITE", "CHAMPIGNON"},
        "les amanites",
        MUSHROOMS,
        M_CAULDRON,
        "De petits champignons blancs",
        4 // 0b00000100
    },
    { // BONES
        {"SQUELETTE","OS","OSSEMENTS","CRANE"},
        "le squelette",
        BONES,
        MIRROR_ROOM,
        "Des ossements humains",
        0b00001000
    },
    { // SALT
        {"SEL", "SALIERE"},
        "le sel",
        SALT,
        BONES,
        "Du sel",
        4
    },
    { // PEPPER
        {"POIVRE"},
        "le poivre",
        PEPPER,
        BONES,
        "Du poivre",
        4
    },
    { // ARTEFACT
        {"SCEPTRE", "BATON", "SEPTRE", "FLUTE"},
        "le sceptre",
        ARTEFACT,
        CHEST,
        "Un bâton percé de trous avec une boule  au bout",
        0b00000100
    },
    { // GONG
        {"GONG","CYMBALE","DISQUE"},
        "le gong",
        GONG,
        M_CHURCH_INDOOR,
        "C'est un gong",
        0
    },
    { // CAULDRON
        {"CHAUDRON", "MARMITE", "SUBSTRAT","EAU"},
        "le chaudron",
        CAULDRON,
        LABORATORY,
        "Un petit chaudron",
        0
    },
    { // M_CAULDRON
        {"CHAUDRON", "MARMITE"},
        "le chaudron",
        M_CAULDRON,
        M_LABORATORY,
        "Un chaudron usé par le temps",
        0
    },
    { // STATUETTE
        {"STATUETTE","STATUE","TROU","SOCLE"},
        "la statuette",
        STATUETTE,
        CRYPT,
        "Une statue fixée à un socle percé\r\nd'un petit trou",
        128 // 0b10000000 // MASK_CUSTOM_STATE
    },
    { // M_STATUETTE
        {"STATUETTE","STATUE","TROU","SOCLE"},
        "la statuette",
        M_STATUETTE,
        M_CRYPT,
        "Une statue fixée à un socle percé d'un petit trou",
        0
    },
    { // WHISTLE
        {"SIFFLET"},
        "le sifflet",
        WHISTLE,
        BASRELIEF,
        "Un sifflet",
        4 // 0b00000100
    },
    { // PARTITION
        {"PARTITION", "PAPIER", "FEUILLE"},
        "la partition",
        PARTITION,
        M_BASRELIEF,
        "Une partition musicale",
        4 // 0b00000100
    },
    { // DOOR
        {"PORTE"},
        "la porte",
        DOOR,
        CRYPT,
        "Elle n'a ni serrure ni poignée",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_DOOR
        {"PORTE"},
        "la porte",
        M_DOOR,
        M_CRYPT,
        "Elle n'a ni serrure ni poignée",
        1 // 0b00000001, MASK_CLOSED
    },
    { // CHURCH
        {"CHAPELLE", "RUINE", "EGLISE"},
        "la chapelle",
        CHURCH,
        CHURCH_OUTDOOR,
        "Un bâtiment délabré",
        0
    },
    { // CHEST
        {"COFFRE", "BOITE"},
        "le coffre",
        CHEST,
        CAVERN_INDOOR,
        "Un coffre en bois",
        0b01001011
    },
    { // M_CHEST
        {"COFFRE", "BOITE"},
        "le coffre",
        M_CHEST,
        M_CAVERN_INDOOR,
        "Un coffre en bois",
        0b01001011
    },
    { // KEY
        {"CLEF", "CLE"},
        "la clef",
        KEY,
        HERMIT,
        "Une petite clef",
        4 // 0b00000100
    },
    { // FIREBRAND
        {"TISONNIER", "PIQUE"},
        "le tisonnier",
        FIREBRAND,
        M_CHEST,
        "Une fine barre de métal pointue",
        4 // 0b00000100
    },
    { // MIRROR
        {"MIROIR", "GLACE", "REFLET", "MIRROIR"},
        "le miroir",
        MIRROR,
        MIRROR_ROOM,
        "Un grand miroir",
        0
    },
    { // M_MIRROR
        {"MIROIR", "GLACE", "REFLET", "MIRROIR"},
        "le miroir",
        M_MIRROR,
        M_MIRROR_ROOM,
        "Un grand miroir",
        0
    },
    // Simulation locations
    { // NW_ROOM
        {"NW_ROOM"},
        "",
        NW_ROOM,
        NO_OBJECT,
        "Une salle avec un coffre à OUVRIR",
        0
    },
    { // N_ROOM
        {"N_ROOM"},
        "",
        N_ROOM,
        NO_OBJECT,
        "PARLER au garde",
        0
    },
    { // NE_ROOM
        {"NE_ROOM"},
        "",
        NE_ROOM,
        NO_OBJECT,
        "PRENDRE la clef semble être une bonne\r\nidée",
        0
    },
    { // W_ROOM
        {"W_ROOM"},
        "",
        W_ROOM,
        NO_OBJECT,
        "Pensez à consulter votre INVENTAIRE",
        0
    },
    { // CENTER_ROOM
        {"CENTER_R"},
        "",
        CENTER_ROOM,
        NO_OBJECT,
        "Une salle vide",
      //"aaaaaaaabbbbbbbbccccccccddddddddaaaaaaaabbbbbbbbccccccccdddddddd"
        0
    },
    { // E_ROOM
        {"E_ROOM"},
        "",
        E_ROOM,
        NO_OBJECT,
        "Vous pouvez OUVRIR la porte",
        0
    },
    { // SW_ROOM
        {"SW_ROOM"},
        "",
        SW_ROOM,
        NO_OBJECT,
        "Une salle vide",
        0
    },
    { // S_ROOM
        {"S_ROOM"},
        "",
        S_ROOM,
        NO_OBJECT,
        "Tapez NORD,SUD,EST ou OUEST pour vous\r\ndéplacer",
        0
    },
    { // SE_ROOM
        {"SE_ROOM"},
        "",
        SE_ROOM,
        NO_OBJECT,
        "Une salle vide",
        0
    },
    // Simulation objects
    { // SIM_CLUB
        {"MASSUE", "MASSE"},
        "la massue",
        SIM_CLUB,
        SIM_CHEST,
        "Une arme pesante",
        4
    },
    { // SIM_GUARD
        {"GARDE", "SOLDAT", "HOMME"},
        "le garde",
        SIM_GUARD,
        N_ROOM,
        "Il n'a pas l'air commode",
        0
    },
    { // SIM_CHEST
        {"COFFRE","BOITE","MALLE"},
        "le coffre",
        SIM_CHEST,
        NW_ROOM,
        "Un gros coffre",
        0b01001011
    },
    { // SIM_KEY
        {"CLE", "CLEF"},
        "la clef",
        SIM_KEY,
        NE_ROOM,
        "Une clé à UTILISER sur un COFFRE",
        4 // 0b00000100
    },
    { // SIM_DOOR
        {"PORTE"},
        "la porte",
        SIM_DOOR,
        E_ROOM,
        "Une porte",
        0b01000001
    },
    // Lieux
    { // GOD_ROOM
        {"GODROOM"},
        "",
        GOD_ROOM,
        NO_OBJECT,
        "Une grande sphère flotte au milieu d'un étrange paysage",
        0
    },
    { // FOREST
        {"FORET"},
        "",
        FOREST,
        NO_OBJECT,
        "Des arbres,encore des arbres",
        0
    },
    { // M_FOREST
        {"MFORET"},
        "",
        M_FOREST,
        NO_OBJECT,
        "Des arbres,encore des arbres.Et une   échelle!",
        0
    },
    { // CHURCH_OUTDOOR
        {"EXT"},
        "",
        CHURCH_OUTDOOR,
        NO_OBJECT,
        "Une clairière.En haut d'une colline,  une chapelle abandonnée",
        0
    },
    { // M_CHURCH_OUTDOOR
        {"MEXT"},
        "",
        M_CHURCH_OUTDOOR,
        NO_OBJECT,
        "Une clairière.En haut d'une colline,  une chapelle abandonnée",
        0
    },
    { // CHURCH_INDOOR
        {"INT"},
        "",
        CHURCH_INDOOR,
        NO_OBJECT,
        "La lumière bleutée des vitraux révèle\r\nune trappe au sol",
        0
    },
    { // M_CHURCH_INDOOR
        {"MINT"},
        "",
        M_CHURCH_INDOOR,
        NO_OBJECT,
        "Un gong imposant se dresse au milieu de la pièce",
        0
    },
    { // CRYPT
        {"CRYPTE"},
        "",
        CRYPT,
        NO_OBJECT,
        "La crypte.Une petite statuette occupe\r\nune niche dans le mur",
        0
    },
    { // M_CRYPT
        {"MCRYPT"},
        "",
        M_CRYPT,
        NO_OBJECT,
        "La crypte.Une petite statuette occupe\r\nune niche dans le mur",
        0
    },
    { // LABORATORY
        {"LABO"},
        "",
        LABORATORY,
        NO_OBJECT,
        "Sur le poêle,un chaudron rempli d'eau",
        0
    },
    { // M_LABORATORY
        {"MLABO"},
        "",
        M_LABORATORY,
        NO_OBJECT,
        "Odeur de rouille et d'humidité",
        0
    },
    { // MIRROR_ROOM
        {"SALLE"},
        "",
        MIRROR_ROOM,
        NO_OBJECT,
        "la salle du miroir.\r\nUn squelette gît sur le sol",
        0
    },
    { // M_MIRROR_ROOM
        {"MSALLE"},
        "",
        M_MIRROR_ROOM,
        NO_OBJECT,
        "De l'autre coté du miroir",
        0
    },
    { // HUT_OUTDOOR
        {"EXTCAB"},
        "",
        HUT_OUTDOOR,
        NO_OBJECT,
        "Quiétude absolue",
        0
    },
    { // M_HUT_OUTDOOR
        {"MEXTCAB"},
        "",
        M_HUT_OUTDOOR,
        NO_OBJECT,
        "Une cabane à la cime des arbres",
        0
    },
    { // HUT_INDOOR
        {"INTCAB"},
        "",
        HUT_INDOOR,
        NO_OBJECT,
        "Enfin seul!",
        0
    },
    { // M_HUT_INDOOR
        {"MINTCAB"},
        "",
        M_HUT_INDOOR,
        NO_OBJECT,
        "Un vieux moine se repose sur un fauteuil",
        0
    },
    { // CAVERN_OUTDOOR
        {"EXTCAVE"},
        "",
        CAVERN_OUTDOOR,
        NO_OBJECT,
        "Une tour en ruine envahie par la végéta-tion",
        0
    },
    { // M_CAVERN_OUTDOOR
        {"MEXTCAVE"},
        "",
        M_CAVERN_OUTDOOR,
        NO_OBJECT,
        "Les vestiges d'une gloire passée",
        0
    },
    { // CAVERN_INDOOR
        {"INTCAVE"},
        "",
        CAVERN_INDOOR,
        NO_OBJECT,
        "Un grand coffre occupe une bonne partie de la cave",
        0
    },
    { // M_CAVERN_INDOOR
        {"MINTCAVE"},
        "",
        M_CAVERN_INDOOR,
        NO_OBJECT,
        "Un grand coffre occupe une bonne partie de la cave",
        0
    },
    { // SECRET_ROOM
        {"SECRETR"},
        "",
        SECRET_ROOM,
        NO_OBJECT,
        "Une salle dorée.Un mur est occupé par  un bas-relief",
        0
    },
    { // M_SECRET_ROOM
        {"MSECRETR"},
        "",
        M_SECRET_ROOM,
        NO_OBJECT,
        "Une salle dorée.Un mur est occupé par  un bas-relief",
        0
    }
};
