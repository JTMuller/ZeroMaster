# ZeroMaster

## Version 14
For the latest version go to the GitHub.

## ZeroLED
This function controls RGB LED strips.
ZeroLED holds two different functions: Shine and DigiShine.
The functions both result the same way, yet work completely different.
Internally the Shine function is a simple triple analogWrite.
In this function you can simply control all the colors in one line of code.
DigiShine uses the utility from ZeroPWM to create a PWM wave on a digital port.
This function suffers when used in combination with delay(), but works good when not delayed.

## ZeroAMP
This function controls an ACS712 Ampere meter.
ZeroAMP holds two different functions: Amps and EXA.
Due to different kinds of compensations when working with the ACS, the functions will result in different values.
The EXA function is used more commonly, but the Amps version works better in a smooth system.

## ZeroPWM
This function repurposes digital pins to work with bit-bang PWM.
ZeroPWM holds a single function: pwmWrite.
The function is meant to act exactly like analogWrite, yet on a digital port.
ZeroPWM is the core for many different functions in the other parts of this library, like ZeroLED and ZeroHeat.

## ZeroHeat
This function controls a solid state relay for heaters.
ZeroHeat is the largest function of the library, holding three functions: Heat, HeatFast and HeatRegulate.
The function works with a custom blink effect. ZeroHeat is also usable for reverse-controlled relays
The user defines the total cycletime and uses Heat or HeatFast to control how many % of this time the relay is on.
HeatRegulate is a more complex function. This function controls the % of how long the heater is on automaticly.
This is based on the input Set and Scan values, aswell as a bundle of customisable offset values.

## ZeroFila
This function controls a lightsensor to measure filament in millimeters.
ZeroFila holds two different functions: FilaRead and FilaRead5.
To read filamentwidth, the function makes a lightarray of 128 pixels.
The dark points form the edges from which to calculate the filamentwidth.
FilaRead5 is a heavier function. It reads the filamentwidth 5 times, and takes the average value.

## Zero6675 / Zero31855
These functions are replacements for the MAX6675 and MAX31855 libraries.
Zero6675 holds the HeatRead function and Zero31855 holds the HeatRead2 function.
Both functions read the Celsius value of the thermocouple.
The advantage over the original Adafruit libraries is that these verions do not use delays in their calculations.

## ZeroBuzz
This function controls a piezo buzzer to make an error sound.
ZeroBuzz holds a single function: Pulse.
The Pulse function makes an annoying sound pulse which can be used for system errors in machines.
The frequency of the function is completely adjustable.

## Usage
The ZeroMaster library is free for usage.
When the library is used in a project that is to be set online, please credit the creator and put a link in to the GitHub of the library.