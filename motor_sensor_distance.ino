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
    Serial.println("Obstacle détecté. Arrêt du moteur.");
    arreterMoteur();
    Serial.println("Inversion du sens !");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    analogWrite(enablePin, vitesse);
    delay(2000);
  } else {
    Serial.println("Pas d'obstacle. Sens horaire.");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    analogWrite(enablePin, vitesse);
  }

  delay(100);
}

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

void arreterMoteur() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
  delay(1000); // Pause avant changement de sens
}
