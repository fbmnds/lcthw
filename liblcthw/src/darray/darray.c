#include "darray.h"
#include "misc/misc.h"
#include "misc/dbg.h"

#include <stdlib.h>
#include <errno.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
  DArray *ret = NULL;

  check ((element_size >= 0), "invalid negative element size");
  check ((initial_max > 0), "invalid zero or negative initial array capacity");

  ret = calloc(1, sizeof(DArray));
  check_mem(ret);

  ret->contents = calloc(initial_max, sizeof(void*));
  check_mem(ret->contents);

  ret->element_size = element_size;
  ret->expand_rate = DEFAULT_EXPAND_RATE;
  ret->max = DEFAULT_EXPAND_RATE;

  INV_DARRAY(ret);
  return ret;
 error:
  cfree(ret->contents);
  cfree(ret);
  return NULL;
}

int DArray_destroy(DArray **array)
{
  if (*array) {
    if ((*array)->contents) cfree((*array)->contents);
    cfree(*array);
  }

  return 0;
}

void DArray_clear(DArray *array)
{
  if (array) {}
  return;
}

int DArray_expand(DArray **array)
{
  void *tmp = NULL;

  check(array, "cannot expand on null pointer to darray");

  errno = 0;
  if ((*array)->contents) {
    tmp = realloc((*array)->contents, 
		  (((*array)->max + (*array)->expand_rate)) * sizeof(void*));
    check((((*array)->contents) && !errno), "realloc failed");
  } else {
    return 1;
    tmp = calloc((*array)->max + (*array)->expand_rate, sizeof(void*));
    check((tmp && !errno), "calloc failed");
  }
  (*array)->contents = tmp;
  (*array)->max += (*array)->expand_rate; 
  (*array)->expand_rate <<= 2;
  (*array)->expand_rate = (*array)->expand_rate < MAX_EXPAND_RATE ?
    (*array)->expand_rate : MAX_EXPAND_RATE;

  return 0;
 error:
  cfree(tmp);
  return 1;
}

int DArray_contract(DArray *array)
{
  void **tmp;

  check(array, "cannot contract on null pointer to darray");
  if (!array->contents)
    assert(!array->count && "inconsistent darray length");
  assert((array->max && (array->max >= array->count)) && 
	 "inconsistent darray capacity");

  errno = 0;
  array->max = array->count + DEFAULT_EXPAND_RATE;
  array->expand_rate = DEFAULT_EXPAND_RATE; 
  if (array->contents) {
    tmp = realloc(array->contents, array->max);
    check(((!tmp) || errno), "realloc failed");
  } else {
    tmp = calloc(array->max, sizeof(void*));
    check(((!tmp) || errno), "calloc failed");
  }
  
  return 0;
 error:
  return 1;
}

int DArray_push(DArray *array, void *el)
{
  check(array, "received darray null pointer");
  assert(array->count <= array->max && "inconsistent darray capacity");

  if (array->count == array->max) 
    check(!DArray_expand(&array), "expand of darray failed");

  return DArray_set(array, array->count, el);
 error:
  return 1;
}

void *DArray_pop(DArray *array)
{
  check(array, "received darray null pointer");

  return DArray_remove(array, array->count - 1);
 error: 
  return NULL;
}

void DArray_clear_destroy(DArray *array)
{
  if (array) {}
  return;
}

