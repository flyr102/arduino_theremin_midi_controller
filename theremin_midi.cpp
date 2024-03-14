//=====[Libraries]=============================================================

#include <Arduino.h>
#include <Wire.h>
#include <MIDI.h>
#include "theremin_midi.h"
#include "SparkFun_VL53L1X.h"
#include "Macro.h"
#include "Button.h"

//=====[Declaration of private defines]========================================

#define OCTAVE_SEMITONES 12

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

MIDI_CREATE_DEFAULT_INSTANCE();

SFEVL53L1X distanceSensor;

Macro macros[]{Macro(A3), Macro(A2), Macro(A1), Macro(A0)};
int sizeOfMacros = sizeof(macros)/sizeof(macros[0]);
static int currentMacroReadings[] = {0, 0, 0, 0};

int distanceLastReading = 0;
int lastNoteValue = 0;
int currentOctaveRange = 5;

Button leftButton(4);
Button rightButton(6);

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

Theremin_Midi::Theremin_Midi(){
}

void Theremin_Midi::begin(){
  Wire.begin();
  MIDI.begin(MIDI_CHANNEL_OMNI);
  //Serial.begin(115200);
  leftButton.begin();
  rightButton.begin();
  distanceSensor.begin();
}

void Theremin_Midi::update(){
  updateMidiNote();
  updateCurrentMacroReadings();
  updateMidiMacros();
  //octaveButtonUpdate();
}

//=====[Implementations of private functions]==================================

void Theremin_Midi::updateCurrentMacroReadings(){
  for(int i = 0; i < sizeOfMacros; i++){
    currentMacroReadings[i] = macros[i].getMacro();
  }
}

void Theremin_Midi::updateMidiMacros(){
  for(int i = 0; i < sizeOfMacros; i++){
    if (currentMacroReadings[i] != macros[i].getMacro()){
      MIDI.sendControlChange(i, currentMacroReadings[i], 1);
    }
  }
}

void Theremin_Midi::octaveButtonUpdate(){
  //Serial.println(String(leftButton.buttonEventUpdate()));
  //Serial.println(String(rightButton.buttonEventUpdate()));
  if(leftButton.buttonEventUpdate() == true){
    if(currentOctaveRange >= 0){
      currentOctaveRange--;
    }
  }
  if(rightButton.buttonEventUpdate() == true){
    if(currentOctaveRange <= 12){
      currentOctaveRange++;
    }
  }
}

void Theremin_Midi::updateMidiNote(){
  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
  int currentDistance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();
  //Serial.println(currentDistance);
  int midiNoteValue = millimetersToMidiNodeValue(currentDistance);
  //Serial.println(midiNoteValue);
  if (currentDistance > 1300){
    MIDI.sendNoteOff(lastNoteValue, 0, 2);
  }
  else if (midiNoteValue != lastNoteValue){
    MIDI.sendNoteOff(lastNoteValue, 0, 2);
    MIDI.sendNoteOn(midiNoteValue, 127, 2);
    lastNoteValue = midiNoteValue;
    distanceLastReading = currentDistance;
  }
}

int Theremin_Midi::millimetersToMidiNodeValue(int distance){
  int midiValueConversion = (12 * currentOctaveRange) + (distance/110);
  //Serial.println(midiValueConversion);
  if (midiValueConversion > 127){
    return 127;
  }
  else if (midiValueConversion < 0){
    return 0;
  }
  else{
    return midiValueConversion;
  }
}