#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

#include "Arduino.h"
#include <EEPROM.h>

#define TAILLE_MEMOIRE 512
static const unsigned long STRUCTVERSION = 20170314;


typedef struct 
{
  //La variable structVersion permet de gérer le cas où aucune 
  //donnée ne se trouve en mémoire (première utilisation du programme)
  unsigned long structVersion;
  
  short int lenSSID;
  String ssid;
  short int lenPWD;
  String pwd;
} StructureEEPROM;
  



class EEPROMManager
{ 
  // ===================================================================    
  public:
    // Lors de l'appel au constructeur on effectue une lecture
    EEPROMManager();
    
    // vider le contenu de l'EEPROM
    void viderEEPROM();

    // Lecture des varaibales de la structure
    String lireSSID();
    String lirePassword();

    //Ecriture des variables de la structure
    void ecrireSSID(String ssid);
    void ecrirePassword(String password);

  // =================================================================== 
  private:
    // Déclaration de la structure
    StructureEEPROM contenuEEPROM; 

    // Lecture de l'EEPROM
    bool lireEEPROM();
    
    // Ecriture de l'EEPROM
    void ecrireEEPROM();

    // Lire des variables de type String dans l'EEPROM
    String lire_StringEEPROM(int Addr, int lengthString);

    // Ecrire des variables de type String dans l'EEPROM
    void ecrire_StringEEPROM(int Addr, String stringEcrite);
};

#endif
