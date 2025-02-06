#include <stdio.h>

int main(){

	int *pInt;
	char *pChar;
	short *pShort;
	double *pDouble;

	printf("SIze of pointers are %lu %lu %lu %lu respectively \n ", sizeof(pInt), sizeof(pChar), sizeof(pShort), sizeof(pDouble));

	printf("SIze of variables are %lu %lu %lu %lu respectively \n ", sizeof(*pInt), sizeof(*pChar), sizeof(*pShort), sizeof(*pDouble));

	return 0;
}

