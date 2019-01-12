#include "gbaAudio.hpp"

template<typename T>
int writeBinary(ostream &stream, const T &value) {
    int byteCount = sizeof(T);
    stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
    return byteCount;
}

int writeGBAAudioToPath(GBAAudio gbaAudio, const string& path) {
    ofstream out(path.c_str());
    int byteCount = writeBinary(out, gbaAudio.numChannels);
    for (int channel = 0; channel < gbaAudio.numChannels; channel++) {
        GBAAudioEventList gbaAudioEventList = gbaAudio.channels[channel];
        byteCount += writeBinary(out, gbaAudioEventList.numEvents);
        for (int eventIndex = 0; eventIndex < gbaAudioEventList.numEvents; eventIndex++) {
            GBAAudioEvent gbaAudioEvent = gbaAudioEventList.events[eventIndex];
            byteCount += writeBinary(out, gbaAudioEvent.note);
            byteCount += writeBinary(out, gbaAudioEvent.duration);
        }
    }

    out.flush();
    return byteCount;
}

void freeGBAAudio(GBAAudio& gbaAudio) {
    for (int channel = 0; channel < gbaAudio.numChannels; channel++) {
        free(gbaAudio.channels[channel].events);
        gbaAudio.channels[channel].numEvents = 0;
    }
    free(gbaAudio.channels);
    gbaAudio.numChannels = 0;
}