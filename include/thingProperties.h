#include <Arduino.h>

#if defined(BOARD_HAS_WIFI)
#elif defined(BOARD_HAS_GSM)
#elif defined(BOARD_HAS_LORA)
#elif defined(BOARD_HAS_NB)
#else
  #error "Please check Arduino IoT Cloud supported boards list: https://github.com/arduino-libraries/ArduinoIoTCloud/#what"
#endif


void onAmpereChange();
void onMAmpereChange();
void onA0RawChange();
void onMAxStepChange();
void onMVxAChange();

CloudElectricCurrent ampere;
float mAmpere;
int a0Raw;
int mAxStep;
int mVxA;


void initProperties() {
  Serial.println(" initProperties");
#if defined(BOARD_ESP)
    Serial.println(" initProperties -BOARD_ESP");

  ArduinoCloud.setBoardId(BOARD_ID);
  ArduinoCloud.setSecretDeviceKey(SECRET_DEVICE_KEY);
#endif
#if defined(BOARD_HAS_WIFI) || defined(BOARD_HAS_GSM) || defined(BOARD_HAS_NB)
  ArduinoCloud.addProperty(ampere, READWRITE, ON_CHANGE, onAmpereChange);
  ArduinoCloud.addProperty(mAmpere, READWRITE, ON_CHANGE, onMAmpereChange);
  ArduinoCloud.addProperty(a0Raw, READWRITE, ON_CHANGE, onA0RawChange);
  ArduinoCloud.addProperty(mAxStep, READWRITE, ON_CHANGE, onMAxStepChange);
  ArduinoCloud.addProperty(mVxA, READWRITE, ON_CHANGE, onMVxAChange);
#elif defined(BOARD_HAS_LORA)
  ArduinoCloud.addProperty(ampere,3, READWRITE, ON_CHANGE, onAmpereChange);
  ArduinoCloud.addProperty(mAmpere,3, READWRITE, ON_CHANGE, onMAmpereChange);
    /// ... to complete .... 
#endif
}

#if defined(BOARD_HAS_WIFI)
  #warning "board has a WIFI"
  WiFiConnectionHandler ArduinoIoTPreferredConnection(SECRET_SSID, SECRET_PASS);
#elif defined(BOARD_HAS_GSM)
  GSMConnectionHandler ArduinoIoTPreferredConnection(SECRET_PIN, SECRET_APN, SECRET_LOGIN, SECRET_PASS);
#elif defined(BOARD_HAS_LORA)
  LoRaConnectionHandler ArduinoIoTPreferredConnection(SECRET_APP_EUI, SECRET_APP_KEY, _lora_band::EU868, NULL, _lora_class::CLASS_A);
#elif defined(BOARD_HAS_NB)
  NBConnectionHandler ArduinoIoTPreferredConnection(SECRET_PIN, SECRET_APN, SECRET_LOGIN, SECRET_PASS);
#endif
