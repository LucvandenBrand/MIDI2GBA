AudioEvent defaultTune[6] = {
    {0x02, 100},
    {0x05, 100},
    {0x12, 400},
    {0x02, 100},
    {0x05, 100},
    {0x12, 400}
};

AudioEventList defaultAudioEventList = {
    6,
    defaultTune
};

Audio defaultAudio = {
    1,
    &defaultAudioEventList,
    {{0}, {0}}
};
