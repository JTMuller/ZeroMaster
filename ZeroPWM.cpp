/*
 * ZeroPWM is used for any digital pin that should function as PWM.
 * This class and function simulate a PWM wave. The cycletime is set as 2000 Microseconds. 
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

ZeroPWM::ZeroPWM(int pin)
  {
  pwmpin = pin;
  pinMode(pwmpin, OUTPUT);
  PWMOldTime = 0;
  Value = 0;
  c = 2000;
  }
 
void ZeroPWM::pwmWrite(int x)
  {
  x2 = x*20;
  if (x >= 100) {digitalWrite(pwmpin, HIGH);}
  else if (x <= 0) {digitalWrite(pwmpin, LOW);}
  else {  
  unsigned long PWMTime = micros();
  
  if(PWMTime - PWMOldTime >= (c-x2) && Value == 0) {
  PWMOldTime = PWMTime; 
  digitalWrite(pwmpin, HIGH);
  Value = 1;}

  if(PWMTime - PWMOldTime >= x2 && Value == 1) {
  PWMOldTime = PWMTime; 
  digitalWrite(pwmpin, LOW);
  Value = 0;}    
  }
  }
