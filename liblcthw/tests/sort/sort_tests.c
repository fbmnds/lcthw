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
inline static int array_equal(DArray *array1, int *array2, size_t count)
{
  for (size_t i = 0; i < count; i++)
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

DArray *darray_init(int *array, size_t count)
{
  DArray *darray = DArray_create(sizeof(int*), count);

  INV_DARRAY(darray);
  
  for (size_t i = 0; i < count; i++)
    darray->contents[i] = &array[i];
  darray->count = count;

  INV_DARRAY(darray);
 
 return darray;
 error:
  return NULL;
}

#define TEST_MERGE_SORT(IDX) void *test_merge_sort_ ## IDX ()\
{\
  DArray *darray = darray_init(array_ ## IDX, IDX);\
  void **result;\
\
  printf("test_merge_sort_" #IDX "()\n");\
  printf("-------------------\n");\
\
  result = merge_sort(darray->contents, IDX, &cmp_TYPE_lt);\
  cfree(darray->contents);\
  darray->contents = result;\
  check(array_equal(darray, res_array_ ## IDX, IDX), "array_" #IDX " result mismatch");\
\
  INV_DARRAY(darray);\
\
  cfree(darray->contents);\
  cfree(darray);\
\
  printf("(done.)\n");\
  return NULL;\
 error:\
  printf("print merge-sorted failed result:\n");\
  DArray_print(darray);\
  return "test_merge_sort_" #IDX "() failed";\
}


TEST_MERGE_SORT(3);
TEST_MERGE_SORT(4);
TEST_MERGE_SORT(5);
TEST_MERGE_SORT(6);
TEST_MERGE_SORT(7);
TEST_MERGE_SORT(8);
TEST_MERGE_SORT(9);
TEST_MERGE_SORT(10);
TEST_MERGE_SORT(11);

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
