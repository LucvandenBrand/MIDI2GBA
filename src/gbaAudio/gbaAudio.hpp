#ifndef GBA_AUDIO_H
#define GBA_AUDIO_H

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_CHANNELS 4

typedef struct {
    uint16_t note;
    uint16_t duration;
} GBAAudioEvent;

typedef struct {
    uint32_t numEvents;
    GBAAudioEvent * events;
} GBAAudioEventList;

typedef struct {
    uint32_t numChannels;
    GBAAudioEventList * channels;
} GBAAudio;

int writeGBAAudioToPath(GBAAudio gbaAudio, const string& path);
void freeGBAAudio(GBAAudio& gbaAudio);

#endif