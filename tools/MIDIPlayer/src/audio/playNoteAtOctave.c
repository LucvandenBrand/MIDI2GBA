#include "tonc.h"

void playNoteAtOctave(int note, int octave) {
    REG_SND1FREQ = SFREQ_RESET | SND_RATE(note, octave);
}
