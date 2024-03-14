#include "theremin_midi.h"

Theremin_Midi thereminMidi;

void setup() {
  thereminMidi.begin();
}

void loop() {
  thereminMidi.update();
}