/*
 * ZeroMaster.h - Library for using several devices for the 3Devo NEXT 1.0
 * Created by Julian Muller, November 30, 2015
 * Last updated on December 31, 2015
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
   ZeroLED(int RpinI, int GpinI, int BpinI);
   void Shine(int R, int G, int B);
   void DigiShine(int R, int G, int B);
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
   ZeroAMP(int pin);
   double EXA();
   double Amps();
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
   ZeroPWM(int pin); 
   void pwmWrite(int x);
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
   ZeroHeat(int pin, int cycle);
   void HeatFast(int x);
   void HeatFastReverse(int x);
   void Heat(int x);
   void HeatReverse(int x);
};


/*
 * ZeroFila is a library that controls a TSL1401CL sensor to measure filament width.
 * This class and function will convert light input into a width value.
 */

class ZeroFila
{
  int pinCLK;   
  int pinSI;   
  int pinAO1;
  int IntArray[128];
  int LightMax;
  int LightMin;
  double Filamentwidth;
  double SensorStep;
  double FSA[5];

  public:
   ZeroFila(int SI, int CLK, int AO1);
   double FilaRead();
   double FilaRead5();
};


/*
 * Zero6675 is a converted version of the adafruit MAX6675 library where no delays are used.
 * This class and function will read the MAX6675 value and and convert it to celsius.
 */

class Zero6675 
{
  public:
   Zero6675(int8_t SCLK, int8_t CS, int8_t MISO);
   double HeatRead();
  private:
   int8_t sclk, miso, cs;
   uint8_t SPIRead();
};

/*
 * Zero31855 is a converted version of the adafruit MAX31855 library where no delays are used.
 * This class and function will read the MAX31855 value and and convert it to celsius.
 */

class Zero31855 
{
  public:
   Zero31855(int8_t SCLK, int8_t CS, int8_t MISO);
  double HeatRead2();
  private:
   int8_t sclk, miso, cs;
   uint32_t SPIRead2();
};


/*
 * ZeroBuzz is used for Piezo Buzzers on a PWM pin.
 * This class and function create an error signal to hear when something is wrong. 
 */

class ZeroBuzz
{
  int BuzzPin;
  byte Value;
  unsigned long BuzzTime;
  unsigned long BuzzOldTime;

  public:
   ZeroBuzz(int pin);
   void Pulse(int x);

};
#endif