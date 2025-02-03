#include <stdio.h>

int main(){
	int a,b,c,d;
	a = 5;
	b = a++;
	c = ++b;
	d = b++;

	int x, y, z, w;
	x = 10;
	y = 9;
	z = 8;
	w = 7;

	if((w==y++) && (z=++x)){
		w = 100;	
		printf("This is obviously true");
	}
	
	z = ++w+y++;

	printf("a = %d\n", a);

	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("d = %d\n", d);
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	printf("z = %d\n", z);
	printf("w = %d\n", w);
	return 0;
}	
/*
 Guessing:
 a will be 5
 b will be 5
 c will also be 6
 d will also be 6

 x will be 10
 y will be 9
 w will be 7

 z will be 17

*/

