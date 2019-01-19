#include <stdio.h>
#include "tonc.h"
#include "audio/audio.h"

int main() {
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0)|BG_SBB(31));
    tte_init_con();

    tte_printf("MIDIPlayer v0.1.1.\n\n");

    initAudioSystem();

    tte_printf("Loading...\n");
    Audio audio = loadAudio();

    tte_printf("Playing...\n");
    setCurrentAudio(&audio);

    while (1);
}
