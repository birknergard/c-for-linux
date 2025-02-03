#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	srand(time(NULL));
	int a = rand()%20;

	switch(a){
		case 5: 
			printf("%d is a prime\n", a);
			break;
		case 7:
			printf("%d is a prime\n", a);
			break;
		case 11:
			printf("%d is a prime\n", a);
			break;
		case 13:
			printf("%d is a prime\n", a);
			break;
		case 17:
			printf("%d is a prime\n", a);
			break;
		case 19:
			printf("%d is a prime\n", a);
			break;
		default:
			printf("%d is not a prime\n", a);
			break;

	}
	
	srand(time(NULL));	
	int iSumB = 0;

	int b = rand()%40;
	do {
		iSumB = iSumB + b++;
		printf("DOWHILE: sum is %d\n", iSumB);
	} while(b < 40);

	int iSumC = 0;
	for(int c = rand()%40; c < 40; c++){
		iSumC = iSumC + c++;	
		printf("FOR: sum is %d \n", iSumC);
	}

	return 0;
}
