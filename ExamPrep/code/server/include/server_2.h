#ifndef SERVER_H
#define SERVER_H

#define MAX_HEADER 8
#define MAX_BODY 2048
#define MAX_PACKET 2056
#define PORT 8080
	
/* BSCP stands for "Birk Server Client Protocol".*/

/* Max size of 5-8 Bytes depending on padding */
typedef struct _BSCP_HEADER {
	int iDataSize; /* 4 Bytes */
	char cAction; /* 1 Byte */
} BSCP_HEADER;

/* Packet sent after with header. Max size 2120 BYTES */
#pragma pack(1)
typedef struct _BSCP_PACKET {
	BSCP_HEADER Header; /* 5-8 Bytes */
	char szBody[MAX_BODY]; /* 2048 Bytes */
} BSCP_PACKET;
#pragma pack()

typedef struct _THREAD_DATA{
	int iThreadID;
	int **ppiThreadTracker;
	sem_t *semThreadReady;
	sem_t *semEditingTracker;
	int sockClientDescriptor;
} THREAD_DATA;

void *HandleRequest(void *tData);
int RunServer();
	
#endif /* SERVER_H */
