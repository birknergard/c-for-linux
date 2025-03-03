/*
Exercise 1:

Read a text file full of double values and convert it into a binary file.
Write code that converts it back to double values as a text file.
*/

#include <stdio.h>
#include <stdlib.h>


int main(int iArgC, char **apszArgV){
	system("rm ./o1.txt");
	system("rm ./o1.bin");


	FILE *fpTextFile, *fpBinFile, *fpConvertedFile;
	long lFileSize;
	char *szSingleNum, *szFileContentsRaw;
	float *szFileContentsBin, *fNum, i;
	int j;

/*
Creating a file with a hundred numbers
*/
	fNum = (float *) malloc(sizeof(float));
	fpTextFile = fopen("./o1.txt", "w");

	for(i = 0; i < 100; i++ ){
		*fNum = i / 10;
		fprintf(fpTextFile, "%.1f ", *fNum);	
	}

	fclose(fpTextFile);

/*
Get size of file
*/
	fpTextFile = fopen("./o1.txt", "r");
	if(fpTextFile != NULL){
		if(fseek(fpTextFile, 0, SEEK_END) == 0){
			lFileSize = ftell(fpTextFile);
			rewind(fpTextFile);
		}	
	}

/*
store text file as local string	
*/
	szFileContentsRaw = (char *) malloc(lFileSize + 1);
	fgets(szFileContentsRaw, lFileSize, fpTextFile);
	fclose(fpTextFile);

	printf(szFileContentsRaw);
	
	fpBinFile = fopen("./o1.bin", "wb");
	szSingleNum = (char*) malloc(sizeof(char) * 3);
	for(j = 0; j < lFileSize; j+=4){
/*
temp store each number ...
*/
		szSingleNum[0] = szFileContentsRaw[j];
		szSingleNum[1] = '.';
		szSingleNum[2] = szFileContentsRaw[j + 2];

		*fNum = atof(szSingleNum);
		printf("\nszNum=%.1f", *fNum);
/*
insert num into binary file ...
*/
		fwrite(fNum, sizeof(float), 1, fpBinFile);	
	}

	fclose(fpBinFile);
	free(fNum);

/*
read binary file
*/
	fpBinFile = fopen("./o1.bin", "rb");
	int iElements;
	szFileContentsBin = (float*) malloc(sizeof(float) * 100);
	iElements = fread(szFileContentsBin, sizeof(float), 100, fpBinFile);

	if(iElements < 100){
		printf("\nERROR: Less elements read from binary file than expected (%d).", iElements);
		return 1;
	}

	fpConvertedFile = fopen("./o1-2.txt", "w+");
	printf("\n\nConverted binary numbers: ");
	for(j = 0; j < 100; j++){
		fprintf(fpConvertedFile, "%.1f ", szFileContentsBin[j]);
	}
	fclose(fpBinFile);
	fclose(fpBinFile);
	fclose(fpConvertedFile);

	
	free(szSingleNum);
	free(szFileContentsBin);
	free(szFileContentsRaw);

	return 0;
}
