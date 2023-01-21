void testfunc();
int freeRam() ;
void display_freeram();
void separaDecimali(float valoreFloat, String &Intero, String &Decimale);
long GetAvarageMisure(long valore,long voltages[]);

const int delayVeryShort = 100;//100
const int delayShort = 150;//250
const int delayAvarge = 350;//500
const int delayLong = 500;//1000

#if  defined(ARDUINO_ARCH_SAMD)
    // #include "arduino_secrets.h"
    // #include <ArduinoIoTCloud.h>
    // #include <Arduino_ConnectionHandler.h>
    // // const char SSID[]     = SECRET_SSID;    // Network SSID (name)
    // const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
    // WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
   
    // void initProperties();
    void initArduinoMKR_Cloud();
    
#endif 