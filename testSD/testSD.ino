// Ce code est un premier test pour l'utilisation d'une carte mémoire, sa fonction : créé un fichier test.txt et écrire dessus
//================================================================================================================================================================
// -------------------------------------Les bibliothèques dont on a besoin
#include <SPI.h>
#include <SD.h>

// -------------------------------------Variable qui va contenir le fichier
File myFile;

void setup() {
// On ouvre le moniteur série
Serial.begin(9600);

while (!Serial) {
; // ------------------------------------On attend que le moniteur s'ouvre
}

// ------------------------------------- Initialisation de la carte mémoire avec la bibliothèque SD.h
Serial.print("Initialisation de la carte SD...");
if (!SD.begin(10)) {
Serial.println("initialisation echouee!");
while (1);
}

Serial.println("initialisation reussie.");
// -------------------------------------Ouverture du fichier (on peut en ouvrir qu'un seul à la fois)
myFile = SD.open("test.txt", FILE_WRITE);

// -------------------------------------Si il s'ouvre correctement : 
if (myFile) {
Serial.print("Ecriture dans test.txt...");
myFile.println("C'est un fichier test :");
myFile.println("Test 1, 2, 3.");
for (int i = 0; i < 20; i++) {
myFile.println(i);
}
// Fermeture du fichier
myFile.close();
Serial.println("Fait.");
} else {
// ------------------------------------Erreur dans le cas où le fichier ne s'est pas ouvert :
Serial.println("Erreur dans l'ouverture de test.txt");
}
}

void loop() {
// ------------------------------------Il n'y a rien qui se passe ici
}
