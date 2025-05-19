/**
 * Controll over the three stepper motos for flip clock
 */

#include "stepperMotors.h"
#define stepsPerRevolution 32*32 //full step drive

Stepper hourStep(stepsPerRevolution,39,40,41,42);
Stepper tensStep(stepsPerRevolution,35,36,37,38);
Stepper minsStep(stepsPerRevolution,20,21,47,48);
void initStepperMotors(){

}