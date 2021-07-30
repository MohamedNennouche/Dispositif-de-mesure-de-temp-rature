//========================================================================================= Test du DHT22
//---------------------------------------------- On inclue la bibliothèque
#include "DHT.h"
//----------------------------------------------

#define DHTPIN 2 //--> Pin de la carte reliée à la pin de donnée du DHT 
#define DHTTYPE DHT22 //--> Type du capteur DHT (DHT11/DHT22)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // ------------------------------------------- Initialisation du moniteur série
  Serial.begin(9600);
  delay(100);
  
  //---------------------------------------------- Initialisation du DHT22
  Serial.println("Initialisation du DHT22");
  dht.begin();
  delay(100);
  Serial.println();
  //----------------------------------------------
}

void loop() {

  //---------------------------------------------- Receuillir ou mettre à jour les valeurs de température et d'humidité
  //---------------------------------------------- La lecture de la température et de l'humidité prend jusqu'à 250 ms voire jusqu'à 2s pour les vieux capteurs
  int h = dht.readHumidity();
  //---------------------------------------------- C'est en celcius par défaut
  float t = dht.readTemperature();
  //----------------------------------------------

  //---------------------------------------------- Vérification s'il n'y pas eu d'erreur de lecture
  //---------------------------------------------- S'il y a eu une erreur on quitte et on refait 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read Data from DHT sensor!");
    delay(500);
    return;
  }
  //----------------------------------------------

  //---------------------------------------------- Ecriture de la valeur de température et d'humidité sur le moniteur série
  Serial.print("Temperature : ");
  Serial.print(h);
  Serial.print(" | Humidity : ");
  Serial.println(t);
  delay(2000);
  //----------------------------------------------
}
//=========================================================================================
