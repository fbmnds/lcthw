#include <stdio.h>

int main (int argc, char * argv[])
{
  /*
 - ex7.c:1-4 The usual start of a C program.
 - ex7.c:5-6 Declare an int and double for some fake bug data.
 - ex7.c:8-9 Print out those two, so nothing new here.
 - ex7.c:11 Declare a huge number using a new type long for storing big numbers.
 - ex7.c:12-13 Print out that number using %ld which adds a modifier to the usual %d. Adding ’l’ (the letter ell) means "print this as a long decimal".
 - ex7.c:15-17 Just more math and printing.
 - ex7.c:19-21 Craft up a depiction of your bug rate compared to the bugs in the universe, which is a completely inaccurate calculation. It’s so small though that we have to use %e to print it in scientific notation. 
 - ex7.c:24 Make a character, with a special syntax '\0' which creates a ’nul byte’ character. This is effectively
the number 0.
 - ex7.c:25 Multiply bugs by this character, which produces 0 for how much you should care. This demonstrates an ugly hack you find sometimes.
 - ex7.c:26-27 Print that out, and notice I’ve got a %% (two percent chars) so I can print a ’%’ (percent) character.
 - ex7.c:28-30 The end of the main function.
   */  
  int bugs = 9;
  double bug_rate = 1.2;
  long bugs_universe = 1L * 1024 * 1024 * 1024;
  double expected_bugs = bugs * bug_rate;
  double universe_bug_rate = (double) bugs / bugs_universe;
  char nul_byte = '\0';
  
  printf ("The code contains %d bugs whichs relate to a bug rate of %.2f %%.\n", 
	  bugs, bug_rate);
  
  printf("The universe contains %ld bugs.\n", bugs_universe);
  
  printf("The number of expected bugs id %.2f.\n", expected_bugs);
  
  printf("The %d bugs are a percentage of %e %% of the total bug universe.\n",
	 bugs, universe_bug_rate);
  
  printf("Multiplying with nul_byte achieves %d.\n", bugs * nul_byte);
  

  return 0;
}
