#include <Arduino.h>

#if defined(BOARD_HAS_WIFI)
#elif defined(BOARD_HAS_GSM)
#elif defined(BOARD_HAS_LORA)
#elif defined(BOARD_HAS_NB)
#else
  #error "Please check Arduino IoT Cloud supported boards list: https://github.com/arduino-libraries/ArduinoIoTCloud/#what"
#endif



// void onBmeAltitudeChange();
// void onBmeGASChange();
// void onBmeHumidityChange();
// void onBmePRressureChange();
// void onBmeTEMPERATUREChange();
// void onBmeSEAAltitudeChange();
// void onLightAlexaChange();
// void onGasSensorChange();
// void onVoltRawChange();
// void onGASM2PresentChange();


// float bmeAltitude;
// float bmeGAS;
// float bmeHumidity;
// float bmePRressure;
// float bme_SEA_Altitude;
// float bmeTEMPERATURE;
// CloudLight lightAlexa;
// int gasSensor;
// int voltRaw;
// // valore  digitale ArduinoClouds D8 di ESP8266 se c'è un GAS True
// bool gAS_M2_present;


void initProperties() {
  Serial.println(" initProperties");
#if defined(BOARD_ESP)
    Serial.println(" initProperties -BOARD_ESP");

  ArduinoCloud.setBoardId(BOARD_ID);
  ArduinoCloud.setSecretDeviceKey(SECRET_DEVICE_KEY);
#endif
#if defined(BOARD_HAS_WIFI) || defined(BOARD_HAS_GSM) || defined(BOARD_HAS_NB)
  // ArduinoCloud.addProperty(bmeAltitude, READWRITE, ON_CHANGE, onBmeAltitudeChange);
  // ArduinoCloud.addProperty(bmeGAS, READWRITE, ON_CHANGE, onBmeGASChange);
  // ArduinoCloud.addProperty(bmeHumidity, READWRITE, ON_CHANGE, onBmeHumidityChange);
  // ArduinoCloud.addProperty(bmePRressure, READWRITE, ON_CHANGE, onBmePRressureChange);
  // ArduinoCloud.addProperty(bmeTEMPERATURE, READWRITE, ON_CHANGE, onBmeTEMPERATUREChange);
  // ArduinoCloud.addProperty(bme_SEA_Altitude, READWRITE, ON_CHANGE, onBmeSEAAltitudeChange);
  // ArduinoCloud.addProperty(lightAlexa, READWRITE, ON_CHANGE, onLightAlexaChange);
  // ArduinoCloud.addProperty(gasSensor, READWRITE, ON_CHANGE, onGasSensorChange);
  // ArduinoCloud.addProperty(voltRaw, READWRITE, ON_CHANGE, onVoltRawChange);
  // ArduinoCloud.addProperty(gAS_M2_present, READWRITE, ON_CHANGE, onGASM2PresentChange);

#elif defined(BOARD_HAS_LORA)
  // ArduinoCloud.addProperty(bmeAltitude,3, READWRITE, ON_CHANGE, onBmeAltitudeChange);
  // ArduinoCloud.addProperty(bmeGAS,3, READWRITE, ON_CHANGE, onBmeGASChange);
  // ArduinoCloud.addProperty(bmeHumidity,3, READWRITE, ON_CHANGE, onBmeHumidityChange);
  // ArduinoCloud.addProperty(bmePRressure,3, READWRITE, ON_CHANGE, onBmePRressureChange);
  // ArduinoCloud.addProperty(bmeTEMPERATURE,3, READWRITE, ON_CHANGE, onBmeTEMPERATUREChange);
  // ArduinoCloud.addProperty(bme_SEA_Altitude,3, READWRITE, ON_CHANGE, onBmeSEAAltitudeChange);
  // ArduinoCloud.addProperty(lightAlexa,3, READWRITE, ON_CHANGE, onLightAlexaChange);
  // ArduinoCloud.addProperty(gasSensor,3, READWRITE, ON_CHANGE, onGasSensorChange);
  // ArduinoCloud.addProperty(voltRaw,3, READWRITE, ON_CHANGE, onVoltRawChange);
  // ArduinoCloud.addProperty(gAS_M2_present,3, READWRITE, ON_CHANGE, onGASM2PresentChange);

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
