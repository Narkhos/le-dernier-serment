#ifndef __SOUND__
#define __SOUND__

//Firmware requires it in the central 32K of RAM (0x4000 to 0xC000), move it as you need...
// #define SOUND_BUFF 0xAC00 //9 bytes
// #define ENT_BUFF 0xAC09 //16 bytes
// #define ENV_BUFF 0xACF1 //16 bytes

// #define SOUND_BUFF 0xA620 //9 bytes
// #define ENT_BUFF 0xA610 //16 bytes
// #define ENV_BUFF 0xA600 //16 bytes

extern char soundBuffer[9];
extern char entBuffer[16];
extern char envBuffer[16];

// #define SOUND_BUFF 0x9F00 //9 bytes
// #define ENT_BUFF 0x9F09 //16 bytes
// #define ENV_BUFF 0x9FF1 //16 bytes
// #define SOUND_BUFF 0x4FF6 //9 bytes
// #define ENT_BUFF 0x4FE6 //16 bytes
// #define ENV_BUFF 0x4FD6 //16 bytes

// #define SOUND_BUFF 0xA560 //9 bytes
// #define ENT_BUFF 0xA550 //16 bytes
// #define ENV_BUFF 0xA540 //16 bytes

unsigned char sound(unsigned char nChannelStatus, int nTonePeriod, int nDuration, unsigned char nVolume, char nVolumeEnvelope, char nToneEnvelope, unsigned char nNoisePeriod);

void ent(unsigned char nEnvelopeNumber, unsigned char nNumberOfSteps, char nTonePeriodOfStep, unsigned char nTimePerStep);

void env(unsigned char nEnvelopeNumber, unsigned char nNumberOfSteps, char nSizeOfStep, unsigned char nTimePerStep);

#endif