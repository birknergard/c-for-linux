#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "list.h"

#define MAX_LINE 256

int main(void){

   // Testing of sortedlist
   LIST *pHead = NULL; 
   void *pLookupValue = (void*) malloc(MAX_DATA);

   pHead = CreateList("B", 'I', 205);

   InsertSorted(&pHead, "A", 'I', 521);
   InsertSorted(&pHead, "D", 'S', "Hello world!");
   InsertSorted(&pHead, "Daaaa", 'x', "Hello world!");
   InsertSorted(&pHead, "C", 'S', "MY beloved");
   InsertSorted(&pHead, "B", 'I', 42);
   InsertSorted(&pHead, "C", 'S', "MY aaa");
   
   PrintList(pHead);

   memcpy(pLookupValue, Lookup(pHead, "A"), sizeof(int));
   printf("Int value from lookup = %d\n", *(int*)pLookupValue);

   memcpy(pLookupValue, Lookup(pHead, "D"), MAX_DATA);
   printf("str value from lookup = %s\n", (char*) pLookupValue);

   free(pLookupValue);

   Delete(&pHead, "A");
   Delete(&pHead, "D");

   PrintList(pHead);

   FreeList(&pHead);

   // Main program
   printf("\n\nSTARTING MAIN PROGRAM\n\n");
   LIST *pEntryList = NULL;
   char *pszDataBuffer = NULL; 
   char *pszEntryData = NULL, *pszEntryKey = NULL; 
   char cCurrent, L;
   FILE *fFileData;
   int iBufferIndex, lFileSize, iEntryData;


   pszDataBuffer = (char*) malloc(MAX_LINE);
   if(pszDataBuffer == NULL){
      return 1;     
   }
   
   fFileData = fopen("./main_text.txt", "r");
   if(fFileData == NULL) {
      printf("File not found.\n");
      return 1;
   }

   for(;;){
      // TODO: Store file by line in buffer (max linebuffer size) or until newline is found
      iBufferIndex = 0;
      while(iBufferIndex < MAX_LINE){
         cCurrent = fgetc(fFileData);      
         
         if(feof(fFileData)){
            break;  
         }

         if(cCurrent == '\n')
            break;

         if(cCurrent == 0)
            break;

         // raw indexing to flex
         *(pszDataBuffer + (iBufferIndex * sizeof(char))) = cCurrent; 

         ++iBufferIndex;
      }

      if(feof(fFileData)){
         break;  
      }

      // NULL TERMINATION
      pszDataBuffer[iBufferIndex] = '\0';

      printf("\nParsing data.\n");
      // Parsing string into LIST structure  
      
      // Defining limits for splitting databuffer into key and value
      int iValueStart, iValueEnd; 
      int iKeyStart = 0, iKeyEnd;

      iValueEnd = strlen(pszDataBuffer) - 1;

      for(iKeyEnd = 0; iKeyEnd < iValueEnd + 1; iKeyEnd++){
         if(pszDataBuffer[iKeyEnd + 1] == '='){
            break; 
         }
      }

      iValueStart = iKeyEnd + 2;
      int iDatasize = iValueEnd - iValueStart;

      pszEntryKey = (char *) malloc((sizeof(char) * iKeyEnd) + 2);
      pszEntryData = (char *) malloc((sizeof(char) * iDatasize) + 2);

      // Parsing line into data fields (Key and value)
      strncpy(pszEntryKey, pszDataBuffer, iKeyEnd + 1);
      pszEntryKey[iKeyEnd + 1] = '\0';

      strncpy(pszEntryData, pszDataBuffer + (iValueStart * sizeof(char)), iValueEnd + 1);
      pszEntryData[iValueEnd + 1] = '\0'; 

      printf("DEBUG: %s ", pszEntryKey, sizeof(pszEntryKey));
      printf("-- %s\n", pszEntryData, sizeof(pszEntryData));

      free(pszEntryKey);
      pszEntryKey = NULL;
      free(pszEntryData);
      pszEntryData = NULL;
   }

   fclose(fFileData);
   fFileData = NULL;

   free(pszDataBuffer);
   pszDataBuffer = NULL;
   FreeList(&pEntryList);
   pEntryList = NULL;

   return 0;   
}
