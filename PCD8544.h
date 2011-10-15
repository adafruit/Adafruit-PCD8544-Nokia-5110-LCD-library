#ifndef PCD8544_H // Albert
#define PCD8544_H // Albert

/*
$Id:$

PCD8544 LCD library!

Copyright (C) 2010 Limor Fried, Adafruit Industries

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 84
#define LCDHEIGHT 48

#define PCD8544_POWERDOWN 0x04
#define PCD8544_ENTRYMODE 0x02
#define PCD8544_EXTENDEDINSTRUCTION 0x01

#define PCD8544_DISPLAYBLANK 0x0
#define PCD8544_DISPLAYNORMAL 0x4
#define PCD8544_DISPLAYALLON 0x1
#define PCD8544_DISPLAYINVERTED 0x5

// H = 0
#define PCD8544_FUNCTIONSET 0x20
#define PCD8544_DISPLAYCONTROL 0x08
#define PCD8544_SETYADDR 0x40
#define PCD8544_SETXADDR 0x80

// H = 1
#define PCD8544_SETTEMP 0x04
#define PCD8544_SETBIAS 0x10
#define PCD8544_SETVOP 0x80

#define swap(a, b) { byte t = a; a = b; b = t; }

class PCD8544 : public Print {
 public:
  PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS=0, int8_t RST=0); // Albert use default parameters

  void init(byte contrast=50); // Albert use default parameters
  //void init(void); // Albert use default parameters 
  
  void command(byte c);
  void data(byte c);
  
  void setContrast(byte val);
  void clearDisplay(void);
  void clear();
  void display();
  void displayBuffer();
  
  void setPixel(byte x, byte y, byte color);
  byte getPixel(byte x, byte y);
  void fillcircle(byte x0, byte y0, byte r, 
		  byte color);
  void drawcircle(byte x0, byte y0, byte r, 
		  byte color);
  void drawrect(byte x, byte y, byte w, byte h, 
		byte color);
  void fillrect(byte x, byte y, byte w, byte h, 
		byte color);
  void drawline(byte x0, byte y0, byte x1, byte y1, 
		byte color);
  
  void setCursor(byte x, byte y);
  void setTextSize(byte s);
  void setTextColor(byte c);
  #if defined(ARDUINO) && ARDUINO >= 100
    size_t write(byte c);
  #else
    void write(byte c);
  #endif

  void drawchar(byte x, byte line, char c);
  void drawstring(byte x, byte line, char *c);
  void drawstring_P(byte x, byte line, const char *c);
  void drawbitmap(byte x, byte y, 
		  const byte *bitmap, byte w, byte h,
		  byte color);

 private:
  byte cursor_x, cursor_y, textsize, textcolor;
  int8_t _din, _sclk, _dc, _rst, _cs;
  void spiwrite(byte c);

  void my_setpixel(byte x, byte y, byte color);
};

#endif // Albert
