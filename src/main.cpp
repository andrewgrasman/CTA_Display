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

void setup(){
    lcdinit();
}
void loop(){
    checkSwitch();
}

