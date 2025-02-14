#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	char *psz, *pInit;

	char *pVowelsCurr;
	char *szVowels;

	pInit = (char*) malloc(50 * sizeof(char) + 1);

	int iLen, iMaxSize, i, j;

	szVowels = "aeiouy";
	pVowelsCurr = szVowels;

	iMaxSize = 50;
	psz = (char*) malloc(50 * sizeof(char) + 1);

	printf("Please enter a string: ");
	scanf("%s", psz);

	/* pInit stores the initial position of the pointer */
	pInit = psz;

	iLen = strlen(psz);


	/* With indices */
	printf("\nARRAY: All vowels for string: %s ->", psz);
	for(i = 0; i < iLen; ++i){
		for(j = 0; j < strlen(szVowels); ++j){
			if(psz[i] == szVowels[j]){
				printf(" %c", psz[i]);
			}
		}
	}
	printf("\n");

	/* With pointer arithmetic */
	printf("\nPOINTER: All vowels for string: %s ->", psz);
	for(i = 0; i < iLen; ++i){
		psz++;
		pVowelsCurr = szVowels; 
		for(j = 0; j < strlen(szVowels) + 1; ++j){
			pVowelsCurr++;			
			if(*psz == *pVowelsCurr){
				printf(" %c", *psz);
			}	
		} 
	}
	printf("\n");


	/* Restores position of pointer with pszInit */ 
	psz = pInit;

	free(psz);
	

	return 0;
}
