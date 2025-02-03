#include <stdio.h>

int main(){
	for(int beers = 100; beers > 0; beers--){
		if(beers == 1){
			printf("%d bottles of beer on the wall, %d bottles of beer. Take one down and pass it around, no more bottles of beer on the wall.\n", beers);
			continue;
		}
		printf("%d bottles of beer on the wall, %d bottles of beer. Take one down and pass it around, %d bottles of beer on the wall.\n" , beers, beers, beers - 1);
	} 
	printf("No more bottles of beer on the wall, no bottles of ber. Go to the store, buy 99 more, 99 bottles of beer.\n");
	return 0;
}






