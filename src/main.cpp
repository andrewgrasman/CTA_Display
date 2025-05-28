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
// cppcheck-suppress unusedFunction
void setup(){
	Serial.begin(115200);
	Serial.println("Starting CTA Display!!!");
	sei(); // Enable interrupts
	// Serial.setDebugOutput(true);

	//TODO: verify implementation
	// wifiInit();
	// setClock();
	// fetchStationIds();
	
	lcdinit();
	//TODO: lcdMainMenu();
	pixels.begin(); //single neopixel can be used for debugging
	pixels.setPixelColor(0, 0xFF0000);

	initStepperMotors();
	//TODO: align to actual seconds
	//example https://github.com/espressif/esp-idf/blob/master/examples/system/esp_timer/main/esp_timer_example_main.c
	esp_timer_create_args_t clockTimerArgs = {
		.callback = [](void* arg) {
			nextMin();
			//possible realign to actual seconds
		},
		.name = "Clock Timer"
	};
	esp_timer_handle_t clockTimer;
	esp_timer_create(&clockTimerArgs, &clockTimer);
	esp_timer_start_periodic(clockTimer, 60*1000000);
	
	esp_timer_create_args_t apiTimerArgs = {
		.callback = [](void* arg) {
			fetchStationIds();
			//TODO: update lines
			//TODO: update LCD if on eta display
			//possible realign to api publish time
		},
		.name = "API Timer"
	};
	esp_timer_handle_t apiTimer;
	esp_timer_create(&apiTimerArgs, &apiTimer);
	esp_timer_start_periodic(apiTimer, 60*1000000);

}
// cppcheck-suppress unusedFunction
void loop(){
	//sign of life
	static unsigned long lastUpdate = 0;
	if (millis() - lastUpdate >= 1000) {
		lastUpdate = millis();
		if(pixels.getPixelColor(0)==0) {
			pixels.setPixelColor(0, 0xFF0000);
		} else {
			pixels.setPixelColor(0, 0x000000);
		}
		pixels.show(); // Update the strip to show the changes
	}

	//checkSwitch();//DONE: implement as interrupts on three pins
	
	//TODO: implement BT Serial for on the fly flap clock control
	//Handle negatives by doing most of a full revolution
	// manualStep(id,steps); //id is 0 for hour, 1 for tens, 2 for minutes
	//TODO:option to send time displayed in military format (100*hour+minute) to realign to current time
}

