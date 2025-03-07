#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastruct.h"

/*
 *	NODE is a generic struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
NODE *_NewNode(void *pData){
	NODE noNew, *nopNew; 


	nopNew->pData = pData;
	nopNew->pNext = NULL;

	nopNew = &noNew;
	return nopNew;
}

/*
 *	LIST struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
LIST NewList(void* pData){
	LIST liNew;
	NODE *noHead;
	noHead = _NewNode(pData);	

	liNew.iLength = 1;
	liNew.noHead = noHead;

	return liNew;
}

void Push(LIST *lip, void *pData){
	NODE *newNode;		
	newNode = _NewNode(pData); 

	newNode->pNext = lip->noHead;
	lip->noHead = newNode;

	++lip->iLength;	
}

NODE *_GetNode(LIST *lip, int iIndex){
	int i;
	NODE *nopCurrent;
	nopCurrent = lip->noHead;	

	for(i = 0; i < iIndex; i++){
		nopCurrent = nopCurrent->pNext;
	}

	return nopCurrent;
}

void *GetValue(LIST *lip, int iIndex){
	int i;
	NODE *nopCurrent;
	nopCurrent = lip->noHead;	

	for(i = 0; i < iIndex; i++){
		nopCurrent = nopCurrent->pNext;
	}

	return nopCurrent->pData;
}

int RemoveFirst(LIST *lip){
	if(lip->iLength == 1){
		lip->noHead->pNext = NULL;
		lip->noHead->pData = NULL;
		lip->iLength = 0;	
		return 0;
	}
	
	/* Sets head to adjacent node when removed */
	lip->noHead = lip->noHead->pNext;
	--lip->iLength;

	return 0;
}

int RemoveLast(LIST *lip){
	NODE *nopPenultimate;
	nopPenultimate = _GetNode(lip, lip->iLength - 1);
	nopPenultimate->pNext == NULL;	
	--lip->iLength;

	return 0;		
}


int Remove(LIST *lip, int iIndex){
	NODE *noAdjacent, *noRemoved;
	int *iLength;
	iLength = &lip->iLength;

	if(iIndex >= *iLength){
		printf("ERROR in LIST: index %d is out of bounds", iIndex);
		return 1;	
	}  	

	if(iIndex == 0){
		if(lip->iLength == 1){
			lip->noHead->pNext = NULL;
			lip->noHead->pData = NULL;
			*iLength = 0; 
			return 0;
		}
		
		/* Sets head to adjacent node when removed */
		lip->noHead = lip->noHead->pNext;
		lip->noHead->pNext = NULL;
		--*iLength;
		return 0;
	}

	if(iIndex == *iLength){
		noAdjacent = _GetNode(lip, *iLength - 1);
		noAdjacent->pNext == NULL;	
		--*iLength;

		return 0;		
	}

	noAdjacent = _GetNode(lip, iIndex - 1);
	noRemoved = _GetNode(lip, iIndex);
	
	noAdjacent->pNext = noRemoved->pNext;

	return 0;
}

/* For testing */
int main(void){
	printf("DEBUG1: Declaring LIST\n");
	LIST *liStart;
	int a,b,c,d,i;

	a = 1;
	b = 2;
	c = 3;
	d = 4;

	liStart = (LIST*) malloc(sizeof(LIST));
	if(liStart == NULL)
		return 1;

	*liStart = NewList(&a);

	Push(liStart, &b); 

	Push(liStart, &c); 

	Push(liStart, &d); 

	printf("First value: %d\n", *(int*)GetValue(liStart, 0));
	printf("Second value: %d\n", *(int*)GetValue(liStart, 1));
	printf("Third value: %d\n", *(int*)GetValue(liStart, 2));
	printf("Fourth value: %d\n", *(int*)GetValue(liStart, 3));

	printf("\n\n Popping first value.");
	RemoveFirst(liStart);

	printf("\n\n Current list:");
	for(i = 0; i < liStart->iLength; i++){
		printf(" %d", *(int*) GetValue(liStart, i));	
	}
	printf("\n");

	free(liStart);

	return 0;
}
