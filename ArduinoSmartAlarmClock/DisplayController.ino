#include "DisplayController.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544_MOD.h"
#include "Images.h"

DisplayController::DisplayController(int clk, int din, int dc, int cs, int rst, int bl) {
  this->CLK = clk;
  this->DIN = din;
  this->DC = dc;
  this->CS = cs;
  this->RST = rst;
  this->BL = bl;

  this->LCDdisplay = Adafruit_PCD8544(CLK, DIN, DC, CS, RST);
}

//Inicializa el LCD
void DisplayController::begin() {

  //Pin para el brillo
  pinMode(BL, OUTPUT);

  //Inicializa el display
  LCDdisplay.begin();

  //Ajuste Contraste
  LCDdisplay.setContrast(Contraste);

  //Muestra el logo
  LCDdisplay.display();
  
  //Limpia el display y el buffer
  LCDdisplay.clearDisplay();
}

//Enciende la luz del LCD
void DisplayController::PowerON() {
  
  if (!ON) {
    ON = true;
    SetBrightness(Brightness);
  }
}

//Apaga la luz del LCD
void DisplayController::PowerOFF() {

  if (ON) {
    ON = false;
    analogWrite(BL, 0);
  }
}

//Cambia entre apagado y encendido
void DisplayController::SwitchPower() {

  if (ON)
    PowerOFF();
  else
    PowerON();
}

//Devuelve el estado de la luz del LCD
bool DisplayController::isON() {

  return ON;
}

//Devuelve la intensidad de la luz del LCD
int DisplayController::GetBrightness() {

  return Brightness;
}

//Establece la intensidad de la luz del LCD
void DisplayController::SetBrightness(int brightness) {
  
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


//Dibuja la hora
void DisplayController::DrawHour(String hour) {

  LCDdisplay.setTextSize(2);
  LCDdisplay.setTextColor(BLACK);
  LCDdisplay.setCursor(15,16);
  
  LCDdisplay.write(hour[0]);
  LCDdisplay.write(hour[1]);
  LCDdisplay.write(':');
  LCDdisplay.write(hour[2]);
  LCDdisplay.write(hour[3]);
  
  LCDdisplay.display();
}

//Dibuja la fecha
void DisplayController::DrawDate(String date) {

  LCDdisplay.setTextSize(1);
  LCDdisplay.setTextColor(BLACK);
  LCDdisplay.setCursor(18,34);
  
  LCDdisplay.write(date[0]);
  LCDdisplay.write(date[1]);
  LCDdisplay.write('/');
  LCDdisplay.write(date[2]);
  LCDdisplay.write(date[3]);
  LCDdisplay.write('/');
  LCDdisplay.write(date[4]);
  LCDdisplay.write(date[5]);
  
  LCDdisplay.display();
}

//Dibuja el icono de bluetooth
void DisplayController::DrawBluetooth() {
  
  LCDdisplay.drawBitmap(75, 0, bluetooth, 9, 15, 1);
  
  LCDdisplay.display();
}

//Limpia la pantalla
void DisplayController::ClearDisplay() {

    LCDdisplay.clearDisplay();
}

//Procesa un código recivido por el módulo bluetooth
void DisplayController::ProcessCode(String code, BTController btModule) {

  switch (code[2]) {
    
    //El código #DP Enciende o apaga el display
    case 'P':
      SwitchPower();
    break;

    //El código #DD Obtiene los datos del led
    case 'D':

      // 1º Información de encendido o apagado
      if (isON())
        btModule.write("#1$");
      else
        btModule.write("#0$");

    break;
  }
  
}
