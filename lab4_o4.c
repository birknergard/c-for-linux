#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Swap(int *ipFirst, int *ipSecond){
	
	if(*ipFirst < *ipSecond){
		int ipTemp = *ipFirst;
		*ipFirst = *ipSecond; 
		*ipSecond = ipTemp; 
		return 1;
	} else {
		return 0;
	}
}

int main(int iArgC, char *pszArgV[]){
	
	int iSize = iArgC - 1;

	printf("Array size: %d -> ", iSize);	
	// print raw input with size 
	for(int i = 1; i < iSize + 1; ++i){
		printf(" %d", atoi(pszArgV[i]));
	}

	// Convert raw input into int array
	printf("converted list: ");	
	int iarrNums[iSize];
	for(int i = 1; i < iSize + 1; ++i){
		iarrNums[i - 1] = atoi(pszArgV[i]);
		printf("%d ", iarrNums[i - 1]);
	}
	printf("\n");	

	while(1){
		int iIterations = 0;

		// start at index 2 because index[1-1] isnt an input 
		for(int i = iSize - 1; i > 0; --i){
			/* Creates pointers to indexes 0 and 1 in the array
			 * When swap is invoked, the
			 * */
			int *ipFirst = &iarrNums[i];
			int *ipSecond = &iarrNums[i - 1];

			if(Swap(ipFirst, ipSecond) == 1){
				printf("%d and %d have been swapped!\n", *ipFirst, *ipSecond);
				++iIterations;
			}
		}
		printf("Sorting through ...\n");
		// if no changes are made, break the loop 
		if(iIterations == 0){

			printf("Sort complete!\n");
			break;
		}

	} 

	printf("\nSorted:");
	for(int i = 0; i < iSize; ++i){
		printf(" %d", iarrNums[i]);
	}
	printf("\n");

	return 0;

}
/*
Exercise 4:

Expected time on the problem: 40 min

Write a small program that does bubble sort on an array of positive integers.
The integers and the number of them is unknown.

An example on using the program could be:
ex3 12 3 45 67 99

Then the program should print the number of numbers, then the numbers in ascending order as:
5: 3 12 45 67 99

Hint: int main(int iArgC, char *pszArgV[]), atoi();

Bubble sort:

Run through the elements and swap when you find a[i-1] > a[i]. Keep doing
this until you cannot swap anymore. Swapping should be done by function call
Swap(a,b).
*/
