#include "BTController.h"
#include "LCD5110Controller.h"
#include "RGBLEDController.h"
#include "BUZZERController.h"

/////////////////////////////////////////////////////////////////////////////
///////////////////// VARIABLES DE CONFIGURACIÓN ////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//Pines módulo Bluetooth
int RxB = 11;
int TxB = 12;

//Pines LCD Nokia5110
int Clk = 7;
int Din = 6;
int DC = 5;
int CS = 4;
int RST = 3;
int BL = 2;

//Pines LED RGB
int RedPin = 8;
int GreenPin = 9;
int BluePin = 10;

//Pin Buzzer
int BuzzerPin = 13;

/////////////////////////////////////////////////////////////////////////////
////////////////////////// VARIABLES INTERNAS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int* Color;
char CharRecibido;
String Codigo = "";

BTController btModule(RxB, TxB);
LCD5110Controller lcdModule(Clk,Din,DC,CS,RST,BL);
RGBLEDController rgbLED(RedPin,GreenPin,BluePin,HIGH);
BUZZERController buzzer(BuzzerPin);

/////////////////////////////////////////////////////////////////////////////
////////////////////////// FUNCIONES DE ARDUINO /////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void setup() {

  //Inicializamos el LCD
  lcdModule.begin();
  lcdModule.PowerON();
  lcdModule.SetBrightness(100);
  lcdModule.DrawHour("1425");
  lcdModule.DrawDate("260695");
  lcdModule.DrawBluetooth();

  //Inicializamos modulo BT
  btModule.begin();
  
  //Inicializamos el Led RGB
  rgbLED.begin();

  //Inicializamos el Buzzer
  buzzer.begin();

  //Inicializamos  el puerto serie
  Serial.begin(9600);
}


void loop() {

  //Recive datos del módulo Bluetooth
  if (btModule.readChar(CharRecibido)) {
    RecibirCodigo(CharRecibido);
  }

  //Un pequeño delay para aumantar la estabilidad
  delay(2);
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNCIONES PROPIAS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////


//Función para recibir códigos del módulo BT
void RecibirCodigo (char recibido) {

  //Lee los códigos Recibidos por Bluetooth
  // Los códigos empiezan por '#' 
  // seguido de una letra que indica para que son y seguido de los datos.
  // La recepcion de un código acaba al recibir el simbolo '$'.
  if (recibido == '#')
    Codigo = recibido;
  else if (recibido == '$')
    procesarCodigo();
  else if (Codigo[0] == '#')
    Codigo = Codigo+recibido;
}

//Función para procesar los códigos recibidos
void procesarCodigo() {

  switch (Codigo[1]) {

    //El código #D... para el display
    case 'D':
      lcdModule.SwitchPower();
    break;
    
    //El código #L.. para el modulo led
    case 'L':
      rgbLED.ProcessCode(Codigo, btModule);
    break;

  }

  //Limpia la variable Codigo
  Codigo = "";
}
