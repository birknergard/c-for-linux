// list.c: Lession 7, exercise 3 (Lession 9 / Example)
/*Excercise 3: Sorting lists
==========================

Rewrite list.h / list.c to handle lists of this type:

typedef struct _LIST {
   struct _LIST *pNext;
   char *pszString;
} LIST;

Add a InsertSorted() function that, when inserting elements, keeps a list of strings sorted
in alphabetical order.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_2.h"

LIST CreateList(char *pszString, int iSize){
   LIST *pList = (LIST*) malloc(sizeof(LIST) + iSize);
   if(pList != NULL){
      memset(pList, 0, (sizeof(LIST) + iSize))
      strncpy(pList->pszString, pszString, iSize);
   }
   return pList;
}

int FreeList(LIST *pHead){
   LIST pPrev = NULL;

   if(pHead->pNext == NULL){
      free(pHead); 
      return 0;
   }

   LIST *pCurrent = pHead;   
   LIST *pNext = pHead->pNext;

   while(pNext != NULL){
      free(pNext);
      pNext = pNext->pNext;
   }

}

int InsertSorted(LIST *pHead, char *pszString){
   LIST *pNewNode = CreateList(pszString, strlen(pszString)); 
   LIST *pCurrent = pHead;
   LIST *pPrev = NULL;


   while(pCurrent != NULL){
      if(strcmp(pNewNode->pszString, pCurrent->pszString) == 1){
         // If equal or higher value, go next
         pPrev = pCurrent;
         pCurrent = pCurrent->pNext;       

      } else {
         // if pointing to head node
         if(pCurrent == pHead){
            pNewNode->pNext = pCurrent;
            pHead = pNewNode;
            return 0;
         }  

         // if pointing to null
         if(pCurrent->pNext == NULL){
            pCurrent->pNext = pNewNode;
         } 

         // handle insert
         pPrev->pNext = pNewNode;
         pNewNode->pNext = pCurrent;
      }
   }
}
