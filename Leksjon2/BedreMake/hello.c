#include <stdio.h>

// extern void print_number (int i);
#include "number.h"

void main (void)
{
   printf ("Hello class!!\n");

   print_number (1);
   print_number (5);

   for (int i = 0; i < 5; i++) {
      print_number(i);
   }
}


