/*
  Button.h - Library for button inputs with debouncing.
  Created by Conor Fryer 20240310.
*/
//=====[#include guards - begin]===============================================

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

class Button
{
  public:
    Button(int digitalPin);
    void begin();
    bool buttonEventUpdate();
    int read();
  private:
    int _digitalPin;
    bool buttonStateUpdate();
};

//=====[#include guards - end]=================================================

#endif // _BUTTON_H_