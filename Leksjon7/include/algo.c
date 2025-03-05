#include "algo.h"

#include <stdio.h>
#include <stdlib.h>

void Swap(int *ipA, int *ipB){
	int	temp;
	temp = *ipA;
	*ipA = *ipB;
	*ipB = temp;
}

void BubbleSort(int *iarr, int iLength){
	printf("Starting bubble sort.\n");
	int i, *iA, *iB, iIterations;
	iA = NULL;
	iB = NULL;

	for(;;){
		iIterations = 0;
			
		for(i = 1; i < iLength; ++i){
			iA = &iarr[i];
			iB = &iarr[i - 1];

			if(*iA > *iB){
				Swap(iA, iB);
				++iIterations;
			}
		}

		if(iIterations == 0)
		   break;
	}
	
	printf("Completed bubble sort.\n");
}

void BinarySearch(int iNum, int *iarr){
	puts("Perform BinarySearch\n");
}
