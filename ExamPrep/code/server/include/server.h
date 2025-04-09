#ifndef SERVER_H
#define SERVER_H

#define MAX_HEADER_SIZE 72
#define MAX_MESSAGE_SIZE 2048
	
typedef struct _HEADER {
	char szType[64];
	int iDataSize;
	char cAction;
} HEADER;

/* BSCP stands for "Birk Server Client Protocol" */
typedef struct _BSCPRequest {
	HEADER Header;
	char szDataContainer[MAX_MESSAGE_SIZE];
} BSCPRequest;

int HandleRequest(BSCPRequest *bscpRequest, int iDataSize);
int RunServer();
	
#endif /* SERVER_H */
