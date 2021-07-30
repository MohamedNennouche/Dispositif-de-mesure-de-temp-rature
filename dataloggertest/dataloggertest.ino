//---------------------------------------------- Bibliothèques utilisées
#include "RTClib.h"
#include "DHT.h"
#include <SD.h>
#include <SPI.h>
//----------------------------------------------

RTC_DS1307 rtc; //--> Initilisation du RTC_DS1307

#define DHTPIN 2 //--> Pin utilisé par le DHT  
#define DHTTYPE DHT22 //--> Type du capteur DHT utilisé 
DHT dht(DHTPIN, DHTTYPE);

File myFile; //--> Initialisation du fichier
const int chipSelect = 4; //--> Pin CS utilisée

unsigned long previousMillis = 0; //--> Servira pour stocker le dernier temps utilisé
const long interval = 1000; //--> Interval utilisé (1000 = 1 seconde)

void setup() {
  
  Serial.begin(9600);

  Serial.println("Initilisation du RTC DS1307...");
  delay(100);

  //----------------------------------------------Initialisation du RTC DS1307
  if (! rtc.begin()) {
    Serial.println("RTC introuvable");
    while (1);
  }
  //----------------------------------------------

  Serial.println("Initialisation faite avec succes du RTC DS1307");
  Serial.println();

  Serial.println("Debut du fonctionnement du RTC DS1307...");
  delay(100);

  //---------------------------------------------- Vérification si le module peut fonctionner correctement
  if (! rtc.isrunning()) {
    Serial.println("RTC ne marche pas!");
    // Ces lignes permettront de resynchroniser le module RTC avec l'horloge interne du PC
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> Si cette ligne ne marche pas utiliser cette ligne de code "if (! rtc.isrunning())"
    // Pour synchroniser manuellement
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //----------------------------------------------

  //----------------------------------------------Synchronisation du temps et de la date du module RTC
  // A faire lors de la premiere compilation pour synchroniser le module avec l'horloge interne du PC
  //Serial.println("Ajustement du temps et de la date...");
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> En cas de problème à changer avec -> "if (! rtc.isrunning())"
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  //delay(100);
  //Serial.println("Synchronisation faite avec succes !");
  //Serial.println();
  // Si ca ne marche pas revérifiez le cablage et recompilez le code.
  //----------------------------------------------

  Serial.println("RTC DS1307 fonctionne bien");
  delay(100);

  //---------------------------------------------- Utilisation du DHT22
  Serial.println("Start DHT22");
  dht.begin();
  delay(100);
  Serial.println();
  //----------------------------------------------

  //---------------------------------------------- Initialisation du module de carte mémoire
  Serial.println("Initialisation du module de carte Micro SD...");
  delay(100);

  if (!SD.begin(chipSelect)) {
    Serial.println("Initialisation echouee!");
    while (1);
  }

  Serial.println("Initialisation faite avec succes");
  Serial.println();
  delay(100);
  //----------------------------------------------
}

void loop() {
  
  //___________________________________________________________________________________ Utilisation de Millis pour la définition de l'intervalle
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Sauvegarde du dernier moment ou on a pris une mesure
    previousMillis = currentMillis;

    DateTime now = rtc.now(); //--> Mise à jour du temps actuel

    //---------------------------------------------- Les valeurs de températures et d'humidité
    int h = dht.readHumidity();
    // Température en Celcius par défaut
    float t = dht.readTemperature();
    //----------------------------------------------

    //---------------------------------------------- Vérification di la lecture s'est bien faite sinon on quitte
    if (isnan(h) || isnan(t)) {
      Serial.println("Lecture du capteur DHT22 impossible");
      delay(500);
      return;
    }
    //----------------------------------------------

    //___________________________________________________________________________________ Ecriture sur la carte mémoire
    // Ecriture (le format peut changer si vous voulez)
    if (now.second() %5 == 0) {
      Serial.println("----");
      //---------------------------------------------- Affichage sur le moniteur série
      Serial.print(now.day(), DEC);
      Serial.print('/');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.print(now.year(), DEC);
      Serial.print(" ");   
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.println();
      //----------------------------------------------

      //---------------------------------------------- Affichage de la température et de l'humidité
      Serial.print("Temperature : ");
      Serial.print(h);
      Serial.print(" | Humidite : ");
      Serial.println(t);
      Serial.println();
      //----------------------------------------------
    
      //___________________________________________________________________________________ Ecrirture sur la carte mémoire
      //---------------------------------------------- Ouverture du fichier sur la carte mémoire (s'il n'existe pas il y sera créé)
      myFile = SD.open("DHT22Log.txt", FILE_WRITE);
      //----------------------------------------------
    
      //---------------------------------------------- Ecriture sur ce fichier les données du capteur
      // Si l'ouverture se fait sans problème écrire dessus :
      if (myFile) {
        Serial.println("Ecriture sur DHT22Log.txt...");
        
        //---------------------------------------------- Ecriture des données
        myFile.print(now.day());
        myFile.print("-");
        myFile.print(now.month());
        myFile.print("-");
        myFile.print(now.year());
        //----------------------------------------------
        
        myFile.print(","); //--> Ecriture pour délimiter les différente parties (pour une conversion en fichier CSV efficace)

        //---------------------------------------------- Ecriture du temps sur la carte mémoire
        myFile.print(now.hour());
        myFile.print(":");
        myFile.print(now.minute());
        myFile.print(":");
        myFile.print(now.second());
        //----------------------------------------------
    
        myFile.print(","); //--> Délimiteur
        
        myFile.print(t); //--> Température
    
        myFile.print(","); //--> Délimiteur
    
        myFile.println(h); //--> Humidité
          
        myFile.close(); //--> Fermer le fichier
        
        Serial.println("Ecriture sur la carte memoire faite avec succes");
        Serial.println("----");
        Serial.println();
      } else {      
        Serial.println("Erreur lors de l'ouverture du fichier DHT11Log.txt"); //--> Si le fichier ne s'ouvre pas, afficher une erreur
      }
      //----------------------------------------------
      //___________________________________________________________________________________
    }
    //___________________________________________________________________________________
  }
  //___________________________________________________________________________________
}
//=========================================================================================
