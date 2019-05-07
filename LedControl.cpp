/*
 *    LedControl.cpp - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */


#include "LedControl.h"

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

LedControl::LedControl(int dataPin, int clkPin, int csPin) {
    SPI_MOSI=dataPin;
    SPI_CLK=clkPin;
    SPI_CS=csPin;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);
    SPI_MOSI=dataPin;
    for(int i=0;i<64;i++) 
        status[i]=0x00;
    
    spiTransfer(OP_DISPLAYTEST,0);
    //scanlimit is set to max on startup
    setScanLimit(7);
    //decode is done in source
    spiTransfer(OP_DECODEMODE,0);
    clearDisplay();
    //we go into shutdown-mode on startup
    shutdown(true);
    
}


void LedControl::shutdown(bool b) {
    if(b)
        spiTransfer(OP_SHUTDOWN,0);
    else
        spiTransfer(OP_SHUTDOWN,1);
}

void LedControl::setScanLimit(int limit) {
    if(limit>=0 && limit<8)
        spiTransfer(OP_SCANLIMIT,limit);
}

void LedControl::setIntensity(int intensity) {
    if(intensity>=0 && intensity<16)	
        spiTransfer(OP_INTENSITY,intensity);
}

void LedControl::clearDisplay() {
    for(int i=0;i<8;i++) {
        status[i]=0;
        spiTransfer(i+1,status[i]);
    }
}

void LedControl::setLed(int row, int column, boolean state) {
    byte val=0x00;

    if(row<0 || row>7 || column<0 || column>7)
        return;
    val=B10000000 >> column;
    if(state)
        status[row]=status[row]|val;
    else {
        val=~val;
        status[row]=status[row]&val;
    }
    spiTransfer(row+1,status[row]);
}

void LedControl::setRow(int row, byte value) {
    if(row<0 || row>7)
        return;
    status[row]=value;
    spiTransfer(row+1,status[row]);
}

void LedControl::setColumn(int col, byte value) {
    byte val;
    if(col<0 || col>7) 
        return;
    for(int row=0;row<8;row++) {
        val=value >> (7-row);
        val=val & 0x01;
        setLed(row,col,val);
    }
}

void LedControl::setDigit(int digit, byte value, boolean dp) {
    byte v;

    if(digit<0 || digit>7 || value>15)
        return;
    v=pgm_read_byte_near(charTable + value); 
    if(dp)
        v|=B10000000;
    status[digit]=v;
    spiTransfer(digit+1,v);
}

void LedControl::setChar(int digit, char value, boolean dp) {
    byte index,v;
    if(digit<0 || digit>7)
        return;
    index=(byte)value;
    if(index >127) {
        //no defined beyond index 127, so we use the space char
        index=32;
    }
    v=pgm_read_byte_near(charTable + index); 
    if(dp)
        v|=B10000000;
    status[digit]=v;
    spiTransfer(digit+1,v);
}

void LedControl::spiTransfer(volatile byte opcode, volatile byte data) {
    //Create an array with the data to shift out

    for(int i=0;i<2;i++)
        spidata[i]=(byte)0;
    //put our device data into the array
    spidata[1]=opcode;
    spidata[0]=data;
    //enable the line 
    digitalWrite(SPI_CS,LOW);
    //Now shift out the data 
    for(int i=2;i>0;i--)
        shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    digitalWrite(SPI_CS,HIGH);
}    


