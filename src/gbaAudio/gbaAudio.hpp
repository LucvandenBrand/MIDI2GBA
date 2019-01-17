#ifndef GBA_AUDIO_H
#define GBA_AUDIO_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
    uint16_t note;
    uint16_t duration;
} GBAAudioEvent;

/**
 * Class to contain GBA music data.
 */
class GBAAudio {
public:
    /**
     * Add a GBA Audio Event to a given channel
     * @param channel The audio channel.
     * @param gbaAudioEvent The event.
     */
    void addEvent(uint32_t channel, GBAAudioEvent gbaAudioEvent);

    /**
     * Write the GBA Audio as binary data to a given location.
     * @param path The write location.
     * @return Number of bytes written.
     */
    int writeToPath(const string& path);

    const static int MAX_CHANNELS = 4;
private:
    vector<GBAAudioEvent> _channels[MAX_CHANNELS];

    template<typename T>
    int writeBinary(ostream &stream, const T &value);

};

#endif