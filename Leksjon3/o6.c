#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

int Fibo(int iNum){
	if(iNum == 0){
		return 0;
	} 

	if(iNum == 1){
		return 1;
	}

	return Fibo(iNum - 1) + Fibo(iNum - 2);
}

int QuickFibo(int iNum){
// tbd
	int num1 = iNum - 1;
	int num2 = iNum - 2;
	int fibo = num1 + num2;

	if(iNum == 0){
		return 0;
	} 

	if(iNum == 1){
		return 1;
	}

}



unsigned long GetTime() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*(unsigned long)1000000+tv.tv_usec;
}


int main(int iArgC, char *cparrArgV[]){

	unsigned long timeStart, timeEnd;
	timeStart = GetTime();

	//Do some processing here;
	int iNum = atoi(cparrArgV[1]);	

	if(iNum == 0){
		printf("Number has to be non-zero value.\n");
		return 1;
	}	

	if(iNum < 2){
		printf("Number has to be greater than 1.\n");
		return 1;
	}
		
	printf("Your number %d is the %d number of the fibonacci sequence.\n", Fibo(iNum - 1), iNum);


	timeEnd = GetTime();
	printf("The elapsed time is %lu ms\n", (timeEnd - timeStart)/1000);

	return 0;
}




