#ifndef NokiaFa5110_h
#define NokiaFa5110_h

#include "Arduino.h"

class NokiaFa5110{
public:
  NokiaFa5110(byte SCLK, byte DIN, byte DC, byte CS, byte RST, byte LIGHT);
  void LcdClear(void);
  void WriteString(String s, int x, int y);
  void Light(bool state);
  void LightNot(void);
  void PrintPicPos(prog_uchar pic[], int picsize, int x, int y, byte div);
  void PrintPic(prog_uchar pic[], int picsize);

private:
  byte _din, _sclk, _dc, _rst, _cs, _light;
  bool _state;
  void Print(char ch, int x, int y);
  void LcdWrite(byte dc, byte data);
  void LcdInitialise(void);    
};

#endif

