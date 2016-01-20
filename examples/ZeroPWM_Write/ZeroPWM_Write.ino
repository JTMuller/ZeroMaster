/*
 * ZeroPWM - Library for using digital arduino ports as PWM replacement
 * Created by Julian Muller, November 13, 2015
 */

#include <ZeroMaster.h>

// Define the digital pin that you want to use as PWM pin
ZeroPWM coolingfan(12);

void setup() {
}

void loop() {
// Set a pwm value between 0 and 255 as 0 and 100%
coolingfan.pwmWrite(200);
}
