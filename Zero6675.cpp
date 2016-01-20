/*
 * Zero6675 is a converted version of the adafruit MAX6675 library where no delays are used.
 * This class and function will read the MAX6675 value and and convert it to celsius.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

Zero6675::Zero6675(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);
  digitalWrite(cs, HIGH);
}
double Zero6675::HeatRead() {

  uint16_t v;
  digitalWrite(cs, LOW);
  v = SPIRead();
  v <<= 8;
  v |= SPIRead();
  digitalWrite(cs, HIGH);
  if (v & 0x4) {
    return NAN; // No signal
  }
  v >>= 3;
  return v*0.25;
}

byte Zero6675::SPIRead() { 
  int i;
  byte d = 0;
  
  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    if (digitalRead(miso)) {
      d |= (1 << i); //set the bit to 0 no matter what
    }
    digitalWrite(sclk, HIGH);
  }
  return d;
}