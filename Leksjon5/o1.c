#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int InsertInt(
	int *iArr,
   	int iVal,
	int iAtRow,
   	int iColCount
);
void BubbleSort(int *iArr, int iArrLen);
void Swap(int *ipA, int *ipB);
void PrintTable(int **iArr, int iRows, int iCols);

int TableInsert(
	int **iArr,
	int iRows,
	int iCols,
	int iInput
){

	int i, bInserted;

	srand(time(NULL));
	int iRandomRow = rand() % iRows;
	printf("Randomly assigned row (ceiling: %d): %d\n", iRows-1, iRandomRow);

	/* Initial insert */
	bInserted = InsertInt(iArr[iRandomRow], iInput, iRandomRow, iCols);

	/* Linear insert (if initial fails) */
	if(bInserted == 1){
		printf("Data was not inserted at random row [%d]\n --> Inserting linearly ...\n", iRandomRow);
		for(i = 0; i < iRows; i++){

			/* Row was on initial random insert attempt, so we skip it */
			if(i == iRandomRow){
				continue;
			}


			bInserted = InsertInt(iArr[i], iInput, i, iCols);	
			if(bInserted == 0){
				printf("--> Inserted at available space after failed random assignment.\n");
				break;
			}
		}	

		/* Checking the very last insert attempt. Since  */ 
		if(bInserted == 1){
			printf("Array is full.\n");	
			return 1;
		}

		if(bInserted == 0){
			return 0;
		}
	} 

}


int main(int iArgC, char **apszArgV){

	int **iArr;
	int *ipRows, *ipCols, *ipIn; 
	int bInserted;
	int i, j;

	ipRows = (int *) malloc(sizeof(int));
	ipCols = (int *) malloc(sizeof(int));

	printf("\nEnter rows: ");
	scanf("%d", ipRows);
	printf("\nEnter columns: ");
	scanf("%d", ipCols);
	
	printf("rows: %d - cols: %d\n", *ipRows, *ipCols);

	iArr = (int **) malloc(*ipRows * sizeof(int *));
	for(i = 0; i < *ipRows; ++i){
		iArr[i] = (int *) malloc(*ipCols * sizeof(int));
		for(j = 0; j < *ipCols; j++){
			iArr[i][j] = 0;	
		}
	}

	ipIn = (int *) malloc(sizeof(int));
	int bIsFull = 1;
	while(1){
		printf("\nEnter a non-zero positive integer.\n Num: ");
		scanf("%d", ipIn);	
			
		if(*ipIn <= 0){
			while(*ipIn <= 0){
				printf("\nNot a non-zero positive integer. Try again.\n Num:");
				scanf("%d", ipIn);	
			}
		}

		bIsFull = TableInsert(iArr, *ipRows, *ipCols, *ipIn);
		if(bIsFull == 1){
			break;	
		}
		printf("\nCurrent Table:\n");
		PrintTable(iArr, *ipRows, *ipCols);
	}
	free(ipIn);
	ipIn = NULL;

	printf("Table is full!\n\nUnsorted Table\n");
	PrintTable(iArr, *ipRows, *ipCols);

	for(i = 0; i < *ipRows; ++i){
		BubbleSort(iArr[i], *ipCols);	
	}

	printf("\nSorted Table\n");
	PrintTable(iArr, *ipRows, *ipCols);

	/* Freeing pointers and arrays */
	for(i = 0; i < *ipRows; ++i){
		free(iArr[i]);	
		iArr[i] = NULL;
	}
	printf("Freed columns in array\n");

	free(iArr);
	iArr = NULL;
	printf("Freed rows in array\n");

	free(ipRows);
	printf("Freed row pointer\n");

	free(ipCols);
	printf("Freed col pointer\n");


	return 0;
} 

int InsertInt(
	int *iArr,
   	int iVal,
	int iAtRow,
   	int iColCount
){
	int result, i;

	for(i = 0; i < iColCount; i++){
		if(iArr[i] != 0 && i == iColCount -1){ /* check over this again */
			return 1;	
			
		}
		if(iArr[i] == 0){
			iArr[i] = iVal;
			printf("%d was inserted at index [%d][%d]\n", iVal, iAtRow, i);
			return 0;
		}
	}
}

void BubbleSort(int *iArr, int iArrLen){
	int iIterations, i;
	int *ipA = NULL;
	int *ipB = NULL;

	for(;;){
		iIterations = 0;

		for(i = 1; i < iArrLen; ++i){

			ipA = &iArr[i - 1];
			ipB = &iArr[i];
			if(*ipA < *ipB){
				Swap(ipA, ipB);	
			}
		}	

		if(iIterations == 0) break;
	}
}

void Swap(int *ipA, int *ipB){
	int temp;
	temp = *ipA;
	*ipA = *ipB;
	*ipB = temp;	
}

void PrintTable(int **iArr, int iRows, int iCols){
	int i, j;
	for(i = 0; i < iRows; i++){
		printf("%d: [", i);
		for(j = 0; j < iCols; j++){
			printf(" %d ", iArr[i][j]);	
		}
		printf("]\n");
	}	
}
/*
Exercise 1:
Consider the following - You have a multidimensional array of size [r][c] -
r rows and c cols. (r,c) are provided at run-time. Example: (r=10,c=5)(r=5,c=5)
Take input from user and store each integer into a random row. Store it
in another row if the row is already full. Then print the whole array in a nice formatting.
Then write a function that takes a pointer to a row and sorts the integers in place.

Hints: See ex0a.c and ex0b.c for how to create a multi-dimensional array dynamically.
       Use the BubbleSort() from previous exercises.
*/
