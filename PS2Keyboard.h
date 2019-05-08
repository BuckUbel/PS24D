/*
  PS2Keyboard.h - PS2Keyboard library
  Copyright (c) 2007 Free Software Foundation.  All right reserved.
  Written by Christian Weichel <info@32leaves.net>
  
  ** Mostly rewritten Paul Stoffregen <paul@pjrc.com>, June 2010
  ** Modified for use with Arduino 13 by L. Abraham Smith, <n3bah@microcompdesign.com> * 
  ** Modified for easy interrup pin assignement on method begin(datapin,irq_pin). Cuningan <cuninganreset@gmail.com> **
  
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
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PS2Keyboard_h
#define PS2Keyboard_h
#include "Arduino.h" // for attachInterrupt, FALLING
  
// Every call to read() returns a single byte for each
// keystroke.  These configure what byte will be returned
// for each "special" key.  To ignore a key, use zero.

#define PS2_TAB                       9
#define PS2_ENTER                     13
#define PS2_BACKSPACE                 127
#define PS2_ESC                       27
#define PS2_INSERT                    0
#define PS2_DELETE                    127
#define PS2_HOME                      0
#define PS2_END                       0
#define PS2_PAGEUP                    25
#define PS2_PAGEDOWN                  26
#define PS2_UPARROW                   11
#define PS2_LEFTARROW                 8
#define PS2_DOWNARROW                 10
#define PS2_RIGHTARROW                21
#define PS2_F1                        5
#define PS2_F2                        6
#define PS2_F3                        4
#define PS2_F4                        12
#define PS2_F5                        3
#define PS2_F6                        11
#define PS2_F7                        83//
#define PS2_F8                        10
#define PS2_F9                        1
#define PS2_F10                       9
#define PS2_F11                       120
#define PS2_F12                       7
#define PS2_SCROLL                    126

#define PS2_CURRENCY_SIGN             164 // ¤
#define PS2_SECTION_SIGN              167 // §
#define PS2_DEGREE_SIGN               176 // °
#define PS2_SUPERSCRIPT_TWO           178 // ²
#define PS2_SUPERSCRIPT_THREE         179 // ³
#define PS2_MICRO_SIGN                181 // µ
#define PS2_A_DIAERESIS               196 // Ä
#define PS2_O_DIAERESIS               214 // Ö
#define PS2_U_DIAERESIS               220 // Ü
#define PS2_SHARP_S                   223 // ß
#define PS2_a_DIAERESIS               228 // ä
#define PS2_o_DIAERESIS               246 // ö
#define PS2_u_DIAERESIS               252 // ü

#define PS2_KEYMAP_SIZE 136

typedef struct {
  uint8_t noshift[PS2_KEYMAP_SIZE];
  uint8_t shift[PS2_KEYMAP_SIZE];
  unsigned int uses_altgr;
  uint8_t altgr[PS2_KEYMAP_SIZE];
} PS2Keymap_t;

class PS2Keyboard {
  public:
    PS2Keyboard();

    /**
     * Registering the external interrupt.
     * setting the pin modes correctly and driving those needed to high.
     */
    static void begin(uint8_t dataPin, uint8_t irq_pin);

    /**
     * Returns true if there is a char to be read, false if not.
     */
    static bool available();

    /** 
     *  Discards any received data, sets available() to false without a call to read()
     */
    static void clear();

    /**
     * Retutns ps2 scan code.
     */
    static uint8_t readScanCode(void);

    /**
     * Returns the char last read from the keyboard.
     * If there is no char available, -1 is returned.
     */
    static int read();
    static int readUnicode();
};

#endif
