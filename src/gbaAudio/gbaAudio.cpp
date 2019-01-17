#include "gbaAudio.hpp"

void GBAAudio::addEvent(uint32_t channel, GBAAudioEvent gbaAudioEvent) {
    if (channel >= MAX_CHANNELS)
        return;

    _channels[channel].push_back(gbaAudioEvent);
}

int GBAAudio::writeToPath(const string& path) {
    ofstream out(path.c_str());
    int byteCount = writeBinary(out, (uint32_t) MAX_CHANNELS);
    for (vector<GBAAudioEvent> &gbaAudioEventList : _channels) {
        byteCount += writeBinary(out, (uint32_t) gbaAudioEventList.size());
        for (GBAAudioEvent &gbaAudioEvent : gbaAudioEventList) {
            byteCount += writeBinary(out, gbaAudioEvent.note);
            byteCount += writeBinary(out, gbaAudioEvent.duration);
        }
    }

    out.flush();
    return byteCount;
}

template<typename T>
int GBAAudio::writeBinary(ostream &stream, const T &value) {
    int byteCount = sizeof(T);
    stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
    return byteCount;
}