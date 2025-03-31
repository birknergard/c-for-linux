#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "util.h"


int ParsePositiveInt(char *psz){
	int iNum, iLen, i;
	char *pszBuffer = NULL;


	if(sizeof(psz) >= MAX_STRING_SIZE){
		berror("Input is too large. (MAX: 128 bytes)");
		return -1;	
	}

	/* Check each char if digit */
	i = 0;
	iLen = strlen(psz);
	while(i < iLen){
		if(isdigit(psz[i]) == 0){
			bdebug("This char: %d is not digit\n", psz[i]);
			return -1;	
		}
		i++;
	}
;

	iNum = atoi(psz);

	free(pszBuffer);
	pszBuffer = NULL;
	
	return iNum;
}
