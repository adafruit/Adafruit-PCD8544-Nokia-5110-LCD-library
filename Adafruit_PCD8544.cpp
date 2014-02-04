/*********************************************************************
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
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

#include "Adafruit_PCD8544.h"
#include <limits.h>
#include "pins_arduino.h"
#include "wiring_private.h"
#include <SPI.h>
// #include <util/delay.h>
// #include <stdlib.h>

// the memory buffer for the LCD
uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFC, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x87, 0x8F, 0x9F, 0x9F, 0xFF, 0xFF, 0xFF,
0xC1, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE,
0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0xC0, 0xE0, 0xF1, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x0F, 0x87,
0xE7, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0x3F, 0xF9, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFD, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x7E, 0x3F, 0x3F, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFC, 0xF0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x7F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


// reduces how much is refreshed, which speeds it up!
// originally derived from Steve Evans/JCW's mod but cleaned up and optimized
#define enablePartialUpdate

#ifdef enablePartialUpdate
static uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
#endif

static void updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax) {
#ifdef enablePartialUpdate
  if (xmin < xUpdateMin) xUpdateMin = xmin;
  if (xmax > xUpdateMax) xUpdateMax = xmax;
  if (ymin < yUpdateMin) yUpdateMin = ymin;
  if (ymax > yUpdateMax) yUpdateMax = ymax;
#endif
}


// Constructor when using software SPI.  All output pins are configurable.
Adafruit_PCD8544::Adafruit_PCD8544(uint8_t cs, uint8_t rs, uint8_t sid,
 uint8_t sclk, uint8_t rst) : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  _cs   = cs;
  _rs   = rs;
  _sid  = sid;
  _sclk = sclk;
  _rst  = rst;
  hwSPI = false;
}


// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
Adafruit_PCD8544::Adafruit_PCD8544(uint8_t cs, uint8_t rs, uint8_t rst) :
    Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  _cs   = cs;
  _rs   = rs;
  _rst  = rst;
  hwSPI = true;
  _sid  = _sclk = 0;
}


#ifdef __AVR__
inline void Adafruit_PCD8544::spiwrite(uint8_t c) {
  //Serial.println(c, HEX);
  if (hwSPI) {
    SPDR = c;
    while(!(SPSR & _BV(SPIF)));
  } else {
    // Fast SPI bitbang swiped from LPD8806 library
    for(uint8_t bit = 0x80; bit; bit >>= 1) {
      if(c & bit) *dataport |=  datapinmask;
      else        *dataport &= ~datapinmask;
      *clkport |=  clkpinmask;
      *clkport &= ~clkpinmask;
    }
    // Slow SPI bitbang shiftOut(_din, _sclk, MSBFIRST, c);
  }
}


void Adafruit_PCD8544::writecommand(uint8_t c) {
  *rsport &= ~rspinmask;
  *csport &= ~cspinmask;

  //Serial.print("C ");
  spiwrite(c);

  *csport |= cspinmask;
}


void Adafruit_PCD8544::writedata(uint8_t c) {
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;

  //Serial.print("D ");
  spiwrite(c);

  *csport |= cspinmask;
}
#endif //#ifdef __AVR__


#if defined(__SAM3X8E__)
inline void Adafruit_PCD8544::spiwrite(uint8_t c) {
  //Serial.println(c, HEX);
  if (hwSPI) {
    SPI.transfer(c);
  } else {
    // Fast SPI bitbang swiped from LPD8806 library
    for(uint8_t bit = 0x80; bit; bit >>= 1) {
      if(c & bit) dataport->PIO_SODR |= datapinmask;
      else        dataport->PIO_CODR |= datapinmask;
      clkport->PIO_SODR |= clkpinmask;
      clkport->PIO_CODR |= clkpinmask;
    }
  }
}


void Adafruit_PCD8544::writecommand(uint8_t c) {
  rsport->PIO_CODR |= rspinmask;
  csport->PIO_CODR |= cspinmask;

  //Serial.print("C ");
  spiwrite(c);

  csport->PIO_SODR |= cspinmask;
}


void Adafruit_PCD8544::writedata(uint8_t c) {
  rsport->PIO_SODR |= rspinmask;
  csport->PIO_CODR |= cspinmask;

  //Serial.print("D ");
  spiwrite(c);

  csport->PIO_SODR |= cspinmask;
}
#endif //#if defined(__SAM3X8E__)


void Adafruit_PCD8544::begin(uint8_t contrast) {
  pinMode(_rs, OUTPUT);
  pinMode(_cs, OUTPUT);
#ifdef __AVR__
  csport    = portOutputRegister(digitalPinToPort(_cs));
  rsport    = portOutputRegister(digitalPinToPort(_rs));
#endif
#if defined(__SAM3X8E__)
  csport    = digitalPinToPort(_cs);
  rsport    = digitalPinToPort(_rs);
#endif
  cspinmask = digitalPinToBitMask(_cs);
  rspinmask = digitalPinToBitMask(_rs);

  if(hwSPI) { // Using hardware SPI
    SPI.begin();
#ifdef __AVR__
    SPI.setClockDivider(SPI_CLOCK_DIV4); // 4 MHz (half speed)
    //Due defaults to 4mHz (clock divider setting of 21)
#endif
#if defined(__SAM3X8E__)
    SPI.setClockDivider(21); // 4 MHz
    //Due defaults to 4mHz (clock divider setting of 21), but we'll set it anyway
#endif
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
  } else {
    pinMode(_sclk, OUTPUT);
    pinMode(_sid , OUTPUT);
#ifdef __AVR__
    clkport     = portOutputRegister(digitalPinToPort(_sclk));
    dataport    = portOutputRegister(digitalPinToPort(_sid));
#endif
#if defined(__SAM3X8E__)
    clkport     = digitalPinToPort(_sclk);
    dataport    = digitalPinToPort(_sid);
#endif
    clkpinmask  = digitalPinToBitMask(_sclk);
    datapinmask = digitalPinToBitMask(_sid);
#ifdef __AVR__
    *clkport   &= ~clkpinmask;
    *dataport  &= ~datapinmask;
#endif
#if defined(__SAM3X8E__)
    clkport ->PIO_CODR |= clkpinmask; // Set control bits to LOW (idle)
    dataport->PIO_CODR |= datapinmask; // Signals are ACTIVE HIGH
#endif
  }

  // toggle RST low to reset; CS low so it'll listen to us
#ifdef __AVR__
  *csport &= ~cspinmask;
#endif
#if defined(__SAM3X8E__)
  csport ->PIO_CODR |= cspinmask; // Set control bits to LOW (idle)
#endif
  if (_rst) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(500);
    digitalWrite(_rst, LOW);
    delay(500);
    digitalWrite(_rst, HIGH);
    delay(500);
  }
  // END common SPI code

  // get into the EXTENDED mode!
  writecommand(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION );

  // LCD bias select (4 is optimal?)
  writecommand(PCD8544_SETBIAS | 0x4);

  // set VOP
  if (contrast > 0x7f)
    contrast = 0x7f;
  writecommand(PCD8544_SETVOP | contrast); // Experimentally determined

  // normal mode
  writecommand(PCD8544_FUNCTIONSET);

  // Set display to Normal
  writecommand(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);

  // initial display line
  // set page address
  // set column address
  // write display data

  // set up a bounding box for screen updates
  updateBoundingBox(0, 0, LCDWIDTH-1, LCDHEIGHT-1);
  
  // Push out pcd8544_buffer to the Display (will show the AFI logo)
  display();
}


// the most basic function, set a single pixel
void Adafruit_PCD8544::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT))
    return;

  // x is which column
  if (color)
    pcd8544_buffer[x+ (y/8)*LCDWIDTH] |= _BV(y%8);
  else
    pcd8544_buffer[x+ (y/8)*LCDWIDTH] &= ~_BV(y%8);

  updateBoundingBox(x,y,x,y);
}


// the most basic function, get a single pixel
uint8_t Adafruit_PCD8544::getPixel(int8_t x, int8_t y) {
  if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT))
    return 0;

  return (pcd8544_buffer[x+ (y/8)*LCDWIDTH] >> (y%8)) & 0x1;
}


void Adafruit_PCD8544::setContrast(uint8_t val) {
  if (val > 0x7f) {
    val = 0x7f;
  }
  writecommand(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION );
  writecommand(PCD8544_SETVOP | val);
  writecommand(PCD8544_FUNCTIONSET);
}


void Adafruit_PCD8544::display(void) {
  uint8_t col, maxcol, p;

  for(p = 0; p < 6; p++) {
#ifdef enablePartialUpdate
    // check if this page is part of update
    if ( yUpdateMin >= ((p+1)*8) ) {
      continue;   // nope, skip it!
    }
    if (yUpdateMax < p*8) {
      break;
    }
#endif

    writecommand(PCD8544_SETYADDR | p);

#ifdef enablePartialUpdate
    col = xUpdateMin;
    maxcol = xUpdateMax;
#else
    // start at the beginning of the row
    col = 0;
    maxcol = LCDWIDTH-1;
#endif

    writecommand(PCD8544_SETXADDR | col);

    // digitalWrite(_dc, HIGH);
    // if (_cs > 0) digitalWrite(_cs, LOW);
#ifdef __AVR__
	  *rsport |=  rspinmask;
	  *csport &= ~cspinmask;
#endif //#ifdef __AVR__
#if defined(__SAM3X8E__)
	  rsport->PIO_SODR |= rspinmask;
	  csport->PIO_CODR |= cspinmask;
#endif //#if defined(__SAM3X8E__)

    for(; col <= maxcol; col++) {
      spiwrite(pcd8544_buffer[(LCDWIDTH*p)+col]);
    }

    // if (_cs > 0) digitalWrite(_cs, HIGH);
#ifdef __AVR__
	  *csport |= cspinmask;
#endif //#ifdef __AVR__
#if defined(__SAM3X8E__)
	  csport->PIO_SODR |= cspinmask;
#endif //#if defined(__SAM3X8E__)
  }

  writecommand(PCD8544_SETYADDR );  // no idea why this is necessary but it is to finish the last byte?
#ifdef enablePartialUpdate
  xUpdateMin = LCDWIDTH - 1;
  xUpdateMax = 0;
  yUpdateMin = LCDHEIGHT-1;
  yUpdateMax = 0;
#endif

}

// clear everything
void Adafruit_PCD8544::clearDisplay(void) {
  memset(pcd8544_buffer, 0, LCDWIDTH*LCDHEIGHT/8);
  updateBoundingBox(0, 0, LCDWIDTH-1, LCDHEIGHT-1);
  cursor_y = cursor_x = 0;
}

/*
// this doesn't touch the buffer, just clears the display RAM - might be handy
void Adafruit_PCD8544::clearDisplay(void) {
  uint8_t p, c;

  for(p = 0; p < 8; p++) {
    st7565_command(CMD_SET_PAGE | p);
    for(c = 0; c < 129; c++) {
      //uart_putw_dec(c);
      //uart_putchar(' ');
      st7565_command(CMD_SET_COLUMN_LOWER | (c & 0xf));
      st7565_command(CMD_SET_COLUMN_UPPER | ((c >> 4) & 0xf));
      st7565_data(0x0);
    }
  }
}
*/
