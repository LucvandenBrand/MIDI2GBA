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
    GBAAudioEventList convertMidiEventList(MidiEventList& midiEventList);
    GBAAudioEvent convertMidiEvent(MidiEvent& event);
    uint16_t convertMidiDuration(double duration);
    uint16_t convertMidiKey(int key);

    static const std::map<int, uint16_t> _noteMap;
    double _previousTime = 0;
};

#endif