const int motorPin1 = 3; // Broche Input1 du L293D pour le sens horaire
const int motorPin2 = 4; // Broche Input2 du L293D pour le sens antihoraire
const int enablePin = 5; // Broche Enable1 du L293D pour activer le moteur (pwm)
int vitesse = 255;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Activer le moteur en utilisant le PWM (valeur maximale pour pleine vitesse)
  
}

void loop() {
  // Rotation dans le sens horaire
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, vitesse);
  delay(2000); // Pause de 2 secondes

  // Arrêter le moteur 
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(2000); // Pause entre les changements de sens 
 // Rotation dans le sens antihoraire
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, vitesse);
  delay(2000); // Pause de 2 secondes

  // Arrêter le moteur
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(2000); // Pause entre les cycles
}
