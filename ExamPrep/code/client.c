#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include "debug.h"

int SendRequest(){

}

int RunClient(){
	int sockClientDescriptor, iConnection, iErrorCode;
	struct sockaddr_in saClientAddress = { 0 };

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
		saClientAddress.sin_port = htons(80);
		saClientAddress.sin_addr.s_addr = 0x100000F7;
		
		iConnectionStatus = connect(
			sockClientDescriptor,
			&saAddr,
			sizeof(saAddr)
		);

		if(iConnectionStatus < 0){
			iErrorCode = errno;
			berror("connect() failed - errcode %d", iErrorCode);
		} else {

			send(sockClientDescriptor, "Hello server!", 32, 0);
			if(sockClientDescriptor < 0){
				iErrorCode = errno;
				berror("write to socket faield - errcode %d", iErrorCode);
			} /* Send was successful */
		} /* Establishshed connection */
	} /* Generated socket */

	if(iErrorCode != 0)
		return iErrorCode;

	/* Dont want to return "error" code when its not an error. Return OK (0) instead. */
	return OK;
}

int main(){

}
