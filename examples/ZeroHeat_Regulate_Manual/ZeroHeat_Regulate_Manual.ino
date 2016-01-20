#include <ZeroMaster.h>
#include <max6675.h>

#define Hpin    9 //Pin of the solid state relay that is controlling the heater.
#define SCKpin 10 //Pins of the MAX6675 board used as Thermocouple for this example.
#define CSpin  11 
#define SOpin  12

double Temp1Set = 100; // Set temperature of the heater. This is the goal to reach.
double Temp1Scan =  0; // Scan temperature of the thermocouple. This is the measured value.
byte Temp1Peak =    0; // Peak switch for initial control.

MAX6675 Temp1S(SCKpin, CSpin, SOpin); // Temp1S is the thermocouples name.
ZeroHeat Temp1(Hpin, 2000);           // Temp1 is the heaters name.

void setup() {
}

void loop() {
Temp1Scan = Temp1S.readCelsius(); // Always keep scanning the thermocouple regardless of heating.

if (Temp1Peak == 0)
{ 
  if (Temp1Scan < (Temp1Set - 40))
  {Temp1.HeatSlow(100);}
  else if (Temp1Scan < (Temp1Set - 25))
  {Temp1.HeatSlow(75);}
  else if (Temp1Scan < (Temp1Set - 10))
  {Temp1.HeatSlow(50);}
  else if (Temp1Scan <=(Temp1Set - 1))
  {Temp1.HeatSlow(25);}
  else if (Temp1Scan > (Temp1Set - 1))
  {Temp1Peak = 1;}
}
else if (Temp1Peak == 1)
{
  if (Temp1Scan > (Temp1Set + 1))
  {Temp1.HeatSlow(0);}
  else if (Temp1Scan < (Temp1Set - 3))
  {Temp1.HeatSlow(100);}
  else if (Temp1Scan < (Temp1Set - 2))
  {Temp1.HeatSlow(75);}
  else if (Temp1Scan < (Temp1Set - 1))
  {Temp1.HeatSlow(50);}
  else if (Temp1Scan > (Temp1Set - 1) && Temp1Scan < (Temp1Set + 1))
  {Temp1.HeatSlow(25);}
}

}
