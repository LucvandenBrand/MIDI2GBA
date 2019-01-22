# MIDI2GBA

Simple CLI for converting [MIDI](https://en.wikipedia.org/wiki/MIDI) music to data the **G**ame **B**oy **A**dvance understands.
Special thanks to [Jasper Vijn](https://www.coranac.com) for providing a great tutorial on GBA development!

## Releases
You can download binary releases [here](https://github.com/LucvandenBrand/MIDI2GBA/releases).

## How to build
This project is divided in two subfolders: `converter` for converting MIDI files, and `player` for playing the converted sounds on the GBA.

### Converter
The converter comes with a handy `CMake` file. Building the converter is done by going into the `converter` folder and executing the following commands:

1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

You should have a `MIDI2GBA` binary now.

### Player
The player contains a `gbaAudio` library in its `lib` folder, **which you can use for your own gba projects**. Both the player as the library come with a handy `make` file. Builing the player and its libraries is done by going into the `player` folder and executing **one** of the two commands:

- `make no-content` to make the player without any audio data.
- `make` to make the player with audio data in the `data` folder appended.

You should have a GBA rom now.

### Licence
All source files are protected under the MIT Licence, except for the included external libraries. The used libraries are open-source, but please read their included licenses for
their specific terms and conditions.
