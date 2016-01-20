/*
 * ZeroMaster.h - Library for using several devices for the 3Devo NEXT 1.0
 * Created by Julian Muller, November 30, 2015
 */

#ifndef ZEROMASTER_H
#define ZEROMASTER_H


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

/*
 * ZeroLED is the class made for RBG LED Strips.
 * This class and function simply compiles all 3 colors in one element for an easier code.
 */

class ZeroLED
{
 int Rpin;
 int Gpin;
 int Bpin;
  
 public:
 ZeroLED(int Rpin, int Gpin, int Bpin)
 {
 int R;
 int G;
 int B; 
 pinMode(Rpin, OUTPUT); analogWrite(Rpin, 0);
 pinMode(Gpin, OUTPUT); analogWrite(Gpin, 0);
 pinMode(Bpin, OUTPUT); analogWrite(Bpin, 0);
 }
 
 void Shine(int R, int G, int B)
 {  
 analogWrite(Rpin, R);
 analogWrite(Gpin, G);
 analogWrite(Bpin, B);  
 }
};


/*
 * ZeroAMP is used for ACS712 Ampere meters.
 * This class and function read the amps and stabilise a part of the static.
 */

class ZeroAMP
{
  int amppin;
  double ARead;
  double AMath;
  double ACalc;
  unsigned long ATime2;
  double ARead2;
  int count;

  public:
  ZeroAMP(int pin)
  {
  amppin = pin;
  pinMode(amppin, INPUT);     
  ARead  = 0;
  AMath  = 0;
  ACalc  = 0;
  ATime2 = 0;
  ARead2 = 0;
  count  = 0;
  }
 
  double EXA()
  {
  unsigned long ATime = millis() - ATime2;
  if (ATime > 500)
   {
   ARead = analogRead(amppin);
   ARead2 = ARead2  + ARead;
   count = count + 1;
   ATime2 = ATime;
   }

  if (count >= 1000)
   {
   ARead = ARead2 / count;
   AMath = (ARead / 1023.0) * 5000;
   ACalc = ((AMath - 2500) / 66) / 1.85;
   count = 0;
   ARead2 = 0;
   }
  return ACalc;
  } 
};


/*
 * ZeroPWM is used for any digital pin that should function as PWM.
 * This class and function simulate a PWM wave. The cycletime is set as 2000 Microseconds. 
 */

class ZeroPWM
{
  int pwmpin;
  byte Value;
  unsigned long PWMOldTime;
  int c;
  int x2;
  
  public:
  ZeroPWM(int pin)
  {
  pwmpin = pin;
  pinMode(pwmpin, OUTPUT);
  PWMOldTime = 0;
  Value = 0;
  c = 2000;
  }
 
  void pwmWrite(int x)
  {
  x2 = x*20;
  if (x2 > c) {digitalWrite(pwmpin, HIGH);}
  else if (x2 < 0) {digitalWrite(pwmpin, LOW);}
  else {  
  unsigned long PWMTime = micros();
  
  if(PWMTime - PWMOldTime >= (c-x2) && Value == 0) {
  PWMOldTime = PWMTime; 
  digitalWrite(pwmpin, HIGH);
  Value = 1;}

  if(PWMTime - PWMOldTime >= x2 && Value == 1) {
  PWMOldTime = PWMTime; 
  digitalWrite(pwmpin, LOW);
  Value = 0;}    
  }
  }
};

/*
 * ZeroHeat is a variation of ZeroPWM used for solid state relays.
 * This class and function allows the user to set the cycletime themselves and allows them to use either millis or micro's
 */

class ZeroHeat
{
  int heatpin;
  byte Value;
  unsigned long HeatOldTime;
  int c;
  int x2;
  
  public:
  ZeroHeat(int pin, int cycle)
  {
  heatpin = pin;
  pinMode(heatpin, OUTPUT);
  HeatOldTime = 0;
  Value = 0;
  c = cycle;
  }
 
  void Heat(int x)
  {
  x2 = x*(c / 100);
  if (x2 > c) {digitalWrite(heatpin, HIGH);}
  else if (x2 < 0) {digitalWrite(heatpin, LOW);}
  else {  
  unsigned long HeatTime = micros();
  
  if(HeatTime - HeatOldTime >= (c-x2) && Value == 0) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, HIGH);
  Value = 1;}

  if(HeatTime - HeatOldTime >= x2 && Value == 1) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, LOW);
  Value = 0;}    
  }
  }

  void HeatSlow(int x)
  {
  x2 = x*(c / 100);
  if (x2 > c) {digitalWrite(heatpin, HIGH);}
  else if (x2 < 0) {digitalWrite(heatpin, LOW);}
  else {  
  unsigned long HeatTime = millis();
  
  if(HeatTime - HeatOldTime >= (c-x2) && Value == 0) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, HIGH);
  Value = 1;}

  if(HeatTime - HeatOldTime >= x2 && Value == 1) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, LOW);
  Value = 0;}    
  }
  }
};

/*
 * ZeroRegulate is there to regulate heaters. It works together with ZeroHeat.
 * This function converts the input Set and Scanned temperature values into a heat% to be used by ZeroHeat.
 */

double ZeroRegulate(double Temp1Set, double Temp1Scan)
{
#ifndef Temp1Peak
byte Temp1Peak = 0;
#endif
int Temp1;

if (Temp1Peak == 0)
{ 
  if (Temp1Scan < (Temp1Set - 40))
  {Temp1 = 100;}
  else if (Temp1Scan < (Temp1Set - 25))
  {Temp1 = 75;}
  else if (Temp1Scan < (Temp1Set - 10))
  {Temp1 = 50;}
  else if (Temp1Scan <=(Temp1Set - 1))
  {Temp1 = 25;}
  else if (Temp1Scan > (Temp1Set - 1))
  {Temp1Peak = 1;}
}
else if (Temp1Peak == 1)
{
  if (Temp1Scan > (Temp1Set + 1))
  {Temp1 = 0;}
  else if (Temp1Scan < (Temp1Set - 3))
  {Temp1 = 100;}
  else if (Temp1Scan < (Temp1Set - 2))
  {Temp1 = 75;}
  else if (Temp1Scan < (Temp1Set - 1))
  {Temp1 = 50;}
  else if (Temp1Scan > (Temp1Set - 1) && Temp1Scan < (Temp1Set + 1))
  {Temp1 = 25;}
}

return Temp1;
}

#endif