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

#include <WProgram.h>

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

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

class PCD8544 {
 public:
  PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST) : _din(DIN), _sclk(SCLK), _dc(DC), _rst(RST), _cs(CS) {}
  PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t RST) : _din(DIN), _sclk(SCLK), _dc(DC), _rst(RST), _cs(-1) {}

  void init(void);
  void begin(uint8_t contrast);
  
  void command(uint8_t c);
  void data(uint8_t c);
  
  void setContrast(uint8_t val);
  void setTempControl(uint8_t val);
  void clearDisplay(void);
  void clear();
  void display();
  
  void setPixel(uint8_t x, uint8_t y, uint8_t color);
  uint8_t getPixel(uint8_t x, uint8_t y);
  void fillcircle(uint8_t x0, uint8_t y0, uint8_t r, 
		  uint8_t color);
  void drawcircle(uint8_t x0, uint8_t y0, uint8_t r, 
		  uint8_t color);
  void drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		uint8_t color);
  void fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		uint8_t color);
  void drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, 
		uint8_t color);
  
  void drawchar(uint8_t x, uint8_t line, char c);
  void drawstring(uint8_t x, uint8_t line, char *c);
  void drawstring_P(uint8_t x, uint8_t line, const char *c);
  void drawbitmap(uint8_t x, uint8_t y, 
		  const uint8_t *bitmap, uint8_t w, uint8_t h,
		  uint8_t color);
 private:
  int8_t _din, _sclk, _dc, _rst, _cs;
  void spiwrite(uint8_t c);

  void my_setpixel(uint8_t x, uint8_t y, uint8_t color);
};
