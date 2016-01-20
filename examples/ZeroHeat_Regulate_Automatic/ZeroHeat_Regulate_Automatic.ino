#include <ZeroMaster.h>
#include <max6675.h>

#define Hpin    9 //Pin of the solid state relay that is controlling the heater.
#define SCKpin 10 //Pins of the MAX6675 board used as Thermocouple for this example.
#define CSpin  11 
#define SOpin  12

double Temp1Set = 100; // Set temperature of the heater. This is the goal to reach.
double Temp1Scan =  0; // Scan temperature of the thermocouple. This is the measured value.

MAX6675 Temp1S(SCKpin, CSpin, SOpin); // Temp1S is the thermocouples name.
ZeroHeat Temp1(Hpin, 2000);           // Temp1 is the heaters name.

void setup() {
}

void loop() {
Temp1Scan = Temp1S.readCelsius(); // Always keep scanning the thermocouple regardless of heating.

int Temp1P = ZeroRegulate(Temp1Set, Temp1Scan);
Temp1.HeatSlow(Temp1P);


}
