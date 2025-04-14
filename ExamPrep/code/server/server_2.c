#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../bexam_lib/include/debug.h"
#include "server.h"

#define PORT 8080

int HandleRequest(THREAD_DATA tData, BSCP_PACKET bscpPacket){
	printf("Message received!\n from %p:%d\n", &saClientAddress.sin_addr, PORT);

	/* Verifying header data */
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
	*/

	int iSize;
	char *pszProtocolData;
	pszProtocolData = NULL;

	iSize = bscpPacket.Header.iDataSize;

	/* Return early if protocol is invalid. Will implement sending error back to client later. */
	/* Since there is no data to close at this point in the program returning early should be fine. */
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

int RunServer(){
	/* Declaring variables */
	int sockServerDescriptor, sockNewDescriptor;
	int iNewAddressLength;
	int iStatusCode, iListened;
	int bBindSuccessful;
	char szBuffer[128];

	/* If unchanged, return error free. */
	iStatusCode = 0;

		

	/* Open network socket (TCP/IP Protocol), as a stream */
	sockServerDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	sockNewDescriptor = 0;

	if(sockServerDescriptor < 0){
		iStatusCode = errno;
		berror("Error when opening socket - errcode: %d", iStatusCode);
	}

	/* Initialize server socket address to zero */
	struct sockaddr_in saServerAddress = {0}; 
	struct sockaddr_in saClientAddress = {0};

	/* Sets address type */
	saServerAddress.sin_family = AF_INET; 

	/* Converts port (int) into TCP/IP byte order (from little to big endian) */
	saServerAddress.sin_port = htons(PORT); 

	/* The server listens to any available network interfaces (wifi etc.) on the computer */
	saServerAddress.sin_addr.s_addr = INADDR_ANY;  
			
	/* Bind socket to address */
	bBindSuccessful = bind(
		sockServerDescriptor,
		(struct sockaddr *) &saServerAddress,
		sizeof(saServerAddress)
	);

	/* Does not continue if bind failed */
	if(bBindSuccessful < 0){
		iStatusCode = errno;
		berror("Error with bind() - errcode %d", iStatusCode, bBindSuccessful);
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
	
	/* Initialize client socket address to zero */
	sockNewDescriptor = 0;
	iNewAddressLength = sizeof(saClientAddress); 

	/* Accept connection from client */
	sockNewDescriptor = accept(
		sockServerDescriptor,
		(struct sockaddr *) &saClientAddress,
		(socklen_t *) &iNewAddressLength
	);

	/* Does not continue if accept failed */
	if(sockNewDescriptor < 0){
		iStatusCode = errno;
		berror("Error with accept() - errcode: %d", iStatusCode);	
		close(sockServerDescriptor); sockServerDescriptor = -1;
		close(sockNewDescriptor); sockNewDescriptor = -1;
		return iStatusCode;
	} 

	/* Load string buffer */
	memset(szBuffer, 0, 128);

	/* Receive incoming data */
	recv(sockNewDescriptor, szBuffer, 128, 0);
	if(sockNewDescriptor < 0){
		iStatusCode = errno;
		berror("Error reading message data - errcode: %d", iStatusCode);
		close(sockServerDescriptor); sockServerDescriptor = -1;
		close(sockNewDescriptor); sockNewDescriptor = -1;
		return iStatusCode;
	} 

	/* Print received message */
	printf("C1: %s\n", szBuffer);

	/* Sending new message */
	send(sockNewDescriptor, "Hello client!\n", 128 - 1, MSG_DONTWAIT);

	/* Receiving next message */
	recv(sockNewDescriptor, szBuffer, 128 - 1, 0);
	printf("C2: %s\n", szBuffer);

	/* Send next message */
	send(sockNewDescriptor, "Im good!\n", 128 - 1, MSG_DONTWAIT);

	/* Close the sockets, then assign a secure exit value */
	close(sockServerDescriptor); sockServerDescriptor = -1;
	close(sockNewDescriptor); sockNewDescriptor = -1;

	return iStatusCode;
}

int main(void){
	int iErrorDetected = RunServer(); 

	if(iErrorDetected != 0){
		berror("Server crashed - errcode: %d", iErrorDetected);			
		return 1;
	}

	return 0;
}

