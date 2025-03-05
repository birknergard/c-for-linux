#ifndef DATASTRUCTS_H

#define DATASTRUCTS_H

typedef struct {
	int key;
	void *data;
	NODE *next;
	NODE *prev;
} NODE; 

typedef struct {
	NODE *head;
} LINKEDLIST;

typedef struct {
	int size;
	LINKEDLIST elements;
} LIST;

int push(void *pData);
NODE get(int iIndex);
int pop(int key);  
int size();

#endif
