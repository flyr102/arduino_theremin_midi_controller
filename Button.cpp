//=====[Libraries]=============================================================

#include "arduino.h"
#include "button.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
   WAIT,
   BUTTON_PRESSED,
   BUTTON_RELEASED
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

buttonState_t buttonState;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

Button::Button(int digitalPin)
{
  _digitalPin = digitalPin;
}

void Button::begin()
{
  pinMode(_digitalPin, INPUT);
}

bool Button::buttonEventUpdate(){
  return buttonStateUpdate();
}

int Button::read(){
  return digitalRead(_digitalPin);
}


//=====[Implementations of private functions]==================================

static bool Button::buttonStateUpdate(){ 
   switch(buttonState){
       case WAIT :
           if(this -> read() == 1){
               buttonState = BUTTON_PRESSED;
           }
       break;

       case BUTTON_PRESSED :
       
           if(this -> read() == 0){
               buttonState = BUTTON_RELEASED;
           }
       break;
    
       case BUTTON_RELEASED :
           buttonState = WAIT;
           return true;
       break;
   }
   return false;
}