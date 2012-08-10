#include <stdint.h>
#include <stdio.h>

#include "liblcthw/src/misc/misc.h"

int main(int argc, char *argv[]) 
{
  uint8_t bit8 = 0b00000110;
  /* uint8_t i = (UINT8_MAX >> 1) + 1; */
  uint8_t i = 1 << 7;

  printf("i = %d\n", i);

  while (i) {
    if (bit8 & i) 
      printf("1");
    else
      printf("0");
    i = i >> 1;
  }
  NL;  

  printf("UNIT8_MAX = %d, 0b10000000 = %d\n", UINT8_MAX, 0b10000000);

 error:
  return 0;
}

