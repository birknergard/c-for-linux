// list.c: Lession 7, exercise 3 (Lession 9 / Example)
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static NODE *CreateNode (void *pvData, int iSze)
{
   NODE *pThis = malloc (sizeof(NODE) + iSze);
   if (pThis != NULL) {
      memset (pThis, 0, sizeof(NODE) + iSze);
      pThis->iSze = iSze;
      memcpy (pThis->byBuf, pvData, iSze);
   }
   return pThis;
}


int InsertInList (LIST *pList, void *pvData, int iSze)
{
   int iRc = ERROR;
   NODE *pThis = CreateNode (pvData, iSze);

   if (pThis != NULL) {

      // If head is undefined (list is empty), set new node as head and tail
      if(pList->pHead == NULL){

         pList->pHead = pThis;
         pList->pTail = pThis;

         iRc = OK;

      } else {
         //  Newnode next ptr to current head
         pThis->pNext = pList->pHead;
         //  set current head prev ptr to new node
         pList->pHead->pPrev = pThis;
         // Define new list head as new node 
         pList->pHead = pThis;
         iRc = OK;
      }
   }

   return iRc;
}

int AddToList (LIST *pList, void *pvData, int iSze)
{
   int iRc = ERROR;
   NODE *pThis = CreateNode (pvData, iSze);
   if (pThis != NULL) {
      if (pList->pHead == NULL) {
         // For nodeless list(?) 
      }
      else {
         // Set tail node next ptr to new node
         pList->pTail->pNext = pThis;

         // Set new node as tail
         pList->pTail = pThis;

         iRc = OK;
      }
   }
   return iRc;
}

int RemoveFromList (LIST *pList, NODE *pToDelete)
{
   int iRc = ERROR;
   
   // Sets next node (after head) as new head the deleted node is the head
   if(pToDelete == pList->pHead){
      pList->pHead = pList->pHead->pNext;
   }
   // Sets next node (after head) as new head the deleted node is the head
   if(pToDelete == pList->pTail){
      pList->pTail = pList->pTail->pPrev;
   }

   NODE *pThis = NULL;
   NODE *pPrevious = NULL;
   NODE *pNext = NULL;

   pThis = pList->pHead;

   while (pThis != NULL) {
      if (pThis == pToDelete) {
         pPrevious = pThis->pPrev;
         pNext = pThis->pNext;

         // Handle deletion
         pPrevious->pNext = pNext;
         pNext->pPrev = pPrevious;

         iRc = OK;
         break;
      }
      // Check next node
      pThis = pThis->pNext;
   }

   if (iRc == OK) free (pToDelete);
   return iRc;
}
