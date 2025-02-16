#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int **iarrRender;
	int iSum;
} BOT;

BOT CreateBot(int size){
	int **iArr, i;
	
	/* Allocating memory */
	iArr = (int **) malloc(sizeof(int *) * 3);
	for(i = 0; i < 3; i++){
		iArr[i] = (int *) malloc(sizeof(int) * 3);
	}

	if(size < 5){
		
	} else {
		
	}

	BOT bot;
	bot.iarrRender = iArr;
	bot.iSum = size;

	return bot;  
}

int main(void){
	return 0;
}

