#include "./audio_memmap.h"

void playNoteAtOctave(unsigned int channel, unsigned short note) {
    switch (channel) {
        case 0:
            if (note == 0)
                REG_SND1FREQ |= SFREQ_TIMED;
            else
                REG_SND1FREQ = SFREQ_RESET | SFREQ_HOLD | note;
            break;
        case 1:
            if (note == 0)
                REG_SND2FREQ |= SFREQ_TIMED;
            else
                REG_SND2FREQ = SFREQ_RESET | SFREQ_HOLD | note;
            break;
        case 2:
            if (note == 0)
                REG_SND3FREQ |= SFREQ_TIMED;
            else
                REG_SND3FREQ = SFREQ_RESET | SFREQ_HOLD | note;
            break;
        case 3:
            if (note == 0)
                REG_SND4FREQ |= SFREQ_TIMED;
            else
                REG_SND4FREQ = SFREQ_RESET | SND4_STAGES_15 | SFREQ_TIMED;
        default:
            break;
    }
}
