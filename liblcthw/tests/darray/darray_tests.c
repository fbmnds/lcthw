#include "darray/darray.h"

#include "misc/misc.h"
#include "misc/dbg.h"
#include "../minunit.h"

#include<string.h>
#include<stdlib.h>
#include <assert.h>

static DArray* array;
#define CONTLEN 300
static int *content[CONTLEN];

void init_content()
{
  for (int i = 0; i < CONTLEN; i++) {
    content[i] = malloc(sizeof(int*));
    *(content[i]) = i;
  }
}

void *test_darray_create()
{
  printf("test_darray_create()\n");
  printf("--------------------\n");

  array = DArray_create(sizeof(int*), (size_t) DEFAULT_EXPAND_RATE);

  check((array), "DArray_create returned NULL");
  

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_create failed";
}

void *test_darray_destroy()
{
  int rc;
  printf("test_array_destroy()\n");
  printf("--------------------\n");
  
  rc = DArray_destroy(&array);
  check(!rc, "DArray_destroy return code = %d", rc);

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_destroy failed";
}

void *all_tests()
{
  init_content();
  mu_suite_start();
  mu_run_test(test_darray_create);
  mu_run_test(test_darray_destroy);
  if (array) return "array is not NULL after DArray_destroy()\n";
  mu_run_test(test_darray_destroy); /* destroy empty darray */
  mu_run_test(test_darray_create);
  //mu_run_test(test_darray_clear); /* clear empty darray */
#if 0
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_pop);
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_pop);
  mu_run_test(test_darray_pop);
  mu_run_test(test_darray_pop); /* pop until darray is exhausted */
  mu_run_test(test_darray_destroy); /* destroy exhausted darray */
  if (array) return "array is not NULL after DArray_destroy()\n";
  mu_run_test(test_darray_destroy); /* destroy destroyed darray */
  if (array) return "array is not NULL after DArray_destroy()\n";
  mu_run_test(test_darray_push); /* push creates darray, if necessary */
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_push);
  mu_run_test(test_create_index);
  mu_run_test(test_merge_sort);
  mu_run_test(test_merge_sort);
#endif
  mu_run_test(test_darray_destroy);
  if (array) return "array is not NULL after DArray_destroy()\n";
  NL;

  return NULL;
}

RUN_TESTS(all_tests);

