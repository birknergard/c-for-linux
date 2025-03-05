/*
Excercise 4

In this zip file you will find an C implementation of the MD5-algorith.
The code you'll find here does also include an example on how to use itIn the
folder "Md5" you can run the makefile, then the program md5_test. Do not attempt
(in other words, by all means, do attempt, but it isn't really necessary) to understand
the code in md5.c. What you will need to understand is HOW to use the functions:

   MD5_CTX ctx;      // Needed by the library.
   BYTE hash[16];    // BYTE is defined in md5.h as "typedef unsigned char BYTE"

   md5_init(&ctx);   // Initialize the ctx.

   md5_update(&ctx, text, strlen(text));  // Add text to the hash

   while (we have some data) {
      md5_update(&ctx, data, lenght);     // This can be repeated...
   }

   md5_final(&ctx, hash); // When all data is added, finalize and get the hash

At this point we have a 16 byte buffer containing the hash value.

Then the exercise:

Then make a small program that does the following:

   md5 -add <filename>    - Calculate the MD5 checksum of the file (named filename) and
                            add it as a binary blob at the end of the file.

   md5 -test <filename>   - Calculate the MD5 checksum of the file and test if the checksum
                            at the end of the file is the correct one.

   md5 -strip <filename>  - Same as test, but strip off the checksum at the end of the file.

More details:

So the program should read a file into memory, calculate the MD5-checksum and either add the
checksum to the end of the file, test if the MD5 is the same as one previously added to
the file or, as a third alternative test, then strip off the checksum previously added to the
file. I would start making a program that just reads a given file into memory, calculates the
checksum and prints it in the screen. You will find an example in the Md5-folder.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Leksjon6/md5/md5.h"

void AddHash(FILE *fpChecksum, char *szText);
void TestHash(FILE *fpChecksum);
void StripHash(FILE *fpChecksum);

int main(int iArgC, char **apszArgV){
	FILE *fpChecksum;
	fpChecksum = NULL;

	fpChecksum = fopen("./o4_checksum.bin", "bw+");
	
	fclose(fpChecksum);

	AddHash(fpChecksum, apszArgV[1]);

		

	return 0;
}

void AddHash(FILE *fpChecksum, char *szText){
	MD5_CTX ctx;
	BYTE aucHash[16];

	md5_init(&ctx);   // Initialize the ctx.
	md5_update(&ctx, szText, strlen(szText));  // Add text to the hash
	md5_final(&ctx, aucHash); // When all data is added, finalize and get the hash

	fwrite(aucHash, 16, 1, fpChecksum);
}

void TestHash(FILE *fpChecksum){
	MD5_CTX ctx;
	char *szBuffer;
	BYTE aucHash[16];

	szBuffer = (char*) malloc(16);


	// Read bitstream, specifically the last pointer of the bitstream if it exists.
	fread(szBuffer, 16, 1, fpChecksum);

	free(szBuffer);

}

