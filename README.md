# M.A.R.K

M.A.R.K est un robot modulaire destiné à l'apprentissage. La carte [Arduino Mega] et la librairie fournie permettent une utilisation simple des principaux modules. L'[IDE Arduino] procure les outils nécessaires pour programmer le micro-contrôleur de la carte [Arduino Mega], le celèbre [ATmega2560]. 

[IDE Arduino]: https://www.arduino.cc/en/Main/Software/
[Arduino Mega]:https://www.generationrobots.com/fr/401945-arduino-mega-2560-rev3.html
[ATmega2560]: http://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf

## Installation

### IDE Arduino
Page de téléchargement : <br />
https://www.arduino.cc/en/Main/Software

Tutoriels d'installation : <br />
https://www.arduino.cc/en/Guide/Windows<br />
https://www.arduino.cc/en/Guide/Linux <br />
Le paquet Arduino est également présent dans les dépôts Universe d'Ubuntu.

### M.A.R.K librairie

1. [Télécharger le git](https://github.com/generationrobots-lab/MARK/archive/master.zip)
2. Décompresser l'archive et la placer dans un répertoire de votre choix.
3. Lancer l'IDE Arduino 
4. Dans  `Fichier => Préférences => Paramètres`, le champ "Emplacement du carnet de croquis" doit pointer vers le dossier "Software" de l'archive fraîchement décompressée et rangée (exemple : D:\MARK-master\Software)
5. Dans l'IDE Arduino, vous devriez voir apparaitre dans `Ficher => Exemples => MARK` les exemples pour débuter avec votre M.A.R.K.


Il est également possible de fusionner le dossier Software avec le dossier que vous utilisez déjà (par defaut C:\Users\..\Documents\Arduino).

## Code d'exemple 

```c++
#include <MARK.h>

MARK myrobot; //initialize an instance of the class

void setup() {
  myrobot.begin();
  delay(50);
  myrobot.setLeftMotor(50);
  myrobot.setRightMotor(50);
  delay(3000); //forward 3s
  myrobot.stopLeftMotor();
  myrobot.stopRightMotor();
}

void loop() {
  //nothing
  delay(300);
}

```

## Documentation
Pour plus d'informations, merci de consulter le [wiki.](https://github.com/generationrobots-lab/MARK/wiki)

## Developement

### Contribution


Pour toute contribution au maintien ou à l'amélioration de la librairie, merci de faire un "pull request".  <br />
Pour remonter des problèmes, merci d'ouvrir un ticket dans les "issues".
