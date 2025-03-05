/*
Exercise 1:

Write a function, that can print how many times it has been called so far
without using a global variable
*/

#include <stdio.h>
#include <stdlib.h>


void StaticFunction(){

	static int counter;

	counter+=1;
	printf("StaticFunction has been called %d times\n", counter);
}

int main(void){
	StaticFunction();
	StaticFunction();
	StaticFunction();
	StaticFunction();
	return 0;
}

