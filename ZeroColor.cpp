/*
 * ZeroColor is the class made for the TCS230 and TCS3200 RBG Color Sensors.
 * This class and function simply compiles all 3 colors in one element for an easier code.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

 ZeroColor::ZeroColor(int pinS0, int pinS1, int pinS2, int pinS3, int pinSO, int setting)
 {
	 S0pin = pinS0;
	 S1pin = pinS1;
	 S2pin = pinS2;
	 S3pin = pinS3;
	 SOpin = pinSO;

	 pinMode(S0pin, OUTPUT); digitalWrite(S0pin, LOW);
	 pinMode(S1pin, OUTPUT); digitalWrite(S1pin, LOW);
	 pinMode(S2pin, OUTPUT); digitalWrite(S2pin, LOW);
	 pinMode(S3pin, OUTPUT); digitalWrite(S3pin, LOW);
	 pinMode(SOpin, INPUT);  digitalWrite(SOpin, LOW);

	if (setting == 4) // 100% output
	{
		digitalWrite(S0pin, HIGH);
		digitalWrite(S1pin, HIGH);
	}
	else if (setting == 3) // 20% output
	{
		digitalWrite(S0pin, HIGH);
		digitalWrite(S1pin, LOW);
	}
	else if (setting == 2) // 2% output
	{
		digitalWrite(S0pin, LOW);
		digitalWrite(S1pin, HIGH);
	}
	else if (setting == 1) // 0% output
	{
		digitalWrite(S0pin, LOW);
		digitalWrite(S1pin, LOW);
	}

	TimeDelay = 100; // Delay time of the ReadAll function
 }
 
 void ZeroColor::ChangeSetting(int setting)
 {
	 if (setting == 4) // 100% output
	 {
		 digitalWrite(S0pin, HIGH);
		 digitalWrite(S1pin, HIGH);
	 }
	 else if (setting == 3) // 20% output
	 {
		 digitalWrite(S0pin, HIGH);
		 digitalWrite(S1pin, LOW);
	 }
	 else if (setting == 2) // 2% output
	 {
		 digitalWrite(S0pin, LOW);
		 digitalWrite(S1pin, HIGH);
	 }
	 else if (setting == 1) // 0% output
	 {
		 digitalWrite(S0pin, LOW);
		 digitalWrite(S1pin, LOW);
	 }
 }

 void ZeroColor::Set(char C)
 {
	 if (C == 'R' || C == 'r') // Red color check
	 {
		 digitalWrite(S2pin, LOW);
		 digitalWrite(S3pin, LOW);
	 }
	 else if (C == 'G' || C == 'g') // Green color check
	 {
		 digitalWrite(S2pin, HIGH);
		 digitalWrite(S3pin, HIGH);
	 }
	 else if (C == 'B' || C == 'b') // Blue color check
	 {
		 digitalWrite(S2pin, LOW);
		 digitalWrite(S3pin, HIGH);
	 }
	 else if (C == 'C' || C == 'c') // Clear color check
	 {
		 digitalWrite(S2pin, HIGH);
		 digitalWrite(S3pin, LOW);
	 } 
 }

 int ZeroColor::Read()
 {
	 ColorFreq = pulseIn(SOpin, LOW);
     return ColorFreq;
 }

 void ZeroColor::ReadAll(int RFreq, int GFreq, int BFreq, int CFreq)
 {
	 bool Continue = true;
	 unsigned long CTime = millis();
	 byte Color = 1;

	 Start:

	 if (CTime - COldTime >= TimeDelay && Color == 1)
	 {
		 COldTime = CTime;
		 digitalWrite(S2pin, LOW);
		 digitalWrite(S3pin, LOW);
		 RFreq = pulseIn(SOpin, LOW);
		 Color = 2; // Green next
	 }
	 if (CTime - COldTime >= TimeDelay && Color == 2)
	 {
		 COldTime = CTime;
		 digitalWrite(S2pin, HIGH);
		 digitalWrite(S3pin, HIGH);
		 GFreq = pulseIn(SOpin, LOW);
		 Color = 3; // Blue next
	 }
	 if (CTime - COldTime >= TimeDelay && Color == 3)
	 {
		 COldTime = CTime;
		 digitalWrite(S2pin, LOW);
		 digitalWrite(S3pin, HIGH);
		 BFreq = pulseIn(SOpin, LOW);
		 Color = 4; // Clear next
	 }
	 if (CTime - COldTime >= TimeDelay && Color == 4)
	 {
		 COldTime = CTime;
		 digitalWrite(S2pin, HIGH);
		 digitalWrite(S3pin, HIGH);
		 CFreq = pulseIn(SOpin, LOW);
		 Color = 1; // Red next
		 Continue = false;
	 }

	 if (Continue)
	 {
		 goto Start;
	 }
 }


