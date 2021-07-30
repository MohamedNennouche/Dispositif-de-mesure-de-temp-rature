# Dispositif-de-mesure-de-temp-rature
Les codes suivants servent à la fabrication d'un dispositif de mesure de température en utilisation une sonde de température basée sur une résistance à coefficient de température négative avec une interface sur écran OLED.

# Description des dossiers
- Les fichiers testSD et test2SD servent au tests du module lecteur de carte mémoire : le premier servira au test d'écriture, le deuxième servira au test du bon fonctionnement de la carte mémoire (fichiers, système de fichiers, volume...)
- les fichiers testRTC et test2RTC avec deux différentes bibliothèques avec partie d'initialisation à décommenter au besoin
- le fichier testDHT est un fichier qui servira au test des capteurs de type DHT (DHT11,DHT22...)
- le fichier dataloggertest est le fichier final qui servira à jumeler les 3 modules, ainsi receuillir la donnée à partir du capteur DHT, l'heure et la date à partir du module RTC et ainsi l'enregistrement sur un fichier de type texte sur la carte mémoire via le module lecteur. 
