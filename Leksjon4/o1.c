#include <stdio.h>
#include "include/source.h"

int a, b;

void main(void){
	int i, j;
	printf("Adresses of global variables: %p %p\n", &a, &b);
	printf("Addresses of local variables: %p %p\n", &i, &j);
}
