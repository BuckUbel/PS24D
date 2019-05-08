#include "Font.h"
Font::Font() {
  // nothing to do here, begin() does it all
}
int Font::getFontBytes(char letter){
    switch (letter){
  case 'A':
    return 0b1110010111100000;
    break;

  case 'B':
    return 0b1111101111000000;
    break;
      
  case 'C':
    return 0b0110100110010000;
    break;
      
  case 'D':
    return 0b1111100101100000;
    break;
      
  case 'E':
    return 0b1111110110010000;
    break;
      
  case 'F':
    return 0b1111010100010000;
    break;
      
  case 'G':
    return 0b0110100111010000;
    break;
      
  case 'H':
    return 0b1111011011110000;
    break;

  case 'I':
    return 0b1001111110010000;
      
    break;
  case 'J':
    return 0b0101100101110000;
    break;

  case 'K':
    return 0b1111001011010000;
    break;

  case 'L':
    return 0b1111100010000000;
    break;

  case 'M':
    return 0b1111001111110000;
    break;

  case 'N':
    return 0b1111000111100000;
    break;

  case 'O':
    return 0b0110100101100000;
    break;

  case 'P':
    return 0b1111010100100000;
    break;

  case 'Q':
    return 0b0110100111100000;
    break;

  case 'R':
    return 0b1111010110100000;
    break;

  case 'S':
    return 0b1010100101010000;
    break;

  case 'T':
    return 0b0001111100010000;
    break;

  case 'U':
    return 0b1111100011110000;
    break;

  case 'V':
    return 0b0111100001110000;
    break;

  case 'W':
    return 0b1111110011110000;
    break;

  case 'X':
    return 0b1101001011010000;
    break;

  case 'Y':
    return 0b1001101001110000;
    break;

  case 'Z':
    return 0b1101100110110000;
    break;
    
  case 'a':
    return 0b0100101011100000;
    break;

  case 'b':
    return 0b1111101001000000;
    break;

  case 'c':
    return 0b0100101010100000;
    break;

  case 'd':
    return 0b0100101011110000;
    break;

  case 'e':
    return 0b0110111010100000;
    break;

  case 'f':
    return 0b0100111001010000;
    break;

  case 'g':
    return 0b1010111001100000;
    break;

  case 'h':
    return 0b1111001011000000;
    break;

  case 'i':
    return 0b0000110100000000;
    break;

  case 'j':
    return 0b1000110100000000;
    break;

  case 'k':
    return 0b1111010010100000;
    break;

  case 'l':
    return 0b0000011110000000;
    break;

  case 'm':
    return 0b1110011011100000;
    break;

  case 'n':
    return 0b1110001011000000;
    break;

  case 'o':
    return 0b0100101001000000;
    break;

  case 'p':
    return 0b1110011000000000;
    break;

  case 'q':
    return 0b0110111000000000;
    break;

  case 'r':
    return 0b0000111000100000;
    break;

  case 's':
    return 0b1000111000100000;
    break;

  case 't':
    return 0b0010111110100000;
    break;

  case 'u':
    return 0b1110100011100000;
    break;

  case 'v':
    return 0b0110100001100000;
    break;

  case 'w':
    return 0b1110110011100000;
    break;

  case 'x':
    return 0b1010010010100000;
    break;

  case 'y':
    return 0b1010110001100000;
    break;

  case 'z':
    return 0b0010111010000000;
    break;
    
  case '0':
    return 0b1111100111110000;
    break;

  case '1':
    return 0b1010111110000000;
    break;

  case '2':
    return 0b1001110110100000;
    break;

  case '3':
    return 0b1001101101010000;
    break;

  case '4':
    return 0b0111010011100000;
    break;

  case '5':
    return 0b1011110101010000;
    break;

  case '6':
    return 0b0110110111010000;
    break;

  case '7':
    return 0b0001110100110000;
    break;

  case '8':
    return 0b1111101111110000;
    break;

  case '9':
    return 0b1011101101110000;
    break;

  case -80:
    return 0b0011001100000000;
    break;

  case '-':
    return 0b0100010001000000;
    break;

  case '+':
    return 0b0100111001000000;
    break;

  case '/':
    return 0b1000011000010000;
    break;

  case '*':
    return 0b0101001001010000;;
    break;

  case '=':
    return 0b1010101010100000;;
    break;

  case '.':
    return 0b1000000000000000;
    break;

  case '!':
    return 0b1011000000000000;
    break;

  case '?':
    return 0b0001100100100000;
    break;

  case ',':
    return 0b1000010000000000;
    break;

  case ')':
    return 0b0110100000010000;
    break;

  case '(':
    return 0b1001011000000000;
    break;

  case '[':
    return 0b0000111110010000;
    break;

  case ']':
    return 0b1001111100000000;
    break;

  case ':':
    return 0b0000101000000000;
    break;

  case '"':
    return 0b0011000000110000;
    break;

  case ' ':
    return 0b0000000000000000;
    break;
  }
}

