/*
 * ZeroColor is the class made for the TCS230 and TCS3200 RBG Color Sensors.
 * This class and function simply compiles all 3 colors in one element for an easier code.
 * Created by Julian Muller, May 30, 2018
 */

#include <ZeroMaster.h>

// Define all the pins of board
#define pin_s0  4
#define pin_s1  5
#define pin_s2  6
#define pin_s3  7
#define pin_sO  8
#define set 4 // output% 1=0, 2=2, 3=20, 4=100

ZeroColor TCS(pin_s0, pin_s1, pin_s2, pin_s3, pin_sO, set);

//Create variables for the sensor and commands to fill
String SerialText;
int Red_Value = 0;
int Green_Value = 0;
int Blue_Value = 0;
int Clear_Value = 0;
byte SetColor = 0;

// If the output setting has to be changed somewhere else, use TCS.ChangeSetting(<setting>);

void setup() 
{
// Set a serial channel for readouts
Serial.begin(9600);
delay(1500); // Clear the serial port with some wait time
Serial.println("ZeroColor example with serial commands");
Serial.println("Use the 'set:Red', 'set:Green', 'set:Blue' or 'set:Clear' command to  set the color");
Serial.println("After this, use 'read' to read this color. You can also use 'readAll' to read all colors at once");
Serial.println("Use the 'print' command to print the last measured values");
}

void loop() 
{
// Begin a serial command check to read different sensor functions
if (Serial.available())
  {
    SerialText = Serial.readString();
    SerialText.trim();
    if (SerialText == "set:Red" || SerialText == "set:RED")
    {
      TCS.Set('R'); // Set the color to red
      SetColor = 1;
    }
    else if (SerialText == "set:Green" || SerialText == "set:GREEN")
    {
      TCS.Set('G'); // Set the color to green
      SetColor = 2;
    }
    else if (SerialText == "set:Blue" || SerialText == "set:BLUE")
    {
      TCS.Set('B'); // Set the color to blue
      SetColor = 3;
    }
    else if (SerialText == "set:Clear" || SerialText == "set:CLEAR")
    {
      TCS.Set('C'); // Set the color to clear
      SetColor = 4;
    }
    if (SerialText == "read" && SetColor > 0 && SetColor < 5)
    {
      if (SetColor == 1) // The Red LEDs have been activated
      {
        // Read the value into an integer
        Red_Value = TCS.Read();
        Serial.print("Red: ");
        Serial.println(Red_Value);
      }         
      else if (SetColor == 2) // The Green LEDs have been activated
      {
        // Read the value into an integer
        Green_Value = TCS.Read();
        Serial.print("Green: ");
        Serial.println(Green_Value);        
      }     
      else if (SetColor == 3) // The Blue LEDS have been activated
      {
         // Read the value into an integer
        Blue_Value = TCS.Read();
        Serial.print("Blue: ");
        Serial.println(Blue_Value);       
      }     
      else if (SetColor == 4) // The Clear LEDs have been activated
      {
        // Read the value into an integer
        Clear_Value = TCS.Read();
        Serial.print("Clear: ");
        Serial.println(Clear_Value);
      }
      else
      {
        // No color selected
        Serial.println("No color selected. Use .Set(<R, G, B or C>) to set it");
      }
    }
    else if (SerialText == "readAll")
    {
      // Read all the values at the same time
      TCS.ReadAll(Red_Value, Green_Value, Blue_Value, Clear_Value);
      Serial.print("Red: ");
      Serial.println(Red_Value);
      Serial.print("  Green: ");
      Serial.println(Green_Value);
      Serial.print("  Blue: ");
      Serial.println(Blue_Value);
      Serial.print("  Clear: ");
      Serial.println(Clear_Value);  
    }
    else if (SerialText == "print")
    {
      Serial.print("Red: ");
      Serial.println(Red_Value);
      Serial.print("  Green: ");
      Serial.println(Green_Value);
      Serial.print("  Blue: ");
      Serial.println(Blue_Value);
      Serial.print("  Clear: ");
      Serial.println(Clear_Value);      
    }
  }
}
