#ifndef AUDIO_H
#define AUDIO_H

typedef struct {
    unsigned char note;
    unsigned char duration;
} AudioEvent;

typedef struct {
    unsigned int numEvents;
    AudioEvent * channel1;
} Audio;

void initAudioSystem();
void playNoteAtOctave();
void playAudio(Audio audio);

#endif
