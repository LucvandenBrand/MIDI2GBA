#ifndef AUDIO_H
#define AUDIO_H

typedef struct {
    unsigned char note;
    unsigned char duration;
} AudioEvent;

typedef struct {
    AudioEvent * channel1;
} Audio;

AudioEvent defaultChannel1[6] = {
    {0x02, 1},
    {0x05, 1},
    {0x12, 4},
    {0x02, 1},
    {0x05, 1},
    {0x12, 4}
};

Audio defaultAudio = {
    defaultChannel1
};

#endif
