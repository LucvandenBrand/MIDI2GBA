#include "tonc.h"
#include "audio.h"

Audio * _currentAudio = 0;

void tickAudioSystem() {
    if (_currentAudio == 0)
        return;

    AudioState * state = &_currentAudio->state;
    for (int channel = 0; channel < _currentAudio->numChannels; channel++) {
        AudioEventList audioEventList = _currentAudio->channels[channel];

        unsigned int eventIndex = state->channelIndices[channel];
        if (eventIndex >= audioEventList.numEvents) {
            state->channelIndices[channel] = 0;
            continue;
        }

        AudioEvent event = audioEventList.events[eventIndex];
        if (state->channelDelays[channel] == 0) {
            unsigned char note = event.note;
            playNoteAtOctave(channel, note&15, note>>4);
            state->channelDelays[channel] += event.duration;
            state->channelIndices[channel]++;
        } else {
            state->channelDelays[channel]--;
        }
    }
}
