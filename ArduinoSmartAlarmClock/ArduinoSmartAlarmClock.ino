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
//int powerBT = A0;

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

//Pines Botones
int setButton = A0;
int moreButton = A1;
int lessButton = A2;
int lightButton = A3;

/////////////////////////////////////////////////////////////////////////////
////////////////////////// VARIABLES INTERNAS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int* Color;
char CharRecibido;
String Codigo = "";
int lastMinute = NULL;

//Estado de los bottones
int setState = 1;
int moreState = 1;
int lessState = 1;
int lightState = 1;

//Modulos Conectados
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

  //Inicializa los botones
  pinMode(setButton, INPUT_PULLUP);
  pinMode(moreButton, INPUT_PULLUP);
  pinMode(lessButton, INPUT_PULLUP);
  pinMode(lightButton, INPUT_PULLUP);

  //Inicializamos  el puerto serie
  Serial.begin(9600);
}


void loop() {

  ///////////////////////////////////////////////////////////////////
  ///////////////////// RECEPCIÓN BLUETOOTH /////////////////////////
  ///////////////////////////////////////////////////////////////////

  //Recive datos del módulo Bluetooth
  if (btModule.readChar(CharRecibido)) {
    RecibirCodigo(CharRecibido);
  }

  ///////////////////////////////////////////////////////////////////
  ///////////////////// ACTUALIZACION HORA //////////////////////////
  ///////////////////////////////////////////////////////////////////

  clockModule.GetTime();

  if (lastMinute != clockModule.GetMins()) {
    
    lastMinute = clockModule.GetMins();
    lcdModule.ClearDisplay();
    lcdModule.DrawHour(clockModule.GetStringHour());
    lcdModule.DrawDate(clockModule.GetStringDate());
    lcdModule.DrawBluetooth();
  }

  ///////////////////////////////////////////////////////////////////
  //////////////////////// ESTADO BOTONES  //////////////////////////
  ///////////////////////////////////////////////////////////////////

  setState = digitalRead(setButton);
  moreState = digitalRead(moreButton);
  lessState = digitalRead(lessButton);
  lightState = digitalRead(lightButton);

  //Si se ha pulsado el botón set
  if (setState == LOW) {
    
  } 
  else {
    
  }

  //Si se ha pulsado el botón more
  if (moreState == LOW) {
  
  }
  else {
    
  }

  //Si se ha pulsado el botón less
  if (lessState == LOW) {
  
  }
  else {
    
  }

  //Si se ha pulsado el botón light
  if (lightState == LOW) {
  
  }
  else {
    
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
      //clockModule.ProcessCode(Codigo, btModule);
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
