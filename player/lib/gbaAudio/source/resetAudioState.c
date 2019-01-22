#include "../include/audio.h"

extern Audio * _currentAudio;

void resetAudioState(Audio * audio) {
    AudioState startState;
    for (unsigned int channel = 0; channel < audio->numChannels; channel++) {
        startState.channelIndices[channel] = 0;
        AudioEventList audioEventList = audio->channels[channel];
        startState.channelDelays[channel] = audioEventList.events[0].duration;
    }
    audio->state = startState;
}
