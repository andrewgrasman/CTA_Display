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
	
	esp_timer_create_args_t clockTimerArgs = {
		.callback = [](void* arg) {
			fetchStationIds();
			//TODO: update lines
			//TODO: update LCD if on eta display
			//possible realign to api publish time
		},
		.name = "Clock Timer"
	};
	esp_timer_handle_t clockTimer;
	esp_timer_create(&clockTimerArgs, &clockTimer);
	esp_timer_start_periodic(clockTimer, 60*1000000);

}
// cppcheck-suppress unusedFunction
void loop(){
	//sign of life
	//TODO: implement using millis();
	pixels.setPixelColor(0, 0xFF0000);
	pixels.show(); // Update the strip to show the changes
	delay(1000);
	pixels.setPixelColor(0, 0);
	pixels.show();
	delay(1000);

	//checkSwitch();//DONE: implement as interrupt on three pins
	
	//TODO: implement BT Serial for on the fly flap clock control
	//if()manualStep(0-3,steps);
}

