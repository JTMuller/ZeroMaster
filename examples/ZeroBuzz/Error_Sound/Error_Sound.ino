/*
 * ZeroBuzz - Library for using a piezo buzzer as an error sound
 * Created by Julian Muller, Januari 11, 2016
 */

#include <ZeroMaster.h>

// Define the pwm pin that you want to use for the piezo buzzer
ZeroBuzz Piezo(9);

void setup() {
}

void loop() {
// Set a frequency at which you want to generate the error sound.
Piezo.Pulse(349); // currently F4

/*       1 |   2 |   3 |   4 |   5 |
 * C |  33 |  65 | 131 | 262 | 523 |
 * D |  37 |  73 | 147 | 294 | 587 |
 * E |  41 |  82 | 165 | 330 | 659 |
 * F |  44 |  87 | 175 | 349 | 698 |
 * G |  49 |  98 | 196 | 392 | 784 |
 * A |  55 | 110 | 220 | 440 | 880 |
 * B |  62 | 123 | 247 | 494 | 988 |
 */
}
