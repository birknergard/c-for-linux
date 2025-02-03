#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){

	double a = atof(argv[1]);	
	double b = atof(argv[2]);
	double c = atof(argv[3]);

	double x1 = (b + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
	double x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;

	printf("Solution 1 is x = %.2f\n", x1);
	printf("Solution 2 is x = %.2f\n", x2);
	
	return 0;
}



