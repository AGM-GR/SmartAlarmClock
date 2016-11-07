#ifndef BUZZERCONTROLLER
#define BUZZERCONTROLLER

class BUZZERController {

private:
  int BZPin;
  int numTonos = 10;
  int tonos[10] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
  //            midC  C#    D    D#   E    F    F#   G    G#   A
  bool ON = false;
    
public:
  BUZZERController(int bz);
  void begin();

  void beep(int tono, int tiempo);
  void tono(int tono, int tiempo);
};

#endif
