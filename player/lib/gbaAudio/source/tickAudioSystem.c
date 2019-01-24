#include "../include/audio.h"

Audio * _currentAudio = 0;

void tickAudioSystem() {
    if (_currentAudio == 0)
        return;

    unsigned int channelsFinished = 0;
    AudioState * state = &_currentAudio->state;
    for (unsigned int channel = 0; channel < _currentAudio->numChannels; channel++) {
        AudioEventList audioEventList = _currentAudio->channels[channel];

        unsigned int eventIndex = state->channelIndices[channel];
        if (eventIndex >= audioEventList.numEvents) {
            channelsFinished++;
            continue;
        }

        AudioEvent event = audioEventList.events[eventIndex];
        if (state->channelDelays[channel] == 0) {
            unsigned short note = event.note;
            playNoteAtOctave(channel, note);

            if (eventIndex+1 < audioEventList.numEvents)
                state->channelDelays[channel] += audioEventList.events[eventIndex+1].duration;
            state->channelIndices[channel]++;
        } else {
            state->channelDelays[channel]--;
        }
    }

    if (channelsFinished == _currentAudio->numChannels)
        resetAudioState(_currentAudio);
}
