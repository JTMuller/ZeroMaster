/*
 * ZeroBuzz is used for Piezo Buzzers on a PWM pin.
 * This class and function create an error signal to hear when something is wrong. 
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

ZeroBuzz::ZeroBuzz(int pin)
  {
  BuzzPin = pin;
  pinMode(BuzzPin, OUTPUT);
  BuzzOldTime = 0;
  Value = 0;
  }
 
void ZeroBuzz::Pulse(int x)
  {
  BuzzTime = millis();
   if (Value == 1)
   { tone(BuzzPin, x, 150); }

   if (BuzzTime > 500 + BuzzOldTime)
   { if (Value == 1) {Value = 0;} else {Value = 1;}
   BuzzOldTime = BuzzTime; 
   }
  }
