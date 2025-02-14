#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
		
	char szBase[] = "Hello World";
	char *sz;
	sz = szBase;
	int iSzLen;

	iSzLen = 0;
	for(;;){
		printf("\nCurrent size: %d\n", iSzLen);
		printf("current char: %c\n", *sz);
		if(*sz == NULL || iSzLen > 50){
			break;
		}
		sz++;
		iSzLen++;
	}

	
	printf("Length of \"Hello World\" is %d\n", iSzLen); /* adding one to i given zero termination "\0"*/


	/* Output should be the same as the following */
	printf("strlen of \"Hello World\"%d\n", strlen(szBase));



	return 0;
}
