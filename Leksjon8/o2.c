/*
Exercise 2:

Write a function that prints 8-bit unsigned integer as a binary output.
write a function that inverts the bits in a character and print out the character.
*/

#include <stdio.h>
#include <stdlib.h>

void PrintBin(unsigned short uiInput){
	int i, iBit;
	unsigned int uiBuffer;
	char szBinaryNum[8];

	szBinaryNum[8] = '\0';

	uiBuffer = uiInput;
	i = 7;

	while(uiBuffer > 0){
		iBit = uiBuffer % 2;
		szBinaryNum[i] = iBit + '0';
		uiBuffer = uiBuffer / 2;	
		--i;
	}

	for(; i >= 0; i--){
		szBinaryNum[i] = '0';	
	}

	printf("%u in binary is %s\n", uiInput, szBinaryNum);
}

void InvertCharBits(char c){
	printf("char before conversion ->\n");
	PrintBin((unsigned short) c); 
	char cFlipped;
	cFlipped = ~c;
	
	printf("char after conversion ->\n");
	PrintBin((unsigned short) cFlipped);
}

int main(void){

	int iTest, iShifted;
	iTest = 128;
	iShifted = iTest >> 5;

	PrintBin(iTest);
	PrintBin(105);

	PrintBin(520);

	InvertCharBits('0');			

	return 0;
}
