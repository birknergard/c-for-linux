#ifndef _DBGLOG_H_
#define _DBGLOG_H_
void DbgLogger(unsigned long ulErrorType, int iLine, const char *szFile, const char *szFormat);

#define pgdebug(...) if(glob_bTraceEnabled == 1){ DbgLogger(0, _LINE_, _FILE_, _VA_ARGS_)}
#define pgerror(...) DbgLogger(1, _LINE_, _FILE_, _VA_ARGS_)


#endif

