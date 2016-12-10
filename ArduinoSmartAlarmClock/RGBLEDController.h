#ifndef RGBLEDCONTROLLER
#define RGBLEDCONTROLLER

class RGBLEDController {

  private:
    int RedPin;
    int GreenPin;
    int BluePin;
    //Establecer como HIGH para Ánodo común y LOW para Cátodo común.
    bool Common = HIGH;
    //Guarda el color del led
    int Color[3] = {0, 0, 0};
    //Guarda el estado del led
    bool ON = false;

  public:
    
    RGBLEDController(int RED, int GREEN, int BLUE, bool common);
    void begin();
    
    void PowerON();
    void PowerOFF();
    void SwitchPower();
    bool isON();
    
    int* GetColor();
    int GetRed();
    int GetGreen();
    int GetBlue();
    
    void SetRed(int rojo);
    void SetGreen(int verde);
    void SetBlue(int azul);
    void SetColor(int rojo, int verde, int azul);
    void SetColor(int nuevoColor[]);

    void ProcessCode(String code, BTController btModule);
};

#endif
