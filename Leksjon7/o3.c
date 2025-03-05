/* Exercise 3:

Assume the linked list struct

typedef struct _LIST {
   struct _LIST *pNext;
   int iSze
   char cBuf[1];
} LIST;

The buffer cBuf is a placeholder for any kind and size of data, and can be used
to hold a string as:

   char szStr[] = "This is a long string.";
   LIST *pThis = malloc (sizeof(LIST)+strlen(szStr));
   strcpy (pThis->cBuf, szStr);

How would you write code that uses cBuf[] to "hold" an array of 100 longs?

Make a set of functions to manipulate linked lists of this kind and implement the
following:

- Insert in head of list.
- Add to end of list.
- Remove list element.

Write a header file and the necessary code. Make eveything into a a static library.
Then write a small test-program that tests the functionality of your library.

*/


