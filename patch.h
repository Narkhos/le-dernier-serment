#ifndef __PATCH__
#define __PATCH__

struct Patch {
    unsigned char* data;
    char x;
	char y;
	char w;
	char h;
};

extern struct Patch patches[7];
#endif