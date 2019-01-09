#include <stdio.h>
#include "tonc.h"
#include "audio/audio.h"
#include "audio/defaultAudio.h"

int main() {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);

    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0)|BG_SBB(31));
    tte_init_con();

    tte_printf("MIDIPlayer!\n\n");
    tte_printf("playing...\n\n");

    initAudioSystem();
    playAudio(defaultAudio);

    while (1);
}
