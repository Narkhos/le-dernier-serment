#include "database.h"

// On n'utilise pas la syntaxe .name = {""} dans l'initalisation des tableaux de structure
// car cette syntaxe n'est pas connue de certains compilateurs comme SDCC
struct Object objectDatabase[MAX_OBJECT_COUNT] = {
    // Système
    { // NO_OBJECT
        {"EMPTY"},
        "nada",
        NO_OBJECT,
        NO_OBJECT,
        "",
        0
    },
    { // CONTEXT
        {"CONTEXT"},
        "contexto",
        CONTEXT,
        NO_OBJECT,
        "",
        0
    },
    // Protagoniste
    { // HERO
        // Liste des mots pouvant désigner le joueur en tant qu'objet d'une commande (avant ou après le verbe)
        {"ME", "SE", "M", "SOI", "MOI"},
        "tú",
        HERO,
        CONTEXT,
        "Eres tú",
        0
    },
    { // INVENTORY
        {"SAC"},
        "tu bolsa",
        INVENTORY,
        CONTEXT,
        "Tienes:",
        0
    },
    // Personnages
    { // HERMIT
        {"MOINE", "HOMME", "POCHE", "HERMES"},
        "el monje",
        HERMIT,
        M_HUT_INDOOR,
        "Un anciano monje",
        0b00000000
    },
    { // NAHASH
        {"NAHASH", "ANGE"},
        "Nahash",
        NAHASH,
        NO_OBJECT,
        "Un ángel pasa",
        0
    },
    { // GOD
        {"CREATEUR","SPHERE","DIEU", "BOULE"},
        "le creador",
        GOD,
        GOD_ROOM,
        "El dios creador",
        0
    },
    // Objets
    { // FLUTE (BAS-RELIEF)
        {"FLUTE"},
        "la flauta",
        FLUTE,
        BASRELIEF,
        "La flauta y el músico están esculpidos de una sola pieza",
        0
    },
    { // FLUTE (BAS-RELIEF)
        {"FLUTE"},
        "la flauta",
        M_FLUTE,
        M_BASRELIEF,
        "La flauta y el músico están esculpidos de una sola pieza",
        0
    },
    { // STOVE
        {"POELE", "FOUR", "FEU"},
        "la cocina",
        STOVE,
        LABORATORY,
        "Una vieja cocina",
        0
    },
    { // M_BUTTON
        {"BOUTON", "LEVIER"},
        "la palanca",
        M_BUTTON,
        M_LABORATORY,
        "Una pequeña palanca oxidada",
        0
    },
    { // IVY
        {"LIERRE"},
        "la hiedra",
        IVY,
        CAVERN_OUTDOOR,
        "La hiedra trepa hasta una abertura",
        0
    },
    { // LADDER
        {"ECHELLE"},
        "la escala",
        LADDER,
        M_FOREST,
        "La escala desaparece entre el follaje de los árboles",
        0
    },
    { // TOWER
        {"TOUR","RUINE","CHATEAU"},
        "la torre",
        TOWER,
        CAVERN_OUTDOOR,
        "Una torre en ruinas invadida por la hiedra",
        0
    },
    { // M_TOWER
        {"TOUR","RUINE","CHATEAU"},
        "la torre",
        M_TOWER,
        M_CAVERN_OUTDOOR,
        "Una torre en ruinas",
        0
    },
    { // HUT
        {"CABANE","MAISON","CHALET"},
        "la cabaña",
        HUT,
        HUT_OUTDOOR,
        "Una cabaña es los árboles",
        0
    },
    { // M_HUT
        {"CABANE","MAISON","CHALET"},
        "la cabaña",
        M_HUT,
        M_HUT_OUTDOOR,
        "Una cabaña es los árboles",
        0
    },
    { // BASRELIEF
        {"BAS-RELIEF", "BASRELIEF"},
        "le bas-relief",
        BASRELIEF,
        SECRET_ROOM,
        "Un bajorrelieve que muestra un músico",
        0b00001000
    },
    { // M_BASRELIEF
        {"BAS-RELIEF", "BASRELIEF"},
        "el bajorrelieve",
        M_BASRELIEF,
        M_SECRET_ROOM,
        "Un bajorrelieve que muestra un músico",
        0b00001000
    },
    { // BUSH
        {"BUISSON","PLANTE","ARBRE","BUISSONS"},
        "el arbusto",
        BUSH,
        CAVERN_OUTDOOR,
        "Un arbusto repleto de bayas",
        0b00001000
    },
    { // AMULET
        {"AMULETTE","BIJOU", "PENDANTIF", "TALISMAN"},
        "el amuleto",
        AMULET,
        HERMIT,
        "Un colgante",
        4 // 0b00000100
    },
    { // BERRY
        {"BAIES","FRUITS","BAIE"},
        "las bayas",
        BERRY,
        BUSH,
        "De bayas rojas",
        4 // 0b00000100
    },
    { // TRAPPE
        {"TRAPPE","ESCALIER"},
        "la trampilla",
        TRAPPE,
        CHURCH_INDOOR,
        "Una trampilla",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_TRAPPE
        {"TRAPPE","ESCALIER"},
        "la trampilla",
        M_TRAPPE,
        M_CHURCH_INDOOR,
        "Una trampilla",
        0
    },
    { // BUTTON
        {"BOUTON", "LEVIER"},
        "el botón",
        BUTTON,
        LABORATORY,
        "Una pequeña palanca",
        1 // 0b00000001, MASK_CLOSED
    },
    { // BOOK
        {"LIVRE", "GRIMOIRE", "BOUQUIN"},
        "el grimorio",
        BOOK,
        LABORATORY,
        "Un vetusto grimorio",
        4 // 0b00000100
    },
    { // MINT
        {"MENTHE", "MENTE"},
        "la menta",
        MINT,
        HERMIT,
        "De la menta",
        4 // 0b00000100
    },
    { // TIBIA
        {"TIBIA"},
        "le tibia",
        TIBIA,
        BONES,
        "Parace una cuchara",
        4 // 0b00000100
    },
    { // FLASK
        {"FIOLE", "FLASQUE", "POTION"},
        "un matraza",
        FLASK,
        BONES,
        "Un pequeño matraz",
        4 // 0b00000100
    },
    { // MUSHROOMS
        {"AMANITES", "AMANITE", "CHAMPIGNON"},
        "las amanitas",
        MUSHROOMS,
        M_CAULDRON,
        "De pequeños champiñones blancos",
        4 // 0b00000100
    },
    { // BONES
        {"SQUELETTE","OS","OSSEMENTS","CRANE"},
        "el esqueleto",
        BONES,
        MIRROR_ROOM,
        "De huesos humanos",
        0b00001000
    },
    { // SALT
        {"SEL", "SALIERE"},
        "la sal",
        SALT,
        BONES,
        "De sal",
        4
    },
    { // PEPPER
        {"POIVRE"},
        "la pimienta",
        PEPPER,
        BONES,
        "De pimienta",
        4
    },
    { // ARTEFACT
        {"SCEPTRE", "BATON", "SEPTRE", "FLUTE"},
        "el cetro",
        ARTEFACT,
        CHEST,
        "Un bastón lleno de agujeros y una esfera en un extremo",
        0b00000100
    },
    { // GONG
        {"GONG","CYMBALE","DISQUE"},
        "el gong",
        GONG,
        M_CHURCH_INDOOR,
        "Es un gong",
        0
    },
    { // CAULDRON
        {"CHAUDRON", "MARMITE", "SUBSTRAT","EAU"},
        "el caldero",
        CAULDRON,
        LABORATORY,
        "Un pequeño caldero",
        0
    },
    { // M_CAULDRON
        {"CHAUDRON", "MARMITE"},
        "el caldero",
        M_CAULDRON,
        M_LABORATORY,
        "Un caldero ajado por el uso",
        0
    },
    { // STATUETTE
        {"STATUETTE","STATUE","TROU","SOCLE"},
        "la estatua",
        STATUETTE,
        CRYPT,
        "Una estatua unida a una base perforada con un pequeño orificio",
        128 // 0b10000000 // MASK_CUSTOM_STATE
    },
    { // M_STATUETTE
        {"STATUETTE","STATUE","TROU","SOCLE"},
        "la estatua",
        M_STATUETTE,
        M_CRYPT,
        "Una estatua unida a una base perforada con un pequeño orificio",
        0
    },
    { // WHISTLE
        {"SIFFLET"},
        "el silbato",
        WHISTLE,
        BASRELIEF,
        "Un silbato",
        4 // 0b00000100
    },
    { // PARTITION
        {"PARTITION", "PAPIER", "FEUILLE"},
        "la partitura",
        PARTITION,
        M_BASRELIEF,
        "Una partitura musical",
        4 // 0b00000100
    },
    { // DOOR
        {"PORTE"},
        "la puerta",
        DOOR,
        CRYPT,
        "No tiene cerradura ni manilla",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_DOOR
        {"PORTE"},
        "la puerta",
        M_DOOR,
        M_CRYPT,
        "No tiene cerradura ni manilla",
        1 // 0b00000001, MASK_CLOSED
    },
    { // CHURCH
        {"CHAPELLE", "RUINE", "EGLISE"},
        "la capilla",
        CHURCH,
        CHURCH_OUTDOOR,
        "Un edificio en ruinas",
        0
    },
    { // CHEST
        {"COFFRE", "BOITE"},
        "el cofre",
        CHEST,
        CAVERN_INDOOR,
        "Un cofre de madera",
        0b01001011
    },
    { // M_CHEST
        {"COFFRE", "BOITE"},
        "el cofre",
        M_CHEST,
        M_CAVERN_INDOOR,
        "Un cofre de madera",
        0b01001011
    },
    { // KEY
        {"CLEF", "CLE"},
        "la llave",
        KEY,
        HERMIT,
        "Una pequeña llave",
        4 // 0b00000100
    },
    { // FIREBRAND
        {"TISONNIER", "PIQUE"},
        "el atizador",
        FIREBRAND,
        M_CHEST,
        "Una delgada barra metállica puntiaguda",
        4 // 0b00000100
    },
    { // MIRROR
        {"MIROIR", "GLACE", "REFLET", "MIRROIR"},
        "el espejo",
        MIRROR,
        MIRROR_ROOM,
        "Un gran espejo",
        0
    },
    { // M_MIRROR
        {"MIROIR", "GLACE", "REFLET", "MIRROIR"},
        "el espejo",
        M_MIRROR,
        M_MIRROR_ROOM,
        "Un gran espejo",
        0
    },
    // Simulation locations
    { // NW_ROOM
        {"NW_ROOM"},
        "",
        NW_ROOM,
        NO_OBJECT,
        "Una habitación con un cofre para ABRIR",
        0
    },
    { // N_ROOM
        {"N_ROOM"},
        "",
        N_ROOM,
        NO_OBJECT,
        "HABLAR al guardián",
        0
    },
    { // NE_ROOM
        {"NE_ROOM"},
        "",
        NE_ROOM,
        NO_OBJECT,
        "COGER la llave parece buena idea",
        0
    },
    { // W_ROOM
        {"W_ROOM"},
        "",
        W_ROOM,
        NO_OBJECT,
        "Recuerda echar un ojo a tu INVENTARIO",
        0
    },
    { // CENTER_ROOM
        {"CENTER_R"},
        "",
        CENTER_ROOM,
        NO_OBJECT,
        "Una habitación vacía",
      //"aaaaaaaabbbbbbbbccccccccddddddddaaaaaaaabbbbbbbbccccccccdddddddd"
        0
    },
    { // E_ROOM
        {"E_ROOM"},
        "",
        E_ROOM,
        NO_OBJECT,
        "Puedes ABRIR la puerta",
        0
    },
    { // SW_ROOM
        {"SW_ROOM"},
        "",
        SW_ROOM,
        NO_OBJECT,
        "Una habitación vacía",
        0
    },
    { // S_ROOM
        {"S_ROOM"},
        "",
        S_ROOM,
        NO_OBJECT,
        "Teclea NORTE,SUR,ESTE u OESTE para desplazarte",
        0
    },
    { // SE_ROOM
        {"SE_ROOM"},
        "",
        SE_ROOM,
        NO_OBJECT,
        "Una habitación vacía",
        0
    },
    // Simulation objects
    { // SIM_CLUB
        {"MASSUE", "MASSE"},
        "la maza",
        SIM_CLUB,
        SIM_CHEST,
        "Un arma pesada",
        4
    },
    { // SIM_GUARD
        {"GARDE", "SOLDAT", "HOMME"},
        "el guardián",
        SIM_GUARD,
        N_ROOM,
        "No parece cómodo",
        0
    },
    { // SIM_CHEST
        {"COFFRE","BOITE","MALLE"},
        "el cofre",
        SIM_CHEST,
        NW_ROOM,
        "Un gran cofre",
        0b01001011
    },
    { // SIM_KEY
        {"CLE", "CLEF"},
        "la llave",
        SIM_KEY,
        NE_ROOM,
        "Una llave para UTILIZAR en un COFRE",
        4 // 0b00000100
    },
    { // SIM_DOOR
        {"PORTE"},
        "la puerta",
        SIM_DOOR,
        E_ROOM,
        "Una puerta",
        0b01000001
    },
    // Lieux
    { // GOD_ROOM
        {"GODROOM"},
        "",
        GOD_ROOM,
        NO_OBJECT,
        "Una gran esfera flota en medio de un extraño paisaje",
        0
    },
    { // FOREST
        {"FORET"},
        "",
        FOREST,
        NO_OBJECT,
        "Árboles y más árboles",
        0
    },
    { // M_FOREST
        {"MFORET"},
        "",
        M_FOREST,
        NO_OBJECT,
        "Árboles y más árboles. Y una  escalera!",
        0
    },
    { // CHURCH_OUTDOOR
        {"EXT"},
        "",
        CHURCH_OUTDOOR,
        NO_OBJECT,
        "Un claro. En lo alto de una colina, una capilla abandonada",
        0
    },
    { // M_CHURCH_OUTDOOR
        {"MEXT"},
        "",
        M_CHURCH_OUTDOOR,
        NO_OBJECT,
        "Un claro. En lo alto de una colina, una capilla abandonada",
        0
    },
    { // CHURCH_INDOOR
        {"INT"},
        "",
        CHURCH_INDOOR,
        NO_OBJECT,
        "La luz azul de las vidrieras revela una trampilla en el suelo",
        0
    },
    { // M_CHURCH_INDOOR
        {"MINT"},
        "",
        M_CHURCH_INDOOR,
        NO_OBJECT,
        "Un gong imponente se yergue en el centro de la habitación",
        0
    },
    { // CRYPT
        {"CRYPTE"},
        "",
        CRYPT,
        NO_OBJECT,
        "La cripta. Una pequeña estatua ocupa un nicho en el muro",
        0
    },
    { // M_CRYPT
        {"MCRYPT"},
        "",
        M_CRYPT,
        NO_OBJECT,
        "La cripta. Una pequeña estatua ocupa un nicho en el muro",
        0
    },
    { // LABORATORY
        {"LABO"},
        "",
        LABORATORY,
        NO_OBJECT,
        "Sobre la cocina, un caldero lleno de agua",
        0
    },
    { // M_LABORATORY
        {"MLABO"},
        "",
        M_LABORATORY,
        NO_OBJECT,
        "Olor a óxido y humedad",
        0
    },
    { // MIRROR_ROOM
        {"SALLE"},
        "",
        MIRROR_ROOM,
        NO_OBJECT,
        "La sala del espejo.\r\nUn esqueleto yace en el suelo",
        0
    },
    { // M_MIRROR_ROOM
        {"MSALLE"},
        "",
        M_MIRROR_ROOM,
        NO_OBJECT,
        "Al otro lado del espejo",
        0
    },
    { // HUT_OUTDOOR
        {"EXTCAB"},
        "",
        HUT_OUTDOOR,
        NO_OBJECT,
        "Quietud absoluta",
        0
    },
    { // M_HUT_OUTDOOR
        {"MEXTCAB"},
        "",
        M_HUT_OUTDOOR,
        NO_OBJECT,
        "Una cabaña en la copa de los árboles",
        0
    },
    { // HUT_INDOOR
        {"INTCAB"},
        "",
        HUT_INDOOR,
        NO_OBJECT,
        "¡Por fin solo!",
        0
    },
    { // M_HUT_INDOOR
        {"MINTCAB"},
        "",
        M_HUT_INDOOR,
        NO_OBJECT,
        "Un anciano monje descansa en un sillón",
        0
    },
    { // CAVERN_OUTDOOR
        {"EXTCAVE"},
        "",
        CAVERN_OUTDOOR,
        NO_OBJECT,
        "Una torre en ruinas invadida por la vegetación",
        0
    },
    { // M_CAVERN_OUTDOOR
        {"MEXTCAVE"},
        "",
        M_CAVERN_OUTDOOR,
        NO_OBJECT,
        "Los vestigios de una gloria pasada",
        0
    },
    { // CAVERN_INDOOR
        {"INTCAVE"},
        "",
        CAVERN_INDOOR,
        NO_OBJECT,
        "Un gran cofre ocupa una buena parte de la cueva",
        0
    },
    { // M_CAVERN_INDOOR
        {"MINTCAVE"},
        "",
        M_CAVERN_INDOOR,
        NO_OBJECT,
        "Un gran cofre ocupa una buena parte de la cueva",
        0
    },
    { // SECRET_ROOM
        {"SECRETR"},
        "",
        SECRET_ROOM,
        NO_OBJECT,
        "Una habitación dorada. Un muro está cubierta por un bajorrelieve",
        0
    },
    { // M_SECRET_ROOM
        {"MSECRETR"},
        "",
        M_SECRET_ROOM,
        NO_OBJECT,
        "Una habitación dorada. Un muro está cubierta por un bajorrelieve",
        0
    }
};
