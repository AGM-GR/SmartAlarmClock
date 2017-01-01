#include "BuzzerController.h"

BuzzerController::BuzzerController(int bz) {

  this->BZPin = bz;
}

//Inicializa el Buzzer
void BuzzerController::begin() {

  pinMode(BZPin, OUTPUT);
}

//Reproduce un "beep" con un tono durante un tiempo
void BuzzerController::beep(int tono, int tiempo) {
  
  analogWrite(BZPin, tono);
  delay(tiempo);
  analogWrite(BZPin, 0);
}

//Reproduce un "tono" con un tono durante un tiempo
void BuzzerController::tono(int tono, int tiempo) {

  if (tono < numTonos) {
    tone(BZPin, tonos[tono]);
    delay(tiempo);
    noTone(BZPin);
  }
}
