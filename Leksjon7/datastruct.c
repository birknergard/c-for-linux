#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastruct.h"

/*
 *	NODE is a generic struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
NODE _NewNode(void *pData){
	NODE noNewNode;

	noNewNode.pData = pData;
	noNewNode.pNext = NULL;

	return noNewNode;
}

/*
 *	LIST struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
LIST NewList(void* pData){
	LIST liNewList;
	NODE noHead;
	noHead = _NewNode(pData);	

	liNewList.iLength = 1;
	liNewList.noHead = noHead;

	return liNewList;
}

void Push(LIST *liList, void *pData){
	NODE newNode;		
	newNode = _NewNode(pData); 
	newNode.pNext = &liList->noHead;

	++liList->iLength;	
	liList->noHead = newNode;
}

NODE *_GetNode(LIST *liList, int iIndex){
	int i;
	NODE *nopCurrent;
	nopCurrent = &liList->noHead;	

	for(i = 0; i < iIndex; i++){
		nopCurrent = nopCurrent->pNext;
	}

	return nopCurrent;
}

void *GetValue(LIST liList, int iIndex){
	int i;
	NODE *nopCurrent;
	nopCurrent = &liList.noHead;	

	for(i = 0; i < iIndex; i++){
		nopCurrent = nopCurrent->pNext;
	}

	return nopCurrent->pData;
}

int Pop(LIST *liList, int iIndex){
	NODE *node;
	int iLength = liList->iLength;

	if(iIndex >= iLength){
		printf("ERROR in LIST: index %d is out of bounds", iIndex);
		return 1;	
	}  	

	if(iIndex == 0 && liList->iLength == 1){
		free(liList->noHead);
		liList->noHead = NULL;
		liList->iLength = 0;	
		return 0;
	}

	node = _GetNode(liList, iIndex - 1);
	free(node);
	return 0;

}

/* For testing */
int main(void){
	printf("DEBUG1: Declaring LIST\n");
	LIST *liStart;
	int a,b,c,i;

	a = 1;
	b = 2;
	c = 3;

	liStart = (LIST*) malloc(sizeof(LIST));
	if(liStart == NULL)
		return 1;

	*liStart = NewList(&a);
	printf("First value: %d\n", *(int*)GetValue(*liStart, 0));

	Push(liStart, &b); 
	printf("Second value: %d\n", *(int*)GetValue(*liStart, 1));

	Push(liStart, &c); 
	printf("Third value: %d\n", *(int*)GetValue(*liStart, 2));

	free(liStart);

	return 0;
}
