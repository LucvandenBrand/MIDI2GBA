#include "audio.h"
#include "defaultAudio.h"
#include "gbfs.h"

Audio loadAudio() {
    u32 audioDataSize = 0;
    const GBFS_FILE * audioFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16 * audioData = gbfs_get_obj(audioFile, "audio.bin", &audioDataSize);

    if (audioData == NULL)
        return defaultAudio;

    return loadAudioFromROM(audioData);
}
