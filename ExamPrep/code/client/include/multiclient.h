#ifndef CLIENT_H 
#define CLIENT_H 
/* Max size of 5-8 Bytes depending on padding */
typedef struct _BSCP_HEADER {
	int iDataSize; /* 4 Bytes */
	char cAction; /* 1 Byte */
} BSCP_HEADER;

/* Packet sent after with header. Max size 2120 BYTES */
#pragma pack(1)
typedef struct _BSCP_PACKET {
	BSCP_HEADER Header; /* 5-8 Bytes */
	char szBody[2048]; /* 2048 Bytes */
} BSCP_PACKET;
#pragma pack()

#define OK 0

int Ping();
int RunMultiClient(char szMessage[]);

#endif /* CLIENT_H */

