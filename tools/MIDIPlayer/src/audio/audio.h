#ifndef AUDIO_H
#define AUDIO_H

typedef struct {
    unsigned int note;
    unsigned int duration;
} AudioEvent;

typedef struct {
    unsigned int numEvents;
    AudioEvent * events;
} AudioEventList;

typedef struct {
    unsigned int channelIndices[4];
    unsigned int channelDelays[4];
} AudioState;

typedef struct {
    unsigned int numChannels;
    AudioEventList * channels;
    AudioState state;
} Audio;

void initAudioSystem();
void playNoteAtOctave(int channel, int note, int octave);
void tickAudioSystem();
void setCurrentAudio(Audio * audio);

#endif
