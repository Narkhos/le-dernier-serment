#include "database.h"

// We don't use the .name = {""} syntax in structure array initialization
// because some compilers like SDCC do not recognize this syntax.
struct Object objectDatabase[MAX_OBJECT_COUNT] = {
    // System
    { // NO_OBJECT
        {"EMPTY"},
        "nothing",
        NO_OBJECT,
        NO_OBJECT,
        "",
        0
    },
    { // CONTEXT
        {"CONTEXT"},
        "context",
        CONTEXT,
        NO_OBJECT,
        "",
        0
    },
    // Protagonist
    { // HERO
        {"ME", "SELF", "M", "ONESSELF", "MYSELF"},
        "you",
        HERO,
        CONTEXT,
        "It's you",
        0
    },
    { // INVENTORY
        {"BAG"},
        "your bag",
        INVENTORY,
        CONTEXT,
        "Inventory:",
        0
    },
    // Characters
    { // HERMIT
        {"MONK", "MAN", "POCKET", "HERMES"},
        "the monk",
        HERMIT,
        M_HUT_INDOOR,
        "An old monk",
        0b00000000
    },
    { // NAHASH
        {"NAHASH", "ANGEL"},
        "Nahash",
        NAHASH,
        NO_OBJECT,
        "An angel passes by",
        0
    },
    { // GOD
        {"CREATOR","SPHERE","GOD", "BALL"},
        "the creator",
        GOD,
        GOD_ROOM,
        "The creator god",
        0
    },
    // Objects
    { // FLUTE (BAS-RELIEF)
        {"FLUTE"},
        "the flute",
        FLUTE,
        BASRELIEF,
        "The flute and the musician are sculpted as one piece",
        0
    },
    { // FLUTE (BAS-RELIEF)
        {"FLUTE"},
        "the flute",
        M_FLUTE,
        M_BASRELIEF,
        "The flute and the musician are sculpted as one piece",
        0
    },
    { // STOVE
        {"STOVE", "OVEN", "FIRE"},
        "the stove",
        STOVE,
        LABORATORY,
        "An old stove",
        0
    },
    { // M_BUTTON
        {"BUTTON", "LEVER"},
        "the button",
        M_BUTTON,
        M_LABORATORY,
        "A small rusty lever",
        0
    },
    { // IVY
        {"IVY"},
        "the ivy",
        IVY,
        CAVERN_OUTDOOR,
        "The ivy climbs up to an opening",
        0
    },
    { // LADDER
        {"LADDER"},
        "the ladder",
        LADDER,
        M_FOREST,
        "The ladder disappears into the foliage of the trees",
        0
    },
    { // TOWER
        {"TOWER","RUIN","CASTLE"},
        "the tower",
        TOWER,
        CAVERN_OUTDOOR,
        "A ruined tower overgrown with ivy",
        0
    },
    { // M_TOWER
        {"TOWER","RUIN","CASTLE"},
        "the tower",
        M_TOWER,
        M_CAVERN_OUTDOOR,
        "A ruined tower",
        0
    },
    { // HUT
        {"HUT","HOUSE","CABIN"},
        "the hut",
        HUT,
        HUT_OUTDOOR,
        "A treehouse",
        0
    },
    { // M_HUT
        {"HUT","HOUSE","CABIN"},
        "the hut",
        M_HUT,
        M_HUT_OUTDOOR,
        "A treehouse",
        0
    },
    { // BASRELIEF
        {"BAS-RELIEF", "BASRELIEF"},
        "the bas-relief",
        BASRELIEF,
        SECRET_ROOM,
        "A bas-relief showing a musician",
        0b00001000
    },
    { // M_BASRELIEF
        {"BAS-RELIEF", "BASRELIEF"},
        "the bas-relief",
        M_BASRELIEF,
        M_SECRET_ROOM,
        "A bas-relief showing a musician",
        0b00001000
    },
    { // BUSH
        {"BUSH", "PLANT", "TREE", "BUSHES"},
        "the bush",
        BUSH,
        CAVERN_OUTDOOR,
        "A bush full of berries",
        0b00001000
    },
    { // AMULET
        {"AMULET", "JEWELRY", "PENDANT", "TALISMAN"},
        "the amulet",
        AMULET,
        HERMIT,
        "A pendant",
        4 // 0b00000100
    },
    { // BERRY
        {"BERRIES","FRUITS","BERRY"},
        "the berries",
        BERRY,
        BUSH,
        "Red berries",
        4 // 0b00000100
    },
    { // TRAPDOOR
        {"TRAPDOOR","STAIRCASE"},
        "the trapdoor",
        TRAPPE,
        CHURCH_INDOOR,
        "A trapdoor",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_TRAP
        {"TRAPDOOR", "STAIRS"},
        "the trapdoor",
        M_TRAPPE,
        M_CHURCH_INDOOR,
        "A trapdoor",
        0
    },
    { // BUTTON
        {"BUTTON", "LEVER"},
        "the button",
        BUTTON,
        LABORATORY,
        "A small lever",
        1 // 0b00000001, MASK_CLOSED
    },
    { // BOOK
        {"BOOK", "GRIMOIRE"},
        "the grimoire",
        BOOK,
        LABORATORY,
        "An old grimoire",
        4 // 0b00000100
    },
    { // MINT
        {"MINT", "MENTE"},
        "the mint",
        MINT,
        HERMIT,
        "Some mint",
        4 // 0b00000100
    },
    { // TIBIA
        {"TIBIA"},
        "the tibia",
        TIBIA,
        BONES,
        "It looks like a spoon",
        4 // 0b00000100
    },
    { // FLASK
        {"FLASK", "VIAL", "POTION"},
        "the flask",
        FLASK,
        BONES,
        "A small flask",
        4 // 0b00000100
    },
    { // MUSHROOMS
        {"AMANITAS", "AMANITA", "MUSHROOM"},
        "the amanitas",
        MUSHROOMS,
        M_CAULDRON,
        "Small white mushrooms",
        4 // 0b00000100
    },
    { // BONES
        {"SKELETON", "BONE", "BONES", "SKULL"},
        "the skeleton",
        BONES,
        MIRROR_ROOM,
        "Human bones",
        0b00001000
    },
    { // SALT
        {"SALT", "SALT SHAKER"},
        "the salt",
        SALT,
        BONES,
        "Some salt",
        4
    },
    { // PEPPER
        {"PEPPER"},
        "the pepper",
        PEPPER,
        BONES,
        "Some pepper",
        4
    },
    { // ARTEFACT
        {"SCEPTER", "STAFF", "SEPTRE", "FLUTE"},
        "the scepter",
        ARTEFACT,
        CHEST,
        "A staff with holes and a ball at the end",
        0b00000100
    },
    { // GONG
        {"GONG", "CYMBAL", "DISC"},
        "the gong",
        GONG,
        M_CHURCH_INDOOR,
        "It's a gong",
        0
    },
    { // CAULDRON
        {"CAULDRON", "POT", "SUBSTRATE", "WATER"},
        "the cauldron",
        CAULDRON,
        LABORATORY,
        "A small cauldron",
        0
    },
    { // M_CAULDRON
        {"CAULDRON", "POT"},
        "the cauldron",
        M_CAULDRON,
        M_LABORATORY,
        "A cauldron worn by time",
        0
    },
    { // STATUETTE
        {"STATUETTE", "STATUE", "HOLE", "BASE"},
        "the statuette",
        STATUETTE,
        CRYPT,
        "A statue fixed to a base with a small hole",
        128 // 0b10000000 // MASK_CUSTOM_STATE
    },
    { // M_STATUETTE
        {"STATUETTE", "STATUE", "HOLE", "BASE"},
        "the statuette",
        M_STATUETTE,
        M_CRYPT,
        "A statue fixed to a base with a small hole",
        0
    },
    { // WHISTLE
        {"WHISTLE"},
        "the whistle",
        WHISTLE,
        BASRELIEF,
        "A whistle",
        4 // 0b00000100
    },
    { // PARTITION
        {"SCORE", "PAPER", "SHEET"},
        "the score",
        PARTITION,
        M_BASRELIEF,
        "A musical score",
        4 // 0b00000100
    },
    { // DOOR
        {"DOOR"},
        "the door",
        DOOR,
        CRYPT,
        "It has neither a lock nor a handle",
        1 // 0b00000001, MASK_CLOSED
    },
    { // M_DOOR
        {"DOOR"},
        "the door",
        M_DOOR,
        M_CRYPT,
        "It has neither a lock nor a handle",
        1 // 0b00000001, MASK_CLOSED
    },
    { // CHURCH
        {"CHURCH", "CHAPEL", "RUIN"},
        "the church",
        CHURCH,
        CHURCH_OUTDOOR,
        "A dilapidated building",
        0
    },
    { // CHEST
        {"CHEST", "BOX"},
        "the chest",
        CHEST,
        CAVERN_INDOOR,
        "A wooden chest",
        0b01001011
    },
    { // M_CHEST
        {"COFFRE", "BOITE"},
        "the chest",
        M_CHEST,
        M_CAVERN_INDOOR,
        "A wooden chest",
        0b01001011
    },
    { // KEY
        {"KEY"},
        "the key",
        KEY,
        HERMIT,
        "A small key",
        4 // 0b00000100
    },
    { // FIREBRAND
        {"POKER", "PIKE"},
        "the firebrand",
        FIREBRAND,
        M_CHEST,
        "A thin pointed metal rod",
        4 // 0b00000100
    },
    { // MIRROR
        {"MIRROR", "GLASS", "REFLECTION"},
        "the mirror",
        MIRROR,
        MIRROR_ROOM,
        "A large mirror",
        0
    },
    { // M_MIRROR
        {"MIRROR", "GLASS", "REFLECTION"},
        "the mirror",
        M_MIRROR,
        M_MIRROR_ROOM,
        "A large mirror",
        0
    },
    // Simulation locations
    { // NW_ROOM
        {"NW_ROOM"},
        "",
        NW_ROOM,
        NO_OBJECT,
        "A room with a chest to OPEN",
        0
    },
    { // N_ROOM
        {"N_ROOM"},
        "",
        N_ROOM,
        NO_OBJECT,
        "TALK to the guard",
        0
    },
    { // NE_ROOM
        {"NE_ROOM"},
        "",
        NE_ROOM,
        NO_OBJECT,
        "TAKE the key seems like a good idea",
        0
    },
    { // W_ROOM
        {"W_ROOM"},
        "",
        W_ROOM,
        NO_OBJECT,
        "Remember to check your INVENTORY",
        0
    },
    { // CENTER_ROOM
        {"CENTER_R"},
        "",
        CENTER_ROOM,
        NO_OBJECT,
        "An empty room",
        //"aaaaaaaabbbbbbbbccccccccddddddddaaaaaaaabbbbbbbbccccccccdddddddd"
        0
    },
    { // E_ROOM
        {"E_ROOM"},
        "",
        E_ROOM,
        NO_OBJECT,
        "You can OPEN the door",
        0
    },
    { // SW_ROOM
        {"SW_ROOM"},
        "",
        SW_ROOM,
        NO_OBJECT,
        "An empty room",
        0
    },
    { // S_ROOM
        {"S_ROOM"},
        "",
        S_ROOM,
        NO_OBJECT,
        "Type NORTH,SOUTH,EAST or WEST to move",
        0
    },
    { // SE_ROOM
        {"SE_ROOM"},
        "",
        SE_ROOM,
        NO_OBJECT,
        "An empty room",
        0
    },
    // Simulation objects
    { // SIM_CLUB
        {"CLUB", "MACE"},
        "the club",
        SIM_CLUB,
        SIM_CHEST,
        "A heavy weapon",
        4
    },
    { // SIM_GUARD
        {"GUARD", "SOLDIER", "MAN"},
        "the guard",
        SIM_GUARD,
        N_ROOM,
        "He doesn't look friendly",
        0
    },
    { // SIM_CHEST
        {"CHEST", "BOX", "TRUNK"},
        "the chest",
        SIM_CHEST,
        NW_ROOM,
        "A big chest",
        0b01001011
    },
    { // SIM_KEY
        {"KEY"},
        "the key",
        SIM_KEY,
        NE_ROOM,
        "A key to USE on a CHEST",
        4 // 0b00000100
    },
    { // SIM_DOOR
        {"DOOR"},
        "the door",
        SIM_DOOR,
        E_ROOM,
        "A door",
        0b01000001
    },
    // Locations
    { // GOD_ROOM
        {"GODROOM"},
        "",
        GOD_ROOM,
        NO_OBJECT,
        "A large sphere floats in the middle of a strange landscape",
        0
    },
    { // FOREST
        {"FOREST"},
        "",
        FOREST,
        NO_OBJECT,
        "Trees,more trees",
        0
    },
    { // M_FOREST
        {"MFOREST"},
        "",
        M_FOREST,
        NO_OBJECT,
        "Trees,more trees.And a ladder!",
        0
    },
    { // CHURCH_OUTDOOR
        {"OUTSIDE"},
        "",
        CHURCH_OUTDOOR,
        NO_OBJECT,
        "A clearing.On top of a hill,an abandoned church",
        0
    },
    { // M_CHURCH_OUTDOOR
        {"MOUTSIDE"},
        "",
        M_CHURCH_OUTDOOR,
        NO_OBJECT,
        "A clearing.On top of a hill,an abandoned church",
        0
    },
    { // CHURCH_INDOOR
        {"INSIDE"},
        "",
        CHURCH_INDOOR,
        NO_OBJECT,
        "There is a trapdoor on the floor",
        0
    },
    { // M_CHURCH_INDOOR
        {"MINSIDE"},
        "",
        M_CHURCH_INDOOR,
        NO_OBJECT,
        "A massive gong stands in the middle of the room",
        0
    },
    { // CRYPT
        {"CRYPT"},
        "",
        CRYPT,
        NO_OBJECT,
        "The crypt.A small statuette occupies a niche in the wall",
        0
    },
    { // M_CRYPT
        {"MCRYPT"},
        "",
        M_CRYPT,
        NO_OBJECT,
        "The crypt.A small statuette occupies a niche in the wall",
        0
    },
    { // LABORATORY
        {"LAB"},
        "",
        LABORATORY,
        NO_OBJECT,
        "On the stove,a cauldron filled with water",
        0
    },
    { // M_LABORATORY
        {"MLAB"},
        "",
        M_LABORATORY,
        NO_OBJECT,
        "Smell of rust and humidity",
        0
    },
    { // MIRROR_ROOM
        {"ROOM"},
        "",
        MIRROR_ROOM,
        NO_OBJECT,
        "The mirror room.A skeleton lies on the floor",
        0
    },
    { // M_MIRROR_ROOM
        {"MROOM"},
        "",
        M_MIRROR_ROOM,
        NO_OBJECT,
        "On the other side of the mirror",
        0
    },
    { // HUT_OUTDOOR
        {"OUTHUT"},
        "",
        HUT_OUTDOOR,
        NO_OBJECT,
        "Absolute tranquility",
        0
    },
    { // M_HUT_OUTDOOR
        {"MOUTHUT"},
        "",
        M_HUT_OUTDOOR,
        NO_OBJECT,
        "A hut at the treetop",
        0
    },
    { // HUT_INDOOR
        {"INHUT"},
        "",
        HUT_INDOOR,
        NO_OBJECT,
        "Finally alone!",
        0
    },
    { // M_HUT_INDOOR
        {"MINHUT"},
        "",
        M_HUT_INDOOR,
        NO_OBJECT,
        "An old monk rests on an armchair",
        0
    },
    { // CAVERN_OUTDOOR
        {"OUTCAVE"},
        "",
        CAVERN_OUTDOOR,
        NO_OBJECT,
        "A ruined tower overgrown with vegetation",
        0
    },
    { // M_CAVERN_OUTDOOR
        {"MOUTCAVE"},
        "",
        M_CAVERN_OUTDOOR,
        NO_OBJECT,
        "The remains of a past glory",
        0
    },
    { // CAVERN_INDOOR
        {"INCAVE"},
        "",
        CAVERN_INDOOR,
        NO_OBJECT,
        "A large chest occupies much of the cave",
        0
    },
    { // M_CAVERN_INDOOR
        {"MINCAVE"},
        "",
        M_CAVERN_INDOOR,
        NO_OBJECT,
        "A large chest occupies much of the cave",
        0
    },
    { // SECRET_ROOM
        {"SECRETR"},
        "",
        SECRET_ROOM,
        NO_OBJECT,
        "A golden room.A wall is covered by a bas-relief",
        0
    },
    { // M_SECRET_ROOM
        {"MSECRETR"},
        "",
        M_SECRET_ROOM,
        NO_OBJECT,
        "A golden room.A wall is covered by a bas-relief",
        0
    }
};
