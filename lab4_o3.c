#include <stdio.h>

int main(int iArgC, char* pcharrArgV[]){
	int a,b;

	int *p = &a;
	int *q = &b;

	printf("Type two integers separated with a space:\n");
	scanf("%d %d", p, q); 
	
	printf("The numbers are %d, %d\n", a, b);

	if(a > b){
		printf("The larger number is %d\n", a);
	} else if(a == b) {
		printf("The numbers are even.\n");
	} else {
		printf("The larger number is %d\n", b);
	}

	return 0;
}









































