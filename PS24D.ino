//We always have to include the library
#include "LedControl.h"
#include "stdbool.h"
#include "PS2Keyboard.h"
#include "Font.h"

const int LEDDataPin = 12;
const int LEDLoadPin = 11;
const int LEDCLKPin = 10;
const int DataPin = 8;
const int IRQpin = 3;

LedControl lc = LedControl(LEDDataPin,LEDCLKPin, LEDLoadPin);
PS2Keyboard keyboard;
Font myFont;

bool isEntered = false;
bool isRotating = false;
const int maxCharCount = 100;
int charCount = 0;
char currentLetters[100];
int currentBrightness = 8;
int currentSpeed = 200;
char currentPos = 0;

bool matrix[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  lc.shutdown(false);
  /* Set the brightness to a medium values */
  lc.setIntensity(currentBrightness);
  /* and clear the display */
  lc.clearDisplay();
  // set serial monitor baud
  Serial.begin(9600);
  Serial.println("Begin");
}

void clearMatrix() {
  /* here is the data for the characters */
    for(int i=0; i<(sizeof(matrix)/sizeof(matrix[0]));i++){
      for(int j=0; j<sizeof(matrix[i]); j++){
        matrix[i][j] = 0;
        lc.setLed(i,j,0);
      }
    }
}

void saveLetter(char letter){
  currentLetters[charCount] = letter;
  charCount++;
}

void eraseString(){
  charCount = 0;
  // TODO: erase all chars in array
}

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

void writeBytes (bool matrix[3][4],int bitWord){
  for(int i=0; i< 3; i++){
    for(int j=0; j< 4; j++){
      matrix[i][j] = ((bitWord >> 15-(i*4)-j) & 0x01);
    }
  }
}

void writeLetterOnMatrix (char letter, int x, int y){
  bool matrix[3][4];
  int fontBytes = myFont.getFontBytes(letter);
  writeBytes(matrix, fontBytes);
  writeMatrix(matrix,x,y);
  writeMatrixOnDisplay();
}

void writeMatrixOnDisplay() {
  /* here is the data for the characters */
    for(int i=0; i<sizeof(matrix);i++){
      for(int j=0; j<sizeof(matrix[i]); j++){
        lc.setLed(i,j,matrix[i][j]);
      }
    }
}

void scrollThrough(){
   for(int j=0; j<charCount; j++){
      for(int i=8; i>=-3; i--){
        if(j>0 && i == 8){
          i=0;
        }
        clearMatrix();
        writeLetterOnMatrix(currentLetters[j],i,2);
        if(j+1<charCount){
          writeLetterOnMatrix(currentLetters[j+1],i+4,2);
        }
        if(j+2<charCount){
          writeLetterOnMatrix(currentLetters[j+2],i+8,2);
        }
        delay(currentSpeed);
      }
    }
    currentPos = charCount -1;
}

void loop() { 
  
 if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
    switch (c){
      case PS2_DELETE:
        currentLetters[charCount] = '\0';
        if(charCount>0){
          charCount--;
        }
        if(currentPos>0){
          currentPos--;
        }
        if(currentPos == 0 || charCount == 0){
          currentLetters[charCount] = '\0';
          clearMatrix();
        }
        break;
      case PS2_LEFTARROW:
        if(currentPos>0){
        currentPos--;
      }
        break;
      case PS2_RIGHTARROW:
        if(currentPos<charCount-1){
        currentPos++;        
      }
        break;
      case PS2_UPARROW:
        if(currentSpeed>=100){
        currentSpeed-=50;
      }
        break;
      case PS2_DOWNARROW:
        if(currentSpeed<=2450){
        currentSpeed+=50;        
      }
        break;
      case PS2_PAGEUP:
        if(currentBrightness<=14){
        currentBrightness++;
        lc.setIntensity(currentBrightness);
      }
        break;
      case PS2_PAGEDOWN:
        if(currentBrightness>=0){
        currentBrightness--;
        lc.setIntensity(currentBrightness);
      }
        break;
      case PS2_F1:
        isRotating = !isRotating;
        break;
      case PS2_ENTER:
        Serial.println(charCount);
        isEntered = true;
        break;
      default:
        if(isEntered){
          isEntered = false;
          eraseString();
        }
        Serial.print(c);
        currentPos = charCount;
        saveLetter(c);
        break;
    }
  }
  if(isRotating){
    scrollThrough();
  }
  else if(isEntered){
    scrollThrough();
    isEntered = false;
    clearMatrix();
  }
  else{
    if(currentLetters[currentPos] != '\0'){
     if(currentPos-1 >= 0){
        writeLetterOnMatrix(currentLetters[currentPos],4,2);
        writeLetterOnMatrix(currentLetters[currentPos-1],0,2);
     }
     else{
      writeLetterOnMatrix(currentLetters[currentPos],0,2);
     }
    }
  }
}
