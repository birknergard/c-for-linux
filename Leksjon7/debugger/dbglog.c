#include "dbglog.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void DbgLogger(unsigned long ulErrorType, int iLine, const char *szFile, const char *pszFormat, ...){
	va_list va_ArgumentPtr;
	char szOutput[256] = {0};
	const char *pszType = (ulErrorType==1) ? "ERROR" : "DEBUG";

	static FILE *fLogFile;
	static int iCallCounter;

	fLogFile = fopen("./debug.txt", "w");
	va_start(va_ArgumentPtr, pszFormat);
	vsnprintf(szOutput, 256 - 1, pszFormat, va_ArgumentPtr);
	va_end(va_ArgumentPtr);

	fprintf(fLogFile, "%04i: %s %s", iCallCounter, pszType, szOutput);

	/* We leave it to the OS to close the file. TODO: Will explain later(?) */

	return;
}
