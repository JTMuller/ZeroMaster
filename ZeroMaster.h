/*
 * ZeroMaster.h - Library for using several devices for the 3Devo NEXT 1.0
 * Created by Julian Muller, November 30, 2015
 * Last updated on December 28, 2015
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
 int Rpin; int Gpin; int Bpin;
 byte RValue; byte GValue; byte BValue;
 unsigned long ROldTime; unsigned long GOldTime; unsigned long BOldTime;
 int R; int G; int B; 
 int R2; int G2; int B2;
 int LEDc;
  
 public:
 ZeroLED(int RpinI, int GpinI, int BpinI)
 {
 Rpin = RpinI; 
 Gpin = GpinI;
 Bpin = BpinI;
 pinMode(Rpin, OUTPUT); analogWrite(Rpin, 0);
 pinMode(Gpin, OUTPUT); analogWrite(Gpin, 0);
 pinMode(Bpin, OUTPUT); analogWrite(Bpin, 0);
 ROldTime = 0; RValue = 0;
 GOldTime = 0; GValue = 0; 
 BOldTime = 0; BValue = 0;
 LEDc = 2000; 
 }
 
 void Shine(int R, int G, int B)
 {
 double Rc = R * 2.55;
 double Gc = G * 2.55;
 double Bc = B * 2.55; 
 analogWrite(Rpin, Rc);
 analogWrite(Gpin, Gc);
 analogWrite(Bpin, Bc);  
 }

 void DigiShine(int R, int G, int B)
 {
  R2 = R*20; G2 = G*20; B2 = B*20;
  if (R >= 100) {digitalWrite(Rpin, HIGH);}
  else if (R <= 0) {digitalWrite(Rpin, LOW);}
  else {
  unsigned long RTime = micros();
  
  if(RTime - ROldTime >= (LEDc-R2) && RValue == 0) 
  {ROldTime = RTime; digitalWrite(Rpin, HIGH); RValue = 1;}
  if(RTime - ROldTime >= R2 && RValue == 1) 
  {ROldTime = RTime; digitalWrite(Rpin, LOW); RValue = 0;}    
  }
  
  if (B >= 100) {digitalWrite(Bpin, HIGH);}
  else if (B <= 0) {digitalWrite(Bpin, LOW);}
  else {
  unsigned long BTime = micros();
  
  if(BTime - BOldTime >= (LEDc-B2) && BValue == 0) 
  {BOldTime = BTime; digitalWrite(Bpin, HIGH); BValue = 1;}
  if(BTime - BOldTime >= B2 && BValue == 1) 
  {BOldTime = BTime; digitalWrite(Bpin, LOW); BValue = 0;}    
  }
  
  if (G >= 100) {digitalWrite(Gpin, HIGH);}
  else if (G <= 0) {digitalWrite(Gpin, LOW);}
  else {
  unsigned long GTime = micros();
  
  if(GTime - GOldTime >= (LEDc-G2) && GValue == 0) 
  {GOldTime = GTime; digitalWrite(Gpin, HIGH); GValue = 1;}
  if(GTime - GOldTime >= G2 && GValue == 1) 
  {GOldTime = GTime; digitalWrite(Gpin, LOW); GValue = 0;}    
  }  
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
  if (x >= 100) {digitalWrite(pwmpin, HIGH);}
  else if (x <= 0) {digitalWrite(pwmpin, LOW);}
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
 
  void HeatFast(int x)
  {
  x2 = x*(c / 100);
  if (x >= 100) {digitalWrite(heatpin, HIGH);}
  else if (x <= 0) {digitalWrite(heatpin, LOW);}
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
  }  }

  void HeatFastReverse(int x)
  {
  x2 = x*(c / 100);
  if (x >= 100) {digitalWrite(heatpin, LOW);}
  else if (x <= 0) {digitalWrite(heatpin, HIGH);}
  else {  
  unsigned long HeatTime = micros();
  
  if(HeatTime - HeatOldTime >= (c-x2) && Value == 0) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, LOW);
  Value = 1;}

  if(HeatTime - HeatOldTime >= x2 && Value == 1) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, HIGH);
  Value = 0;}    
  }  }

  void Heat(int x)
  {
  x2 = x*(c / 100);
  if (x >= 100) {digitalWrite(heatpin, HIGH);}
  else if (x <= 0) {digitalWrite(heatpin, LOW);}
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
  }  }

  void HeatReverse(int x)
  {
  x2 = x*(c / 100);
  if (x >= 100) {digitalWrite(heatpin, LOW);}
  else if (x <= 0) {digitalWrite(heatpin, HIGH);}
  else {  
  unsigned long HeatTime = millis();
  
  if(HeatTime - HeatOldTime >= (c-x2) && Value == 0) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, LOW);
  Value = 1;}

  if(HeatTime - HeatOldTime >= x2 && Value == 1) {
  HeatOldTime = HeatTime; 
  digitalWrite(heatpin, HIGH);
  Value = 0;}    
  }  }
};

/*
 * ZeroRegulate is there to regulate heaters. It works together with ZeroHeat.
 * This function converts the input Set and Scanned temperature values into a heat% to be used by ZeroHeat.
 */

double HeatRegulate(double TSet, double TScan)
{
int RegVal;
  
if      (TScan >= TSet + 1 )
{RegVal = 0;  }
else if (TScan <= TSet + 1 && TScan > TSet)
{RegVal = 25; }
else if (TScan <= TSet && TScan > TSet - 10)
{RegVal = 50; }
else if (TScan <= TSet - 10 && TScan > TSet - 30)
{RegVal = 75; }
else if (TScan <= TSet - 30)
{RegVal = 100;}

return RegVal;
}

/*
 * ZeroFila is a library that controls a TSL1401CL sensor to measure filament width.
 * This class and function will convert light input into a width value.
 */

class ZeroFila
{
int pinCLK;   
int pinSI;   
int pinAO1;
int IntArray[128]; // <-- the array where the readout of the photodiodes is stored, as integers
int LightMax;
int LightMin;
double Filamentwidth;
double SensorStep;
double FSA[5];

public:
ZeroFila(int SI, int CLK, int AO1)
  {
  pinSI  = SI;
  pinCLK =CLK;   
  pinAO1 =AO1;
  LightMax = 0;
  LightMin = 1024;
  Filamentwidth = 0.0;
  SensorStep = 44.9; //  44.9 for TSL1401CL,      63.5 for TSL1402R
  pinMode(pinCLK, OUTPUT);   digitalWrite(pinCLK, LOW);
  pinMode(pinSI,  OUTPUT);   digitalWrite(pinSI, LOW);
  digitalWrite(pinSI, HIGH); digitalWrite(pinCLK, HIGH);  
  digitalWrite(pinCLK, LOW); digitalWrite(pinSI, LOW);
  }

  double FS() 
  {
  digitalWrite(pinSI, HIGH);  digitalWrite(pinCLK, HIGH);   
  digitalWrite(pinCLK, LOW);  digitalWrite(pinSI, LOW);

  for(int i=0; i < 128; i++)
   {   IntArray[i] = analogRead(pinAO1);
       digitalWrite(pinCLK, HIGH);   digitalWrite(pinCLK, LOW); 
   }
  digitalWrite(pinSI, HIGH);  digitalWrite(pinCLK, HIGH);   
  digitalWrite(pinCLK, LOW);  digitalWrite(pinSI, LOW);

  for(int i = 0; i < 128; i++)
   {  
   if(LightMax<IntArray[i]){LightMax=IntArray[i];}
   if(LightMin>IntArray[i]){LightMin=IntArray[i];}
   digitalWrite(pinCLK, HIGH);   digitalWrite(pinCLK, LOW);
   }
   
  int iR, iL;
  int ttLevel = ( LightMax-LightMin>256 ? LightMin+(LightMax-LightMin)/3 : 0 ); //if dynamic levels are not far enough apart, we won't measure
  iL=20;  while ( (iL<=120) && (IntArray[iL]>ttLevel) ) { iL++; }
  iR=120; while ( (iR>=20 ) && (IntArray[iR]>ttLevel) ) { iR--; }
  Filamentwidth = 0.0;
  if ( iL<iR ) { Filamentwidth =  double( iR-iL ) * SensorStep / 1000.0 ; }  
  }

  double FilaRead()
  {
  FSA[0] = FS();
  FSA[1] = FS();
  FSA[2] = FS();
  FSA[3] = FS();
  FSA[4] = FS();
  double FSR = (FSA[0]+FSA[1]+FSA[2]+FSA[3]+FSA[4]) / 5;
  return FSR;
  }
};

#endif