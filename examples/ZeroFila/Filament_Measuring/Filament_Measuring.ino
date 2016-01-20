/*
 * ZeroFila.h - Library for filament measurement devices for the 3Devo NEXT 1.0
 * Created by Julian Muller, December 22, 2015
 */

#include <ZeroMaster.h>

// Define the SI, SCK, AO1 pins
ZeroFila Filament(10,9,A0);

void setup()
{
Serial.begin(9600);
}

void loop()
{
// put the readout in a variable.
double X = Filament.FilaRead();

// A heavier setup reading 5 times and taking an average.
//double X = Filament.FilaRead5();

Serial.println(X);
}

