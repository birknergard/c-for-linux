#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../bexam_lib/include/debug.h"
#include "server.h"

#define PORT 8080

int HandleRequest(BSCPRequest *bscpData){
	void *vpProtocolData;
	vpProtocolData = NULL;

	if(bscpData == NULL || bscpData->Header == NULL || bscpData->szDataContainer == NULL){
		berror("Invalid protocol.");
		return ERROR;
	}

	return OK;
}

int RunServer(){
	/* Declaring variables */
	int sockServerDescriptor, sockNewDescriptor;
	int iNewAddressLength;
	int iStatusCode, iListened;
	int bBindSuccessful;
	char szBuffer[MAX_MESSAGE_SIZE];
	HEADER *pHeaderBuffer;

	/* If unchanged, return error free. */
	iErrorCode = 0;

	/* Allocate to header buffer */
	pHeaderBuffer = NULL;
	pHeaderBuffer = (BCSPRequest *) malloc(sizeof(BCSPRequest));
	if(pHeaderBuffer == NULL){
		berror("Could not allocate to header buffer.")
		return 1;
	}
		

	/* Open network socket (TCP/IP Protocol), as a stream */
	sockServerDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	sockNewDescriptor = 0;

	if(sockServerDescriptor < 0){
		iStatusCode = errno;
		berror("Error when opening socket - errcode: %d", iStatusCode);
	} else {
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

		} else {

			/* Make server listen for input */
			iListened =	listen(sockServerDescriptor, 2);
			if(iListened < 0){
				iStatusCode = errno;
				berror("Listen failed - errcode: %d", iStatusCode);
			} else {
				/* Initialize client socket address to zero */
				sockNewDescriptor = 0;
				iNewAddressLength = sizeof(saClientAddress); 

				/* Accept connection from client */
				sockNewDescriptor = accept(
					sockServerDescriptor,
					(struct sockaddr *) &saClientAddress,
					(socklen_t *) &iNewAddressLength
			

				/* Does not continue if accept failed */
				if(sockNewDescriptor < 0){
					iStatusCode = errno;
					berror("Error with accept() - errcode: %d", iStatusCode);	
				} else {
					recv(sockNewDescriptor, pHeaderBuffer, MAX_MESSAGE_SIZE - 1, MSG_DONTWAIT);
					if(sockNewDescriptor < 0){
						iErrorCode = errno;
						berror("Error reading message data - errcode: %d", iStatusCode);
					} else {
						printf("Message received!\n from %p:%d -> %s\n", saClientAddress.sin_addr, PORT, szBuffer);
					
						if(pHeaderBuffer->iDataSize <= MAX_REQUEST_SIZE){
							

							HandleRequest();
						}

					}
				}
			}
		}
	}


	/* Close the sockets */
	close(sockServerDescriptor);
	close(sockNewDescriptor);

	return iErrorCode;
}

int main(void){
	int iErrorDetected = RunServer(); 

	if(iErrorDetected != 0){
		berror("Server crashed - errcode: %d", iErrorDetected);			
		return 1;
	}

	return 0;
}

