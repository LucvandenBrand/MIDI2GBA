#include "./midiConverter.hpp"
#include "../log/logger.hpp"
#include <math.h>

GBAAudio MidiConverter::convert(MidiFile midiFile) {
    auto log = *Logger::getInstance();

    midiFile.deltaTicks();
    midiFile.linkNotePairs();
    midiFile.doTimeAnalysis();
    midiFile.joinTracks();

    if (midiFile.getNumTracks() < 1) {
        log(ERROR, "The MIDI file has no tracks!");
        exit(EXIT_FAILURE);
    }

    MidiEventList& midiEventList = midiFile[0];
    GBAAudio gbaAudio = convertMidiEventList(midiEventList);

    return gbaAudio;
}

GBAAudio MidiConverter::convertMidiEventList(MidiEventList& midiEventList) {
    GBAAudio gbaAudio;

    int skippedEvents = 0;
    int numMidiEvents = midiEventList.getEventCount();
    for (int midiEventIndex = 0; midiEventIndex < numMidiEvents; midiEventIndex++) {
        MidiEvent midiEvent = midiEventList[midiEventIndex];
        if (!midiEvent.isNoteOn()) {
            continue;
        }

        auto channel = (uint32_t) midiEvent.getChannel();
        if (channel >= GBAAudio::MAX_CHANNELS) {
            skippedEvents++;
            continue;
        }

        GBAAudioEvent gbaAudioEvent = convertMidiEvent(midiEvent);
        gbaAudio.addEvent(channel, gbaAudioEvent);
    }

    auto log = *Logger::getInstance();
    if (skippedEvents)
        log(WARN, "Skipped " + to_string(skippedEvents) + " events for being out of range.");

    return gbaAudio;
}

GBAAudioEvent MidiConverter::convertMidiEvent(MidiEvent& midiEvent) {
    GBAAudioEvent gbaAudioEvent;
    int key = midiEvent.getKeyNumber();
    gbaAudioEvent.note = convertMidiKey(key);

    double deltaTime = midiEvent.seconds - _previousTime[midiEvent.getChannel()];
    _previousTime[midiEvent.getChannel()] = midiEvent.seconds;
    gbaAudioEvent.duration = convertMidiDuration(deltaTime);

    return gbaAudioEvent;
}

uint16_t MidiConverter::convertMidiDuration(double duration) {
    return  (uint16_t) (duration / 0.016742706);
}

uint16_t MidiConverter::convertMidiKey(int key) {
    double power = (key - 21) / 12.0;
    double frequency = 27.5 * pow(2, power);
    double rate = pow(2, 11) - pow(2, 17) / frequency;

    if (rate < 0)
        rate = 0;
    return (uint16_t) rate;
}