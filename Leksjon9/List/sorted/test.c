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
   LIST *pFileDataList = NULL;
   char *pszDataBuffer = NULL, cCurrent;
   FILE *fFileData;
   int iBufferIndex, lFileSize;


   pszDataBuffer = (char*) malloc(MAX_LINE);
   if(pszDataBuffer == NULL){
      return 1;     
   }
   
   fFileData = fopen("./main_text.txt", "r");
   if(fFileData == NULL) {
      printf("File not found.\n");
      return 1;
   }

   // TODO: Store file by line in buffer (max linebuffer size) or until newline is found
   for(;;){

      if(feof(fFileData)){
         break;  
      }

      iBufferIndex = 0;
      while(iBufferIndex < MAX_LINE){
         cCurrent = fgetc(fFileData);      

         if(cCurrent == '\n')
            break;

         if(cCurrent == 0)
            break;

         // raw indexing for flex
         *(pszDataBuffer + (iBufferIndex * sizeof(char))) = cCurrent; 

         ++iBufferIndex;
      }
      pszDataBuffer[iBufferIndex] = '\0';
      printf("Line - %s\n", pszDataBuffer);

   }

   fclose(fFileData);
   fFileData = NULL;

   free(pszDataBuffer);
   pszDataBuffer = NULL;
   FreeList(&pFileDataList);
   pFileDataList = NULL;

   return 0;   
}
