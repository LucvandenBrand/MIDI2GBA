#include "tonc.h"

void playNoteAtOctave(u32 channel, u16 note, u16 octave) {
    switch (channel) {
        case 0:
            REG_SND1FREQ = SFREQ_RESET | SFREQ_TIMED | note;
            break;
        case 1:
            REG_SND2FREQ = SFREQ_RESET | SFREQ_TIMED | note;
            break;
        case 2:
            REG_SND3FREQ = SFREQ_RESET | SFREQ_TIMED | note;
            break;
        case 3:
            REG_SND4FREQ = SFREQ_RESET | SFREQ_TIMED | note;
        default:
            break;
    }
}
