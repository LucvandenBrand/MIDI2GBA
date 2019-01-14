#include "tonc.h"

void playNoteAtOctave(u32 channel, u16 note, u16 octave) {
    switch (channel) {
        case 0:
            REG_SND1FREQ = SFREQ_RESET | (2048-(note>>(4+(octave))));
            break;
        case 1:
            REG_SND2FREQ = SFREQ_RESET | (2048-(note>>(4+(octave))));
            break;
        default:
            break;
    }
}
