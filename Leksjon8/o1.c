/*
Exercise 1:
Make a header-parser for TGA files that reports:
x-pixels
y-pixels
compression?
truecolor?
*/

#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)
typedef struct{
	unsigned uIdLen:8;
	unsigned uColorMapType:8; 
	unsigned uImageType:8;
	/* Color map spec */
	unsigned uiFirstEntryIndex:16;
	unsigned uiColorMapLength:16;
	unsigned uColorMapEntrySize:8;

	/* Image spec */
	unsigned uiYOrigin:16;
	unsigned uiXOrigin:16;
	unsigned uiWidth:16;
	unsigned uiHeight:16;
	unsigned uPixelDepth:8;
	unsigned uAlphaChannel:2;
	unsigned uPixelOrdering:2;
	unsigned uRest:2;
	
} TGA_HEADER;
#pragma pack()

int main(void){
	FILE *fTGAFile;
	TGA_HEADER tgaHeader;

	fTGAFile = fopen("tga_sample.tga", "rb");
	fread(&tgaHeader, sizeof(TGA_HEADER), 1, fTGAFile);

	printf("RAW:\n");	
	printf("%u\n", tgaHeader.uIdLen);
	printf("%u\n", tgaHeader.uColorMapType);
	printf("%u\n", tgaHeader.uImageType);

	printf("%u\n", tgaHeader.uiFirstEntryIndex);
	printf("%u\n", tgaHeader.uiColorMapLength);
	printf("%u\n", tgaHeader.uColorMapEntrySize);

	printf("%u\n", tgaHeader.uiYOrigin);
	printf("%u\n", tgaHeader.uiXOrigin);
	printf("%u\n", tgaHeader.uiWidth);
	printf("%u\n", tgaHeader.uiHeight);
	printf("%u\n", tgaHeader.uPixelDepth);
	printf("%u\n", tgaHeader.uAlphaChannel);
	printf("%u\n", tgaHeader.uPixelOrdering);
	printf("\n\n");	

	
	printf("-> compressed? %s\n", tgaHeader.uImageType < 9 ? "YES" : "NO");	
	printf("-> x pixels? %u pixels\n", tgaHeader.uiWidth);
	printf("-> y pixels? %u pixels\n", tgaHeader.uiHeight);
	printf("-> truecolor? %s\n", tgaHeader.uImageType % 2 == 0 ? "YES" : "NO");

	fclose(fTGAFile);


	return 0;
}
