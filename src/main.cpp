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

int i=0;
// cppcheck-suppress unusedFunction
void setup(){
	Serial0.begin(115200);
	lcdinit();
	Serial0.println("Starting CTA Display!!!");
	fetchStationIdsTest();
}
// cppcheck-suppress unusedFunction
void loop(){
	Serial0.println(i++);
	checkSwitch();
}

