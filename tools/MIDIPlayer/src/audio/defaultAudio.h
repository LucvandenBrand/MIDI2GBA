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

AudioEventList channels[2] = {
  {6, defaultTune},
  {6, defaultTune2}
};

Audio defaultAudio = {
    2,
    &channels[0],
    {{0}, {0}}
};
