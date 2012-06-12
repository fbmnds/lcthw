#include <stdio.h>
#include <string.h>

#define NUMSTATES 5

int main (int argc, char * argv[])
{
  int sum = 0, i;
  char* states[] = {"New York", "California", "New Mexico", "Arizona", "Iowa"};

  for (i = 1; i < argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]);

  printf("+-------------------------+-----------------------+\n");
  for (i = 0; i < NUMSTATES; i++) {
    printf("\t\t\t  | strlen(states[%d] = %2ld |\r| states[%d] = %s, \n", 
	   i, strlen(states[i]), 
	   i, states[i]);
    sum += strlen(states[i]);
  }
  printf("+-------------------------+-----------------------+\n");
  printf("\t\t\t    sum(strlen)      = %d\n", sum);
  printf("\t\t\t    sizeof(states)   = %ld\n", sizeof(states));
  
  return 0;
}
