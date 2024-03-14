//=====[Libraries]=============================================================

#include "arduino.h"
#include "Macro.h"

//=====[Declaration of private defines]========================================

#define UPDATE_MARGIN 1

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int lastReading = 0;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

Macro::Macro(int analogPin)
{
  _analogPin = analogPin;
}

void Macro::begin()
{
  lastReading = analogRead(_analogPin)/8;
}

int Macro::getMacro(){
  int currentReading = readMacro();
  if (abs(currentReading - lastReading) > UPDATE_MARGIN){
    lastReading = currentReading;
  }
  return lastReading;
}

//=====[Implementations of private functions]==================================

int Macro::readMacro(){
  return analogRead(_analogPin)/8;
}
