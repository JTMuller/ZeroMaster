/*
 * ZeroAMP is used for ACS712 Ampere meters.
 * This class and function read the amps and stabilise a part of the static.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

ZeroAMP::ZeroAMP(int pin)
  {
  amppin = pin;
  pinMode(amppin, INPUT);     
  ARead  = 0;
  AMath  = 0;
  ACalc  = 0;
  ATime2 = 0;
  ARead2 = 0;
  count  = 0;
  }
 
  double ZeroAMP::Amps()
  {
  unsigned long ATime = millis() - ATime2;
  if (ATime > 500)
   {
   ARead = analogRead(amppin);
   ARead2 = ARead2  + ARead;
   count = count + 1;
   ATime2 = ATime;
   }

  if (count >= 20)
   {
   ARead = ARead2 / count;
   AMath = (ARead / 1023.0) * 5000;
   ACalc = ((AMath - 2500) / 66) / 1.85;
   count = 0;
   ARead2 = 0;
   }
  return ACalc;
  } 

  double ZeroAMP::EXA()
  {
  ARead = analogRead(amppin);
  AMath = (ARead / (double)1023) * (double)5;
  ACalc = (((AMath - (double)2.5)/(double)0.066)*-1);
  return ACalc;
  }