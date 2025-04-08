#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

static NODE *CreateNode(void *pvData){
   NODE *pThis;

   pThis = (NODE *) malloc(sizeof(NODE));
   if (pThis == NULL) {
      berror("failed malloc in CreateNode()");
      return NULL;
   }

   memset (pThis, 0, sizeof(NODE));
   pThis->iSze = sizeof(*pvData);
   memcpy (pThis->pvData, pvData, pThis->iSze);

   return pThis;
}

LIST *CreateList(){
   LIST *pList;
   pList = NULL;

   pList = (LIST *) malloc(sizeof(LIST));
   if(pList == NULL){
      bdebug("Error with malloc in CreateList().");
      return NULL;
   }
   memset(pList, 0, sizeof(LIST));
}

int DestroyList(LIST **ppList){
   LIST *pCurrent = ppList->pHead;   
   LIST *pTemp = NULL;

   while(pCurrent != NULL){

      if(pCurrent->pvData != NULL){
         free(pCurrent->pvData);
         pCurrent->pvData = NULL;
      }
      
      pTemp = pCurrent;
      pCurrent = pCurrent->pNext;
      free(pTemp);
   }

   pCurrent = NULL;
   pTemp = NULL;

   free(ppList);

   return OK;
}

int Add(LIST *pList, void *pvData){
   int iStatusCode = ERROR;
   NODE *pThis = CreateNode(pvData);

   if (pThis != NULL){

      /* If head is undefined (list is empty), set new node as head and tail */
      if(pList->pHead == NULL){
         pList->pHead = pThis;
         pList->pTail = pThis;

         iStatusCode = OK;

      } else {
         /*  Newnode next ptr to current head */
         pThis->pNext = pList->pHead;
         /*  set current head prev ptr to new node */
         pList->pHead->pPrev = pThis;
         /* Define new list head as new node */ 
         pList->pHead = pThis;
         iStatusCode = OK;
      }
   }

   return iStatusCode;
}

int Append(LIST *pList, void *pvData){
   int iStatusCode = ERROR;
   NODE *pThis = CreateNode(pvData);
   if (pThis != NULL) {
      if (pList->pHead == NULL) {
         /* For nodeless list(?) */ 
         pList->pHead = pThis;
      }
      /* Set tail node next ptr to new node */
      pList->pTail->pNext = pThis;

      /* Set new node as tail */
      pList->pTail = pThis;

      iStatusCode = OK;
   }

   return iStatusCode;
}

int Remove(LIST *pList, NODE *pToDelete){
   int iStatusCode = ERROR;
   
   /* Sets next node (after head) as new head the deleted node is the head */
   if(pToDelete == pList->pHead){
      pList->pHead = pList->pHead->pNext;
   }
   /* Sets next node (after head) as new head the deleted node is the head */
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

         /* Handle deletion */
         pPrevious->pNext = pNext;
         pNext->pPrev = pPrevious;

         iStatusCode = OK;
         break;
      }
      /* Check next node */
      pThis = pThis->pNext;
   }

   if (iStatusCode == OK) free (pToDelete);
   return iStatusCode;
}

NODE GetNode(LIST *pList){

   
}

void *GetData(){

}
