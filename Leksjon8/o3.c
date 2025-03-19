/*
Exercise 3:

A ring buffer is something of a queue that has the front and back connected.
Write a function that lets you initialize a ring buffer with binary elements
and that has the following operations. You can assume that the buffer has 8
elements exactly

-shift left by n units-
-shift right by n units-
*/

#include <stdio.h>
#include <stdlib.h>

#pragma pack (1)
typedef struct {
	int *iarr;
	unsigned int iCurrentPosition;


} RING_BUFFER;
#pragma pack ()

void ringbuf_init(RING_BUFFER *pRingBuffer){
	printf("Initializing.\n");
	pRingBuffer = (RING_BUFFER*) malloc(sizeof(RING_BUFFER));
	pRingBuffer->iarr = (int *) malloc(sizeof(int) * 8);
	pRingBuffer->iCurrentPosition = 0;
}

void ringbuf_destroy(RING_BUFFER *pRingBuffer){
	free(pRingBuffer->iarr);
	free(pRingBuffer);
}

void ringbuf_write(RING_BUFFER *pRingBuffer, int iValue){
	printf("DEBUG: Writing ...\n");
	
	pRingBuffer->iarr[pRingBuffer->iCurrentPosition] = iValue;
}

int ringbuf_read(RING_BUFFER *pRingBuffer){
	return pRingBuffer->iarr[pRingBuffer->iCurrentPosition];
}

void ringbuf_shift(RING_BUFFER *pRingBuffer, int iShiftInput){
	printf("DEBUG: Starting shift\n");
	int iPosition, iShiftBy, i;

	iPosition = pRingBuffer->iCurrentPosition;

	/* If shift = 8 the position will be the same, therefore we do nothing */
	if(iShiftInput == 8){
		return;
	}

	/* If shift is greater than 8 we need to shift by the remainder to avoid excessive looping */
	if(iShiftBy > 8 || iShiftBy < -8){
		iShiftBy = iShiftInput % 8;	
	}
	
	/* Shifting n times, negative or positive only indicates direction */
	for(i = 0; i > abs(iShiftInput); i++){
		printf("DEBUG: Shifting ...\n");
		/* Behavior is different when number is negative... */
		if(iShiftInput < 0){
			if(iPosition == -1){
				iPosition = 7;	
			}
			--iPosition;
		}

		/* vs. positive */
		if(iShiftInput > 0){
			if(iPosition == 8){
				iPosition = 0;	
			}
			++iPosition;
		}
	}

	pRingBuffer->iCurrentPosition = iPosition;
}


int main(void){
	RING_BUFFER *pRingBuffer;
	int i;

	ringbuf_init(pRingBuffer);
	for(i = 0; i < 8; i++){
		ringbuf_write(pRingBuffer, i);	
		ringbuf_shift(pRingBuffer, 1);	
	}

	printf("RingBuffer: ");
	for(i = 0; i < 8; i++){
		ringbuf_shift(pRingBuffer, 1);	
		printf(" %d", ringbuf_read(pRingBuffer));
	}
	printf("\n");
	

	ringbuf_destroy(pRingBuffer);

	return 0;
}

