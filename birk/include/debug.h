#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void Debug(unsigned short usErrorType, int iLine, const char *szFormat, ...);

#define bdebug(...) Debug(1, __LINE__, __VA_ARGS__)
#define berror(...) Debug(0, __LINE__, __VA_ARGS__)

#endif /* ndef DEBUG_H */
