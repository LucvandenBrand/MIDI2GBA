#include "tonc.h"
#include "audio.h"

Audio * _currentAudio = 0;

void tickAudioSystem() {
    if (_currentAudio == 0)
        return;

    u32 channelsFinished = 0;
    AudioState * state = &_currentAudio->state;
    for (u32 channel = 0; channel < _currentAudio->numChannels; channel++) {
        AudioEventList audioEventList = _currentAudio->channels[channel];

        u32 eventIndex = state->channelIndices[channel];
        if (eventIndex >= audioEventList.numEvents) {
            channelsFinished++;
            continue;
        }

        AudioEvent event = audioEventList.events[eventIndex];
        if (state->channelDelays[channel] == 0) {
            u16 note = event.note;
            playNoteAtOctave(channel, note, 0);

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
