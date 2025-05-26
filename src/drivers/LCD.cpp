#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "LCD.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcdinit(){
    pinMode(19, INPUT_PULLUP); // left button
    pinMode(40, INPUT_PULLUP); // right button
    pinMode(41, INPUT_PULLUP); // enter button
    Wire.begin(20,21);
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

void checkSwitch(){
    int leftButtonState = digitalRead(19);
    int rightButtonState = digitalRead(40);
    int enterButtonState = digitalRead(41);
    if(leftButtonState == 0){
        lcd.clear();
        lcd.print("this is the left button");
    }
    
    else if (rightButtonState == 0)
    {
        lcd.clear();
        lcd.print("this is the right button");
    }

    else if (enterButtonState == 0)
    {
        lcd.clear();
        lcd.print("ENTER!!");
    }
    delay(200);
}

