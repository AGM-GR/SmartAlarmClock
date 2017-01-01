#include "ClockController.h"
#include <DS3231.h>
#include <Wire.h>

ClockController::ClockController(int powerPin) {
  
  this->PowerPin = powerPin;  
}

ClockController::ClockController() {}

void ClockController::begin() {

  if (PowerPin != NULL)
  
    pinMode(PowerPin, OUTPUT);

  PowerON();

  //Inicializa la interfáz I2C
  Wire.begin();
}

void ClockController::PowerON() {
  
  if (PowerPin != NULL)

    digitalWrite(PowerPin, HIGH);

  ON = true;
}

void ClockController::PowerOFF() {

  if (PowerPin != NULL)

    digitalWrite(PowerPin, LOW);

  ON = false;
}

void ClockController::SwitchPower() {

  if (ON)
    PowerOFF();
  else
    PowerON();
}

bool ClockController::isON() {

  return ON;
}

void ClockController::Set24Mode() {

  //Se establece el modo horario en 24 horas
  ClockModule.setClockMode(false); 
}

void ClockController::Set12Mode() {

  //Se establece el modo horario en 12 horas
  ClockModule.setClockMode(true); 
}

void ClockController::SetDate(int Cyear, int Cmonth, int Cday, int CDoW) {

  //Año
  ClockModule.setYear((byte)Cyear);
  //Mes
  ClockModule.setMonth((byte)Cmonth);
  //Dia de la semana
  ClockModule.setDoW((byte)CDoW);
  //Día
  ClockModule.setDate((byte)Cday);
}

void ClockController::SetDate(int Cyear, int Cmonth, int Cday) {

  //Año
  ClockModule.setYear((byte)Cyear);
  //Mes
  ClockModule.setMonth((byte)Cmonth);
  //Día
  ClockModule.setDate((byte)Cday);
}

void ClockController::SetHour(int Chour, int Cminutes, int Cseconds) {

  //Hora
  ClockModule.setHour((byte)Chour);
  //Minutos
  ClockModule.setMinute((byte)Cminutes);
  //Segundos
  ClockModule.setSecond((byte)Cseconds); 
}

void ClockController::SetHour(int Chour, int Cminutes) {

  //Hora
  ClockModule.setHour((byte)Chour);
  //Minutos
  ClockModule.setMinute((byte)Cminutes);
}

void ClockController::GetTime() {

  ClockModule.getTime(year, month, date, DoW, hour, minute, second);
  
  bool mode = false;
  bool pm = false;
  hour = ClockModule.getHour(mode, pm);
}

int ClockController::GetYear() {

  return ((int) year);
}
  
int ClockController::GetMonth() {

  return ((int) month);
}

int ClockController::GetDay() {

  return ((int) date);
}

int ClockController::GetDoW() {

  return ((int) DoW);
}

int ClockController::GetHour() {

  return ((int) hour);
}

int ClockController::GetMins() {

  return ((int) minute);
}

int ClockController::GetSecs() {

  return ((int) second);
}

String ClockController::GetStringHour() {

  String Chour = "";

  Chour = AdjustString((String) hour);
  Chour += AdjustString((String) minute);

  return Chour;
}

String ClockController::GetStringDate() {

  String Cdate = "";

  Cdate = AdjustString((String) date);
  Cdate += AdjustString((String) month);
  Cdate += AdjustString((String) year);

  return Cdate;
}

float ClockController::GetTemperature() {

  return ClockModule.getTemperature();
}

void ClockController::ProcessCode(String code, BTController btModule) {

  int Chour, Cminute, Cday, Cmonth, Cyear;
    
  switch (code[2]) {

    //El código #CH Establece la hora
    case 'H':

      Chour = (code[3] - '0') * 10;
      Chour += (code[4] - '0');
      Cminute = (code[5] - '0') * 10;
      Cminute += (code[6] - '0');

      SetHour(Chour, Cminute);
      
    break;

    //El código #CD Establece la fecha
    case 'D':

      Cday = (code[3] - '0') * 10;
      Cday += (code[4] - '0');
      Cmonth = (code[5] - '0') * 10;
      Cmonth += (code[6] - '0');
      Cyear = (code[7] - '0') * 10;
      Cyear += (code[8] - '0');

      SetDate(Cyear, Cmonth, Cday);
      
    break;

    //El código #CG Obtiene los datos del reloj
    case 'G':

      // Envia un string con todos los datos
      GetTime();

      String Cdate = "";
      Cdate = AdjustString((String) hour);
      Cdate += AdjustString((String) minute);
      Cdate += AdjustString((String) second);
      Cdate += AdjustString((String) date);
      Cdate += AdjustString((String) DoW);
      Cdate += AdjustString((String) month);
      Cdate += AdjustString((String) year);

      btModule.write("#"+Cdate+"$");
      
    break;
  }
}

String ClockController::AdjustString(String date) {

    String fitDate = date;

    while (fitDate.length() < 2)
      fitDate = "0" + fitDate;

    return fitDate;
}
