#include "./midiConverter.hpp"
#include "../log/logger.hpp"
#include <math.h>

GBAAudio MidiConverter::convert(MidiFile midiFile) {
    auto log = *Logger::getInstance();

    midiFile.deltaTicks();
    midiFile.linkNotePairs();
    midiFile.doTimeAnalysis();

    int numTracks = midiFile.getTrackCount();
    if (numTracks > MAX_CHANNELS) {
        log(WARN, "Only up to " + to_string(MAX_CHANNELS) + " tracks supported, this MIDI has " +
                  to_string(numTracks) + ". Cropping.");
        numTracks = MAX_CHANNELS;
    }

    GBAAudio gbaAudio;
    gbaAudio.numChannels = (uint32_t) numTracks;
    gbaAudio.channels = (GBAAudioEventList *) malloc(sizeof(GBAAudioEventList) * numTracks);

    for (int track = 0; track < numTracks; track++) {
        MidiEventList& midiEventList = midiFile[track];
        GBAAudioEventList gbaAudioEventList = convertMidiEventList(midiEventList);
        gbaAudio.channels[track] = gbaAudioEventList;

        log(INFO, "Track " + to_string(track) + ": converted " + to_string(gbaAudioEventList.numEvents) +
                  " events.");
    }

    return gbaAudio;
}

GBAAudioEventList MidiConverter::convertMidiEventList(MidiEventList& midiEventList) {
    GBAAudioEventList gbaAudioEventList;
    int numMidiEvents = midiEventList.getEventCount();
    gbaAudioEventList.numEvents = (uint32_t) numMidiEvents;
    gbaAudioEventList.events = (GBAAudioEvent *) malloc(sizeof(GBAAudioEvent) * numMidiEvents);

    double previousTime = 0;
    int gbaEventIndex = 0;
    for (int midiEventIndex = 0; midiEventIndex < numMidiEvents; midiEventIndex++) {
        MidiEvent midiEvent = midiEventList[midiEventIndex];
        if (!midiEvent.isNote()) {
            gbaAudioEventList.numEvents--;
            continue;
        }

        GBAAudioEvent gbaAudioEvent;
        int key = midiEvent.getKeyNumber();
        gbaAudioEvent.note = convertMidiKey(key);

        double deltaTime = midiEvent.seconds - previousTime;
        previousTime = midiEvent.seconds;
        gbaAudioEvent.duration = convertMidiDuration(deltaTime);

        gbaAudioEventList.events[gbaEventIndex] = gbaAudioEvent;

        gbaEventIndex++;
    }

    return gbaAudioEventList;
}

uint16_t MidiConverter::convertMidiDuration(double duration) {
    return  (uint16_t) (duration * 60);
}

uint16_t MidiConverter::convertMidiKey(int key) {
    double power = (key - 21) / 12.0;
    double frequency = 27.5 * pow(2, power);
    double rate = (pow(2, 11) - pow(2, 17) / frequency - 2048) * -16;

    if (rate > 0)
        return (uint16_t) rate;
    return 0;
}