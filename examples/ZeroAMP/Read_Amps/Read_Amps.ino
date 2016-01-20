/*
 * ZeroAMP.h - Library for using Ampere measurement devices for the 3Devo NEXT 1.0
 * Created by Julian Muller, November 30, 2015
 */

#include <ZeroMaster.h>

// Define the output pin of the ampere measurement device
ZeroAMP amp(A3);

void setup() {
Serial.begin(9600);
}

void loop() {
// Write the readout as serial value
double Value = amp.EXA();
Serial.println(Value);
}
