/**
* CTA Display: A display of various aspects of the Chicago Rail L system
* 
* 
*/
#include <stdio.h>
#include <Arduino.h>
#include "drivers/ledLines.h"
#include "drivers/stepperMotors.h"
#include "drivers/infoGet.h"
#include "drivers/LCD.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel pixels(1,48, NEO_GRB + NEO_KHZ800);
int i=0;
// cppcheck-suppress unusedFunction
void setup(){
	Serial.begin(115200);
	lcdinit();
	Serial.println("Starting CTA Display!!!");
	// fetchStationIdsTest();
	pixels.begin();
}
// cppcheck-suppress unusedFunction
void loop(){
	pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Set the first pixel to off
	pixels.show(); // Update the strip to show the changes
	delay(1000);
	pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Set the first pixel to red
	pixels.show(); // Update the strip to show the changes
	// Serial0.println(i++);
	checkSwitch();
	delay(1000);
}

