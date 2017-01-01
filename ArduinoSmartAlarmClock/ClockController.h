#ifndef CLOCKCONTROLLER
#define CLOCKCONTROLLER

#include <DS3231.h>

class ClockController {

private:
  int PowerPin = NULL;
  bool ON = false;
  DS3231 ClockModule;
  byte year, month, date, DoW, hour, minute, second;
    
public:
  ClockController(int powerPin);
  ClockController();

  void begin();

  void PowerON();
  void PowerOFF();
  void SwitchPower();
  bool isON();

  void Set24Mode();
  void Set12Mode();
  void SetDate(int Cyear, int Cmonth, int Cday, int CDoW);
  void SetDate(int Cyear, int Cmonth, int Cday);
  void SetHour(int Chour, int Cminutes, int Cseconds);
  void SetHour(int Chour, int Cminutes);
  void GetTime();
  int GetYear();
  int GetMonth();
  int GetDay();
  int GetDoW();
  int GetHour();
  int GetMins();
  int GetSecs();
  String GetStringHour();
  String GetStringDate();

  float GetTemperature();

  void ProcessCode(String code, BTController btModule);

private:

  String AdjustString(String date);
  
};

#endif
