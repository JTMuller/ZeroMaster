/*
 * ZeroHeat-Regulate - A special function to control the input % for heaters.
 * Created by Julian Muller, Januari 19, 2016
 */

#include <ZeroMaster.h>

#define HeatPin 4 //Pin of the solid state relay that is controlling the heater.
#define SCKpin 10 //Pins of the MAX6675 / MAX31855 board used as Thermocouple for this example.
#define CSpin  11 
#define SOpin  12

double Temp1Set  =100; // Set temperature of the heater. This is the goal to reach.
double Temp1Scan =  0; // Scan temperature of the thermocouple. This is the measured value.
byte   Temp1Reg  =  0; // Regulated % value 0-100%.

#define OSBig  20
#define OSMin   2

//Zero31855 Temp1S(SCKpin,CSpin,SOpin); // When using 31855 use this function, when using 6675, keep this commented.
Zero6675 Temp1S(SCKpin, CSpin, SOpin); // Temp1S is the thermocouples name.
ZeroHeat Temp1(HeatPin, 2000);        // Temp1 is the heaters name.

void setup() {
Serial.begin(9600);
}

void loop() {
//Temp1Scan = Temp1S.HeatRead2(); // When using 31855, use this function instead.
Temp1Scan = Temp1S.HeatRead();

/* Use your the following values in this order
 * Variable Set Value
 * Variable Scan Value
 * Constant offset from the set value for the first step (in this example 80)
 * Constant offset from the set value for the second step (in this example 98)
 * % return when under Set - big offset
 * % return when under Set - small offset
 * # return when under Set
 * # return when Set or higher
 */
 
Temp1Reg = Temp1.HeatRegulate(Temp1Set, Temp1Scan, OSBig, OSMin, 100, 30, 10, 0);
Temp1.Heat(Temp1Reg);
Serial.println(Temp1Reg);
}
