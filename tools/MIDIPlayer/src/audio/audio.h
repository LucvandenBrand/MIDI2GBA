#ifndef AUDIO_H
#define AUDIO_H

#include "tonc.h"

typedef struct {
    u16 note;
    u16 duration;
} AudioEvent;

typedef struct {
    u32 numEvents;
    AudioEvent * events;
} AudioEventList;

typedef struct {
    u32 channelIndices[4];
    u16 channelDelays[4];
} AudioState;

typedef struct {
    u32 numChannels;
    AudioEventList channels[4];
    AudioState state;
} Audio;

void initAudioSystem();
void playNoteAtOctave(u32 channel, u16 note, u16 octave);
void tickAudioSystem();
void setCurrentAudio(Audio * audio);
void resetAudioState(Audio * audio);
Audio loadAudio();
Audio loadAudioFromROM(const u16 * audioData);

#define SOUND3_STEP32		(0<<5)	// Use two banks of 32 steps each
#define SOUND3_SET_BANK(n)	(n<<6)	// Bank to play 0 or 1 (non set bank is written to)
#define SOUND3_PLAY			(1<<7)	// Output sound

#endif
