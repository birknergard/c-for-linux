#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int siarrList[5]; 
	
	srand(time(NULL));
	siarrList[0] = rand()%100;
	siarrList[1] = rand()%100;
	siarrList[2] = rand()%100;
	siarrList[3] = rand()%100;
	siarrList[4] = rand()%100;

	printf("The unsorted list: %s", siarrList);
	
	return 0;

}
