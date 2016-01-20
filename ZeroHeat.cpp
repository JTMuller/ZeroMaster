/*
 * ZeroHeat is a variation of ZeroPWM used for solid state relays.
 * This class and function allows the user to set the cycletime themselves and allows them to use either millis or micro's
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

ZeroHeat::ZeroHeat(int pin, int cycle)
  {
  heatpin = pin;
  pinMode(heatpin, OUTPUT);
  HeatOldTime = 0;
  Value = 0;
  c = cycle;
  }
 
void ZeroHeat::HeatFast(int x)
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

void ZeroHeat::HeatFastReverse(int x)
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

void ZeroHeat::Heat(int x)
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

void ZeroHeat::HeatReverse(int x)
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