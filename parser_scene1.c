#include "parser_scene1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lib.h"
#include "define.h"

void init_parser_scene() {
	// drawImage();
	// drawTextArea();
	setCursor(0,14);
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf("                                        ");
    printf(">                                       ");
	setCursor(1,24);
}

int parser_scene() {
	readLine(33);
	return STATE_CHOICE;
}