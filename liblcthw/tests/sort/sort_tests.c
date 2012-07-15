#include "sort/sort.h"
#include "darray/darray.h"

#include "misc/misc.h"
#include "misc/dbg.h"
#include "minunit.h"

#include<string.h>
#include<stdlib.h>
#include <assert.h>

int array_3[] = {2, 2, 0};
int array_4[] = {2, 1, 0, 3};
int array_5[] = {2, 1, 0, 0, 1};
int array_6[] = {2, 1, 2, 1, 0, 0};
int array_7[] = {2, 1, 0, 2, 0, 3, 1};
int array_8[] = {2, 1, 0, 2, 0, 3, 1, 3};
int array_9[] = {4, 2, 1, 0, 2, 0, 3, 1, 3};
int array_10[] = {4, 2, 1, 0, 4, 2, 0, 3, 1, 3};
int array_11[] = {4, 2, 1, 0, 5, 4, 2, 0, 3, 1, 3};

int res_array_3[] = {0, 2, 2};
int res_array_4[] = {0, 1, 2, 3};
int res_array_5[] = {0, 0, 1, 1, 2};
int res_array_6[] = {0, 0, 1, 1, 2, 2};
int res_array_7[] = {0, 0, 1, 1, 2, 2, 3};
int res_array_8[] = {0, 0, 1, 1, 2, 2, 3, 3};
int res_array_9[] = {0, 0, 1, 1, 2, 2, 3, 3, 4};
int res_array_10[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4};
int res_array_11[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5};

/*
  return 1 if equal/not equal
 */
inline static int array_equal(DArray *array1, int *array2, int count)
{
  for (int i = 0; i < count; i++)
    if (*(int *)(array1->contents[i]) != array2[i]) goto not_equal;
  
  return 1;
 not_equal:
  return 0;
}

int cmp_int_lt(void *vp1, void *vp2)
{
  int v1, v2;

  v1 = *(int*)vp1;
  v2 = *(int*)vp2;
  if (v1 < v2)
    return 1;
  else
    return 0;
  /*
 error:
  return -1;
  */
}

inline static void array_print(int *array, size_t count)
{
  for (size_t i = 0; i < count; i++)
    printf("array[%ld] = %d\n", i, array[i]);
  return;
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

DArray *init_darray(int *array, int count)
{
  DArray *darray = DArray_create(sizeof(int*), (size_t) count);

  INV_DARRAY(darray);

  for (int i = 0; i < count; i++)
    darray->contents[i] = array + i;
  darray->count = count;

  return darray;
 error:
  return NULL;
}

void *test_merge_sort_3()
{
  DArray *darray = init_darray(array_3, 3);

  printf("test_merge_sort_3()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 3, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_3, 3), "array_3 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_3() failed";
}

void *test_merge_sort_4()
{
  DArray *darray = init_darray(array_4, 4);

  printf("test_merge_sort_4()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 4, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_4, 4), "array_4 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_4() failed";
}

void *test_merge_sort_5()
{
  DArray *darray = init_darray(array_5, 5);

  printf("test_merge_sort_5()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 5, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_5, 5), "array_5 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_5() failed";
}

void *test_merge_sort_6()
{
  DArray *darray = init_darray(array_6, 6);

  printf("test_merge_sort_6()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 6, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_6, 6), "array_6 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_6() failed";
}

void *test_merge_sort_7()
{
  DArray *darray = init_darray(array_7, 7);

  printf("test_merge_sort_7()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 7, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_7, 7), "array_7 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_7() failed";
}

void *test_merge_sort_8()
{
  DArray *darray = init_darray(array_8, 8);

  printf("test_merge_sort_8()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 8, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_8, 8), "array_8 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_8() failed";
}

void *test_merge_sort_9()
{
  DArray *darray = init_darray(array_9, 9);

  printf("test_merge_sort_9()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 9, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_9, 9), "array_9 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_9() failed";
}

void *test_merge_sort_10()
{
  DArray *darray = init_darray(array_10, 10);

  printf("test_merge_sort_10()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 10, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_10, 10), "array_10 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_10() failed";
}

void *test_merge_sort_11()
{
  DArray *darray = init_darray(array_11, 11);

  printf("test_merge_sort_11()\n");
  printf("-------------------\n");

  darray->contents = (void **) merge_sort((void **)darray->contents, 11, &cmp_TYPE_lt);
  check(array_equal(darray, res_array_11, 11), "array_11 result mismatch");

  printf("(done.)\n");
  return NULL;
 error:
  printf("print merge-sorted failed result:\n");
  DArray_print(darray);
  return "test_merge_sort_11() failed";
}

void *all_tests()
{
  mu_suite_start();
  mu_run_test(test_merge_sort_3);
  mu_run_test(test_merge_sort_4);
  mu_run_test(test_merge_sort_5);
  mu_run_test(test_merge_sort_6);
  mu_run_test(test_merge_sort_7);
  mu_run_test(test_merge_sort_8);
  mu_run_test(test_merge_sort_9);
  mu_run_test(test_merge_sort_10);
  mu_run_test(test_merge_sort_11);
  NL;

  return NULL;
}

RUN_TESTS(all_tests);
