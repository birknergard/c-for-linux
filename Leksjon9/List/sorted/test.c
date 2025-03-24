#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(void){
   LIST *pHead = NULL; 

   pHead = CreateList("B", 'I', 205);

   InsertSorted(pHead, "A", 'I', 521);

   InsertSorted(pHead, "D", 'S', "Hello world!");

   InsertSorted(pHead, "C", 'S', "MY beloved");

   InsertSorted(pHead, "C", 'I', 42);
   
   PrintList(pHead);

   FreeList(pHead);

   return 0;   
}
