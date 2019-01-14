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
Audio loadAudio();
Audio loadAudioFromROM(const u16 * audioData);

#endif
