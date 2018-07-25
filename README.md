# SR
*Smart Room*

## Project Overview
*GUC, Winter 2017, CSEN701*

The smart electronic system serves 3 main purposes:

The first is detecting the presence of people within a room to light up the room, and adjust the room temperature, without needing to press any switches. This sensor is to be placed at a room’s door to detect whenever a person enters the room or leaves the room. A counter of the people within the room is saved and displayed on the 7-segment displays, and based on the information received from the sensor, the counter is either incremented (in case someone enters the room) or decremented in case someone leaves the room. If the counter is equal to zero, the lighting system will be turned off as well as the conditioning system.

The second sensor, which represents the second purpose, detects the light intensity to control the intensity of lighting. Before lighting up, the sensor is going to detect the light intensity of the room, and the intensity of the light provided by the lighting system is inversely proportional to the light intensity of the room detected by the sensor. In other words, the brightness provided by the electronic system will be adjusted automatically, depending on the current brightness of the room.
By using the lighting system’s smart mode a considerable amount of electricity can be saved, and this presents a solution to one of the most common problems presented nowadays.

The third sensor, the third input to the system, is the temperature sensor that measures the current temperature of the room, and whenever the temperature of the room reaches a specific level of heat, the fan will be turned on in case there is anyone in the room, otherwise, the fan will be off as there is no one in the room, so there is no need to waste energy to turn the fan on.

Inputs: Light Sensor, Temperature Sensor, Motion Sensor

Outputs: LEDs, Fan, 7-Segment Display (4x1)

## Circuit Schematic

![Preview](https://github.com/ahmedhamdi96/SR/blob/master/Preview/preview.png)

## Hardware Components

* 1 Arduino Uno development board
* 1 AVR ATmega328P microcontroller
* 2 IR sensors
* 2 seven-segment displays
* 1 LM35 temperature sensor
* 1 transistor
* 1 voltage regulator
* 1 DC fan
* 2 breadboards
* LEDs, resistors, capacitors and jumpers

## Project Partners
*in alphabetical order*

* [Ahmed Ashraf](https://github.com/ahmedElqutb)
* [Ebraheem Mohamed](https://github.com/Ebraheem1)
* [Marwan Adel](https://github.com/marwanadel)
