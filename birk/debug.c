#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <starg.h>

#define MAX_BUFFER 4096

void Debug(unsigned short usErrorType, int iLine, const char *szFormat, ...){
	va_list vaArgs;
	char szOutput[MAX_BUFFER + 1] = {0};
	const char *szType = (usErrorType == 1) ? "ERROR" : "DEBUG";

	va_start(vaArgs, szFormat);
	vsnprintf(szOutput, MAX_BUFFER, szFormat, vaArgs);
	va_end(vaArgs);

	printf(fLogFile, "%04i: %s %s", iLine, szType, szOutput);
}

