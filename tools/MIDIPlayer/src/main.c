#include <stdio.h>
#include "tonc.h"
#include "audio/audio.h"

void initAudioSystem() {
    // turn sound on
    REG_SNDSTAT = SSTAT_ENABLE;
    // snd1 on left/right ; both full volume
    REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7);
    // DMG ratio to 100%
    REG_SNDDSCNT = SDS_DMG100;

    // no sweep
    REG_SND1SWEEP = SSW_OFF;
    // envelope: vol=12, decay, max step time (7) ; 50% duty
    REG_SND1CNT = SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
    REG_SND1FREQ = 0;
}

void playNoteAtOctave(int note, int octave) {
    REG_SND1FREQ = SFREQ_RESET | SND_RATE(note, octave);
}

void playAudio() {
    for (int i=0; i<6; i++) {
        unsigned char note = defaultAudio.channel1[i].note;
        playNoteAtOctave(note&15, note>>4);
        unsigned char delay = defaultAudio.channel1[i].duration;
        VBlankIntrDelay(8*delay);
    }
}

int main() {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);

    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0)|BG_SBB(31));
    tte_init_con();

    tte_printf("MIDIPlayer!\n\n");
    tte_printf("playing...\n\n");

    initAudioSystem();
    playAudio();

    while (1);
}
