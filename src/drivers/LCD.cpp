#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "LCD.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
void IRAM_ATTR handleLeftButtonInterrupt();
void IRAM_ATTR handleRightButtonInterrupt();
void IRAM_ATTR handleConfButtonInterrupt();

void lcdinit(){
    pinMode(4, INPUT_PULLUP); // left button
    pinMode(5, INPUT_PULLUP); // right button
    pinMode(6, INPUT_PULLUP); // enter button
    attachInterrupt(digitalPinToInterrupt(4), handleLeftButtonInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(5), handleRightButtonInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(6), handleConfButtonInterrupt, FALLING);
    
    Wire.begin(1,2);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ESP32-S3 Config");

    lcd.setCursor(0, 1);
    lcd.print("20x4 LCD Display");

    lcd.setCursor(0, 2);
    lcd.print("This is row 3");

    lcd.setCursor(0, 3);
    lcd.print("This is row 4");
}

void IRAM_ATTR handleLeftButtonInterrupt() {
    //TODO: implement debounce if needed likely using millis();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("this is the left button");
}
void IRAM_ATTR handleRightButtonInterrupt() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("this is the right button");
}
void IRAM_ATTR handleConfButtonInterrupt() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ENTER!!");
}

//TODO: custom print function that takes a string and row and prints centered


// void checkSwitch(){
//     int leftButtonState = digitalRead(4);
//     int rightButtonState = digitalRead(5);
//     int enterButtonState = digitalRead(6);
//     if(leftButtonState == 0){
//         lcd.clear();
//         lcd.print("this is the left button");
//     }
    
//     else if (rightButtonState == 0)
//     {
//         lcd.clear();
//         lcd.print("this is the right button");
//     }

//     else if (enterButtonState == 0)
//     {
//         lcd.clear();
//         lcd.print("ENTER!!");
//     }
//     delay(200);
// }

