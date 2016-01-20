/*
 * ZeroHeat-Regulate - A special function to control the input % for heaters.
 * Created by Julian Muller, December 8, 2015
 */
 
#include <ZeroMaster.h>

#define Hpin    4 //Pin of the solid state relay that is controlling the heater.

double TSet = 100; // Set temperature of the heater. This is the goal to reach.
double TScan = 94; // Scan temperature of the thermocouple. This is the measured value.
int RegVal = 0; // The regulation value. 0 = OFF, 100 = Full power
// for testing purposes, just fill in the Temp1Scan with any value.
// When using an thermistor, let it's value go to Temp1Scan for automatisation.

ZeroHeat Temp1(Hpin, 2000);           // Temp1 is the heaters name.

void setup() {
}

void loop() {
// Regulation on several different points. This can be extended and more dettailed.
// This testversion is very simple because most of the time, more complicated versions are not needed.
if      (TScan >= TSet + 1 ) // f.e. 101
{RegVal = 0;  }
else if (TScan <= TSet + 1 && TScan > TSet) // f.e. 100-101
{RegVal = 25; }
else if (TScan <= TSet && TScan > TSet - 10) // f.e. 90-100
{RegVal = 50; }
else if (TScan <= TSet - 10 && TScan > TSet - 30) // f.e. 70-90
{RegVal = 75; }
else if (TScan <= TSet - 30) // f.e. 0-70
{RegVal = 100;}

Temp1.Heat(RegVal);
}
