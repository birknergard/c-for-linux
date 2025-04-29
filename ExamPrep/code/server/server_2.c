#include <sys/socket.h>
#include <netinet/in.h> /* For INADDR_ANY */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "../bexam_lib/include/debug.h"
#include "server_2.h"

int main(void){
	int iErrorDetected;
	iErrorDetected = RunServer(); 
	
	if(iErrorDetected != 0){
		berror("Server crashed - errcode: %d", iErrorDetected);			
		return 1;
	}

	return 0;
}

int RunServer(){
	/* Declaring variables */
	int bBindStatus, iListened, iStatusCode, i;

	int iThreads;
	pthread_t *pThreads;
	THREAD_DATA **pptDataContainers;
	sem_t semThreadReady;
	/* Size of array matches the number of threads*/
	int *ipThreadTracker;

	int sockServerDescriptor;
	struct sockaddr_in saServerAddress;

	int iNewAddressLength;
	int iRequests;

	/* Setting number of threads */
	iThreads = 3;

	/* Set pointers to NULL */
	ipThreadTracker = NULL;
	pThreads = NULL;
	pptDataContainers = NULL;

	/* If unchanged, return error free. */
	iStatusCode = 0;

	/* Open network socket (TCP/IP Protocol), as a stream */
	sockServerDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(sockServerDescriptor < 0){
		iStatusCode = errno;
		close(sockServerDescriptor);
		berror("Error when opening socket - errcode: %d", iStatusCode);
		return iStatusCode;
	}

	/* Sets address type */
	saServerAddress.sin_family = AF_INET; 

	/* Converts port (int) into TCP/IP byte order (from little to big endian) */
	saServerAddress.sin_port = htons(PORT); 

	/* The server listens to any available network interfaces (wifi etc.) on the computer */
	saServerAddress.sin_addr.s_addr = INADDR_ANY;  
			
	/* Bind socket to address */
	bBindStatus = bind(
		sockServerDescriptor,
		(struct sockaddr *) &saServerAddress,
		sizeof(saServerAddress)
	);
	if(bBindStatus < 0){
		iStatusCode = errno;
		berror("Error with bind() - errcode %d", iStatusCode, bBindStatus);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		return iStatusCode;
	} 


	/* Make server listen for input */
	iListened =	listen(sockServerDescriptor, 5);
	if(iListened < 0){
		iStatusCode = errno;
		berror("Listen failed - errcode: %d", iStatusCode);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		return iStatusCode;
	}

	/* Initialize thread tracker */
	ipThreadTracker = (int *) malloc(sizeof(int) * iThreads);
	if(ipThreadTracker == NULL){
		berror("An error occured whiile allocating the thread tracker.", iStatusCode);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		return ERROR;
	}
	memset(ipThreadTracker, 0, sizeof(int) * iThreads);

	/* Allocate memory for threads */
	pThreads = (pthread_t *) malloc(sizeof(pthread_t) * iThreads);
	if(pThreads == NULL){
		close(sockServerDescriptor); sockServerDescriptor = -1;
		berror("An error occurred while allocating to thread containers.\n");
		return ERROR;
	}

	pptDataContainers = (THREAD_DATA **) malloc(sizeof(THREAD_DATA *) * iThreads);
	if(pptDataContainers == NULL) {
		close(sockServerDescriptor); sockServerDescriptor = -1;
		free(pThreads);
		berror("An error occurred while allocating to thread containers.\n");
		return ERROR;
	}
	memset(pptDataContainers, 0, sizeof(THREAD_DATA *) * iThreads);

	/* Initialize semaphores and mutexes */
	sem_init(&semThreadReady, 0, 2);

	/* Initializing request count tracker */
	iRequests = 0;

	puts("STARTING SERVER\n");
	/* Handle requests */
	while(1){
		puts("Accepting new request ...\n");
		/* Add request */
		iRequests++;
		if(iRequests > 1){
			bdebug("Max requests exceeded, exiting ... \n");
			break;
		}

		/* Wait for empty thread */ 
		bdebug("Waiting for open thread ...\n");
		sem_wait(&semThreadReady);

		/* Thread is confirmed open above, now to find it*/
		i = 0;
		for(;;){
			/* Loops until it finds an open thread */
			i++;
			if(i == iThreads) i = 0;

			/* when open thread flag is found, start new thread */
			bdebug("FINDING AVAILABLE THREAD\n");
			if(ipThreadTracker[i] == 0){
				bdebug("JOINING ...\n");
				/* makes sure thread is completed before restarting NOTE: WILL WARN IN VALGRIND*/
				/*pthread_join(pThreads[i], NULL);*/

				bdebug("FREEING OLD DATA FOR TD-%d if exists ...\n", i);
				/* Create unique pointer for each new thread */
				if(pptDataContainers[i] != NULL){
					free(pptDataContainers[i]);
				}

				bdebug("ALLOCATING NEW MEMORY FOR FOR TD-%d DATA ...\n", i);
				pptDataContainers[i] = (THREAD_DATA *) malloc(sizeof(THREAD_DATA));
				if(pptDataContainers[i] == NULL){
					close(sockServerDescriptor); sockServerDescriptor = -1;
					berror("An error occurred while allocating to thread container.\n");
					break;
				}

				bdebug("SETTING NEW MEMORY FOR FOR TD-%d DATA ...\n", i);
				memset(pptDataContainers[i], 0, sizeof(THREAD_DATA));
				pptDataContainers[i]->saClientAddress = (struct sockaddr_in) {0}; 
				iNewAddressLength = sizeof(pptDataContainers[i]->saClientAddress); 

				pptDataContainers[i]->sockClientDescriptor = accept(
						sockServerDescriptor,
						(struct sockaddr *) &pptDataContainers[i]->saClientAddress,
						(socklen_t *) &iNewAddressLength
				);
				/* if connection was unsuccessful */ 
				if(pptDataContainers[i]->sockClientDescriptor < 0){
					iStatusCode = errno;
					berror("An error occured when accepting connection - errcode: %d\n", iStatusCode);
					break;
				} 

				/* Stores a reference to our thread tracker... */
				pptDataContainers[i]->ipThreadTracker = ipThreadTracker; 

				/* and semaphores */
				pptDataContainers[i]->semThreadReady = &semThreadReady;

				/*bdebug("Open thread found (id:%d)! Running thread ... \n", i);*/
				pptDataContainers[i]->iThreadID = i;
				pptDataContainers[i]->ipThreadTracker[i] = 1;
				pthread_create(&pThreads[i], NULL, HandleRequest, (void*) pptDataContainers[i]);
				break;	
			}
		}
	}

	/* Close any open threads */
	for(i = 0; i < iThreads; i++){
		if(ipThreadTracker[i] == 1)
			pthread_join(pThreads[i], NULL);
	}
	free(pThreads);
	pThreads = NULL;

	/* Destroy thread resources */
	sem_destroy(&semThreadReady);
	for(i = 0; i < iThreads; i++){
		if(pptDataContainers[i] != NULL){
			close(pptDataContainers[i]->sockClientDescriptor); pptDataContainers[i]->sockClientDescriptor = -1;
			free(pptDataContainers[i]);
		}
	}
	free(ipThreadTracker);
	free(pptDataContainers);
	pptDataContainers = NULL;

	/* Close the sockets, then assign a secure exit value */
	close(sockServerDescriptor); sockServerDescriptor = -1;

	return iStatusCode;
}

void *HandleRequest(void *vptData){
	/* Accept connection from client, execute in open thread */
	THREAD_DATA *ptData = (THREAD_DATA *) vptData;

	printf("TH-ID %d: THREAD STARTED! on port: %d -> TRACKER [%d, %d, %d]\n", 
		ptData->iThreadID,
		PORT,
		ptData->ipThreadTracker[0],
		ptData->ipThreadTracker[1],
		ptData->ipThreadTracker[2]
	);

	/* Simulate work */
	sleep(5);
	ptData->ipThreadTracker[ptData->iThreadID] = 0;

	printf("TH-ID %d: THREAD COMPLETE! Exiting ... -> TRACKER [%d, %d, %d]\n",
		ptData->iThreadID,
		ptData->ipThreadTracker[0],
		ptData->ipThreadTracker[1],
		ptData->ipThreadTracker[2]
	);

	/* Signal completion to main process */
	sem_post(ptData->semThreadReady);

	/* TODO: Retrieve data from thread? */ 
	return NULL;
}
