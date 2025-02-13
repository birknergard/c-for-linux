#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(char **apsz, int iIndex);
void SwapTwo(char **pszA, char **pszB);
void BubbleSort(char **apszArr, int iLen);
void PrintStringArray(char **apszArr, int iLen, char *szDesc);


int main(int iArgC, char **paszArgV){

	int iMaxLength = 50;

	int iLen = iArgC - 1; 
	char **szArr;	
	szArr = malloc(iLen * sizeof(char*));
	if(szArr == NULL) return 1;
	
	int i;
	for(i = 1; i < iLen; i++){
		/* verify each string for max length */
		if(sizeof(paszArgV + 1) > iMaxLength){
			printf("%s contains too many characters. MAX = 50 characters.\n", paszArgV[i]);
			return 1;	
		}
	}

	for(i = 0; i < iLen; i++){
		/* Allocating memory for each string in the array*/
		szArr[i] = malloc((iMaxLength * sizeof(char)) + 1); 	
		if(szArr[i] == NULL) return 1;

		/* copying strings from args to sz array */
		szArr[i] = paszArgV[i + 1];
	}

	PrintStringArray(szArr, iLen, "unsorted");

	BubbleSort(szArr, iLen);

	PrintStringArray(szArr, iLen, "sorted");
	
	/* Freeing memory for stringarray*/
	for(i = iLen - 1; i >= 0; --i){
		printf("Freeing %s(%d bytes) from strArr\n", szArr[i], strlen(szArr[i]));
		free(szArr[i]);
	}

	printf("Freeing szArr.\n");
	free(szArr);

	return 0;	
}

void Swap(char **apsz, int iIndex){
	printf("Entering swap.\n");
	printf("Running swap on words %s and %s...\n", apsz[iIndex - 1], apsz[iIndex]);

	char *temp = apsz[iIndex - 1];	
	
	apsz[iIndex - 1] = apsz[iIndex];
	apsz[iIndex] = temp;
}

void SwapTwo(char **pszA, char **pszB){
	char *temp = NULL;
	temp = *pszA;

	*pszA = *pszB;	
	*pszB = temp;	

}

void BubbleSort(char **apszArr, int iLen){
	printf("args size = %d\n", iLen);
	while(1){
		printf("\n---------------------------------------\n");
		int iIterations	= 0;	
		int i;
		for(i = 1; i < iLen;  ++i){
			printf("i = %d\n", i);
			printf("i - 1 = %d\n", i - 1);

			printf(
				"Checking bubble on \"%s\" and \"%s\" (indexes %d and %d) ...\n",
				apszArr[i - 1], apszArr[i], i - 1, i
			);

			int iStrCompare = strcmp(apszArr[i - 1], apszArr[i]);
			printf("Stringcompare results: %d\n", iStrCompare);
			if(iStrCompare <= 0){
				printf("\"%s\" is smaller or equal to \"%s\". Not swapping ...", apszArr[i - 1], apszArr[i]);
			} else {
				printf("\"%s\" is bigger than \"%s\". Swapping ...", apszArr[i - 1], apszArr[i]);
				SwapTwo(&apszArr[i - 1], &apszArr[i]);
				++iIterations;
			}

			printf("%d iterations\n", iIterations);
		}
		PrintStringArray(apszArr, iLen, "Current");
		
		if(iIterations == 0){
			printf("Sort complete! \n\n");	
			break;
		} else {
			printf("Items were swapped %d times on current loop. Continuing ...\n\n", iIterations);	
		}
	}
}

void PrintStringArray(char **apszArr, int iLen, char *szDesc){
	printf("%s: ", szDesc);
	int i;
	for(i = 0; i < iLen; ++i){
		/* verifies string size */
		printf(" %s(%p)", apszArr[i], &apszArr[i]);
	}
	printf("\n");
}
/*
Exercise 6 - Important exam preperation !!!

Combine the techniques from exercise 4 and 5 and print out the parameters in
sorted order. Tip: Use strcmp() or stricmp() to compare the strings.
Check the man pages and/or Google. Another tip: There is no need to copy
the strings themselves from one place to another, just swap pointers...

(This exercise was previously a obligatory assignment.)

MANUEL FOR STRCMP
NAME
       strcmp, strncmp - compare two strings

SYNOPSIS
       #include <string.h>

       int strcmp(const char *s1, const char *s2);

       int strncmp(const char *s1, const char *s2, size_t n);

DESCRIPTION
       The  strcmp()  function compares the two strings s1 and s2.  It returns an integer less than, equal to, or greater
       than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.

       The strncmp() function is similar, except it compares only the first (at most) n bytes of s1 and s2.

RETURN VALUE
       The strcmp() and strncmp() functions return an integer less than, equal to, or greater than zero  if  s1  (or  the
       first n bytes thereof) is found, respectively, to be less than, to match, or be greater than s2.
*/
