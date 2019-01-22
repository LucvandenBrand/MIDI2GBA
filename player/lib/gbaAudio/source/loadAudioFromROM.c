#include "../include/audio.h"

Audio loadAudioFromROM(const unsigned short * audioData) {
    Audio audio;
    unsigned int index = 0;

    audio.numChannels = audioData[index++];
    audio.numChannels |= audioData[index++] >> 8;

    for (unsigned int channel = 0; channel < audio.numChannels; channel++) {
        AudioEventList audioEventList;
        audioEventList.numEvents = audioData[index++];
        audioEventList.numEvents |= audioData[index++] >> 7;

        if (audioEventList.numEvents > 0) {
            audioEventList.events = (AudioEvent *) &audioData[index];
            index += audioEventList.numEvents * 2;
        }
        audio.channels[channel] = audioEventList;
    }

    AudioState state = {{0}, {0}};
    audio.state = state;

    return audio;
}
