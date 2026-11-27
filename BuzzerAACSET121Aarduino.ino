const int buzzerPin = 8;

void setup() {
  pinMode(buzzerPin, OUTPUT);

  // 1. Teste como Buzzer ATIVO (tensão contínua)
  // Se apitar alto aqui, o seu buzzer é ATIVO.
  //digitalWrite(buzzerPin, HIGH);
  //delay(1000);
  //digitalWrite(buzzerPin, LOW);
  //delay(1000);

  // 2. Teste como Buzzer PASSIVO (sinal de 2300 Hz)
  // Se só apitar aqui (ou soar muito mais alto aqui), é PASSIVO.
  tone(buzzerPin, 2300); 
  delay(1000);
  noTone(buzzerPin);
  delay(2000);


}

void loop() {

}