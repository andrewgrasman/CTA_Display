/**
* Control over the three stepper motors for flip clock
*/

#include "stepperMotors.h"
#define stepsPerRevolution 32*32 //full step drive (high torque)

Stepper hourStep(stepsPerRevolution,39,40,41,42);
Stepper tensStep(stepsPerRevolution,35,36,37,38);
Stepper minsStep(stepsPerRevolution,20,21,47,48);
Preferences prefs;
uint8_t minute,tens,hour;

void timeStore(){
	prefs.begin("clk",false);
	prefs.putUChar("mins",10*tens+minute);
	prefs.putUChar("hrs",hour);
	prefs.end();
}
void initStepperMotors(){
	hourStep.setSpeed(60/12);
	tensStep.setSpeed(60/6);
	minsStep.setSpeed(60/10);
	prefs.begin("clk",false);
	minute=prefs.getUChar("mins",0);
	tens=minute/10;
	minute=minute%10;
	hour=prefs.getUChar("hrs",1);
	prefs.end();
}
void setNewTime(uint8_t hour,uint8_t minute){
	minsStep.step((minute%10-::minute)%10*stepsPerRevolution/10);
	tensStep.step(-(minute/10-tens)%6*stepsPerRevolution/6);
	hourStep.step((hour-::hour)%12*stepsPerRevolution/12);
	::hour=hour;
	tens=minute/10;
	::minute=minute%10;
	timeStore();
}
void nextMin(){
	if(++minute==10){
		minsStep.step(stepsPerRevolution/10);
		minute=0;
		if(++tens==7){
			tens=0;
			tensStep.step(stepsPerRevolution/6);
			if(++hour==13){
				hour=1;
				hourStep.step(stepsPerRevolution/12);
			}
		}
		timeStore();
	}
}
void manualStep(uint8_t id,int steps){
	switch (id){
		case 0:
		hourStep.step(steps);
		break;
		case 1:
		tensStep.step(steps);
		break;
		case 2:
		minsStep.step(steps);
		break;
		default:
		break;
	}
}