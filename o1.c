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

int main(int iArgC, char **apszArgV){

	int *ipRows, *ipCols, iArgs, *ipIn, iInserted;

	ipRows = (int *) malloc(sizeof(int*));
	ipCols = (int *) malloc(sizeof(int*));

	int **iArr, i, j;

	iArgs = 0;
	printf("\nEnter rows: ");
	scanf("%d", ipRows);
	printf("\nEnter columns: ");
	scanf("%d", ipCols);
	
	printf("rows: %d - cols: %d\n", *ipRows, *ipCols);

	iArr = (int **) malloc(*ipRows * sizeof(int *));
	for(i = 0; i < *ipRows; ++i){
		iArr[i] = (int *) malloc(*ipCols * sizeof(int ));
		for(j = 0; j < *ipCols; j++){
			iArr[i][j] = 0;	
		}

	}



	while(1){
		ipIn = (int *) malloc(sizeof(int*));
		printf("\nEnter a non-zero positive integer.\n Num: ");
		scanf("%d", ipIn);	
			
		if(*ipIn <= 0){
			while(*ipIn <= 0){
				printf("\nNot a non-zero positive integer. Try again.\n Num:");
				scanf("%d", ipIn);	
			}
		}

		srand(time(NULL));
		int iRandomRow = rand()% (*ipRows);
		printf("Randomly assigned row (ceiling: %d): %d\n", *ipRows-1, iRandomRow);

		iInserted = InsertInt(iArr[iRandomRow], *ipIn, iRandomRow, *ipCols);
		if(iInserted == 1){
			printf(
				"Data was not inserted at row [%d]\n Checking from start ...\n",
				iRandomRow
			);

			for(i = 0; i < *ipRows - 1; i++){
				if(i != iRandomRow){
					iInserted = InsertInt(iArr[i], *ipIn, i, *ipCols);	
					if(iInserted == 0){
						printf("--> Inserted at available space after failed random assignment.\n");
						break;	
					}
				}

			}	

			if(iInserted == 0){
				printf("Array is full.\n");	
				break;
			}
		} 
		printf("\nCurrent Table:\n");
		PrintTable(iArr, *ipRows, *ipCols);
	}

	printf("\nUnsorted Table\n");
	PrintTable(iArr, *ipRows, *ipCols);

	for(i = 0; i < *ipRows; ++i){
		BubbleSort(iArr[i], *ipCols);	
	}

	printf("\nSorted Table\n");
	PrintTable(iArr, *ipRows, *ipCols);

	/* Freeing pointers and arrays */
	free(ipRows);
	free(ipCols);
	free(ipIn);

	for(i = 0; i < *ipRows; ++i){
		free(iArr[i]);	
	}

	free(iArr);

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
	int *ipA = (int *) malloc(sizeof(int)); 
	int *ipB = (int *) malloc(sizeof(int));

	for(;;){
		iIterations = 0;
		for(i = 1; i < iArrLen; ++i){
			ipA = &iArr[i - 1];
			ipB = &iArr[i];
			if(*ipA > *ipB){
				Swap(ipA, ipB);	
			}
		}	

		if(iIterations == 0) break;
	}

	free(ipA);
	free(ipB);
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
