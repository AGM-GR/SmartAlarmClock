#include "BTController.h"
#include "DisplayController.h"
#include "ClockController.h"
#include "RGBLEDController.h"
#include "BuzzerController.h"

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
int lastMinute = NULL;

BTController btModule(RxB, TxB);
DisplayController lcdModule(Clk,Din,DC,CS,RST,BL);
ClockController clockModule;
RGBLEDController rgbLED(RedPin,GreenPin,BluePin,HIGH);
BuzzerController buzzer(BuzzerPin);

/////////////////////////////////////////////////////////////////////////////
////////////////////////// FUNCIONES DE ARDUINO /////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void setup() {

  //Inicializamos el Reloj
  clockModule.begin();
  
  //Inicializamos el LCD
  lcdModule.begin();
  lcdModule.PowerON();
  lcdModule.SetBrightness(100);
  
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

  clockModule.GetTime();

  if (lastMinute != clockModule.GetMins()) {
    
    lastMinute = clockModule.GetMins();
    lcdModule.ClearDisplay();
    lcdModule.DrawHour(clockModule.GetStringHour());
    lcdModule.DrawDate(clockModule.GetStringDate());
    lcdModule.DrawBluetooth();
  }
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

    //El código #C... para el reloj
    case 'C':
      clockModule.ProcessCode(Codigo, btModule);
      //Redibuja la pantalla
      lastMinute = -1;
    break;
    
    //El código #D... para el display
    case 'D':
      lcdModule.ProcessCode(Codigo, btModule);
    break;
    
    //El código #L.. para el modulo led
    case 'L':
      rgbLED.ProcessCode(Codigo, btModule);
    break;
  }

  //Limpia la variable Codigo
  Codigo = "";
}
