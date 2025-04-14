#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../bexam_lib/include/debug.h"
#include "client.h"

int RunClient(){
	int sockClientDescriptor, iConnectionStatus, iErrorCode;
	struct sockaddr_in saClientAddress;
	char szResponse[128];

	/* Changes when error occurs, stays 0 if not */
	iErrorCode = 0;
	
	/* Set client socket */
	sockClientDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	/* Check if successful */
	if(sockClientDescriptor < 0){
		iErrorCode = errno;
		berror("socket() failed - errcode %d", iErrorCode);
	} else {
		saClientAddress.sin_family = AF_INET;
		saClientAddress.sin_port = htons(8080);
		saClientAddress.sin_addr.s_addr = htonl(0x7F000001);
		
		iConnectionStatus = connect(
			sockClientDescriptor,
			(struct sockaddr *) &saClientAddress,
			sizeof(saClientAddress)
		);

		if(iConnectionStatus < 0){
			iErrorCode = errno;
			berror("connect() failed - errcode %d", iErrorCode);
		} else {
			send(sockClientDescriptor, "Hello server!", 128 - 1, MSG_DONTWAIT);

			if(sockClientDescriptor < 0){
				iErrorCode = errno;
				berror("write to socket failed - errcode %d", iErrorCode);
			} else {

				memset(szResponse, 0, 128);
	  			recv(sockClientDescriptor, szResponse, 128 - 1, 0); 
				printf("S1: %s\n", szResponse);

				send(sockClientDescriptor, "How are you server?", 128 - 1, MSG_DONTWAIT);

				recv(sockClientDescriptor, szResponse, 128 - 1, 0);
				printf("S2: %s\n", szResponse);

			}/* Send was successful */
		} /* Establishshed connection */
	} /* Generated socket */

	close(sockClientDescriptor);

	if(iErrorCode != 0)
		return iErrorCode;

	/* Dont want to return an "error" code when its not an error.
	* Return OK (0) instead. This is purely semantic and for code readability */
	return OK;
}

int main(int iArgC, char **apszArgV){
	int iStatus;
	iStatus = RunClient();
	if(iStatus != 0){
		printf("Server exited with error: %d\n", iStatus);
		return 1;
	}

	return 0;
}
