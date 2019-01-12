#ifndef GBA_AUDIO_H
#define GBA_AUDIO_H

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_CHANNELS 4

typedef struct {
    int note;
    int duration;
} GBAAudioEvent;

typedef struct {
    int numEvents;
    GBAAudioEvent * events;
} GBAAudioEventList;

typedef struct {
    int numChannels;
    GBAAudioEventList * channels;
} GBAAudio;

int writeGBAAudioToPath(GBAAudio gbaAudio, const string& path);
void freeGBAAudio(GBAAudio& gbaAudio);

#endif