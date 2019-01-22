#include <stdio.h>
#include "tonc.h"
#include "audio.h"
#include "gbfs.h"

AudioEvent defaultTune[6] = {
    {0x02, 100},
    {0x05, 100},
    {0x12, 400},
    {0x02, 100},
    {0x05, 100},
    {0x12, 400}
};

AudioEvent defaultTune2[6] = {
    {0x05, 200},
    {0x03, 200},
    {0x05, 200},
    {0x02, 200},
    {0x03, 200},
    {0x12, 200}
};

Audio defaultAudio = {
    2,
    {
        {6, defaultTune},
        {6, defaultTune2},
        {0, 0},
        {0, 0}
    },
    {{0}, {0}}
};

Audio loadAudio() {
    u32 audioDataSize = 0;
    const GBFS_FILE * audioFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16 * audioData = gbfs_get_obj(audioFile, "audio.bin", &audioDataSize);

    if (audioData == NULL)
        return defaultAudio;

    return loadAudioFromROM(audioData);
}

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
