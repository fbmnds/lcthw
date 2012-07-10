#include "darray/darray.h"
#include "misc/misc.h"
#include "misc/dbg.h"
#include "minunit.h"

#include<string.h>
#include<stdlib.h>
#include <assert.h>

static DArray* array;
#define CONTLEN 65
static int *content[CONTLEN];

void init_content()
{
  for (int i = 0; i < CONTLEN; i++) {
    content[i] = malloc(sizeof(int*));
    *(content[i]) = i;
  }
}

inline static void DArray_print(DArray *array)
{
  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content");
  assert((array->max && (array->max >= array->count)) && 
	 "inconsistent array capacity");

  for (int i = 0; i < array->count; i++) {
    printf("array[%d] = %d\n", i, *((int *)(array->contents[i])));
  }

 error: /* fallthrough */
  return;
}

void *test_darray_create()
{
  printf("test_darray_create()\n");
  printf("--------------------\n");

  array = DArray_create(sizeof(int*), (size_t) DEFAULT_EXPAND_RATE);

  check((array), "DArray_create returned NULL");

  DArray_print(array);

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_create failed";
}

void *test_darray_destroy()
{
  int rc;
  printf("test_darray_destroy()\n");
  printf("---------------------\n");
  
  rc = DArray_destroy(&array);
  check(!rc, "DArray_destroy return code = %d", rc);

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_destroy failed";
}

void *test_darray_push()
{
  int rc;
  printf("test_darray_push()\n");
  printf("------------------\n");
  
  for (int i = 0; i < CONTLEN; i++) {
    rc = DArray_push(array, content[i]);
    check(!rc, "DArray_push return code = %d", rc);
  }

  DArray_print(array);

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_push failed";
}

void *test_darray_pop()
{
  int *el;
  printf("test_darray_pop()\n");
  printf("-----------------\n");
  
  for (int i = 0; i < CONTLEN + 1; i++)
    if (el = DArray_pop(array)) printf("popped *el = %d\n", *el);

  printf("print exhausted darray:\n");
  DArray_print(array);

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_pop failed";
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
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_pop);
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_pop);
#if 0
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

