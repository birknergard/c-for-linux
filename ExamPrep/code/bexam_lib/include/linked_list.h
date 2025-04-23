/*--------------------------------------------------
* AUTHOR: BKN
* DESCRIPTION: Doubly linked list implementation
*              which holds anonymous datatype in
*              form of a void *. Hence it is made
*              to be used as a baseline for further
*              abstractions.
--------------------------------------------------*/
#ifndef LINKED_LIST_H 
#define LINKED_LIST_H 

typedef struct _NODE {
   struct _NODE *pNext;
   struct _NODE *pPrev;
   int iSize;
   void *pvData;
} NODE;

/* Hate the LISTHEAD name so here we are. 
 * Why would you call it listhead when it just contains the head and tail? you good? */
typedef struct _LIST {
   NODE *pHead;
   NODE *pTail;
} LIST;

/* Prototypes - functions return OK or ERROR */
LIST *CreateList();
int Push(LIST *pList, void *pvData);
int Append(LIST *pList, void *pvData);
int RemoveFromList(LIST *pList, NODE *pToDelete);
int DestroyList(LIST **ppList);

#endif /* DOUBLELIST_H */ 
