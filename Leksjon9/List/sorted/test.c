#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(void){
   LIST *pHead = NULL; 

   pHead = CreateList("B", 'I', 205);

   InsertSorted(&pHead, "A", 'I', 521);

   InsertSorted(&pHead, "D", 'S', "Hello world!");

   InsertSorted(&pHead, "C", 'S', "MY beloved");

   InsertSorted(&pHead, "B", 'I', 42);

   InsertSorted(&pHead, "C", 'S', "MY aaa");
   
   PrintList(pHead);

   FreeList(&pHead);

   return 0;   
}
