#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#if OTA_STORAGE_SNU
#  include <SNU.h>
#  include <WiFiNINA.h> /* WiFiStorage */
#endif
/* A complete list of supported boards with WiFi is available here:
 * https://github.com/arduino-libraries/ArduinoIoTCloud/#what
 */
#if defined(BOARD_HAS_WIFI)
  // #define SECRET_SSID "Ospiti-2.4GHzPro"
  // #define SECRET_PASS "xxxx"
  #define SECRET_SSID "xxx"
  #define SECRET_PASS "xxxxx"

#endif
#error "information are not real please  replace  with real info"

/* ESP8266  -secretKey  secondoD1r2 */
#if defined(BOARD_ESP)
  #define SECRET_DEVICE_KEY "xxxxxZLNLDG" 
#endif

#if defined(BOARD_ESP)
  #define BOARD_ID "xxxxxx-5f4022383260" 
#endif

/* MKR GSM 1400 */
#if defined(BOARD_HAS_GSM)
  #define SECRET_PIN ""
  #define SECRET_APN ""
  #define SECRET_LOGIN ""
  #define SECRET_PASS ""
#endif

/* MKR WAN 1300/1310 */
#if defined(BOARD_HAS_LORA)
  #define SECRET_APP_EUI ""
  #define SECRET_APP_KEY ""
#endif

/* MKR NB 1500 */
#if defined(BOARD_HAS_NB)
  #define SECRET_PIN ""
  #define SECRET_APN ""
  #define SECRET_LOGIN ""
  #define SECRET_PASS ""
#endif

#pragma region Blynk

#define BLYNK_TEMPLATE_ID "xxxxxxxPat9hf"
#define BLYNK_DEVICE_NAME "xxxxxxxeter"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxbbnWnke"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxbbnWnke";

#pragma endregion