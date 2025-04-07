#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "list.h"

LIST *CreateList(char *szKey, char cFlag, ...){

   va_list vaData;
   LIST *pList = NULL;

   va_start(vaData, cFlag);

   pList = (LIST *) malloc(sizeof(LIST));
   if(pList != NULL){
      
      pList->pNext = NULL;
      pList->pszKey = (char*) malloc(MAX_KEY);

      if(pList->pszKey != NULL){
         strncpy(pList->pszKey, szKey, 31);
         pList->pszKey[31] = '\0';
      }


      if(cFlag == 'S'){
         pList->pszValue = (char*) malloc(MAX_DATA);
         char *szInputStr = va_arg(vaData, char*);
         
         if(pList->pszValue != NULL){
            strncpy(pList->pszValue, szInputStr, MAX_DATA);
         }


      } else if(cFlag == 'I'){
         int iValue = va_arg(vaData, int);
         pList->pszValue = NULL;
         pList->iValue = iValue;
      
      }  else {
         printf("ERROR! Invalid type flag.\n"); 
         va_end(vaData);
         return NULL;
      }

   }

   va_end(vaData);
   return pList;
}

int FreeList(LIST **ppHead){

   LIST *pCurrent = *ppHead;   
   LIST *pTemp = NULL;

   while(pCurrent != NULL){
      //printf("Freeing node with key %s. \n", pCurrent->pszKey);
      free(pCurrent->pszKey);
      pCurrent->pszKey = NULL;

      if(pCurrent->pszValue != NULL){
         free(pCurrent->pszValue);
         pCurrent->pszValue = NULL;
      }
      
      pTemp = pCurrent;
      pCurrent = pCurrent->pNext;
      free(pTemp);
   }

   pCurrent = NULL;
   pTemp = NULL;
}

int InsertSorted(LIST **ppHead, char *szKey, char cFlag, ...){
   va_list vaData; 
   LIST *pCurrent = *ppHead;
   LIST *pPrev = NULL;
   LIST *pNewNode = NULL;

   va_start(vaData, cFlag);

   // TODO: Make keys unique

   // Check for valid type flag
   if(cFlag == 'I'){
      int iInputValue = va_arg(vaData, int);
      pNewNode = CreateList(szKey, cFlag, iInputValue); 

   } else if(cFlag == 'S'){
      char *szInputValue = va_arg(vaData, char*);
      pNewNode = CreateList(szKey, cFlag, szInputValue); 

   } else {
      printf("Invalid type flag. Needs to be either \"I\" or \"S\"\n");
      return 1;
   }


   int iCompareResult;
   while(pCurrent != NULL){
      iCompareResult = strcmp(pNewNode->pszKey, pCurrent->pszKey);

      // Matching keys
      if(iCompareResult == 0){
         printf("ERROR: An entry with this key(\"%s\") already exists in the list.\n", pCurrent->pszKey);
         FreeList(&pNewNode);
         return 1;
      }

      // Key is greater
      if(iCompareResult > 0){
         // If higher value, go next, unless there is no null
         if(pCurrent->pNext == NULL){
            pCurrent->pNext = pNewNode;
            break;
         } 

         pPrev = pCurrent;
         pCurrent = pCurrent->pNext;       

      // Key is smaller, element is insert before the next key 
      } else {

         // reassign head if current node is head
         if(pCurrent == *ppHead){
            pNewNode->pNext = *ppHead;
            *ppHead = pNewNode;
            break;
         }  

         // handle insert
         pPrev->pNext = pNewNode;
         pNewNode->pNext = pCurrent;
         break;
      }
   }

   va_end(vaData);
   return 0;
}

 
void *Lookup(LIST *pHead, char *szKey){

   // TODO: Handle output of multiple types (macros?)
   LIST *pCurrent = pHead; 
   while(pCurrent != NULL){
      if(strcmp(pCurrent->pszKey, szKey) == 0){
         if(pCurrent->pszValue == NULL){
            return &pCurrent->iValue; 
         } else {
            return pCurrent->pszValue; 
         }
      } 
   
      pCurrent = pCurrent->pNext;
   }
}

int Delete(LIST **pHead, char *szKey){
   LIST *pCurrent = *pHead;

   // pointer to target for deletion
   LIST *pTarget = NULL;

   if(strcmp(pCurrent->pszKey, szKey) == 0){
      // assigning target
      pTarget = pCurrent;

      // Reassigning head node pointer
      *pHead = pCurrent->pNext;
   }

   if(pTarget == NULL){
      for(;;){

         if(pCurrent == NULL) {
            printf("Could not find node with key %s\n", szKey);
            return 1; 
         }

         // Matching node is found
         if(strcmp(pCurrent->pNext->pszKey, szKey) == 0){
            pTarget = pCurrent->pNext;

            // Reassigning previous node pointer to omit target
            pCurrent->pNext = pTarget->pNext;
            break;
         } 

         pCurrent = pCurrent->pNext;
      }
   }

   // deleting node
   free(pTarget->pszKey);

   if(pTarget->pszValue != NULL)
      free(pTarget->pszValue);

   free(pTarget);
   pTarget = NULL;
   pCurrent = NULL;
   return 0;
}

void PrintList (LIST *pList){
   LIST *pThis = pList;
   int i = 0;
   while (pThis != NULL) {
      if(pThis->pszValue == NULL){
         printf ("%d: %s - %d\n", ++i, pThis->pszKey, pThis->iValue);
      } else {
         printf ("%d: %s - %s\n", ++i, pThis->pszKey, pThis->pszValue);
      }
      pThis = pThis->pNext;
   }
   printf ("\n");
}
