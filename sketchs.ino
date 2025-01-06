// Broches du moteur 1
const int motor1Pin1 = 4;  // Input1 du L293D pour le moteur 1 3
const int motor1Pin2 = 3;  // Input2 du L293D pour le moteur 1 4
const int enable1Pin = 5;  // Enable1 du L293D pour le moteur 1 (PWM)5

// Broches du moteur 2
const int motor2Pin1 = 7;  // Input1 du L293D pour le moteur 2 6 
const int motor2Pin2 = 6;  // Input2 du L293D pour le moteur 2 7 
const int enable2Pin = 9;  // Enable2 du L293D pour le moteur 2 (PWM)9  

// Broches du capteur à ultrasons (HC-SR04)
const int trigPin = 10; // Pin Trig du capteur
const int echoPin = 11; // Pin Echo du capteur

// Vitesse des moteurs
int vitesse = 255;

// Distance minimale pour considérer un obstacle (en cm)
const int distanceSeuil = 15;

void setup() {
  // Configurer les broches des moteurs comme sorties
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // Configurer les broches du capteur comme sorties/entrées
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialiser la communication série pour le débogage
  Serial.begin(9600);

  // Démarrer les moteurs
  demarrerMoteurs();
}

void loop() {
  // Lire la distance à partir du capteur à ultrasons
  int distance = mesurerDistance();

  // Débogage : Afficher la distance mesurée
  Serial.print("Distance mesurée : ");
  Serial.print(distance);
  Serial.println(" cm");

  // Si un obstacle est détecté (distance inférieure au seuil)
  if (distance <= distanceSeuil) {
    // Reculer les deux moteurs
    reculer();
    delay(1000); // Pause de 2 secondes ****change

    // Faire tourner un seul moteur
    tournerUnSeulMoteur();
    delay(1000); // Pause de 1 seconde

    // Revenir au mode normal (avancer les deux moteurs)
    demarrerMoteurs();
  }
}

// Fonction pour mesurer la distance avec le capteur à ultrasons
int mesurerDistance() {
  // Envoyer une impulsion sur le Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lire la durée de l'impulsion Echo
  long duree = pulseIn(echoPin, HIGH);

  // Convertir la durée en distance (cm)
  int distance = duree * 0.034 / 2;

  return distance;
}

// Fonction pour faire avancer les deux moteurs (mode normal)
void demarrerMoteurs() {
  // Faire avancer le moteur 1 (sens horaire)
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, vitesse);

  // Faire avancer le moteur 2 (sens horaire)
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enable2Pin, vitesse);
}

// Fonction pour reculer les deux moteurs
void reculer() {
  // Faire reculer le moteur 1 (sens antihoraire)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  analogWrite(enable1Pin, vitesse);

  // Faire reculer le moteur 2 (sens antihoraire)
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enable2Pin, vitesse);
}

// Fonction pour faire tourner uniquement le moteur 1
void tournerUnSeulMoteur() {
  // Arrêter le moteur 2
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enable2Pin, 0);

  // Faire avancer le moteur 1 (sens horaire)
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(enable1Pin, vitesse);
}
