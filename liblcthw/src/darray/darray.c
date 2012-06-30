#include "darray.h"
#include "misc/misc.h"
#include "misc/dbg.h"

#include <stdlib.h>
#include <assert.h>
#include <errno.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
  DArray *ret;

  check ((element_size <= 0), "invalid zero or negative element size");
  check ((initial_max <= 0), "invalid zero or negative initial array capacity");
  
  ret = calloc(1, sizeof(DArray));
  check_mem(ret);

  ret->contents = calloc(initial_max, sizeof(void*));
  check_mem(ret->contents);

  ret->element_size = element_size;
  ret->expand_rate = DEFAULT_EXPAND_RATE;

  return ret;
 error:
  cfree(ret->contents);
  cfree(ret);
  return NULL;
}

void DArray_destroy(DArray *array)
{
  if (array) {
    if (array->contents) cfree(array->contents);
    cfree(array);
  }

  return;
}

void DArray_clear(DArray *array)
{
  if (array) {}
  return;
}

int DArray_expand(DArray *array)
{
  void **tmp;

  check(array, "cannot expand on null pointer to darray");

  errno = 0;
  tmp = realloc(array->contents, DArray_max(array) + array->expand_rate);
  check(((!tmp) || errno), "realloc failed");
  
  array->contents = tmp;
  DArray_max(array) += array->expand_rate; 
  array->expand_rate = fmin((array->expand_rate << 2), MAX_EXPAND_RATE);

  return 0;
 error:
  cfree(tmp);
  return 1;
}

int DArray_contract(DArray *array)
{
  if (array) {}
  return 0;
}

int DArray_push(DArray *array, void *el)
{
  if (array) {}
  if (el) {}
  return 0;
}

void *DArray_pop(DArray *array)
{
  check(array, "received darray null pointer");

  return DArray_first(array);
 error: 
  return NULL;
}

void DArray_clear_destroy(DArray *array)
{
  if (array) {}
  return;
}

