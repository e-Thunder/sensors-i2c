/*
 1. Download from https://github.com/marcoschwartz/LiquidCrystal_I2C/archive/master.zip
 2. Add to lib folder
 3. Make src folder in Liqui...I2C and put there .cpp and .h files
*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int lcdColumns = 16;
int lcdRows = 2;
// 0x27 - address given by scanner
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup()
{
    lcd.init();
    lcd.backlight();
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print("Czesc Lukasz !");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("I2C dziala");
    delay(1000);
    lcd.clear();
}

void begin_scanner()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("\nI2C scanner");
}
void scanning()
{
    int nDevices = 0;
    Serial.println("Scanning...");
    for (byte address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknow error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("done\n");
    }
    delay(5000);
}