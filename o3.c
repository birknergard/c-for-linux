/*
Exercise 3:

Consider the following text:

"Now the way that the book winds up is this: Tom and me found the money that the robbers
hid in the cave, and it made us rich. We got six thousand dollars apiece -- all gold.
It was an awful sight of money when it was piled up. Well, Judge Thatcher he took it
and put it out at interest, and it fetched us a dollar a day apiece all the year
round -- more than a body could tell what to do with. The Widow Douglas she took me
for her son, and allowed she would sivilize me; but it was rough living in the house
all the time, considering how dismal regular and decent the widow was in all her ways;
and so when I couldn't stand it no longer I lit out. I got into my old rags and my
sugar-hogshead again, and was free and satisfied. But Tom Sawyer he hunted me up
and said he was going to start a band of robbers, and I might join if I would go
back to the widow and be respectable. So I went back."

This text can also be found as "adventures.txt".

Now if I take the word : "computer"

Encode it such that I only find the position of each character in the text and make sure
that each position is atleast seperated by 10 characters from the previous position.

My output will be :

101 133 200 218 236 253 282 314
C   O   M   P   U   T   E   R

Now write a program that takes a word from the user as an input and encode it as following:

-> All letters must be converted to positions
-> The output must be just the positions seperated by space
-> The positions must follow one specific rule : they must be seperated by atleast 10 characters.
-> If it is unable to complete the word - print error message and exit

Write a program that does the opposite - takes in a code and decodes it to the word.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER 4096

void AddPosition(long iPosition, long *lpArray, int iIndex);

void PrintCode(long *lpArray, int iLength);

int main(int iArgC, char **apszArgV){

	FILE *fpText;
	char *szInput, *szFileBuffer, cTextChar, cInputChar;
	int i, iCurrentCharIndex, iInputLength, iTextLength, iTextSize;
	long lPosition, *lpPositionArray;


	szInput = (char*) malloc(MAX_BUFFER + 1);


	fpText = fopen("./Leksjon6/adventures.txt","r");
	if(fpText != NULL){
		if(fseek(fpText, 0, SEEK_END) == 0){
			iTextSize = ftell(fpText);	
			rewind(fpText);
		}	
	}

	szFileBuffer = (char*) malloc(iTextSize);
	fgets(szFileBuffer, iTextSize, fpText);
	fclose(fpText);
	
	puts("Enter your input\n--> ");
	fgets(szInput, MAX_BUFFER, stdin);

	iInputLength = strlen(szInput);
	iTextLength = strlen(szFileBuffer);

	lpPositionArray = (long*) malloc(sizeof(long) * iInputLength);
	if(lpPositionArray == NULL) return 1;
	
	iCurrentCharIndex = 0;
	for(i = 0; i < iTextLength; i++){
		cTextChar = szFileBuffer[i];	
		cInputChar = szInput[iCurrentCharIndex];

		if(cTextChar == cInputChar){
			lPosition = iCurrentCharIndex; 
			AddPosition(lPosition, lpPositionArray, iCurrentCharIndex);
			++iCurrentCharIndex;	
		}
	}

	PrintCode(lpPositionArray, iInputLength);
	
	free(szInput);
	free(lpPositionArray);
	
	return 0;
}

void AddPosition(long iPosition, long *lpArray, int iIndex){
	lpArray[iIndex] = iPosition;
}

void PrintCode(long *lpArray, int iLength){
	int i;

	puts("-");
	for(i = 0; i < iLength; i++){
		printf(" %d", lpArray[i]);	
	}
	puts(" -\n");
}

