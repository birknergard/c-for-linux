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

typedef struct _THREAD_DATA{
	int *ipData;
	pthread_mutex_t tmLock;

} THREAD_DATA;

void *ThreadRoutine(void *p){
	THREAD_DATA *thrData;
	thrData = (THREAD_DATA *) p; 

	pthread_mutex_lock(&thrData->tmLock);
	printf("Thread %d operation \n", *thrData->ipData);
	
	pthread_mutex_unlock(&thrData->tmLock);
	return NULL;
}


int main(void){
	THREAD_DATA *sdThreadData1, *sdThreadData2;
	pthread_mutex_t *tmLock;
	pthread_t pThread1, pThread2;

	int iNum1, iNum2;
	iNum1 = 1;
	iNum2 = 2;

	pthread_mutex_init(tmLock, NULL);
	sdThreadData1->tmLock = tmLock;
	sdThreadData2->ipData = &iNum2;

	sdThreadData2->tmLock = tmLock;
	sdThreadData1->ipData = &iNum1;


	printf("Starting threads ...\n");

/* First is thread id/address (defined above),
 * NULL is default(second arg) attribute, third is the function to be executed,
 * Fourth is the arguments for the function stored as a void ptr*/
	pthread_create(&pThread1, NULL, ThreadRoutine, (void *) &sdThreadData1);
	pthread_create(&pThread2, NULL, ThreadRoutine, (void *) &sdThreadData2);


/* First argument is the pthread_t (NOTE: not the adress, but the value!)
 * Dont know what second value is
 * */
	pthread_join(pThread1, NULL);
	pthread_join(pThread2, NULL);

	return 0;
}


