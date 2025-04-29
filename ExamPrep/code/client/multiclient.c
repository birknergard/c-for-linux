#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../bexam_lib/include/debug.h"
#include "multiclient.h"

int RunMultiClient(char szMessage[]){
	int sockClientDescriptor;
	struct sockaddr_in saClientAddress;
	BSCP_PACKET bscpPacket;
	char szResponse[2048];
	int iConnected, iSent, iReceived;
	
	sockClientDescriptor = -1;

	/* Set client socket */
	sockClientDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(sockClientDescriptor < 0){
		berror("socket() failed - errcode %d", errno);
		return ERROR;
	}

	saClientAddress.sin_family = AF_INET;
	saClientAddress.sin_port = htons(8080);
	saClientAddress.sin_addr.s_addr = htonl(0x7F000001);
	
	if((iConnected = connect(
		sockClientDescriptor,
		(struct sockaddr *) &saClientAddress,
		sizeof(saClientAddress)
	)) < 0){
		berror("Failed to connect to server - errcode %d", errno);
		close(sockClientDescriptor); sockClientDescriptor = -1;
		return ERROR;
	} 

	bscpPacket = (BSCP_PACKET) {0};
	memset(bscpPacket.szBody, 0, 2048);
	strncpy(bscpPacket.szBody, szMessage, 127);
	bscpPacket.szBody[128] = '\0';

	if((iSent = send(
		sockClientDescriptor,
	   	&bscpPacket,
	   	sizeof(BSCP_PACKET),
	   	MSG_DONTWAIT
	)) < 0){
		berror("Failed to send request - errcode %d", errno);
		close(sockClientDescriptor); sockClientDescriptor = -1;
		return ERROR;
	} 

	if((iReceived = recv(
		sockClientDescriptor,
		szResponse, 2048, 0
	)) < 2){
		berror("Failed to receive response from server - errcode %d", errno);
		close(sockClientDescriptor); sockClientDescriptor = -1;
		return ERROR; 
	} 

	printf("RESPONSE=%s\n", szResponse);
	close(sockClientDescriptor); sockClientDescriptor = -1;

	return OK;
}

int main(int iArgC, char **apszArgV){
	int iStatus;

	iStatus = RunMultiClient(apszArgV[1]);
	if(iStatus != 0){
		printf("Server exited with error: %d\n", iStatus);
		return 1;
	}

	return 0;
}
