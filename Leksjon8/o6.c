/*
 * Implement multithreading using somaphores
 * */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

#define MAX_BUFFER 4096

#pragma pack (1)
typedef struct {
	char *szBuffer;
	FILE *f;
	sem_t semWorkerDone;
	sem_t semPrinterDone;
	int iExitStatus;

} THREAD_DATA;

#pragma pack()

void *WorkerThread(void *pThreadData){
	THREAD_DATA *td = (THREAD_DATA *) pThreadData;

	while(td->iExitStatus == 0){
		sem_wait(&td->semPrinterDone);

		if(td->iExitStatus == 1)
			break;	

		fprintf(td->f, "%s", td->szBuffer);

		sem_post(&td->semWorkerDone);
	}

	return NULL;
}

int main(void){

	/* Declare variables/pointers */
	THREAD_DATA *td;
	pthread_t tpWorkerThread;
	char *szInputBuffer;
	int iSliceStart;

	/* Allocate for pointers, verify allocation */
	szInputBuffer = (char*) malloc(MAX_BUFFER);
	if(szInputBuffer == NULL) return 1;

	td = (THREAD_DATA*) malloc(sizeof(THREAD_DATA));
	if(td == NULL) return 1;

	td->szBuffer = (char *) malloc(11);
	if(td->szBuffer == NULL) return 1;

	/* Initialize semaphores */
	sem_init(&td->semWorkerDone, 0, 0);
	sem_init(&td->semPrinterDone, 0, 0);

	/* Open textfile for write */
	td->f = fopen("o6_text.txt", "w");
	if(td->f == NULL) return 1;

	/* Initialize exit status to 0 (false) */
	td->iExitStatus = 0;

	/* Start worker thread */
	pthread_create(&tpWorkerThread, NULL, WorkerThread, (void*) td);

	while(td->iExitStatus == 0){

		/* Take user input */
		puts("Enter some text (type \"exit\" to end program): ");
		fgets(szInputBuffer, MAX_BUFFER, stdin);

		/* If input is "quit" the a signal is sent to worker thread early*/
		if(strcmp(szInputBuffer, "exit\n") == 0){
			td->iExitStatus = 1;
		}

		if(td->iExitStatus != 0){
			sem_post(&td->semPrinterDone);
			break;

		} else {
		
			/* initialize startindex to copy from */
			iSliceStart = 0;
			while(iSliceStart < strlen(szInputBuffer)){

				/* Copy 10 characters from userinput to buffer */
				strncpy(td->szBuffer, (szInputBuffer + iSliceStart), 10);
				printf("buf:%s", td->szBuffer);
				td->szBuffer[10] = '\0';

				/* Signal to worker thread that input is ready to be parsed */
				sem_post(&td->semPrinterDone);

				/* Wait until workerthread is done parsing input */
				sem_wait(&td->semWorkerDone);

				/* Flag the next 10 characters for copy */
				iSliceStart += 10;
			} 
		}
	}
	
	/* Close worker thread, destroy semaphores */
	pthread_join(tpWorkerThread, NULL);
	sem_destroy(&td->semPrinterDone);
	sem_destroy(&td->semWorkerDone);

	/* Close the text file */
	fclose(td->f);

	/* Free pointers */
	free(td->szBuffer);
	free(td);
	free(szInputBuffer);
	
	return 0;
}
