#ifndef LedControl_h
#define LedControl_h

#include <avr/pgmspace.h>
#include <Arduino.h>

class LedControl {
    private :
        /* Send out a single command to the device */
        void spiTransfer(byte opcode, byte data);
        byte spidata[2];
        byte status[8];
        
        /* Data is shifted out of this pin*/
        int SPI_MOSI;
        /* The clock is signaled on this pin */
        int SPI_CLK;
        /* This one is driven LOW for chip selectzion */
        int SPI_CS;

    public:
        LedControl(int dataPin, int clkPin, int csPin);
        void shutdown(bool status);
        void setScanLimit(int limit);
        void setIntensity(int intensity);
        void clearDisplay();
        void setLed(int row, int col, boolean state);
};

#endif



