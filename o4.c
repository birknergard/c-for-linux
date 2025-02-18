#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

#pragma pack (1)
typedef struct {
	int **iaMatrix;
	int iSum;
} BOT;
#pragma pack ()

void FreeBot(BOT bot){
	int i, j;
	for(i = 0; i < 3; i++){
		free(bot.iaMatrix[i]);	
	}
	free(bot.iaMatrix);
}

void PrintArray(int *iarr, int iLen){
	int i;
	printf("[");
	for(i = 0; i < iLen; ++i){
		printf(" %d ", iarr[i]);	
	} 
	printf("]\n");
}

void PrintMatrix(int **matrix){
	printf("printing bot: \n");
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("%d ", matrix[i][j]);		
		}
		printf("\n");
	}
	printf("\n");
}

void PrintBot(BOT bot){
	PrintMatrix(bot.iaMatrix);
}

BOT CreateBot(int iSize){
	printf("Creating bot.\n");
	BOT bot;
	int **iaMatrix, i, j;
	int *iaFlat;
	iaFlat = (int *) malloc(sizeof(int) * 9);
	
	/* Allocating memory */
	iaMatrix = (int **) malloc(sizeof(int *) * 3);
	for(i = 0; i < 3; ++i){
		iaMatrix[i] = (int *) malloc(sizeof(int) * 3);
	}

	// flat array where random indices are incremented 1s in linear order
	for(i = 0; i < 9; ++i){
		if(i <= iSize - 1){
			iaFlat[i] = 1;	
		} else {
			iaFlat[i] = 0;	
		}	
	}

	/*
	printf("DEBUG: Generating linear array: Creating bot.\n");
	PrintArray(iaFlat, 9);
	*/	

	/* Scramble linear array so order is random */
	for(i = 0; i < 9; ++i){
		int iRand = rand()%8;
		printf("random index:%d\n", iRand);
		Swap(&iaFlat[iRand], &iaFlat[8 - i]);
	}
	/*
	printf("DEBUG: Scrambling linear array: Creating bot.\n");
	PrintArray(iaFlat, 9);
	*/
	/* Convert scrambled array into matrix */
	for(i = 0; i < 3; ++i){
		for(j = 0; j < 3; ++j){
			if(i == 1){
				iaMatrix[i][j] = iaFlat[j+3];

			} else if(i == 2){
				iaMatrix[i][j] = iaFlat[j+6];

			} else {
				iaMatrix[i][j] = iaFlat[j];
			}
		}
   	}

	/*
	printf("DEBUG: Converting linear into matrix : Creating bot.\n");
	PrintMatrix(iaMatrix);
	*/	

	bot.iaMatrix = iaMatrix;
	bot.iSum = iSize;

	return bot;  
}

void FreeBots(BOT* bots, int iBotCount){
	int i;
	for(i = 0; i < iBotCount; ++i){
		FreeBot(bots[i]);
	}
	free(bots);
}

void StartLevel(int iBotCount, int iTime){
	BOT *aBots;
	int i, iRand;
	aBots = (BOT *) malloc(sizeof(BOT) * iBotCount);

	for(i = 0; i < iBotCount; ++i){
		iRand = rand()%9;
		aBots[i] = CreateBot(iRand);
	}


	
	FreeBots(aBots, iBotCount);
}


int main(int iArgc, char **apszArgV){
	srand(time(NULL));
	int iTime;

	iTime = 10;

	StartLevel(3, iTime);

	return 0;
}

