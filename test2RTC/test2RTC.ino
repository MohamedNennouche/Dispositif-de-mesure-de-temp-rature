//=========================================================================================Test 2 RTC DS1307 (plus optimisé en terme de place)
//---------------------------------------------- Bibliothèques
#include "RTClib.h" //--> Télécharger RTClib.h : https://github.com/adafruit/RTClib
//----------------------------------------------

RTC_DS1307 rtc; //--> Initialisation du RTC_DS1307

void setup() {

  Serial.begin(9600);
  Serial.println("Initialisation du RTC DS1307...");
  delay(100);

  //---------------------------------------------- Initialisation RTC DS1307
  if (! rtc.begin()) {
    Serial.println("RTC introuvable");
    while (1);
  }
  //----------------------------------------------

  Serial.println("Initialisation avec succes du RTC DS1307");
  Serial.println();

  Serial.println("Debut de l'activite du RTC DS1307...");
  delay(100);

  //---------------------------------------------- On vérifie si il marche bien
  if (! rtc.isrunning()) {
    Serial.println("RTC ne fonctionne pas!");
    //=========================================================================================
    /* Cette partie du code est à faire juste lors de la première compilation et sert à l'initilisation de l'horloge du RTC 
     *  (Ajuste l'heure par rapport à l'heure du PC)
     
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> Si cette ligne occasionne une erreur utiliser la ligne suivante -> "if (! rtc.isrunning())"
     // Cette ligne ajuste la date explicitement (à deconseiller)
     // January 21, 2014 at 3am you would call:
     rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    */
  }
  //----------------------------------------------

  //---------------------------------------------- Synchronisation le temps du module RTC
  //Serial.println("Synchronisation de la date et de l'heure...");
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> Synchronisation grâce à l'horloge interne du PC
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); //--> Synchronisation manuelle
  //delay(100);
  //Serial.println("Synchronisation faite avec succes");
  //Serial.println();
  // Si la synchronisation a bien ete faite enlever commenter cette partie 
  //----------------------------------------------

  Serial.println("Initalisation reussie du RTC DS1307");
  delay(100);
}

void loop() {

  //---------------------------------------------- Affichage de l'heure et de la date sur le moniteur série chaque seconde
  DateTime now = rtc.now();
  Serial.print("Date ");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" | Heure ");   
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
  //----------------------------------------------
}
