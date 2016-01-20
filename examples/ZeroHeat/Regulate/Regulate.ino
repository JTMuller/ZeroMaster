/*
 * ZeroHeat-Regulate - A special function to control the input % for heaters.
 * Created by Julian Muller, December 8, 2015
 */

#include <ZeroMaster.h>

#define Hpin    4 //Pin of the solid state relay that is controlling the heater.
#define SCKpin 10 //Pins of the MAX6675 board used as Thermocouple for this example.
#define CSpin  11 
#define SOpin  12

#define Reg0    0 //
#define Reg1   25 //
#define Reg2   50 // The values of the steps in % on. 
#define Reg3   75 //
#define Reg4  100 //

double Temp1Set = 100; // Set temperature of the heater. This is the goal to reach.
double Temp1Scan =  0; // Scan temperature of the thermocouple. This is the measured value.
int Temp1Reg = 0; //
//Zero31855 Temp1S(SCKpin,CSpin,SOpin); // When using 31855 use this function, when using 6675, keep this commented.
Zero6675 Temp1S(SCKpin, CSpin, SOpin); // Temp1S is the thermocouples name.
ZeroHeat Temp1(Hpin, 2000);           // Temp1 is the heaters name.

void setup() {
Serial.begin(9600);
}

void loop() {
//Temp1Scan = Temp1S.HeatRead2(); // When using 31855, use this function instead.
Temp1Scan = Temp1S.HeatRead();

// Regulation on several different points. This can be extended and more dettailed.
// This testversion is very simple because most of the time, more complicated versions are not needed.
if      (Temp1Scan >= Temp1Set + 1 ) // f.e. 101
{Temp1Reg = Reg0;  }
else if (Temp1Scan <= Temp1Set + 1 && Temp1Scan > Temp1Set) // f.e. 100-101
{Temp1Reg = Reg1; }
else if (Temp1Scan <= Temp1Set && Temp1Scan > Temp1Set - 10) // f.e. 90-100
{Temp1Reg = Reg2; }
else if (Temp1Scan <= Temp1Set - 10 && Temp1Scan > Temp1Set - 30) // f.e. 70-90
{Temp1Reg = Reg3; }
else if (Temp1Scan <= Temp1Set - 30) // f.e. 0-70
{Temp1Reg = Reg4;}

Temp1.Heat(Temp1Reg);
Serial.println(Temp1Reg);
}
