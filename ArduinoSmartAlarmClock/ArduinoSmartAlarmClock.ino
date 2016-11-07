#include "BTController.h"
#include "LCD5110Controller.h"
#include "RGBLEDController.h"
#include "BUZZERController.h"

/******************************************************/

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

/******************************************************/

//Variables internas
int* Color;
char CharRecivido;
String Codigo = "";

BTController btModule(RxB, TxB);
LCD5110Controller lcdModule(Clk,Din,DC,CS,RST,BL);
RGBLEDController rgbLED(RedPin,GreenPin,BluePin,HIGH);
BUZZERController buzzer(BuzzerPin);

void setup() {

  //Inicializamos modulo BT
  btModule.begin();

  //Inicializamos el LCD
  lcdModule.begin();
  lcdModule.PowerON();
  lcdModule.SetBrightness(100);
  
  //Inicializamos el Led RGB
  rgbLED.begin();

  //Inicializamos el Buzzer
  buzzer.begin();

  //Inicializamos  el puerto serie
  Serial.begin(9600);
}

void loop() {

  //Recive datos del módulo Bluetooth
  if (btModule.readChar(CharRecivido)) {

    //Lee los códigos recividos por Bluetooth
    // Los códigos empiezan por '#' 
    // seguido de una letra que indica para que son y seguido de los datos.
    // La recepcion de un código acaba al recibir el simbolo '$'.
    if (CharRecivido == '#')
      Codigo = CharRecivido;
    else if (CharRecivido == '$')
      procesarCodigo();
    else if (Codigo[0] == '#')
      Codigo = Codigo+CharRecivido;
  
  }

  //Un pequeño delay para aumantar la estabilidad
  delay(2);
}

void procesarCodigo() {

  int nuevocolor;

  switch (Codigo[1]) {

    //El código #H Pide los datos del sistema
    case 'H':

    break;
    
    //El código #P Enciende o apaga el led
    case 'P':
      rgbLED.SwitchPower();
    break;
    
    //El código #Rxxx Cambia el color Rojo del led
    case 'R':
      nuevocolor = (Codigo[2] - '0') * 100;
      nuevocolor += (Codigo[3] - '0') * 10;
      nuevocolor += (Codigo[4] - '0');

      rgbLED.SetRed(nuevocolor);
    break;

    //El código #Gxxx Cambia el color Verde del led
    case 'G':
      nuevocolor = (Codigo[2] - '0') * 100;
      nuevocolor += (Codigo[3] - '0') * 10;
      nuevocolor += (Codigo[4] - '0');

      rgbLED.SetGreen(nuevocolor);
    break;

    //El código #Bxxx Cambia el color Azul del led
    case 'B':
      nuevocolor = (Codigo[2] - '0') * 100;
      nuevocolor += (Codigo[3] - '0') * 10;
      nuevocolor += (Codigo[4] - '0');

      rgbLED.SetBlue(nuevocolor);
    break;

  }

  //Limpia la variable Codigo
  Codigo = "";
}
