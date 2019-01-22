#ifndef MIDI_CONVERTER_H
#define MIDI_CONVERTER_H

#include "../lib/midifile/MidiFile.h"
#include "../gbaAudio/gbaAudio.hpp"
#include <map>

using namespace smf;

/**
 * Class for converting midi files to gba data.
 */
class MidiConverter {
public:
    /**
     * Convert a midi file to data the gba understands.
     * @param midiFile The midi file to convert.
     * @return GBA audio data.
     */
    GBAAudio convert(MidiFile midiFile);

private:
    GBAAudio convertMidiEventList(MidiEventList& midiEventList);
    GBAAudioEvent convertMidiEvent(MidiEvent& event);
    uint16_t convertMidiDuration(double duration);
    uint16_t convertMidiKey(int key);

    double _previousTime[4] = {0};
};

#endif