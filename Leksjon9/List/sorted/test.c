#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "list.h"

#define MAX_LINE 512 

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

   
   fFileData = fopen("./main_text.txt", "r");
   if(fFileData == NULL) {
      printf("File not found.\n");
      return 1;
   }

   for(;;){
      // TODO: Store file by line in buffer (max linebuffer size) or until newline is found
      //
      pszDataBuffer = (char*) malloc(MAX_LINE);
      if(pszDataBuffer == NULL){
         return 1;     
      }

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
         *(pszDataBuffer + iBufferIndex) = cCurrent; 
         ++iBufferIndex;
      }

      if(feof(fFileData)){
         free(pszDataBuffer);
         pszDataBuffer = NULL;
         break;  
      }

      // NULL TERMINATION
      pszDataBuffer[iBufferIndex] = '\0';

      // Defining limits for splitting databuffer into key and value
      int iValueStart = 0, iValueEnd = 0; 
      int iKeyStart = 0, iKeyEnd = 0; 
      int i, iEntryDataLength;
      

      for(i = 0; i < iBufferIndex; i++){
         if(pszDataBuffer[i + 1] == '=' && i < iBufferIndex){
            iKeyEnd = i;
            iValueStart = i+2;
         }
      }

      printf("bufferindex %d", iBufferIndex);

      iValueEnd = iBufferIndex - 1; 

      // Check for datatype, omit first and last index (to remove "") if string
      char cDataTypeFlag;
      if(pszDataBuffer[iValueStart] == '\"'){
         cDataTypeFlag = 'S';
         ++iValueStart;
         --iValueEnd;

      } else if(isdigit(pszDataBuffer[iValueStart])){
         cDataTypeFlag = 'I';
          
      } else {
         cDataTypeFlag = 'x';
      }

      pszEntryKey = (char *) malloc(iKeyEnd + 2);

      iEntryDataLength = iValueEnd - iValueStart; 

      //printf("Data Length %d - %s", iValueEnd - iValueStart + 1, pszDataBuffer);
      pszEntryData = (char *) malloc(iEntryDataLength + 2);

      // Parsing line into data fields (Key and value)
      strncpy(pszEntryKey, pszDataBuffer, iKeyEnd + 1);
      *(pszEntryKey + iKeyEnd + 1) = '\0';

      char *pszData = pszDataBuffer + iValueStart;

      strncpy(pszEntryData, pszData, iEntryDataLength + 1);
      *(pszEntryData + (iValueEnd - iValueStart) + 1) = '\0'; 

      pszData = NULL;

      printf("DEBUG: %s ", pszEntryKey);
      printf("-- %s\n", pszEntryData);


      // Checking first index to determine datatype
      if(pEntryList == NULL){
         if(cDataTypeFlag == 'I'){
            pEntryList = CreateList(pszEntryKey, 'I', atoi(pszEntryData));
         } else {
            pEntryList = CreateList(pszEntryKey, cDataTypeFlag, pszEntryData); 
         }
      } else {
         if(cDataTypeFlag == 'I'){
            InsertSorted(&pEntryList, pszEntryKey, 'I', atoi(pszEntryData));
         } else {
            InsertSorted(&pEntryList, pszEntryKey, cDataTypeFlag, pszEntryData); 
         }
      }

      free(pszEntryKey);
      pszEntryKey = NULL;

      free(pszEntryData);
      pszEntryData = NULL;

      free(pszDataBuffer);
      pszDataBuffer = NULL;
   }

   PrintList(pEntryList);

   fclose(fFileData);
   fFileData = NULL;

   FreeList(&pEntryList);
   pEntryList = NULL;

   return 0;   
}
