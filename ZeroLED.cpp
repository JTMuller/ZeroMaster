/*
 * ZeroLED is the class made for RBG LED Strips.
 * This class and function simply compiles all 3 colors in one element for an easier code.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

 ZeroLED::ZeroLED(int RpinI, int GpinI, int BpinI)
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
 
 void ZeroLED::Shine(int R, int G, int B)
 {
 double Rc = R * 2.55;
 double Gc = G * 2.55;
 double Bc = B * 2.55; 
 analogWrite(Rpin, Rc);
 analogWrite(Gpin, Gc);
 analogWrite(Bpin, Bc);  
 }

 void ZeroLED::DigiShine(int R, int G, int B)
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


