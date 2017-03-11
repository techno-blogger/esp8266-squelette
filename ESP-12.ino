#include "WifiManager.h"

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("==========================================");
  Serial.print("Identifiant de la puce : ");
  Serial.println(ESP.getChipId());
  Serial.print("Identifiant de la puce flash : "); 
  Serial.println(ESP.getFlashChipId());
  Serial.println("==========================================");
  
  WifiManager espWifi;
  espWifi.connectWifi("DD_box","je suis le reseau de Ste7&Jul5");
  delay(100);
  espWifi.createWifi("espWifi5","12345678");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
