#include "WifiManager.h"

void setup() {
  Serial.begin(115200);
  
  WifiManager espWifi;
  espWifi.connectWifi("DD_box","je suis le reseau de Ste7&Jul5");
  delay(100);
  espWifi.createWifi("espWifi","dd");

  Serial.println(ESP.getChipId());
  Serial.println(ESP.getFlashChipId());
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
