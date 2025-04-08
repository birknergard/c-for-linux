#ifndef SERVER_H
#define SERVER_H
	#define MAX_MESSAGE_SIZE 128 
	
	#typedef struct _HEADER{
		int iDataSize;
		char cAction;
		char cType;
	} HEADER;

	#typedef struct _BPROTOCOL{
		HEADER bHead;
		void *vpData;
	} BPROTOCOL;

	int HandleRequest(BPROTOCOL *bpRequest);
	int RunServer();
	
#endif /* SERVER_H */
