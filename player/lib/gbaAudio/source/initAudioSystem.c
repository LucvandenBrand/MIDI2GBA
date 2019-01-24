#include "./audio_memmap.h"
#include "../include/audio.h"

void initAudioSystem() {
    // turn sound on
    REG_SNDSTAT = SSTAT_ENABLE;
    // snd1, 2 and 3 on left/right ; both full volume
    REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7) |
                    SDMG_BUILD_LR(SDMG_SQR2, 7) |
                    SDMG_BUILD_LR(SDMG_WAVE, 7) |
                    SDMG_BUILD_LR(SDMG_NOISE, 7);
    // DMG ratio to 100%
    REG_SNDDSCNT = SDS_DMG100;

    // no sweep
    REG_SND1SWEEP = SSW_OFF;
    // envelope: vol=12, decay, max step time (7) ; 50% duty
    REG_SND1CNT = SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
    REG_SND1FREQ = 0;
    REG_SND2CNT = SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
    REG_SND2FREQ = 0;

    // setup the wave channel
    REG_SND3SEL = SOUND3_STEP32 | SOUND3_SET_BANK(1);
    REG_WAVE_RAM0 = 0x10325476;
    REG_WAVE_RAM1 = 0x98badcfe;
    REG_WAVE_RAM2 = 0x10326476;
    REG_WAVE_RAM3 = 0x98badcfe;
    REG_SND3SEL = SOUND3_STEP32 | SOUND3_SET_BANK(0);

    REG_SND3SEL |= SOUND3_PLAY;
    REG_SND3CNT = SSQR_ENV_BUILD(12, 0, 7);

    // setup the noise channel
    REG_SND4CNT = SSQR_ENV_BUILD(12, 0, 7);
}
