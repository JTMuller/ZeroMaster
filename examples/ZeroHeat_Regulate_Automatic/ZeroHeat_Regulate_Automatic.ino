/*
 * ZeroHeat-Regulate - A special function to control the input % for heaters.
 * Created by Julian Muller, December 8, 2015
 */

#include <ZeroMaster.h>
#include <max6675.h>

#define Hpin    4 //Pin of the solid state relay that is controlling the heater.
#define SCKpin 10 //Pins of the MAX6675 board used as Thermocouple for this example.
#define CSpin  11 
#define SOpin  12

double Temp1Set = 100; // Set temperature of the heater. This is the goal to reach.
double Temp1Scan =  0; // Scan temperature of the thermocouple. This is the measured value.
int Temp1Reg = 0; //
MAX6675 Temp1S(SCKpin, CSpin, SOpin); // Temp1S is the thermocouples name.
ZeroHeat Temp1(Hpin, 2000);           // Temp1 is the heaters name.

void setup() {
Serial.begin(9600);
}

void loop() {
Temp1Scan = Temp1S.readCelsius(); // Always keep scanning the thermocouple regardless of heating.

Temp1Reg = HeatRegulate(Temp1Set, Temp1Scan);
Temp1.Heat(Temp1Reg);
Serial.println(Temp1Reg);
}
