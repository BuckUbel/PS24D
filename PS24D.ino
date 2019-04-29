//We always have to include the library
#include "LedControl.h"
#include "stdbool.h"
#include "PS2Keyboard.h"

const int DataPin = 8;
const int IRQpin =	3;

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

void writeLetter (char letter, int x, int y){
	bool matrix[3][4];
	switch (letter){
	case 'A':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'B':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;
			
	case 'C':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;
			
	case 'D':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;
			
	case 'E':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;
			
	case 'F':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;
			
	case 'G':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;
			
	case 'H':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'I':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
			
		break;
	case 'J':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'K':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case 'L':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'M':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'N':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'O':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'P':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'Q':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'R':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'S':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case 'T':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case 'U':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'V':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'W':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'X':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case 'Y':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'Z':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=1;
	
		break;
		
	case 'a':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'b':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'c':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'd':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case 'e':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'f':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case 'g':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'h':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'i':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'j':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'k':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'l':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'm':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'n':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'o':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'p':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'q':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case 'r':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 's':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 't':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'u':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'v':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'w':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'x':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'y':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case 'z':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
	
		break;
		
		
	case '0':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case '1':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '2':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case '3':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case '4':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case '5':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case '6':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case '7':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case '8':
		matrix[0][0]=1;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;

	case '9':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=1;
		matrix[2][3]=1;
		break;
/*
	case '(char)223':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;
*/
	case '-':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '+':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '/':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case '*':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=1;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case '=':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case '.':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '!':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '?':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=0;
		break;

	case ',':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case ')':
		matrix[0][0]=0;
		matrix[0][1]=1;
		matrix[0][2]=1;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case '(':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '[':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=1;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=1;
		break;

	case ']':
		matrix[0][0]=1;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=1;
		matrix[1][0]=1;
		matrix[1][1]=1;
		matrix[1][2]=1;
		matrix[1][3]=1;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case ':':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=0;
		matrix[0][3]=0;
		matrix[1][0]=1;
		matrix[1][1]=0;
		matrix[1][2]=1;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=0;
		matrix[2][3]=0;
		break;

	case '"':
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[0][2]=1;
		matrix[0][3]=1;
		matrix[1][0]=0;
		matrix[1][1]=0;
		matrix[1][2]=0;
		matrix[1][3]=0;
		matrix[2][0]=0;
		matrix[2][1]=0;
		matrix[2][2]=1;
		matrix[2][3]=1;
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
LedControl lc=LedControl(12,10,11,1);

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
	
	lc.shutdown(0,false);
	/* Set the brightness to a medium values */
	lc.setIntensity(0,8);
	/* and clear the display */
	lc.clearDisplay(0);
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
				
				lc.setLed(0,i,j,matrix[i][j]);
			}
		}
}

void clearArduinoOnMatrix() {
	/* here is the data for the characters */
		for(int i=0; i<(sizeof(matrix)/sizeof(matrix[0]));i++){
			for(int j=0; j<sizeof(matrix[i]); j++){
				matrix[i][j] = 0;
				lc.setLed(0,i,j,0);
			}
		}
}

void loop() { 
	
//	writeLetter('C',0,4);
//	writeArduinoOnMatrix();
//	writeLetter('h',4,4);
//	writeArduinoOnMatrix();

 // writeLetter('r',0,0);
//	writeArduinoOnMatrix();

//	writeLetter('i',4,0);
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
// delay(10000);
 // rows();
	//columns();
	//single();
}
