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
//Make sure to use PWM ports for the best results.
//Replace Shine with DigiShine when not using PWM ports.
led.Shine(100,0,0); // Red
delay(1000);
led.Shine(0,100,0); // Green
delay(1000);
led.Shine(0,0,100); // Blue
delay(1000);
led.Shine(100,100,0); // Brown
delay(1000);
led.Shine(0,100,100); // Lightgreen
delay(1000);
led.Shine(100,0,100);
delay(1000);
led.Shine(100,100,100);
delay(1000);
led.Shine(0,0,0);
delay(1000);
}
