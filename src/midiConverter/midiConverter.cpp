#include "./midiConverter.hpp"
#include "../log/logger.hpp"

GBAAudio MidiConverter::convert(MidiFile midiFile) {
    auto log = *Logger::getInstance();

    int numTracks = midiFile.getTrackCount();
    if (numTracks > MAX_CHANNELS) {
        log(WARN, "Only up to " + to_string(MAX_CHANNELS) + " tracks supported, this MIDI has " +
                  to_string(numTracks) + ". Cropping.");
        numTracks = MAX_CHANNELS;
    }

    GBAAudio gbaAudio;
    gbaAudio.numChannels = numTracks;
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
    gbaAudioEventList.numEvents = numMidiEvents;
    gbaAudioEventList.events = (GBAAudioEvent *) malloc(sizeof(GBAAudioEvent) * numMidiEvents);

    int gbaEventIndex = 0;
    for (int midiEventIndex = 0; midiEventIndex < numMidiEvents; midiEventIndex++) {
        MidiEvent midiEvent = midiEventList[midiEventIndex];
        if (!midiEvent.isNote()) {
            gbaAudioEventList.numEvents--;
            continue;
        }
        gbaEventIndex++;

        GBAAudioEvent gbaAudioEvent;
        gbaAudioEvent.note = midiEvent.getKeyNumber();
        gbaAudioEvent.duration = (int) midiEvent.getDurationInSeconds();
        gbaAudioEventList.events[gbaEventIndex] = gbaAudioEvent;
    }

    return gbaAudioEventList;
}