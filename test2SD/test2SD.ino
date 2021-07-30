//=========================================================================================Test 2 module carte SD
/*
  Ce code servira à tester le bon fonctionnement d'une carte mémoire ainsi que donner un certain nombre
  d'information qui pourrait être utile : le type de la carte mémoire, taille... 

  Le montage : 
  * Le module est relié via le bus SPI comme suit :
  ** UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (pin CS peut être changée librement)
     et la pin #10 (SS) doit être une sortie (OUTPUT)
  ** Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 4 (pin CS peut être changée librement)
     et la pin #52 (SS) doit être une sortie (OUTPUT) 
*/
//----------------------------------------------Includes Libraries
#include <SD.h>
#include <SPI.h>
//----------------------------------------------

Sd2Card card; //--> Initialisation de la carte SD
SdVolume volume; //--> Initialisation du volume
SdFile root; //--> Initialisation de l'arborescence 

const int chipSelect = 4; //--> Choix de la pin CS

void setup() {
  Serial.begin(9600);

  Serial.print("Initialisation du module micro SD...");
  Serial.println();

  //---------------------------------------------- Vérification si la carte mémoire peut être lue sans problème
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("Initialisation echouee !");
    Serial.println("* Est ce que la carte memoire est bien inseree ?");
    Serial.println("* Les connexion sont justes ?");
    Serial.println("* Verifiez le cablage, peut etre l'un deux est endommage !");
    while (1);
  } else {
    Serial.println();
    Serial.println("Initialiation reussie");
  }
  //----------------------------------------------

  Serial.println();
  Serial.print("Type de la micro SD : ");

  //---------------------------------------------- Les types de cartes SD
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
    case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
    case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
    default:
    Serial.println("Type inconnu a eviter !!!"); 
  }
  //----------------------------------------------

  //---------------------------------------------- Système de fichiers de la carte mémoire
  if (!volume.init(card)) {
    Serial.println("Systeme de fichier FAT16 / FAT32 introuvable !!!");
    Serial.println("Soyez sure que la carte memoire est formatee sur les systemes de fichiers FAT16 / FAT32.");
    while (1);
  }
  //----------------------------------------------

  //---------------------------------------------- Affichage du volume et du système de fichiers
  uint32_t volumesize;
  
  Serial.println();
  Serial.print("Type de volume is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();
  volumesize *= volume.clusterCount();

  volumesize *= 512;   
  Serial.print("Volume (octets): ");
  Serial.println(volumesize);

  Serial.print("Volume (Koctets): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.print("Volume (Moctets): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.print("Volume (Goctets): ");
  float vsg = volumesize;
  float VG  = vsg / 1024;
  Serial.println(VG);
  //----------------------------------------------

  //---------------------------------------------- Affichage des fichiers à l'intérieure de la carte mémoire
  Serial.println();
  Serial.println("Fichiers dans la carte memoire (nom, date et taille en octets : ");

  root.openRoot(volume);

  root.ls(LS_R | LS_DATE | LS_SIZE);
  //----------------------------------------------
}

void loop() {
  // Y a rien ici 
}
//=========================================================================================
