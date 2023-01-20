#include <Arduino.h>


//
//    FILE: ACS712_20_AC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AC measurement with point to point
//     URL: https://github.com/RobTillaart/ACS712


///////////////////////////////////////////////////////////////////
//
//  DISPLAY
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
// #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels



// #define BACKLIGHT_PIN   3
// #define En_pin          2
// #define Rw_pin          1
// #define Rs_pin          0
// #define D4_pin          4
// #define D5_pin          5
// #define D6_pin          6
// #define D7_pin          7

#define BL_OFF          0
#define BL_ON           1

// #define DISPLAY_ADDR    0x3F    //  check

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
uint32_t lastDisplay = 0;


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 3.3, 1023, 66);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  
  lcd.init();   
  lcd.begin(20, 4);
  // //lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(BL_ON);

  lcd.clear();

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


  ACS.autoMidPoint();

}


void loop()
{
  lcd.clear();

  // ACS.suppressNoise(true);
  // ACS.setNoisemV(0);
  float f1 = ACS.mA_DC();
  float f2 = ACS.getmVperAmp ();
  float f3=ACS.getmAPerStep();

  lcd.setCursor(0, 0);
  lcd.print("mA_DC: ");
  lcd.print(f1, 1);
  


  
  lcd.setCursor(0, 1);
  lcd.print("Vm per A ");
  lcd.print(f2);

  

  lcd.setCursor(0,2);
  lcd.print("Am per Step ");
  lcd.print(f3);

  lcd.setCursor(0,3);
  lcd.print("A0 Raw ");
  lcd.print(analogRead(A0));

  delay(1000);
  
  Serial.print("mA_DC: ");
  Serial.println(f1, 1);
  Serial.print("Vm per A ");
  Serial.println(f2);
  
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  // display.println(F("Hello, world!"));

  // display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  // display.println(3.141592);

  display.setTextSize(1);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("mA_DC: ")); 
  display.println(f1, 1);


  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(F("Vm per A ")); 
  display.println(f2, 1);

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(F("Am per Step ")); 
  display.println(f3, 1);

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(F("A0 Raw ")); 
  display.println(analogRead(A0));

  display.display();
  // delay(1000);
}


// -- END OF FILE --
