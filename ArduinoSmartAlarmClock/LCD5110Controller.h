#ifndef LCD5110CONTROLLER
#define LCD5110CONTROLLER

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544_MOD.h"

class LCD5110Controller {

private:
  int CLK;
  int DIN;
  int DC;
  int CS;
  int RST;
  int BL;
  int Contraste = 50;
  int Brightness = 0;
  bool ON = false;
  Adafruit_PCD8544 LCDdisplay;
    
public:
  LCD5110Controller(int clk, int din, int dc, int cs, int rst, int bl);
  void begin();
  
  void PowerON();
  void PowerOFF();
  void SwitchPower();
  bool isON();

  int GetBrightness();
  void SetBrightness(int brightness);

  void DrawHour(String hour);
  void DrawDate(String date);
  void DrawBluetooth();
  
};

#endif
