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

void BTController::waitOK() {

  char CharRecibido;
  String ok = "";
  int timeout = TIMEOUT;

  while ((ok != "OK") && (timeout > 0)) {

    delay(1);
    timeout -= 1;
    
    if (btModule.readChar(CharRecibido)) {
      
      if (CharRecibido == 'O')
        ok = CharRecibido;
      else if (ok[0] == 'O')
        ok = ok+CharRecibido;
      else
        ok = "";
    }

    if (ok == "OK")
      Serial.println("OK RECIBIDO.");
    else if (timeout < 1)
      Serial.println("TIMEOUT");
  }
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

int BTController::write(char command) {

  int result = BTmodule.write(command);

  waitOK();
  
  return result;
}

int BTController::write(char* command) {
  
  int result = BTmodule.write(command);

  waitOK();
  
  return result;
}

int BTController::write(String command) {

  int bytesSent = 0;
  char cadena[command.length()];
  
  for(int i=0; i<command.length(); i++)
    cadena[i] = command[i];
    
  bytesSent = BTmodule.write(cadena);

  waitOK();
  
  return bytesSent;
}
