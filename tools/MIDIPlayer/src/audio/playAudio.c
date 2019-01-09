#include "tonc.h"
#include "audio.h"

void playAudio(Audio audio) {
    for (int i=0; i<6; i++) {
        unsigned char note = audio.channel1[i].note;
        playNoteAtOctave(note&15, note>>4);
        unsigned char delay = audio.channel1[i].duration;
        VBlankIntrDelay(8*delay);
    }
}
