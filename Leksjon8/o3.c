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
	unsigned int *iarr;
	unsigned int *ipWriter;
	unsigned int iCurrentPosition;


} RING_BUFFER;
#pragma pack ()

void ringbuf_init(RING_BUFFER *pRingBuffer){
	printf("Initializing.\n");
	pRingBuffer->iarr = (unsigned int *) malloc(sizeof(unsigned int) * 8);
	pRingBuffer->ipWriter = &pRingBuffer->iarr[0];
	pRingBuffer->iCurrentPosition = 0;
}

void ringbuf_destroy(RING_BUFFER *pRingBuffer){
	free(pRingBuffer->iarr);
	free(pRingBuffer);
}

void ringbuf_write(RING_BUFFER *pRingBuffer, int iValue){
	*pRingBuffer->ipWriter = iValue;
}

unsigned int ringbuf_read(RING_BUFFER *pRingBuffer){
	return *pRingBuffer->ipWriter;
}

void ringbuf_shift(RING_BUFFER *pRingBuffer, int iShiftInput){
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
	for(i = 0; i < abs(iShiftInput); i++){
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
	pRingBuffer->ipWriter = &pRingBuffer->iarr[iPosition];
}


int main(void){
	RING_BUFFER *pRingBuffer;
	pRingBuffer = (RING_BUFFER*) malloc(sizeof(RING_BUFFER));
	if(pRingBuffer == NULL) return 1;

	int i;

	ringbuf_init(pRingBuffer);
	for(i = 0; i < 8; i++){
		ringbuf_write(pRingBuffer, i);	
		ringbuf_shift(pRingBuffer, 1);	
	}

	printf("RingBuffer: ");
	for(i = 0; i < 8; i++){
		printf(" %d", ringbuf_read(pRingBuffer));
		ringbuf_shift(pRingBuffer, 1);	
	}
	printf("\n");

	ringbuf_shift(pRingBuffer, 50); /* should shift by 2*/;
	printf("shift by 50 %d\n", ringbuf_read(pRingBuffer));
	
	ringbuf_shift(pRingBuffer, -12); /* Should shift left by 4 */
	printf("shift by -12 %d\n", ringbuf_read(pRingBuffer));

	ringbuf_shift(pRingBuffer, -3); /* Should shift left by 4 */
	printf("shift by -3 %d\n", ringbuf_read(pRingBuffer));

	ringbuf_shift(pRingBuffer, 4); /* Should shift left by 4 */
	printf("shift by 4 %d\n", ringbuf_read(pRingBuffer));
	
	ringbuf_destroy(pRingBuffer);

	return 0;
}

