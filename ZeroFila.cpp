/*
 * ZeroFila is a library that controls a TSL1401CL sensor to measure filament width.
 * This class and function will convert light input into a width value.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ZeroMaster.h"

ZeroFila::ZeroFila(int SI, int CLK, int AO1)
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

double ZeroFila::FilaRead() 
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

double ZeroFila::FilaRead5()
  {
  FSA[0] = FilaRead();
  FSA[1] = FilaRead();
  FSA[2] = FilaRead();
  FSA[3] = FilaRead();
  FSA[4] = FilaRead();
  double FSR = (FSA[0]+FSA[1]+FSA[2]+FSA[3]+FSA[4]) / 5;
  return FSR;
  }