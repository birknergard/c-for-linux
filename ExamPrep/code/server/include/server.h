#ifndef SERVER_H
#define SERVER_H

#define MAX_HEADER 72
#define MAX_BODY 2048
#define MAX_PACKET 2120 
	
/* BSCP stands for "Birk Server Client Protocol".*/
#pragma pack(1)

/* Max size of 5-8 Bytes */
typedef struct _BSCP_HEADER {
	int iDataSize; /* 4 Bytes */
	char cAction; /* 1 Byte */
} BSCP_HEADER;

#pragma pack()

/* Packet sent after with header. Max size 2120 BYTES */
typedef struct _BSCP_PACKET {
	BSCP_HEADER Header; /* 72 Bytes */
	char szBody[MAX_BODY]; /* 2048 Bytes */
} BSCP_PACKET;

int HandleRequest(BSCP_PACKET bscpPacket);
int RunServer();
	
#endif /* SERVER_H */
