#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAX_BUFFER 256

int ParseInt(char *string){
	int len, i, j;
	len = strlen(string);

	i = 0;
	while(isspace(string[i]) == 0) i++;

	j = 0;
	if(string[i] == '-') i++; 

	do{
		if(string[i] == '\0') break;	
		if(isdigit(string[i]) == 0) i++;
		else return false;	
	} while(i < len);

	return true;
}

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



void PrintArray(int *iarr, int iLen){
	int i;
	printf("[");
	for(i = 0; i < iLen; i++){
		printf(" %d ", iarr[i]);	
	} 
	printf("]\n");
}

void PrintMatrix(int **matrix){
	int i, j;
	printf("\n");
	for(i = 0; i < 2; i++){
		for(j = 0; j < 3; j++){
			printf("%d ", matrix[i][j]);		
		}
		printf("\n");
	}

	/* Prints the last separately row for text formatting purposes */
	for(j = 0; j < 3; j++){
		printf("%d ", matrix[2][j]);	
	}

}

void PrintBot(BOT bot){
	PrintMatrix(bot.iaMatrix);
}

BOT CreateBot(int iSize){
	BOT bot;
	int **iaMatrix, i, j;
	int *iaFlat;
	iaFlat = (int *) malloc(sizeof(int) * 9);
	
	/* Allocating memory */
	iaMatrix = (int **) malloc(sizeof(int *) * 3);
	for(i = 0; i < 3; i++){
		iaMatrix[i] = (int *) malloc(sizeof(int) * 3);
	}

	/* 1 added to array for each size */
	for(i = 0; i < 9; i++){
		if(i < iSize){
			iaFlat[i] = 1;	
		} else {
			iaFlat[i] = 0;	
		}	
	}

	/* Scramble linear array so order is random */
	for(i = 0; i < 9; i++){
		int iRand = (rand()%8) + 1;
		Swap(&iaFlat[iRand], &iaFlat[8 - i]);
	}

	/* Convert scrambled array into matrix */
	for(i = 0; i < 3; ++i){
		for(j = 0; j < 3; j++){
			if(i == 1){
				iaMatrix[i][j] = iaFlat[j+3];

			} else if(i == 2){
				iaMatrix[i][j] = iaFlat[j+6];

			} else {
				iaMatrix[i][j] = iaFlat[j];
			}
		}
   	}

	free(iaFlat);

	bot.iaMatrix = iaMatrix;
	bot.iSum = iSize;

	return bot;  
}

void FreeBot(BOT bot){
	int i, j;
	for(i = 0; i < 3; i++){
		free(bot.iaMatrix[i]);	
	}
	free(bot.iaMatrix);
}

void FreeBots(BOT* bots, int iBotCount){
	int i, j;
	for(i = 0; i < iBotCount; i++){
		for(j = 0; j < 3; j++){
			free(bots[i].iaMatrix[j]);	
		}
		free(bots[i].iaMatrix);
	}
	free(bots);
}

bool RunLevel(int iBotCount, int iTime, int *ipKillCount){
	int iLifePoints, iCurrentBot, iBotsLeft, iRand, timeLeft, i;

	BOT *aBots;
	
	bool parsed, completed;
	char *buffer;
	int *pInput;

	time_t timestampBase, timestampCurrent;
	timestampBase = time(NULL);

	buffer = (char *) malloc(MAX_BUFFER);

	aBots = (BOT *) malloc(sizeof(BOT) * iBotCount);

	for(i = 0; i < iBotCount; i++){
		iRand = 1 + rand()%9;
		aBots[i] = CreateBot(iRand);
	}

	pInput = (int *) malloc(sizeof(int));

	iBotsLeft = iBotCount;

	iLifePoints = 20;
	iCurrentBot = 0;

	for(;;){
		system("clear");
		timestampCurrent = time(NULL);
		timeLeft = timestampCurrent - timestampBase;
		
		printf("Lifepoints: %d\n", iLifePoints);
		printf("Time left: %d\n",  (iTime - timeLeft));
		if(iTime - timeLeft <= 0){
			printf("You ran out of time.\n");	
			completed = false;
			break;
		}

		if(iBotsLeft == 0){
			printf("\nYou killed all the bots!\n");
			completed = true;
			break;	
		}
	
		printf("\n-Bot #%d/%d-\n", iCurrentBot + 1, iBotCount);
		PrintBot(aBots[iCurrentBot]);

		printf("-> Sum?: ");
		fgets(buffer, MAX_BUFFER, stdin);
		parsed = ParseInt(buffer);

		if(parsed == false){
			*pInput = -1;	
			printf("Invalid input. Sum has to be a positive integer.");
		} else {
			*pInput = atoi(buffer);	
		}

		if(*pInput == aBots[iCurrentBot].iSum){
			iBotsLeft--;
			*ipKillCount++;

			printf("Correct! You killed the bot. Next ...\n");
			iCurrentBot++;

		} else {
			iLifePoints -= 5;	
			if(iLifePoints == 0){
				completed = false;	
				break;
			}
			printf("Wrong. You lost 5 points. You have %d left.\n", iLifePoints);
		}
	}

	free(buffer);
	free(pInput);
	
	FreeBots(aBots, iBotCount);

	if(completed){
		return true;
	} else {
		return false;
	}

}

int main(int iArgc, char **apszArgV){
	srand(time(NULL));
	int iBotsPerLevel, iTime, iCompletedLevels;
	int *ipKills;
	bool completedLevel;
	char* buffer;

	buffer = (char *) malloc(MAX_BUFFER);
	ipKills = (int *) malloc(sizeof(int));

	*ipKills = 0;

	iBotsPerLevel = 3;
	iTime = 10;
	iCompletedLevels = 0;

	printf("Welcome to the game!\n\n Your objective is sum numbers to kill bots!\n");
	printf("To kill bots you add up all their numbers and write the sum in the terminal.\n");
	printf("If you miss, you lose 5 points. If you lose all your points you lose.\n");
	printf("\n\nPress enter any character to start ...\n");

	fgets(buffer, MAX_BUFFER, stdin);
	
	system("clear");


	for(;;){
		completedLevel = RunLevel(iBotsPerLevel, iTime, ipKills);
		if(completedLevel){
			printf("You completed the level!\n Enter any key to continue ...");
			fgets(buffer, MAX_BUFFER, stdin);
			iTime--;
			iBotsPerLevel++;
			system("clear");
		} else {
			printf(
				"You failed.\n\nStats\nLevels Completed: %d\nKills: %d",
				iCompletedLevels, *ipKills  
			);	
			break;
		}
	}
	
	free(buffer);
	free(ipKills);

	return 0;
}

