#include <Arduino.h>


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

#include "funzioni.h"
#if defined (ARDUINO_ARCH_SAMD)
  #include "arduino_secrets.h"
  #include "thingProperties.h"
  #if OTA_STORAGE_SNU
    #  include <SNU.h>
    #  include <WiFiNINA.h> /* WiFiStorage */
  #endif
#elif defined (ARDUINO_ARCH_ESP8266)
  #include "arduino_secrets.h"
  #include "thingProperties.h"

#endif
 
//

#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 3.3, 1023, 66);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


void doThisOnConnect(){
  /* add your custom code here */
  Serial.println("Board successfully connected to Arduino IoT Cloud");
}
void doThisOnSync(){
  /* add your custom code here */
  Serial.println("Thing Properties synchronised");
}
void doThisOnDisconnect(){
  /* add your custom code here */
  Serial.println("Board disconnected from Arduino IoT Cloud");
}



 /// @brief la funzione per nizializzare la Cloud di Arduino aggiungere  ThingProperties e arduino_secrets.h
    void initArduinoMKR_Cloud()
    {// Defined in thingProperties.h
        initProperties();
        
        // Connect to Arduino IoT Cloud
        ArduinoCloud.begin(ArduinoIoTPreferredConnection);

       /*
      Invoking `addCallback` on the ArduinoCloud object allows you to subscribe
      to any of the available events and decide which functions to call when they are fired.
      The functions `doThisOnConnect`, `doThisOnSync`, `doThisOnDisconnect`
      are custom functions and can be named to your likings and for this example
      they are defined/implemented at the bottom of the Sketch
  */
        ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, doThisOnConnect);
        ArduinoCloud.addCallback(ArduinoIoTCloudEvent::SYNC, doThisOnSync);
        ArduinoCloud.addCallback(ArduinoIoTCloudEvent::DISCONNECT, doThisOnDisconnect);

        /*
            The following function allows you to obtain more information
            related to the state of network and IoT Cloud connection and errors
            the higher number the more granular information you’ll get.
            The default is 0 (only errors).
            Maximum is 4  DBG_VERBOSE
        */
        setDebugMessageLevel(DBG_VERBOSE);
        ArduinoCloud.printDebugInfo();
  }



void setup()
{
  Serial.begin(115200);
  for(unsigned long const serialBeginTime = millis(); (millis() - serialBeginTime > 5000); ) { }  
  
  #pragma region ACS712
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  #pragma endregion


#pragma  region HD44780
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
#pragma endregion

  ACS.autoMidPoint();

  initArduinoMKR_Cloud();
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
    if (ArduinoCloud.connected())
    Serial.println("it's  joined  to ArdinoCloud");
  else
  {
      Serial.println("it's not yet joined to ARduino Cloud ") ;
  }
  #if  defined(ARDUINO_ARCH_SAMD) ||  defined(ONLINE) || defined(ESP8266)
    ArduinoCloud.update();
#endif
}


// -- END OF FILE --


/*
  Since Ampere is READ_WRITE variable, onAmpereChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAmpereChange()  {
  // Add your code here to act upon Ampere change
}

/*
  Since MAmpere is READ_WRITE variable, onMAmpereChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMAmpereChange()  {
  // Add your code here to act upon MAmpere change
}

/*
  Since A0Raw is READ_WRITE variable, onA0RawChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onA0RawChange()  {
  // Add your code here to act upon A0Raw change
}

/*
  Since MAxStep is READ_WRITE variable, onMAxStepChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMAxStepChange()  {
  // Add your code here to act upon MAxStep change
}

/*
  Since MVxA is READ_WRITE variable, onMVxAChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMVxAChange()  {
  // Add your code here to act upon MVxA change
}