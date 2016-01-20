/*
 * ZeroHeat - Library for using SSR heaters with a simple % ontime control.
 * Created by Julian Muller, December 1, 2015
 */

#include <ZeroMaster.h>

// Define the digital pin that you want to use for your heater
// Also defines the cycle in millis (for HeatSlow) or micros (for Heat)
// Lastly defines reverse as true or false. True means that HIGH = 0% and LOW = 100%
ZeroHeat SSR1(4, 1000, false); // The cycletime is 1 second

void setup() {
}

void loop() {
// Set a control value between 0 and 100%
// When using micros as cycle, use one of these functions based on your solid state response
//SSR1.HeatFast(40); // Heat for 40%
// When using millis as cycle, use one of these functions based on your solid state response
SSR1.Heat(40); // Heat for 40%
}
