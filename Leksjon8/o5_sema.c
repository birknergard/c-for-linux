/*
 * Implement multithreading using somaphores
 * */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#pragma pack (1)
typedef struct {
	int *ipArg;
	sem_t *semSignal;

} THREAD_DATA;

#pragma pack()

void *ThreadMethod(void *pThreadData){
	THREAD_DATA td = *(THREAD_DATA *) pThreadData;

	sem_wait(td.semSignal);
	printf("Thread data: %d", *td.ipArg);
	sem_post(td.semSignal);
}

int main(void){
	THREAD_DATA td;
	pthread_t pThread1, pThread2;

	int *ipNumber;
	ipNumber = (int*)malloc(sizeof(int));
	if(ipNumber == NULL) return 1;
	*ipNumber = 5;

	td.semSignal = (sem_t*) malloc(sizeof(sem_t));
	if(td.semSignal == NULL) return 1;

	td.ipArg = ipNumber;
	sem_init(td.semSignal, 0, 1);

	
	pthread_create(&pThread1, NULL, ThreadMethod, &td);
	pthread_create(&pThread2, NULL, ThreadMethod, &td);
	
	pthread_join(pThread1, NULL);
	pthread_join(pThread2, NULL);

	free(ipNumber);
	free(td.semSignal);
	
	return 0;
}
