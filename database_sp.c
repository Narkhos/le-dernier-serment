#include "database.h"

// On n'utilise pas la syntaxe .name = {""} dans l'initalisation des tableaux de structure
// car cette syntaxe n'est pas connue de certains compilateurs comme SDCC
struct Object objectDatabase[MAX_OBJECT_COUNT] = {
    // Système
    { // NO_OBJECT
        {"NADA"},
        "nada",
        NO_OBJECT,
        NO_OBJECT,
        "",
        0
    },
    { // CONTEXT
        {"CONTEXTO"},
        "contexto",
        CONTEXT,
        NO_OBJECT,
        "",
        0
    },
    // Protagoniste
    { // HERO
        // Liste des mots pouvant désigner le joueur en tant qu'objet d'une commande (avant ou après le verbe)
        {"ME","SE","TE","MI","YO"},
        "tú",
        HERO,
        CONTEXT,
        "Eres tú",
        0
    },
    { // INVENTORY
        {"BOLSA","MOCHILA"},
        "tu bolsa",
        INVENTORY,
        CONTEXT,
        "Tienes:",
        0
    },
    // Personnages
    { // HERMIT
        {"MONJE","HOMBRE","FRAILE","HERMES"},
        "el monje",
        HERMIT,
        M_HUT_INDOOR,
        "Un anciano monje",
        0b00000000
    },
    { // NAHASH
        {"NAHASH","ANGEL"},
        "Nahash",
        NAHASH,
        NO_OBJECT,
        "Un ángel pasa",
        0
    },
    { // GOD
        {"CREADOR","ESFERA","DIOS","BOLA"},
        "el creador",
        GOD,
        GOD_ROOM,
        "El dios creador",
        0
    },
    // Objets
    { // FLUTE (BAS-RELIEF)
        {"FLAUTA"},
        "la flauta",
        FLUTE,
        BASRELIEF,
        "La flauta y el músico están esculpidos  de una sola pieza",
        0
    },
    { // FLUTE (BAS-RELIEF)
        {"FLAUTA"},
        "la flauta",
        M_FLUTE,
        M_BASRELIEF,
        "La flauta y el músico están esculpidos  de una sola pieza",
        0
    },
    { // STOVE
        {"COCINA","HORNO","FUEGO"},
        "la cocina",
        STOVE,
        LABORATORY,
        "Una vieja cocina",
        0
    },
    { // M_BUTTON
        {"MANDO","PALANCA"},
        "la palanca",
        M_BUTTON,
        M_LABORATORY,
        "Una pequeña palanca oxidada",
        0
    },
    { // IVY
        {"HIEDRA","ENREDADERA"},
        "la hiedra",
        IVY,
        CAVERN_OUTDOOR,
        "La hiedra trepa hasta una abertura",
        0
    },
    { // LADDER
        {"ESCALERA"},
        "la escalera",
        LADDER,
        M_FOREST,
        "La escalera desaparece entre el follaje de los árboles",
        0
    },
    { // TOWER
        {"TORRE","RUINAS","CASTILLO"},
        "la torre",
        TOWER,
        CAVERN_OUTDOOR,
        "Una torre en ruinas invadida por la     hiedra",
        0
    },
    { // M_TOWER
        {"TORRE","RUINAS","CASTILLO"},
        "la torre",
        M_TOWER,
        M_CAVERN_OUTDOOR,
        "Una torre en ruinas",
        0
    },
    { // HUT
        {"CHOZA","CASITA","CASA"},
        "la casita",
        HUT,
        HUT_OUTDOOR,
        "Una casita en los árboles",
        0
    },
    { // M_HUT
        {"CHOZA","CASITA","CASA"},
        "la casita",
        M_HUT,
        M_HUT_OUTDOOR,
        "Una casita en los árboles",
        0
    },
    { // BASRELIEF
        {"GRABADO"},
        "el grabado",
        BASRELIEF,
        SECRET_ROOM,
        "Un bajorrelieve que muestra un músico",
        0b00001000
    },
    { // M_BASRELIEF
        {"GRABADO"},
        "el grabado",
        M_BASRELIEF,
        M_SECRET_ROOM,
        "Un bajorrelieve que muestra un músico",
        0b00001000
    },
    { // BUSH
        {"ARBUSTO","PLANTA","ARBOL","ARBUSTOS"},
        "el arbusto",
        BUSH,
        CAVERN_OUTDOOR,
        "Un arbusto repleto de bayas",
        0b00001000
    },
    { // AMULET
        {"AMULETO","JOYA","COLGANTE","TALISMAN"},
        "el amuleto",
        AMULET,
        HERMIT,
        "Un colgante",
        4 // 0b00000100
    },
    { // BERRY
        {"BAYAS","FRUTOS","FRUTAS","BAYA"},
        "las bayas",
        BERRY,
        BUSH,
        "Unas bayas rojas",
        4 // 0b00000100
    },
    { // TRAPPE
        {"TRAMPILLA","ESCALERA","ESCALERAS"},
        "la trampilla",
        TRAPPE,
        CHURCH_INDOOR,
        "Una trampilla",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_TRAPPE
        {"TRAMPILLA","ESCALERA","ESCALERAS"},
        "la trampilla",
        M_TRAPPE,
        M_CHURCH_INDOOR,
        "Una trampilla",
        0
    },
    { // BUTTON
        {"MANDO","PALANCA"},
        "el mando",
        BUTTON,
        LABORATORY,
        "Una pequeña palanca",
        1 // 0b00000001, MASK_CLOSED
    },
    { // BOOK
        {"LIBRO","GRIMORIO"},
        "el grimorio",
        BOOK,
        LABORATORY,
        "Un vetusto grimorio",
        4 // 0b00000100
    },
    { // MINT
        {"MENTA"},
        "la menta",
        MINT,
        HERMIT,
        "Hojas de menta",
        4 // 0b00000100
    },
    { // TIBIA
        {"TIBIA"},
        "la tibia",
        TIBIA,
        BONES,
        "Parece una cuchara",
        4 // 0b00000100
    },
    { // FLASK
        {"MATRAZ","PROBETA","POCION","POCIMA"},
        "el matraz",
        FLASK,
        BONES,
        "Un pequeño matraz",
        4 // 0b00000100
    },
    { // MUSHROOMS
        {"AMANITAS","AMANITA","SETAS","SETA"},
        "las amanitas",
        MUSHROOMS,
        M_CAULDRON,
        "Pequeñas setas blancas",
        4 // 0b00000100
    },
    { // BONES
        {"ESQUELETO","HUESOS","CALAVERA"},
        "el esqueleto",
        BONES,
        MIRROR_ROOM,
        "Huesos humanos",
        0b00001000
    },
    { // SALT
        {"SAL","SALERO"},
        "la sal",
        SALT,
        BONES,
        "Un puñado de sal",
        4
    },
    { // PEPPER
        {"PIMIENTA"},
        "la pimienta",
        PEPPER,
        BONES,
        "Un puñado de pimienta",
        4
    },
    { // ARTEFACT
        {"CETRO","BASTON","FLAUTA"},
        "el cetro",
        ARTEFACT,
        CHEST,
        "Un bastón lleno de agujeros y una esferaen un extremo",
        0b00000100
    },
    { // GONG
        {"GONG","DISCO"},
        "el gong",
        GONG,
        M_CHURCH_INDOOR,
        "Es un gong",
        0
    },
    { // CAULDRON
        {"CALDERO","POCIMA","OLLA","AGUA"},
        "el caldero",
        CAULDRON,
        LABORATORY,
        "Un pequeño caldero",
        0
    },
    { // M_CAULDRON
        {"CALDERO","POCIMA","OLLA","AGUA"},
        "el caldero",
        M_CAULDRON,
        M_LABORATORY,
        "Un caldero ajado por el uso",
        0
    },
    { // STATUETTE
        {"ESTATUILLA","ESTATUA","ORIFICIO","PEDESTAL"},
        "la estatuilla",
        STATUETTE,
        CRYPT,
        "Una estatua alada sobre un pedestal con un pequeño orificio",
        128 // 0b10000000 // MASK_CUSTOM_STATE
    },
    { // M_STATUETTE
        {"ESTATUILLA","ESTATUA","ORIFICIO","PEDESTAL"},
        "la estatuilla",
        M_STATUETTE,
        M_CRYPT,
        "Una estatua alada sobre un pedestal con un pequeño orificio",
        0
    },
    { // WHISTLE
        {"SILBATO","PITO"},
        "el silbato",
        WHISTLE,
        BASRELIEF,
        "Un silbato",
        4 // 0b00000100
    },
    { // PARTITION
        {"PARTITURA","PAPEL"},
        "la partitura",
        PARTITION,
        M_BASRELIEF,
        "Una partitura musical",
        4 // 0b00000100
    },
    { // DOOR
        {"PUERTA"},
        "la puerta",
        DOOR,
        CRYPT,
        "No tiene cerradura ni manilla",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_DOOR
        {"PUERTA"},
        "la puerta",
        M_DOOR,
        M_CRYPT,
        "No tiene cerradura ni manilla",
        1 // 0b00000001, MASK_CLOSED
    },
    { // CHURCH
        {"CAPILLA","RUINAS","IGLESIA"},
        "la capilla",
        CHURCH,
        CHURCH_OUTDOOR,
        "Un edificio en ruinas",
        0
    },
    { // CHEST
        {"COFRE","CAJA"},
        "el cofre",
        CHEST,
        CAVERN_INDOOR,
        "Un cofre de madera",
        0b01001011
    },
    { // M_CHEST
        {"COFRE","CAJA"},
        "el cofre",
        M_CHEST,
        M_CAVERN_INDOOR,
        "Un cofre de madera",
        0b01001011
    },
    { // KEY
        {"LLAVE"},
        "la llave",
        KEY,
        HERMIT,
        "Una pequeña llave",
        4 // 0b00000100
    },
    { // FIREBRAND
        {"ATIZADOR","BARRA"},
        "el atizador",
        FIREBRAND,
        M_CHEST,
        "Una delgada barra metálica puntiaguda",
        4 // 0b00000100
    },
    { // MIRROR
        {"ESPEJO","REFLEJO"},
        "el espejo",
        MIRROR,
        MIRROR_ROOM,
        "Un espejo grande",
        0
    },
    { // M_MIRROR
        {"ESPEJO","REFLEJO"},
        "el espejo",
        M_MIRROR,
        M_MIRROR_ROOM,
        "Un espejo grande",
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
        "HABLA con el guardián",
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
        "Teclea NORTE,SUR,ESTE u OESTE para    desplazarte",
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
        {"MAZA","ARMA"},
        "la maza",
        SIM_CLUB,
        SIM_CHEST,
        "Un arma pesada",
        4
    },
    { // SIM_GUARD
        {"GUARDIAN","SOLDADO","HOMBRE"},
        "el guardián",
        SIM_GUARD,
        N_ROOM,
        "Parece incómodo",
        0
    },
    { // SIM_CHEST
        {"COFRE","CAJA"},
        "el cofre",
        SIM_CHEST,
        NW_ROOM,
        "Un cofre grande",
        0b01001011
    },
    { // SIM_KEY
        {"LLAVE",},
        "la llave",
        SIM_KEY,
        NE_ROOM,
        "Una llave para UTILIZAR en un COFRE",
        4 // 0b00000100
    },
    { // SIM_DOOR
        {"PUERTA"},
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
        "Una gran esfera flota en medio de un    extraño paisaje",
        0
    },
    { // FOREST
        {"FORET"},
        "",
        FOREST,
        NO_OBJECT,
        "Arboles y más árboles",
        0
    },
    { // M_FOREST
        {"MFORET"},
        "",
        M_FOREST,
        NO_OBJECT,
        "Arboles y más árboles.¡Y una escalera!",
        0
    },
    { // CHURCH_OUTDOOR
        {"EXT"},
        "",
        CHURCH_OUTDOOR,
        NO_OBJECT,
        "Un claro.En lo alto de una colina,una capilla abandonada",
        0
    },
    { // M_CHURCH_OUTDOOR
        {"MEXT"},
        "",
        M_CHURCH_OUTDOOR,
        NO_OBJECT,
        "Un claro.En lo alto de una colina,una capilla abandonada",
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
        "Un imponente gong se yergue en el centrode la habitación",
        0
    },
    { // CRYPT
        {"CRYPTE"},
        "",
        CRYPT,
        NO_OBJECT,
        "La cripta.Una pequeña estatuilla ocupa un nicho en el muro",
        0
    },
    { // M_CRYPT
        {"MCRYPT"},
        "",
        M_CRYPT,
        NO_OBJECT,
        "La cripta.Una pequeña estatuilla ocupa un nicho en el muro",
        0
    },
    { // LABORATORY
        {"LABO"},
        "",
        LABORATORY,
        NO_OBJECT,
        "Sobre la cocina,un caldero lleno       de agua",
        0
    },
    { // M_LABORATORY
        {"MLABO"},
        "",
        M_LABORATORY,
        NO_OBJECT,
        "Huele a moho y humedad",
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
        "Una casita en la copa de los árboles",
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
        "Una torre en ruinas invadida por la     vegetación",
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
        "Un enorme cofre ocupa una buena parte dela sala",
        0
    },
    { // M_CAVERN_INDOOR
        {"MINTCAVE"},
        "",
        M_CAVERN_INDOOR,
        NO_OBJECT,
        "Un enorme cofre ocupa una buena parte dela sala",
        0
    },
    { // SECRET_ROOM
        {"SECRETR"},
        "",
        SECRET_ROOM,
        NO_OBJECT,
        "Una cámara dorada.Un muro está cubiertopor un grabado",
        0
    },
    { // M_SECRET_ROOM
        {"MSECRETR"},
        "",
        M_SECRET_ROOM,
        NO_OBJECT,
        "Una cámara dorada.Un muro está cubiertopor un grabado",
        0
    }
};
