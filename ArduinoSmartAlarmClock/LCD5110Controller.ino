#include "LCD5110Controller.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544_MOD.h"

LCD5110Controller::LCD5110Controller(int clk, int din, int dc, int cs, int rst, int bl) {
  this->CLK = clk;
  this->DIN = din;
  this->DC = dc;
  this->CS = cs;
  this->RST = rst;
  this->BL = bl;

  this->LCDdisplay = Adafruit_PCD8544(CLK, DIN, DC, CS, RST);
}

//Inicializa el LCD
void LCD5110Controller::begin() {

  //Pin para el brillo
  pinMode(BL, OUTPUT);

  //Inicializa el display
  LCDdisplay.begin();

  //Ajuste Contraste
  LCDdisplay.setContrast(Contraste);

  LCDdisplay.display(); // show splashscreen
  delay(2000);
  LCDdisplay.clearDisplay();   // clears the screen and buffer
}

//Enciende la luz del LCD
void LCD5110Controller::PowerON() {
  
  if (!ON) {
    ON = true;
    SetBrightness(Brightness);
  }
}

//Apaga la luz del LCD
void LCD5110Controller::PowerOFF() {

  if (ON) {
    ON = false;
    analogWrite(BL, 0);
  }
}

//Cambia entre apagado y encendido
void LCD5110Controller::SwitchPower() {

  if (ON)
    PowerOFF();
  else
    PowerON();
}

//Devuelve el estado de la luz del LCD
bool LCD5110Controller::isON() {

  return ON;
}

//Devuelve la intensidad de la luz del LCD
int LCD5110Controller::GetBrightness() {

  return Brightness;
}

//Establece la intensidad de la luz del LCD
void LCD5110Controller::SetBrightness(int brightness) {
  
  //Si está encendido cambia el brillo visualmente de forma suabe 
  // y lo almacena en la variable.
  if (ON) {

    //If necesario cuando enciendes la pantalla
    if (Brightness == brightness)
      analogWrite(BL, Brightness);

    //Transición suabe al color
    while(Brightness != brightness) {

      if (Brightness < brightness)
        Brightness++;
      else
        Brightness--;
        
      analogWrite(BL, Brightness);

      delay(8);
    }
  }
  //Si está apagado cambia el color en la variable
  else
    Brightness = brightness;
}


