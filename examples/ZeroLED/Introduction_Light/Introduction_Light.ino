/*
 * ZeroLED.h - Library for using RGB LEDStrips for the 3Devo NEXT 1.0
 * Created by Julian Muller, November 26, 2015
 */

#include <ZeroMaster.h>

// Define the timer for each step in milliseconds. Remember that the system has 300 steps.
#define Delay 25

// Define the R, G and B pins of your ledstrip
ZeroLED led(10,11,12);
byte Red   = 0;
byte Green = 0;
byte Blue  = 0;


void setup() {
while (Red < 100) // Start the RED LED first
 {
 led.Shine(Red,0,0);
 delay(Delay);
 Red++;
 }
while (Green < 100) // Start the GREEN LED second
 {
 led.Shine(Red,Green,0);
 delay(Delay);
 Green++;
 }
while (Blue < 100) // Start the BLUE LED last
 {
 led.Shine(Red,Green,Blue);
 delay(Delay);
 Blue++;
 }

}

void loop() {
// Shine all the LEDs
led.Shine(100,100,100);

}
