const int motorPin1 = 3;   // Broche Input1 du L293D pour le sens horaire
const int motorPin2 = 4;   // Broche Input2 du L293D pour le sens antihoraire
const int enablePin = 5;   // Broche Enable1 du L293D pour activer le moteur (PWM)
const int trigPin = 9;     // Broche Trig du capteur à ultrasons
const int echoPin = 10;    // Broche Echo du capteur à ultrasons

int vitesse = 255;         // Vitesse maximale (PWM)
long distance;             // Distance mesurée en cm
long duree;                // Temps pour le signal d'écho

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Initialisation pour afficher les distances
}

void loop() {
  // Mesurer la distance avec le capteur à ultrasons
  distance = mesurerDistance();

  if (distance < 10) {
    Serial.println("Obstacle détecté. Arrêt progressif du moteur.");
    arreterMoteur();
    Serial.println("Inversion progressive du sens !");
    accelererMoteur(0); // Accélérer doucement en sens antihoraire
    delay(2000); // Maintenir le moteur dans le sens inverse
  } else {
    Serial.println("Pas d'obstacle. Sens horaire.");
    accelererMoteur(1); // Accélérer doucement en sens horaire
  }

  delay(100);
}

// Fonction pour mesurer la distance avec le capteur à ultrasons
long mesurerDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duree = pulseIn(echoPin, HIGH, 30000); // Timeout de 30 ms
  if (duree == 0) {
    Serial.println("Pas de mesure valide !");
    return 1000; // Distance élevée si aucune mesure
  }

  distance = duree * 0.034 / 2;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// Fonction pour ralentir progressivement le moteur
void ralentirMoteur() {
  for (int i = vitesse; i >= 0; i -= 10) { // Réduire la vitesse par pas de 10
    analogWrite(enablePin, i);
    delay(50); // Pause pour chaque étape
  }
}

// Fonction pour arrêter complètement le moteur
void arreterMoteur() {
  ralentirMoteur(); // Réduire la vitesse avant d'arrêter
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
  delay(1000); // Pause avant changement de sens
}

// Fonction pour accélérer progressivement le moteur
void accelererMoteur(int sens) {
  for (int i = 0; i <= vitesse; i += 10) { // Augmenter la vitesse par pas de 10
    if (sens == 1) { // Sens horaire
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
    } else { // Sens antihoraire
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
    }
    analogWrite(enablePin, i);
    delay(50); // Pause pour chaque étape
  }
}
