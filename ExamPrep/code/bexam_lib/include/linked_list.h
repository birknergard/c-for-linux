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

/* Node struct */
typedef struct _NODE {
   struct _NODE *pNext;
   struct _NODE *pPrev;
   int iSize;
   void *pvData;
} NODE;

/* Doubly linked list struct */
typedef struct _LIST {
   NODE *pHead;
   NODE *pTail;
   int iLength;
} LIST;

/* Creation functions */
LIST *CreateList();
int DestroyList(LIST **ppList);

/* Getter functions */
NODE Get(LIST pList, int i);
void *GetData(LIST pList, int i);

/* List modification functions - return OK or ERROR */
int Push(LIST *pList, void *pvData);
int Append(LIST *pList, void *pvData);
int RemoveFromList(LIST *pList, NODE *pToDelete);

#endif /* DOUBLELIST_H */ 
