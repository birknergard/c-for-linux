/*
Exercise 2:

Download a book from project gutenburg and find the number of occurences of the following:

-> two consecutive vowels
-> a specific letter followed immediately by the same letter
-> a pair of letters seperated by atleast 'm' and atmost 'n' characters

Try this first on a small piece of text to verify the correctness.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool SameCharWithinRange(char *szString, char cQuery, int iStart, int iMax);

bool IsVowel(char c);

int main(int iArgC, char **apszArgV){

	FILE *fpBook;
	char *szContent, *szVowels;
	char cWord, cNext;
	int iBookSize, i;
	int iTwoVowels, iDoubleLetters, iSameChar;

	fpBook = fopen("./o2_BOOK.txt", "r");
	if(fpBook != NULL){
		printf("Book found.\n");
		if(fseek(fpBook, 0, SEEK_END) == 0){
			iBookSize = ftell(fpBook);	
			rewind(fpBook);
		}	
	}

	szContent = (char *) malloc(iBookSize + 1);

	fgets(szContent, iBookSize, fpBook);

	iTwoVowels = 0;
	iDoubleLetters = 0;
	iSameChar = 0;

	for(i = 1; i < iBookSize - 1; i++){
		cWord = szContent[i];
		cNext = szContent[i+1];
		
		if(IsVowel(cWord) && IsVowel(cNext)){
			printf("%c and %c are both vowels.\n", cWord, cNext);
			iTwoVowels++;
		} 

		if(cWord == szContent[i+1]) iDoubleLetters++;

		if(SameCharWithinRange(szContent, cWord, i, 20)) iSameChar++;
	}

	printf("Total letters: %d\n", i);

	printf("Consecutive vowels occurences: %d\n", iTwoVowels);
	printf("Consecutive same letters occurences: %d\n", iDoubleLetters);
	printf("Same character within index: %d\n", iSameChar);

	fclose(fpBook);

	free(szContent);

	return 0;
}

bool SameCharWithinRange(char *szString, char cQuery, int iStart, int iRange){
	int i;
	char cCurrent;
	int iLength = strlen(szString); 

	/* Preventing overflow */
	if(iRange > iLength){
		iRange = iLength;	
	} 

	for(i = iStart; i < iRange; i++){
		cCurrent = szString[i+1]; 

		if(cCurrent == cQuery){
			return true;
		}
	}

	return false;
}

bool IsVowel(char c){
	int i;
	char *szVowels = "aeiou";
	for(i = 0; i < 5; i++){
		if(c == szVowels[i]) return true;	
	}
	return false;
}
