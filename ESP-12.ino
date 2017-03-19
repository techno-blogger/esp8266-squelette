#include "WifiManager.h"
#include "EEPROMManager.h"

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("==========================================");
  Serial.print("Identifiant de la puce : ");
  Serial.println(ESP.getChipId());
  Serial.print("Identifiant de la puce flash : "); 
  Serial.println(ESP.getFlashChipId());
  Serial.println("==========================================");

  // Les identifiants et mots de passe du réseau wifi.
  String monSSID ="";
  String monPWD = "";

  // lecture du SSID et password de l'EEPROM
  EEPROMManager memoire;
  
  String ssid = memoire.lireSSID();
  String pwd  = memoire.lirePassword();

  if (ssid == "" and pwd == ""){
    memoire.ecrireSSID(monSSID);
    memoire.ecrirePassword(monPWD);
    ssid = monSSID;
    pwd = monPWD;
  }
  
  WifiManager espWifi;
  bool wifiConnecte = espWifi.connectWifi(ssid,pwd);

  if (wifiConnecte == false){
    Serial.println("Connexion impossible au réseau");
  }
   
  delay(100);
  espWifi.createWifi("espWifi5","12345678");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
