#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

/*
 *	NODE is a generic struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
NODE *_NewNode(void *p){
	NODE *nopNew; 

	nopNew = (NODE*) malloc(sizeof(NODE));

	nopNew->pData = p;
	nopNew->pNext = NULL;

	return nopNew;
}

/*
 *	LIST struct which can hold a pointer to any data,
 *	as well as a pointer to the "next" node.
 * */
LIST *NewList(){
	LIST *liNew;
	liNew = (LIST*) malloc(sizeof(LIST));

	liNew->iLength = 0;
	liNew->noHead = NULL;

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

int FreeList(LIST *lip){
	/* for tracking current node */
	if(lip == NULL)	return 1;

	if(lip->noHead == NULL){
		free(lip);	
	}

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

	if(lip->iLength == 0){
		lip->noHead = newNode;	
		lip->iLength++;
		return;
	}

	newNode->pNext = lip->noHead;
	lip->noHead = newNode;
	lip->iLength++;	
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
	NODE *noOldHead;

	/*TODO: Make list be emptyable, list can be initialized as empty but still take values.*/
	if(lip->iLength == 0){
		printf("Cant remove element on empty list.\n");
		return 1;
	}

	if(lip->iLength == 1){
		lip->noHead = NULL;	
		lip->iLength = 0;
		return 0;
	}

	/* Holds the current head */
	noOldHead = lip->noHead;

	/* Sets head adress to second node */
	lip->noHead = noOldHead->pNext;

	/* Frees the previous head adress */
	_FreeNode(noOldHead);

	/* Decreases list size */
	lip->iLength--;

	return 0;
}

int RemoveLast(LIST *lip){
	int i;
	NODE *nopOldTail, *nopNewTail;

	if(lip->iLength == 0)
		return 1;

	if(lip->iLength == 1){
		lip->noHead = NULL;
		lip->iLength = 0;
		return 0;
	} 

	nopNewTail = _GetNode(lip, lip->iLength - 2);
	nopOldTail = nopNewTail->pNext; 

	_FreeNode(nopOldTail);
	nopNewTail->pNext = NULL;	

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
	int **ip, i;

	liStart = NewList();
	if(liStart == NULL){
		puts("DEBUG: liStart is NULL");
		return 1;
	}
		
	
	ip = (int**) malloc(sizeof(long*) * 100);
	for(i = 0; i < 100; i++){
		ip[i] = (int*) malloc(sizeof(int));
		*ip[i] = i; 
	}

	for(i = 0; i < 100; i++){
		Push(liStart, ip[i]);	
	}


	printf("\n\n Current list (%d):", liStart->iLength);
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

	printf("\n Popping last value.");
	RemoveLast(liStart);
	printf("\n\n Current list:");
	for(i = 0; i < liStart->iLength; i++){
		printf(" %d", *(int*) GetValue(liStart, i));	
	}
	printf("\n");

	FreeList(liStart);
	free(ip);

	return 0;
}
