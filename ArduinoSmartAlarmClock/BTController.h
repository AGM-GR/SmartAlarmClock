#ifndef BTCONTROLLER
#define BTCONTROLLER

#include <SoftwareSerial.h>

class BTController {

private:
  int Rx;
  int Tx;
  int KEY;
  int POWER;
  int Baudios;
  bool ON = false;
  //Predefino el bluetooth en los pines 10 y 11 por la falta de un constructor vacío en la clase SoftwareSerial
  // en el contructor de esta clase se le asigna los pines correspondientes.
  SoftwareSerial BTmodule = SoftwareSerial(10,11);
    
public:
  BTController(int RX, int TX, int key, int power, int baudios);
  BTController(int RX, int TX, int power, int baudios);
  BTController(int RX, int TX, int baudios);
  BTController(int RX, int TX);
  void begin();
  
  void PowerON();
  void PowerOFF();
  void SwitchPower();
  bool isON();
  
  bool readChar(char &command);
  int sendBT(char command);
  int sendBT(char* command); 
  int sendBT(String command);  
};

#endif
