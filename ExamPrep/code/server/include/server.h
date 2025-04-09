#ifndef SERVER_H
#define SERVER_H
	#define MAX_HEADER_SIZE 8
	#define MAX_MESSAGE_SIZE 2048
	
	#pragma pack(1)
	#typedef struct _HEADER{
		int iDataSize;
		char cAction;
		char cType;
	} HEADER;

	#typedef struct _BPROTOCOL{
		szDataContainer[MAX_MESSAGE_SIZE];
	} BPROTOCOL;
	#pragma pack()

	int HandleRequest(BPROTOCOL *bpRequest);
	int RunServer();
	
#endif /* SERVER_H */
