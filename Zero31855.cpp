/*
 * Zero31855 is a converted version of the adafruit MAX31855 library where no delays are used.
 * This class and function will read the MAX31855 value and and convert it to celsius.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

Zero31855::Zero31855(int8_t PSCLK, int8_t PCS, int8_t PMISO) {
  sclk = PSCLK;
  cs = PCS;
  miso = PMISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);
  digitalWrite(cs, HIGH);
}

double Zero31855::HeatRead2() {
  int32_t v;
  v = SPIRead2();
  if (v & 0x7) {
    return NAN; // No signal
  }

  if (v & 0x80000000) {
    v = 0xFFFFC000 | ((v >> 18) & 0x00003FFFF);
  }
  else {
    v >>= 18;
  }
  double centigrade = v;
  centigrade *= 0.25;
  return centigrade;
}

uint32_t Zero31855::SPIRead2() { 
  int i;
  uint32_t d = 0;

  digitalWrite(sclk, LOW);
  digitalWrite(cs, LOW);
  for (i=31; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    delay(1);
    d <<= 1;
    if (digitalRead(miso)) {
      d |= 1;
    }
    digitalWrite(sclk, HIGH);
  }
  digitalWrite(cs, HIGH);
  return d;
}