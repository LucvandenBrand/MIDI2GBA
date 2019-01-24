#include "./audio_memmap.h"

void playNoteAtOctave(unsigned int channel, unsigned short note) {
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
            REG_SND4FREQ = SFREQ_RESET | SND4_STAGES_15 | SFREQ_TIMED;
        default:
            break;
    }
}
