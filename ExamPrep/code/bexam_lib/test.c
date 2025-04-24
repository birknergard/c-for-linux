#include <stdio.h>

#include "debug.h"
#include "linked_list.h"
#include "menu.h"

int main(void){
	printf("Ran test.\n");
	int iNums[5], i, a, b, c;

	printf("Creating values\n");
	int *pa, *pb, *pc;
	a = 1;
	b = 2;
	c = 3;

	pa = &a;
	pb = &b;
	pc = &c;

	printf("Creating List\n");
	LIST *liTestList; 
	liTestList = CreateList();  

	printf("Adding to list\n");
	Add(liTestList, (void *) pa);
	Add(liTestList, (void *) pb);
	Add(liTestList, (void *) pc);

	printf("Destroying\n");
	DestroyList(&liTestList);


	return OK;
}

