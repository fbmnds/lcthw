#include "hashmap/hashmap.h"

#include "misc/misc.h"
#include "misc/dbg.h"
#include "minunit.h"

#include <stdio.h>
#include <stdlib.h>

void *test_hashmap_1()
{
  hashmap *hm;
  int *data;
  unsigned long i;

  printf("test_hashmap_1()\n");
  printf("----------------\n");

  check_mem(hm = hashmapCreate(1000));
;

  for (i = 0; i < 1024; i++) {
    check_mem(data = malloc(sizeof(int)));
    *data = (int) i;
    hashmapInsert(hm, data, i);
  }
  
  check((unsigned long) hashmapCount(hm) == i, 
	"hashmapCount %ud != i %ud", hashmapCount(hm), i);

  hashmapDelete(hm);
  
  printf("(done.)\n");
  return NULL;
 error:
  return "test_hashmap_1() failed";
}

void *all_tests()
{
  mu_suite_start();
  mu_run_test(test_hashmap_1);
  //mu_run_test(test_hashmap_2);

  return NULL;
}

RUN_TESTS(all_tests);

