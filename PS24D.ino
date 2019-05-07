//We always have to include the library
#include "LedControl.h"
#include "stdbool.h"
#include "PS2Keyboard.h"

const int DataPin = 8;
const int IRQpin = 3;

PS2Keyboard keyboard;

bool matrix[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

char currentChar = 'A';

void writeMatrix(bool charMatrix[3][4],int x, int y){
  if(x<8){
    if(y<8){
      for(int i=x;i<x+3;i++){
        for(int j=y;j<y+4;j++){
          if(i-x>=0){
            if(j-y>=0){
              matrix[i][j] = charMatrix[i-x][j-y];
            }
          }
        }
      }
    }
  }
}
void writeBytes (bool matrix[3][4],unsigned char byteFlag1,unsigned char byteFlag2){
  matrix[0][0] = ((byteFlag1 >> 7) & 0x01);
  matrix[0][1] = ((byteFlag1 >> 6) & 0x01);
  matrix[0][2] = ((byteFlag1 >> 5) & 0x01);
  matrix[0][3] = ((byteFlag1 >> 4) & 0x01);
  matrix[1][0] = ((byteFlag1 >> 3) & 0x01);
  matrix[1][1] = ((byteFlag1 >> 2) & 0x01);
  matrix[1][2] = ((byteFlag1 >> 1) & 0x01);
  matrix[1][3] = ((byteFlag1 >> 0) & 0x01);
  matrix[2][0] = ((byteFlag2 >> 7) & 0x01);
  matrix[2][1] = ((byteFlag2 >> 6) & 0x01);
  matrix[2][2] = ((byteFlag2 >> 5) & 0x01);
  matrix[2][3] = ((byteFlag2 >> 4) & 0x01);
}

void writeLetter (char letter, int x, int y){
  bool matrix[3][4];
  switch (letter){
  case 'A':
    writeBytes(matrix,0b11100101,0b11100000);
    break;

  case 'B':
    writeBytes(matrix,0b11111011,0b11000000);
    break;
      
  case 'C':
    writeBytes(matrix,0b01101001,0b10010000);
    break;
      
  case 'D':
    writeBytes(matrix,0b11111001,0b01100000);
    break;
      
  case 'E':
    writeBytes(matrix,0b11111101,0b10010000);
    break;
      
  case 'F':
    writeBytes(matrix,0b11110101,0b00010000);
    break;
      
  case 'G':
    writeBytes(matrix,0b01101001,0b11010000);
    break;
      
  case 'H':
    writeBytes(matrix,0b11110110,0b11110000);
    break;

  case 'I':
    writeBytes(matrix,0b10011111,0b10010000);
      
    break;
  case 'J':
    writeBytes(matrix,0b01011001,0b01110000);
    break;

  case 'K':
    writeBytes(matrix,0b11110010,0b11010000);
    break;

  case 'L':
    writeBytes(matrix,0b11111000,0b10000000);
    break;

  case 'M':
    writeBytes(matrix,0b11110011,0b11110000);
    break;

  case 'N':
    writeBytes(matrix,0b11110001,0b11100000);
    break;

  case 'O':
    writeBytes(matrix,0b01101001,0b01100000);
    break;

  case 'P':
    writeBytes(matrix,0b11110101,0b00100000);
    break;

  case 'Q':
    writeBytes(matrix,0b01101001,0b11100000);
    break;

  case 'R':
    writeBytes(matrix,0b11110101,0b10100000);
    break;

  case 'S':
    writeBytes(matrix,0b10101101,0b01010000);
    break;

  case 'T':
    writeBytes(matrix,0b00011111,0b00010000);
    break;

  case 'U':
    writeBytes(matrix,0b11111000,0b11110000);
    break;

  case 'V':
    writeBytes(matrix,0b01111000,0b01110000);
    break;

  case 'W':
    writeBytes(matrix,0b11111100,0b11110000);
    break;

  case 'X':
    writeBytes(matrix,0b11010010,0b11010000);
    break;

  case 'Y':
    writeBytes(matrix,0b10011010,0b01110000);
    break;

  case 'Z':
    writeBytes(matrix,0b11011001,0b10110000);
  
    break;
    
  case 'a':
    writeBytes(matrix,0b01001010,0b11100000);
    break;

  case 'b':
    writeBytes(matrix,0b11111010,0b01000000);
    break;

  case 'c':
    writeBytes(matrix,0b01001010,0b10100000);
    break;

  case 'd':
    writeBytes(matrix,0b01001010,0b11110000);
    break;

  case 'e':
    writeBytes(matrix,0b01101110,0b10100000);
    break;

  case 'f':
    writeBytes(matrix,0b01001110,0b01010000);
    break;

  case 'g':
    writeBytes(matrix,0b10101110,0b01100000);
    break;

  case 'h':
    writeBytes(matrix,0b11110010,0b11000000);
    break;

  case 'i':
    writeBytes(matrix,0b00001101,0b00000000);
    break;

  case 'j':
    writeBytes(matrix,0b10001101,0b00000000);
    break;

  case 'k':
    writeBytes(matrix,0b11110100,0b10100000);
    break;

  case 'l':
    writeBytes(matrix,0b00000111,0b10000000);
    break;

  case 'm':
    writeBytes(matrix,0b11100110,0b11100000);
    break;

  case 'n':
    writeBytes(matrix,0b11100010,0b11000000);
    break;

  case 'o':
    writeBytes(matrix,0b01001010,0b01000000);
    break;

  case 'p':
    writeBytes(matrix,0b11100110,0b00000000);
    break;

  case 'q':
    writeBytes(matrix,0b01101110,0b00000000);
    break;

  case 'r':
    writeBytes(matrix,0b00001110,0b00100000);
    break;

  case 's':
    writeBytes(matrix,0b10001110,0b00100000);
    break;

  case 't':
    writeBytes(matrix,0b00101111,0b10100000);
    break;

  case 'u':
    writeBytes(matrix,0b11101000,0b11100000);
    break;

  case 'v':
    writeBytes(matrix,0b01101000,0b01100000);
    break;

  case 'w':
    writeBytes(matrix,0b11101100,0b11100000);
    break;

  case 'x':
    writeBytes(matrix,0b10100100,0b10100000);
    break;

  case 'y':
    writeBytes(matrix,0b10101100,0b01100000);
    break;

  case 'z':
    writeBytes(matrix,0b00101110,0b10000000);
  
    break;
    
    
  case '0':
    writeBytes(matrix,0b11111001,0b11110000);
    break;

  case '1':
    writeBytes(matrix,0b10101111,0b10000000);
    break;

  case '2':
    writeBytes(matrix,0b10011101,0b10100000);
    break;

  case '3':
    writeBytes(matrix,0b10011011,0b01010000);
    break;

  case '4':
    writeBytes(matrix,0b01110100,0b11100000);
    break;

  case '5':
    writeBytes(matrix,0b10111101,0b01010000);
    break;

  case '6':
    writeBytes(matrix,0b01101101,0b11010000);
    break;

  case '7':
    writeBytes(matrix,0b00011101,0b00110000);
    break;

  case '8':
    writeBytes(matrix,0b11111011,0b11110000);
    break;

  case '9':
    writeBytes(matrix,0b10111011,0b01110000);
    break;

 /* case 223:
    writeBytes(matrix,0b00110011,0b00000000);
    break;*/

  case '-':
    writeBytes(matrix,0b01000100,0b01000000);
    break;

  case '+':
    writeBytes(matrix,0b01001110,0b01000000);
    break;

  case '/':
    writeBytes(matrix,0b10000110,0b00010000);
    break;

  case '*':
    writeBytes(matrix,0b01010010,0b01010000);;
    break;

  case '=':
    writeBytes(matrix,0b10101010,0b10100000);;
    break;

  case '.':
    writeBytes(matrix,0b10000000,0b00000000);
    break;

  case '!':
    writeBytes(matrix,0b10110000,0b00000000);
    break;

  case '?':
    writeBytes(matrix,0b00011001,0b00100000);
    break;

  case ',':
    writeBytes(matrix,0b10000100,0b00000000);
    break;

  case ')':
    writeBytes(matrix,0b01101000,0b00010000);
    break;

  case '(':
    writeBytes(matrix,0b10010110,0b00000000);
    break;

  case '[':
    writeBytes(matrix,0b00001111,0b10010000);
    break;

  case ']':
    writeBytes(matrix,0b10011111,0b00000000);
    break;

  case ':':
    writeBytes(matrix,0b00001010,0b00000000);
    break;

  case '"':
    writeBytes(matrix,0b00110000,0b00110000);
    break;
  
  }
  writeMatrix(matrix,x,y);
}
void writeLetterOnMatrix(char letter, int x, int y){
  writeLetter(letter,x,y);
  writeArduinoOnMatrix();
}
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,10,11);

/* we always wait a bit between updates of the display */
unsigned long delaytime1=500;
unsigned long delaytime2=50;
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  
  lc.shutdown(false);
  /* Set the brightness to a medium values */
  lc.setIntensity(8);
  /* and clear the display */
  lc.clearDisplay();
  Serial.begin(9600);
  
  Serial.println("Begin");
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */


 byte ToByte(bool b[8])
{
    byte c = 0;
    for (int i=8; i >= 0; --i)
        if (b[i])
            c |= 1 << i;
    return c;
}
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
    for(int i=0; i<sizeof(matrix);i++){
      for(int j=0; j<sizeof(matrix[i]); j++){
        
        lc.setLed(i,j,matrix[i][j]);
      }
    }
}

void clearArduinoOnMatrix() {
  /* here is the data for the characters */
    for(int i=0; i<(sizeof(matrix)/sizeof(matrix[0]));i++){
      for(int j=0; j<sizeof(matrix[i]); j++){
        matrix[i][j] = 0;
        lc.setLed(i,j,0);
      }
    }
}

void loop() { 
  
//  writeLetter('C',0,4);
//  writeArduinoOnMatrix();
//  writeLetter('h',4,4);
//  writeArduinoOnMatrix();

 // writeLetter('r',0,0);
//  writeArduinoOnMatrix();

//  writeLetter('i',4,0);
 // writeArduinoOnMatrix();

  //writeLetter('s',0,4);
  //writeArduinoOnMatrix();
  
 /* for(int i=8; i>=-2; i--){
     clearArduinoOnMatrix();
    writeLetterOnMatrix('Q',i,2);
    //writeLetterOnMatrix('Q',-1,2);
    delay(200);
  }
    delay(2000);
  */
 if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else {
      Serial.print(c);
      currentChar = c;
     //for(int i=8; i>=-2; i--){
      //clearArduinoOnMatrix();
      //writeLetterOnMatrix(c,i,2);
      //Serial.print("Y: ");
      //Serial.print(2);
      //Serial.print("X: ");
      //Serial.println(2);
      //delay(200);
     // }
      //delay(2000);
    }
  }
  
       writeLetterOnMatrix(currentChar,2,2);
   // writeLetterOnMatrix('Q',-1,2);
// delay(10000);;
 // rows();
  //columns();
  //single();
}
