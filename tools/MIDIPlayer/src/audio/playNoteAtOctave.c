#include "tonc.h"

void playNoteAtOctave(int channel, int note, int octave) {
    switch (channel) {
        case 0:
            REG_SND1FREQ = SFREQ_RESET | SND_RATE(note, octave);
            break;
        case 1:
            REG_SND2FREQ = SFREQ_RESET | SND_RATE(note, octave);
            break;
        default:
            break;
    }
}
