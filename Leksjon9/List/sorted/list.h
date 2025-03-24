/*
Excercise 4: Sorting lists - a bit more challenging
===================================================

Based on excercize 3. Rewrite list.h / list.c to handle lists of this type:

#define MAX_KEY 32

typedef struct _LIST {
   struct _LIST *pNext;
   char szKey[MAX_KEY];
   char *pszValue;
   int  iValue;
} LIST;

Add code that reads any number of lines from a file on the following format:

   <key>=[<numeric value>|"<string value>"]

For example...

   college="Westerdals"
   class=2
   grade="A+"
   students=77

Use a variant of the InsertSorted() function that, when inserting elements,
keeps the list sorted and ensures that the key doesn't become too long.

Add a function Lookup() that looks up a key and returns the value.
How can you handle the two types, integer and string?

Add another function Delete() that deletes an element given the key.

Keep the list handling in one source file and the reading of the key/value
pair file in the main source file.*/

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
   int *piValue;
} LIST;
#pragma pack()

// Prototypes - functions return OK or ERROR.
LIST *CreateList(char *szKey, char cFlag, int iDataSize, ...);
int FreeList(LIST *pHead);
int InsertSorted(LIST *pHead, char *szKey, char cFlag, int iDataSize, ...);

/*
 * How to handle num / string type
 * format string ["[str/int] [key]"]
 * */
void Lookup(LIST *pHead, char *szFormatFlag);
int Delete(LIST *pHead, char *szKey);
void PrintList (LIST *pList);

#endif // ndef _LIST_H
