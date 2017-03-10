#include "WifiManager.h"


WifiManager::WifiManager(){
  modeSTA_actif = false;
  modeAP_actif  = false;
}

bool WifiManager::connectWifi(String ssid, String password) {
  
  int compteurBoucle = 0;
  
  //Si le point d'accès n'est pas activé alors on passe en mode station seul
  //Sinon en mode station et point d'acces 
  if (modeAP_actif == false) {
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi mode : STA");
  }else{
    WiFi.mode(WIFI_AP_STA); 
    Serial.println("WiFi mode : AP_STA");
  }

  delay(10);

  //si le mot de passe n'est pas renseigné alors on se connecte sans
  if (password == ""){
    WiFi.begin(ssid.c_str());  
  }else{
    WiFi.begin(ssid.c_str(), password.c_str());  
  }
  
  while (WiFi.status() != WL_CONNECTED && compteurBoucle < 20) {
    delay(500);
    compteurBoucle = compteurBoucle + 1;
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    modeSTA_actif = true;
  }else{
    Serial.println("");
    Serial.println("WiFi not connected");
    
    modeSTA_actif = false; 
  }
  return modeSTA_actif;
}

bool WifiManager::getSTA_actif(){
  return modeSTA_actif;
}

bool WifiManager::createWifi(String ssid,String password){

  //Si le mode station n'est pas activé alors on passe en mode point d'acces seul
  //Sinon en mode station et point d'acces 
  if (modeSTA_actif == false) {
    WiFi.mode(WIFI_AP);
    Serial.println("WiFi mode : AP");
  }else{
    WiFi.mode(WIFI_AP_STA); 
    Serial.println("WiFi mode : AP_STA");
  }

  delay(10);

  //si le mot de passe n'est pas renseigné alors on crée un réseau sans
  if (password == ""){
    WiFi.softAP(ssid.c_str());  
  }else{
    WiFi.softAP(ssid.c_str(), password.c_str());  
  }
  
  Serial.println("");
  Serial.println("Réseau wifi créé");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  return modeAP_actif;
}

bool WifiManager::getAP_actif(){
  return modeAP_actif;
}
