#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

static NODE *CreateNode(const void *pvData){
   NODE *pNode;

   pNode = (NODE *) malloc(sizeof(NODE));
   if (pNode == NULL) {
      berror("failed malloc in CreateNode()");
      return NULL;
   }

   memset (pNode, 0, sizeof(NODE));

   pNode->pvData = (void *) malloc(sizeof(void *));
   if(pNode->pvData == NULL){
      berror("Failed malloc in CreateNode() struct pvData\n");
      free(pNode);
      pNode = NULL;
      return NULL;
   }

   pNode->iSize = sizeof(*pvData);
   memcpy(pNode->pvData, pvData, sizeof(void *));

   return pNode;
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

   return pList;
}

int DestroyList(LIST **ppList){
   NODE *pCurrent = (*ppList)->pHead;   
   NODE *pTemp = NULL;

   while(pCurrent != NULL){
      if(pCurrent->pvData != NULL){
         printf("Freeing node data\n");
         free(pCurrent->pvData);
         pCurrent->pvData = NULL;
      }
      
      pTemp = pCurrent;
      pCurrent = pCurrent->pNext;
      printf("->Freeing node\n");
      free(pTemp);
   }

   pCurrent = NULL;
   pTemp = NULL;

   (*ppList)->pTail = NULL; 
   (*ppList)->pHead = NULL; 

   printf("Freeing list.\n");
   free(*ppList);

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

int Remove(LIST *pList, NODE pToDelete){
   int iStatusCode = ERROR;
   
   /* Sets next node (after head) as new head if the deleted node is the head */
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
      if (*pThis == pToDelete) {
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

   pThis = NULL;
   pPrevious = NULL;
   pNext = NULL;

   if (iStatusCode == OK) free (pToDelete);
   return iStatusCode;
}

NODE GetNode(LIST *pList){


   
}

void *GetData(){

}
