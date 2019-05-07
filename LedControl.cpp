#include "LedControl.h"

//the opcodes for the MAX7221 and MAX7219
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

LedControl::LedControl(int dataPin, int clkPin, int csPin) {
    
    // setup pins
    SPI_MOSI=dataPin;
    SPI_CLK=clkPin;
    SPI_CS=csPin;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    
    // send HIGH to device
    digitalWrite(SPI_CS,HIGH);
    SPI_MOSI=dataPin;
    
    // initialisize status array
    for(int i=0;i<8;i++) 
        status[i]=0x00;
    
    // test on start all LEDs
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
    
    // shift the 1 to the postion of column
    val=B10000000 >> column;
    
    // if the led is to be turned on
    if(state)
        // then combine the previous status with the on-state led
        status[row]=status[row]|val;
    
    // but if the led is to be turned off
    else {
        
        // B1000000 will be turned to B0111111
        val=~val;
        // then combine the previous status with the off-state led
        status[row]=status[row]&val;
    }
    
    // operation code 1-8 for the led rows -> pass status byte
    spiTransfer(row+1,status[row]);
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
