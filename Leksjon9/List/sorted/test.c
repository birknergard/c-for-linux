#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(void){
   LIST *pHead = NULL; 

   pHead = CreateList("A", 'I', sizeof(int), 205);

   PrintList(pHead);

   InsertSorted(pHead, "B", 'I', sizeof(int), 521);

   PrintList(pHead);

   InsertSorted(pHead, "D", 'I', sizeof(int), 123);

   InsertSorted(pHead, "C", 'I', sizeof(int), 456);
   
   PrintList(pHead);

   FreeList(pHead);

   return 0;   
}
