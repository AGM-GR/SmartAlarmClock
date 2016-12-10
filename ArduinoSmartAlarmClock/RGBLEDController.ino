#include "RGBLEDController.h"

//Constructor de la clase RGBLEDController
// RED = red pin.
// GREEN = green pin.
// BLUE = blue pin.
// common = HIGH if common anode, LOW if common cathode.
RGBLEDController::RGBLEDController(int RED, int GREEN, int BLUE, bool common) {

  this->RedPin = RED;
  this->GreenPin = GREEN;
  this->BluePin = BLUE;
  this->Common = common;
}

//Inicializa los pines del led segun el comun
void RGBLEDController::begin() {

  //Inicializa los pines como salidas
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  //Apaga el LED
  analogWrite(RedPin, Common*255);
  analogWrite(GreenPin, Common*255);
  analogWrite(BluePin, Common*255);
}

//Enciende el LED con el color almacenado
void RGBLEDController::PowerON() {

  if (!ON) {
    ON = true;
    SetColor(Color);
  }
}

//Apaga el LED
void RGBLEDController::PowerOFF() {

  if (ON) {
    ON = false;

    analogWrite(RedPin, Common*255);
    analogWrite(GreenPin, Common*255);
    analogWrite(BluePin, Common*255);
  }
}

//Cambia entre apagado y encendido
void RGBLEDController::SwitchPower() {

  if (ON)
    PowerOFF();
  else
    PowerON();
}

//Devuelve el estado del LED
bool RGBLEDController::isON() {
  return ON;
}

//Devuelve el color del LED
int* RGBLEDController::GetColor() {
  return Color;
}

//Devuleve el valor del color rojo
int RGBLEDController::GetRed() {
  return Color[0];
}

//Devuleve el valor del color verde
int RGBLEDController::GetGreen() {
  return Color[1];
}

//Devuleve el valor del color azul
int RGBLEDController::GetBlue() {
  return Color[2];
}

//Establece el color rojo
void RGBLEDController::SetRed(int rojo) {

  //Si está encendido cambia el color visualmente de forma suabe 
  // y lo almacena en la variable.
  if (ON) {

    //If necesario cuando enciendes el LED con un color ya definido
    if (Color[0] == rojo)
      if (Common)
        analogWrite(RedPin, 255 - Color[0]);
      else
        analogWrite(RedPin, Color[0]);

    //Transición suabe al color
    while(Color[0] != rojo) {

      if (Color[0] < rojo)
        Color[0]++;
      else
        Color[0]--;
        
      if (Common)
        analogWrite(RedPin, 255 - Color[0]);
      else
        analogWrite(RedPin, Color[0]);

      delay(1);
    }
  }
  //Si está apagado cambia el color en la variable
  else
    Color[0] = rojo;
}

//Establece el color verde
void RGBLEDController::SetGreen(int verde) {

  //Si está encendido cambia el color visualmente de forma suabe 
  // y lo almacena en la variable.
  if (ON) {

    //If necesario cuando enciendes el LED con un color ya definido
    if (Color[1] == verde)
      if (Common)
        analogWrite(GreenPin, 255 - Color[1]);
      else
        analogWrite(GreenPin, Color[1]);

    //Transición suabe al color
    while(Color[1] != verde) {

      if (Color[1] < verde)
        Color[1]++;
      else
        Color[1]--;
        
      if (Common)
        analogWrite(GreenPin, 255 - Color[1]);
      else
        analogWrite(GreenPin, Color[0]);

      delay(1);
    }
  }
  //Si está apagado cambia el color en la variable
  else
    Color[1] = verde;
}

//Establece el color azul
void RGBLEDController::SetBlue(int azul) {

  //Si está encendido cambia el color visualmente de forma suabe 
  // y lo almacena en la variable.
  if (ON) {

    //If necesario cuando enciendes el LED con un color ya definido
    if (Color[2] == azul)
      if (Common)
        analogWrite(BluePin, 255 - Color[2]);
      else
        analogWrite(BluePin, Color[2]);

    //Transición suabe al color
    while(Color[2] != azul) {

      if (Color[2] < azul)
        Color[2]++;
      else
        Color[2]--;
        
      if (Common)
        analogWrite(BluePin, 255 - Color[2]);
      else
        analogWrite(BluePin, Color[2]);

      delay(1);
    }
  }
  //Si está apagado cambia el color en la variable
  else
    Color[2] = azul;
}

//Establece el color pasado como argumento
void RGBLEDController::SetColor(int rojo, int verde, int azul) {

  SetRed(rojo);
  SetGreen(verde);
  SetBlue(azul);
}

//Establece el color pasado como un vector
void RGBLEDController::SetColor(int nuevoColor[]) {

  SetRed(nuevoColor[0]);
  SetGreen(nuevoColor[1]);
  SetBlue(nuevoColor[2]);
}

//Procesa un código recivido por el módulo bluetooth
void RGBLEDController::ProcessCode(String code, BTController btModule) {

  int nuevocolor;

  switch (Codigo[2]) {
    
    //El código #LP Enciende o apaga el led
    case 'P':
      rgbLED.SwitchPower();
    break;
    
    //El código #LRxxx Cambia el color Rojo del led
    case 'R':
      nuevocolor = (Codigo[3] - '0') * 100;
      nuevocolor += (Codigo[4] - '0') * 10;
      nuevocolor += (Codigo[5] - '0');

      rgbLED.SetRed(nuevocolor);
    break;

    //El código #LGxxx Cambia el color Verde del led
    case 'G':
      nuevocolor = (Codigo[3] - '0') * 100;
      nuevocolor += (Codigo[4] - '0') * 10;
      nuevocolor += (Codigo[5] - '0');

      rgbLED.SetGreen(nuevocolor);
    break;

    //El código #LBxxx Cambia el color Azul del led
    case 'B':
      nuevocolor = (Codigo[3] - '0') * 100;
      nuevocolor += (Codigo[4] - '0') * 10;
      nuevocolor += (Codigo[5] - '0');

      rgbLED.SetBlue(nuevocolor);
    break;

    //El código #LD Obtiene los datos del led
    case 'D':

      // 1º Información de encendido o apagado
      if (isON())
        btModule.write("#1$");
      else
        btModule.write("#0$");

      // 2º Información Color R
      btModule.write("#"+String(Color[0])+"$");
      
      // 3º Información Color G
      btModule.write("#"+String(Color[1])+"$");
      
      // 4º Información Color B
      btModule.write("#"+String(Color[2])+"$");
    break;
  }
  
}

