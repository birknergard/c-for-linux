// ex3.c: Lession 7, exercise 3
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static void PrintList (LIST *pList);

int main (void)
{
   LIST *pList = (LIST*) malloc(sizeof(LIST));
   NODE *pThis = NULL;
   int iRc = OK;

   char *apszStrings[] = {"String number 1", "Second string", "Third string", "String number 4", NULL};
   char *pszFifth = "The 5th Element";

   for (int i = 0; apszStrings[i]; i++) {
      iRc = InsertInList (pList, apszStrings[i], strlen(apszStrings[i])+1);
      if (iRc != OK) break;
   }

   if (iRc != OK) {
      printf ("Something went wrong.\n");
      return 1;
   }

   PrintList(pList);
   iRc = AddToList (pList, pszFifth, strlen(pszFifth) + 1);

   if (iRc != OK) {
      printf ("Something went wrong.\n");
      return 1;
   }

   puts("Baselist");
   PrintList(pList);

   // Pick out the 3rd element in the list:
   pThis = pList->pHead;
   for (int i = 0; pThis != NULL && i < 2; i++) {
      pThis = pThis->pNext;
   }

   // And remove it:
   if (pThis != NULL) {
      iRc = RemoveFromList (pList, pThis);
   }

   if (iRc != OK) {
      printf ("Something went wrong.\n");
      return 1;
   }

   PrintList (pList);

   // Remove first element in list
   iRc = RemoveFromList (pList, pList->pHead);
   if (iRc == OK) {
      PrintList (pList);
   }

   free(pList);

}

static void PrintList (LIST *pList)
{
   NODE *pThis = pList->pHead;
   int i = 0;
   while (pThis != NULL) {
      printf ("%d: %s\n", ++i, pThis->byBuf);
      pThis = pThis->pNext;
   }
   printf ("\n");
}

