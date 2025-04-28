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
	int iErrorDetected = RunServer(); 

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
	THREAD_DATA *ptDataContainer;

	int sockServerDescriptor;
	struct sockaddr_in saServerAddress;

	int iNewAddressLength;

	int iRequests;

	/* Setting number of threads */
	iThreads = 2;
	iRequests = 0;
	pThreads = NULL;
	ptDataContainer = NULL;

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

	ptDataContainer = (THREAD_DATA *) malloc(sizeof(THREAD_DATA));
	if(ptDataContainer == NULL){
		close(sockServerDescriptor); sockServerDescriptor = -1;
		berror("An error occurred while allocating to thread container.\n");
		return ERROR;
	}
	memset(ptDataContainer, 0, sizeof(THREAD_DATA));

	/* Make server listen for input */
	iListened =	listen(sockServerDescriptor, 4);
	if(iListened < 0){
		iStatusCode = errno;
		berror("Listen failed - errcode: %d", iStatusCode);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		return iStatusCode;
	}

	/* Allocate memory for threads */
	pThreads = (pthread_t *) malloc(sizeof(pthread_t) * iThreads);
	if(pThreads == NULL){
		close(sockServerDescriptor); sockServerDescriptor = -1;
		berror("An error occurred while allocating to thread containers.\n");
		return ERROR;
	}
    	
	/* Initialize thread tracker */
	memset(ptDataContainer->ipThreadTracker, 0, sizeof(int));

	iNewAddressLength = sizeof(ptDataContainer->saClientAddress); 

	/* Initialize semaphores and mutexes */
	sem_init(&(ptDataContainer->semThreadReady), 0, iThreads);

	/* Handle requests */
	while((ptDataContainer->sockClientDescriptor = accept(
			sockServerDescriptor,
			(struct sockaddr *) &(ptDataContainer->saClientAddress),
			(socklen_t *) &iNewAddressLength
	)) >= 0){

		/* Add request */
		iRequests++;

		/* Initialize new client socket address to zero */
		ptDataContainer->sockClientDescriptor = 0;

		/* Wait for empty thread */ 
		sem_wait(&(ptDataContainer->semThreadReady));

		/* Thread is confirmed open above, now to find it*/
		for(i = 0; i < iThreads; i++){
			/* when open thread flag is found, start new thread */
			if(ptDataContainer->ipThreadTracker[i] == 0){
				/* makes sure thread is completed before starting a new one */
				ptDataContainer->iThreadID = i;
				pthread_join(pThreads[i], NULL); 
				pthread_create(&pThreads[i], NULL, HandleRequest, (void*) ptDataContainer);
				break;	
			}
		}

		if(iRequests > 3)
			break;
	}

	/* if connection was unsuccessful */ 
	if(ptDataContainer->sockClientDescriptor < 0){
		iStatusCode = errno;
		berror("An error occured when accepting connection - errcode: %d\n", iStatusCode);
	}

	/* Close the sockets, then assign a secure exit value */
	free(pThreads);
	sem_destroy(&(ptDataContainer->semThreadReady));
	free(ptDataContainer);
	ptDataContainer = NULL;
	pThreads = NULL;
	close(sockServerDescriptor); sockServerDescriptor = -1;
	close(ptDataContainer->sockClientDescriptor); ptDataContainer->sockClientDescriptor = -1;

	return iStatusCode;
}

void *HandleRequest(void *vptData){
	/* Accept connection from client, execute in open thread */
	THREAD_DATA *ptData = (THREAD_DATA *) vptData;

	ptData->ipThreadTracker[ptData->iThreadID] = 1;

	printf("Thread created! on address: %p:%d -", &(ptData->saClientAddress.sin_addr), PORT);
	printf("TRACKER [%d, %d]", ptData->ipThreadTracker[0], ptData->ipThreadTracker[1]);
	sleep(3);

	ptData->ipThreadTracker[ptData->iThreadID] = 0;
	

	sem_post(&ptData->semThreadReady);

	return NULL;
}
