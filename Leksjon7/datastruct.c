#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastruct.h"

/*
 *	NODE is a generic struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
NODE *_NewNode(void *pData){
	NODE *nopNew; 
	nopNew = (NODE*) malloc(sizeof(NODE));

	nopNew->pData = pData;
	nopNew->pNext = NULL;

	return nopNew;
}

/*
 *	LIST struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
LIST *NewList(void* pData){
	LIST *liNew;
	liNew = (LIST*) malloc(sizeof(LIST));

	NODE *noHead;
	noHead = _NewNode(pData);	

	liNew->iLength = 1;
	liNew->noHead = noHead;

	return liNew;
}

int _FreeNode(NODE *no){
	if(no == NULL){
		puts("Cannot free null pointer.");	
		return 1;
	}

	free(no->pData);
	free(no);
}

int _FreeList(LIST *lip){
	/* for tracking current node */
	if(lip == NULL)	return 1;

	NODE *noCurrent, *noNext;
	int i;

	noCurrent == lip->noHead;

	while(noCurrent != NULL){
		noNext = noCurrent->pNext;
		_FreeNode(noCurrent);
		noCurrent = noNext;
	}

	free(lip);
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
	NODE *noCurrentHead, *noNewHead;

	if(lip->iLength == 1){
		lip->noHead == NULL;
		lip->iLength = 0;	
		return 0;
	}

	/* Holds the current head */
	noCurrentHead = lip->noHead;

	/* Holds the new head */
	noNewHead = lip->noHead->pNext;
	
	/* Sets head adress to second node */
	lip->noHead = noNewHead;

	/* Deletes the previous head adress */
	_FreeNode(noCurrentHead);



	/* Decreases list size */
	lip->iLength--;

	return 0;
}

int RemoveLast(LIST *lip){
	int i;
	NODE *nopPenultimate, *nopTail;

	if(lip->iLength == 0)
		return 1;

	if(lip->iLength == 1){
		lip->noHead == NULL;
		return 0;
	} 

	nopPenultimate = _GetNode(lip, lip->iLength - 1);
	nopTail = nopPenultimate->pNext; 

	_FreeNode(nopTail);
	nopPenultimate->pNext = NULL;	

	lip->iLength--;

	return 0;		
}

int DeleteList(LIST *liList){
	int i;
	NODE *noCurrent, *noNext;
	noCurrent = liList->noHead;

	/* Freeing each node from start to end */
	while(noCurrent->pNext != NULL){
		noNext = noCurrent->pNext;
		free(noCurrent->pNext);
		free(noCurrent->pData);
	}
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
	int a,b,c,d,e,i;

	a = 1;
	b = 2;

	liStart = NewList(&a);
	if(liStart == NULL){
		puts("DEBUG: liStart is NULL");
		return 1;
	}

	Push(liStart, &b); 

	printf("\n\n Current list:");
	for(i = 0; i < liStart->iLength; i++){
		printf(" %d", *(int*) GetValue(liStart, i));	
	}
	printf("\n");


	printf("\n\n Popping first value.");
	RemoveFirst(liStart);

	printf("\n\n Current list:");
	for(i = 0; i < liStart->iLength; i++){
		printf(" %d", *(int*) GetValue(liStart, i));	
	}
	printf("\n");

	RemoveLast(liStart);
	printf("\n\n Current list:");
	for(i = 0; i < liStart->iLength; i++){
		printf(" %d", *(int*) GetValue(liStart, i));	
	}
	printf("\n");

	_FreeList(liStart);

	return 0;
}
