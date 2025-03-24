// list.h: Lession 7, exercise 3
//
//
/*Exercise 2: Doubly linked lists
===============================

Look at List/lish.h and list.c. Rewrite the list to be a doubly linked list.
For the list-head and tail use the following struct:

typedef struct _LISTHEAD {
   LIST *pHead;
   LIST *pTail;
} LISTHEAD;

Rewrite the Insert/Append/Delete-functions to use a LISTHEAD * as first parameter.
Rewrite testlist.c to handle the new format.
*/

#ifndef _LIST_H_
#define _LIST_H_

#define OK      0
#define ERROR   1

// The list type:
typedef unsigned char BYTE;

/* If you think im calling a node a list you are dreaming my guy */
typedef struct _NODE {
   struct _NODE *pNext;
   struct _NODE *pPrev;
   int iSze;
   BYTE byBuf[];
} NODE;

/* Hate the LISTHEAD name so here we are. 
 * Why would you call it listhead when it contains the list and the head????? you good? */
typedef struct _LIST {
   NODE *pHead;
   NODE *pTail;
} LIST;

// Prototypes - functions return OK or ERROR.
int InsertInList (LIST *pList, void *pvData, int iSze);
int AddToList (LIST *pList, void *pvData, int iSze);
int RemoveFromList (LIST *pList, NODE *pToDelete);

#endif // ndef _LIST_H
