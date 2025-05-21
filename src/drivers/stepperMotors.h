/**
 * stepperMotors.h
 * 
 * Stepper motors for flip clock header
 * 
 * 
 * Author: Andrew Grasman
 */

 #pragma once

#include <Arduino.h>
#include <Stepper.h>
#include <Preferences.h>

extern void initStepperMotors();
extern void setNewTime(uint8_t hour,uint8_t minute);
extern void nextMin();
extern void manualStep(uint8_t id,int steps);