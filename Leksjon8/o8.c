#include <stdio.h>
#include <stdlib.h>

typedef union _GENERIC{
	unsigned short usPort1:16;
	unsigned short usPort2:16;
} PORT;
#pragma pack(1)
typedef struct {
	unsigned short usLength:16;
	unsigned short usChecksum:16;
} UDP_HEADER;

typedef struct {
	unsigned long ulSequenceNum: 32;
	unsigned long ulAckSet: 32;

	unsigned uOffset: 4;
	unsigned uReserved: 4;
	unsigned CWR:1;
	unsigned ECE:1;
	unsigned URG:1;
	unsigned ACK:1;
	unsigned PSH:1;
	unsigned RST:1;
	unsigned SYN:1;
	unsigned FIN:1;
	unsigned short usWindowSize: 16;

	unsigned short usChecksum:16;
	unsigned short usUrgentPointer:16;

} TCP_HEADER;

typedef struct{
	PORT Port;
	UDP_HEADER udpHeader;

} UDP_PACKET;

typedef struct{
	PORT Port;
	TCP_HEADER tcpHeader;

} TCP_PACKET;
#pragma pack ()

int parse_tcp_header(TCP_PACKET packet){

	return 0;
}
int parse_udp_header(UDP_PACKET packet){

	return 0;
}

int main(void){

	return 0;
}
