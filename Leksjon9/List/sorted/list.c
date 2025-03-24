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

LIST *CreateList(char *szKey, char cFlag, int iDataSize, ...){

   if(iDataSize > MAX_DATA){
      printf("ERROR: MAX_DATA exceeded."); 
      return NULL;
   }

   va_list vaData;
   LIST *pList;
   va_start(vaData, iDataSize);

   pList = (LIST *) malloc(sizeof(LIST));
   if(pList != NULL){

      pList->pszKey = (char*) malloc(MAX_KEY);
      if(pList->pszKey != NULL){
         strncpy(pList->pszKey, szKey, 31);
         pList->pszKey[31] = '\0';
      }


      if(cFlag == 'S'){
         pList->pszValue = (char*) malloc(MAX_DATA);
         char *inputStr = va_arg(vaData, char*);

         if(pList->pszValue != NULL){
            strncpy(pList->pszValue, inputStr, strlen(inputStr));
         }


      } else if(cFlag == 'I'){
         pList->pszValue = NULL;
         pList->iValue = va_arg(vaData, int);
      
      }  else {
         printf("ERROR! Invalid type flag.\n"); 
         va_end(vaData);
         return NULL;
      }

   }

   va_end(vaData);
   return pList;
}

int FreeList(LIST *pHead){
   if(pHead->pNext == NULL){
      free(pHead); 
      return 0;
   }

   LIST *pCurrent = NULL;   
   LIST *pNext = pHead->pNext;

   while(pNext != NULL){
      pCurrent = pNext;
      free(pNext->pszKey);

      if(pNext->pszValue != NULL){
         free(pNext->pszValue);
      }
      
      pNext = pCurrent->pNext;
      free(pCurrent);
   }

}

int InsertSorted(LIST *pHead, char *szKey, char cFlag, ...){
   va_list vaData; 
   LIST *pCurrent = pHead;
   LIST *pPrev = NULL;

   va_start(vaData, cFlag);
   LIST *pNewNode = CreateList(szKey, cFlag, MAX_DATA, vaData); 

   // Check if input is string or int

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
         if(pCurrent == pHead){
            pNewNode->pNext = pHead;
            pHead = pNewNode;
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
