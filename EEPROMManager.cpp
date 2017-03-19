#include "EEPROMManager.h"

// =================================== Constructeur ================================
EEPROMManager::EEPROMManager(){
  
  
  if(lireEEPROM() == false){ 
    viderEEPROM();
  }
  
  contenuEEPROM.structVersion = STRUCTVERSION;
};

// =================================== Vider l'EEPROM ================================
void EEPROMManager::viderEEPROM(){
  EEPROM.begin(TAILLE_MEMOIRE);
  Serial.println("");
  Serial.println("****** Vidage de l'EEPROM");
  for (int i = 0; i < TAILLE_MEMOIRE; i++){
    EEPROM.write(i, 0);  
  }   
  EEPROM.commit();  
//  EEPROM.end();
};

// =================================== lire EEPROM ================================
bool EEPROMManager::lireEEPROM(){
  bool retour = false;
  int adrLectureEE;
  
  EEPROM.begin(TAILLE_MEMOIRE);
  Serial.println("");
  Serial.println("****** Lecture de l'EEPROM");

  adrLectureEE = 0;
  EEPROM.get( adrLectureEE, contenuEEPROM.structVersion );
  
  Serial.println("Controle de la validité des données.");
  if(contenuEEPROM.structVersion != STRUCTVERSION){
    Serial.print("La version de l'EEPROM est différente de : ");
    Serial.println(STRUCTVERSION);
    Serial.print("Version EEPROM => ");
    Serial.println(contenuEEPROM.structVersion);

    retour = false;
  }else{
    Serial.print("La version de l'EEPROM est correcte :");
    Serial.println(contenuEEPROM.structVersion);

    adrLectureEE = adrLectureEE  + sizeof(contenuEEPROM.structVersion);
    EEPROM.get( adrLectureEE, contenuEEPROM.lenSSID);  
    
    adrLectureEE = adrLectureEE  + sizeof(contenuEEPROM.lenSSID);
    contenuEEPROM.ssid = lire_StringEEPROM(adrLectureEE,contenuEEPROM.lenSSID);
    Serial.print("-> Adresse debut lecture = ");
    Serial.print(adrLectureEE);
    Serial.print(" // Longueur SSID : ");
    Serial.println(contenuEEPROM.lenSSID);
    Serial.print("-> valeur ssid : ");
    Serial.println(contenuEEPROM.ssid);
  
    adrLectureEE = adrLectureEE  + sizeof(contenuEEPROM.ssid);
    EEPROM.get( adrLectureEE, contenuEEPROM.lenPWD);
  
    adrLectureEE = adrLectureEE  + sizeof(contenuEEPROM.lenPWD);
    contenuEEPROM.pwd = lire_StringEEPROM(adrLectureEE,contenuEEPROM.lenPWD);
    Serial.print("-> Adresse debut lecture = ");
    Serial.print(adrLectureEE);
    Serial.print(" // Longueur password : ");
    Serial.println(contenuEEPROM.lenPWD);
    Serial.print("-> valeur password : ");
    Serial.println(contenuEEPROM.pwd);
    
    retour = true;
  }

  return retour;
};

// =================================== Lire string EEPROM ================================
String EEPROMManager::lire_StringEEPROM(int Addr, int lengthString)
{
  char cbuff[lengthString];
  String stemp="";
  
  for (int i = 0; i < lengthString; i++){
    cbuff[i] = EEPROM.read(Addr+i);
    stemp.concat(cbuff[i]);
//    delay(10);
  }
  return stemp;
}

// =================================== Ecrire EEPROM ================================
void EEPROMManager::ecrireEEPROM(){
  int adrEcritureEE;
  
  EEPROM.begin(TAILLE_MEMOIRE);
  Serial.println("");
  Serial.print("****** Ecriture dans l'EEPROM => version :");
  Serial.println(STRUCTVERSION);

  adrEcritureEE = 0;
  contenuEEPROM.structVersion = STRUCTVERSION;
  Serial.print("adresse =");
  Serial.print(adrEcritureEE);
  Serial.print("  => structVersion =");
  Serial.println(contenuEEPROM.structVersion);
  EEPROM.put( adrEcritureEE, contenuEEPROM.structVersion );

  adrEcritureEE = adrEcritureEE  + sizeof(contenuEEPROM.structVersion);
  Serial.print("adresse =");
  Serial.print(adrEcritureEE);
  Serial.print("  => lenSSID =");
  Serial.println(contenuEEPROM.lenSSID);
  EEPROM.put( adrEcritureEE, contenuEEPROM.lenSSID);
  
  adrEcritureEE = adrEcritureEE  + sizeof(contenuEEPROM.lenSSID);
  Serial.print("adresse =");
  Serial.print(adrEcritureEE);
  Serial.print("  => ssid =");
  Serial.println(contenuEEPROM.ssid);
  ecrire_StringEEPROM(adrEcritureEE, contenuEEPROM.ssid);

  adrEcritureEE = adrEcritureEE  + sizeof(contenuEEPROM.ssid);
  Serial.print("adresse =");
  Serial.print(adrEcritureEE);
  Serial.print("  => lenPWD =");
  Serial.println(contenuEEPROM.lenPWD);
  EEPROM.put( adrEcritureEE, contenuEEPROM.lenPWD);

  adrEcritureEE = adrEcritureEE  + sizeof(contenuEEPROM.lenPWD);
  Serial.print("adresse =");
  Serial.print(adrEcritureEE);
  Serial.print("  => pwd =");
  Serial.println(contenuEEPROM.pwd);
  ecrire_StringEEPROM(adrEcritureEE, contenuEEPROM.pwd);

  EEPROM.commit();
};

// =================================== Ecrire string EEPROM ================================
void EEPROMManager::ecrire_StringEEPROM(int Addr, String stringEcrite)
{ 
  char cbuff[stringEcrite.length()];
  stringEcrite.toCharArray(cbuff,stringEcrite.length()+1);
 
  for (int i = 0; i < stringEcrite.length(); i++) {
    EEPROM.write(Addr + i,cbuff[i]);
  }
}

// =================================== Ecrire SSID ================================
void EEPROMManager::ecrireSSID(String ssid){
  if(contenuEEPROM.ssid != ssid){
    contenuEEPROM.ssid = ssid;
    contenuEEPROM.lenSSID = contenuEEPROM.ssid.length();
    
    ecrireEEPROM(); 
    Serial.println("SSID");     
  }
};

// =================================== Lire SSID ================================
String EEPROMManager::lireSSID(){
  return contenuEEPROM.ssid ;   
};

// =================================== Ecrire Password ================================
void EEPROMManager::ecrirePassword(String password){
  if(contenuEEPROM.pwd != password){
    contenuEEPROM.pwd = password;
    contenuEEPROM.lenPWD = contenuEEPROM.pwd.length();
    
    ecrireEEPROM();   
    Serial.println("Password");   
  }
};

// =================================== Lire password ================================
String EEPROMManager::lirePassword(){
  return contenuEEPROM.pwd ;   
};
