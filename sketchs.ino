// Broches du moteur 1
const int motor1Pin1 = 3;  // Input1 du L293D pour contrôler le sens horaire du moteur 1
const int motor1Pin2 = 4;  // Input2 du L293D pour contrôler le sens antihoraire du moteur 1
const int enable1Pin = 5;  // Enable1 du L293D pour activer le moteur 1 (PWM)

// Broches du moteur 2
const int motor2Pin1 = 6;  // Input1 du L293D pour contrôler le sens horaire du moteur 2
const int motor2Pin2 = 7;  // Input2 du L293D pour contrôler le sens antihoraire du moteur 2
const int enable2Pin = 9;  // Enable2 du L293D pour activer le moteur 2 (PWM)

// Broche du capteur d'obstacle
const int obstaclePin = 8; // Broche pour le capteur d'obstacle (entrée numérique)

// Vitesse des moteurs
int vitesse = 255; // Valeur maximale pour pleine vitesse

void setup() {
  // Configurer les broches des moteurs comme sorties
  pinMode(motor1Pin1, OUTPUT); // Contrôle du sens horaire du moteur 1
  pinMode(motor1Pin2, OUTPUT); // Contrôle du sens antihoraire du moteur 1
  pinMode(enable1Pin, OUTPUT); // Activation du moteur 1 avec PWM

  pinMode(motor2Pin1, OUTPUT); // Contrôle du sens horaire du moteur 2
  pinMode(motor2Pin2, OUTPUT); // Contrôle du sens antihoraire du moteur 2
  pinMode(enable2Pin, OUTPUT); // Activation du moteur 2 avec PWM

  // Configurer la broche du capteur comme entrée
  pinMode(obstaclePin, INPUT); // Lecture de l'état du capteur d'obstacle

  // Démarrer les moteurs en mode normal
  demarrerMoteurs();
}

void loop() {
  // Vérifier si un obstacle est détecté
  if (digitalRead(obstaclePin) == HIGH) { // HIGH indique la détection d'un obstacle
    // Obstacle détecté - Reculer les moteurs
    reculer();
    delay(2000); // Pause de 2 secondes

    // Faire tourner uniquement le moteur 1 pour changer de direction
    tournerUnSeulMoteur();
    delay(1000); // Pause de 1 seconde

    // Revenir au mode normal avec les deux moteurs qui avancent
    demarrerMoteurs();
  }
}

// Fonction pour faire avancer les deux moteurs (mode normal)
void demarrerMoteurs() {
  // Faire avancer le moteur 1 (sens horaire)
  digitalWrite(motor1Pin1, HIGH); // Sens horaire pour moteur 1
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, vitesse); // Activer le moteur 1 avec la vitesse définie

  // Faire avancer le moteur 2 (sens horaire)
  digitalWrite(motor2Pin1, HIGH); // Sens horaire pour moteur 2
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enable2Pin, vitesse); // Activer le moteur 2 avec la vitesse définie
}

// Fonction pour faire reculer les deux moteurs
void reculer() {
  // Faire reculer le moteur 1 (sens antihoraire)
  digitalWrite(motor1Pin1, LOW); // Sens antihoraire pour moteur 1
  digitalWrite(motor1Pin2, HIGH);
  analogWrite(enable1Pin, vitesse); // Activer le moteur 1 avec la vitesse définie

  // Faire reculer le moteur 2 (sens antihoraire)
  digitalWrite(motor2Pin1, LOW); // Sens antihoraire pour moteur 2
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enable2Pin, vitesse); // Activer le moteur 2 avec la vitesse définie
}

// Fonction pour faire tourner uniquement le moteur 1
void tournerUnSeulMoteur() {
  // Arrêter le moteur 2
  digitalWrite(motor2Pin1, LOW); // Désactiver le sens horaire pour moteur 2
  digitalWrite(motor2Pin2, LOW); // Désactiver le sens antihoraire pour moteur 2
  analogWrite(enable2Pin, 0); // Arrêter le moteur 2

  // Faire avancer le moteur 1 (sens horaire)
  digitalWrite(motor1Pin1, HIGH); // Sens horaire pour moteur 1
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, vitesse); // Activer le moteur 1 avec la vitesse définie
}
