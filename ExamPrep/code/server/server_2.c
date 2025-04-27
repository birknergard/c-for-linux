#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "../bexam_lib/include/debug.h"
#include "server_2.h"

void Method(){ printf("Hello");}

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
	int sockServerDescriptor, sockNewDescriptor;
	int bBindStatus;
	int i, iStatusCode, iListened;
	int iNewAddressLength;

	int iThreads;
	pthread_t threads[2];
	sem_t semThreadReady, semThreadComplete;
	struct sockaddr_in saServerAddress;
	struct sockaddr_in *saClientAddress;


	/* Setting number of threads */
	iThreads = 2;

	/* If unchanged, return error free. */
	iStatusCode = 0;

	/* Open network socket (TCP/IP Protocol), as a stream */
	sockServerDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(sockServerDescriptor < 0){
		iStatusCode = errno;
		berror("Error when opening socket - errcode: %d", iStatusCode);
	}

	/* Initialize server socket address(es) to zero */
	saClientAddress = (struct sockaddr_in *) malloc(sizeof(struct sockaddr) * 2);
	if(saClientAddress == NULL){
		berror("An error occurred while initializing client address.\n");
		return ERROR;
	}
	memset(&saClientAddress[0], 0, sizeof(struct sockaddr));

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

	/* Does not continue if bind failed */
	if(bBindStatus < 0){
		iStatusCode = errno;
		berror("Error with bind() - errcode %d", iStatusCode, bBindStatus);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		return iStatusCode;
	} 

	/* Make server listen for input */
	iListened =	listen(sockServerDescriptor, 2);
	if(iListened < 0){
		iStatusCode = errno;
		berror("Listen failed - errcode: %d", iStatusCode);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		return iStatusCode;
	}

	/* Initialize semaphores */
	sem_init(&semThreadReady, 0, 2);
	sem_init(&semThreadComplete, 0, 2);

	/* Open threads */
	for(i = 0; i <= iThreads; i++){
		pthread_create(&threads[i], NULL, (void *) Method, NULL);
	}

	/* Handle requests /
	for(;;){
		/ TODO: Initialize client socket address to zero /
		sockNewDescriptor = 0;
		iNewAddressLength = sizeof(saClientAddress[i]); 

		accept(
			sockServerDescriptor,
			(struct sockaddr *) &saClientAddress,
			(socklen_t *) &iNewAddressLength
		);
	}
		*/
 
	/* Close threads */
	for(i = 0; i <= iThreads; i++){
		pthread_join(threads[i], NULL);
	}

	/* Close the sockets, then assign a secure exit value */
	free(saClientAddress);
	saClientAddress = NULL;
	close(sockServerDescriptor); sockServerDescriptor = -1;
	close(sockNewDescriptor); sockNewDescriptor = -1;

	return iStatusCode;
}

/*
int HandleRequest(THREAD_DATA tData, BSCP_PACKET bscpPacket){
	/ TODO: Accept connection from client, execute in open thread /
	printf("Message received!\n from %p:%d\n", &saClientAddress.sin_addr, PORT);

	if(preqBuffer == NULL){
		iStatusCode = ERROR;
		berror("Data could not be read.");

	} else if(sizeof(preqBuffer->Header) > MAX_HEADER){
		iStatusCode = ERROR;
		berror("HEADER exceeds data capacity.");

	} else if(preqBuffer->Header.iDataSize > MAX_BODY){
		iStatusCode = ERROR;
		berror("BODY exceeds data capacity.");

		} else {
			switch(preqBuffer->Header.cAction){
				case 'R':
					HandleRequest(*preqBuffer);
					break;
				case 'W':
					HandleRequest(*preqBuffer);
					break;

				default:
					berror("Invalid action.");
					break;
			} 
		} 
	}

	int iSize;
	char *pszProtocolData;
	pszProtocolData = NULL;

	iSize = bscpPacket.Header.iDataSize;

	/ Return early if protocol is invalid. Will implement sending error back to client later. /
	/ Since there is no data to close at this point in the program returning early should be fine. /
	if(bscpPacket.szBody == NULL){
		berror("PACKET BODY could not be read.");
		return ERROR;
	}

	pszProtocolData = (char *) malloc(iSize + 1);
	if(pszProtocolData == NULL){
		berror("Malloc failed on data buffer.");
		return ERROR;
	}

	strncpy(pszProtocolData, bscpPacket.szBody, iSize);
	pszProtocolData[iSize] = '\0';
	if(pszProtocolData != NULL){
		printf("-> %s\n", pszProtocolData);
	}

	free(pszProtocolData);
	pszProtocolData = NULL;

	return OK;
}
*/
