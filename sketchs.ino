// Broches du moteur 1
const int motor1Pin1 = 3;  // Input1 du L293D pour le moteur 1
const int motor1Pin2 = 4;  // Input2 du L293D pour le moteur 1
const int enable1Pin = 5;  // Enable1 du L293D pour le moteur 1 (PWM)

// Broches du moteur 2
const int motor2Pin1 = 6;  // Input1 du L293D pour le moteur 2
const int motor2Pin2 = 7;  // Input2 du L293D pour le moteur 2
const int enable2Pin = 9;  // Enable2 du L293D pour le moteur 2 (PWM)

// Broche du capteur d'obstacle
const int obstaclePin = 8; // Broche pour le capteur d'obstacle (entrée numérique)

// Vitesse des moteurs
int vitesse = 255;

void setup() {
  // Configurer les broches des moteurs comme sorties
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // Configurer la broche du capteur comme entrée
  pinMode(obstaclePin, INPUT);

  // Démarrer les moteurs
  demarrerMoteurs();
}

void loop() {
  // Vérifier si un obstacle est détecté
  if (digitalRead(obstaclePin) == HIGH) {
    // Obstacle détecté - Reculer
    reculer();
    delay(2000); // Pause de 2 secondes

    // Tourner en utilisant un seul moteur
    tournerUnSeulMoteur();
    delay(1000); // Pause de 1 seconde

    // Retourner au mode normal
    demarrerMoteurs();
  }
}

// Fonction pour démarrer les moteurs dans le mode normal
void demarrerMoteurs() {
  // Faire avancer les deux moteurs
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, vitesse);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enable2Pin, vitesse);
}

// Fonction pour reculer les moteurs
void reculer() {
  // Inverser le sens des deux moteurs
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  analogWrite(enable1Pin, vitesse);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enable2Pin, vitesse);
}

// Fonction pour faire tourner un seul moteur
void tournerUnSeulMoteur() {
  // Arrêter le moteur 2
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enable2Pin, 0);

  // Faire avancer le moteur 1
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, vitesse);
}
