#include <stdio.h>
#include <stdlib.h>

int InsertIntIn(
	int **iArr,
   	int iVal,
	int iAtRow,
   	int iColCount,
);

int main(int iArgC, char **apszArgV){

	int *iRows, *iCols, iArgs, *iIn, iInserted;

	int **iArr, i;


	while iArgs != 2{
		printf("Enter rows, columns (r, c):");
		iArgs = scanf("%d, %d", iRows, iCols);
	}
	
	iArr = (int **) malloc(*iRows * sizeof(int));
	for(i = 0; i < iCols; ++i){
		iArr[i] = (int *) malloc(*iCols * sizeof(int));
	}

	while(iIn < 0){
		printf("Enter a positive integer or a negative number to exit.\n Num: ");
		iArgs = scanf("%d", iIn);	
			
		
		srand(time(NULL));
		int iRandomRow = rand()%(iRows-1);

		iInserted = InsertInt(iArr, *iIn, iRandomRow, iCols);
		if(iInserted == 0){
			
		}

	}	

	/* Freeing pointers and arrays */
	free(iRows);
	free(iCols);
	free(iIn);

	for(i = 0; i < iRows; i++){
		free(iArr[i]);	
	}

	free(iArr);

	return 0;
} 

int InsertInt(
	int **iArr,
   	int iVal,
	int iAtRow,
   	int iColCount,
){
	int result, i;

	for(i = 0; i < iColCount; i++){
		if(iArr[i] != NULL && i == iColCount -1){
			return 0;	

		} else {
			iArr[iAtRow][i] = *iIn;
			printf("%d was inserted at index [%d][%d]");
			return 1;
		} 

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
