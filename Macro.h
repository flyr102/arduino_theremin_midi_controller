//=====[#include guards - begin]===============================================

#ifndef MACRO_H_
#define MACRO_H_

#include "Arduino.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

class Macro
{
  public:
    Macro(int analogPin);
    void begin();
    int getMacro();
  private:
    int _analogPin;
    int lastReading;
    int readMacro();
};

//=====[#include guards - end]=================================================

#endif // _MACRO_H_