#ifndef __DATATEXT_H__
#define __DATATEXT_H__

#include <stdbool.h>
#include <stddef.h>

#define MAX_TEXT_COUNT 52
#define MAX_TEXT_LENGTH 80

struct DataText {
	char str[MAX_TEXT_LENGTH];
};

// Liste des textes
enum textIds{
    // TODO : donner une constante à chaque texte plutôt que de référencer directement
    // leur numéro
    // (cf book.c et dialog.c les méthodes printDataText)
    // Je peux appeler les textes BOOK_SHINY_01, ..., DIALOG_HERMIT_01, ...
    // histoire de ne pas avoir à nommer chaque phrase mais d'avoir quand même
    // un moyen de limiter les erreurs
    TEXT_COUNT
};

extern struct DataText textDatabase[MAX_TEXT_COUNT];

#endif
