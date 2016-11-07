#include "BUZZERController.h"

BUZZERController::BUZZERController(int bz) {

  this->BZPin = bz;
}

//Inicializa el Buzzer
void BUZZERController::begin() {

  pinMode(BZPin, OUTPUT);
}

//Reproduce un "beep" con un tono durante un tiempo
void BUZZERController::beep(int tono, int tiempo) {
  
  analogWrite(BZPin, tono);
  delay(tiempo);
  analogWrite(BZPin, 0);
}

//Reproduce un "tono" con un tono durante un tiempo
void BUZZERController::tono(int tono, int tiempo) {

  if (tono < numTonos) {
    tone(BZPin, tonos[tono]);
    delay(tiempo);
    noTone(BZPin);
  }
}
