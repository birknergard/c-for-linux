#ifndef DBGLOG_H
#define DBGLOG_H
void DbgLogger(unsigned long ulErrorType, int iLine, const char *szFile, const char *pszFormat, ...);

#define pgdebug(...) if(glob_bTraceEnabled == 1){ DbgLogger(0, __LINE__, __FILE__, __VA_ARGS__)}
#define pgerror(...) DbgLogger(1, __LINE__, __FILE__, __VA_ARGS__)


#endif

