/*
 * ZeroHeat is a variation of ZeroPWM used for solid state relays.
 * This class and function allows the user to set the cycletime themselves and allows them to use either millis or micro's
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

ZeroHeat::ZeroHeat(int pin, int cycle, bool reverse)
  {
  heatpin = pin;
  c = cycle;
  Rev = reverse;
  pinMode(heatpin, OUTPUT);
  HeatOldTime = 0;
  Value = 0;
  }
 
void ZeroHeat::HeatFast(int x)
  {
  x2 = x*(c / 100);
  if (x >= 100) 
   {
   if(Rev == false) {digitalWrite(heatpin, HIGH);}
   else		   {digitalWrite(heatpin,  LOW);}
   }
  else if (x <= 0) 
   {
   if(Rev == false) {digitalWrite(heatpin,  LOW);}
   else		   {digitalWrite(heatpin, HIGH);}
   }
  else {  
  unsigned long HeatTime = micros();
  
  if(HeatTime - HeatOldTime >= (c-x2) && Value == 0) {
  HeatOldTime = HeatTime; 
  if(Rev == false) {digitalWrite(heatpin, HIGH);}
  else		   {digitalWrite(heatpin,  LOW);}
  Value = 1;}

  if(HeatTime - HeatOldTime >= x2 && Value == 1) {
  HeatOldTime = HeatTime; 
  if(Rev == false) {digitalWrite(heatpin,  LOW);}
  else		   {digitalWrite(heatpin, HIGH);}
  Value = 0;}    
  }  }


void ZeroHeat::Heat(int x)
  {
  x2 = x*(c / 100);
  if (x >= 100) 
   {
   if(Rev == false) {digitalWrite(heatpin, HIGH);}
   else		   {digitalWrite(heatpin,  LOW);}
   }
  else if (x <= 0) 
   {
   if(Rev == false) {digitalWrite(heatpin,  LOW);}
   else		   {digitalWrite(heatpin, HIGH);}
   }
  else {  
  unsigned long HeatTime = millis();
  
  if(HeatTime - HeatOldTime >= (c-x2) && Value == 0) {
  HeatOldTime = HeatTime; 
  if(Rev == false) {digitalWrite(heatpin, HIGH);}
  else		   {digitalWrite(heatpin,  LOW);}
  Value = 1;}

  if(HeatTime - HeatOldTime >= x2 && Value == 1) {
  HeatOldTime = HeatTime; 
  if(Rev == false) {digitalWrite(heatpin,  LOW);}
  else		   {digitalWrite(heatpin, HIGH);}
  Value = 0;}    
  }  }


void ZeroHeat::HeatRegulate(double TSet, double TScan, double TOffBig, double TOffSmall, int TP1, int TP2, int TP3, int TP4)
{
  TOff2 = TSet - TOffSmall;
  TOff1 = TSet - TOffBig;
    
  if ( TScan < TOff1 )                { TPercent = TP1; }
  if ( TScan < TOff2 && TScan >=TOff1){ TPercent = TP2; }
  if ( TScan >=TOff2 && TScan < TSet ){ TPercent = TP3; }
  if ( TScan >=TSet )                 { TPercent = TP4; }
  Heat(TPercent);
}