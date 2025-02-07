#include <stdio.h>

int main(int iArgC, char* parrArgV[]){

	printf("number of strings: %d\n", iArgC - 1);
	
	for(int i = 1; i < iArgC; ++i){
		printf("%d: %s\n", i, parrArgV[i]);
	}

	return 0;
}
/*
Exercise 5:

Expected time on the problem: 10 min

Write a small program that takes a series of strings as parameters and just
prints them as:

ex5 hallo on the bath you old candybar
Number of strings: 7
1: hallo
2: on
3: the
4: bath
5: you
6: old
7: candybar
*/



