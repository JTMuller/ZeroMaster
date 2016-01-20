/*
 * ZeroHeat - Library for using SSR heaters with a simple % ontime control.
 * Created by Julian Muller, December 1, 2015
 */

#include <ZeroMaster.h>

// Define the digital pin that you want to use for your heater
// Also defines the cycle in millis (for HeatSlow) or micros (for Heat). in this case, the cycle is 1 second.
ZeroHeat SSR1(4, 1000);

void setup() {
}

void loop() {
// Set a control value between 0 and 100%
// When using micros as cycle, use one of these functions based on your solid state response
//SSR1.HeatFast(40); // HIGH = 100%
//SSR1.HeatFastReverse(40); // HIGH = 0%
// When using millis as cycle, use one of these functions based on your solid state response
SSR1.Heat(40); // HIGH = 100%
//SSR1.HeatReverse(40); // HIGH = 0%
}
