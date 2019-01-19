#include "audio.h"
#include "tonc.h"

Audio loadAudioFromROM(const u16 * audioData) {
    Audio audio;
    u32 index = 0;

    audio.numChannels = audioData[index++];
    audio.numChannels |= audioData[index++] >> 8;

    tte_printf(" * Channels: %d\n", audio.numChannels);

    for (u32 channel = 0; channel < audio.numChannels; channel++) {
        AudioEventList audioEventList;
        audioEventList.numEvents = audioData[index++];
        audioEventList.numEvents |= audioData[index++] >> 7;

        if (audioEventList.numEvents > 0) {
            audioEventList.events = (AudioEvent *) &audioData[index];
            index += audioEventList.numEvents * 2;
        }
        audio.channels[channel] = audioEventList;

        tte_printf("  * Channel %d : %d events", channel, audioEventList.numEvents);
        if (channel >= 3)
            tte_printf(" [ ]\n");
        else
            tte_printf(" [x]\n");
    }

    AudioState state = {{0}, {0}};
    audio.state = state;

    return audio;
}
