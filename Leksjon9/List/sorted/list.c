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

Add a function Lookup() that looks up a key and returns the value.
How can you handle the two types, integer and string?

Add another function Delete() that deletes an element given the key.

Keep the list handling in one source file and the reading of the key/value
pair file in the main source file.
*/

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

      pList->pszKey = (char*) malloc(MAX_KEY);
      if(pList->pszKey != NULL){
         strncpy(pList->pszKey, szKey, 31);
         pList->pszKey[31] = '\0';
      }


      if(cFlag == 'S'){
         pList->pszValue = (char*) malloc(MAX_DATA);
         char *szInputStr = va_arg(vaData, char*);

         if(pList->pszValue != NULL){
            strncpy(pList->pszValue, szInputStr, (strlen(szInputStr) > MAX_DATA ? MAX_DATA : strlen(szInputStr)));
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
      printf("Freeing node with key %s. \n", pCurrent->pszKey);
      free(pCurrent->pszKey);

      if(pCurrent->pszValue != NULL){
         free(pCurrent->pszValue);
      }
      
      pTemp = pCurrent;
      pCurrent = pCurrent->pNext;
      free(pTemp);
   }

}

int InsertSorted(LIST **ppHead, char *szKey, char cFlag, ...){
   va_list vaData; 
   LIST *pCurrent = *ppHead;
   LIST *pPrev = NULL;
   LIST *pNewNode = NULL;

   va_start(vaData, cFlag);

   // Check for valid type flag
   if(cFlag == 'I'){
      int iInputValue = va_arg(vaData, int);
      pNewNode = CreateList(szKey, cFlag, iInputValue); 

   } else if(cFlag == 'S'){
      char *szInputValue = va_arg(vaData, char*);
      pNewNode = CreateList(szKey, cFlag, szInputValue); 

   } else {
      printf("Invalid type flag.\n");
      return 1;
   }


   while(pCurrent != NULL){
      if(strcmp(pNewNode->pszKey, pCurrent->pszKey) >= 0){
         // If higher value, go next, unless there is no null
         if(pCurrent->pNext == NULL){
            pCurrent->pNext = pNewNode;
            return 0;
         } 

         pPrev = pCurrent;
         pCurrent = pCurrent->pNext;       

      } else {
         // if pointing to head node
         if(pCurrent == *ppHead){
            pNewNode->pNext = *ppHead;
            *ppHead = pNewNode;
            return 0;
         }  

         // handle insert
         pPrev->pNext = pNewNode;
         pNewNode->pNext = pCurrent;
         return 0;
      }
   }
   va_end(vaData);
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
