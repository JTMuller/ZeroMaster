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

class ZeroAMP
{
  int amppin;
  double EXAT_A1;
  double EXAT_A2;
  double EXAT_A3;
  double EXAT_A4;
  double EXAT_A5;
  double EXAT_A6;
  double EXAT_A7;
  double EXAT_A8;
  double EXAT_A9;
  double EXAT_A10;
  double EXAT_A11;
  double EXAT_A12;
  double EXAT_A13;
  double EXAT_A14;
  double EXAT_A15;
  double EXAT_A16;
  double EXAT_A17;
  double EXAT_A18;
  double EXAT_A19;
  double EXAT_A20;
  double EXAT_ARead;
  double EXAT_ACalc;
  unsigned long EXAT_OldTime;

  public:
  ZeroAMP(int pin)
  {
  amppin = pin;
  pinMode(amppin, INPUT);     
  EXAT_OldTime = 0;
  }
 
  double EXA()
  {
  unsigned long EXAT_Timer = millis() - EXAT_OldTime;
  if (EXAT_Timer > 25 && EXAT_Timer < 50) {
  EXAT_A1 = analogRead(amppin); }
  if (EXAT_Timer > 50 && EXAT_Timer < 75) {
  EXAT_A2 = analogRead(amppin); }
  if (EXAT_Timer > 75 && EXAT_Timer <100) {
  EXAT_A3 = analogRead(amppin); }  
  if (EXAT_Timer >100 && EXAT_Timer <125) {
  EXAT_A4 = analogRead(amppin); }
  if (EXAT_Timer >125 && EXAT_Timer <150) {
  EXAT_A5 = analogRead(amppin); }
  if (EXAT_Timer >150 && EXAT_Timer <175) {
  EXAT_A6 = analogRead(amppin); }
  if (EXAT_Timer >175 && EXAT_Timer <200) {
  EXAT_A7 = analogRead(amppin); }  
  if (EXAT_Timer >200 && EXAT_Timer <225) {
  EXAT_A8 = analogRead(amppin); }
  if (EXAT_Timer >225 && EXAT_Timer <250) {
  EXAT_A9 = analogRead(amppin); }
  if (EXAT_Timer >250 && EXAT_Timer <275) {
  EXAT_A10 = analogRead(amppin); }
  if (EXAT_Timer >275 && EXAT_Timer <300) {
  EXAT_A11 = analogRead(amppin); }  
  if (EXAT_Timer >300 && EXAT_Timer <325) {
  EXAT_A12 = analogRead(amppin); }
  if (EXAT_Timer >325 && EXAT_Timer <350) {
  EXAT_A13 = analogRead(amppin); }
  if (EXAT_Timer >350 && EXAT_Timer <375) {
  EXAT_A14 = analogRead(amppin); }
  if (EXAT_Timer >375 && EXAT_Timer <400) {
  EXAT_A15 = analogRead(amppin); }  
  if (EXAT_Timer >400 && EXAT_Timer <425) {
  EXAT_A16 = analogRead(amppin); }
  if (EXAT_Timer >425 && EXAT_Timer <450) {
  EXAT_A17 = analogRead(amppin); }
  if (EXAT_Timer >450 && EXAT_Timer <475) {
  EXAT_A18 = analogRead(amppin); }
  if (EXAT_Timer >475 && EXAT_Timer <500) {
  EXAT_A19 = analogRead(amppin); }  
  if (EXAT_Timer >500) {
  EXAT_A20 = analogRead(amppin); 
  
  EXAT_ARead =( EXAT_A1+EXAT_A2+EXAT_A3+EXAT_A4+EXAT_A5+EXAT_A6+EXAT_A7+EXAT_A8+EXAT_A9+EXAT_A10+EXAT_A11+EXAT_A12+EXAT_A13+EXAT_A14+EXAT_A15+EXAT_A16+EXAT_A17+EXAT_A18+EXAT_A19+EXAT_A20 ) / 20;
  EXAT_ACalc = (( ((EXAT_ARead /  1023) * 5) ) - 2.5) /0.066 ;
  EXAT_OldTime = EXAT_Timer;
  return EXAT_ACalc;
  } 
  }
};

class ZeroPWM
{
  int pwmpin;
  int Value;
  unsigned long PWMOldTime;
  
  public:
  ZeroPWM(int pin)
  {
  pwmpin = pin;
  pinMode(pwmpin, OUTPUT);
  PWMOldTime = 0;
  }
 
  void pwmWrite(int x)
  {
  unsigned long PWMTime = millis() - PWMOldTime;
  if (x > 0 && x < 255) {
   if (PWMTime == x && Value == 0)
   {
   digitalWrite(pwmpin, HIGH); Value = 1;
   }
   if (PWMTime == (255-x) && Value == 1)
   {
   digitalWrite(pwmpin, LOW);
   PWMOldTime = PWMTime; Value = 0;
   }
  }
  else {
   if (x >= 255)
   {x = 255;
   digitalWrite(pwmpin, HIGH);}
   if (x <= 0)
   {x=0;
   digitalWrite(pwmpin, LOW);}
   }    
  }
};

class ZeroHeat
{
  int heatpin;
  int Value;
  int cycle;
  unsigned long HeaterOldTime;
  
  public:
  ZeroHeat(int hpin, int c)
  {
  heatpin = hpin;
  cycle = c;
  pinMode(heatpin, OUTPUT);
  HeaterOldTime = 0;
  }
  
  void Heat(int y)
  {
  int z = (y / 100) * cycle; // % to millis
  unsigned long HeaterTime = millis() - HeaterOldTime;
  if (z > 0 && z < cycle) {
   if (HeaterTime >= z && Value == 0)
   {
   digitalWrite(heatpin, LOW); 
   HeaterOldTime = HeaterTime; Value = 1;
   }
   if (HeaterTime >= (cycle-z) && Value == 1)
   {
   digitalWrite(heatpin, HIGH);
   HeaterOldTime = HeaterTime; Value = 0;
   }
  }
  else {
   if (z >= cycle)
   {z = cycle;
   digitalWrite(heatpin, LOW);}
   if (z <= 0)
   {z = 0;
   digitalWrite(heatpin, HIGH);}
   HeaterOldTime = HeaterTime;
   }    
  }
};

#endif