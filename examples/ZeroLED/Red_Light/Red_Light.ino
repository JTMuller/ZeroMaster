/*
 * ZeroLED.h - Library for using RGB LEDStrips for the 3Devo NEXT 1.0
 * Created by Julian Muller, November 26, 2015
 */

#include <ZeroMaster.h>

// Define the R, G and B pins of your ledstrip
ZeroLED led(10,11,12); 

void setup() {
}

void loop() {
// Give the strip values of RGB. 0 is off, 100 is maximum.
//Make sure to use PWM ports for the best results  
led.Shine(100,0,0);
//When not using PWM ports, use this line instead
led.DigiShine(100,0,0);
}
