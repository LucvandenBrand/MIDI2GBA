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
    static const std::map<int, uint16_t> _noteMap;

private:
    GBAAudioEventList convertMidiEventList(MidiEventList& midiEventList);
    uint16_t convertMidiDuration(double duration);
    uint16_t convertMidiKey(int key);
};

#endif