#include "WifiManager.h"

// =================================== Constructeur ================================
WifiManager::WifiManager(){
  modeSTA_actif = false;
  modeAP_actif  = false;
}

// =================================== Connect Wifi ================================
bool WifiManager::connectWifi(String ssid, String password) {
  Serial.println("");
  Serial.println("****** Connection à un réseau WiFi");
  
  ssidSTA = &ssid;
  passwordSTA = &password;
  
  int compteurBoucle = 0;
  modeSTA_actif = false;
  
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
    Serial.println("Sans MDP"); 
  }else{
    WiFi.begin(ssid.c_str(), password.c_str()); 
    Serial.println("Avec MDP"); 
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

// =================================== Etat STA ================================
bool WifiManager::getSTA_actif(){
  return modeSTA_actif;
}

// =================================== Créer Wifi ================================
bool WifiManager::createWifi(String ssid, String password){
  Serial.println("");
  Serial.println("****** Création d'un réseau WiFi");
  
  ssidAP = &ssid;
  passwordAP = &password;
  
  modeAP_actif = false;
  
  if (password.length() < 8 and password != "" ){
    Serial.println("Création du wifi impossible le mot de passe doit dépasser 8 caractères");
    return false;  
  }

  //Si le mode station n'est pas activé alors on passe en mode point d'acces seul
  //Sinon en mode station et point d'acces 
  if (modeSTA_actif == false) {
    WiFi.mode(WIFI_AP);
    Serial.println("WiFi mode : AP");
  }else{
    WiFi.mode(WIFI_AP_STA); 
    Serial.println("WiFi mode : AP_STA");
  }
  //WiFi.disconnect();

  delay(10);
  
  //si le mot de passe n'est pas renseigné alors on crée un réseau sans
  if (password == ""){
    WiFi.softAP(ssid.c_str()); 
  }else{
    WiFi.softAP(ssid.c_str(), password.c_str()); 
  }
  modeAP_actif = true;
  
  Serial.println("Wifi créé");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  return modeAP_actif;

}

// =================================== Etat AP ================================
bool WifiManager::getAP_actif(){
  return modeAP_actif;
}
