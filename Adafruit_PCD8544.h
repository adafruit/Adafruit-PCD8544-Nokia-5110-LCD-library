/**************************************************************************/
/*!
  @file Adafruit_PCD8544.h

  This is a library for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

  These displays use SPI to communicate, 4 or 5 pins are required to
  interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*/
/**************************************************************************/
#ifndef _ADAFRUIT_PCD8544_H
#define _ADAFRUIT_PCD8544_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

#include <Adafruit_GFX.h>
#include <SPI.h>

#if defined(__SAM3X8E__) || defined(ARDUINO_ARCH_SAMD)
typedef volatile RwReg PortReg; ///< PortReg for SAMD
typedef uint32_t PortMask;      ///< PortMask for SAMD
#elif defined(__AVR__)
typedef volatile uint8_t PortReg; ///< PortReg for AVR
typedef uint8_t PortMask;         ///< PortMask for AVR
#else
typedef volatile uint32_t PortReg; ///< PortReg for other chips
typedef uint32_t PortMask;         ///< PortMask for other chips
#endif

#define BLACK 1 ///< Black pixel
#define WHITE 0 ///< White pixel

#define LCDWIDTH 84  ///< LCD is 84 pixels wide
#define LCDHEIGHT 48 ///< 48 pixels high

#define PCD8544_POWERDOWN 0x04 ///< Function set, Power down mode
#define PCD8544_ENTRYMODE 0x02 ///< Function set, Entry mode
#define PCD8544_EXTENDEDINSTRUCTION                                            \
  0x01 ///< Function set, Extended instruction set control

#define PCD8544_DISPLAYBLANK 0x0    ///< Display control, blank
#define PCD8544_DISPLAYNORMAL 0x4   ///< Display control, normal mode
#define PCD8544_DISPLAYALLON 0x1    ///< Display control, all segments on
#define PCD8544_DISPLAYINVERTED 0x5 ///< Display control, inverse mode

#define PCD8544_FUNCTIONSET 0x20 ///< Basic instruction set
#define PCD8544_DISPLAYCONTROL                                                 \
  0x08 ///< Basic instruction set - Set display configuration
#define PCD8544_SETYADDR                                                       \
  0x40 ///< Basic instruction set - Set Y address of RAM, 0 <= Y <= 5
#define PCD8544_SETXADDR                                                       \
  0x80 ///< Basic instruction set - Set X address of RAM, 0 <= X <= 83

#define PCD8544_SETTEMP                                                        \
  0x04 ///< Extended instruction set - Set temperature coefficient
#define PCD8544_SETBIAS 0x10 ///< Extended instruction set - Set bias system
#define PCD8544_SETVOP                                                         \
  0x80 ///< Extended instruction set - Write Vop to register

#define PCD8544_SPI_CLOCK_DIV                                                  \
  SPI_CLOCK_DIV4 ///< Default to max SPI clock speed for PCD8544 of 4 mhz (16mhz
                 ///< / 4) for normal Arduinos. This can be modified to change
                 ///< the clock speed if necessary (like for supporting other
                 ///< hardware).

/**************************************************************************/
/*!
    @brief The PCD8544 LCD class
 */
class Adafruit_PCD8544 : public Adafruit_GFX {
public:
  Adafruit_PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST);
  Adafruit_PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t RST);
  Adafruit_PCD8544(int8_t DC, int8_t CS, int8_t RST);

  void begin(uint8_t contrast = 40, uint8_t bias = 0x04);

  void command(uint8_t c);
  void data(uint8_t c);

  void setContrast(uint8_t val);
  void setBias(uint8_t val);
  uint8_t getContrast(void);
  uint8_t getBias(void);
  void clearDisplay(void);
  void display();
  void setReinitInterval(uint8_t val);
  uint8_t getReinitInterval(void);

  void drawPixel(int16_t x, int16_t y, uint16_t color);
  uint8_t getPixel(int8_t x, int8_t y);

  void initDisplay();

private:
  int8_t _din;              ///< DIN pin
  int8_t _sclk;             ///< SCLK pin
  int8_t _dc;               ///< DC pin
  int8_t _rst;              ///< RST pin
  int8_t _cs;               ///< CS pin
  uint8_t _contrast;        ///< Contrast level, Vop
  uint8_t _bias;            ///< Bias value
  uint8_t _reinit_interval; ///< Reinitialize the display after this many calls
                            ///< to display()
  uint8_t _display_count;   ///< Count for reinit interval
  volatile PortReg *mosiport; ///< MOSI port
  volatile PortReg *clkport;  ///< CLK port
  PortMask mosipinmask;       ///< MOSI port mask
  PortMask clkpinmask;        ///< CLK port mask

  void spiWrite(uint8_t c);
  bool isHardwareSPI();
};

#endif
