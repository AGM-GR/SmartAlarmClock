#include "BTController.h"
#include <SoftwareSerial.h>

BTController::BTController(int RX, int TX, int key, int power, int baudios) {

  this->Rx = RX;
  this->Tx = TX;
  this->KEY = key;
  this->POWER = power;
  this->Baudios = baudios;
  this->BTmodule = SoftwareSerial(Rx,Tx);
}


BTController::BTController(int RX, int TX, int power, int baudios) {

  this->Rx = RX;
  this->Tx = TX;
  this->KEY = NULL;
  this->POWER = power;
  this->Baudios = baudios;
  this->BTmodule = SoftwareSerial(Rx,Tx);
}

BTController::BTController(int RX, int TX, int baudios) {

  this->Rx = RX;
  this->Tx = TX;
  this->KEY = NULL;
  this->POWER = NULL;
  this->Baudios = baudios;
  this->BTmodule = SoftwareSerial(Rx,Tx);
}

BTController::BTController(int RX, int TX) {
  
  this->Rx = RX;
  this->Tx = TX;
  this->KEY = NULL;
  this->POWER = NULL;
  this->Baudios = 9600;
  this->BTmodule = SoftwareSerial(Rx,Tx);
}

//Inicializa el Módulo Bluetooth
void BTController::begin() {
  
  if (KEY != NULL)
    pinMode(KEY, OUTPUT);
    
  if (POWER != NULL) {
    pinMode(POWER, OUTPUT);
    PowerON();
    
  } else {
    ON = true;
    BTmodule.begin(Baudios);
    BTmodule.flush(); //Limpia cache
    delay(500); //Tiempo para esperar arranque del modulo
  }
}

//Enciende el Módulo Bluetooth
void BTController::PowerON() {

  if (!ON && POWER != NULL) {
    ON = true;
    digitalWrite(POWER, HIGH);
    
    BTmodule.begin(Baudios);
    BTmodule.flush(); //Limpia cache
    delay(500); //Tiempo para esperar arranque del modulo
  }
}

//Apaga el Módulo Bluetooth
void BTController::PowerOFF() {

  if (ON && POWER != NULL) {
    ON = false;
    digitalWrite(POWER, LOW); 
  }
}

//Cambia entre apagado y encendido
void BTController::SwitchPower() {
  
  if (ON)
    PowerOFF();
  else
    PowerON();
}

//Devuelve el estado del BT
bool BTController::isON() {
  return ON;
}

bool BTController::readChar(char &command) {

  bool datoRecibido = false;
  
  if (BTmodule.available()) {
    datoRecibido = true;
    command = BTmodule.read();
    BTmodule.flush();
  
  } else {
    datoRecibido = false;
  }

  return datoRecibido;
}

int BTController::sendBT(char command) {
  
  return BTmodule.write(command);
}

int BTController::sendBT(char* command) {
  
  return BTmodule.write(command);
}

int BTController::sendBT(String command) {

  int bytesSent = 0;

  for(int i=0; i<command.length(); i++)
    bytesSent += BTmodule.write(command[i]);
  
  return bytesSent;
}
