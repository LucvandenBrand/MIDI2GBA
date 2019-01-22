#include "../include/audio.h"

extern Audio * _currentAudio;

void setCurrentAudio(Audio * audio) {
    _currentAudio = audio;
    resetAudioState(_currentAudio);
}
