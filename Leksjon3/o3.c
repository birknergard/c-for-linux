#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	int iInput = atoi(argv[1]);

	printf("your input: %d\n", iInput);


	if(iInput == 0){
		printf("Invalid input. needs to be a non-zero number.");	
		return 1;
	}

	if(iInput % 2 == 0) {
		printf("Your number is even!\n");	
		return 0;
	} 
	if(iInput % 2 != 0){
		printf("Your number is odd!\n");	
		return 0;
	}	
	else {
		printf("invalid input. needs to be a number.");
		return 1;
	}

		
	return 0;
}
	
