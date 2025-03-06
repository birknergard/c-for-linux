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

int Encode();
int Decode();

int main(int iArgC, char **apszArgV){

	FILE *fpText;
	char *szInput, *szFileBuffer, cTextChar, cInputChar;
	int i, iCurrentCharIndex, iInputLength, iTextLength, iTextSize;
	long lPosition, *lpPositionArray;

	szInput = (char*) malloc(MAX_BUFFER);
	if(szInput == NULL)
		return 1;

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
	if(lpPositionArray == NULL)
	   	return 1;
	
	Encode(szInput, lpPositionArray, szFileBuffer, iTextLength);

	Decode(lpPositionArray, iInputLength, szFileBuffer);
	
	free(szInput);
	free(szFileBuffer);
	free(lpPositionArray);
	
	return 0;
}

int Encode(char *szWord, long *lpCode, char *szFileText, int iFileTextLength){
	int i;
	int iRemainingChars = strlen(szWord);	
	int iCurrentCharIndex = 0;
	int lPosition = 0;
	const int iWordLength = iRemainingChars;

	char cTextChar, cInputChar;

	for(i = 0; i < iFileTextLength; i++){
		printf("%c", szFileText[i]);
		cTextChar = szFileText[i];	
		cInputChar = szWord[iCurrentCharIndex];

		if(lPosition == 0 && cTextChar == cInputChar){
			lPosition = (long) i; 
			AddPosition(lPosition, lpCode, iCurrentCharIndex);
			++iCurrentCharIndex;	
			--iRemainingChars;

		} else if(i - lPosition >= 10 && cTextChar == cInputChar){
			lPosition = (long) i; 
			AddPosition(lPosition, lpCode, iCurrentCharIndex);
			++iCurrentCharIndex;	
			--iRemainingChars;
		}
	}

	if(iRemainingChars != 1){
		puts("\n\nYour input could not be encoded.\n");
		return 1;	
	} else {
		PrintCode(lpCode, iWordLength - 1);
		return 0;
	}
}

int Decode(long *lpCode, int iCodeLength, char *szFileText){
	const int iFileTextLength = strlen(szFileText) - 1;
	int i;
	char *szDecoded;

	szDecoded = (char*) malloc((sizeof(char) * iCodeLength));
	if(szDecoded == NULL)
		return 1;
	
	for(i = 0; i < iCodeLength - 1; i++){
		if(lpCode[i] > iFileTextLength || lpCode[i] < 0){
			printf("Code -%d- is out of bounds.", lpCode[i]);
			return 1;
		}

		szDecoded[i] = szFileText[lpCode[i]];
	}

	printf("The decoded code is %s\n", szDecoded);

	free(szDecoded);

	return 0;
}

void AddPosition(long iPosition, long *lpArray, int iIndex){
	lpArray[iIndex] = iPosition;
}

void PrintCode(long *lpArray, int iLength){
	int i;

	printf("\nYour code is: ");
	for(i = 0; i < iLength; i++){
		printf(" %d", lpArray[i]);	
	}
	printf("\n");
}
