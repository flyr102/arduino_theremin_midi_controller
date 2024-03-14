/*
  theremin_midi.h - Creates an instance of the theremin_midi
  Created by Conor Fryer 20240310.
*/
//=====[#include guards - begin]===============================================

#ifndef THEREMIN_MIDI_H
#define THEREMIN_MIDI_H

#include "Arduino.h"

class Theremin_Midi
{
  //=====[Declaration of public defines]=========================================
  public:
    Theremin_Midi();
    //=====[Declaration of public data types]======================================
      void begin();
      void update();
    //=====[Declarations (prototypes) of public functions]=========================
  private:
    int attackLastReading;
    void updateMidiMacros();
    void updateCurrentMacroReadings();
    void octaveButtonUpdate();
    void updateMidiNote();
    int millimetersToMidiNodeValue(int distance);
};

//=====[#include guards - end]=================================================

#endif // _THEREMIN_MIDI_H_