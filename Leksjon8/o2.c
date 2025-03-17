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
	printf("char before conversion -> %c", c);
	int iCharBits = (int) c;


	
	printf("char after conversion -> %c", iCharBits);


}

int main(void){
	PrintBin(105);
	PrintBin(520);

	return 0;
}
