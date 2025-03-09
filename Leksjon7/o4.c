/*
Exercise 4:

Consider the following header : myalloc.h
===================================================================================
/* Multi-type memory allocation and initialization function.
        void *myalloc(const char *, ...);

        first argument accepts a string that has type and initialization flag.
        accepted types:
                char
                int
                float
        accepted flags:
                T or F

        second argument is the number of elements that need to be allocated.
        <if initialization flag is true>third argument - initialization value.

        returns a void * pointer.

        Example  Usage:
                int *p;
                p = (int *)myalloc("int T",100,4);
                //Gives you an array with 100 ints and all are 4

                float *p;
                p = (float *)myalloc("float F",200);
                //Gives you a float array with 200 floats unintialized

======================================================================================
Now assume you are an open source contributor and you are assigned to implement this.
How would you do this?

// An example on variable number of arguments:

#include <stdio.h>
#include <stdarg.h>

void simple_printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0') {
        if (*fmt == 'd') {
            int i = va_arg(args, int);
            printf("%d\n", i);
        } else if (*fmt == 'c') {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            printf("%c\n", c);
        } else if (*fmt == 'f') {
            double d = va_arg(args, double);
            printf("%f\n", d);
        }
        ++fmt;
    }

    va_end(args);
}

int main(void)
{
    simple_printf("dcff", 3, 'a', 1.999, 42.5);
}

Source: http://en.cppreference.com/w/c/variadic
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MAX_BUFFER 2048 

void *myalloc(const char *type, ...){
	int i, iCount;
	char *szTypeBuf, cInitFlag;

	va_list args;
	va_start(args, type);

	i = 0;
	szTypeBuf = (char*) malloc(MAX_BUFFER);

	/* Separate type string from flag */
	while(*type != ' '){
		szTypeBuf[i] = *type;
		++i;
		++type;
	}

	szTypeBuf[i] = '\0';

	while(*type != '\0'){
		cInitFlag = *type;
		++type;
	}


	printf("Type: [%s] -- Flag: %c", szTypeBuf, cInitFlag);
	iCount = va_arg(args, int);

	if(strcmp(szTypeBuf, "int") == 0){
		int *ptr;
		ptr = (int*) malloc(sizeof(int) * iCount);	
		if(ptr == NULL) return NULL;

		if(cInitFlag == 'T'){
			int iInitialValue = va_arg(args, int);
			for(i = 0; i < iCount; i++){
				ptr[i] = iInitialValue;	
			}
		}

		va_end(args);
		free(szTypeBuf);
		return ptr;

	} else if(strcmp(szTypeBuf, "char") == 0){
		char *ptr;
		ptr = (char*) malloc(sizeof(char) * iCount);	
		if(ptr == NULL) return NULL;

		if(cInitFlag == 'T'){
			char iInitialValue = va_arg(args, char);
			for(i = 0; i < iCount; i++){
				ptr[i] = iInitialValue;	
			}
		}

		va_end(args);
		free(szTypeBuf);
		return ptr;
		
	} else if(strcmp(szTypeBuf, "float") == 0){
		float *ptr;
	 	ptr = (float*) malloc(sizeof(char) * iCount);	
		if(ptr == NULL) return NULL;

		if(cInitFlag == 'T'){
			float iInitialValue = va_arg(args, float);
			for(i = 0; i < iCount; i++){
				ptr[i] = iInitialValue;	
			}
		}
		
		va_end(args);
		free(szTypeBuf);
		return ptr;

	} else {
		puts("\nERROR: Incorrect type flag. Returning NULL pointer");	
		return NULL;
	}

}

int main(void){
	int *ptr, i;
	ptr = (int*)myalloc("int T", 100, 10);
	printf("\nPointer: %X -> ", ptr);

	for(i = 0; i < 100; i++){
		printf(" %d", ptr[i]);	
	}
	
	free(ptr);
}


