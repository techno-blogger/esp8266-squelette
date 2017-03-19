#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 

class WifiManager
{ 
  private:
    bool modeSTA_actif;
    bool modeAP_actif;
      
  public:
    //constructeur
         WifiManager();
         
    // Connection au wifi (mode STA)                                     
    bool connectWifi(String ssid, String password = "");
    
    // Obtenir la valeur du mode STA (actif ou non)
    bool getSTA_actif();
    
    // Création d'un point d'acces (mode AP)
    bool createWifi(String ssid, String password ="");
    
    // Obtenir la valeur du mode AP (actif ou non)
    bool getAP_actif();
};

#endif

