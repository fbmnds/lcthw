#ifndef _DArray_h 
#define _DArray_h 

#include <stdlib.h> 
#include "misc/misc.h"
#include "misc/dbg.h"

typedef struct DArray { 
  int end;              /* index + 1 of last element of darray */
  int max;              /* max number of elements */
  size_t element_size;
  size_t expand_rate;
  void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);

void DArray_clear(DArray *array);

int DArray_expand(DArray *array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end        /* index + 1 of last element of darray */
#define DArray_count(A) DArray_end(A)  /* index + 1 = number of elements of darray */
#define DArray_max(A) ((A)->max)       /* max number of elements */
#define DEFAULT_EXPAND_RATE 256
#define MAX_EXPAND_RATE 60000

inline static void DArray_set(DArray *array, int i, void *el)
{
  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content");
  check((i > 0 && i < DArray_max(array)), "out-of-bound index for darray");

  if (!el) log_warn("received null pointer as content");
  array->contents[i] = el; 

error:
  return; 
}

inline static void *DArray_get(DArray *array, int i)
{
  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content");
  check((i > 0 && i < array->max), "out-of-bound index for darray");

  return array->contents[i]; 
error:
  return NULL; 
}

static inline void *DArray_remove(DArray *array, int i)
{
  void *el;
  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content");
  check((i > 0 && i < DArray_max(array)), "out-of-bound index for darray");
  el = array->contents[i];

  array->contents[i] = NULL;

 error:
  return el; 
}

static inline void *DArray_new(DArray *array)
{
  check(array->element_size > 0, "received nonpositive size for darray.");
  
  return calloc(1, array->element_size);
error:
  return NULL;
}

#define DArray_free(E) cfree((E))

#endif
