/*
 * Implement multithreading using somaphores
 * */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

#define MAX_BUFFER 4096
#define BUFFER 

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
	THREAD_DATA *td;
	pthread_t tpWorkerThread;
	char *szInputBuffer;
	int iSliceStart;

	szInputBuffer = (char*) malloc(MAX_BUFFER);
	if(szInputBuffer == NULL) return 1;

	td = (THREAD_DATA*)malloc(sizeof(THREAD_DATA));
	if(td == NULL) return 1;

	td->szBuffer = (char *)malloc(11);
	if(td->szBuffer == NULL) return 1;

	sem_init(&td->semWorkerDone, 0, 0);
	sem_init(&td->semPrinterDone, 0, 0);

	td->f = fopen("./o6_text.txt", "w+");

	pthread_create(&tpWorkerThread, NULL, WorkerThread, (void*) td);

	td->iExitStatus = 0;
	while(td->iExitStatus == 0){
		printf("Enter some text: ");
		fgets(szInputBuffer, MAX_BUFFER, stdin);

		if(strcmp(szInputBuffer, "quit") == 0){
			td->iExitStatus = 1;	
		}

		iSliceStart = 0;

		do{
			sem_wait(&td->semWorkerDone);
			strncpy(td->szBuffer, szInputBuffer, 10);
			td->szBuffer[11] = '\0';

			iSliceStart += 10;

			sem_post(&td->semPrinterDone);

		} while(iSliceStart < strlen(szInputBuffer));
	}
	
	pthread_join(tpWorkerThread, NULL);
	sem_destroy(&td->semPrinterDone);
	sem_destroy(&td->semWorkerDone);

	fclose(td->f);
	free(td);
	
	return 0;
}
