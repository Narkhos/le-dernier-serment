////////////////////////////////////////////////////////////////////////
// Sound01.c
// Mochilote - www.cpcmania.com
////////////////////////////////////////////////////////////////////////
#include "sound.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////
//sound
////////////////////////////////////////////////////////////////////////

char soundBuffer[9];
char entBuffer[16];
char envBuffer[16];

unsigned char bQueue = 0;
unsigned char sound(unsigned char nChannelStatus, int nTonePeriod, int nDuration, unsigned char nVolume, char nVolumeEnvelope, char nToneEnvelope, unsigned char nNoisePeriod)
{
	//This function uses 9 bytes of memory for sound buffer. Firmware requires it in the central 32K of RAM (0x4000 to 0xC000)
	/*
		The bytes required to define the sound are as follows
		byte 0 - channel status byte
		byte 1 - volume envelope to use
		byte 2 - tone envelope to use
		bytes 3&4 - tone period
		byte 5 - noise period
		byte 6 - start volume
		bytes 7&8 - duration of the sound, or envelope repeat count	
	*/
	
	__asm
		LD HL, #_soundBuffer

		LD A, 4 (IX) ;nChannelStatus
		LD (HL), A
		INC HL

		LD A, 10 (IX) ;nVolumeEnvelope
		LD (HL), A
		INC HL

		LD A, 11 (IX) ;nToneEnvelope
		LD (HL), A
		INC HL

		LD A, 5 (IX) ;nTonePeriod
		LD (HL), A
		INC HL
		LD A, 6 (IX) ;nTonePeriod
		LD (HL), A
		INC HL

		LD A, 12 (IX) ;nNoisePeriod
		LD (HL), A
		INC HL

		LD A, 9 (IX) ;nVolume
		LD (HL), A
		INC HL

		LD A, 7 (IX) ;nDuration
		LD (HL), A
		INC HL
		LD A, 8 (IX) ;nDuration
		LD (HL), A
		INC HL

		LD HL, #_soundBuffer
		CALL #0xBCAA ;SOUND QUEUE
	
		LD HL, #_bQueue
		LD (HL), #0
		JP NC, _EndSound
		LD (HL), #1
		_EndSound:
	__endasm;
	
	return bQueue;
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//ent
////////////////////////////////////////////////////////////////////////
void ent(unsigned char nEnvelopeNumber, unsigned char nNumberOfSteps, char nTonePeriodOfStep, unsigned char nTimePerStep)
{
	//This function uses 16 bytes of memory for ent buffer. Firmware requires it in the central 32K of RAM (0x4000 to 0xC000)
	
	__asm
		LD HL, #_entBuffer

		LD A, #0x1
		LD (HL), A
		INC HL

		LD A, 5 (IX) ;nNumberOfSteps
		LD (HL), A
		INC HL

		LD A, 6 (IX) ;nTonePeriodOfStep
		LD (HL), A
		INC HL

		LD A, 7 (IX) ;nTimePerStep
		LD (HL), A
		INC HL

		LD A, 4 (IX) ;nEnvelopeNumber
		LD HL, #_entBuffer
		CALL #0xBCBF ;SOUND TONE ENVELOPE
	__endasm;
}

void env(unsigned char nEnvelopeNumber, unsigned char nNumberOfSteps, char nSizeOfStep, unsigned char nTimePerStep)
{
	//This function uses 16 bytes of memory for env buffer. Firmware requires it in the central 32K of RAM (0x4000 to 0xC000)
	
	__asm
		LD HL, #_envBuffer

		LD A, #0x1
		LD (HL), A
		INC HL

		LD A, 5 (IX) ;nNumberOfSteps
		LD (HL), A
		INC HL

		LD A, 6 (IX) ;nSizeOfStep
		LD (HL), A
		INC HL

		LD A, 7 (IX) ;nTimePerStep
		LD (HL), A
		INC HL

		LD A, 4 (IX) ;nEnvelopeNumber
		LD HL, #_envBuffer
		CALL #0xBCBC ;SOUND AMPL ENVELOPE
	__endasm;
}