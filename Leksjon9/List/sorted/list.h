/* AUTHOR: BKN
 * DESCRIPTION:

*/
#ifndef LIST_H
#define LIST_H

#define OK      0
#define ERROR   1
#define MAX_KEY 32
#define MAX_DATA 256

#pragma pack(1)
typedef struct _LIST {
   struct _LIST *pNext;
   char *pszKey;
   char *pszValue;
   int iValue;
} LIST;
#pragma pack()

LIST *CreateList(char *szKey, char cFlag, ...);
int FreeList(LIST **ppHead);
int InsertSorted(LIST **pHead, char *szKey, char cFlag, ...);

/*
 * How to handle num / string type
 * format string ["[S (for string) or I(for int)]", data]
 * */
void *Lookup(LIST *pHead, char *szKey);
int Delete(LIST **pHead, char *szKey);
void PrintList (LIST *pList);


#endif // ndef _LIST_H
