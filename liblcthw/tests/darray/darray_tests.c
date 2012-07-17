#include "darray/darray.h"
#include "sort/sort.h"

#include "misc/misc.h"
#include "misc/dbg.h"
#include "minunit.h"

#include<string.h>
#include<stdlib.h>
#include <assert.h>

static DArray* array;
#define CONTLEN 67
static int *content[CONTLEN];

void content_init()
{
  for (size_t i = 0; i < CONTLEN; i++) {
    content[i] = malloc(sizeof(int*));
    *(content[i]) = i;
  }
}

/*
  return 1/0/-1 on equal/not/equal/error
*/
int content_equal(DArray *array1, DArray *array2)
{
  INV_DARRAY(array1);
  INV_DARRAY(array2);

  if (array1->count != array2->count) {
    printf("darrays differ in length\n");
    goto nonequal;
  } 

  for (size_t i = 0; i < array1->count; i++)
    if (*(int *)array1->contents[i] != *(int *)array2->contents[i]) {
      printf("darrays differ at position [%ld]\n", i);
      goto nonequal;
    }

  return 1;
 nonequal:
  return 0;
 error:
  return -1;
}

inline static void DArray_print(DArray *array)
{
  INV_DARRAY(array);

  for (size_t i = 0; i < array->count; i++) {
    printf("array[%ld] = %d\n", i, *((int *)(array->contents[i])));
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
  
  for (size_t i = 0; i < CONTLEN; i++) {
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
  
  for (size_t i = 0; i < CONTLEN + 1; i++)
    if ((el = DArray_pop(array))) printf("popped *el = %d\n", *el);

  INV_DARRAY(array);

  printf("print exhausted darray:\n");
  DArray_print(array);

  printf("(done.)\n");
  return NULL;
 error:
  return "DArray_pop failed";
}

void *test_bubble_sort()
{
  void **tmp;
  printf("test_bubble_sort()\n");
  printf("------------------\n");

  
  INV_DARRAY(array);
  tmp = bubble_sort((void **)array->contents, array->count, &cmp_TYPE_lt);
  INV_DARRAY(array);
  assert(tmp == array->contents);

  printf("print bubble-sorted darray:\n");
  DArray_print(array);

  printf("(done.)\n");
  return NULL;
 error:
  return "bubble_sort(DArray) failed";
}

void *test_merge_sort()
{
  DArray *result;
  void **result_contents;
  void **tmp;

  printf("test_merge_sort()\n");
  printf("-----------------\n");

  INV_DARRAY(array);
  result = DArray_create(array->element_size, array->max);
  check_mem(result);

  for (size_t i = 0; i < array->count; i++)
    result->contents[i] = array->contents[i];
  result->max = array->max;
  result->count = array->count;
  result->expand_rate = array->expand_rate;
  INV_DARRAY(result);

  result->contents = bubble_sort(result->contents, result->count, &cmp_TYPE_lt);
  INV_DARRAY(result);
  
  INV_DARRAY(array);
  tmp = array->contents;
  result_contents = merge_sort(array->contents, array->count, &cmp_TYPE_lt);
  array->contents = result_contents;
  INV_DARRAY(array);
  
  check(content_equal(array, result), "bubble sort and merge sort results differ");
  cfree(result_contents);
  array->contents = tmp;

  DArray_destroy(&result);

  printf("(done.)\n");
  return NULL;
 error:
  printf("print failed merge-sorted darray:\n");
  DArray_print(array);
  return "merge_sort(DArray) failed";
}

void *all_tests()
{
  content_init();
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
  mu_run_test(test_darray_pop);
  mu_run_test(test_darray_pop); /* pop until darray is exhausted */
  mu_run_test(test_darray_destroy); /* destroy exhausted darray */
  if (array) return "array is not NULL after DArray_destroy()\n";
  mu_run_test(test_darray_destroy); /* destroy destroyed darray */
  if (array) return "array is not NULL after DArray_destroy()\n";
  mu_run_test(test_darray_create); /* push does not create darray */
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_push);
  mu_run_test(test_bubble_sort);
  mu_run_test(test_bubble_sort);
  mu_run_test(test_darray_destroy);
  if (array) return "array is not NULL after DArray_destroy()\n";
  mu_run_test(test_darray_create); /* push does not create darray */
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_push);
  mu_run_test(test_darray_push);
  mu_run_test(test_merge_sort);
  mu_run_test(test_merge_sort);
  mu_run_test(test_darray_destroy);
  if (array) return "array is not NULL after DArray_destroy()\n";
  NL;

  return NULL;
}

RUN_TESTS(all_tests);

