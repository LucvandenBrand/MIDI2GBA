#include "tonc.h"
#include "audio.h"

void initAudioSystem() {
    irq_init(NULL);
    irq_add(II_VBLANK, tickAudioSystem);

    // turn sound on
    REG_SNDSTAT = SSTAT_ENABLE;
    // snd1 and 2 on left/right ; both full volume
    REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7) | SDMG_BUILD_LR(SDMG_SQR2, 7);
    // DMG ratio to 100%
    REG_SNDDSCNT = SDS_DMG100;

    // no sweep
    REG_SND1SWEEP = SSW_OFF;
    // envelope: vol=12, decay, max step time (7) ; 50% duty
    REG_SND1CNT = SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
    REG_SND1FREQ = 0;
    REG_SND2CNT = SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
    REG_SND2FREQ = 0;
}
