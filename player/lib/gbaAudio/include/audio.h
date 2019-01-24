#ifndef AUDIO_H
#define AUDIO_H

typedef struct {
    unsigned short note;
    unsigned short duration;
} AudioEvent;

typedef struct {
    unsigned int numEvents;
    AudioEvent * events;
} AudioEventList;

typedef struct {
    unsigned int channelIndices[4];
    unsigned short channelDelays[4];
} AudioState;

typedef struct {
    unsigned int numChannels;
    AudioEventList channels[4];
    AudioState state;
} Audio;

void initAudioSystem();
void setCurrentAudio(Audio * audio);
void resetAudioState(Audio * audio);
void tickAudioSystem();
void playNoteAtOctave(unsigned int channel, unsigned short note);
Audio loadAudioFromROM(const unsigned short * audioData);

#endif
