/*
Exercise 5:

Play with pthreads library. Try to accomplish the following

-create a thread that prints numbers

Example:

void *PrintMessage (void *pvData)
{
   char *pszMessage = (char *)pvData;

   pthread_mutex_lock (&pmMux1);

   iCounter += 1;
   printf ("In %s: iCounter=%d\n", pszMessage, iCounter);
   usleep(200);

   iCounter += 1;
   printf ("In %s: iCounter=%d\n", pszMessage, iCounter);
   usleep(200);

   pthread_mutex_unlock (&pmMux1);

   return NULL;
}

void main (void)
{
   pthread_t pThread1, pThread2;
   char *pszMessage1 = "Thread 1";
   char *pszMessage2 = "Thread 2";

   printf("Before threads started.\n");

   pthread_create (&pThread1, NULL, PrintMessage, (void *) pszMessage1);
   pthread_create (&pThread2, NULL, PrintMessage, (void *) pszMessage2);

   printf("After threads started.\n");

   pthread_join(pThread1, NULL);  // Wait for thread 1 to finish.
   pthread_join(pThread2, NULL);  // Wait for thread 2 to finish.

   printf("After threads finished.\n");
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#pragma pack(1)
typedef struct {
	int *ipData;
	pthread_mutex_t *tmLock;

} THREAD_DATA;
#pragma pack()

void *ThreadRoutine(void *p){
	int iRand = (rand()%10);


	THREAD_DATA *thrData;
	thrData = (THREAD_DATA *) p; 

	pthread_mutex_lock(thrData->tmLock);
	printf("Thread %d operation - num: %d\n", *thrData->ipData, *thrData->ipData * iRand);
	
	pthread_mutex_unlock(thrData->tmLock);
	return NULL;
}

int main(void){
	THREAD_DATA *sdThreadData;
	pthread_mutex_t *tmLock;
	pthread_t *pThread;

	srand(time(NULL));

	pThread = (pthread_t *) malloc(sizeof(pthread_t) * 10);
	if(pThread == NULL)
		return 1;
	
	sdThreadData = (THREAD_DATA*) malloc(sizeof(THREAD_DATA) * 10);
	if(sdThreadData == NULL)
		return 1;
	

	tmLock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if(tmLock == NULL)
		return 1;


	int iNum1, i;
	iNum1 = 1;

	pthread_mutex_init(tmLock, NULL);

	printf("Starting threads ...\n");
	for(i = 0; i < 10; i++){
		sdThreadData[i].tmLock = tmLock;	
		sdThreadData[i].ipData = &iNum1;
		pthread_create(&pThread[i], NULL, ThreadRoutine, (void *) &sdThreadData[i]);
	}


/* First is thread id/address (defined above),
 * NULL is default(second arg) attribute, third is the function to be executed,
 * Fourth is the arguments for the function stored as a void ptr*/


/* First argument is the pthread_t (NOTE: not the adress, but the value!)
 * Dont know what second value is
 * */
	/* Close threads and free memory */
	printf("Closing threads\n");
	for(i = 0; i < 10; i++){
		pthread_join(pThread[i], NULL);
	}

	free(sdThreadData);
	free(pThread);
	free(tmLock);

	return 0;
}


