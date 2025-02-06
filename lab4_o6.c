#include <stdio.h>
#include <string.h>

int main(int iArgC, char *paszArgV[]){

	printf("Unsorted:");
	for(int i = 1; i < iArgC - 1; ++i){
		printf(" %s", paszArgV[i]);
	}

	while(1){
		int iIterations = 0;
		for(int i = iArgC; i > 0; --i){ 

			char* pszFirstWord[sizeof(paszArgV[i])] = NULL;
			char* pszSecondWord[sizeof(paszArgV[i - 1])] = NULL;	

			pszFirstWord = &paszArgV[i];	
			pszSecondWord = &paszArgV[i - 1];	

			if(strcmp(pszFirstWord, pszSecondWord) == 1){
				char *pszTemp[] = NULL;
				*pszTemp = *pszFirstWord;
				*pszFirstWord = *pszSecondWord;	
				*pszSecondWord = *pszTemp;
				++iIterations;
			}
		}

		if(iIterations == 0){
			printf("Sorting complete!\n");
			break;
		}
	}

	printf("sorted:");
	for(int i = 1; i < iArgC - 1; ++i){
		printf(" %s", paszArgV[i]);
	}


	
	return 0;	
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
