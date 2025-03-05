/*
Exercise 2:

Take your bubble sort and binary search code, make them into functions. Then
provide interfaces to them using header files. Compile them into a static library
Then rewrite your main program so that you simply include the header and use the
functions but not the source of the implementaton. Instead you should link with
the library.
*/
#include <stdio.h>
#include "./include/algo.h"

int main(void){
	int i;
	int iarr[] = {10, 5, 1, 2, 3, 6, 4, 7, 8, 0};

	for(i = 0; i < 10; i++){
		printf("%d ", iarr[i]);
	}

	puts("\n");

	BubbleSort(iarr, 10);

	for(i = 0; i < 10; i++){
		printf("%d ", iarr[i]);
	}

	puts("\n");


	return 0;
}
